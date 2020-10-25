; ModuleID = 'Module stdin'
source_filename = "Module stdin"

@gLVTable0 = internal global [512 x i8*] zeroinitializer, align 8
@global_string = private constant [11 x i8] c"called fun\00", align 1
@gLVTable1 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.2 = private constant [6 x i8] c"%s...\00", align 1
@global_string.3 = private constant [4 x i8] c"yes\00", align 1
@global_string.4 = private constant [3 x i8] c"no\00", align 1
@gArray4 = global [3 x [3 x [3 x i32]]] [[3 x [3 x i32]] [[3 x i32] [i32 1, i32 2, i32 3], [3 x i32] [i32 2, i32 3, i32 4], [3 x i32] [i32 5, i32 6, i32 7]], [3 x [3 x i32]] [[3 x i32] [i32 1, i32 2, i32 3], [3 x i32] [i32 1, i32 2, i32 3], [3 x i32] [i32 1, i32 2, i32 3]], [3 x [3 x i32]] [[3 x i32] [i32 11, i32 12, i32 13], [3 x i32] [i32 14, i32 15, i32 16], [3 x i32] [i32 17, i32 18, i32 19]]], align 4
@gLVTable2 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.5 = private constant [30 x i8] c"global array initializer test\00", align 1
@global_string.6 = private constant [23 x i8] c"array initializer test\00", align 1
@global_string.7 = private constant [29 x i8] c"local array initializer test\00", align 1
@global_string.8 = private constant [4 x i8] c"AAA\00", align 1
@global_string.9 = private constant [4 x i8] c"BBB\00", align 1
@global_string.10 = private constant [4 x i8] c"AAA\00", align 1
@global_string.11 = private constant [4 x i8] c"BBB\00", align 1
@global_string.12 = private constant [37 x i8] c"local cstring array initializer test\00", align 1

declare i32 @puts(i8*)

declare i32 @exit(i32)

declare i32 @printf(i8*, ...)

declare i8* @calloc(i64, i64)

declare void @free(i8*)

declare i32 @atoi(i8*)

declare i32 @atoi.1(i8*)

declare i32 @strcmp(i8*, i8*)

define i32 @fun() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %0 = call i32 @puts(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @global_string, i32 0, i32 0))
  ret i32 2
}

define void @xassert(i8* %msg, i1 %exp) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %msg2 = alloca i8*
  store i8* %msg, i8** %msg2, align 8
  %0 = bitcast i8** %msg2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable1, i32 0, i32 0), align 8
  %exp3 = alloca i1
  store i1 %exp, i1* %exp3, align 1
  %1 = bitcast i1* %exp3 to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable1, i32 0, i32 1), align 8
  %2 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable1, i32 0, i32 0), align 8
  %3 = bitcast i8* %2 to i8**
  %msg4 = load i8*, i8** %3, align 8
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @global_string.2, i32 0, i32 0), i8* %msg4)
  %5 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable1, i32 0, i32 1), align 8
  %6 = bitcast i8* %5 to i1*
  %exp5 = load i1, i1* %6, align 1
  br i1 %exp5, label %cond_jump_then, label %cond_else_block

cond_jump_then:                                   ; preds = %entry
  %7 = call i32 @puts(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.3, i32 0, i32 0))
  br label %cond_end

cond_else_block:                                  ; preds = %entry
  %8 = call i32 @puts(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @global_string.4, i32 0, i32 0))
  %9 = call i32 @exit(i32 2)
  br label %cond_end

cond_end:                                         ; preds = %cond_else_block, %cond_jump_then
  ret void
}

define i32 @main() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %gArray4 = load [3 x [3 x [3 x i32]]], [3 x [3 x [3 x i32]]]* @gArray4, align 4
  %element = load i32, i32* getelementptr inbounds ([3 x [3 x [3 x i32]]], [3 x [3 x [3 x i32]]]* @gArray4, i32 0, i32 0, i32 1, i32 2), align 4
  %aaaaaa = alloca i32
  %0 = bitcast i32* %aaaaaa to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable2, i32 0, i32 0), align 8
  store i32 %element, i32* %aaaaaa, align 4
  %aaaaaa2 = load i32, i32* %aaaaaa, align 4
  %eqtmpX = icmp eq i32 %aaaaaa2, 4
  call void @xassert(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @global_string.5, i32 0, i32 0), i1 %eqtmpX)
  %gArray43 = load [3 x [3 x [3 x i32]]], [3 x [3 x [3 x i32]]]* @gArray4, align 4
  %element4 = load i32, i32* getelementptr inbounds ([3 x [3 x [3 x i32]]], [3 x [3 x [3 x i32]]]* @gArray4, i32 0, i32 1, i32 1, i32 1), align 4
  %eqtmpX5 = icmp eq i32 %element4, 2
  store i1 %eqtmpX5, i1* %andand_result_var, align 1
  br i1 %eqtmpX5, label %cond_jump_then, label %cond_jump_end

