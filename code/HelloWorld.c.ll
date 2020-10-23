; ModuleID = 'Module stdin'
source_filename = "Module stdin"

@gLVTable0 = internal global [512 x i8*] zeroinitializer, align 8
@global_string = private constant [7 x i8] c"1 or 2\00", align 1
@global_string.2 = private constant [2 x i8] c"3\00", align 1
@global_string.3 = private constant [8 x i8] c"default\00", align 1
@global_string.4 = private constant [6 x i8] c"i %d\0A\00", align 1
@global_string.5 = private constant [4 x i8] c"AAA\00", align 1

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
  %i = alloca i32
  %0 = bitcast i32* %i to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable0, i32 0, i32 0), align 8
  store i32 0, i32* %i, align 4
  br label %loop_top_block

cond_then_block:                                  ; preds = %cond_else_block, %entry
  %1 = call i32 @puts(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @global_string, i32 0, i32 0))
  br label %end_block

cond_else_block:                                  ; preds = %entry
  br i1 true, label %cond_then_block, label %cond_else_block2

cond_else_block2:                                 ; preds = %after_break, %cond_else_block
  br i1 false, label %cond_then_block3, label %cond_else_block4

after_break:                                      ; No predecessors!
  br label %cond_else_block2

cond_then_block3:                                 ; preds = %cond_else_block2
  %2 = call i32 @puts(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @global_string.2, i32 0, i32 0))
  br label %end_block

cond_else_block4:                                 ; preds = %after_break5, %cond_else_block2
  br label %cond_then_block6

after_break5:                                     ; No predecessors!
  br label %cond_else_block4

cond_then_block6:                                 ; preds = %cond_else_block4
  %3 = call i32 @puts(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @global_string.3, i32 0, i32 0))
  br label %end_block

cond_else_block7:                                 ; preds = %after_break8
  br label %end_block

after_break8:                                     ; No predecessors!
  br label %cond_else_block7

loop_top_block:                                   ; preds = %cond_end, %end_block
  %i9 = load i32, i32* %i, align 4
  %letmp = icmp slt i32 %i9, 3
  br i1 %letmp, label %cond_then_block10, label %cond_end_block

cond_then_block10:                                ; preds = %loop_top_block
  %4 = load i8*, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable0, i32 0, i32 0), align 8
  %5 = bitcast i8* %4 to i32*
  %i11 = load i32, i32* %5, align 4
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @global_string.4, i32 0, i32 0), i32 %i11)
  br i1 true, label %cond_jump_then, label %cond_end

cond_end_block:                                   ; preds = %loop_top_block
  ret i32 0

cond_jump_then:                                   ; preds = %cond_then_block10
  %7 = call i32 @puts(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.5, i32 0, i32 0))
  br label %cond_end

cond_end:                                         ; preds = %cond_jump_then, %cond_then_block10
  %i12 = load i32, i32* %i, align 4
  %addtmp = add nsw i32 %i12, 1
  store i32 %addtmp, i32* %i, align 4
  %subttmp = sub nsw i32 %addtmp, 1
  br label %loop_top_block
}
