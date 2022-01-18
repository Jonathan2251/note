	.text
	.section .mdebug.abiO32
	.previous
	.file	"ch7_1_longlong.cpp"
	.globl	_Z14test_longlong2x             # -- Begin function _Z14test_longlong2x
	.p2align	1
	.type	_Z14test_longlong2x,@function
	.ent	_Z14test_longlong2x             # @_Z14test_longlong2x
_Z14test_longlong2x:
	.frame	$fp,24,$lr
	.mask 	0x00001000,-4
	.set	noreorder
	.set	nomacro
# %bb.0:
	addiu	$sp, $sp, -24
	st	$fp, 20($sp)                    # 4-byte Folded Spill
	move	$fp, $sp
	st	$5, 12($fp)
	st	$4, 8($fp)
	ld	$2, 8($fp)
	ld	$3, 12($fp)
	st	$3, 4($fp)
	st	$2, 0($fp)
	ld	$2, 0($fp)
	addiu	$3, $zero, -1
	slt	$2, $3, $2
	bne	$2, $zero, $BB0_2
	nop
# %bb.1:
	ld	$2, 0($fp)
	ld	$3, 4($fp)
	addiu	$4, $zero, 0
	xor	$5, $3, $4    // $3(fffffffe) xor 0 -> $3(fffffffe)
	sltu	$5, $zero, $5 // $5=1
	addu	$2, $2, $5    // 7fffffff+1
	subu	$2, $4, $2    // 0-80000000=80000000
	subu	$3, $4, $3    // 0-fffffffe=2
	st	$3, 4($fp)
	st	$2, 0($fp)
$BB0_2:
	ld	$2, 0($fp)
	ld	$3, 4($fp)
	move	$sp, $fp
	ld	$fp, 20($sp)                    # 4-byte Folded Reload
	addiu	$sp, $sp, 24
	ret	$lr
	nop
	.set	macro
	.set	reorder
	.end	_Z14test_longlong2x
$func_end0:
	.size	_Z14test_longlong2x, ($func_end0)-_Z14test_longlong2x
                                        # -- End function
	.ident	"Apple clang version 13.0.0 (clang-1300.0.29.30)"
	.section	".note.GNU-stack","",@progbits
