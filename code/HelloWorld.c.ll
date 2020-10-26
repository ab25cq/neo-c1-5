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
@gArray4 = global [3 x [3 x [3 x i32]]] [[3 x [3 x i32]] [[3 x i32] [i32 1, i32 2, i32 3], [3 x i32] [i32 2, i32 3, i32 4], [3 x i32] [i32 5, i32 6, i32 7]], [3 x [3 x i32]] [[3 x i32] [i32 1, i32 2, i32 3], [3 x i32] [i32 1, i32 2, i32 3], [3 x i32] [i32 1, i32 2, i32 3]], [3 x [3 x i32]] [[3 x i32] [i32 11, i32 12, i32 13], [3 x i32] [i32 14, i32 15, i32 16], [3 x i32] [i32 17, i32 18, i32 19]]], align 4
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
@global_string.29 = private constant [32 x i8] c"GenericsData3!<T>::fun version1\00", align 1
@gLVTable18 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable19 = internal global [512 x i8*] zeroinitializer, align 8
@global_string.32 = private constant [7 x i8] c"%d %d\0A\00", align 1
@global_string.33 = private constant [32 x i8] c"GenericsData3!<T>::fun version2\00", align 1
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
@global_string.86 = private constant [6 x i8] c"i %d\0A\00", align 1
@global_string.87 = private constant [6 x i8] c"i %d\0A\00", align 1
@global_string.88 = private constant [6 x i8] c"i %d\0A\00", align 1
@global_string.89 = private constant [7 x i8] c"1 or 2\00", align 1
@global_string.90 = private constant [2 x i8] c"3\00", align 1
@global_string.91 = private constant [8 x i8] c"default\00", align 1
@global_string.92 = private constant [30 x i8] c"global array initializer test\00", align 1
@global_string.93 = private constant [23 x i8] c"array initializer test\00", align 1
@global_string.94 = private constant [29 x i8] c"local array initializer test\00", align 1
@global_string.95 = private constant [4 x i8] c"AAA\00", align 1
@global_string.96 = private constant [4 x i8] c"BBB\00", align 1
@global_string.97 = private constant [4 x i8] c"AAA\00", align 1
@global_string.98 = private constant [4 x i8] c"BBB\00", align 1
@global_string.99 = private constant [37 x i8] c"local cstring array initializer test\00", align 1

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
  %94 = getelementptr inbounds [3 x [3 x i32]], [3 x [3 x i32]]* %array4, i32 0, i32 1
  %95 = getelementptr inbounds [3 x i32], [3 x i32]* %94, i32 0, i32 2
  store i32 123, i32* %95, align 4
  %array4161 = load [3 x [3 x i32]], [3 x [3 x i32]]* %array4, align 4
  %96 = getelementptr inbounds [3 x [3 x i32]], [3 x [3 x i32]]* %array4, i32 0, i32 1
  %97 = getelementptr inbounds [3 x i32], [3 x i32]* %96, i32 0, i32 2
  %element162 = load i32, i32* %97, align 4
  %eqtmpX163 = icmp eq i32 %element162, 123
  call void @xassert(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.71, i32 0, i32 0), i1 %eqtmpX163)
  %array5 = alloca [10 x [100 x i8]]
  %98 = bitcast [10 x [100 x i8]]* %array5 to i8*
  store i8* %98, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 24), align 8
  %array5164 = load [10 x [100 x i8]], [10 x [100 x i8]]* %array5, align 1
  %99 = getelementptr inbounds [10 x [100 x i8]], [10 x [100 x i8]]* %array5, i32 0, i32 0
  %100 = getelementptr inbounds [100 x i8], [100 x i8]* %99, i32 0, i32 0
  %101 = call i8* @strcpy(i8* %100, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.72, i32 0, i32 0))
  %array5165 = load [10 x [100 x i8]], [10 x [100 x i8]]* %array5, align 1
  %102 = getelementptr inbounds [10 x [100 x i8]], [10 x [100 x i8]]* %array5, i32 0, i32 1
  %103 = getelementptr inbounds [100 x i8], [100 x i8]* %102, i32 0, i32 0
  %104 = call i8* @strcpy(i8* %103, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.73, i32 0, i32 0))
  %array5166 = load [10 x [100 x i8]], [10 x [100 x i8]]* %array5, align 1
  %105 = getelementptr inbounds [10 x [100 x i8]], [10 x [100 x i8]]* %array5, i32 0, i32 0
  %106 = getelementptr inbounds [100 x i8], [100 x i8]* %105, i32 0, i32 0
  %107 = call i32 @strcmp(i8* %106, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.74, i32 0, i32 0))
  %eqtmpX167 = icmp eq i32 %107, 0
  store i1 %eqtmpX167, i1* %andand_result_var, align 1
  br i1 %eqtmpX167, label %cond_jump_then168, label %cond_jump_end169

