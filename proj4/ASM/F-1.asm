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
	move $s0, $s1
	sw $s1, -108($fp)
	move $v0, $s1
	sw $s0, -112($fp)
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
	lw $ra, 108($sp)
	lw $fp, 104($sp)
	addi $sp, $sp, 112
	jr $ra

power:
	subu $sp, $sp, 140
	sw $ra, 136($sp)
	sw $fp, 132($sp)
	addi $fp, $sp, 140
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
	li, $v0, 1
	lw $s0, -92($fp)
	add $s1, $v0, $s0
	sub $s2, $s1, $s0
	sw $s0, -92($fp)
	sw $s1, -100($fp)
	sw $s2, -104($fp)
label0:
	lw $s0, -104($fp)
	sub $s1, $s0, $s0
	sw $s0, -104($fp)
	addi $s0, $s1, 90
	sw $s1, -108($fp)
	addi $s1, $s0, -89
	sw $s0, -112($fp)
	addi $s0, $s1, 1
	sw $s1, -116($fp)
	addi $s1, $s0, -2
	sw $s0, -120($fp)
	lw $s0, -92($fp)
	sw $s0, -92($fp)
	sw $s1, -124($fp)
	ble $s0, $s1, label1
	lw $s0, -104($fp)
	lw $s1, -96($fp)
	mul $s0, $s0, $s1
	sw $s0, -104($fp)
	sw $s1, -96($fp)
	li $v0, 2
	li $v1, 1
	mul $s0, $v0, $v1
	lw $s1, -92($fp)
	mul $s2, $s0, $s1
	sw $s0, -128($fp)
	li $v0, 1
	mul $s0, $v0, $s1
	sw $s1, -92($fp)
	sub $s1, $s2, $s0
	sw $s0, -136($fp)
	sw $s2, -132($fp)
	addi $s0, $s1, -1
	sw $s1, -140($fp)
	sw $s0, -92($fp)
	j label0
label1:
	lw $s0, -104($fp)
	sw $s0, -104($fp)
	move $v0, $s0
	j ret_power
ret_power:
	lw $s0, -12($fp)
	lw $s1, -16($fp)
	lw $s2, -20($fp)
	lw $s3, -24($fp)
	lw $s4, -28($fp)
	lw $s5, -32($fp)
	lw $s6, -36($fp)
	lw $s7, -40($fp)
	lw $ra, 136($sp)
	lw $fp, 132($sp)
	addi $sp, $sp, 140
	jr $ra

getNumDigits:
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
	li $s0, 0
	lw $s1, -96($fp)
	li $v1, 0
	sw $s1, -96($fp)
	sw $s0, -100($fp)
	bge $s1, $v1, label2
	li $s0, 1
	li, $v0, 0
	sub $s1, $v0, $s0
	sw $s0, -104($fp)
	sw $s1, -108($fp)
	move $v0, $s1
	j ret_getNumDigits
label2:
label3:
	lw $s0, -96($fp)
	li $v1, 0
	sw $s0, -96($fp)
	ble $s0, $v1, label4
	lw $s0, -96($fp)
	li $v1, 10
	div $s0, $v1
	mflo $s0
	sw $s0, -96($fp)
	lw $s0, -100($fp)
	addi $s0, $s0, 2
	addi $s0, $s0, 2
	addi $s0, $s0, -3
	sw $s0, -100($fp)
	j label3
label4:
	lw $s0, -100($fp)
	sw $s0, -100($fp)
	move $v0, $s0
	j ret_getNumDigits
ret_getNumDigits:
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

isNarcissistic:
	subu $sp, $sp, 128
	sw $ra, 124($sp)
	sw $fp, 120($sp)
	addi $fp, $sp, 128
	sw $s0, -12($fp)
	sw $s1, -16($fp)
	sw $s2, -20($fp)
	sw $s3, -24($fp)
	sw $s4, -28($fp)
	sw $s5, -32($fp)
	sw $s6, -36($fp)
	sw $s7, -40($fp)
	sw $a0, -96($fp)
	li, $v0, 1
	lw $s0, -96($fp)
	add $s1, $v0, $s0
	sw $s0, -96($fp)
	addi $s0, $s1, -1
	sw $s1, -100($fp)
	sw $s0, -104($fp)
	lw $s0, -104($fp)
	move $a0, $s0
	sw $s0, -104($fp)
	jal getNumDigits
	move $s0, $v0
	sw $s0, -108($fp)
	li $s0, 0
	lw $s1, -96($fp)
	move $s2, $s1
	sw $s1, -96($fp)
	sw $s0, -112($fp)
	sw $s2, -116($fp)
label5:
	lw $s0, -116($fp)
	li $v1, 0
	sw $s0, -116($fp)
	ble $s0, $v1, label6
	lw $s0, -116($fp)
	move $a0, $s0
	sw $s0, -116($fp)
	li $a1, 10
	jal mod
	move $s0, $v0
	sw $s0, -120($fp)
	lw $s0, -116($fp)
	lw $s1, -120($fp)
	sub $s2, $s0, $s1
	sw $s1, -120($fp)
	sw $s0, -116($fp)
	li $v1, 10
	div $s2, $v1
	mflo $s0
	sw $s2, -124($fp)
	sw $s0, -116($fp)
	lw $s0, -120($fp)
	move $a0, $s0
	sw $s0, -120($fp)
	lw $s0, -108($fp)
	move $a1, $s0
	sw $s0, -108($fp)
	jal power
	move $s0, $v0
	sw $s0, -128($fp)
	lw $s0, -112($fp)
	lw $s1, -128($fp)
	add $s0, $s0, $s1
	sw $s1, -128($fp)
	sw $s0, -112($fp)
	j label5
label6:
	lw $s0, -112($fp)
	lw $s1, -96($fp)
	sw $s0, -112($fp)
	sw $s1, -96($fp)
	bne $s0, $s1, label7
	li $v0, 1
	j ret_isNarcissistic
	j label8
label7:
	li $v0, 0
	j ret_isNarcissistic
label8:
ret_isNarcissistic:
	lw $s0, -12($fp)
	lw $s1, -16($fp)
	lw $s2, -20($fp)
	lw $s3, -24($fp)
	lw $s4, -28($fp)
	lw $s5, -32($fp)
	lw $s6, -36($fp)
	lw $s7, -40($fp)
	lw $ra, 124($sp)
	lw $fp, 120($sp)
	addi $sp, $sp, 128
	jr $ra

main:
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
	li $s0, 0
	li $s1, 300
	sw $s0, -100($fp)
	sw $s1, -104($fp)
label9:
	lw $s0, -104($fp)
	li $v1, 500
	sw $s0, -104($fp)
	bge $s0, $v1, label10
	lw $s0, -104($fp)
	move $a0, $s0
	sw $s0, -104($fp)
	jal isNarcissistic
	move $s0, $v0
	sw $s0, -108($fp)
	lw $s0, -108($fp)
	li $v1, 1
	sw $s0, -108($fp)
	bne $s0, $v1, label11
	lw $s0, -104($fp)
	move $a0, $s0
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	sw $s0, -104($fp)
	lw $s0, -100($fp)
	addi $s0, $s0, 1
	sw $s0, -100($fp)
label11:
	lw $s0, -104($fp)
	addi $s0, $s0, 1
	sw $s0, -104($fp)
	j label9
label10:
	lw $s0, -100($fp)
	move $a0, $s0
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	sw $s0, -100($fp)
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
	lw $ra, 104($sp)
	lw $fp, 100($sp)
	addi $sp, $sp, 108
	jr $ra
