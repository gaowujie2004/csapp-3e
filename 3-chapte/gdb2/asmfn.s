.global fn1
fn1:
    
    movl $1, %ecx
    movq $0xabcdef7890abcd01, %rcx
    addl $1, %ecx



    // 对齐组合单精度浮点数-xmm
    movaps .LC0(%rip), %xmm0
    movaps .LC1(%rip), %xmm1

    addss  %xmm1, %xmm0
    

    ret
    .align 16
.LC0:
    .long	0B01000010110010000000000000000000  #100f
	.long	0B01000010110010100000000000000000  #101f
	.long	0B01000010110011000000000000000000  #102f
	.long	0B01000010110011100000000000000000  #103f
    .align 16
.LC1:
	.long	0B01000001101000000000000000000000  #20f
	.long	0B01000001101010000000000000000000  #21f
	.long	0B01000001101100000000000000000000  #22f
	.long	0B01000001101110000000000000000000  #24f
	.align 16
.LC2:
	.float 30.0
	.float 31.0
	.float 32.0
	.float 33.0
	.align 16
