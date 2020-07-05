#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void errOut(char *msg)
{
    printf("error: %s\n", msg);
    exit(1);
}


int main(int argc, char *argv[])
{
    int in_fd, out_fd;

    if (argc < 3)
    {
        printf("cp: missing file operand\n");
        exit(1);
    }

    // Open file arguments
    in_fd = open(argv[1], O_RDONLY);
    if (in_fd == -1)
    {
        errOut("file open");
    }

    out_fd = open(argv[2], O_RDWR | O_CREAT, S_IRWXU); // Allow for creation if target does not exist
    if (out_fd == -1)
    {
        errOut("file open");
    }


    // Find out how many bytes the file is
    off_t curr, end, total;
    char *content;    

    curr = lseek(in_fd, 0, SEEK_CUR); // Retrieve current location of file offset
    end = lseek(in_fd, -1, SEEK_END); // Go to the end
    lseek(in_fd, 0, SEEK_SET); // Return offset back to the beginning


    // Read bytes into buffer
    total = end - curr + 1; // Determine the total size of the content + 1 for the offset calculation
    content = malloc(sizeof(off_t) * total);
    read(in_fd, content, total);


    // Write bytes from buffer to output file
    write(out_fd, content, total);


    free(content);

    // Close file arguments
    if (close(in_fd) == -1)
    {
        errOut("file close");
    }

    if (close(out_fd) == -1)
    {
        errOut("file close");
    }



}