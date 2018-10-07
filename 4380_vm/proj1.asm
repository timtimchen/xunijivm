; ############################
; SC 4380 Project 1
; by Jinghong Chen
; ############################

B1		.INT	300
B2		.INT	150
B3		.INT	50
B4		.INT	20
B5		.INT	10
B6		.INT	5

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

START	LDB		R3, C
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
		
AddB	LDR		R1, B1
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
		LDB		R3, newline
		TRP		3
		TRP		3

END		TRP		0
