#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

char* getFileName(char *fileType) {
    char *fileName;
    printf("Enter %s file name: ", fileType);
    scanf("%ms", &fileName);

    if (strlen(fileName) < 1) {
        printf("Invalid %s file name", fileType);
        exit(1);
    }

    return fileName;
}

int main(int argc, char *argv[]) {
    char *srcFileName;
    if (argc > 1) {
        srcFileName = argv[1];
    } else {
        srcFileName = getFileName("source");
    }
    printf("source file name: %s\n", srcFileName);

    char *dstFileName; 
    if (argc > 2) {
        dstFileName = argv[2];;
    } else {
        dstFileName = getFileName("destination");
    }
    printf("destination file name: %s\n", dstFileName);

    FILE *srcFile = fopen(srcFileName, "rb");
    if (srcFile == NULL) {
        printf("Unable to open file for reading: %s\n", srcFileName);
        exit(1);
    }

    FILE *dstFile = fopen(dstFileName, "wb");
    if (dstFile == NULL) {
        printf("Unable to open file for writing: %s\n", dstFileName);
        exit(1);
    }

    int BUFFER_SIZE = 1024;
    u_int8_t *buffer = (u_int8_t*) malloc(BUFFER_SIZE * sizeof(u_int8_t));
    if (buffer == NULL) {
        printf("Unable to allocate buffer for file read\n");
        exit(1);
    }

    size_t totalNumRead = 0;
    size_t numRead = fread(buffer, sizeof(u_int8_t), BUFFER_SIZE, srcFile);
    while (numRead > 0) {
        totalNumRead += numRead;
        fwrite(buffer, sizeof(u_int8_t), numRead, dstFile);
        numRead = fread(buffer, sizeof(u_int8_t), BUFFER_SIZE, srcFile);
    }
    
    free(buffer);
    fclose(srcFile);
    fclose(dstFile);

    printf("Copied %lu bytes from %s to %s\n", totalNumRead, srcFileName, dstFileName);

    return 0;
}