cond_jump_then168:                                ; preds = %cond_jump_end142
  %array5170 = load [10 x [100 x i8]], [10 x [100 x i8]]* %array5, align 1
  %108 = getelementptr inbounds [10 x [100 x i8]], [10 x [100 x i8]]* %array5, i32 0, i32 1
  %109 = getelementptr inbounds [100 x i8], [100 x i8]* %108, i32 0, i32 0
  %110 = call i32 @strcmp(i8* %109, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.75, i32 0, i32 0))
  %eqtmpX171 = icmp eq i32 %110, 0
  %andand172 = and i1 %eqtmpX167, %eqtmpX171
  store i1 %andand172, i1* %andand_result_var, align 1
  br label %cond_jump_end169

cond_jump_end169:                                 ; preds = %cond_jump_then168, %cond_jump_end142
  %andand_result_value173 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.76, i32 0, i32 0), i1 %andand_result_value173)
  %gArray = load [3 x i32], [3 x i32]* @gArray, align 4
  %element174 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @gArray, i32 0, i32 0), align 4
  %eqtmpX175 = icmp eq i32 %element174, 1
  store i1 %eqtmpX175, i1* %andand_result_var, align 1
  br i1 %eqtmpX175, label %cond_jump_then176, label %cond_jump_end177

cond_jump_then176:                                ; preds = %cond_jump_end169
  %gArray178 = load [3 x i32], [3 x i32]* @gArray, align 4
  %element179 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @gArray, i32 0, i32 1), align 4
  %eqtmpX180 = icmp eq i32 %element179, 2
  %andand181 = and i1 %eqtmpX175, %eqtmpX180
  store i1 %andand181, i1* %andand_result_var, align 1
  br label %cond_jump_end177

cond_jump_end177:                                 ; preds = %cond_jump_then176, %cond_jump_end169
  %andand_result_value182 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value182, i1* %andand_result_var, align 1
  br i1 %andand_result_value182, label %cond_jump_then183, label %cond_jump_end184

cond_jump_then183:                                ; preds = %cond_jump_end177
  %gArray185 = load [3 x i32], [3 x i32]* @gArray, align 4
  %element186 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @gArray, i32 0, i32 2), align 4
  %eqtmpX187 = icmp eq i32 %element186, 3
  %andand188 = and i1 %andand_result_value182, %eqtmpX187
  store i1 %andand188, i1* %andand_result_var, align 1
  br label %cond_jump_end184

