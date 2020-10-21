; ModuleID = 'Module stdin'
source_filename = "Module stdin"

%Data = type { i32, i32 }
%GenericsData_int = type { i32, i32 }
%GenericsData2_int = type { i32 }
%GenericsData3_int = type { i32, i32 }
%anonmous_struct0 = type { i32, i32 }
%anonmous_union0 = type { i32 }
%Data3 = type { i64, i32 }

@gLVTable0 = internal global [512 x i8*] zeroinitializer, align 8
@global_string = private constant [11 x i8] c"called fun\00", align 1
@gLVTable1 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.2 = private constant [6 x i8] c"%s...\00", align 1
@global_string.3 = private constant [4 x i8] c"yes\00", align 1
@global_string.4 = private constant [3 x i8] c"no\00", align 1
@gLVTable2 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.5 = private constant [16 x i8] c"called int::fun\00", align 1
@global_string.6 = private constant [9 x i8] c"self %d\0A\00", align 1
@gLVTable3 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable4 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable5 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.7 = private constant [5 x i8] c"+ABC\00", align 1
@gLVTable6 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable7 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.8 = private constant [21 x i8] c"inheritFun version 1\00", align 1
@gLVTable8 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.9 = private constant [21 x i8] c"inheritFun version 2\00", align 1
@gA = global i32 zeroinitializer, align 4
@gB = global i32 123, align 4
@kA = global i32 0, align 4
@kB = global i32 1, align 4
@kC = global i32 2, align 4
@kA2 = global i32 123, align 4
@kB2 = global i32 124, align 4
@kC2 = global i32 125, align 4
@gArray = global [3 x i32] [i32 1, i32 2, i32 3], align 4
@gArray2 = global [3 x i8] c"AB\00", align 1
@gArray3 = global [3 x i32] [i32 1, i32 2, i32 3], align 4
@gLVTable9 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.10 = private constant [12 x i8] c"HELLO WORLD\00", align 1
@global_string.11 = private constant [6 x i8] c"test1\00", align 1
@global_string.12 = private constant [21 x i8] c"message passing test\00", align 1
@global_string.13 = private constant [4 x i8] c"ABC\00", align 1
@global_string.14 = private constant [11 x i8] c"const test\00", align 1
@global_string.15 = private constant [4 x i8] c"ABC\00", align 1
@global_string.16 = private constant [10 x i8] c"eqeq test\00", align 1
@global_string.17 = private constant [4 x i8] c"FUN\00", align 1
@global_string.18 = private constant [22 x i8] c"function pointer test\00", align 1
@global_string.19 = private constant [26 x i8] c"load field and store test\00", align 1
@global_string.20 = private constant [27 x i8] c"load field and store test2\00", align 1
@gLVTable10 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.21 = private constant [7 x i8] c"%d %d\0A\00", align 1
@global_string.22 = private constant [18 x i8] c"generics fun test\00", align 1
@gLVTable11 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.23 = private constant [25 x i8] c"method generics fun test\00", align 1
@global_string.24 = private constant [4 x i8] c"123\00", align 1
@gLVTable12 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.25 = private constant [26 x i8] c"method generics fun test2\00", align 1
@gLVTable13 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.26 = private constant [9 x i8] c"map test\00", align 1
@gLVTable14 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable15 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.28 = private constant [7 x i8] c"%d %d\0A\00", align 1
@gLVTable16 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable17 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.29 = private constant [31 x i8] c"GenericsData3<T>::fun version1\00", align 1
@gLVTable18 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable19 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.32 = private constant [7 x i8] c"%d %d\0A\00", align 1
@global_string.33 = private constant [31 x i8] c"GenericsData3<T>::fun version2\00", align 1
@gLVTable20 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable21 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.36 = private constant [7 x i8] c"%d %d\0A\00", align 1
@global_string.37 = private constant [16 x i8] c"global variable\00", align 1
@global_string.38 = private constant [17 x i8] c"global variable2\00", align 1
@global_string.39 = private constant [10 x i8] c"enum test\00", align 1
@global_string.40 = private constant [11 x i8] c"enum test2\00", align 1
@global_string.41 = private constant [22 x i8] c"anonymous struct test\00", align 1
@global_string.42 = private constant [27 x i8] c"anonyumous_union_data test\00", align 1
@global_string.43 = private constant [16 x i8] c"struct bit test\00", align 1
@global_string.44 = private constant [12 x i8] c"gt lt ge le\00", align 1
@global_string.45 = private constant [6 x i8] c"shift\00", align 1
@global_string.46 = private constant [11 x i8] c"and or xor\00", align 1
@global_string.47 = private constant [17 x i8] c"struct bit test2\00", align 1
@global_string.48 = private constant [15 x i8] c"logical denial\00", align 1
@global_string.49 = private constant [12 x i8] c"complement \00", align 1
@global_string.50 = private constant [8 x i8] c"pointer\00", align 1
@global_string.51 = private constant [9 x i8] c"pointer2\00", align 1
@global_string.52 = private constant [4 x i8] c"ABC\00", align 1
@global_string.53 = private constant [4 x i8] c"BBC\00", align 1
@global_string.54 = private constant [9 x i8] c"inc test\00", align 1
@global_string.55 = private constant [4 x i8] c"ABC\00", align 1
@global_string.56 = private constant [10 x i8] c"inc test2\00", align 1
@global_string.57 = private constant [4 x i8] c"CBC\00", align 1
@global_string.58 = private constant [10 x i8] c"inc test3\00", align 1
@global_string.59 = private constant [11 x i8] c"comma test\00", align 1
@global_string.60 = private constant [15 x i8] c"plus_plus test\00", align 1
@global_string.61 = private constant [15 x i8] c"plus_plus test\00", align 1
@global_string.62 = private constant [22 x i8] c"minus minus test test\00", align 1
@global_string.63 = private constant [13 x i8] c"mult eq test\00", align 1
@global_string.64 = private constant [4 x i8] c"ABC\00", align 1
@global_string.65 = private constant [4 x i8] c"ABC\00", align 1
@global_string.66 = private constant [11 x i8] c"array test\00", align 1
@global_string.67 = private constant [4 x i8] c"ABC\00", align 1
@global_string.68 = private constant [4 x i8] c"ABC\00", align 1
@global_string.69 = private constant [12 x i8] c"array test2\00", align 1
@global_string.70 = private constant [12 x i8] c"array test3\00", align 1
@global_string.71 = private constant [12 x i8] c"array test4\00", align 1
@global_string.72 = private constant [4 x i8] c"ABC\00", align 1
@global_string.73 = private constant [4 x i8] c"DEF\00", align 1
@global_string.74 = private constant [4 x i8] c"ABC\00", align 1
@global_string.75 = private constant [4 x i8] c"DEF\00", align 1
@global_string.76 = private constant [12 x i8] c"array test5\00", align 1
@global_string.77 = private constant [23 x i8] c"array initializer test\00", align 1
@global_string.78 = private constant [24 x i8] c"array initializer test2\00", align 1
@global_string.79 = private constant [3 x i8] c"AB\00", align 1
@global_string.80 = private constant [24 x i8] c"array initializer test3\00", align 1
@global_string.81 = private constant [3 x i8] c"AB\00", align 1
@global_string.82 = private constant [24 x i8] c"array initializer test4\00", align 1
@global_string.83 = private constant [24 x i8] c"array initializer test5\00", align 1
@global_string.84 = private constant [24 x i8] c"array initializer test6\00", align 1
@global_string.85 = private constant [10 x i8] c"char test\00", align 1

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

define i32 @int_fun(i32 %self) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %self2 = alloca i32
  store i32 %self, i32* %self2, align 4
  %0 = bitcast i32* %self2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable2, i32 0, i32 0), align 8
  %1 = call i32 @puts(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @global_string.5, i32 0, i32 0))
  %2 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable2, i32 0, i32 0), align 8
  %3 = bitcast i8* %2 to i32*
  %self3 = load i32, i32* %3, align 4
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @global_string.6, i32 0, i32 0), i32 %self3)
  ret i32 123
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
  %sext14 = zext i32 %addtmp to i64
  %4 = call i8* @calloc(i64 %sext14, i64 1)
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
  %sext14 = zext i32 %addtmp to i64
  %4 = call i8* @calloc(i64 %sext14, i64 1)
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
  %9 = call i8* @strcat(i8* %result6, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @global_string.7, i32 0, i32 0))
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
  %1 = call i8* @calloc(i64 128, i64 1)
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

define void @inheritFun() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %0 = call i32 @puts(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @global_string.8, i32 0, i32 0))
  ret void
}

define void @inheritFun_1() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  call void @inheritFun()
  %0 = call i32 @puts(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @global_string.9, i32 0, i32 0))
  ret void
}

