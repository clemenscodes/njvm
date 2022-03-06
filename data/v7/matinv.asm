//
// version
//
	.vers	7

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
// Integer gcd(Integer, Integer)
//
_gcd:
	asf	1
	jmp	__2
__1:
	pushl	-4
	pushl	-3
	mod
	popl	0
	pushl	-3
	popl	-4
	pushl	0
	popl	-3
__2:
	pushl	-3
	pushc	0
	ne
	brt	__1
__3:
	pushl	-4
	popr
	jmp	__0
__0:
	rsf
	ret

//
// record { Integer num; Integer den; } newFraction(Integer, Integer)
//
_newFraction:
	asf	4 // stackframe with four local variables
	pushl	-4 // put first function paramter on the stack
	pushc	0 // put 0 on the stack
	lt // check if paramter is negative
	brf	__5 // jump to __5 if paramter is not negative
	pushc	0 // put 0 on the stack
	pushl	-4 // put first function paramter on the stack
	sub // subtract function parameter from 0, getting the negative value
	popl	0 // saving the negative value of the first function paramter in the first local variable
	jmp	__6 // jump to __6
__5:
	pushl	-4 // put first function paramter on the stack
	popl	0 // save value of first function paramter in first local variable
__6:
	pushl	-3 // put second function parameter on the stack 
	pushc	0 // put 0 on the stack
	lt // check if second function parameter is negative
	brf	__7 // jump to __7 if second function parameter is not negative
	pushc	0 // put 0 on the stack
	pushl	-3 // put second function parameter on the stack
	sub // subtract value of second function parameter from 0, getting the negative value
	popl	1 // saving the negative value of the second function paramter in the second local variable
	jmp	__8 // jump to __8)
__7:
	pushl	-3 // put second function parameter on the stack
	popl	1 // save the value of the second function parameter in the second local variable
__8:
	pushl	0 // put the first local variable on the stack
	pushl	1 // put the second local variable on the stack
	call	_gcd // call function to compute the greatest common divisor of the two local variables
	drop	2 // cleanup function call parameters
	pushr // put return value of gcd on the stack
	popl	2 // save return value of gcd in the third local variable
	new	2 // create a new record with two fields
	popl	3 // save the record in the fourth local variable
	pushl	-4 // put the first function parameter on the stack
	pushc	0 // put 0 on the stack
	lt // check if first function paramter is negative
	pushl	-3 // put the second function parameter on the stack
	pushc	0 // put 0 on the stack
	lt // check if the second function paramter is negative
	ne // check if any of the function parameters is negative but the other is not
	brf	__9 // jump to __0
	pushl	3 // put fourth local variable on the stack
	pushc	0 // put 0 on the stack
	pushl	0 // put the first local variable on the stack
	sub // subtract the value of the first local variable from 0, getting the negative value of it
	pushl	2 // put the third local variable on the stack
	div // divide the negative value of the first local variable with the value of the third local variable
	putf	0 // save the result of the previous computation in the first field of the record
	jmp	__10 // jump to __10
__9:
	pushl	3 // put fourth local variable on the stack
	pushc	0 // put 0 on the stack
	pushl	2 // put the third local variable on the stack
	div // divide the value of the first local variable with the value of the third local variable
	putf	0 // save the result of the previous computation in the first field of the record
__10:
	pushl	3 // put fourth local variable on the stack
	pushl	1 // put second local variable on the stack
	pushl	2 // put third local variable on the stack
	div // divide the value of the second local variable with the value of the third local variable
	putf	1 // save the result of the previous computation in the second field of the record
	pushl	3 // put fourth local variable on the stack
	popr // save the edited record in the return value register
	jmp	__4 // jump to __4
__4:
	rsf // reset the stack frame
	ret // end function call, jump back to return address

//
// void writeFraction(record { Integer num; Integer den; })
//
_writeFraction:
	asf	0
	pushl	-3
	getf	0
	call	_writeInteger
	drop	1
	pushc	1
	newa
	dup
	pushc	0
	pushc	47
	putfa
	call	_writeString
	drop	1
	pushl	-3
	getf	1
	call	_writeInteger
	drop	1
__11:
	rsf
	ret