cond_jump_end184:                                 ; preds = %cond_jump_then183, %cond_jump_end177
  %andand_result_value189 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @global_string.77, i32 0, i32 0), i1 %andand_result_value189)
  %array6 = alloca [3 x i32]
  %111 = bitcast [3 x i32]* %array6 to i8*
  store i8* %111, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 25), align 8
  %112 = load [3 x i32], [3 x i32]* %array6, align 4
  %113 = bitcast [3 x i32]* %array6 to i32*
  %element_address190 = getelementptr i32, i32* %113, i64 0
  store i32 1, i32* %element_address190, align 8
  %element_address191 = getelementptr i32, i32* %113, i64 1
  store i32 2, i32* %element_address191, align 8
  %element_address192 = getelementptr i32, i32* %113, i64 2
  store i32 3, i32* %element_address192, align 8
  %array6193 = load [3 x i32], [3 x i32]* %array6, align 4
  %114 = bitcast [3 x i32]* %array6 to i32*
  %element_address194 = getelementptr i32, i32* %114, i32 0
  %element195 = load i32, i32* %element_address194, align 4
  %eqtmpX196 = icmp eq i32 %element195, 1
  store i1 %eqtmpX196, i1* %andand_result_var, align 1
  br i1 %eqtmpX196, label %cond_jump_then197, label %cond_jump_end198

cond_jump_then197:                                ; preds = %cond_jump_end184
  %array6199 = load [3 x i32], [3 x i32]* %array6, align 4
  %115 = bitcast [3 x i32]* %array6 to i32*
  %element_address200 = getelementptr i32, i32* %115, i32 1
  %element201 = load i32, i32* %element_address200, align 4
  %eqtmpX202 = icmp eq i32 %element201, 2
  %andand203 = and i1 %eqtmpX196, %eqtmpX202
  store i1 %andand203, i1* %andand_result_var, align 1
  br label %cond_jump_end198

cond_jump_end198:                                 ; preds = %cond_jump_then197, %cond_jump_end184
  %andand_result_value204 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value204, i1* %andand_result_var, align 1
  br i1 %andand_result_value204, label %cond_jump_then205, label %cond_jump_end206

cond_jump_then205:                                ; preds = %cond_jump_end198
  %array6207 = load [3 x i32], [3 x i32]* %array6, align 4
  %116 = bitcast [3 x i32]* %array6 to i32*
  %element_address208 = getelementptr i32, i32* %116, i32 2
  %element209 = load i32, i32* %element_address208, align 4
  %eqtmpX210 = icmp eq i32 %element209, 3
  %andand211 = and i1 %andand_result_value204, %eqtmpX210
  store i1 %andand211, i1* %andand_result_var, align 1
  br label %cond_jump_end206

cond_jump_end206:                                 ; preds = %cond_jump_then205, %cond_jump_end198
  %andand_result_value212 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @global_string.78, i32 0, i32 0), i1 %andand_result_value212)
  %array7 = alloca [3 x i8]
  %117 = bitcast [3 x i8]* %array7 to i8*
  store i8* %117, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 26), align 8
  %118 = load [3 x i8], [3 x i8]* %array7, align 1
  %119 = bitcast [3 x i8]* %array7 to i8*
  %element_address213 = getelementptr i8, i8* %119, i64 0
  store i8 65, i8* %element_address213, align 8
  %element_address214 = getelementptr i8, i8* %119, i64 1
  store i8 66, i8* %element_address214, align 8
  %element_address215 = getelementptr i8, i8* %119, i64 2
  store i8 0, i8* %element_address215, align 8
  %array7216 = load [3 x i8], [3 x i8]* %array7, align 1
  %120 = bitcast [3 x i8]* %array7 to i8*
  %121 = call i32 @strcmp(i8* %120, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @global_string.79, i32 0, i32 0))
  %eqtmpX217 = icmp eq i32 %121, 0
  call void @xassert(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @global_string.80, i32 0, i32 0), i1 %eqtmpX217)
  %gArray2 = load [3 x i8], [3 x i8]* @gArray2, align 1
  %122 = call i32 @strcmp(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @gArray2, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @global_string.81, i32 0, i32 0))
  %eqtmpX218 = icmp eq i32 %122, 0
  call void @xassert(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @global_string.82, i32 0, i32 0), i1 %eqtmpX218)
  %gArray3 = load [3 x i32], [3 x i32]* @gArray3, align 4
  %element219 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @gArray3, i32 0, i32 0), align 4
  %eqtmpX220 = icmp eq i32 %element219, 1
  store i1 %eqtmpX220, i1* %andand_result_var, align 1
  br i1 %eqtmpX220, label %cond_jump_then221, label %cond_jump_end222

