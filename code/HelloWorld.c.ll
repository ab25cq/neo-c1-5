; ModuleID = 'Module stdin'
source_filename = "Module stdin"

@gLVTable = internal global [8192 x i8*] zeroinitializer, align 8
@global_string = private constant [12 x i8] c"HELLO WORLD\00", align 1

declare i32 @puts(i8*)

declare i32 @exit(i32)

define i32 @main() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %0 = call i32 @puts(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string, i32 0, i32 0))
  ret i32 0
}
