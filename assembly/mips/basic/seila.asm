.data
    	um:	.double	1.0
    	dois:	.double	2.0
.text
	.globl divv
		l.d	$f0,	um
		l.d	$f2,	um
		l.d	$f4, 	dois
	divv: 					# loop
		div.d	$f0,	$f0,	$f4 	# divisão: eps = eps / 2
		add.d	$f6,	$f2,	$f0 	# soma: soma = 1 + eps
		c.eq.d	$f6, 	$f2		# checa: soma == 1
		bc1f divv
	mul.d	$f0,	$f0,	$f4		# last number x that satisfies x + 1 = 1: 
	add.d	$f10,	$f2,	$f0		# soma: 1 + eps
	
	
	
	li $v0, 3
	mov.d $f12, $f10
	syscall