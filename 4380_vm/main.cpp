//
//  main.cpp
//  4380_vm
//
//  Created by jing hong chen on 9/18/18.
//  Copyright © 2018 jing hong chen. All rights reserved.
//

#include "VM.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        cout << "Please input the assembly file name in the command line." << endl;
    }
    else {
        VM newVM;
        if (newVM.assemblyPass1(argv[1])) {
            if (newVM.assemblyPass2(argv[1])) {
                newVM.run();
            }
        }
    }
    
    return 0;
}

