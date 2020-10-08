; ModuleID = 'Module stdin'
source_filename = "Module stdin"

@global_string = private constant [6 x i8] c"%s...\00", align 1
@global_string.1 = private constant [4 x i8] c"yes\00", align 1
@global_string.2 = private constant [3 x i8] c"no\00", align 1
@global_string.3 = private constant [9 x i8] c"self %d\0A\00", align 1
@global_string.4 = private constant [5 x i8] c"+ABC\00", align 1
@global_string.5 = private constant [12 x i8] c"HELLO WORLD\00", align 1
@global_string.6 = private constant [6 x i8] c"test1\00", align 1
@global_string.7 = private constant [21 x i8] c"message passing test\00", align 1
@global_string.8 = private constant [4 x i8] c"ABC\00", align 1
@global_string.9 = private constant [11 x i8] c"const test\00", align 1
@global_string.10 = private constant [4 x i8] c"ABC\00", align 1
@global_string.11 = private constant [10 x i8] c"eqeq test\00", align 1
@global_string.12 = private constant [8 x i8] c"xxx %d\0A\00", align 1
@global_string.13 = private constant [11 x i8] c"block test\00", align 1

declare i32 @puts(i8*)

declare i32 @exit(i32)

declare i32 @printf(i8*, ...)

declare i8* @calloc(i64, i64)

declare void @free(i8*)

define void @xassert(i8* %msg, i1 %exp) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %lv_table = alloca [512 x i8*]
  %msg2 = alloca i8*
  store i8* %msg, i8** %msg2, align 8
  %0 = bitcast [512 x i8*]* %lv_table to i8**
  %1 = getelementptr i8*, i8** %0, i32 0
  %2 = bitcast i8** %msg2 to i8*
  store i8* %2, i8** %1, align 8
  %exp3 = alloca i1
  store i1 %exp, i1* %exp3, align 1
  %3 = bitcast [512 x i8*]* %lv_table to i8**
  %4 = getelementptr i8*, i8** %3, i32 1
  %5 = bitcast i1* %exp3 to i8*
  store i8* %5, i8** %4, align 8
  %6 = bitcast [512 x i8*]* %lv_table to i8**
  %7 = getelementptr i8*, i8** %6, i32 0
  %8 = load i8*, i8** %7, align 8
  %9 = bitcast i8* %8 to i8**
  %msg4 = load i8*, i8** %9, align 8
  %10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @global_string, i32 0, i32 0), i8* %msg4)
  %11 = bitcast [512 x i8*]* %lv_table to i8**
  %12 = getelementptr i8*, i8** %11, i32 1
  %13 = load i8*, i8** %12, align 8
  %14 = bitcast i8* %13 to i1*
  %exp5 = load i1, i1* %14, align 1
  br i1 %exp5, label %cond_jump_then, label %cond_else_block

cond_jump_then:                                   ; preds = %entry
  %15 = call i32 @puts(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.1, i32 0, i32 0))
  br label %cond_end

cond_else_block:                                  ; preds = %entry
  %16 = call i32 @puts(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @global_string.2, i32 0, i32 0))
  %17 = call i32 @exit(i32 2)
  br label %cond_end

cond_end:                                         ; preds = %cond_else_block, %cond_jump_then
  ret void
}

define i1 @int_fun(i32 %self) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %lv_table = alloca [512 x i8*]
  %self2 = alloca i32
  store i32 %self, i32* %self2, align 4
  %0 = bitcast [512 x i8*]* %lv_table to i8**
  %1 = getelementptr i8*, i8** %0, i32 0
  %2 = bitcast i32* %self2 to i8*
  store i8* %2, i8** %1, align 8
  %3 = bitcast [512 x i8*]* %lv_table to i8**
  %4 = getelementptr i8*, i8** %3, i32 0
  %5 = load i8*, i8** %4, align 8
  %6 = bitcast i8* %5 to i32*
  %self3 = load i32, i32* %6, align 4
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @global_string.3, i32 0, i32 0), i32 %self3)
  ret i1 true
}

define i1 @const_test(i8* %str) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %lv_table = alloca [512 x i8*]
  %str2 = alloca i8*
  store i8* %str, i8** %str2, align 8
  %0 = bitcast [512 x i8*]* %lv_table to i8**
  %1 = getelementptr i8*, i8** %0, i32 0
  %2 = bitcast i8** %str2 to i8*
  store i8* %2, i8** %1, align 8
  %3 = bitcast [512 x i8*]* %lv_table to i8**
  %4 = getelementptr i8*, i8** %3, i32 0
  %5 = load i8*, i8** %4, align 8
  %6 = bitcast i8* %5 to i8**
  %str3 = load i8*, i8** %6, align 8
  %7 = call i32 @puts(i8* %str3)
  ret i1 true
}

