.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
	li $v0, 4
	la $a0, _prompt
	syscall
	li $v0, 5
	syscall
	jr $ra

write:
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, _ret
	syscall
	move $v0, $0
	jr $ra

changeCal:
	subu $sp, $sp, 204
	sw $ra, 200($sp)
	sw $fp, 196($sp)
	addi $fp, $sp, 204
	sw $s0, -12($fp)
	sw $s1, -16($fp)
	sw $s2, -20($fp)
	sw $s3, -24($fp)
	sw $s4, -28($fp)
	sw $s5, -32($fp)
	sw $s6, -36($fp)
	sw $s7, -40($fp)
	sw $a0, -96($fp)
	lw $s0, -96($fp)
	addi $s1, $s0, 345
	addi $s2, $s1, -345
	sw $s1, -100($fp)
	lw $s1, -136($fp)
	mul $s3, $s0, $s1
	add $s4, $s2, $s3
	sw $s3, -108($fp)
	sw $s2, -104($fp)
	mul $s2, $s0, $s1
	sub $s3, $s4, $s2
	sw $s2, -116($fp)
	sw $s4, -112($fp)
	mul $s2, $s0, $s0
	add $s4, $s3, $s2
	sw $s2, -124($fp)
	sw $s3, -120($fp)
	mul $s2, $s0, $s0
	sub $s1, $s4, $s2
	sw $s2, -132($fp)
	sw $s4, -128($fp)
	li $v1, 2
	mul $s2, $s1, $v1
	li $v1, 3
	mul $s3, $s1, $v1
	sub $s4, $s2, $s3
	sw $s3, -144($fp)
	sw $s2, -140($fp)
	li $v1, 2
	mul $s2, $s1, $v1
	add $s3, $s4, $s2
	sw $s2, -152($fp)
	sw $s4, -148($fp)
	li $v0, 34
	li $v1, 2
	div $v0, $v1
	mflo $s2
	add $s4, $s3, $s2
	sw $s2, -160($fp)
	sw $s3, -156($fp)
	li $v0, 10
	li $v1, 3
	div $v0, $v1
	mflo $s2
	add $s3, $s4, $s2
	sw $s2, -168($fp)
	sw $s4, -164($fp)
	li $v0, 20
	li $v1, 1
	div $v0, $v1
	mflo $s2
	sub $s1, $s3, $s2
	sw $s2, -176($fp)
	sw $s3, -172($fp)
	li, $v0, 7
	addi $s2, $v0, 6
	li $v0, 11
	li $v1, 1
	mul $s3, $v0, $v1
	sub $s1, $s2, $s3
	sw $s3, -184($fp)
	sw $s2, -180($fp)
	li $v0, 4
	li $v1, 5
	mul $s2, $v0, $v1
	add $s3, $s0, $s2
	sw $s2, -188($fp)
	sw $s0, -96($fp)
	li $v0, 10
	li $v1, 2
	mul $s0, $v0, $v1
	sub $s2, $s3, $s0
	sw $s0, -196($fp)
	sw $s3, -192($fp)
	li $v0, 5
	li $v1, 6
	div $v0, $v1
	mflo $s0
	sub $s1, $s2, $s0
	sw $s0, -204($fp)
	sw $s2, -200($fp)
	sw $s1, -136($fp)
	move $v0, $s1
	j ret_changeCal
ret_changeCal:
	lw $s0, -12($fp)
	lw $s1, -16($fp)
	lw $s2, -20($fp)
	lw $s3, -24($fp)
	lw $s4, -28($fp)
	lw $s5, -32($fp)
	lw $s6, -36($fp)
	lw $s7, -40($fp)
	lw $ra, 200($sp)
	lw $fp, 196($sp)
	addi $sp, $sp, 204
	jr $ra