cond_jump_then:                                   ; preds = %entry
  %gArray46 = load [3 x [3 x [3 x i32]]], [3 x [3 x [3 x i32]]]* @gArray4, align 4
  %element7 = load i32, i32* getelementptr inbounds ([3 x [3 x [3 x i32]]], [3 x [3 x [3 x i32]]]* @gArray4, i32 0, i32 2, i32 0, i32 1), align 4
  %eqtmpX8 = icmp eq i32 %element7, 12
  %andand = and i1 %eqtmpX5, %eqtmpX8
  store i1 %andand, i1* %andand_result_var, align 1
  br label %cond_jump_end

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %andand_result_value = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @global_string.6, i32 0, i32 0), i1 %andand_result_value)
  %ay = alloca [2 x [2 x [3 x i32]]]
  %1 = bitcast [2 x [2 x [3 x i32]]]* %ay to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable2, i32 0, i32 1), align 8
  %2 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %3 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %2, i32 0, i32 0
  %4 = getelementptr inbounds [3 x i32], [3 x i32]* %3, i32 0, i32 0
  store i32 1, i32* %4, align 4
  %5 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %6 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %5, i32 0, i32 0
  %7 = getelementptr inbounds [3 x i32], [3 x i32]* %6, i32 0, i32 1
  store i32 2, i32* %7, align 4
  %8 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %9 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %8, i32 0, i32 0
  %10 = getelementptr inbounds [3 x i32], [3 x i32]* %9, i32 0, i32 2
  store i32 3, i32* %10, align 4
  %11 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %12 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %11, i32 0, i32 1
  %13 = getelementptr inbounds [3 x i32], [3 x i32]* %12, i32 0, i32 0
  store i32 4, i32* %13, align 4
  %14 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %15 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %14, i32 0, i32 1
  %16 = getelementptr inbounds [3 x i32], [3 x i32]* %15, i32 0, i32 1
  store i32 5, i32* %16, align 4
  %17 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %18 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %17, i32 0, i32 1
  %19 = getelementptr inbounds [3 x i32], [3 x i32]* %18, i32 0, i32 2
  store i32 6, i32* %19, align 4
  %20 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %21 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %20, i32 0, i32 0
  %22 = getelementptr inbounds [3 x i32], [3 x i32]* %21, i32 0, i32 0
  store i32 7, i32* %22, align 4
  %23 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %24 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %23, i32 0, i32 0
  %25 = getelementptr inbounds [3 x i32], [3 x i32]* %24, i32 0, i32 1
  store i32 8, i32* %25, align 4
  %26 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %27 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %26, i32 0, i32 0
  %28 = getelementptr inbounds [3 x i32], [3 x i32]* %27, i32 0, i32 2
  store i32 9, i32* %28, align 4
  %29 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %30 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %29, i32 0, i32 1
  %31 = getelementptr inbounds [3 x i32], [3 x i32]* %30, i32 0, i32 0
  store i32 11, i32* %31, align 4
  %32 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %33 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %32, i32 0, i32 1
  %34 = getelementptr inbounds [3 x i32], [3 x i32]* %33, i32 0, i32 1
  store i32 12, i32* %34, align 4
  %35 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %36 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %35, i32 0, i32 1
  %37 = getelementptr inbounds [3 x i32], [3 x i32]* %36, i32 0, i32 2
  store i32 13, i32* %37, align 4
  %ay9 = load [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, align 4
  %38 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %39 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %38, i32 0, i32 1
  %40 = getelementptr inbounds [3 x i32], [3 x i32]* %39, i32 0, i32 2
  %element10 = load i32, i32* %40, align 4
  %eqtmpX11 = icmp eq i32 %element10, 6
  call void @xassert(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @global_string.7, i32 0, i32 0), i1 %eqtmpX11)
  %aa = alloca [2 x i8*]
  %41 = bitcast [2 x i8*]* %aa to i8*
  store i8* %41, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable2, i32 0, i32 2), align 8
  %42 = load [2 x i8*], [2 x i8*]* %aa, align 8
  %43 = bitcast [2 x i8*]* %aa to i8**
  %element_address = getelementptr i8*, i8** %43, i64 0
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.8, i32 0, i32 0), i8** %element_address, align 8
  %element_address12 = getelementptr i8*, i8** %43, i64 1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.9, i32 0, i32 0), i8** %element_address12, align 8
  %aa13 = load [2 x i8*], [2 x i8*]* %aa, align 8
  %44 = bitcast [2 x i8*]* %aa to i8**
  %element_address14 = getelementptr i8*, i8** %44, i32 0
  %element15 = load i8*, i8** %element_address14, align 8
  %45 = call i32 @strcmp(i8* %element15, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.10, i32 0, i32 0))
  %eqtmpX16 = icmp eq i32 %45, 0
  store i1 %eqtmpX16, i1* %andand_result_var, align 1
  br i1 %eqtmpX16, label %cond_jump_then17, label %cond_jump_end18

cond_jump_then17:                                 ; preds = %cond_jump_end
  %aa19 = load [2 x i8*], [2 x i8*]* %aa, align 8
  %46 = bitcast [2 x i8*]* %aa to i8**
  %element_address20 = getelementptr i8*, i8** %46, i32 1
  %element21 = load i8*, i8** %element_address20, align 8
  %47 = call i32 @strcmp(i8* %element21, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.11, i32 0, i32 0))
  %eqtmpX22 = icmp eq i32 %47, 0
  %andand23 = and i1 %eqtmpX16, %eqtmpX22
  store i1 %andand23, i1* %andand_result_var, align 1
  br label %cond_jump_end18

cond_jump_end18:                                  ; preds = %cond_jump_then17, %cond_jump_end
  %andand_result_value24 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @global_string.12, i32 0, i32 0), i1 %andand_result_value24)
  ret i32 0
}
