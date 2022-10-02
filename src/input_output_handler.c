#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// Input_Handler -> It will all sort of the input and Output


// Input the Long int 
long int input_long_int(){

    long int size;
    scanf("%ld",&size);
    if (size <= 0)
    {
        perror("Error Invaild File Size");
        exit(1);
    }
    else{
        return size;
    }
    
} 