declare i8* @strcpy(i8*, i8*)

declare i32 @strlen(i8*)

declare i8* @strcat(i8*, i8*)

define internal i8* @string(i8* %str) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %lv_table = alloca [512 x i8*]
  %str2 = alloca i8*
  store i8* %str, i8** %str2, align 8
  %0 = bitcast [512 x i8*]* %lv_table to i8**
  %1 = getelementptr i8*, i8** %0, i32 0
  %2 = bitcast i8** %str2 to i8*
  store i8* %2, i8** %1, align 8
  %3 = bitcast [512 x i8*]* %lv_table to i8**
  %4 = getelementptr i8*, i8** %3, i32 0
  %5 = load i8*, i8** %4, align 8
  %6 = bitcast i8* %5 to i8**
  %str3 = load i8*, i8** %6, align 8
  %7 = call i32 @strlen(i8* %str3)
  %addtmp = add nsw i32 %7, 1
  %sext14 = zext i32 %addtmp to i64
  %8 = call i8* @calloc(i64 %sext14, i64 1)
  %result = alloca i8*
  %9 = bitcast [512 x i8*]* %lv_table to i8**
  %10 = getelementptr i8*, i8** %9, i32 1
  %11 = bitcast i8** %result to i8*
  store i8* %11, i8** %10, align 8
  store i8* %8, i8** %result, align 8
  %12 = bitcast [512 x i8*]* %lv_table to i8**
  %13 = getelementptr i8*, i8** %12, i32 0
  %14 = load i8*, i8** %13, align 8
  %15 = bitcast i8* %14 to i8**
  %str4 = load i8*, i8** %15, align 8
  %result5 = load i8*, i8** %result, align 8
  %16 = call i8* @strcpy(i8* %result5, i8* %str4)
  %result6 = load i8*, i8** %result, align 8
  ret i8* %result6
}

define i8* @string2(i8* %str) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %lv_table = alloca [512 x i8*]
  %str2 = alloca i8*
  store i8* %str, i8** %str2, align 8
  %0 = bitcast [512 x i8*]* %lv_table to i8**
  %1 = getelementptr i8*, i8** %0, i32 0
  %2 = bitcast i8** %str2 to i8*
  store i8* %2, i8** %1, align 8
  %3 = bitcast [512 x i8*]* %lv_table to i8**
  %4 = getelementptr i8*, i8** %3, i32 0
  %5 = load i8*, i8** %4, align 8
  %6 = bitcast i8* %5 to i8**
  %str3 = load i8*, i8** %6, align 8
  %7 = call i32 @strlen(i8* %str3)
  %addtmp = add nsw i32 %7, 6
  %sext14 = zext i32 %addtmp to i64
  %8 = call i8* @calloc(i64 %sext14, i64 1)
  %result = alloca i8*
  %9 = bitcast [512 x i8*]* %lv_table to i8**
  %10 = getelementptr i8*, i8** %9, i32 1
  %11 = bitcast i8** %result to i8*
  store i8* %11, i8** %10, align 8
  store i8* %8, i8** %result, align 8
  %12 = bitcast [512 x i8*]* %lv_table to i8**
  %13 = getelementptr i8*, i8** %12, i32 0
  %14 = load i8*, i8** %13, align 8
  %15 = bitcast i8* %14 to i8**
  %str4 = load i8*, i8** %15, align 8
  %result5 = load i8*, i8** %result, align 8
  %16 = call i8* @strcpy(i8* %result5, i8* %str4)
  %result6 = load i8*, i8** %result, align 8
  %17 = call i8* @strcat(i8* %result6, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @global_string.4, i32 0, i32 0))
  %result7 = load i8*, i8** %result, align 8
  %18 = load i8*, i8** %str2, align 8
  %19 = ptrtoint i8* %18 to i64
  %20 = icmp ne i64 %19, 0
  br i1 %20, label %cond_then_block, label %cond_end

cond_then_block:                                  ; preds = %entry
  br label %cond_end

cond_end:                                         ; preds = %cond_then_block, %entry
  call void @free(i8* %18)
  ret i8* %result7
}