cond_jump_then221:                                ; preds = %cond_jump_end206
  %gArray3223 = load [3 x i32], [3 x i32]* @gArray3, align 4
  %element224 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @gArray3, i32 0, i32 1), align 4
  %eqtmpX225 = icmp eq i32 %element224, 2
  %andand226 = and i1 %eqtmpX220, %eqtmpX225
  store i1 %andand226, i1* %andand_result_var, align 1
  br label %cond_jump_end222

cond_jump_end222:                                 ; preds = %cond_jump_then221, %cond_jump_end206
  %andand_result_value227 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value227, i1* %andand_result_var, align 1
  br i1 %andand_result_value227, label %cond_jump_then228, label %cond_jump_end229

cond_jump_then228:                                ; preds = %cond_jump_end222
  %gArray3230 = load [3 x i32], [3 x i32]* @gArray3, align 4
  %element231 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @gArray3, i32 0, i32 2), align 4
  %eqtmpX232 = icmp eq i32 %element231, 3
  %andand233 = and i1 %andand_result_value227, %eqtmpX232
  store i1 %andand233, i1* %andand_result_var, align 1
  br label %cond_jump_end229

cond_jump_end229:                                 ; preds = %cond_jump_then228, %cond_jump_end222
  %andand_result_value234 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @global_string.83, i32 0, i32 0), i1 %andand_result_value234)
  %array8 = alloca [3 x i32]
  %123 = bitcast [3 x i32]* %array8 to i8*
  store i8* %123, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 27), align 8
  %124 = load [3 x i32], [3 x i32]* %array8, align 4
  %125 = bitcast [3 x i32]* %array8 to i32*
  %element_address235 = getelementptr i32, i32* %125, i64 0
  store i32 1, i32* %element_address235, align 8
  %element_address236 = getelementptr i32, i32* %125, i64 1
  store i32 2, i32* %element_address236, align 8
  %element_address237 = getelementptr i32, i32* %125, i64 2
  store i32 3, i32* %element_address237, align 8
  %array8238 = load [3 x i32], [3 x i32]* %array8, align 4
  %126 = bitcast [3 x i32]* %array8 to i32*
  %element_address239 = getelementptr i32, i32* %126, i32 0
  %element240 = load i32, i32* %element_address239, align 4
  %eqtmpX241 = icmp eq i32 %element240, 1
  store i1 %eqtmpX241, i1* %andand_result_var, align 1
  br i1 %eqtmpX241, label %cond_jump_then242, label %cond_jump_end243

cond_jump_then242:                                ; preds = %cond_jump_end229
  %array8244 = load [3 x i32], [3 x i32]* %array8, align 4
  %127 = bitcast [3 x i32]* %array8 to i32*
  %element_address245 = getelementptr i32, i32* %127, i32 1
  %element246 = load i32, i32* %element_address245, align 4
  %eqtmpX247 = icmp eq i32 %element246, 2
  %andand248 = and i1 %eqtmpX241, %eqtmpX247
  store i1 %andand248, i1* %andand_result_var, align 1
  br label %cond_jump_end243

cond_jump_end243:                                 ; preds = %cond_jump_then242, %cond_jump_end229
  %andand_result_value249 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value249, i1* %andand_result_var, align 1
  br i1 %andand_result_value249, label %cond_jump_then250, label %cond_jump_end251

cond_jump_then250:                                ; preds = %cond_jump_end243
  %array8252 = load [3 x i32], [3 x i32]* %array8, align 4
  %128 = bitcast [3 x i32]* %array8 to i32*
  %element_address253 = getelementptr i32, i32* %128, i32 2
  %element254 = load i32, i32* %element_address253, align 4
  %eqtmpX255 = icmp eq i32 %element254, 3
  %andand256 = and i1 %andand_result_value249, %eqtmpX255
  store i1 %andand256, i1* %andand_result_var, align 1
  br label %cond_jump_end251

