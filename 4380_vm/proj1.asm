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
space	.BYT	20

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
END		TRP		0
