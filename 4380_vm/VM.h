//
//  VM.h
//  4380_vm
//
//  Created by jing hong chen on 9/26/18.
//  Copyright © 2018 jing hong chen. All rights reserved.
//

#ifndef VM_h
#define VM_h
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#define REG_SIZE 8  // total general regesters
#define MEM_SIZE 10000  // total bytes of memory
#define FIX_LENGTH 12  // fixed length of an instrution
#define JMP 1
#define JMR 2
#define BNZ 3
#define BGT 4
#define BLT 5
#define BRZ 6
#define MOV 7
#define LDA 8
#define STR 9
#define LDR 10
#define STB 11
#define LDB 12
#define ADD 13
#define ADI 14
#define SUB 15
#define MUL 16
#define DIV 17
#define AND 18
#define OR 19
#define CMP 20
#define TRP 21
#define _INT -4
#define _BYT -1

struct Instruction {
    int OpCode;
    int Oprand1;
    int Oprand2;
};

class VM {
private:
    int PC; // VM program conter register
    int REG[REG_SIZE];  // VM registers
    char MEM[MEM_SIZE];  // VM memory
    std::map<std::string, int> OpCodeTable;  // Operator Codes map (including Directives
    std::map<std::string, int> SymbolTable;  // Operator Codes map (including Directives

public:
    VM() {
        PC = 0;
        
        OpCodeTable.insert(std::pair<std::string, int>("JMP", JMP));
        OpCodeTable.insert(std::pair<std::string, int>("JMR", JMR));
        OpCodeTable.insert(std::pair<std::string, int>("BNZ", BNZ));
        OpCodeTable.insert(std::pair<std::string, int>("BGT", BGT));
        OpCodeTable.insert(std::pair<std::string, int>("BLT", BLT));
        OpCodeTable.insert(std::pair<std::string, int>("BRZ", BRZ));
        OpCodeTable.insert(std::pair<std::string, int>("MOV", MOV));
        OpCodeTable.insert(std::pair<std::string, int>("LDA", LDA));
        OpCodeTable.insert(std::pair<std::string, int>("STR", STR));
        OpCodeTable.insert(std::pair<std::string, int>("LDR", LDR));
        OpCodeTable.insert(std::pair<std::string, int>("STB", STB));
        OpCodeTable.insert(std::pair<std::string, int>("LDB", LDB));
        OpCodeTable.insert(std::pair<std::string, int>("ADD", ADD));
        OpCodeTable.insert(std::pair<std::string, int>("ADI", ADI));
        OpCodeTable.insert(std::pair<std::string, int>("SUB", SUB));
        OpCodeTable.insert(std::pair<std::string, int>("MUL", MUL));
        OpCodeTable.insert(std::pair<std::string, int>("DIV", DIV));
        OpCodeTable.insert(std::pair<std::string, int>("AND", AND));
        OpCodeTable.insert(std::pair<std::string, int>("OR", OR));
        OpCodeTable.insert(std::pair<std::string, int>("CMP", CMP));
        OpCodeTable.insert(std::pair<std::string, int>("TRP", TRP));
        OpCodeTable.insert(std::pair<std::string, int>(".INT", _INT));
        OpCodeTable.insert(std::pair<std::string, int>(".BYT", _BYT));
    }
    
    void loadInstruction(int addr, int opcode, int oprand1, int oprand2) {
        Instruction * ip = reinterpret_cast<Instruction *>(& MEM[addr]);
        ip->OpCode = opcode;
        ip->Oprand1 = oprand1;
        ip->Oprand2 = oprand2;
    }
    
    Instruction * fetchInstruction(int addr) {
        if (addr + FIX_LENGTH > MEM_SIZE) {
            return nullptr;
        }
        return reinterpret_cast<Instruction *>(& MEM[addr]);
    }
    
    // set a JMP instruction to the beginning of Memory, jump to the real start point
    void setProgramStartPoint(int startPoint) {
        loadInstruction(0, JMP, startPoint, 0);
    }
    
    int getInt(int addr) {
        int * p = reinterpret_cast<int *>(& MEM[addr]);
        return *p;
    }
    
    bool assemblyPass1(std::string fileName) {
        std::ifstream inputFile(fileName);
        if (inputFile) {
            std::string line;
            int lineCounter = 0;
            int addrCounter = FIX_LENGTH;  //reserve first 12 bytes for start JMP
            int tokenCounter = 0;
            // check the input assembly file by Pass 1
            //ignore all the whitespace
            while (std::getline(inputFile, line)) {
                lineCounter++;
                unsigned long firstCharPos = line.find_first_not_of(" \t\n\r\v\f");
                // skip empty lines and comments (start with ';')
                if (firstCharPos != std::string::npos && line.at(firstCharPos) != ';') {
                    // split a line into tokens
                    std::istringstream iss(line);
                    std::vector<std::string> tokens((std::istream_iterator<std::string>(iss)),std::istream_iterator<std::string>());
                    // every line of code should contain at least two token
                    if (tokens.size() < 2) {
                        std::cout << "Command line too short. (line: " << lineCounter << ")\n";
                        return false;
                    }
                    tokenCounter = 0;
                    if (OpCodeTable.find(tokens[tokenCounter]) == OpCodeTable.end()) {
                        // if first token is a Label, check if it is a new one, if yes, put it in the Symbol table
                        if (SymbolTable.find(tokens[tokenCounter]) != SymbolTable.end()) {
                            std::cout << "Repeated Label. (line: " << lineCounter << ")\n";
                            return false;
                        }
                        SymbolTable.insert(std::pair<std::string, int>(tokens[tokenCounter], addrCounter));
                        tokenCounter++;
                        if (OpCodeTable.find(tokens[tokenCounter]) == OpCodeTable.end()) {
                            std::cout << "Error format command line. (line: " << lineCounter << ")\n";
                            return false;
                        }
                    } // after this checking, we found a OpCode, and the tokenCounter is pointing to the OpCode
                    if (OpCodeTable[tokens[tokenCounter]] > 0) {
                        // it is an Instruction
                        addrCounter += FIX_LENGTH;
                    } else {
                        // it is a directive
                        addrCounter += -OpCodeTable[tokens[tokenCounter]];
                    }
                }
            }
            // pass first checking step
            return true;
        } else {
            std::cout << "Cannot open the file: " << fileName << std::endl;
            return false;
        }
    }
    