//
// record { Integer num; Integer den; } negFraction(record { Integer num; Integer den; })
//
_negFraction:
	asf	0
	pushc	0
	pushl	-3
	getf	0
	sub
	pushl	-3
	getf	1
	call	_newFraction
	drop	2
	pushr
	popr
	jmp	__12
__12:
	rsf
	ret

//
// record { Integer num; Integer den; } addFraction(record { Integer num; Integer den; }, record { Integer num; Integer den; })
//
_addFraction:
	asf	0
	pushl	-4
	getf	0
	pushl	-3
	getf	1
	mul
	pushl	-3
	getf	0
	pushl	-4
	getf	1
	mul
	add
	pushl	-4
	getf	1
	pushl	-3
	getf	1
	mul
	call	_newFraction
	drop	2
	pushr
	popr
	jmp	__13
__13:
	rsf
	ret

//
// record { Integer num; Integer den; } subFraction(record { Integer num; Integer den; }, record { Integer num; Integer den; })
//
_subFraction:
	asf	0
	pushl	-4
	getf	0
	pushl	-3
	getf	1
	mul
	pushl	-3
	getf	0
	pushl	-4
	getf	1
	mul
	sub
	pushl	-4
	getf	1
	pushl	-3
	getf	1
	mul
	call	_newFraction
	drop	2
	pushr
	popr
	jmp	__14
__14:
	rsf
	ret

//
// record { Integer num; Integer den; } mulFraction(record { Integer num; Integer den; }, record { Integer num; Integer den; })
//
_mulFraction:
	asf	0
	pushl	-4
	getf	0
	pushl	-3
	getf	0
	mul
	pushl	-4
	getf	1
	pushl	-3
	getf	1
	mul
	call	_newFraction
	drop	2
	pushr
	popr
	jmp	__15
__15:
	rsf
	ret

//
// record { Integer num; Integer den; } divFraction(record { Integer num; Integer den; }, record { Integer num; Integer den; })
//
_divFraction:
	asf	0
	pushl	-4
	getf	0
	pushl	-3
	getf	1
	mul
	pushl	-4
	getf	1
	pushl	-3
	getf	0
	mul
	call	_newFraction
	drop	2
	pushr
	popr
	jmp	__16
__16:
	rsf
	ret

//
// Fraction[][] newMatrix(record { Integer num; Integer den; }, record { Integer num; Integer den; }, record { Integer num; Integer den; }, record { Integer num; Integer den; })
//
_newMatrix:
	asf	1
	pushc	2
	newa
	popl	0
	pushl	0
	pushc	0
	pushc	2
	newa
	putfa
	pushl	0
	pushc	1
	pushc	2
	newa
	putfa
	pushl	0
	pushc	0
	getfa
	pushc	0
	pushl	-6
	putfa
	pushl	0
	pushc	0
	getfa
	pushc	1
	pushl	-5
	putfa
	pushl	0
	pushc	1
	getfa
	pushc	0
	pushl	-4
	putfa
	pushl	0
	pushc	1
	getfa
	pushc	1
	pushl	-3
	putfa
	pushl	0
	popr
	jmp	__17
__17:
	rsf
	ret

//
// void writeMatrix(Fraction[][])
//
_writeMatrix:
	asf	2
	pushc	0
	popl	0
	jmp	__20
__19:
	pushc	0
	popl	1
	jmp	__23
__22:
	pushl	-3
	pushl	0
	getfa
	pushl	1
	getfa
	call	_writeFraction
	drop	1
	pushc	2
	newa
	dup
	pushc	0
	pushc	32
	putfa
	dup
	pushc	1
	pushc	32
	putfa
	call	_writeString
	drop	1
	pushl	1
	pushc	1
	add
	popl	1
__23:
	pushl	1
	pushl	-3
	pushl	0
	getfa
	getsz
	lt
	brt	__22
__24:
	pushc	1
	newa
	dup
	pushc	0
	pushc	10
	putfa
	call	_writeString
	drop	1
	pushl	0
	pushc	1
	add
	popl	0
__20:
	pushl	0
	pushl	-3
	getsz
	lt
	brt	__19
__21:
	pushc	1
	newa
	dup
	pushc	0
	pushc	10
	putfa
	call	_writeString
	drop	1
__18:
	rsf
	ret

