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

mod:
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
	lw $s0, -96($fp)
	lw $s1, -92($fp)
	div $s0, $s1
	mflo $s2
	mul $s3, $s2, $s1
	sw $s2, -100($fp)
	sw $s1, -92($fp)
	sub $s1, $s0, $s3
	sw $s3, -104($fp)
	sw $s0, -96($fp)
	sw $s1, -108($fp)
	move $v0, $s1
	j ret_mod
ret_mod:
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

main:
	subu $sp, $sp, 116
	sw $ra, 112($sp)
	sw $fp, 108($sp)
	addi $fp, $sp, 116
	sw $s0, -12($fp)
	sw $s1, -16($fp)
	sw $s2, -20($fp)
	sw $s3, -24($fp)
	sw $s4, -28($fp)
	sw $s5, -32($fp)
	sw $s6, -36($fp)
	sw $s7, -40($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal read
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $s0, $v0
	sw $s0, -100($fp)
	lw $s0, -100($fp)
	move $a0, $s0
	sw $s0, -100($fp)
	li $a1, 400
	jal mod
	move $s0, $v0
	sw $s0, -104($fp)
	lw $s0, -104($fp)
	li $v1, 0
	sw $s0, -104($fp)
	bne $s0, $v1, label0
	li $s0, 1
	sw $s0, -108($fp)
	j label1
label0:
	lw $s0, -100($fp)
	move $a0, $s0
	sw $s0, -100($fp)
	li $a1, 4
	jal mod
	move $s0, $v0
	sw $s0, -112($fp)
	lw $s0, -112($fp)
	li $v1, 0
	sw $s0, -112($fp)
	bne $s0, $v1, label2
	lw $s0, -100($fp)
	move $a0, $s0
	sw $s0, -100($fp)
	li $a1, 100
	jal mod
	move $s0, $v0
	sw $s0, -116($fp)
	lw $s0, -116($fp)
	li $v1, 0
	sw $s0, -116($fp)
	beq $s0, $v1, label2
	li $s0, 1
	sw $s0, -108($fp)
	j label3
label2:
	li $s0, 0
	sw $s0, -108($fp)
label3:
label1:
	lw $s0, -108($fp)
	move $a0, $s0
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	sw $s0, -108($fp)
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
	lw $ra, 112($sp)
	lw $fp, 108($sp)
	addi $sp, $sp, 116
	jr $ra
