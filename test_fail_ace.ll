; bug: asm still print "tensor_fail	a0, 16, 1" (incorrect, since operand 16 is imm4 type), while llvm-objdump -d print "tensor_fail a0, 0, 1"
; ~/andes/riscv/git/Phoenix/llvm-project/build_riscv_newlib/bin/llc -mtriple=riscv64 test_fail_ace.ll -filetype=asm -O0 -o -
; ~/andes/riscv/git/Phoenix/llvm-project/build_riscv_newlib/bin/llc -mtriple=riscv64 test_fail_ace.ll -filetype=obj -O0
; ~/andes/riscv/git/Phoenix/llvm-project/build_riscv_newlib/bin/llvm-objdump -d test_fail_ace.o 

define dso_local i64 @foo() nounwind {
entry:
;  %token = alloca i64, align 8
  %0 = call i64 @llvm.riscv.tensor.fail(i64 16, i64 1)
;  store i64 %0, i64* %token, align 8
  ret i64 0
}

; Function Attrs: nounwind
declare i64 @llvm.riscv.tensor.fail(i64 immarg, i64 immarg)