define i8* @string_test1(i8* %var) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %lv_table = alloca [512 x i8*]
  %var2 = alloca i8*
  store i8* %var, i8** %var2, align 8
  %0 = bitcast [512 x i8*]* %lv_table to i8**
  %1 = getelementptr i8*, i8** %0, i32 0
  %2 = bitcast i8** %var2 to i8*
  store i8* %2, i8** %1, align 8
  %3 = call i8* @calloc(i64 128, i64 1)
  %a = alloca i8*
  %4 = bitcast [512 x i8*]* %lv_table to i8**
  %5 = getelementptr i8*, i8** %4, i32 1
  %6 = bitcast i8** %a to i8*
  store i8* %6, i8** %5, align 8
  store i8* %3, i8** %a, align 8
  %7 = bitcast [512 x i8*]* %lv_table to i8**
  %8 = getelementptr i8*, i8** %7, i32 0
  %9 = load i8*, i8** %8, align 8
  %10 = bitcast i8* %9 to i8**
  %var3 = load i8*, i8** %10, align 8
  %a4 = load i8*, i8** %a, align 8
  %11 = call i8* @strcpy(i8* %a4, i8* %var3)
  %a5 = load i8*, i8** %a, align 8
  %12 = call i32 @puts(i8* %a5)
  %a6 = load i8*, i8** %a, align 8
  %13 = load i8*, i8** %var2, align 8
  %14 = ptrtoint i8* %13 to i64
  %15 = icmp ne i64 %14, 0
  br i1 %15, label %cond_then_block, label %cond_end

cond_then_block:                                  ; preds = %entry
  br label %cond_end

cond_end:                                         ; preds = %cond_then_block, %entry
  call void @free(i8* %13)
  ret i8* %a6
}

define i32 @main() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %lv_table = alloca [512 x i8*]
  %0 = call i32 @puts(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.5, i32 0, i32 0))
  call void @xassert(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @global_string.6, i32 0, i32 0), i1 true)
  %1 = call i1 @int_fun(i32 3)
  call void @xassert(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @global_string.7, i32 0, i32 0), i1 %1)
  %2 = call i1 @const_test(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.8, i32 0, i32 0))
  call void @xassert(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @global_string.9, i32 0, i32 0), i1 %2)
  %3 = call i8* @string(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.10, i32 0, i32 0))
  %4 = call i8* @string2(i8* %3)
  %5 = call i8* @string_test1(i8* %4)
  %b = alloca i8*
  %6 = bitcast [512 x i8*]* %lv_table to i8**
  %7 = getelementptr i8*, i8** %6, i32 0
  %8 = bitcast i8** %b to i8*
  store i8* %8, i8** %7, align 8
  store i8* %5, i8** %b, align 8
  %b2 = load i8*, i8** %b, align 8
  %9 = call i32 @puts(i8* %b2)
  %xxx = alloca i32
  %10 = bitcast [512 x i8*]* %lv_table to i8**
  %11 = getelementptr i8*, i8** %10, i32 1
  %12 = bitcast i32* %xxx to i8*
  store i8* %12, i8** %11, align 8
  store i32 123, i32* %xxx, align 4
  %xxx3 = load i32, i32* %xxx, align 4
  %eqtmpX = icmp eq i32 %xxx3, 123
  call void @xassert(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @global_string.11, i32 0, i32 0), i1 %eqtmpX)
  %13 = call i32 @"code/HelloWorld.c_coroutine1"([512 x i8*]* %lv_table)
  %yyy = alloca i32
  %14 = bitcast [512 x i8*]* %lv_table to i8**
  %15 = getelementptr i8*, i8** %14, i32 2
  %16 = bitcast i32* %yyy to i8*
  store i8* %16, i8** %15, align 8
  store i32 %13, i32* %yyy, align 4
  %yyy4 = load i32, i32* %yyy, align 4
  %eqtmpX5 = icmp eq i32 %yyy4, 123
  call void @xassert(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @global_string.13, i32 0, i32 0), i1 %eqtmpX5)
  %17 = load i8*, i8** %b, align 8
  %18 = ptrtoint i8* %17 to i64
  %19 = icmp ne i64 %18, 0
  br i1 %19, label %cond_then_block, label %cond_end

cond_then_block:                                  ; preds = %entry
  br label %cond_end

cond_end:                                         ; preds = %cond_then_block, %entry
  call void @free(i8* %17)
  ret i32 0
}

define internal i32 @"code/HelloWorld.c_coroutine1"([512 x i8*]) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %1 = bitcast [512 x i8*]* %lv_table to i8**
  %2 = getelementptr i8*, i8** %1, i32 1
  %3 = load i8*, i8** %2, align 8
  %4 = bitcast i8* %3 to i32*
  %xxx = load i32, i32* %4, align 4
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @global_string.12, i32 0, i32 0), i32 %xxx)
  %6 = bitcast [512 x i8*]* %lv_table to i8**
  %7 = getelementptr i8*, i8** %6, i32 1
  %8 = load i8*, i8** %7, align 8
  %9 = bitcast i8* %8 to i32*
  %xxx2 = load i32, i32* %9, align 4
  ret i32 %xxx2
}
