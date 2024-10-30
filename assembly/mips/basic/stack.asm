.data

.text
	li	$a0,	0
	
	jal	A
	
	li	$v0,	1
	syscall
	
	j	END
	
	A:
	addi	$a0,	$a0,	1
	
	subi	$sp,	$sp,	4
	sw	$ra,	($sp)
	
	jal	B
	
	lw	$ra,	($sp)
	addi	$sp,	$sp,	4
	jr	$ra
	
	
	B:
	addi	$a0,	$a0,	1
	
	subi	$sp,	$sp,	8
	sw	$ra,	($sp)
	
	jal	C
	
	lw	$ra,	($sp)
	addi	$sp,	$sp,	4
	
	jr	$ra
	

	END:
		li	$v0,	10
		syscall
		
	C:
	addi	$a0,	$a0,	1
	
	jr	$ra