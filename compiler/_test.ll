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
store i32 10, i32* %5, align 4
%6 = load i32, i32* %5, align 4
store i32 %6, i32* %4, align 4
%7 = load i32, i32* %1, align 4
%8 = alloca i32, align 4
store i32 1, i32* %8, align 4
%9 = load i32, i32* %8, align 4
%10 = add nsw i32 %7, %9
%11 = load i32, i32* %4, align 4
%12 = icmp sle i32 %10, %11
br i1 %12, label %13, label %32

; <label>:13:                                      ; preds = %0
%14 = load i32, i32* %4, align 4
%15 = alloca i32, align 4
store i32 2, i32* %15, align 4
%16 = load i32, i32* %15, align 4
%17 = mul nsw i32 %14, %16
%18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %17)
%19 = load i32, i32* %4, align 4
%20 = alloca i32, align 4
store i32 2, i32* %20, align 4
%21 = load i32, i32* %20, align 4
%22 = sdiv i32 %19, %21
%23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %22)
%24 = load i32, i32* %4, align 4
%25 = alloca i32, align 4
store i32 10, i32* %25, align 4
%26 = load i32, i32* %25, align 4
%27 = icmp eq i32 %24, %26
br i1 %27, label %28, label %31

; <label>:28:                                      ; preds = %0
%29 = load i32, i32* %4, align 4
%30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %29)
 br label %31

; <label>:31:                                      ; preds = %2092975808, %28
 br label %40

; <label>:32:                                      ; preds = %0
%33 = load i32, i32* %4, align 4
%34 = alloca i32, align 4
store i32 2, i32* %34, align 4
%35 = load i32, i32* %34, align 4
%36 = sub nsw i32 %33, %35
%37 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %36)
%38 = load i32, i32* %1, align 4
%39 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %38)
 br label %40


; <label>:40:                                      ; preds = %32, %13
%41 = load i32, i32* %4, align 4
%42 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %41)
ret i32 0
}

declare i32 @printf(i8*, ...) #1
attributes #0 = { nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
 attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
!llvm.module.flags = !{!0}
!llvm.ident = !{!1}
!0 = !{i32 1, !"PIC Level", i32 2}
!1 = !{!"Apple LLVM version 8.1.0 (clang-802.0.42)"}
