#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>

uint32_t data (const char *filename){
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    
    // Check file size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    if (filesize < sizeof(uint32_t)) {
        fprintf(stderr, "Error: File size is less than 4 bytes.\n");
        fclose(file);
        exit(1);
    }
    fseek(file, 0, SEEK_SET);
    
    uint32_t buffer;
    if (fread(&buffer, sizeof(uint32_t), 1, file) > 0) {
        fclose(file);
        return ntohl(buffer);
    }

    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Wrong number of arguments. Please provide two file names as arguments.\n");
        return 1;
    }
    const char *file1 = argv[1];
    const char *file2 = argv[2];

    uint32_t data1 = data(file1);
    uint32_t data2 = data(file2);

    uint32_t sum = data1 | data2;

    printf("%u(0x%04X) | %u(0x%04X) = %u(0x%04X)\n", data1, data1, data2, data2, sum, sum);

    return 0;
}
