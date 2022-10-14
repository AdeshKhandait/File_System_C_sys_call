#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "file_system.h"


// Update the Inode 
void update_Inode(long int Inode_num) {

    // Setting the File Pointer to Respective Inode
    long int jump = SB.start_MetaData;
    jump = jump + size_MetaData*Inode_num;
    int error_lseek = lseek(file,jump,SEEK_SET);
    
    if (error_lseek == -1)
    {
        perror("\n Error in SEEK_SET\n");
        exit(1);
    }
    


    long int error_write = write(file,&Inodes[Inode_num],size_MetaData);

    if (error_write != size_MetaData)
    {
        perror("\n Error in Writing the MetaData\n");
    }
    
}


// update the DBK
void update_DBK( long int DBK_num) {

    // Setting the File Pointer to Respective Inode
    long int jump = SB.start_Data_Block;
    jump = jump + size_Disk_Block*DBK_num;
    int error_lseek = lseek(file,jump,SEEK_SET);

    if (error_lseek == -1)
    {
        perror("\n Error in SEEK_SET\n");
        exit(1);
    }


    long int error_write = write(file,&DBK[DBK_num],size_Disk_Block);

    if (error_write != size_Disk_Block)
    {
        perror("\n Error in Writing the DiskBlock\n");
        exit(1);
    }
    


}

// read the inode
void read_Inode(long int Inode_num) {

    struct MetaData temp;

    long int jump = SB.start_MetaData;
    jump = jump + size_MetaData*Inode_num;

    lseek(file,jump,SEEK_SET);
    read(file,&temp,size_MetaData);

    printf("\nFile Size: %ld",temp.file_size);
    printf("\nFirst Block: %ld",temp.first_Block);
    printf("\nFile Number: %ld",temp.file_number);
    printf("\nFile Name: %s",temp.file_name);
}

// read the DiskBlock
void read_DBK(long int DBK_num) {

    struct Disk_Block temp;

    long int jump = SB.start_Data_Block;
    jump = jump + size_Disk_Block*DBK_num;

    lseek(file,jump,SEEK_SET);
    read(file,&temp,size_Disk_Block);

    printf("\n Next: %ld\n",temp.Next_Data_Block);
    printf("\n Pos: %d\n",temp.pos);
}


// allocate file
long int allocate_file() {

// Collecting the File Name
    char name[NAME];
    printf("\nEnter the File Name(max: 256 char): ");
    scanf("%s",name);

// Finding Inode and Disk Block
    long int empty_Inode = search_empty_IN();
    long int empty_DBK = search_empty_DBK();

// Claiming the Inode and Disk Block
    Inodes[empty_Inode].first_Block = empty_DBK;
    DBK[empty_DBK].Next_Data_Block = -2; 

// Updating the BitMap
    Clear_Bit_IN(empty_Inode);
    Clear_Bit_DBK(empty_DBK);

// updating the file name
    strcpy(Inodes[empty_Inode].file_name,name);

// Updating the Inode
    Inodes[empty_Inode].file_number = empty_Inode;

// Updating the Disk
    update_Inode(empty_Inode);

// Updating the file DBK
    update_DBK(empty_DBK);

    return empty_Inode;
}

// Check the File Exist of not
int check_file(long int filenum){

    for (long int i = 0; i < num_MetaData; i++)
    {
        if (filenum == Inodes[i].file_number)
        {
            return 1;
        }
    }
    return 0;
}

// Shrinking the file size
void shrink_file_size(long int block_num){

    long int nn = DBK[block_num].Next_Data_Block;

    if (nn >= 0)
    {
        shrink_file_size(nn);
    }
    
    // Free the Block
    DBK[block_num].Next_Data_Block = -1;
    // Upading the DBK block
    update_DBK(block_num);
    // Updating the BitMap
    Set_Bit_DBK(block_num);
}


// Set the File size of the file
void set_file_size(long int file_num, long int file_size){

    
// Check if file exist
    int error_file = check_file(file_num);
    
    if (error_file == 0)
    {
        perror("\n File Does not Exist\n");
        exit(1);
    }
    
// Count the number of the Block Needed
    long int count_block = file_size + BLOCKSIZE - 1;
    count_block = count_block/ BLOCKSIZE;
    // count_block--;

    long int temp_blk = Inodes[file_num].first_Block;
    count_block--;
    

    while (count_block > 0)
    {
        // Check if the next is empty
        long int next = DBK[temp_blk].Next_Data_Block;
        if (next == -2)
        {
            long int empty = search_empty_DBK();
            // Assigning the next to currnet 
            DBK[temp_blk].Next_Data_Block = empty;
            // updating the DBk and BITMap
            update_DBK(temp_blk);
            Clear_Bit_DBK(temp_blk);
            // Setting the block as occpuied
            DBK[empty].Next_Data_Block = -2;
            update_DBK(empty);
            Clear_Bit_DBK(empty);
        }
        
        // Updating the Block num
        temp_blk = DBK[temp_blk].Next_Data_Block;
        update_DBK(temp_blk);
        Clear_Bit_DBK(temp_blk);
        count_block--;
    }
    

    // Check for the Shrinking the File
    shrink_file_size(temp_blk);

    // Setting the Block as occupied
    DBK[temp_blk].Next_Data_Block = -2;
    update_DBK(temp_blk);
    Clear_Bit_DBK(temp_blk);

    Inodes[file_num].file_size = file_size;
    // updating the Inode
    update_Inode(file_num);

    printf("\n %ld Bytes is Allocated!\n",file_size);
}


// Write the file into Disk
void insert_file() {

// Allocating the file and return file number
    long int file_num = allocate_file();

    char input_file_name[256];

    printf("\nEnter the File name along with path(max: 256): ");
    scanf("%s",input_file_name);

    int input_file_fd = open(input_file_name,O_RDONLY);

    long int input_file_size;
    lseek(input_file_fd,0,SEEK_SET);
    input_file_size = lseek(input_file_fd,0,SEEK_END);
    
    printf("\nSize in Bytes: %ld\n",input_file_size);
    set_file_size(file_num,input_file_size);


    // read input
    char buff[BLOCKSIZE];
    
    

    long int count_block = input_file_size + BLOCKSIZE - 1;
    count_block = count_block/ BLOCKSIZE;
    lseek(input_file_fd,0,SEEK_SET);
    long int start_write = DBK[file_num].Next_Data_Block;
    for (long int i = 0; i < count_block; i++)
    {
        int error_read_input = read(input_file_fd,buff,BLOCKSIZE);

        // printf("\nRead: %d\n",error_read_input);
        if (error_read_input < 0)
        {
            perror("\n Error in reading input file\n");
            exit(1);
        }
        
        for (int i = 0; i < BLOCKSIZE; i++)
        {
            DBK[start_write].Data[i] = buff[i];
        }
        // strcpy(DBK[start_write].Data,buff);
        update_DBK(start_write);
        start_write = DBK[start_write].Next_Data_Block;
    }
    
}

void read_file(long file_num) {

    long int temp = Inodes[file_num].first_Block;

    while ( temp < 0)
    {
        printf("\n%s",DBK[temp].Data);
        temp = DBK[temp].Next_Data_Block;
    }
    
}