define i32 @main() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %0 = call i32 @puts(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.10, i32 0, i32 0))
  call void @xassert(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @global_string.11, i32 0, i32 0), i1 true)
  %1 = call i32 @fun()
  %2 = call i32 @int_fun(i32 3)
  %eqtmpX = icmp eq i32 %2, 123
  call void @xassert(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @global_string.12, i32 0, i32 0), i1 %eqtmpX)
  %3 = call i1 @const_test(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.13, i32 0, i32 0))
  call void @xassert(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @global_string.14, i32 0, i32 0), i1 %3)
  %4 = call i8* @string(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.15, i32 0, i32 0))
  %5 = call i8* @string2(i8* %4)
  %6 = call i8* @string_test1(i8* %5)
  %b = alloca i8*
  %7 = bitcast i8** %b to i8*
  store i8* %7, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable9, i32 0, i32 0), align 8
  store i8* %6, i8** %b, align 8
  %b2 = load i8*, i8** %b, align 8
  %8 = call i32 @puts(i8* %b2)
  %xxx = alloca i32
  %9 = bitcast i32* %xxx to i8*
  store i8* %9, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable9, i32 0, i32 1), align 8
  store i32 123, i32* %xxx, align 4
  %xxx3 = load i32, i32* %xxx, align 4
  %eqtmpX4 = icmp eq i32 %xxx3, 123
  call void @xassert(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @global_string.16, i32 0, i32 0), i1 %eqtmpX4)
  %aaa = alloca i32 ()*
  %10 = bitcast i32 ()** %aaa to i8*
  store i8* %10, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable9, i32 0, i32 2), align 8
  store i32 ()* @coroutine1, i32 ()** %aaa, align 8
  %aaa5 = load i32 ()*, i32 ()** %aaa, align 8
  %11 = call i32 %aaa5()
  %eqtmpX6 = icmp eq i32 %11, 123
  call void @xassert(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @global_string.18, i32 0, i32 0), i1 %eqtmpX6)
  %data = alloca %Data
  %12 = bitcast %Data* %data to i8*
  store i8* %12, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable9, i32 0, i32 3), align 8
  %data7 = load %Data, %Data* %data, align 8
  %13 = getelementptr inbounds %Data, %Data* %data, i32 0, i32 0
  store i32 123, i32* %13, align 4
  %data8 = load %Data, %Data* %data, align 8
  %14 = getelementptr inbounds %Data, %Data* %data, i32 0, i32 1
  store i32 234, i32* %14, align 4
  %data9 = load %Data, %Data* %data, align 8
  %15 = getelementptr inbounds %Data, %Data* %data, i32 0, i32 0
  %16 = load i32, i32* %15, align 4
  %eqtmpX10 = icmp eq i32 %16, 123
  store i1 %eqtmpX10, i1* %andand_result_var, align 1
  br i1 %eqtmpX10, label %cond_jump_then, label %cond_jump_end

cond_jump_then:                                   ; preds = %entry
  %data11 = load %Data, %Data* %data, align 8
  %17 = getelementptr inbounds %Data, %Data* %data, i32 0, i32 1
  %18 = load i32, i32* %17, align 4
  %eqtmpX12 = icmp eq i32 %18, 234
  %andand = and i1 %eqtmpX10, %eqtmpX12
  store i1 %andand, i1* %andand_result_var, align 1
  br label %cond_jump_end

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %andand_result_value = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @global_string.19, i32 0, i32 0), i1 %andand_result_value)
  %data2 = alloca %GenericsData_int
  %19 = bitcast %GenericsData_int* %data2 to i8*
  store i8* %19, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable9, i32 0, i32 4), align 8
  %data213 = load %GenericsData_int, %GenericsData_int* %data2, align 8
  %20 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %data2, i32 0, i32 0
  store i32 123, i32* %20, align 4
  %data214 = load %GenericsData_int, %GenericsData_int* %data2, align 8
  %21 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %data2, i32 0, i32 1
  store i32 234, i32* %21, align 4
  %data215 = load %GenericsData_int, %GenericsData_int* %data2, align 8
  %22 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %data2, i32 0, i32 0
  %23 = load i32, i32* %22, align 4
  %eqtmpX16 = icmp eq i32 %23, 123
  store i1 %eqtmpX16, i1* %andand_result_var, align 1
  br i1 %eqtmpX16, label %cond_jump_then17, label %cond_jump_end18

cond_jump_then17:                                 ; preds = %cond_jump_end
  %data219 = load %GenericsData_int, %GenericsData_int* %data2, align 8
  %24 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %data2, i32 0, i32 1
  %25 = load i32, i32* %24, align 4
  %eqtmpX20 = icmp eq i32 %25, 234
  %andand21 = and i1 %eqtmpX16, %eqtmpX20
  store i1 %andand21, i1* %andand_result_var, align 1
  br label %cond_jump_end18

cond_jump_end18:                                  ; preds = %cond_jump_then17, %cond_jump_end
  %andand_result_value22 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @global_string.20, i32 0, i32 0), i1 %andand_result_value22)
  %data223 = load %GenericsData_int, %GenericsData_int* %data2, align 8
  %26 = call i32 @GenericsData_int_show(%GenericsData_int %data223)
  %eqtmpX24 = icmp eq i32 %26, 123
  call void @xassert(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @global_string.22, i32 0, i32 0), i1 %eqtmpX24)
  %27 = call i32 @fun2(i32 123)
  %eqtmpX25 = icmp eq i32 %27, 124
  call void @xassert(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @global_string.23, i32 0, i32 0), i1 %eqtmpX25)
  %28 = call i32 @fun3(i32 (i8*)* @coroutine2, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.24, i32 0, i32 0))
  %eqtmpX26 = icmp eq i32 %28, 123
  call void @xassert(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @global_string.25, i32 0, i32 0), i1 %eqtmpX26)
  %data227 = load %GenericsData_int, %GenericsData_int* %data2, align 8
  %29 = call i32 @GenericsData_int_map(%GenericsData_int %data227, i32 (i32)* @coroutine3)
  %eqtmpX28 = icmp eq i32 %29, 124
  call void @xassert(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @global_string.26, i32 0, i32 0), i1 %eqtmpX28)
  call void @inheritFun_1()
  %30 = call i8* @calloc(i64 1, i64 4)
  %31 = bitcast i8* %30 to %GenericsData2_int*
  %xyz = alloca %GenericsData2_int*
  %32 = bitcast %GenericsData2_int** %xyz to i8*
  store i8* %32, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable13, i32 0, i32 5), align 8
  store %GenericsData2_int* %31, %GenericsData2_int** %xyz, align 8
  %33 = ptrtoint %GenericsData2_int* %31 to i64
  %34 = icmp ne i64 %33, 0
  br i1 %34, label %cond_then_block, label %cond_end

cond_then_block:                                  ; preds = %cond_jump_end18
  br label %cond_end

cond_end:                                         ; preds = %cond_then_block, %cond_jump_end18
  %35 = bitcast %GenericsData2_int* %31 to i8*
  call void @free(i8* %35)
  %xyz29 = load %GenericsData2_int*, %GenericsData2_int** %xyz, align 8
  call void @GenericsData2_int_fun(%GenericsData2_int* %xyz29)
  %xyz2 = alloca %GenericsData3_int
  %36 = bitcast %GenericsData3_int* %xyz2 to i8*
  store i8* %36, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable15, i32 0, i32 6), align 8
  %xyz230 = load %GenericsData3_int, %GenericsData3_int* %xyz2, align 8
  call void @GenericsData3_int_fun_1(%GenericsData3_int %xyz230)
  store i32 1, i32* @gA, align 4
  %gA = load i32, i32* @gA, align 4
  %eqtmpX31 = icmp eq i32 %gA, 1
  call void @xassert(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @global_string.37, i32 0, i32 0), i1 %eqtmpX31)
  %gB = load i32, i32* @gB, align 4
  %eqtmpX32 = icmp eq i32 %gB, 123
  call void @xassert(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @global_string.38, i32 0, i32 0), i1 %eqtmpX32)
  %kA = load i32, i32* @kA, align 4
  %eqtmpX33 = icmp eq i32 %kA, 0
  store i1 %eqtmpX33, i1* %andand_result_var, align 1
  br i1 %eqtmpX33, label %cond_jump_then34, label %cond_jump_end35

cond_jump_then34:                                 ; preds = %cond_end
  %kB = load i32, i32* @kB, align 4
  %eqtmpX36 = icmp eq i32 %kB, 1
  %andand37 = and i1 %eqtmpX33, %eqtmpX36
  store i1 %andand37, i1* %andand_result_var, align 1
  br label %cond_jump_end35

cond_jump_end35:                                  ; preds = %cond_jump_then34, %cond_end
  %andand_result_value38 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value38, i1* %andand_result_var, align 1
  br i1 %andand_result_value38, label %cond_jump_then39, label %cond_jump_end40

cond_jump_then39:                                 ; preds = %cond_jump_end35
  %kC = load i32, i32* @kC, align 4
  %eqtmpX41 = icmp eq i32 %kC, 2
  %andand42 = and i1 %andand_result_value38, %eqtmpX41
  store i1 %andand42, i1* %andand_result_var, align 1
  br label %cond_jump_end40

cond_jump_end40:                                  ; preds = %cond_jump_then39, %cond_jump_end35
  %andand_result_value43 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @global_string.39, i32 0, i32 0), i1 %andand_result_value43)
  %kA2 = load i32, i32* @kA2, align 4
  %eqtmpX44 = icmp eq i32 %kA2, 123
  store i1 %eqtmpX44, i1* %andand_result_var, align 1
  br i1 %eqtmpX44, label %cond_jump_then45, label %cond_jump_end46

