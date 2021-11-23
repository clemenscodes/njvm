//
// prog2.asm -- an assembler example with local variables
//

// local Integer x;
// local Integer y;
// x = 2;
// y = x + 3;
// x = 7 * y + x;
// z = x + 5;
// writeInteger(z + -33);
// writeCharacter('\n');

	asf	3
	pushc	2
	popl	0
	pushl	0
	pushc	3
	add
	popl	1
	pushc	7
	pushl	1
	mul
	pushl	0
	add
	popl	0
	pushl	0
    pushc   5
    add
    popl    2
	pushl	2
	pushc	-33
	add
	wrint
	pushc	'\n'
	wrchr
	rsf
	halt
