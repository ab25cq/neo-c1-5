; ModuleID = 'Module stdin'
source_filename = "Module stdin"

@gLVTable = internal global [8192 x i8*] zeroinitializer, align 8

declare i32 @puts(i8*)

declare i32 @exit(i32)
