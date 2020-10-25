; ModuleID = 'Module stdin'
source_filename = "Module stdin"

@gLVTable0 = internal global [512 x i8*] zeroinitializer, align 8
@global_string = private constant [4 x i8] c"%d\0A\00", align 1

declare i32 @puts(i8*)

declare i32 @exit(i32)

declare i32 @printf(i8*, ...)

declare i8* @calloc(i64, i64)

declare void @free(i8*)

declare i32 @atoi(i8*)

declare i32 @atoi.1(i8*)

declare i32 @strcmp(i8*, i8*)

define i32 @main() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %ay = alloca [2 x [2 x [3 x i32]]]
  %0 = bitcast [2 x [2 x [3 x i32]]]* %ay to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable0, i32 0, i32 0), align 8
  %1 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %2 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %1, i32 0, i32 0
  %3 = getelementptr inbounds [3 x i32], [3 x i32]* %2, i32 0, i32 0
  store i32 1, i32* %3, align 4
  %4 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %5 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %4, i32 0, i32 0
  %6 = getelementptr inbounds [3 x i32], [3 x i32]* %5, i32 0, i32 1
  store i32 2, i32* %6, align 4
  %7 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %8 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %7, i32 0, i32 0
  %9 = getelementptr inbounds [3 x i32], [3 x i32]* %8, i32 0, i32 2
  store i32 3, i32* %9, align 4
  %10 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %11 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %10, i32 0, i32 1
  %12 = getelementptr inbounds [3 x i32], [3 x i32]* %11, i32 0, i32 0
  store i32 4, i32* %12, align 4
  %13 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %14 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %13, i32 0, i32 1
  %15 = getelementptr inbounds [3 x i32], [3 x i32]* %14, i32 0, i32 1
  store i32 5, i32* %15, align 4
  %16 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %17 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %16, i32 0, i32 1
  %18 = getelementptr inbounds [3 x i32], [3 x i32]* %17, i32 0, i32 2
  store i32 6, i32* %18, align 4
  %19 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %20 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %19, i32 0, i32 0
  %21 = getelementptr inbounds [3 x i32], [3 x i32]* %20, i32 0, i32 0
  store i32 7, i32* %21, align 4
  %22 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %23 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %22, i32 0, i32 0
  %24 = getelementptr inbounds [3 x i32], [3 x i32]* %23, i32 0, i32 1
  store i32 8, i32* %24, align 4
  %25 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %26 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %25, i32 0, i32 0
  %27 = getelementptr inbounds [3 x i32], [3 x i32]* %26, i32 0, i32 2
  store i32 9, i32* %27, align 4
  %28 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %29 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %28, i32 0, i32 1
  %30 = getelementptr inbounds [3 x i32], [3 x i32]* %29, i32 0, i32 0
  store i32 11, i32* %30, align 4
  %31 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %32 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %31, i32 0, i32 1
  %33 = getelementptr inbounds [3 x i32], [3 x i32]* %32, i32 0, i32 1
  store i32 12, i32* %33, align 4
  %34 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %35 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %34, i32 0, i32 1
  %36 = getelementptr inbounds [3 x i32], [3 x i32]* %35, i32 0, i32 2
  store i32 13, i32* %36, align 4
  %ay2 = load [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, align 4
  %37 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %38 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %37, i32 0, i32 1
  %39 = getelementptr inbounds [3 x i32], [3 x i32]* %38, i32 0, i32 2
  %element = load i32, i32* %39, align 4
  %40 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string, i32 0, i32 0), i32 %element)
  ret i32 0
}
