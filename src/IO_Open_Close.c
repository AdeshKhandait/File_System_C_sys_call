#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h> 
#include<errno.h> 
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


// Opening the File
void create_file(){

    int file = open("bin/Data.vd", O_CREAT | O_WRONLY| O_TRUNC ,0642|00070);

    if(file == -1){
        perror("\nError in Creating the File_System!\n");
    }
    else{
        printf("\nFile Created Successully!!\n");
    }

    if (close(file) < 0)
    {
        perror("\nFile Does not Close");
    }else
    {
        printf("\nFile Successfully Closed!!\n");
    }
}


int open_file(){

    int file = open("bin/Data.vd",O_WRONLY);
    
    if(file == -1){
        perror("\nError in Opening the File_System!\n");
    }
    else{
        printf("\nFile Opened Successully!!\n");
    }

    return file;
}