cond_jump_then45:                                 ; preds = %cond_jump_end40
  %kB2 = load i32, i32* @kB2, align 4
  %eqtmpX47 = icmp eq i32 %kB2, 124
  %andand48 = and i1 %eqtmpX44, %eqtmpX47
  store i1 %andand48, i1* %andand_result_var, align 1
  br label %cond_jump_end46

cond_jump_end46:                                  ; preds = %cond_jump_then45, %cond_jump_end40
  %andand_result_value49 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value49, i1* %andand_result_var, align 1
  br i1 %andand_result_value49, label %cond_jump_then50, label %cond_jump_end51

cond_jump_then50:                                 ; preds = %cond_jump_end46
  %kC2 = load i32, i32* @kC2, align 4
  %eqtmpX52 = icmp eq i32 %kC2, 125
  %andand53 = and i1 %andand_result_value49, %eqtmpX52
  store i1 %andand53, i1* %andand_result_var, align 1
  br label %cond_jump_end51

cond_jump_end51:                                  ; preds = %cond_jump_then50, %cond_jump_end46
  %andand_result_value54 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @global_string.40, i32 0, i32 0), i1 %andand_result_value54)
  %anonyumous_struct_data = alloca %anonmous_struct0
  %37 = bitcast %anonmous_struct0* %anonyumous_struct_data to i8*
  store i8* %37, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 7), align 8
  %anonyumous_struct_data55 = load %anonmous_struct0, %anonmous_struct0* %anonyumous_struct_data, align 8
  %38 = getelementptr inbounds %anonmous_struct0, %anonmous_struct0* %anonyumous_struct_data, i32 0, i32 0
  store i32 123, i32* %38, align 4
  %anonyumous_struct_data56 = load %anonmous_struct0, %anonmous_struct0* %anonyumous_struct_data, align 8
  %39 = getelementptr inbounds %anonmous_struct0, %anonmous_struct0* %anonyumous_struct_data, i32 0, i32 1
  store i32 234, i32* %39, align 4
  %anonyumous_struct_data57 = load %anonmous_struct0, %anonmous_struct0* %anonyumous_struct_data, align 8
  %40 = getelementptr inbounds %anonmous_struct0, %anonmous_struct0* %anonyumous_struct_data, i32 0, i32 0
  %41 = load i32, i32* %40, align 4
  %eqtmpX58 = icmp eq i32 %41, 123
  store i1 %eqtmpX58, i1* %andand_result_var, align 1
  br i1 %eqtmpX58, label %cond_jump_then59, label %cond_jump_end60

cond_jump_then59:                                 ; preds = %cond_jump_end51
  %anonyumous_struct_data61 = load %anonmous_struct0, %anonmous_struct0* %anonyumous_struct_data, align 8
  %42 = getelementptr inbounds %anonmous_struct0, %anonmous_struct0* %anonyumous_struct_data, i32 0, i32 1
  %43 = load i32, i32* %42, align 4
  %eqtmpX62 = icmp eq i32 %43, 234
  %andand63 = and i1 %eqtmpX58, %eqtmpX62
  store i1 %andand63, i1* %andand_result_var, align 1
  br label %cond_jump_end60

cond_jump_end60:                                  ; preds = %cond_jump_then59, %cond_jump_end51
  %andand_result_value64 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @global_string.41, i32 0, i32 0), i1 %andand_result_value64)
  %anonyumous_union_data = alloca %anonmous_union0
  %44 = bitcast %anonmous_union0* %anonyumous_union_data to i8*
  store i8* %44, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 8), align 8
  %anonyumous_union_data65 = load %anonmous_union0, %anonmous_union0* %anonyumous_union_data, align 8
  %45 = bitcast %anonmous_union0* %anonyumous_union_data to i32*
  store i32 123, i32* %45, align 4
  %anonyumous_union_data66 = load %anonmous_union0, %anonmous_union0* %anonyumous_union_data, align 8
  %46 = bitcast %anonmous_union0* %anonyumous_union_data to i32*
  %47 = load i32, i32* %46, align 4
  %eqtmpX67 = icmp eq i32 %47, 123
  call void @xassert(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @global_string.42, i32 0, i32 0), i1 %eqtmpX67)
  %data3 = alloca %Data3
  %48 = bitcast %Data3* %data3 to i8*
  store i8* %48, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 9), align 8
  %data368 = load %Data3, %Data3* %data3, align 8
  %49 = getelementptr inbounds %Data3, %Data3* %data3, i32 0, i32 0
  store i64 123, i64* %49, align 4
  %data369 = load %Data3, %Data3* %data3, align 8
  %50 = getelementptr inbounds %Data3, %Data3* %data3, i32 0, i32 1
  store i32 234, i32* %50, align 4
  %data370 = load %Data3, %Data3* %data3, align 8
  %51 = getelementptr inbounds %Data3, %Data3* %data3, i32 0, i32 0
  %52 = load i64, i64* %51, align 4
  %eqtmpX71 = icmp eq i64 %52, 123
  store i1 %eqtmpX71, i1* %andand_result_var, align 1
  br i1 %eqtmpX71, label %cond_jump_then72, label %cond_jump_end73

cond_jump_then72:                                 ; preds = %cond_jump_end60
  %data374 = load %Data3, %Data3* %data3, align 8
  %53 = getelementptr inbounds %Data3, %Data3* %data3, i32 0, i32 1
  %54 = load i32, i32* %53, align 4
  %eqtmpX75 = icmp eq i32 %54, 234
  %andand76 = and i1 %eqtmpX71, %eqtmpX75
  store i1 %andand76, i1* %andand_result_var, align 1
  br label %cond_jump_end73

cond_jump_end73:                                  ; preds = %cond_jump_then72, %cond_jump_end60
  %andand_result_value77 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @global_string.43, i32 0, i32 0), i1 %andand_result_value77)
  store i1 true, i1* %andand_result_var, align 1
  br i1 true, label %cond_jump_then78, label %cond_jump_end79

cond_jump_then78:                                 ; preds = %cond_jump_end73
  store i1 true, i1* %andand_result_var, align 1
  br label %cond_jump_end79

cond_jump_end79:                                  ; preds = %cond_jump_then78, %cond_jump_end73
  %andand_result_value80 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value80, i1* %andand_result_var, align 1
  br i1 %andand_result_value80, label %cond_jump_then81, label %cond_jump_end82

cond_jump_then81:                                 ; preds = %cond_jump_end79
  store i1 %andand_result_value80, i1* %andand_result_var, align 1
  br label %cond_jump_end82

cond_jump_end82:                                  ; preds = %cond_jump_then81, %cond_jump_end79
  %andand_result_value83 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value83, i1* %andand_result_var, align 1
  br i1 %andand_result_value83, label %cond_jump_then84, label %cond_jump_end85

cond_jump_then84:                                 ; preds = %cond_jump_end82
  store i1 %andand_result_value83, i1* %andand_result_var, align 1
  br label %cond_jump_end85

cond_jump_end85:                                  ; preds = %cond_jump_then84, %cond_jump_end82
  %andand_result_value86 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.44, i32 0, i32 0), i1 %andand_result_value86)
  store i1 true, i1* %andand_result_var, align 1
  br i1 true, label %cond_jump_then87, label %cond_jump_end88

cond_jump_then87:                                 ; preds = %cond_jump_end85
  store i1 true, i1* %andand_result_var, align 1
  br label %cond_jump_end88

cond_jump_end88:                                  ; preds = %cond_jump_then87, %cond_jump_end85
  %andand_result_value89 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @global_string.45, i32 0, i32 0), i1 %andand_result_value89)
  store i1 true, i1* %andand_result_var, align 1
  br i1 true, label %cond_jump_then90, label %cond_jump_end91

cond_jump_then90:                                 ; preds = %cond_jump_end88
  store i1 true, i1* %andand_result_var, align 1
  br label %cond_jump_end91

cond_jump_end91:                                  ; preds = %cond_jump_then90, %cond_jump_end88
  %andand_result_value92 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value92, i1* %andand_result_var, align 1
  br i1 %andand_result_value92, label %cond_jump_then93, label %cond_jump_end94

cond_jump_then93:                                 ; preds = %cond_jump_end91
  store i1 %andand_result_value92, i1* %andand_result_var, align 1
  br label %cond_jump_end94

