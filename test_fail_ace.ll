; ~/andes/riscv/git/Phoenix/llvm-project/build_riscv_newlib/bin/llc -mtriple=riscv64 test_fail_ace.ll -debug -print-before-all -o -

define dso_local i64 @foo() nounwind {
entry:
;  %token = alloca i64, align 8
  %0 = call i64 @llvm.riscv.tensor.fail(i32 0, i32 1)
;  store i64 %0, i64* %token, align 8
  ret i64 0
}

; Function Attrs: nounwind
declare i64 @llvm.riscv.tensor.fail(i32 immarg, i32 immarg)
