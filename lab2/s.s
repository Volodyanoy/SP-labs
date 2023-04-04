.data

array:
	.long 12, 2, -2, 1, 13, 2, -11, 5, 4, -3, -14, 0
	array_end:

positive_sum:
	.string "Positive sum = %d\n"

negative_sum:
	.string "Negative sum = %d\n"

print_ok:
	.string "Seventh bit in the negative sum: Available\n"

print_no:
	.string "Seventh bit in the negative sum: Not available\n"

.text
.global main

main:
	xorl %eax, %eax
	xorl %ebx, %ebx
	movl $array, %esi

funct:
	movl (%esi), %edx
	cmpl $0, %edx
	jl less

	addl %edx, %eax
	jmp next

less:
	addl %edx, %ebx
	
next:
	addl $4, %esi
	cmp $array_end, %esi
	jne funct

pushl %eax
pushl $positive_sum
call printf
addl $8, %esp

pushl %ebx
pushl $negative_sum
call printf
addl $8, %esp

movl %ebx, %ecx
andb $0x80, %cl
cmpl $0, %ecx
jne ok

pushl $print_no
call printf
jmp end

ok:
	pushl $print_ok
	call printf

end:
	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80
