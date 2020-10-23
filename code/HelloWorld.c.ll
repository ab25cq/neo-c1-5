; ModuleID = 'Module stdin'
source_filename = "Module stdin"

@gLVTable0 = internal global [512 x i8*] zeroinitializer, align 8
@global_string = private constant [7 x i8] c"1 or 2\00", align 1
@global_string.2 = private constant [2 x i8] c"3\00", align 1
@global_string.3 = private constant [8 x i8] c"default\00", align 1

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
  br i1 false, label %cond_then_block, label %cond_else_block

end_block:                                        ; preds = %cond_else_block7, %cond_then_block6, %cond_then_block3, %cond_then_block
  ret i32 0

cond_then_block:                                  ; preds = %cond_else_block, %entry
  %0 = call i32 @puts(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @global_string, i32 0, i32 0))
  br label %end_block

cond_else_block:                                  ; preds = %entry
  br i1 false, label %cond_then_block, label %cond_else_block2

cond_else_block2:                                 ; preds = %after_break, %cond_else_block
  br i1 false, label %cond_then_block3, label %cond_else_block4

after_break:                                      ; No predecessors!
  br label %cond_else_block2

cond_then_block3:                                 ; preds = %cond_else_block2
  %1 = call i32 @puts(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @global_string.2, i32 0, i32 0))
  br label %end_block

cond_else_block4:                                 ; preds = %after_break5, %cond_else_block2
  br label %cond_then_block6

after_break5:                                     ; No predecessors!
  br label %cond_else_block4

cond_then_block6:                                 ; preds = %cond_else_block4
  %2 = call i32 @puts(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @global_string.3, i32 0, i32 0))
  br label %end_block

cond_else_block7:                                 ; preds = %after_break8
  br label %end_block

after_break8:                                     ; No predecessors!
  br label %cond_else_block7
}