//
// Fraction[][] invertMatrix(Fraction[][])
//
_invertMatrix:
	asf	1
	pushl	-3
	pushc	0
	getfa
	pushc	0
	getfa
	pushl	-3
	pushc	1
	getfa
	pushc	1
	getfa
	call	_mulFraction
	drop	2
	pushr
	pushl	-3
	pushc	0
	getfa
	pushc	1
	getfa
	pushl	-3
	pushc	1
	getfa
	pushc	0
	getfa
	call	_mulFraction
	drop	2
	pushr
	call	_subFraction
	drop	2
	pushr
	popl	0
	pushl	0
	getf	0
	pushc	0
	eq
	brf	__26
	pushc	33
	newa
	dup
	pushc	0
	pushc	101
	putfa
	dup
	pushc	1
	pushc	114
	putfa
	dup
	pushc	2
	pushc	114
	putfa
	dup
	pushc	3
	pushc	111
	putfa
	dup
	pushc	4
	pushc	114
	putfa
	dup
	pushc	5
	pushc	58
	putfa
	dup
	pushc	6
	pushc	32
	putfa
	dup
	pushc	7
	pushc	109
	putfa
	dup
	pushc	8
	pushc	97
	putfa
	dup
	pushc	9
	pushc	116
	putfa
	dup
	pushc	10
	pushc	114
	putfa
	dup
	pushc	11
	pushc	105
	putfa
	dup
	pushc	12
	pushc	120
	putfa
	dup
	pushc	13
	pushc	32
	putfa
	dup
	pushc	14
	pushc	99
	putfa
	dup
	pushc	15
	pushc	97
	putfa
	dup
	pushc	16
	pushc	110
	putfa
	dup
	pushc	17
	pushc	110
	putfa
	dup
	pushc	18
	pushc	111
	putfa
	dup
	pushc	19
	pushc	116
	putfa
	dup
	pushc	20
	pushc	32
	putfa
	dup
	pushc	21
	pushc	98
	putfa
	dup
	pushc	22
	pushc	101
	putfa
	dup
	pushc	23
	pushc	32
	putfa
	dup
	pushc	24
	pushc	105
	putfa
	dup
	pushc	25
	pushc	110
	putfa
	dup
	pushc	26
	pushc	118
	putfa
	dup
	pushc	27
	pushc	101
	putfa
	dup
	pushc	28
	pushc	114
	putfa
	dup
	pushc	29
	pushc	116
	putfa
	dup
	pushc	30
	pushc	101
	putfa
	dup
	pushc	31
	pushc	100
	putfa
	dup
	pushc	32
	pushc	10
	putfa
	call	_writeString
	drop	1
	call	_exit
__26:
	pushl	-3
	pushc	1
	getfa
	pushc	1
	getfa
	pushl	0
	call	_divFraction
	drop	2
	pushr
	pushl	-3
	pushc	0
	getfa
	pushc	1
	getfa
	call	_negFraction
	drop	1
	pushr
	pushl	0
	call	_divFraction
	drop	2
	pushr
	pushl	-3
	pushc	1
	getfa
	pushc	0
	getfa
	call	_negFraction
	drop	1
	pushr
	pushl	0
	call	_divFraction
	drop	2
	pushr
	pushl	-3
	pushc	0
	getfa
	pushc	0
	getfa
	pushl	0
	call	_divFraction
	drop	2
	pushr
	call	_newMatrix
	drop	4
	pushr
	popr
	jmp	__25
__25:
	rsf
	ret

//
// void main()
//
_main:
	asf	3
	pushc	1
	newa
	dup
	pushc	0
	pushc	10
	putfa
	call	_writeString
	drop	1
	pushc	7
	pushc	1
	call	_newFraction
	drop	2
	pushr
	pushc	4
	pushc	1
	call	_newFraction
	drop	2
	pushr
	pushc	6
	pushc	1
	call	_newFraction
	drop	2
	pushr
	pushc	5
	pushc	1
	call	_newFraction
	drop	2
	pushr
	call	_newMatrix
	drop	4
	pushr
	popl	0
	pushl	0
	call	_writeMatrix
	drop	1
	pushl	0
	call	_invertMatrix
	drop	1
	pushr
	popl	1
	pushl	1
	call	_writeMatrix
	drop	1
	pushl	1
	call	_invertMatrix
	drop	1
	pushr
	popl	2
	pushl	2
	call	_writeMatrix
	drop	1
__27:
	rsf
	ret
