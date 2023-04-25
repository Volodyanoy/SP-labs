#include <stdio.h>
#include <stdlib.h>

int main() 
{
    srand(time(NULL));
    const int size_mass = 7;
    int mass[size_mass];

    for (int i = 0; i < size_mass; i++)
    {
        // Заполнение массива числами от -40 до 40
        mass[i] = rand() % 81 - 40;
        printf("%d ", mass[i]);
    }
    
    printf("\n");
    int max_value = 0;
    int index = 0;
    int pos_sum=0;
    int neg_sum=0;
    int flag = 1;
    int* ptr_mass = mass;	


    asm (
        "movq %[ptr_mass], %%rax;"
        "movl %[size_mass], %%ebx;"        
        "xorl %%ecx, %%ecx;" // pos sum                 
        "xorl %%edx, %%edx;" // neg sum           
        "xorl %%edi, %%edi;"
        
"funct:"
	"movl (%%rax), %%esi;"
	"cmpl $0, %%esi;"
	"jl less;"

	"addl %%esi, %%ecx;"
	"jmp next;"

"less:"
	"addl %%esi, %%edx;"
	
"next:"
	"inc %%edi;"
	"addq $4, %%rax;"
        "cmpl %%ebx, %%edi;"
        "jne funct;"


        "movl %%ecx, %[pos_sum];"
        "movl %%edx, %[neg_sum];"
            
        "xorl %%ecx, %%ecx;"
        "movl %%edx, %%ecx;"
	"andb $0x80, %%cl;"
	"cmpl $0, %%ecx;"
	"jne ok;"
        "movl $0, %[flag];"
        
"ok:"  
      
        "movq %[ptr_mass], %%rax;"
        "movl %[size_mass], %%ebx;"        
        "xorl %%ecx, %%ecx;" // index max value
        "xorl %%edx, %%edx;"
        "xorl %%esi, %%esi;"                      
        "xorl (%%rax), %%edx;" // max value         
        "xorl %%edi, %%edi;"  
              
"loop:"
	"movl (%%rax), %%esi;"
        "cmpl %%esi, %%edx;"
        "jg loop_step;"       

        "movl %%esi, %%edx;"
        "movl %%edi, %%ecx;"
        
"loop_step:"        	

        "inc %%edi;"
        "addq $4, %%rax;"
            
        "cmpl %%ebx, %%edi;"
        "jne loop;"

        "movl %%edx, %[max_value];"
        "movl %%ecx, %[index];"
	 
	    
        :
        :[size_mass]"m"(size_mass), [ptr_mass]"m"(ptr_mass),
           [pos_sum]"m"(pos_sum), [neg_sum]"m"(neg_sum),
           [flag]"m"(flag), [max_value]"m"(max_value), [index]"m"(index)
        :
        );
     
    printf("Positive sum = %d\n", pos_sum);
    printf("Negative sum = %d\n", neg_sum);
    printf("Flag (seventh bit) = %d\n", flag);    
    printf("Seventh bit in the negative sum: ");

        	
    if ((neg_sum & 0x80) == 0)
	printf("Not available\n");
    else
	printf("Available\n");

    printf("Index max value = %d\n", index);
    printf("Max value = %d\n", max_value);
    	
    return 0;
}