main:
	subu $sp, $sp, 304
	sw $ra, 300($sp)
	sw $fp, 296($sp)
	addi $fp, $sp, 304
	sw $s0, -12($fp)
	sw $s1, -16($fp)
	sw $s2, -20($fp)
	sw $s3, -24($fp)
	sw $s4, -28($fp)
	sw $s5, -32($fp)
	sw $s6, -36($fp)
	sw $s7, -40($fp)
	li, $v0, 7
	addi $s0, $v0, 6
	li $v0, 11
	li $v1, 1
	mul $s1, $v0, $v1
	sub $s2, $s0, $s1
	sw $s1, -104($fp)
	sw $s0, -100($fp)
	li, $v0, 8
	addi $s0, $v0, -4
	li, $v0, 4
	addi $s1, $v0, 4
	li $v0, 5
	li $v1, 6
	mul $s3, $v0, $v1
	li $v1, 3
	div $s3, $v1
	mflo $s4
	sw $s3, -120($fp)
	add $s3, $s1, $s4
	sw $s4, -124($fp)
	sw $s1, -116($fp)
	addi $s1, $s3, -4
	sw $s3, -128($fp)
	add $s3, $s2, $s0
	sub $s4, $s3, $s1
	sw $s3, -136($fp)
	add $s3, $s2, $s0
	li $v1, 2
	mul $s5, $s1, $v1
	add $s6, $s3, $s5
	sw $s5, -148($fp)
	sw $s3, -144($fp)
	add $s3, $s2, $s0
	add $s5, $s3, $s1
	sw $s3, -156($fp)
	li $s3, 42
	li $s7, 0
	sw $s5, -160($fp)
	add $s5, $s2, $s0
	sw $s0, -112($fp)
	sw $s2, -108($fp)
	add $s0, $s5, $s1
	sw $s1, -132($fp)
	sw $s5, -172($fp)
	sub $s1, $s0, $s4
	sw $s4, -140($fp)
	sw $s0, -176($fp)
	sub $s0, $s1, $s6
	sw $s6, -152($fp)
	sw $s1, -180($fp)
	lw $s1, -160($fp)
	add $s1, $s0, $s1
	sw $s1, -160($fp)
	sw $s0, -184($fp)
	sw $s3, -164($fp)
	sw $s7, -168($fp)
label0:
	lw $s0, -112($fp)
	lw $s1, -108($fp)
	sub $s2, $s0, $s1
	sw $s1, -108($fp)
	sw $s0, -112($fp)
	lw $s0, -160($fp)
	sw $s2, -188($fp)
	sw $s0, -160($fp)
	bge $s2, $s0, label1
	lw $s0, -168($fp)
	li $v1, 4
	mul $s1, $s0, $v1
	sw $s0, -168($fp)
	lw $s0, -164($fp)
	add $s2, $s0, $s1
	sw $s1, -192($fp)
	sw $s0, -164($fp)
	addi $s0, $s2, 3
	sw $s2, -196($fp)
	addi $s1, $s0, 4
	sw $s0, -200($fp)
	addi $s0, $s1, 5
	sw $s1, -204($fp)
	sw $s0, -164($fp)
	lw $s0, -112($fp)
	move $a0, $s0
	sw $s0, -112($fp)
	jal changeCal
	move $s0, $v0
	sw $s0, -208($fp)
	lw $s0, -160($fp)
	lw $s1, -208($fp)
	sub $s2, $s0, $s1
	sw $s1, -208($fp)
	lw $s1, -108($fp)
	li $v1, 2
	mul $s3, $s1, $v1
	sw $s1, -108($fp)
	add $s1, $s2, $s3
	sw $s3, -216($fp)
	sw $s2, -212($fp)
	lw $s2, -132($fp)
	lw $s3, -140($fp)
	mul $s4, $s2, $s3
	sw $s2, -132($fp)
	sw $s3, -140($fp)
	add $s2, $s1, $s4
	sw $s4, -224($fp)
	sw $s1, -220($fp)
	sub $s1, $s2, $s0
	sw $s0, -160($fp)
	sw $s2, -228($fp)
	lw $s0, -168($fp)
	addi $s2, $s0, 1
	addi $s0, $s2, 0
	sw $s2, -236($fp)
	addi $s2, $s0, 3
	addi $s0, $s2, 1
	sw $s2, -240($fp)
	addi $s2, $s0, -2
	addi $s0, $s2, -2
	sw $s2, -244($fp)
	li $v1, 3
	div $s0, $v1
	mflo $s2
	li $v1, 3
	mul $s3, $s2, $v1
	sw $s2, -248($fp)
	sub $s2, $s0, $s3
	sw $s3, -252($fp)
	sw $s0, -168($fp)
	sw $s1, -232($fp)
	sw $s2, -256($fp)
	lw $s0, -108($fp)
	move $a0, $s0
	sw $s0, -108($fp)
	jal changeCal
	move $s0, $v0
	sw $s0, -260($fp)
	lw $s0, -108($fp)
	lw $s1, -260($fp)
	sub $s2, $s0, $s1
	sw $s1, -260($fp)
	sw $s0, -108($fp)
	lw $s0, -112($fp)
	add $s1, $s2, $s0
	sw $s2, -264($fp)
	sub $s2, $s1, $s0
	sw $s0, -112($fp)
	sw $s1, -268($fp)
	lw $s0, -132($fp)
	add $s1, $s2, $s0
	sw $s2, -272($fp)
	sub $s2, $s1, $s0
	sw $s0, -132($fp)
	sw $s1, -276($fp)
	lw $s0, -256($fp)
	sw $s0, -256($fp)
	sw $s2, -280($fp)
	bne $s0, $s2, label2
	lw $s0, -160($fp)
	addi $s1, $s0, 1
	sw $s0, -160($fp)
	addi $s0, $s1, 1
	sw $s1, -284($fp)
	sw $s0, -160($fp)