cond_jump_end251:                                 ; preds = %cond_jump_then250, %cond_jump_end243
  %andand_result_value257 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @global_string.84, i32 0, i32 0), i1 %andand_result_value257)
  %ccc = alloca i8
  store i8* %ccc, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 28), align 8
  store i8 10, i8* %ccc, align 1
  %ccc2 = alloca i8
  store i8* %ccc2, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 29), align 8
  store i8 97, i8* %ccc2, align 1
  %ccc3 = alloca i8
  store i8* %ccc3, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 30), align 8
  store i8 0, i8* %ccc3, align 1
  %ccc258 = load i8, i8* %ccc, align 1
  %eqtmpX259 = icmp eq i8 %ccc258, 10
  store i1 %eqtmpX259, i1* %andand_result_var, align 1
  br i1 %eqtmpX259, label %cond_jump_then260, label %cond_jump_end261

cond_jump_then260:                                ; preds = %cond_jump_end251
  %ccc2262 = load i8, i8* %ccc2, align 1
  %eqtmpX263 = icmp eq i8 %ccc2262, 97
  %andand264 = and i1 %eqtmpX259, %eqtmpX263
  store i1 %andand264, i1* %andand_result_var, align 1
  br label %cond_jump_end261

cond_jump_end261:                                 ; preds = %cond_jump_then260, %cond_jump_end251
  %andand_result_value265 = load i1, i1* %andand_result_var, align 1
  store i1 %andand_result_value265, i1* %andand_result_var, align 1
  br i1 %andand_result_value265, label %cond_jump_then266, label %cond_jump_end267

cond_jump_then266:                                ; preds = %cond_jump_end261
  %ccc3268 = load i8, i8* %ccc3, align 1
  %eqtmpX269 = icmp eq i8 %ccc3268, 0
  %andand270 = and i1 %andand_result_value265, %eqtmpX269
  store i1 %andand270, i1* %andand_result_var, align 1
  br label %cond_jump_end267

cond_jump_end267:                                 ; preds = %cond_jump_then266, %cond_jump_end261
  %andand_result_value271 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @global_string.85, i32 0, i32 0), i1 %andand_result_value271)
  %i = alloca i32
  %129 = bitcast i32* %i to i8*
  store i8* %129, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 31), align 8
  store i32 0, i32* %i, align 4
  br label %loop_top_block

loop_top_block:                                   ; preds = %cond_then_block273, %cond_jump_end267
  %i272 = load i32, i32* %i, align 4
  %letmp = icmp slt i32 %i272, 3
  br i1 %letmp, label %cond_then_block273, label %cond_end_block

cond_then_block273:                               ; preds = %loop_top_block
  %130 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 31), align 8
  %131 = bitcast i8* %130 to i32*
  %i274 = load i32, i32* %131, align 4
  %132 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @global_string.86, i32 0, i32 0), i32 %i274)
  %i275 = load i32, i32* %i, align 4
  %addtmp276 = add nsw i32 %i275, 1
  store i32 %addtmp276, i32* %i, align 4
  %subttmp277 = sub nsw i32 %addtmp276, 1
  br label %loop_top_block

cond_end_block:                                   ; preds = %loop_top_block
  %i278 = alloca i32
  %133 = bitcast i32* %i278 to i8*
  store i8* %133, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 31), align 8
  store i32 0, i32* %i278, align 4
  br label %loop_top_block279

loop_top_block279:                                ; preds = %cond_then_block282, %cond_end_block
  %i280 = load i32, i32* %i278, align 4
  %letmp281 = icmp slt i32 %i280, 3
  br i1 %letmp281, label %cond_then_block282, label %cond_end_block283

