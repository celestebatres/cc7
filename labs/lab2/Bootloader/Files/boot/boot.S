
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
   

	movw     $0x0043, %ax 	#Put an ASCII Value to ax
        movb     $0x0E,%ah 	#Bios Teletype,This number must be used to 
				#tell the BIOS to put a character on the screen
        movb     $0x00,%bh 	#Page number (For most of our work this will remain 0x00)
        movb     $0x08,%bl      #Text attribute (For most of our work this will remain 0x07) 
				#Try to change this value
        int      $0x10  	#BIOS video interrupt. 
	
	call bootmain     	#SECOND PHASE: a C program that would load the
				#kernel into memory.

# Bootstrap GDT
.p2align 2                                # force 4 byte alignment





