// Meta Information about ther File System

#define BLOCKSIZE 1024
#define NAME 256

// StartBlock -> Stores Information
// - Size of File System
// - Start of MetaData
// - Start of Data_Block 
struct StartBlock
{
    // Size of the File system 
    long int size_HDD;
    long int start_MetaData;
    long int start_Data_Block;
    int size_block;
};

// MetaData -> Stores the Stores Information
// 1.File Size
// 2.First Data Block
// 3.File Number
// 4.File Name

struct MetaData
{
    long int file_size;
    long int first_Block;
    long int file_number;
    char file_name[NAME];
};

// Disk_Block
struct Disk_Block
{
    long int Next_Data_Block;
    int pos;
    char Data[BLOCKSIZE];
};


//----------------------------------------Declaration of the File System Operation---------------------------------------------------

// Creating the File System
void create_file_system();

// Sync the File System
void sync_file_system();


// --------------------------------------------------Input_Output_Handler-----------------------------------------------------------------

long int input_long_int();

void create_file();

int open_file();


