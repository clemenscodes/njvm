//
// version
//
	.vers	8

//
// execution framework
//
__start:
	call	_main
	call	_exit
__stop:
	jmp	__stop

//
// Integer readInteger()
//
_readInteger:
	asf	0
	rdint
	popr
	rsf
	ret

//
// void writeInteger(Integer)
//
_writeInteger:
	asf	0
	pushl	-3
	wrint
	rsf
	ret

//
// Character readCharacter()
//
_readCharacter:
	asf	0
	rdchr
	popr
	rsf
	ret

//
// void writeCharacter(Character)
//
_writeCharacter:
	asf	0
	pushl	-3
	wrchr
	rsf
	ret

//
// Integer char2int(Character)
//
_char2int:
	asf	0
	pushl	-3
	popr
	rsf
	ret

//
// Character int2char(Integer)
//
_int2char:
	asf	0
	pushl	-3
	popr
	rsf
	ret

//
// void exit()
//
_exit:
	asf	0
	halt
	rsf
	ret

//
// void writeString(String)
//
_writeString:
	asf	1
	pushc	0
	popl	0
	jmp	_writeString_L2
_writeString_L1:
	pushl	-3
	pushl	0
	getfa
	call	_writeCharacter
	drop	1
	pushl	0
	pushc	1
	add
	popl	0
_writeString_L2:
	pushl	0
	pushl	-3
	getsz
	lt
	brt	_writeString_L1
	rsf
	ret

//
// void main()
//
_main:
	asf	0
	call	_readInteger
	pushr
	pushc	42
	eq
	brf	__1
	pushc	9
	newa
	dup
	pushc	0
	pushc	69
	putfa
	dup
	pushc	1
	pushc	120
	putfa
	dup
	pushc	2
	pushc	97
	putfa
	dup
	pushc	3
	pushc	99
	putfa
	dup
	pushc	4
	pushc	116
	putfa
	dup
	pushc	5
	pushc	108
	putfa
	dup
	pushc	6
	pushc	121
	putfa
	dup
	pushc	7
	pushc	33
	putfa
	dup
	pushc	8
	pushc	10
	putfa
	call	_writeString
	drop	1
	jmp	__2
__1:
	pushc	6
	newa
	dup
	pushc	0
	pushc	78
	putfa
	dup
	pushc	1
	pushc	111
	putfa
	dup
	pushc	2
	pushc	112
	putfa
	dup
	pushc	3
	pushc	101
	putfa
	dup
	pushc	4
	pushc	33
	putfa
	dup
	pushc	5
	pushc	10
	putfa
	call	_writeString
	drop	1
__2:
__0:
	rsf
	ret
