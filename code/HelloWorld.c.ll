; ModuleID = 'Module stdin'
source_filename = "Module stdin"

@gLVTable = internal global [8192 x i8*] zeroinitializer, align 8

define i32 @main() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %a = alloca i32
  %0 = bitcast i32* %a to i8*
  store i8* %0, i8** getelementptr (i8*, i8** getelementptr inbounds ([8192 x i8*], [8192 x i8*]* @gLVTable, i32 0, i32 0), i32 -1), align 8
  store i32 2, i32* %a, align 4
  %a2 = load i32, i32* %a, align 4
  ret i32 %a2
}
