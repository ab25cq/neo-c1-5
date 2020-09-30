; ModuleID = 'Module stdin'
source_filename = "Module stdin"

@gLVTable = internal global [8192 x i8*] zeroinitializer, align 8
@global_string = private constant [12 x i8] c"HELLO WORLD\00", align 1
@global_string.1 = private constant [6 x i8] c"if ok\00", align 1
@global_string.2 = private constant [12 x i8] c"else if ok1\00", align 1
@global_string.3 = private constant [12 x i8] c"else if ok2\00", align 1
@global_string.4 = private constant [5 x i8] c"else\00", align 1

declare i32 @puts(i8*)

declare i32 @exit(i32)

define i32 @main() {
entry:
  %andand_result_var = alloca i1
  %andand_result_var1 = alloca i1
  %0 = call i32 @puts(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string, i32 0, i32 0))
  br i1 false, label %cond_jump_then, label %"cond_jump_elif0\0A"

cond_jump_then:                                   ; preds = %entry
  %1 = call i32 @puts(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @global_string.1, i32 0, i32 0))
  br label %cond_end

"cond_jump_elif0\0A":                             ; preds = %entry
  br i1 false, label %"cond_jump_elif_then0\0A", label %"cond_jump_elif1\0A"

"cond_jump_elif_then0\0A":                        ; preds = %"cond_jump_elif0\0A"
  %2 = call i32 @puts(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.2, i32 0, i32 0))
  br label %cond_end

"cond_jump_elif1\0A":                             ; preds = %"cond_jump_elif0\0A"
  br i1 false, label %"cond_jump_elif_then1\0A", label %cond_else_block

"cond_jump_elif_then1\0A":                        ; preds = %"cond_jump_elif1\0A"
  %3 = call i32 @puts(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.3, i32 0, i32 0))
  br label %cond_end

cond_else_block:                                  ; preds = %"cond_jump_elif1\0A"
  %4 = call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @global_string.4, i32 0, i32 0))
  br label %cond_end

cond_end:                                         ; preds = %cond_else_block, %"cond_jump_elif_then1\0A", %"cond_jump_elif_then0\0A", %cond_jump_then
  ret i32 0
}
