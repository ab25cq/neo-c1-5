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

declare i32 @puts(i8*)

declare i32 @exit(i32)

declare i32 @printf(i8*, ...)

declare i8* @calloc(i64, i64)

declare void @free(i8*)

declare i32 @atoi(i8*)

declare i32 @atoi.1(i8*)

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
  %55 = load i8*, i8** %b, align 8
  %56 = ptrtoint i8* %55 to i64
  %57 = icmp ne i64 %56, 0
  br i1 %57, label %cond_then_block78, label %cond_end79

cond_then_block78:                                ; preds = %cond_jump_end73
  br label %cond_end79

cond_end79:                                       ; preds = %cond_then_block78, %cond_jump_end73
  call void @free(i8* %55)
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