cond_jump_end94:                                  ; preds = %cond_jump_then93, %cond_jump_end91
  %andand_result_value95 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @global_string.46, i32 0, i32 0), i1 %andand_result_value95)
  %55 = call i8* @calloc(i64 1, i64 12)
  %56 = bitcast i8* %55 to %Data3*
  %data3_2 = alloca %Data3*
  %57 = bitcast %Data3** %data3_2 to i8*
  store i8* %57, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 10), align 8
  store %Data3* %56, %Data3** %data3_2, align 8
  %data3_296 = load %Data3*, %Data3** %data3_2, align 8
  %58 = getelementptr inbounds %Data3, %Data3* %data3_296, i32 0, i32 0
  store i64 234, i64* %58, align 4
  %data3_297 = load %Data3*, %Data3** %data3_2, align 8
  %59 = getelementptr inbounds %Data3, %Data3* %data3_297, i32 0, i32 1
  store i32 345, i32* %59, align 4
  %data3_298 = load %Data3*, %Data3** %data3_2, align 8
  %60 = getelementptr inbounds %Data3, %Data3* %data3_298, i32 0, i32 0
  %61 = load i64, i64* %60, align 4
  %eqtmpX99 = icmp eq i64 %61, 234
  store i1 %eqtmpX99, i1* %andand_result_var, align 1
  br i1 %eqtmpX99, label %cond_jump_then100, label %cond_jump_end101

cond_jump_then100:                                ; preds = %cond_jump_end94
  %data3_2102 = load %Data3*, %Data3** %data3_2, align 8
  %62 = getelementptr inbounds %Data3, %Data3* %data3_2102, i32 0, i32 1
  %63 = load i32, i32* %62, align 4
  %eqtmpX103 = icmp eq i32 %63, 345
  %andand104 = and i1 %eqtmpX99, %eqtmpX103
  store i1 %andand104, i1* %andand_result_var, align 1
  br label %cond_jump_end101

cond_jump_end101:                                 ; preds = %cond_jump_then100, %cond_jump_end94
  %andand_result_value105 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @global_string.47, i32 0, i32 0), i1 %andand_result_value105)
  call void @xassert(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @global_string.48, i32 0, i32 0), i1 true)
  %compl_a = alloca i8
  store i8* %compl_a, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 11), align 8
  store i8 -2, i8* %compl_a, align 1
  %compl_a106 = load i8, i8* %compl_a, align 1
  %xortmp = xor i8 %compl_a106, -1
  %eqtmpX107 = icmp eq i8 %xortmp, 1
  call void @xassert(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.49, i32 0, i32 0), i1 %eqtmpX107)
  %data4 = alloca i32
  %64 = bitcast i32* %data4 to i8*
  store i8* %64, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 12), align 8
  store i32 123, i32* %data4, align 4
  %data4108 = load i32, i32* %data4, align 4
  %p_data4 = alloca i32*
  %65 = bitcast i32** %p_data4 to i8*
  store i8* %65, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 13), align 8
  store i32* %data4, i32** %p_data4, align 8
  %p_data4109 = load i32*, i32** %p_data4, align 8
  %derefference_value = load i32, i32* %p_data4109, align 8
  %eqtmpX110 = icmp eq i32 %derefference_value, 123
  call void @xassert(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @global_string.50, i32 0, i32 0), i1 %eqtmpX110)
  %p_data4111 = load i32*, i32** %p_data4, align 8
  %pp_data4 = alloca i32**
  %66 = bitcast i32*** %pp_data4 to i8*
  store i8* %66, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 14), align 8
  store i32** %p_data4, i32*** %pp_data4, align 8
  %pp_data4112 = load i32**, i32*** %pp_data4, align 8
  %derefference_value113 = load i32*, i32** %pp_data4112, align 8
  %derefference_value114 = load i32, i32* %derefference_value113, align 8
  %eqtmpX115 = icmp eq i32 %derefference_value114, 123
  call void @xassert(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @global_string.51, i32 0, i32 0), i1 %eqtmpX115)
  %67 = call i8* @calloc(i64 128, i64 1)
  %str2 = alloca i8*
  %68 = bitcast i8** %str2 to i8*
  store i8* %68, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 15), align 8
  store i8* %67, i8** %str2, align 8
  %69 = ptrtoint i8* %67 to i64
  %70 = icmp ne i64 %69, 0
  br i1 %70, label %cond_then_block116, label %cond_end117

cond_then_block116:                               ; preds = %cond_jump_end101
  br label %cond_end117

cond_end117:                                      ; preds = %cond_then_block116, %cond_jump_end101
  call void @free(i8* %67)
  %str2118 = load i8*, i8** %str2, align 8
  %71 = call i8* @strcpy(i8* %str2118, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.52, i32 0, i32 0))
  %str2119 = load i8*, i8** %str2, align 8
  %derefference_value120 = load i8, i8* %str2119, align 8
  %72 = load i8, i8* %str2119, align 1
  %addtmp = add nsw i8 %72, 1
  store i8 %addtmp, i8* %str2119, align 8
  %str2121 = load i8*, i8** %str2, align 8
  %73 = call i32 @strcmp(i8* %str2121, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.53, i32 0, i32 0))
  %eqtmpX122 = icmp eq i32 %73, 0
  call void @xassert(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @global_string.54, i32 0, i32 0), i1 %eqtmpX122)
  %str2123 = load i8*, i8** %str2, align 8
  %derefference_value124 = load i8, i8* %str2123, align 8
  %74 = load i8, i8* %str2123, align 1
  %subtmp = sub nsw i8 %74, 1
  store i8 %subtmp, i8* %str2123, align 8
  %str2125 = load i8*, i8** %str2, align 8
  %75 = call i32 @strcmp(i8* %str2125, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.55, i32 0, i32 0))
  %eqtmpX126 = icmp eq i32 %75, 0
  call void @xassert(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @global_string.56, i32 0, i32 0), i1 %eqtmpX126)
  %str2127 = load i8*, i8** %str2, align 8
  %derefference_value128 = load i8, i8* %str2127, align 8
  %76 = load i8, i8* %str2127, align 1
  %addtmp129 = add nsw i8 %76, 2
  store i8 %addtmp129, i8* %str2127, align 8
  %str2130 = load i8*, i8** %str2, align 8
  %77 = call i32 @strcmp(i8* %str2130, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.57, i32 0, i32 0))
  %eqtmpX131 = icmp eq i32 %77, 0
  call void @xassert(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @global_string.58, i32 0, i32 0), i1 %eqtmpX131)
  %comma = alloca i32
  %78 = bitcast i32* %comma to i8*
  store i8* %78, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 16), align 8
  store i32 2, i32* %comma, align 4
  %comma132 = load i32, i32* %comma, align 4
  %eqtmpX133 = icmp eq i32 %comma132, 2
  call void @xassert(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @global_string.59, i32 0, i32 0), i1 %eqtmpX133)
  %plus_plus = alloca i32
  %79 = bitcast i32* %plus_plus to i8*
  store i8* %79, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 17), align 8
  store i32 1, i32* %plus_plus, align 4
  %plus_plus134 = load i32, i32* %plus_plus, align 4
  %addtmp135 = add nsw i32 %plus_plus134, 1
  store i32 %addtmp135, i32* %plus_plus, align 4
  %eqtmpX136 = icmp eq i32 %addtmp135, 2
  call void @xassert(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @global_string.60, i32 0, i32 0), i1 %eqtmpX136)
  %plus_plus137 = load i32, i32* %plus_plus, align 4
  %eqtmpX138 = icmp eq i32 %plus_plus137, 2
  call void @xassert(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @global_string.61, i32 0, i32 0), i1 %eqtmpX138)
  %plus_plus139 = load i32, i32* %plus_plus, align 4
  %subttmp = sub nsw i32 %plus_plus139, 1
  store i32 %subttmp, i32* %plus_plus, align 4
  %eqtmpX140 = icmp eq i32 %subttmp, 1
  store i1 %eqtmpX140, i1* %andand_result_var, align 1
  br i1 %eqtmpX140, label %cond_jump_then141, label %cond_jump_end142

cond_jump_then141:                                ; preds = %cond_end117
  %plus_plus143 = load i32, i32* %plus_plus, align 4
  %eqtmpX144 = icmp eq i32 %plus_plus143, 1
  %andand145 = and i1 %eqtmpX140, %eqtmpX144
  store i1 %andand145, i1* %andand_result_var, align 1
  br label %cond_jump_end142