    bool assemblyPass2(std::string fileName) {
        std::ifstream inputFile(fileName);
        if (inputFile) {
            std::string line;
            int lineCounter = 0;
            int addrCounter = FIX_LENGTH;   //reserve first 12 bytes for start JMP
            int tokenCounter = 0;
            bool programStart = false;
            // check the input assembly file by Pass 2, if commands are correct, load them to Memory
            //ignore all the whitespace
            while (std::getline(inputFile, line)) {
                lineCounter++;
                unsigned long firstCharPos = line.find_first_not_of(" \t\n\r\v\f");
                // skip empty lines and comments (start with ';')
                if (firstCharPos != std::string::npos && line.at(firstCharPos) != ';') {
                    // split a line into tokens
                    std::istringstream iss(line);
                    std::vector<std::string> tokens((std::istream_iterator<std::string>(iss)),std::istream_iterator<std::string>());
                    // every line of code should contain at least two token
                    if (tokens.size() < 2) {
                        std::cout << "Command line too short. (line: " << lineCounter << ")\n";
                        return false;
                    }
                    tokenCounter = 0;
                    if (OpCodeTable.find(tokens[tokenCounter]) == OpCodeTable.end()) {
                        tokenCounter++;
                        if (OpCodeTable.find(tokens[tokenCounter]) == OpCodeTable.end()) {
                            std::cout << "Error format command line. (line: " << lineCounter << ")\n";
                            return false;
                        }
                    } // after this checking, we found a OpCode, and the tokenCounter is pointing to the OpCode
                    if (OpCodeTable[tokens[tokenCounter]] > 0) {
                        // it is an Instruction
                        if (!programStart) {
                            setProgramStartPoint(addrCounter);
                            programStart = true;
                        }
                        switch (OpCodeTable[tokens[tokenCounter]]) {
                            case JMP:
                                if (tokenCounter + 1 < tokens.size() && SymbolTable.find(tokens[tokenCounter + 1]) != SymbolTable.end()) {
                                    loadInstruction(addrCounter, JMP, SymbolTable[tokens[tokenCounter + 1]], 0);
                                } else {
                                    std::cout << "Command Line Error. (line: " << lineCounter << ")\n";
                                    return false;
                                }
                                break;
                            case JMR:
                                break;
                            case BNZ:
                                break;
                            case BGT:
                                break;
                            case BLT:
                                break;
                            case BRZ:
                                break;
                            case MOV:
                                break;
                            case LDA:
                                break;
                            case STR:
                                break;
                            case LDR:
                                break;
                            case STB:
                                break;
                            case LDB:
                                break;
                            case ADD:
                                break;
                            case ADI:
                                break;
                            case SUB:
                                break;
                            case MUL:
                                break;
                            case DIV:
                                break;
                            case AND:
                                break;
                            case OR:
                                break;
                            case CMP:
                                break;
                            case TRP:
                                if (tokenCounter + 1 < tokens.size() && tokens[tokenCounter + 1].size() == 1 && tokens[tokenCounter + 1].at(0) <= '4' && tokens[tokenCounter + 1].at(0) >= '0') {
                                    loadInstruction(addrCounter, TRP, tokens[tokenCounter + 1].at(0) - '0', 0);
                                } else {
                                    std::cout << "Command Line Error. (line: " << lineCounter << ")\n";
                                    return false;
                                }
                                break;
                        }
                        addrCounter += FIX_LENGTH;
                    } else {
                        // it is a directive
                        addrCounter += -OpCodeTable[tokens[tokenCounter]];
                    }
                }
            }
            // pass first checking step
            return true;
        } else {
            std::cout << "Cannot open the file: " << fileName << std::endl;
            return false;
        }
    }
    
    void run() {
        bool programStop = false;
        PC = 0; // start from MEM[0]
        while (!programStop && PC < MEM_SIZE) {
            Instruction * ip = fetchInstruction(PC);
            if (ip == nullptr) {
                std::cout << "Out of Memory!" << std::endl;
                return;
            }
            switch (ip -> OpCode) {
                case JMP:
                    PC = ip -> Oprand1;
                    break;
                case JMR:
                    break;
                case BNZ:
                    break;
                case BGT:
                    break;
                case BLT:
                    break;
                case BRZ:
                    break;
                case MOV:
                    break;
                case LDA:
                    break;
                case STR:
                    break;
                case LDR:
                    break;
                case STB:
                    break;
                case LDB:
                    break;
                case ADD:
                    break;
                case ADI:
                    break;
                case SUB:
                    break;
                case MUL:
                    break;
                case DIV:
                    break;
                case AND:
                    break;
                case OR:
                    break;
                case CMP:
                    break;
                case TRP:
                    switch (ip -> Oprand1) {
                        case 0:
                            std::cout << "Program end.\n";
                            programStop = true;
                            break;
                            
                        default:
                            std::cout << "Unexpected Error!" << std::endl;
                            programStop = true;
                            break;
                    }
                    break;
            }
        }
    }
    
};

#endif /* VM_h */
