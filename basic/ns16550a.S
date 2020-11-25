.global uart_put_char
.global uart_get_char

uart_get_char:
    .cfi_startproc
	
	addi sp, sp, -32

	sd fp, 24(sp)

	addi fp, sp, 32
	
	mv a5, a0
	
	sb a5, -17(s0)

    .cfi_endproc

uart_put_char:
    .cfi_startproc

	addi sp, sp, -16
	
	sd s0, 8(sp)
	
	add s0, sp, 16

    .cfi_endproc

.end