cond_jump_end142:                                 ; preds = %cond_jump_then141, %cond_end117
  %andand_result_value146 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @global_string.62, i32 0, i32 0), i1 %andand_result_value146)
  %mult_eq = alloca i32
  %80 = bitcast i32* %mult_eq to i8*
  store i8* %80, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 18), align 8
  store i32 12, i32* %mult_eq, align 4
  %mult_eq147 = load i32, i32* %mult_eq, align 4
  %multtmp = mul nsw i32 %mult_eq147, 2
  store i32 %multtmp, i32* %mult_eq, align 4
  %mult_eq148 = load i32, i32* %mult_eq, align 4
  %eqtmpX149 = icmp eq i32 %mult_eq148, 24
  call void @xassert(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @global_string.63, i32 0, i32 0), i1 %eqtmpX149)
  %array = alloca [100 x i8]
  %81 = bitcast [100 x i8]* %array to i8*
  store i8* %81, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 19), align 8
  %array150 = load [100 x i8], [100 x i8]* %array, align 1
  %82 = bitcast [100 x i8]* %array to i8*
  %83 = call i8* @strcpy(i8* %82, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.64, i32 0, i32 0))
  %array151 = load [100 x i8], [100 x i8]* %array, align 1
  %84 = bitcast [100 x i8]* %array to i8*
  %85 = call i32 @strcmp(i8* %84, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.65, i32 0, i32 0))
  %eqtmpX152 = icmp eq i32 %85, 0
  call void @xassert(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @global_string.66, i32 0, i32 0), i1 %eqtmpX152)
  %array_num = alloca i32
  %86 = bitcast i32* %array_num to i8*
  store i8* %86, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 20), align 8
  store i32 128, i32* %array_num, align 4
  %array_num153 = load i32, i32* %array_num, align 4
  %array2 = alloca i8*
  %87 = bitcast i8** %array2 to i8*
  store i8* %87, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 21), align 8
  %element_memory = alloca i8, i32 %array_num153
  store i8* %element_memory, i8** %array2, align 8
  %array2154 = load i8*, i8** %array2, align 1
  %88 = call i8* @strcpy(i8* %array2154, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.67, i32 0, i32 0))
  %array2155 = load i8*, i8** %array2, align 1
  %89 = call i32 @strcmp(i8* %array2155, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.68, i32 0, i32 0))
  %eqtmpX156 = icmp eq i32 %89, 0
  call void @xassert(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.69, i32 0, i32 0), i1 %eqtmpX156)
  %array3 = alloca [3 x i32]
  %90 = bitcast [3 x i32]* %array3 to i8*
  store i8* %90, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 22), align 8
  %array3157 = load [3 x i32], [3 x i32]* %array3, align 4
  %91 = bitcast [3 x i32]* %array3 to i32*
  %element_addressC = getelementptr i32, i32* %91, i32 0
  store i32 123, i32* %element_addressC, align 4
  %array3158 = load [3 x i32], [3 x i32]* %array3, align 4
  %92 = bitcast [3 x i32]* %array3 to i32*
  %element_address = getelementptr i32, i32* %92, i32 0
  %element = load i32, i32* %element_address, align 4
  %eqtmpX159 = icmp eq i32 %element, 123
  call void @xassert(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.70, i32 0, i32 0), i1 %eqtmpX159)
  %array4 = alloca [3 x [3 x i32]]
  %93 = bitcast [3 x [3 x i32]]* %array4 to i8*
  store i8* %93, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 23), align 8
  %array4160 = load [3 x [3 x i32]], [3 x [3 x i32]]* %array4, align 4
  %94 = getelementptr inbounds [3 x [3 x i32]], [3 x [3 x i32]]* %array4, i32 1, i32 2
  %95 = getelementptr inbounds [3 x i32], [3 x i32]* %94, i32 2
  %96 = bitcast [3 x i32]* %95 to i32*
  store i32 123, i32* %96, align 4
  %array4161 = load [3 x [3 x i32]], [3 x [3 x i32]]* %array4, align 4
  %97 = getelementptr inbounds [3 x [3 x i32]], [3 x [3 x i32]]* %array4, i32 1, i32 2
  %98 = getelementptr inbounds [3 x i32], [3 x i32]* %97, i32 2
  %99 = bitcast [3 x i32]* %98 to i32*
  %element162 = load i32, i32* %99, align 4
  %eqtmpX163 = icmp eq i32 %element162, 123
  call void @xassert(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.71, i32 0, i32 0), i1 %eqtmpX163)
  %array5 = alloca [100 x [10 x i8]]
  %100 = bitcast [100 x [10 x i8]]* %array5 to i8*
  store i8* %100, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 24), align 8
  %array5164 = load [100 x [10 x i8]], [100 x [10 x i8]]* %array5, align 1
  %101 = getelementptr inbounds [100 x [10 x i8]], [100 x [10 x i8]]* %array5, i32 0
  %102 = bitcast [100 x [10 x i8]]* %101 to i8*
  %element165 = load i8, i8* %102, align 1
  %103 = call i8* @strcpy(i8* %102, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.72, i32 0, i32 0))
  %array5166 = load [100 x [10 x i8]], [100 x [10 x i8]]* %array5, align 1
  %104 = getelementptr inbounds [100 x [10 x i8]], [100 x [10 x i8]]* %array5, i32 1
  %105 = bitcast [100 x [10 x i8]]* %104 to i8*
  %element167 = load i8, i8* %105, align 1
  %106 = call i8* @strcpy(i8* %105, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.73, i32 0, i32 0))
  %array5168 = load [100 x [10 x i8]], [100 x [10 x i8]]* %array5, align 1
  %107 = getelementptr inbounds [100 x [10 x i8]], [100 x [10 x i8]]* %array5, i32 0
  %108 = bitcast [100 x [10 x i8]]* %107 to i8*
  %element169 = load i8, i8* %108, align 1
  %109 = call i32 @strcmp(i8* %108, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.74, i32 0, i32 0))
  %eqtmpX170 = icmp eq i32 %109, 0
  store i1 %eqtmpX170, i1* %andand_result_var, align 1
  br i1 %eqtmpX170, label %cond_jump_then171, label %cond_jump_end172

cond_jump_then171:                                ; preds = %cond_jump_end142
  %array5173 = load [100 x [10 x i8]], [100 x [10 x i8]]* %array5, align 1
  %110 = getelementptr inbounds [100 x [10 x i8]], [100 x [10 x i8]]* %array5, i32 1
  %111 = bitcast [100 x [10 x i8]]* %110 to i8*
  %element174 = load i8, i8* %111, align 1
  %112 = call i32 @strcmp(i8* %111, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.75, i32 0, i32 0))
  %eqtmpX175 = icmp eq i32 %112, 0
  %andand176 = and i1 %eqtmpX170, %eqtmpX175
  store i1 %andand176, i1* %andand_result_var, align 1
  br label %cond_jump_end172

cond_jump_end172:                                 ; preds = %cond_jump_then171, %cond_jump_end142
  %andand_result_value177 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.76, i32 0, i32 0), i1 %andand_result_value177)
  %gArray = load [3 x i32], [3 x i32]* @gArray, align 4
  %element178 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @gArray, i32 0, i32 0), align 4
  %eqtmpX179 = icmp eq i32 %element178, 1
  store i1 %eqtmpX179, i1* %andand_result_var, align 1
  br i1 %eqtmpX179, label %cond_jump_then180, label %cond_jump_end181

cond_jump_then180:                                ; preds = %cond_jump_end172
  %gArray182 = load [3 x i32], [3 x i32]* @gArray, align 4
  %element183 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @gArray, i32 0, i32 1), align 4
  %eqtmpX184 = icmp eq i32 %element183, 2
  %andand185 = and i1 %eqtmpX179, %eqtmpX184
  store i1 %andand185, i1* %andand_result_var, align 1
  br label %cond_jump_end181

cond_jump_end181:                                 ; preds = %cond_jump_then180, %cond_jump_end172
  %andand_result_value186 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value186, i1* %andand_result_var, align 1
  br i1 %andand_result_value186, label %cond_jump_then187, label %cond_jump_end188

cond_jump_then187:                                ; preds = %cond_jump_end181
  %gArray189 = load [3 x i32], [3 x i32]* @gArray, align 4
  %element190 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @gArray, i32 0, i32 2), align 4
  %eqtmpX191 = icmp eq i32 %element190, 3
  %andand192 = and i1 %andand_result_value186, %eqtmpX191
  store i1 %andand192, i1* %andand_result_var, align 1
  br label %cond_jump_end188

cond_jump_end188:                                 ; preds = %cond_jump_then187, %cond_jump_end181
  %andand_result_value193 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @global_string.77, i32 0, i32 0), i1 %andand_result_value193)
  %array6 = alloca [3 x i32]
  %113 = bitcast [3 x i32]* %array6 to i8*
  store i8* %113, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 25), align 8
  %114 = load [3 x i32], [3 x i32]* %array6, align 4
  %115 = bitcast [3 x i32]* %array6 to i32*
  %element_address194 = getelementptr i32, i32* %115, i64 0
  store i32 1, i32* %element_address194, align 8
  %element_address195 = getelementptr i32, i32* %115, i64 1
  store i32 2, i32* %element_address195, align 8
  %element_address196 = getelementptr i32, i32* %115, i64 2
  store i32 3, i32* %element_address196, align 8
  %array6197 = load [3 x i32], [3 x i32]* %array6, align 4
  %116 = bitcast [3 x i32]* %array6 to i32*
  %element_address198 = getelementptr i32, i32* %116, i32 0
  %element199 = load i32, i32* %element_address198, align 4
  %eqtmpX200 = icmp eq i32 %element199, 1
  store i1 %eqtmpX200, i1* %andand_result_var, align 1
  br i1 %eqtmpX200, label %cond_jump_then201, label %cond_jump_end202

cond_jump_then201:                                ; preds = %cond_jump_end188
  %array6203 = load [3 x i32], [3 x i32]* %array6, align 4
  %117 = bitcast [3 x i32]* %array6 to i32*
  %element_address204 = getelementptr i32, i32* %117, i32 1
  %element205 = load i32, i32* %element_address204, align 4
  %eqtmpX206 = icmp eq i32 %element205, 2
  %andand207 = and i1 %eqtmpX200, %eqtmpX206
  store i1 %andand207, i1* %andand_result_var, align 1
  br label %cond_jump_end202

