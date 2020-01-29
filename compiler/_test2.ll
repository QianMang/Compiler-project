; ModuleID = 'xxx.c'
source_filename = "xxx.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.12.0"
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
; Function Attrs: nounwind ssp uwtable
define i32 @main() #0 {
%1 = alloca i32, align 4
%2 = alloca i32, align 4
store i32 10, i32* %2, align 4
%3 = load i32, i32* %2, align 4
store i32 %3, i32* %1, align 4
%4 = alloca i32, align 4
%5 = alloca i32, align 4
store i32 3, i32* %5, align 4
%6 = load i32, i32* %5, align 4
store i32 %6, i32* %4, align 4
%7 = alloca i32, align 4
store i32 3, i32* %7, align 4
%8 = load i32, i32* %7, align 4
%9 = alloca i32, align 4
store i32 1, i32* %9, align 4
%10 = load i32, i32* %9, align 4
%11 = alloca i32, align 4
store i32 2, i32* %11, align 4
%12 = load i32, i32* %11, align 4
%13 = alloca i32, align 4
store i32 3, i32* %13, align 4
%14 = load i32, i32* %13, align 4
%15 = mul nsw i32 %12, %14
%16 = mul nsw i32 %10, %15
%17 = mul nsw i32 %8, %16
store i32 %17, i32* %4, align 4
br label %18

; <label>:18:                                      ; preds = %23, %0
%19 = load i32, i32* %1, align 4
%20 = alloca i32, align 4
store i32 0, i32* %20, align 4
%21 = load i32, i32* %20, align 4
%22 = icmp sgt i32 %19, %21
br i1 %22, label %23, label %48

; <label>:23:                                      ; preds = %18
%24 = alloca i32, align 4
store i32 3, i32* %24, align 4
%25 = load i32, i32* %24, align 4
store i32 %25, i32* %4, align 4
br label %26

; <label>:26:                                      ; preds = %31, %0
%27 = load i32, i32* %4, align 4
%28 = alloca i32, align 4
store i32 0, i32* %28, align 4
%29 = load i32, i32* %28, align 4
%30 = icmp sgt i32 %27, %29
br i1 %30, label %31, label %41

; <label>:31:                                      ; preds = %26
%32 = load i32, i32* %4, align 4
%33 = alloca i32, align 4
store i32 1, i32* %33, align 4
%34 = load i32, i32* %33, align 4
%35 = add nsw i32 %32, %34
%36 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %35)
%37 = load i32, i32* %4, align 4
%38 = alloca i32, align 4
store i32 1, i32* %38, align 4
%39 = load i32, i32* %38, align 4
%40 = sub nsw i32 %37, %39
store i32 %40, i32* %4, align 4
br label %26

; <label>:41:                                     ; preds = %26
%42 = load i32, i32* %1, align 4
%43 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %42)
%44 = load i32, i32* %1, align 4
%45 = alloca i32, align 4
store i32 1, i32* %45, align 4
%46 = load i32, i32* %45, align 4
%47 = sub nsw i32 %44, %46
store i32 %47, i32* %1, align 4
br label %18

; <label>:48:                                     ; preds = %18
ret i32 0
}

declare i32 @printf(i8*, ...) #1
attributes #0 = { nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
 attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
!llvm.module.flags = !{!0}
!llvm.ident = !{!1}
!0 = !{i32 1, !"PIC Level", i32 2}
!1 = !{!"Apple LLVM version 8.1.0 (clang-802.0.42)"}
