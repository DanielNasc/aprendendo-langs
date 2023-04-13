.data
	zero:		.double 	0.0
    	um:		.double		1.0
    	dois:		.double		2.0
    	quatro:		.double 	4.0
    	cem_milhoes:	.double 	100000000.0

.text
	l.d	$f0,	um	# sera o tamanho partição
	l.d	$f2,	zero 	# soma
	l.d	$f6,	cem_milhoes
	l.d	$f8, 	zero	# x
	l.d	$f10,	um	# um
	l.d	$f16	quatro	# 4
	
	div.d	$f0,	$f0,	$f6 # tamanho da partição -> (b -a)/N -> 1/100000000
	
	li	$v0,	3
	mov.d	$f12,	$f0
	syscall
	
	riemman:
		mul.d	$f14,	$f8,	$f8 	# x*x
		add.d	$f14,	$f14,	$f10	# x*x + 1
		div.d	$f14,	$f16,	$f14	# 4 / (x*x + 1)
		add.d	$f2,	$f2,	$f14	# sum += 4 / (x*x + 1)
		add.d	$f8,	$f8,	$f0	# x += dx
		
		c.lt.d	$f8,	$f10		# x < 1?
		bc1t	riemman			# if true, then go to riemman again
	
	mul.d	$f2,	$f2,	$f0
	li	$v0,	3
	mov.d	$f12,	$f2
	syscall