cond_jump_end202:                                 ; preds = %cond_jump_then201, %cond_jump_end188
  %andand_result_value208 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value208, i1* %andand_result_var, align 1
  br i1 %andand_result_value208, label %cond_jump_then209, label %cond_jump_end210

cond_jump_then209:                                ; preds = %cond_jump_end202
  %array6211 = load [3 x i32], [3 x i32]* %array6, align 4
  %118 = bitcast [3 x i32]* %array6 to i32*
  %element_address212 = getelementptr i32, i32* %118, i32 2
  %element213 = load i32, i32* %element_address212, align 4
  %eqtmpX214 = icmp eq i32 %element213, 3
  %andand215 = and i1 %andand_result_value208, %eqtmpX214
  store i1 %andand215, i1* %andand_result_var, align 1
  br label %cond_jump_end210

cond_jump_end210:                                 ; preds = %cond_jump_then209, %cond_jump_end202
  %andand_result_value216 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @global_string.78, i32 0, i32 0), i1 %andand_result_value216)
  %array7 = alloca [3 x i8]
  %119 = bitcast [3 x i8]* %array7 to i8*
  store i8* %119, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 26), align 8
  %120 = load [3 x i8], [3 x i8]* %array7, align 1
  %121 = bitcast [3 x i8]* %array7 to i8*
  %element_address217 = getelementptr i8, i8* %121, i64 0
  store i8 65, i8* %element_address217, align 8
  %element_address218 = getelementptr i8, i8* %121, i64 1
  store i8 66, i8* %element_address218, align 8
  %element_address219 = getelementptr i8, i8* %121, i64 2
  store i8 0, i8* %element_address219, align 8
  %array7220 = load [3 x i8], [3 x i8]* %array7, align 1
  %122 = bitcast [3 x i8]* %array7 to i8*
  %123 = call i32 @strcmp(i8* %122, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @global_string.79, i32 0, i32 0))
  %eqtmpX221 = icmp eq i32 %123, 0
  call void @xassert(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @global_string.80, i32 0, i32 0), i1 %eqtmpX221)
  %gArray2 = load [3 x i8], [3 x i8]* @gArray2, align 1
  %124 = call i32 @strcmp(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @gArray2, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @global_string.81, i32 0, i32 0))
  %eqtmpX222 = icmp eq i32 %124, 0
  call void @xassert(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @global_string.82, i32 0, i32 0), i1 %eqtmpX222)
  %gArray3 = load [3 x i32], [3 x i32]* @gArray3, align 4
  %element223 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @gArray3, i32 0, i32 0), align 4
  %eqtmpX224 = icmp eq i32 %element223, 1
  store i1 %eqtmpX224, i1* %andand_result_var, align 1
  br i1 %eqtmpX224, label %cond_jump_then225, label %cond_jump_end226

cond_jump_then225:                                ; preds = %cond_jump_end210
  %gArray3227 = load [3 x i32], [3 x i32]* @gArray3, align 4
  %element228 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @gArray3, i32 0, i32 1), align 4
  %eqtmpX229 = icmp eq i32 %element228, 2
  %andand230 = and i1 %eqtmpX224, %eqtmpX229
  store i1 %andand230, i1* %andand_result_var, align 1
  br label %cond_jump_end226

cond_jump_end226:                                 ; preds = %cond_jump_then225, %cond_jump_end210
  %andand_result_value231 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value231, i1* %andand_result_var, align 1
  br i1 %andand_result_value231, label %cond_jump_then232, label %cond_jump_end233

cond_jump_then232:                                ; preds = %cond_jump_end226
  %gArray3234 = load [3 x i32], [3 x i32]* @gArray3, align 4
  %element235 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @gArray3, i32 0, i32 2), align 4
  %eqtmpX236 = icmp eq i32 %element235, 3
  %andand237 = and i1 %andand_result_value231, %eqtmpX236
  store i1 %andand237, i1* %andand_result_var, align 1
  br label %cond_jump_end233

cond_jump_end233:                                 ; preds = %cond_jump_then232, %cond_jump_end226
  %andand_result_value238 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @global_string.83, i32 0, i32 0), i1 %andand_result_value238)
  %array8 = alloca [3 x i32]
  %125 = bitcast [3 x i32]* %array8 to i8*
  store i8* %125, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 27), align 8
  %126 = load [3 x i32], [3 x i32]* %array8, align 4
  %127 = bitcast [3 x i32]* %array8 to i32*
  %element_address239 = getelementptr i32, i32* %127, i64 0
  store i32 1, i32* %element_address239, align 8
  %element_address240 = getelementptr i32, i32* %127, i64 1
  store i32 2, i32* %element_address240, align 8
  %element_address241 = getelementptr i32, i32* %127, i64 2
  store i32 3, i32* %element_address241, align 8
  %array8242 = load [3 x i32], [3 x i32]* %array8, align 4
  %128 = bitcast [3 x i32]* %array8 to i32*
  %element_address243 = getelementptr i32, i32* %128, i32 0
  %element244 = load i32, i32* %element_address243, align 4
  %eqtmpX245 = icmp eq i32 %element244, 1
  store i1 %eqtmpX245, i1* %andand_result_var, align 1
  br i1 %eqtmpX245, label %cond_jump_then246, label %cond_jump_end247

cond_jump_then246:                                ; preds = %cond_jump_end233
  %array8248 = load [3 x i32], [3 x i32]* %array8, align 4
  %129 = bitcast [3 x i32]* %array8 to i32*
  %element_address249 = getelementptr i32, i32* %129, i32 1
  %element250 = load i32, i32* %element_address249, align 4
  %eqtmpX251 = icmp eq i32 %element250, 2
  %andand252 = and i1 %eqtmpX245, %eqtmpX251
  store i1 %andand252, i1* %andand_result_var, align 1
  br label %cond_jump_end247

cond_jump_end247:                                 ; preds = %cond_jump_then246, %cond_jump_end233
  %andand_result_value253 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value253, i1* %andand_result_var, align 1
  br i1 %andand_result_value253, label %cond_jump_then254, label %cond_jump_end255

cond_jump_then254:                                ; preds = %cond_jump_end247
  %array8256 = load [3 x i32], [3 x i32]* %array8, align 4
  %130 = bitcast [3 x i32]* %array8 to i32*
  %element_address257 = getelementptr i32, i32* %130, i32 2
  %element258 = load i32, i32* %element_address257, align 4
  %eqtmpX259 = icmp eq i32 %element258, 3
  %andand260 = and i1 %andand_result_value253, %eqtmpX259
  store i1 %andand260, i1* %andand_result_var, align 1
  br label %cond_jump_end255

cond_jump_end255:                                 ; preds = %cond_jump_then254, %cond_jump_end247
  %andand_result_value261 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @global_string.84, i32 0, i32 0), i1 %andand_result_value261)
  %ccc = alloca i8
  store i8* %ccc, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 28), align 8
  store i8 10, i8* %ccc, align 1
  %ccc2 = alloca i8
  store i8* %ccc2, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 29), align 8
  store i8 97, i8* %ccc2, align 1
  %ccc3 = alloca i8
  store i8* %ccc3, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 30), align 8
  store i8 0, i8* %ccc3, align 1
  %ccc262 = load i8, i8* %ccc, align 1
  %eqtmpX263 = icmp eq i8 %ccc262, 10
  store i1 %eqtmpX263, i1* %andand_result_var, align 1
  br i1 %eqtmpX263, label %cond_jump_then264, label %cond_jump_end265

cond_jump_then264:                                ; preds = %cond_jump_end255
  %ccc2266 = load i8, i8* %ccc2, align 1
  %eqtmpX267 = icmp eq i8 %ccc2266, 97
  %andand268 = and i1 %eqtmpX263, %eqtmpX267
  store i1 %andand268, i1* %andand_result_var, align 1
  br label %cond_jump_end265

cond_jump_end265:                                 ; preds = %cond_jump_then264, %cond_jump_end255
  %andand_result_value269 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value269, i1* %andand_result_var, align 1
  br i1 %andand_result_value269, label %cond_jump_then270, label %cond_jump_end271

cond_jump_then270:                                ; preds = %cond_jump_end265
  %ccc3272 = load i8, i8* %ccc3, align 1
  %eqtmpX273 = icmp eq i8 %ccc3272, 0
  %andand274 = and i1 %andand_result_value269, %eqtmpX273
  store i1 %andand274, i1* %andand_result_var, align 1
  br label %cond_jump_end271

cond_jump_end271:                                 ; preds = %cond_jump_then270, %cond_jump_end265
  %andand_result_value275 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @global_string.85, i32 0, i32 0), i1 %andand_result_value275)
  %131 = load %Data3*, %Data3** %data3_2, align 8
  %132 = ptrtoint %Data3* %131 to i64
  %133 = icmp ne i64 %132, 0
  br i1 %133, label %cond_then_block276, label %cond_end277

cond_then_block276:                               ; preds = %cond_jump_end271
  br label %cond_end277

