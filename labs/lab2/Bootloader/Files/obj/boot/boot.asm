
obj/boot/boot.out:     file format elf32-i386


Disassembly of section .text:

00007c00 <bootmain>:



void
bootmain(void)
{
    7c00:	55                   	push   %ebp
    7c01:	89 e5                	mov    %esp,%ebp
    7c03:	eb fe                	jmp    7c03 <bootmain+0x3>
