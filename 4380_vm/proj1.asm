; ############################
; SC 4380 Project 1
; by Jinghong Chen
; ############################

A1		.INT	1
A2		.INT	2
A3		.INT	3
A4		.INT	4
A5		.INT	5
A6		.INT	6

B1		.INT	300
B2		.INT	150
B3		.INT	50
B4		.INT	20
B5		.INT	10
B6		.INT	5

C1		.INT	500
C2		.INT	2
C3		.INT	5
C4		.INT	10

C		.BYT	'C'
h		.BYT	'h'
e		.BYT	'e'
n		.BYT	'n'
J		.BYT	'J'
i		.BYT	'i'
g		.BYT	'g'
o		.BYT	'o'
comma	.BYT	','
newline	.BYT	10
space	.BYT	32

START	LDB		R3, C		;print my name
		TRP		3
		LDB		R3, h
		TRP		3
		LDB		R3, e
		TRP		3
		LDB		R3, n
		TRP		3
		LDB		R3, comma
		TRP		3
		LDB		R3, space
		TRP		3
		LDB		R3, J
		TRP		3
		LDB		R3, i
		TRP		3
		LDB		R3, n
		TRP		3
		LDB		R3, g
		TRP		3
		LDB		R3, h
		TRP		3
		LDB		R3, o
		TRP		3
		LDB		R3, n
		TRP		3
		LDB		R3, g
		TRP		3
		LDB		R3, newline
		TRP		3
		TRP		3
		
AddTask	LDR		R1, B1
		LDR		R2,	B2
		ADD		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		LDR		R2,	B3
		ADD		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		LDR		R2,	B4
		ADD		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		LDR		R2,	B5
		ADD		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		LDR		R2,	B6
		ADD		R1,	R2
		MOV		R3, R1
		TRP		1		
		MOV		R4, R1			;move the result to R4
		LDB		R3, newline
		TRP		3
		TRP		3

MulTask	LDR		R1, A1
		LDR		R2,	A2
		MUL		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		LDR		R2,	A3
		MUL		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		LDR		R2,	A4
		MUL		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		LDR		R2,	A5
		MUL		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		LDR		R2,	A6
		MUL		R1,	R2
		MOV		R3, R1
		TRP		1		
		MOV		R5, R1		;move the result to R5
		LDB		R3, newline
		TRP		3
		TRP		3

DivTask	MOV		R1, R4
		LDR		R2,	B1
		DIV		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		MOV		R1, R4
		LDR		R2,	B2
		DIV		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		MOV		R1, R4
		LDR		R2,	B3
		DIV		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		MOV		R1, R4
		LDR		R2,	B4
		DIV		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		MOV		R1, R4
		LDR		R2,	B5
		DIV		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		MOV		R1, R4
		LDR		R2,	B6
		DIV		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, newline
		TRP		3
		TRP		3

SubTask	MOV		R1, R5
		LDR		R2,	C1
		SUB		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		MOV		R1, R5
		LDR		R2,	C2
		SUB		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		MOV		R1, R5
		LDR		R2,	C3
		SUB		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, space
		TRP		3
		TRP		3
		MOV		R1, R5
		LDR		R2,	C4
		SUB		R1,	R2
		MOV		R3, R1
		TRP		1		
		LDB		R3, newline
		TRP		3
		TRP		3

END		TRP		0
