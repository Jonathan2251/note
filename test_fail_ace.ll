; ModuleID = 'test_fail_ace.c'
source_filename = "test_fail_ace.c"
target datalayout = "e-m:e-p:64:64-i64:64-i128:128-n64-S128"
target triple = "riscv64-unknown-unknown-elf"

; Function Attrs: noinline nounwind optnone
define dso_local i64 @foo() #0 {
entry:
  %token = alloca i64, align 8
  %0 = call i64 @llvm.riscv.tensor.fail(i32 0, i32 1)
  store i64 %0, i64* %token, align 8
  ret i64 0
}

; Function Attrs: nounwind
declare i64 @llvm.riscv.tensor.fail(i32 immarg, i32 immarg) #1

attributes #0 = { noinline nounwind optnone "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features"="+64bit,+a,+c,+d,+experimental-v,+experimental-zvlsseg,+f,+m,+relax,-save-restore" }
attributes #1 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 1, !"target-abi", !"lp64d"}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{i32 1, !"SmallDataLimit", i32 8}
!4 = !{!"clang version 13.0.0 (https://gitlab.lightelligence.co/software/Phoenix.git 90b88ad315cb1ec239443aafbd2d98720f267c7c)"}