cond_end277:                                      ; preds = %cond_then_block276, %cond_jump_end271
  %134 = bitcast %Data3* %131 to i8*
  call void @free(i8* %134)
  %135 = load i8*, i8** %b, align 8
  %136 = ptrtoint i8* %135 to i64
  %137 = icmp ne i64 %136, 0
  br i1 %137, label %cond_then_block278, label %cond_end279

cond_then_block278:                               ; preds = %cond_end277
  br label %cond_end279

cond_end279:                                      ; preds = %cond_then_block278, %cond_end277
  call void @free(i8* %135)
  ret i32 0
}

define internal i32 @coroutine1() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %0 = call i32 @puts(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.17, i32 0, i32 0))
  %1 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable9, i32 0, i32 1), align 8
  %2 = bitcast i8* %1 to i32*
  %xxx = load i32, i32* %2, align 4
  ret i32 %xxx
}

define i32 @GenericsData_int_show(%GenericsData_int %self) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %self2 = alloca %GenericsData_int
  store %GenericsData_int %self, %GenericsData_int* %self2, align 8
  %0 = bitcast %GenericsData_int* %self2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable10, i32 0, i32 0), align 8
  %a = alloca i32
  %1 = bitcast i32* %a to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable10, i32 0, i32 1), align 8
  store i32 123, i32* %a, align 4
  %b = alloca i32
  %2 = bitcast i32* %b to i8*
  store i8* %2, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable10, i32 0, i32 2), align 8
  store i32 234, i32* %b, align 4
  %3 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable10, i32 0, i32 0), align 8
  %4 = bitcast i8* %3 to %GenericsData_int*
  %self3 = load %GenericsData_int, %GenericsData_int* %4, align 8
  %a4 = load i32, i32* %a, align 4
  %5 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %4, i32 0, i32 0
  store i32 %a4, i32* %5, align 4
  %6 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable10, i32 0, i32 0), align 8
  %7 = bitcast i8* %6 to %GenericsData_int*
  %self5 = load %GenericsData_int, %GenericsData_int* %7, align 8
  %b6 = load i32, i32* %b, align 4
  %8 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %7, i32 0, i32 1
  store i32 %b6, i32* %8, align 4
  %9 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable10, i32 0, i32 0), align 8
  %10 = bitcast i8* %9 to %GenericsData_int*
  %self7 = load %GenericsData_int, %GenericsData_int* %10, align 8
  %11 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %10, i32 0, i32 1
  %12 = load i32, i32* %11, align 4
  %13 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable10, i32 0, i32 0), align 8
  %14 = bitcast i8* %13 to %GenericsData_int*
  %self8 = load %GenericsData_int, %GenericsData_int* %14, align 8
  %15 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %14, i32 0, i32 0
  %16 = load i32, i32* %15, align 4
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @global_string.21, i32 0, i32 0), i32 %16, i32 %12)
  ret i32 123
}

define i32 @fun2(i32 %a) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %a2 = alloca i32
  store i32 %a, i32* %a2, align 4
  %0 = bitcast i32* %a2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable11, i32 0, i32 0), align 8
  %1 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable11, i32 0, i32 0), align 8
  %2 = bitcast i8* %1 to i32*
  %a3 = load i32, i32* %2, align 4
  %addtmp = add nsw i32 %a3, 1
  ret i32 %addtmp
}

define internal i32 @coroutine2(i8* %str) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %str2 = alloca i8*
  store i8* %str, i8** %str2, align 8
  %0 = bitcast i8** %str2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable11, i32 0, i32 5), align 8
  %1 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable11, i32 0, i32 5), align 8
  %2 = bitcast i8* %1 to i8**
  %str3 = load i8*, i8** %2, align 8
  %3 = call i32 @atoi(i8* %str3)
  ret i32 %3
}

define i32 @fun3(i32 (i8*)* %aaa, i8* %bbb) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %aaa2 = alloca i32 (i8*)*
  store i32 (i8*)* %aaa, i32 (i8*)** %aaa2, align 8
  %0 = bitcast i32 (i8*)** %aaa2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable12, i32 0, i32 0), align 8
  %bbb3 = alloca i8*
  store i8* %bbb, i8** %bbb3, align 8
  %1 = bitcast i8** %bbb3 to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable12, i32 0, i32 1), align 8
  %2 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable12, i32 0, i32 0), align 8
  %3 = bitcast i8* %2 to i32 (i8*)**
  %aaa4 = load i32 (i8*)*, i32 (i8*)** %3, align 8
  %4 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable12, i32 0, i32 1), align 8
  %5 = bitcast i8* %4 to i8**
  %bbb5 = load i8*, i8** %5, align 8
  %6 = call i32 %aaa4(i8* %bbb5)
  ret i32 %6
}

define internal i32 @coroutine3(i32 %c) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %c2 = alloca i32
  store i32 %c, i32* %c2, align 4
  %0 = bitcast i32* %c2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable12, i32 0, i32 5), align 8
  %1 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable12, i32 0, i32 5), align 8
  %2 = bitcast i8* %1 to i32*
  %c3 = load i32, i32* %2, align 4
  %addtmp = add nsw i32 %c3, 1
  ret i32 %addtmp
}

define i32 @GenericsData_int_map(%GenericsData_int %self, i32 (i32)* %aaa) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %self2 = alloca %GenericsData_int
  store %GenericsData_int %self, %GenericsData_int* %self2, align 8
  %0 = bitcast %GenericsData_int* %self2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable13, i32 0, i32 0), align 8
  %aaa3 = alloca i32 (i32)*
  store i32 (i32)* %aaa, i32 (i32)** %aaa3, align 8
  %1 = bitcast i32 (i32)** %aaa3 to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable13, i32 0, i32 1), align 8
  %2 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable13, i32 0, i32 0), align 8
  %3 = bitcast i8* %2 to %GenericsData_int*
  %self4 = load %GenericsData_int, %GenericsData_int* %3, align 8
  %4 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %3, i32 0, i32 0
  store i32 123, i32* %4, align 4
  %5 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable13, i32 0, i32 1), align 8
  %6 = bitcast i8* %5 to i32 (i32)**
  %aaa5 = load i32 (i32)*, i32 (i32)** %6, align 8
  %7 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable13, i32 0, i32 0), align 8
  %8 = bitcast i8* %7 to %GenericsData_int*
  %self6 = load %GenericsData_int, %GenericsData_int* %8, align 8
  %9 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %8, i32 0, i32 0
  %10 = load i32, i32* %9, align 4
  %11 = call i32 %aaa5(i32 %10)
  ret i32 %11
}

define void @GenericsData2_int_fun(%GenericsData2_int* %self) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %self2 = alloca %GenericsData2_int*
  store %GenericsData2_int* %self, %GenericsData2_int** %self2, align 8
  %0 = bitcast %GenericsData2_int** %self2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable14, i32 0, i32 0), align 8
  %data = alloca %GenericsData_int
  %1 = bitcast %GenericsData_int* %data to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable14, i32 0, i32 1), align 8
  %data3 = load %GenericsData_int, %GenericsData_int* %data, align 8
  %2 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %data, i32 0, i32 0
  store i32 123, i32* %2, align 4
  %data4 = load %GenericsData_int, %GenericsData_int* %data, align 8
  %3 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %data, i32 0, i32 1
  store i32 234, i32* %3, align 4
  %data5 = load %GenericsData_int, %GenericsData_int* %data, align 8
  %4 = call i32 @GenericsData_int_show.27(%GenericsData_int %data5)
  ret void
}

define i32 @GenericsData_int_show.27(%GenericsData_int %self) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %self2 = alloca %GenericsData_int
  store %GenericsData_int %self, %GenericsData_int* %self2, align 8
  %0 = bitcast %GenericsData_int* %self2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable15, i32 0, i32 0), align 8
  %a = alloca i32
  %1 = bitcast i32* %a to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable15, i32 0, i32 1), align 8
  store i32 123, i32* %a, align 4
  %b = alloca i32
  %2 = bitcast i32* %b to i8*
  store i8* %2, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable15, i32 0, i32 2), align 8
  store i32 234, i32* %b, align 4
  %3 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable15, i32 0, i32 0), align 8
  %4 = bitcast i8* %3 to %GenericsData_int*
  %self3 = load %GenericsData_int, %GenericsData_int* %4, align 8
  %a4 = load i32, i32* %a, align 4
  %5 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %4, i32 0, i32 0
  store i32 %a4, i32* %5, align 4
  %6 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable15, i32 0, i32 0), align 8
  %7 = bitcast i8* %6 to %GenericsData_int*
  %self5 = load %GenericsData_int, %GenericsData_int* %7, align 8
  %b6 = load i32, i32* %b, align 4
  %8 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %7, i32 0, i32 1
  store i32 %b6, i32* %8, align 4
  %9 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable15, i32 0, i32 0), align 8
  %10 = bitcast i8* %9 to %GenericsData_int*
  %self7 = load %GenericsData_int, %GenericsData_int* %10, align 8
  %11 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %10, i32 0, i32 1
  %12 = load i32, i32* %11, align 4
  %13 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable15, i32 0, i32 0), align 8
  %14 = bitcast i8* %13 to %GenericsData_int*
  %self8 = load %GenericsData_int, %GenericsData_int* %14, align 8
  %15 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %14, i32 0, i32 0
  %16 = load i32, i32* %15, align 4
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @global_string.28, i32 0, i32 0), i32 %16, i32 %12)
  ret i32 123
}

