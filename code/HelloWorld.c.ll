; ModuleID = 'Module stdin'
source_filename = "Module stdin"

@gLVTable0 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable1 = internal global [512 x i8*] zeroinitializer, align 8
@global_string = private constant [6 x i8] c"%s...\00", align 1
@global_string.1 = private constant [4 x i8] c"yes\00", align 1
@global_string.2 = private constant [3 x i8] c"no\00", align 1
@gLVTable2 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.3 = private constant [9 x i8] c"self %d\0A\00", align 1
@gLVTable3 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable4 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable5 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.4 = private constant [5 x i8] c"+ABC\00", align 1
@gLVTable6 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable7 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.5 = private constant [12 x i8] c"HELLO WORLD\00", align 1
@global_string.6 = private constant [6 x i8] c"test1\00", align 1
@global_string.7 = private constant [21 x i8] c"message passing test\00", align 1
@global_string.8 = private constant [4 x i8] c"ABC\00", align 1
@global_string.9 = private constant [11 x i8] c"const test\00", align 1
@global_string.10 = private constant [4 x i8] c"ABC\00", align 1
@global_string.11 = private constant [10 x i8] c"eqeq test\00", align 1

declare i32 @puts(i8*)

declare i32 @exit(i32)

declare i32 @printf(i8*, ...)

declare i8* @calloc(i32, i32)

declare void @free(i8*)

define i32 @fun() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
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
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @global_string, i32 0, i32 0), i8* %msg4)
  %5 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable1, i32 0, i32 1), align 8
  %6 = bitcast i8* %5 to i1*
  %exp5 = load i1, i1* %6, align 1
  br i1 %exp5, label %cond_jump_then, label %cond_else_block

cond_jump_then:                                   ; preds = %entry
  %7 = call i32 @puts(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.1, i32 0, i32 0))
  br label %cond_end

cond_else_block:                                  ; preds = %entry
  %8 = call i32 @puts(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @global_string.2, i32 0, i32 0))
  %9 = call i32 @exit(i32 2)
  br label %cond_end

cond_end:                                         ; preds = %cond_else_block, %cond_jump_then
  ret void
}

define i1 @int_fun(i32 %self) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %self2 = alloca i32
  store i32 %self, i32* %self2, align 4
  %0 = bitcast i32* %self2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable2, i32 0, i32 0), align 8
  %1 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable2, i32 0, i32 0), align 8
  %2 = bitcast i8* %1 to i32*
  %self3 = load i32, i32* %2, align 4
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @global_string.3, i32 0, i32 0), i32 %self3)
  ret i1 true
}

define i1 @const_test(i8* %str) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %str2 = alloca i8*
  store i8* %str, i8** %str2, align 8
  %0 = bitcast i8** %str2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable3, i32 0, i32 0), align 8
  %1 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable3, i32 0, i32 0), align 8
  %2 = bitcast i8* %1 to i8**
  %str3 = load i8*, i8** %2, align 8
  %3 = call i32 @puts(i8* %str3)
  ret i1 true
}

declare i8* @strcpy(i8*, i8*)

declare i32 @strlen(i8*)

declare i8* @strcat(i8*, i8*)

define internal i8* @string(i8* %str) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %str2 = alloca i8*
  store i8* %str, i8** %str2, align 8
  %0 = bitcast i8** %str2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable4, i32 0, i32 0), align 8
  %1 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable4, i32 0, i32 0), align 8
  %2 = bitcast i8* %1 to i8**
  %str3 = load i8*, i8** %2, align 8
  %3 = call i32 @strlen(i8* %str3)
  %addtmp = add nsw i32 %3, 1
  %4 = call i8* @calloc(i32 %addtmp, i32 1)
  %result = alloca i8*
  %5 = bitcast i8** %result to i8*
  store i8* %5, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable4, i32 0, i32 1), align 8
  store i8* %4, i8** %result, align 8
  %6 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable4, i32 0, i32 0), align 8
  %7 = bitcast i8* %6 to i8**
  %str4 = load i8*, i8** %7, align 8
  %result5 = load i8*, i8** %result, align 8
  %8 = call i8* @strcpy(i8* %result5, i8* %str4)
  %result6 = load i8*, i8** %result, align 8
  ret i8* %result6
}

