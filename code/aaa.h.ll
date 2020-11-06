; ModuleID = 'Module code/HelloWorld.c.pp'
source_filename = "Module code/HelloWorld.c.pp"

%anonmous_struct0 = type { i32, i32 }

@data = global %anonmous_struct0 zeroinitializer, align 8

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Debug Info Version", i32 3}
!1 = !{i32 2, !"Dwarf Version", i32 2}
!2 = distinct !DICompileUnit(language: DW_LANG_C, file: !3, producer: "neo-c2", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4)
!3 = !DIFile(filename: "code/HelloWorld.c", directory: "/data/data/com.termux/files/home/repo/neo-c2")
!4 = !{}
