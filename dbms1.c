#include <stdio.h>      // For standard I/O functions
#include <stdlib.h>     // For exit()
#include <fcntl.h>      // For file control options (open)
#include <unistd.h>     // For system calls like read, write, close
#include <string.h>     // For strlen()
#include <sys/stat.h>   // For file permissions (chmod)
#include <errno.h>      // For error codes

#define BUFFER_SIZE 1024

// Demonstrating Unix system calls for file operations
void unix_system_calls(const char *filename) {
    int fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // 1. Open file (with O_CREAT to create it if it doesn't exist)
    fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // 2. Write to file using write()
    const char *text = "Hello, this is a test for Unix system calls!\n";
    bytes_written = write(fd, text, strlen(text));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 3. Use lseek() to move the file pointer to the start
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error using lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 4. Read from file using read()
    bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    buffer[bytes_read] = '\0';  // Null-terminate the string
    printf("Read from file: %s\n", buffer);

    // 5. Append to the file
    const char *append_text = "Appending more text using Unix system calls!\n";
    if (lseek(fd, 0, SEEK_END) == -1) {
        perror("Error seeking to end of file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    bytes_written = write(fd, append_text, strlen(append_text));
    if (bytes_written == -1) {
        perror("Error appending to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 6. Close the file using close()
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    // 7. Change file permissions using chmod()
    if (chmod(filename, 0600) == -1) {
        perror("Error changing file permissions");
        exit(EXIT_FAILURE);
    } else {
        printf("File permissions changed to 600 (rw-------).\n");
    }
}

// Demonstrating C standard library file operations
void c_library_file_operations(const char *filename) {
    FILE *fp;
    char buffer[BUFFER_SIZE];

    // 1. Open file with fopen()
    fp = fopen(filename, "w+");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // 2. Write to file using fwrite()
    const char *text = "Hello, this is a test for C standard library calls!\n";
    if (fwrite(text, sizeof(char), strlen(text), fp) < strlen(text)) {
        perror("Error writing to file");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    // 3. Use fseek() to move the file pointer to the start
    if (fseek(fp, 0, SEEK_SET) != 0) {
        perror("Error using fseek");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    // 4. Read from file using fread()
    size_t bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE - 1, fp);
    if (bytes_read == 0 && ferror(fp)) {
        perror("Error reading from file");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    buffer[bytes_read] = '\0';  // Null-terminate the string
    printf("Read from file (C library): %s\n", buffer);

    // 5. Append to the file
    const char *append_text = "Appending more text using C library!\n";
    if (fseek(fp, 0, SEEK_END) != 0) {
        perror("Error seeking to end of file");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    if (fwrite(append_text, sizeof(char), strlen(append_text), fp) < strlen(append_text)) {
        perror("Error appending to file");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    // 6. Close the file using fclose()
    if (fclose(fp) != 0) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
}

// Removing the file after operations
void remove_file(const char *filename) {
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}

int main() {
    const char *filename = "testfile.txt";

    // Demonstrating Unix System Calls
    printf("Unix System Calls Demo:\n");
    unix_system_calls(filename);

    // Demonstrating C Library File Operations
    printf("\nC Standard Library Calls Demo:\n");
    c_library_file_operations(filename);

    // Removing the file
    printf("\nRemoving the file after operations:\n");
    remove_file(filename);

    return 0;
}