label2:
	lw $s0, -160($fp)
	addi $s1, $s0, -2
	sw $s0, -160($fp)
	addi $s0, $s1, 1
	sw $s1, -288($fp)
	sw $s0, -160($fp)
	j label0
label1:
	lw $s0, -164($fp)
	addi $s1, $s0, -2
	addi $s2, $s1, 3
	sw $s1, -292($fp)
	move $a0, $s2
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	sw $s2, -296($fp)
	move $s1, $s0
	sw $s0, -164($fp)
	sw $s1, -168($fp)
label3:
	li, $v0, 1200
	addi $s0, $v0, 22
	lw $s1, -164($fp)
	sw $s1, -164($fp)
	sw $s0, -300($fp)
	blt $s1, $s0, label4
	lw $s0, -164($fp)
	addi $s1, $s0, 1024
	sw $s0, -164($fp)
	sw $s1, -168($fp)
	lw $s0, -164($fp)
	move $a0, $s0
	sw $s0, -164($fp)
	jal changeCal
	move $s0, $v0
	sw $s0, -304($fp)
	lw $s0, -304($fp)
	addi $s1, $s0, -1
	sw $s0, -304($fp)
	move $s0, $s1
	sw $s1, -164($fp)
	sw $s0, -168($fp)
	j label3
label4:
	lw $s0, -164($fp)
	move $a0, $s0
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	sw $s0, -164($fp)
	lw $s0, -108($fp)
	lw $s1, -112($fp)
	add $s0, $s0, $s1
	add $s1, $s0, $s1
	add $s2, $s0, $s1
	sw $s1, -112($fp)
	sw $s0, -108($fp)
	move $a0, $s2
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	sw $s2, -132($fp)
	li $v0, 0
	j ret_main
ret_main:
	lw $s0, -12($fp)
	lw $s1, -16($fp)
	lw $s2, -20($fp)
	lw $s3, -24($fp)
	lw $s4, -28($fp)
	lw $s5, -32($fp)
	lw $s6, -36($fp)
	lw $s7, -40($fp)
	lw $ra, 300($sp)
	lw $fp, 296($sp)
	addi $sp, $sp, 304
	jr $ra
