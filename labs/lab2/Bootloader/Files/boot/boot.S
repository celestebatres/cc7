.globl start
start:
    # FIRST PHASE: Register y operation mode setup.
    # Assemble for 16-bit mode
    .code16  

    cli
    # The BIOS loads this code from the first sector of the hard disk into
    # memory at physical address 0x7c00 and starts executing in real mode
    # with %cs=0 %ip=7c00.
    movw     $0x07C0,%ax 
    movw     %ax, %ds
    movw     %ax, %es
    movw     %ax, %fs
    movw     %ax, %gs

    #Stack Initialization
    movw     $0x0000 , %ax 
    movw     %ax, %ss
    movw     $0xFFFF,%sp
    sti

    # Buffer de entrada para almacenar caracteres del teclado
    mov $input_buffer, %si   # Puntero al inicio del buffer de entrada

readline:
    xorw %ax, %ax          # Limpiar el registro AX
    int $0x16               # Interrupción del teclado BIOS

    cmpb     $0x0D, %al    # Comprobar si es Enter
    je imprimir            # Si es Enter, imprimir y volver a leer
    movb     %al, (%si)    # Almacenar el caracter en el buffer
    inc %si                # Incrementar el puntero del buffer
    jmp readline           # Volver a leer del teclado


imprimir:
    mov $input_buffer, %si   # Puntero al inicio del buffer de entrada
    call writeline            # Llamar a la función writeline con la cadena de texto ingresada
    mov $input_buffer, %si    # Restablecer el puntero del buffer de entrada al inicio
    jmp readline             # Volver a leer del teclado

writeline:
    push %ax               # Guardar AX
    push %bx               # Guardar BX
    mov $0x0E, %ah         # Función de Teletipo BIOS para mostrar en pantalla
    mov $0x00, %bh         # Página de visualización (0 por defecto)

loop_writeline:
    lodsb                     # Cargar el siguiente byte de la cadena
    cmp $0, %al               # Comprobar si es el final de la cadena
    je end_loop               # Si es el final, salir del bucle
    int $0x10                 # Llamar a la interrupción BIOS para mostrar el carácter
    jmp loop_writeline          # Repetir hasta el final de la cadena

end_loop:
    pop %bx                   # Restaurar BX
    pop %ax                   # Restaurar AX
    ret                       # Retornar de la función

# Buffer de entrada para almacenar caracteres del teclado
.section .bss
    .lcomm input_buffer, 128 # Buffer de 128 bytes para la entrada del teclado