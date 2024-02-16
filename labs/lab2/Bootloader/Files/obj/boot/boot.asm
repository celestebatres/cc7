
obj/boot/boot.out:     file format elf32-i386


Disassembly of section .text:

00007c00 <start>:
start:
    # FIRST PHASE: Register y operation mode setup.
    # Assemble for 16-bit mode
    .code16  

    cli
    7c00:	fa                   	cli    
    # The BIOS loads this code from the first sector of the hard disk into
    # memory at physical address 0x7c00 and starts executing in real mode
    # with %cs=0 %ip=7c00.
    movw     $0x07C0,%ax 
    7c01:	b8 c0 07 8e d8       	mov    $0xd88e07c0,%eax
    movw     %ax, %ds
    movw     %ax, %es
    7c06:	8e c0                	mov    %eax,%es
    movw     %ax, %fs
    7c08:	8e e0                	mov    %eax,%fs
    movw     %ax, %gs
    7c0a:	8e e8                	mov    %eax,%gs

    #Stack Initialization
    movw     $0x0000 , %ax 
    7c0c:	b8 00 00 8e d0       	mov    $0xd08e0000,%eax
    movw     %ax, %ss
    movw     $0xFFFF,%sp
    7c11:	bc ff ff fb be       	mov    $0xbefbffff,%esp
    sti

    # Buffer de entrada para almacenar caracteres del teclado
    mov $input_buffer, %si   # Puntero al inicio del buffer de entrada
    7c16:	80                   	.byte 0x80
    7c17:	7c                   	.byte 0x7c

00007c18 <readline>:

readline:
    xorw %ax, %ax          # Limpiar el registro AX
    7c18:	31 c0                	xor    %eax,%eax
    int $0x16               # Interrupción del teclado BIOS
    7c1a:	cd 16                	int    $0x16

    cmpb     $0x0D, %al    # Comprobar si es Enter
    7c1c:	3c 0d                	cmp    $0xd,%al
    je imprimir            # Si es Enter, imprimir y volver a leer
    7c1e:	74 05                	je     7c25 <imprimir>
    movb     %al, (%si)    # Almacenar el caracter en el buffer
    7c20:	88 04 46             	mov    %al,(%esi,%eax,2)
    inc %si                # Incrementar el puntero del buffer
    jmp readline           # Volver a leer del teclado
    7c23:	eb f3                	jmp    7c18 <readline>

00007c25 <imprimir>:


imprimir:
    mov $input_buffer, %si   # Puntero al inicio del buffer de entrada
    7c25:	be 80 7c e8 05       	mov    $0x5e87c80,%esi
    call writeline            # Llamar a la función writeline con la cadena de texto ingresada
    7c2a:	00 be 80 7c eb e8    	add    %bh,-0x17148380(%esi)

00007c30 <writeline>:
    mov $input_buffer, %si    # Restablecer el puntero del buffer de entrada al inicio
    jmp readline             # Volver a leer del teclado

writeline:
    push %ax               # Guardar AX
    7c30:	50                   	push   %eax
    push %bx               # Guardar BX
    7c31:	53                   	push   %ebx
    mov $0x0E, %ah         # Función de Teletipo BIOS para mostrar en pantalla
    7c32:	b4 0e                	mov    $0xe,%ah
    mov $0x00, %bh         # Página de visualización (0 por defecto)
    7c34:	b7 00                	mov    $0x0,%bh

00007c36 <loop_writeline>:

loop_writeline:
    lodsb                     # Cargar el siguiente byte de la cadena
    7c36:	ac                   	lods   %ds:(%esi),%al
    cmp $0, %al               # Comprobar si es el final de la cadena
    7c37:	3c 00                	cmp    $0x0,%al
    je end_loop               # Si es el final, salir del bucle
    7c39:	74 04                	je     7c3f <end_loop>
    int $0x10                 # Llamar a la interrupción BIOS para mostrar el carácter
    7c3b:	cd 10                	int    $0x10
    jmp loop_writeline          # Repetir hasta el final de la cadena
    7c3d:	eb f7                	jmp    7c36 <loop_writeline>

00007c3f <end_loop>:

end_loop:
    pop %bx                   # Restaurar BX
    7c3f:	5b                   	pop    %ebx
    pop %ax                   # Restaurar AX
    7c40:	58                   	pop    %eax
    ret                       # Retornar de la función
    7c41:	c3                   	ret    

00007c42 <bootmain>:



void
bootmain(void)
{
    7c42:	55                   	push   %ebp
    7c43:	89 e5                	mov    %esp,%ebp
    7c45:	eb fe                	jmp    7c45 <bootmain+0x3>