cond_then_block282:                               ; preds = %loop_top_block279
  %134 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 31), align 8
  %135 = bitcast i8* %134 to i32*
  %i284 = load i32, i32* %135, align 4
  %136 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @global_string.87, i32 0, i32 0), i32 %i284)
  %137 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 31), align 8
  %138 = bitcast i8* %137 to i32*
  %i285 = load i32, i32* %138, align 4
  %addtmp286 = add nsw i32 %i285, 1
  %139 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 31), align 8
  %140 = bitcast i8* %139 to i32*
  store i32 %addtmp286, i32* %140, align 4
  %subttmp287 = sub nsw i32 %addtmp286, 1
  br label %loop_top_block279

cond_end_block283:                                ; preds = %loop_top_block279
  store i32 0, i32* %i278, align 4
  br label %loop_top_block288

loop_top_block288:                                ; preds = %loop_top_block288, %cond_end_block283
  %141 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 31), align 8
  %142 = bitcast i8* %141 to i32*
  %i290 = load i32, i32* %142, align 4
  %143 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @global_string.88, i32 0, i32 0), i32 %i290)
  %144 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 31), align 8
  %145 = bitcast i8* %144 to i32*
  %i291 = load i32, i32* %145, align 4
  %addtmp292 = add nsw i32 %i291, 1
  %146 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 31), align 8
  %147 = bitcast i8* %146 to i32*
  store i32 %addtmp292, i32* %147, align 4
  %subttmp293 = sub nsw i32 %addtmp292, 1
  %i294 = load i32, i32* %i278, align 4
  %letmp295 = icmp slt i32 %i294, 3
  br i1 %letmp295, label %loop_top_block288, label %cond_end_block289

cond_end_block289:                                ; preds = %loop_top_block288
  br i1 false, label %cond_then_block296, label %cond_else_block

end_block:                                        ; preds = %cond_else_block302, %cond_then_block301, %cond_then_block298, %cond_then_block296
  %gArray4 = load [3 x [3 x [3 x i32]]], [3 x [3 x [3 x i32]]]* @gArray4, align 4
  %element304 = load i32, i32* getelementptr inbounds ([3 x [3 x [3 x i32]]], [3 x [3 x [3 x i32]]]* @gArray4, i32 0, i32 0, i32 1, i32 2), align 4
  %aaaaaa = alloca i32
  %148 = bitcast i32* %aaaaaa to i8*
  store i8* %148, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 32), align 8
  store i32 %element304, i32* %aaaaaa, align 4
  %aaaaaa305 = load i32, i32* %aaaaaa, align 4
  %eqtmpX306 = icmp eq i32 %aaaaaa305, 4
  call void @xassert(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @global_string.92, i32 0, i32 0), i1 %eqtmpX306)
  %gArray4307 = load [3 x [3 x [3 x i32]]], [3 x [3 x [3 x i32]]]* @gArray4, align 4
  %element308 = load i32, i32* getelementptr inbounds ([3 x [3 x [3 x i32]]], [3 x [3 x [3 x i32]]]* @gArray4, i32 0, i32 1, i32 1, i32 1), align 4
  %eqtmpX309 = icmp eq i32 %element308, 2
  store i1 %eqtmpX309, i1* %andand_result_var, align 1
  br i1 %eqtmpX309, label %cond_jump_then310, label %cond_jump_end311

cond_then_block296:                               ; preds = %cond_else_block, %cond_end_block289
  %149 = call i32 @puts(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @global_string.89, i32 0, i32 0))
  br label %end_block

cond_else_block:                                  ; preds = %cond_end_block289
  br i1 true, label %cond_then_block296, label %cond_else_block297

cond_else_block297:                               ; preds = %after_break, %cond_else_block
  br i1 false, label %cond_then_block298, label %cond_else_block299

after_break:                                      ; No predecessors!
  br label %cond_else_block297

cond_then_block298:                               ; preds = %cond_else_block297
  %150 = call i32 @puts(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @global_string.90, i32 0, i32 0))
  br label %end_block