define void @GenericsData3_int_fun_1(%GenericsData3_int %self) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %self2 = alloca %GenericsData3_int
  store %GenericsData3_int %self, %GenericsData3_int* %self2, align 8
  %0 = bitcast %GenericsData3_int* %self2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable16, i32 0, i32 0), align 8
  %1 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable16, i32 0, i32 0), align 8
  %2 = bitcast i8* %1 to %GenericsData3_int*
  %self3 = load %GenericsData3_int, %GenericsData3_int* %2, align 8
  call void @GenericsData3_int_fun(%GenericsData3_int %self3)
  %3 = call i32 @puts(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @global_string.33, i32 0, i32 0))
  %4 = call i8* @calloc(i64 1, i64 4)
  %5 = bitcast i8* %4 to %GenericsData2_int*
  %xyz = alloca %GenericsData2_int*
  %6 = bitcast %GenericsData2_int** %xyz to i8*
  store i8* %6, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable19, i32 0, i32 1), align 8
  store %GenericsData2_int* %5, %GenericsData2_int** %xyz, align 8
  %7 = ptrtoint %GenericsData2_int* %5 to i64
  %8 = icmp ne i64 %7, 0
  br i1 %8, label %cond_then_block, label %cond_end

cond_then_block:                                  ; preds = %entry
  br label %cond_end

cond_end:                                         ; preds = %cond_then_block, %entry
  %9 = bitcast %GenericsData2_int* %5 to i8*
  call void @free(i8* %9)
  %xyz4 = load %GenericsData2_int*, %GenericsData2_int** %xyz, align 8
  call void @GenericsData2_int_fun.34(%GenericsData2_int* %xyz4)
  ret void
}

define void @GenericsData3_int_fun(%GenericsData3_int %self) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %self2 = alloca %GenericsData3_int
  store %GenericsData3_int %self, %GenericsData3_int* %self2, align 8
  %0 = bitcast %GenericsData3_int* %self2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable17, i32 0, i32 0), align 8
  %1 = call i32 @puts(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @global_string.29, i32 0, i32 0))
  %2 = call i8* @calloc(i64 1, i64 4)
  %3 = bitcast i8* %2 to %GenericsData2_int*
  %xyz = alloca %GenericsData2_int*
  %4 = bitcast %GenericsData2_int** %xyz to i8*
  store i8* %4, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable17, i32 0, i32 1), align 8
  store %GenericsData2_int* %3, %GenericsData2_int** %xyz, align 8
  %5 = ptrtoint %GenericsData2_int* %3 to i64
  %6 = icmp ne i64 %5, 0
  br i1 %6, label %cond_then_block, label %cond_end

cond_then_block:                                  ; preds = %entry
  br label %cond_end

cond_end:                                         ; preds = %cond_then_block, %entry
  %7 = bitcast %GenericsData2_int* %3 to i8*
  call void @free(i8* %7)
  %xyz3 = load %GenericsData2_int*, %GenericsData2_int** %xyz, align 8
  call void @GenericsData2_int_fun.30(%GenericsData2_int* %xyz3)
  ret void
}

define void @GenericsData2_int_fun.30(%GenericsData2_int* %self) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %self2 = alloca %GenericsData2_int*
  store %GenericsData2_int* %self, %GenericsData2_int** %self2, align 8
  %0 = bitcast %GenericsData2_int** %self2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable18, i32 0, i32 0), align 8
  %data = alloca %GenericsData_int
  %1 = bitcast %GenericsData_int* %data to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable18, i32 0, i32 1), align 8
  %data3 = load %GenericsData_int, %GenericsData_int* %data, align 8
  %2 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %data, i32 0, i32 0
  store i32 123, i32* %2, align 4
  %data4 = load %GenericsData_int, %GenericsData_int* %data, align 8
  %3 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %data, i32 0, i32 1
  store i32 234, i32* %3, align 4
  %data5 = load %GenericsData_int, %GenericsData_int* %data, align 8
  %4 = call i32 @GenericsData_int_show.31(%GenericsData_int %data5)
  ret void
}

define i32 @GenericsData_int_show.31(%GenericsData_int %self) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %self2 = alloca %GenericsData_int
  store %GenericsData_int %self, %GenericsData_int* %self2, align 8
  %0 = bitcast %GenericsData_int* %self2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable19, i32 0, i32 0), align 8
  %a = alloca i32
  %1 = bitcast i32* %a to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable19, i32 0, i32 1), align 8
  store i32 123, i32* %a, align 4
  %b = alloca i32
  %2 = bitcast i32* %b to i8*
  store i8* %2, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable19, i32 0, i32 2), align 8
  store i32 234, i32* %b, align 4
  %3 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable19, i32 0, i32 0), align 8
  %4 = bitcast i8* %3 to %GenericsData_int*
  %self3 = load %GenericsData_int, %GenericsData_int* %4, align 8
  %a4 = load i32, i32* %a, align 4
  %5 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %4, i32 0, i32 0
  store i32 %a4, i32* %5, align 4
  %6 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable19, i32 0, i32 0), align 8
  %7 = bitcast i8* %6 to %GenericsData_int*
  %self5 = load %GenericsData_int, %GenericsData_int* %7, align 8
  %b6 = load i32, i32* %b, align 4
  %8 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %7, i32 0, i32 1
  store i32 %b6, i32* %8, align 4
  %9 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable19, i32 0, i32 0), align 8
  %10 = bitcast i8* %9 to %GenericsData_int*
  %self7 = load %GenericsData_int, %GenericsData_int* %10, align 8
  %11 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %10, i32 0, i32 1
  %12 = load i32, i32* %11, align 4
  %13 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable19, i32 0, i32 0), align 8
  %14 = bitcast i8* %13 to %GenericsData_int*
  %self8 = load %GenericsData_int, %GenericsData_int* %14, align 8
  %15 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %14, i32 0, i32 0
  %16 = load i32, i32* %15, align 4
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @global_string.32, i32 0, i32 0), i32 %16, i32 %12)
  ret i32 123
}

define void @GenericsData2_int_fun.34(%GenericsData2_int* %self) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %self2 = alloca %GenericsData2_int*
  store %GenericsData2_int* %self, %GenericsData2_int** %self2, align 8
  %0 = bitcast %GenericsData2_int** %self2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable20, i32 0, i32 0), align 8
  %data = alloca %GenericsData_int
  %1 = bitcast %GenericsData_int* %data to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable20, i32 0, i32 1), align 8
  %data3 = load %GenericsData_int, %GenericsData_int* %data, align 8
  %2 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %data, i32 0, i32 0
  store i32 123, i32* %2, align 4
  %data4 = load %GenericsData_int, %GenericsData_int* %data, align 8
  %3 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %data, i32 0, i32 1
  store i32 234, i32* %3, align 4
  %data5 = load %GenericsData_int, %GenericsData_int* %data, align 8
  %4 = call i32 @GenericsData_int_show.35(%GenericsData_int %data5)
  ret void
}

define i32 @GenericsData_int_show.35(%GenericsData_int %self) {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %self2 = alloca %GenericsData_int
  store %GenericsData_int %self, %GenericsData_int* %self2, align 8
  %0 = bitcast %GenericsData_int* %self2 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 0), align 8
  %a = alloca i32
  %1 = bitcast i32* %a to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 1), align 8
  store i32 123, i32* %a, align 4
  %b = alloca i32
  %2 = bitcast i32* %b to i8*
  store i8* %2, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 2), align 8
  store i32 234, i32* %b, align 4
  %3 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 0), align 8
  %4 = bitcast i8* %3 to %GenericsData_int*
  %self3 = load %GenericsData_int, %GenericsData_int* %4, align 8
  %a4 = load i32, i32* %a, align 4
  %5 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %4, i32 0, i32 0
  store i32 %a4, i32* %5, align 4
  %6 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 0), align 8
  %7 = bitcast i8* %6 to %GenericsData_int*
  %self5 = load %GenericsData_int, %GenericsData_int* %7, align 8
  %b6 = load i32, i32* %b, align 4
  %8 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %7, i32 0, i32 1
  store i32 %b6, i32* %8, align 4
  %9 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 0), align 8
  %10 = bitcast i8* %9 to %GenericsData_int*
  %self7 = load %GenericsData_int, %GenericsData_int* %10, align 8
  %11 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %10, i32 0, i32 1
  %12 = load i32, i32* %11, align 4
  %13 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 0), align 8
  %14 = bitcast i8* %13 to %GenericsData_int*
  %self8 = load %GenericsData_int, %GenericsData_int* %14, align 8
  %15 = getelementptr inbounds %GenericsData_int, %GenericsData_int* %14, i32 0, i32 0
  %16 = load i32, i32* %15, align 4
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @global_string.36, i32 0, i32 0), i32 %16, i32 %12)
  ret i32 123
}
