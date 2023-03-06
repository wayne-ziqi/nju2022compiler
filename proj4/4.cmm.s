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

func_a:
	subu $sp, $sp, 108
	sw $ra, 104($sp)
	sw $fp, 100($sp)
	addi $fp, $sp, 108
	sw $s0, -12($fp)
	sw $s1, -16($fp)
	sw $s2, -20($fp)
	sw $s3, -24($fp)
	sw $s4, -28($fp)
	sw $s5, -32($fp)
	sw $s6, -36($fp)
	sw $s7, -40($fp)
	sw $a0, -96($fp)
	sw $a1, -92($fp)
	div $a0, $a1
	mflo $s0
	mul $s1, $s0, $a1
	sub $s0, $a0, $s1
	move $v0, $s0
	j ret_func_a
ret_func_a:
	lw $s0, -12($fp)
	lw $s1, -16($fp)
	lw $s2, -20($fp)
	lw $s3, -24($fp)
	lw $s4, -28($fp)
	lw $s5, -32($fp)
	lw $s6, -36($fp)
	lw $s7, -40($fp)
	lw $ra, 104($sp)
	lw $fp, 100($sp)
	addi $sp, $sp, 108
	jr $ra

func_b:
	subu $sp, $sp, 104
	sw $ra, 100($sp)
	sw $fp, 96($sp)
	addi $fp, $sp, 104
	sw $s0, -12($fp)
	sw $s1, -16($fp)
	sw $s2, -20($fp)
	sw $s3, -24($fp)
	sw $s4, -28($fp)
	sw $s5, -32($fp)
	sw $s6, -36($fp)
	sw $s7, -40($fp)
	sw $a0, -96($fp)
	li $s0, 2
label0:
	bge $s0, $a0, label1
	move $a0, $s0
	lw $s1, -96($fp)
	move $a1, $s1
	jal func_a
	move $s2, $v0
	bne $s2, $v1, label2
	li $v0, 0
	j ret_func_b
label2:
	addi $s0, $s0, 1
	j label0
label1:
	li $v0, 1
	j ret_func_b
ret_func_b:
	lw $s0, -12($fp)
	lw $s1, -16($fp)
	lw $s2, -20($fp)
	lw $s3, -24($fp)
	lw $s4, -28($fp)
	lw $s5, -32($fp)
	lw $s6, -36($fp)
	lw $s7, -40($fp)
	lw $ra, 100($sp)
	lw $fp, 96($sp)
	addi $sp, $sp, 104
	jr $ra

func_c:
	subu $sp, $sp, 112
	sw $ra, 108($sp)
	sw $fp, 104($sp)
	addi $fp, $sp, 112
	sw $s0, -12($fp)
	sw $s1, -16($fp)
	sw $s2, -20($fp)
	sw $s3, -24($fp)
	sw $s4, -28($fp)
	sw $s5, -32($fp)
	sw $s6, -36($fp)
	sw $s7, -40($fp)
	sw $a0, -96($fp)
	li $s0, 2
label3:
	mul $s1, $s0, $s0
	bgt $s1, $a0, label4
	move $a0, $s0
	jal func_b
	move $s1, $v0
	beq $s1, $v1, label5
	mul $s1, $s0, $s0
	lw $s1, -96($fp)
	bne $s1, $s1, label6
	li $v0, 1
	j ret_func_c
label6:
label5:
	addi $s0, $s0, 1
	j label3
label4:
	li $v0, 0
	j ret_func_c
ret_func_c:
	lw $s0, -12($fp)
	lw $s1, -16($fp)
	lw $s2, -20($fp)
	lw $s3, -24($fp)
	lw $s4, -28($fp)
	lw $s5, -32($fp)
	lw $s6, -36($fp)
	lw $s7, -40($fp)
	lw $ra, 108($sp)
	lw $fp, 104($sp)
	addi $sp, $sp, 112
	jr $ra

main:
	subu $sp, $sp, 156
	sw $ra, 152($sp)
	sw $fp, 148($sp)
	addi $fp, $sp, 156
	sw $s0, -12($fp)
	sw $s1, -16($fp)
	sw $s2, -20($fp)
	sw $s3, -24($fp)
	sw $s4, -28($fp)
	sw $s5, -32($fp)
	sw $s6, -36($fp)
	sw $s7, -40($fp)
	li $s0, 2
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal read
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $s1, $v0
	la $s2, -104($fp)
	sw $s1, 0($s2)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal read
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $s1, $v0
	la $v1, -104($fp)
	addi $s2, $v1, 4
	sw $s1, 0($s2)
	li $s1, 0
label7:
	bge $s1, $s0, label8
	li $v1, 4
	mul $s2, $s1, $v1
	la $v1, -104($fp)
	add $s3, $v1, $s2
	lw $s2, 0($s3)
	move $a0, $s2
	jal func_c
	move $s2, $v0
	beq $s2, $v1, label9
	li $v1, 4
	mul $s2, $s1, $v1
	la $v1, -104($fp)
	add $s3, $v1, $s2
	lw $s2, 0($s3)
	move $a0, $s2
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
label9:
	addi $s1, $s1, 1
	j label7
label8:
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
	lw $ra, 152($sp)
	lw $fp, 148($sp)
	addi $sp, $sp, 156
	jr $ra