cond_else_block299:                               ; preds = %after_break300, %cond_else_block297
  br label %cond_then_block301

after_break300:                                   ; No predecessors!
  br label %cond_else_block299

cond_then_block301:                               ; preds = %cond_else_block299
  %151 = call i32 @puts(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @global_string.91, i32 0, i32 0))
  br label %end_block

cond_else_block302:                               ; preds = %after_break303
  br label %end_block

after_break303:                                   ; No predecessors!
  br label %cond_else_block302

cond_jump_then310:                                ; preds = %end_block
  %gArray4312 = load [3 x [3 x [3 x i32]]], [3 x [3 x [3 x i32]]]* @gArray4, align 4
  %element313 = load i32, i32* getelementptr inbounds ([3 x [3 x [3 x i32]]], [3 x [3 x [3 x i32]]]* @gArray4, i32 0, i32 2, i32 0, i32 1), align 4
  %eqtmpX314 = icmp eq i32 %element313, 12
  %andand315 = and i1 %eqtmpX309, %eqtmpX314
  store i1 %andand315, i1* %andand_result_var, align 1
  br label %cond_jump_end311

cond_jump_end311:                                 ; preds = %cond_jump_then310, %end_block
  %andand_result_value316 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @global_string.93, i32 0, i32 0), i1 %andand_result_value316)
  %ay = alloca [2 x [2 x [3 x i32]]]
  %152 = bitcast [2 x [2 x [3 x i32]]]* %ay to i8*
  store i8* %152, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 33), align 8
  %153 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %154 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %153, i32 0, i32 0
  %155 = getelementptr inbounds [3 x i32], [3 x i32]* %154, i32 0, i32 0
  store i32 1, i32* %155, align 4
  %156 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %157 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %156, i32 0, i32 0
  %158 = getelementptr inbounds [3 x i32], [3 x i32]* %157, i32 0, i32 1
  store i32 2, i32* %158, align 4
  %159 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %160 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %159, i32 0, i32 0
  %161 = getelementptr inbounds [3 x i32], [3 x i32]* %160, i32 0, i32 2
  store i32 3, i32* %161, align 4
  %162 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %163 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %162, i32 0, i32 1
  %164 = getelementptr inbounds [3 x i32], [3 x i32]* %163, i32 0, i32 0
  store i32 4, i32* %164, align 4
  %165 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %166 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %165, i32 0, i32 1
  %167 = getelementptr inbounds [3 x i32], [3 x i32]* %166, i32 0, i32 1
  store i32 5, i32* %167, align 4
  %168 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %169 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %168, i32 0, i32 1
  %170 = getelementptr inbounds [3 x i32], [3 x i32]* %169, i32 0, i32 2
  store i32 6, i32* %170, align 4
  %171 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %172 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %171, i32 0, i32 0
  %173 = getelementptr inbounds [3 x i32], [3 x i32]* %172, i32 0, i32 0
  store i32 7, i32* %173, align 4
  %174 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %175 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %174, i32 0, i32 0
  %176 = getelementptr inbounds [3 x i32], [3 x i32]* %175, i32 0, i32 1
  store i32 8, i32* %176, align 4
  %177 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %178 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %177, i32 0, i32 0
  %179 = getelementptr inbounds [3 x i32], [3 x i32]* %178, i32 0, i32 2
  store i32 9, i32* %179, align 4
  %180 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %181 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %180, i32 0, i32 1
  %182 = getelementptr inbounds [3 x i32], [3 x i32]* %181, i32 0, i32 0
  store i32 11, i32* %182, align 4
  %183 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %184 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %183, i32 0, i32 1
  %185 = getelementptr inbounds [3 x i32], [3 x i32]* %184, i32 0, i32 1
  store i32 12, i32* %185, align 4
  %186 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 1
  %187 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %186, i32 0, i32 1
  %188 = getelementptr inbounds [3 x i32], [3 x i32]* %187, i32 0, i32 2
  store i32 13, i32* %188, align 4
  %ay317 = load [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, align 4
  %189 = getelementptr inbounds [2 x [2 x [3 x i32]]], [2 x [2 x [3 x i32]]]* %ay, i32 0, i32 0
  %190 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %189, i32 0, i32 1
  %191 = getelementptr inbounds [3 x i32], [3 x i32]* %190, i32 0, i32 2
  %element318 = load i32, i32* %191, align 4
  %eqtmpX319 = icmp eq i32 %element318, 6
  call void @xassert(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @global_string.94, i32 0, i32 0), i1 %eqtmpX319)
  %aa = alloca [2 x i8*]
  %192 = bitcast [2 x i8*]* %aa to i8*
  store i8* %192, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable21, i32 0, i32 34), align 8
  %193 = load [2 x i8*], [2 x i8*]* %aa, align 8
  %194 = bitcast [2 x i8*]* %aa to i8**
  %element_address320 = getelementptr i8*, i8** %194, i64 0
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.95, i32 0, i32 0), i8** %element_address320, align 8
  %element_address321 = getelementptr i8*, i8** %194, i64 1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.96, i32 0, i32 0), i8** %element_address321, align 8
  %aa322 = load [2 x i8*], [2 x i8*]* %aa, align 8
  %195 = bitcast [2 x i8*]* %aa to i8**
  %element_address323 = getelementptr i8*, i8** %195, i32 0
  %element324 = load i8*, i8** %element_address323, align 8
  %196 = call i32 @strcmp(i8* %element324, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.97, i32 0, i32 0))
  %eqtmpX325 = icmp eq i32 %196, 0
  store i1 %eqtmpX325, i1* %andand_result_var, align 1
  br i1 %eqtmpX325, label %cond_jump_then326, label %cond_jump_end327