define i8* @string2(i8* %str) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %str2 = alloca i8*
  store i8* %str, i8** %str2, align 8
  %0 = bitcast i8** %str2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable5, i32 0, i32 0), align 8
  %1 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable5, i32 0, i32 0), align 8
  %2 = bitcast i8* %1 to i8**
  %str3 = load i8*, i8** %2, align 8
  %3 = call i32 @strlen(i8* %str3)
  %addtmp = add nsw i32 %3, 6
  %4 = call i8* @calloc(i32 %addtmp, i32 1)
  %result = alloca i8*
  %5 = bitcast i8** %result to i8*
  store i8* %5, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable5, i32 0, i32 1), align 8
  store i8* %4, i8** %result, align 8
  %6 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable5, i32 0, i32 0), align 8
  %7 = bitcast i8* %6 to i8**
  %str4 = load i8*, i8** %7, align 8
  %result5 = load i8*, i8** %result, align 8
  %8 = call i8* @strcpy(i8* %result5, i8* %str4)
  %result6 = load i8*, i8** %result, align 8
  %9 = call i8* @strcat(i8* %result6, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @global_string.4, i32 0, i32 0))
  %result7 = load i8*, i8** %result, align 8
  %10 = load i8*, i8** %str2, align 8
  %11 = ptrtoint i8* %10 to i64
  %12 = icmp ne i64 %11, 0
  br i1 %12, label %cond_then_block, label %cond_end

cond_then_block:                                  ; preds = %entry
  br label %cond_end

cond_end:                                         ; preds = %cond_then_block, %entry
  call void @free(i8* %10)
  ret i8* %result7
}

define i8* @string_test1(i8* %var) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %var2 = alloca i8*
  store i8* %var, i8** %var2, align 8
  %0 = bitcast i8** %var2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable6, i32 0, i32 0), align 8
  %1 = call i8* @calloc(i32 128, i32 1)
  %a = alloca i8*
  %2 = bitcast i8** %a to i8*
  store i8* %2, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable6, i32 0, i32 1), align 8
  store i8* %1, i8** %a, align 8
  %3 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable6, i32 0, i32 0), align 8
  %4 = bitcast i8* %3 to i8**
  %var3 = load i8*, i8** %4, align 8
  %a4 = load i8*, i8** %a, align 8
  %5 = call i8* @strcpy(i8* %a4, i8* %var3)
  %a5 = load i8*, i8** %a, align 8
  %6 = call i32 @puts(i8* %a5)
  %a6 = load i8*, i8** %a, align 8
  %7 = load i8*, i8** %var2, align 8
  %8 = ptrtoint i8* %7 to i64
  %9 = icmp ne i64 %8, 0
  br i1 %9, label %cond_then_block, label %cond_end

cond_then_block:                                  ; preds = %entry
  br label %cond_end

cond_end:                                         ; preds = %cond_then_block, %entry
  call void @free(i8* %7)
  ret i8* %a6
}

define i32 @main() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
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
  %6 = bitcast i8** %b to i8*
  store i8* %6, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable7, i32 0, i32 0), align 8
  store i8* %5, i8** %b, align 8
  %b2 = load i8*, i8** %b, align 8
  %7 = call i32 @puts(i8* %b2)
  %xxx = alloca i32
  %8 = bitcast i32* %xxx to i8*
  store i8* %8, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable7, i32 0, i32 1), align 8
  store i32 123, i32* %xxx, align 4
  %xxx3 = load i32, i32* %xxx, align 4
  %eqtmpX = icmp eq i32 %xxx3, 123
  call void @xassert(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @global_string.11, i32 0, i32 0), i1 %eqtmpX)
  %a = alloca i32 (i32)*
  %9 = bitcast i32 (i32)** %a to i8*
  store i8* %9, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable7, i32 0, i32 2), align 8
  store i32 (i32)* @coroutine1, i32 (i32)** %a, align 8
  %10 = load i8*, i8** %b, align 8
  %11 = ptrtoint i8* %10 to i64
  %12 = icmp ne i64 %11, 0
  br i1 %12, label %cond_then_block, label %cond_end

cond_then_block:                                  ; preds = %entry
  br label %cond_end

cond_end:                                         ; preds = %cond_then_block, %entry
  call void @free(i8* %10)
  ret i32 0
}

define internal i32 @coroutine1(i32 %a) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %a2 = alloca i32
  store i32 %a, i32* %a2, align 4
  %0 = bitcast i32* %a2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable7, i32 0, i32 2), align 8
  ret i32 123
}
