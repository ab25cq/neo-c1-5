# 1 "code/HelloWorld"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4

# 1 "/usr/include/stdc-predef.h" 3 4
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */




/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */

/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
# 52 "/usr/include/stdc-predef.h" 3 4
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
# 32 "<command-line>" 2
# 1 "code/HelloWorld"

# 1 "code/HelloWorld"
ELF  >  �@ @ `F @ 8 @ % $   @ @ @ @ @ h h    � �@ �@      @ @ H H     @ @ m m    @ @ H H    . >@ >@ p ��    . >@ >@ � �    � �@ �@ D D  P�td � � @ � @ � �  Q�td  R�td . >@ >@    /lib64/ld-1 -x86-64.so.2    GNU      GNU ���g)N�\.�Q)��]V�
                 
       V     *    D  #  =  g 8  1    libc.so.6 strcpy exit puts printf calloc strlen strcat atoi strcmp __libc_start_main free GLIBC_2.2.5 __gmon_start__                ui  [ �?@   �?@  @@   @@   (@@   0@@   8@@   @@@   H@@  P@@  H��H��/ H��t��H��� �5�/ �%�/ @ �%�/ h ������%�/ h ������%�/ h ������%�/ h �����%�/ h �����%�/ h �����%�/ h �����%�/ h �p���1�I��^H��H���PTI��`@ H�� @ H��p@ �/ �D �f.� D �p@@ H=p@@ t� H��t �p@@ ��f��ff.� @ �p@@ H��p@@ H��H��H��?H�H��t� H��t�p@@ ���ff.� @ �= / uUH���~�����. ]�D �ff.� @ �f.� @ H��H�D$H�%�@@ �D$ � ��|$H�L$ H� %�@@ �D$ H� @ �m���� �D$��H���f.�  H��(@��H�|$H�|$H�<%�P@ $�D$H�|$H�<%�P@ H�t$H� @ � �.����D$�D$� � H� @ ������D$ �! H� @ ������ �D$�����D$H��(�f.� f�H���|$H�D$H�%�`@ H� @ �����t$H�, @ �D$ � �����{ �D$��H��� H��H�|$H�|$H�=�] H�|$�A�����D$��H���@ H��(� ��H�|$H�|$H�<%��@ H�|$H�t$����������H�t$�#���H�t$H�4%��@ H�D$H�t$H�|$�����H�t$H�$H��H��(ÐH��H� ��H�|$8H�|$8H�<%��@ H�|$8H�t$(����������H�t$(����H�t$0H�4%��@ H�D$0H�t$8H�|$0�R���H�|$0H�5 @ H�D$ ����H�t$0H�|$8H�� H�D$H�t$H�|$� � H�|$�����H�D$H��H�f.�  H��8�� ��� ��H�|$(H�|$(H�<%��@ H������H�L$ H� %��@ H�D$ H�t$(H�|$ ����H�|$ H�D$����H�L$ H�t$(H�� �D$H�L$H�4$� � H�<$�U���H�D$H��8�f.� ��|$�H�D$�H�%��@ �|$���{���D H���|$H�D$H�%��@ H�: @ ����H�<%��@ �7H�> @ �D$ � ����H�<%��@ �7t$�D$��H���@ UH��H��pH�%�@@ H�F @ ����H�R @ �E��{���H�}�H�<%��@ H�E�H�E�H�%��@ �E�o �u�H�V @ � ����H�\ @ � �E��
���� ������{���b @ ���������H�w @ ������{ @ ���������H�� @ �����H���I���H������H�}�H�<%��@ H�E�H�}������H�}�H�<%��@ �E�{ �}�{���� @ ����E��l���H�}�H�<%��@ H�@ H�}п �UЃ�|���� @ �����5����}�{���� @ ��������H�}�H�<%��@ �E�{ �E�� �}�{���ʀ��U����M�� � �}�� ���M� ����M��u��� @ �������H��H���H��H��H� %��@ �{ �G� �?{��A��A��D�E���H�}��U�� � H�E��x� ���U� ʀ��U��E��� @ �����M���H�}�H�� H�}�� � H�}��]���H�}�H�� H�}�� � H�}��=���1�H��]�fD AWI��AVI��AUA��ATL�%�% UH�-�% SL)�H�������H��t1� L��L��D��A��H��H9�u�H��[]A\A]A^A_� � H��H���   called fun %s... yes no called int::fun self %d
 +ABC FUN xxx %d
 HELLO WORLD AAA a %d
 test1 message passing test ABC const test ABC eqeq test function pointer test eqeq test load field and store test load field and store test2 ;�  4���� ����� ����� ���� ��� ����4 ���L 4���d ����| d���� ���� $���� ����� ���� t���D  zR x �  ���+  zR x �   $��� $ 0 P���� FJ w� ?;*3$"       X   ����S    D N   p   �����    D0�   �   x���M    D H   �   ����,    D g    �   ����o    D0j   �    ����    DP�   �   �����    D@�      P���            \���\    D W    ,  �����   A�C
�  D P ���] B�E�E �E(�H0�H8�G@j8A0A(B BBB  � (��� �@ `@   @
       d@  >@    >@    @ ���o P@  �@  p@
       v    @@  �    �@  X@  0  ���o 8@ ���o  ���o @ >@ 6@ F@ V@ f@ v@ �@ �@ �@ 90 GCC: (Debian 8.3.0-6) 8.3.0 �  � / funXXX u int_fun j main � const_test � string  string_test1 � string2 R xassert G coroutine2 $ coroutine1 �  $   �@ �@ �@ �@ W+ + �  @ �@ W6 6 (� �@ �@ W> > /� �@ @ WF F 5�  @ �@ WQ Q B� �@ C@ W` ` L� P@ �@ Wh h W� �@ @ Wu u s� @ l@ W� � �� p@ �@ V� � �� 2 2 �X  %�B  . @
�@: ; I? 2 $ > �  ( �
   code HelloWorld.c  �@ 
FK��
�
tw%`7w� #
J���4
J��
�
�2�

�z 2�� I
 y ���D
$�
J\
T���"/>h��/�0���Z�uvELgvQG code/HelloWorld.c /home/ab25cq/repo/neo-c2 funXXX int xassert int_fun const_test string pointer string2 string_test1 coroutine1 coroutine2 main  "  � � pointer � int   �@   �@   �@   @   P@   p@   �@   @  8@ 
 X@  �@  @ 
  @   �@   d@   @   � @   p!@   >@   >@   >@   �?@   @@   X@@   p@@               !   ��   �@    @ !   `@ 7   p@@  F   >@ m   �@ y   >@ �  �� �    @ �   F @ �   R @  �   V @  �   \ @     b @     w @  *   { @ =   � @  P   � @
       c   � @  v    @  �   � @
       �   � @  �   � @  �    @  �    @  �    @  �   , @    5 @     : @  -   > @  ?   �@  J   @ \ U   �@@  _   �P@  i   �`@  s   �p@  }   ��@  �   ��@  �   ��@  �   ��@  �   ��@  �   @ o   �� �   D#@  �� �  >@ �   >@ �  >@ �  � @ �   @@    `@  #  �  X@@ 5  I  [   �@@  b   p@@ i   P@ �   d@ v  �   �@@  �  �   �@ , �   �@ M �   �@@  �  �  �   X@@    &  `@@ 3   @  B   �@ S I   @ ] Y   @ � �   ��@ a  �@  �   �@ + y   p@@ �   p@ � �   �@ � �   h@@  �  �  �  �  p@@ S  @ �   x@@  crtstuff.c deregister_tm_clones __do_global_dtors_aux completed.7325 __do_global_dtors_aux_fini_array_entry frame_dummy __frame_dummy_init_array_entry HelloWorld.c.pp .Lglobal_string .Lglobal_string.10 .Lglobal_string.11 .Lglobal_string.12 .Lglobal_string.13 .Lglobal_string.14 .Lglobal_string.15 .Lglobal_string.16 .Lglobal_string.17 .Lglobal_string.18 .Lglobal_string.19 .Lglobal_string.2 .Lglobal_string.20 .Lglobal_string.21 .Lglobal_string.22 .Lglobal_string.3 .Lglobal_string.4 .Lglobal_string.5 .Lglobal_string.6 .Lglobal_string.7 .Lglobal_string.8 .Lglobal_string.9 coroutine1 coroutine2 gLVTable0 gLVTable1 gLVTable2 gLVTable3 gLVTable4 gLVTable5 gLVTable6 gLVTable7 gLVTable8 __FRAME_END__ __init_array_end _DYNAMIC __init_array_start __GNU_EH_FRAME_HDR _GLOBAL_OFFSET_TABLE_ __libc_csu_fini free@@GLIBC_2.2.5 strcpy@@GLIBC_2.2.5 puts@@GLIBC_2.2.5 gSData _edata string_test1 strlen@@GLIBC_2.2.5 yyyyyyyy printf@@GLIBC_2.2.5 const_test int_fun xxxxxxxx __libc_start_main@@GLIBC_2.2.5 calloc@@GLIBC_2.2.5 __data_start strcmp@@GLIBC_2.2.5 __gmon_start__ __dso_handle _IO_stdin_used funXXX __libc_csu_init xassert _dl_relocate_static_pie __bss_start main string2 gAAAAAA atoi@@GLIBC_2.2.5 strcat@@GLIBC_2.2.5 exit@@GLIBC_2.2.5 __TMC_END__ aaa .symtab .strtab .shstrtab .interp .note.ABI-tag .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .text .fini .rodata .eh_frame_hdr .eh_frame .init_array .fini_array .dynamic .got .got.plt .data .bss .comment .debug_pubnames .debug_info .debug_abbrev .debug_line .debug_str .debug_macinfo .debug_pubtypes    �@ �   #   �@ �  1   �@ � $  H   @  H    D ���o P@ P    N  p@ p 8     V   �@ � v  ^ ���o @      k ���o 8@ 8    z   X@ X 0    �  B �@ � �     �   @    �   @  �   �   �@ � �  �   d@ d  �   @ �  �   � @ � �  �   p!@ p! �  �   >@ .    �   >@ .    �   >@ . �    �   �?@ �/    �   @@ 0 X   �   X@@ X0   �   p@@ p0 �  �  0 p0      �0 �    1 �    �2 <  -  �2 �  9  0 �3 �   D  h4   S  i4 &    �4 � # U    @ �    �D c 