cond_jump_then326:                                ; preds = %cond_jump_end311
  %aa328 = load [2 x i8*], [2 x i8*]* %aa, align 8
  %197 = bitcast [2 x i8*]* %aa to i8**
  %element_address329 = getelementptr i8*, i8** %197, i32 1
  %element330 = load i8*, i8** %element_address329, align 8
  %198 = call i32 @strcmp(i8* %element330, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.98, i32 0, i32 0))
  %eqtmpX331 = icmp eq i32 %198, 0
  %andand332 = and i1 %eqtmpX325, %eqtmpX331
  store i1 %andand332, i1* %andand_result_var, align 1
  br label %cond_jump_end327

cond_jump_end327:                                 ; preds = %cond_jump_then326, %cond_jump_end311
  %andand_result_value333 = load i1, i1* %andand_result_var, align 1
  call void @xassert(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @global_string.99, i32 0, i32 0), i1 %andand_result_value333)
  %199 = load %Data3*, %Data3** %data3_2, align 8
  %200 = ptrtoint %Data3* %199 to i64
  %201 = icmp ne i64 %200, 0
  br i1 %201, label %cond_then_block334, label %cond_end335

cond_then_block334:                               ; preds = %cond_jump_end327
  br label %cond_end335

cond_end335:                                      ; preds = %cond_then_block334, %cond_jump_end327
  %202 = bitcast %Data3* %199 to i8*
  call void @free(i8* %202)
  %203 = load i8*, i8** %b, align 8
  %204 = ptrtoint i8* %203 to i64
  %205 = icmp ne i64 %204, 0
  br i1 %205, label %cond_then_block336, label %cond_end337

cond_then_block336:                               ; preds = %cond_end335
  br label %cond_end337

cond_end337:                                      ; preds = %cond_then_block336, %cond_end335
  call void @free(i8* %203)
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
  %3 = call i32 @puts(i8* getelementptr inbounds ([32 x i8], [32 x i8]* @global_string.33, i32 0, i32 0))
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
  %1 = call i32 @puts(i8* getelementptr inbounds ([32 x i8], [32 x i8]* @global_string.29, i32 0, i32 0))
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
