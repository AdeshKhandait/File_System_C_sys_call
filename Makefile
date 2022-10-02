# MakeFile for FileSystem
# Specifying the Compiler
CC=gcc

# Specifying the Flags 

# Specifying the Objects Files
OBJS = obj/create.o obj/print.o obj/File.o

# Specifying the Binary file
BIN = bin/FileSystem

# Export in zip file
EXPORT_NAME = FileSystem.zip

all: $(BIN)

# Binary file generated
bin/FileSystem: $(OBJS)
	$(CC) $(OBJS) -o $@

# Compile all .c and create .o using auto varibles($<) and ($@)
# What they basically means is that same as above
obj/%.o: src/%.c
	$(CC) -c $< -o $@

# Removing the file
clean: 
	$(RM) -r obj/* bin/*
run:
	./$(BIN)
export:
	$(RM) $(EXPORT_NAME)
	zip $(EXPORT_NAME) $(BIN)