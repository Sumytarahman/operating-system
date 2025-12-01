#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // for truncate()
#include <errno.h>

void createFile() {
    char filename[100];
    printf("Enter file name to create: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error creating file");
        return;
    }
    fclose(fp);
    printf("File '%s' created successfully.\n", filename);
}

void deleteFile() {
    char filename[100];
    printf("Enter file name to delete: ");
    scanf("%s", filename);

    if (remove(filename) == 0)
        printf("File deleted successfully.\n");
    else
        perror("Error deleting file");
}

void readFile() {
    char filename[100], ch;
    printf("Enter file name to read: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    printf("\n--- File Content ---\n");
    while ((ch = fgetc(fp)) != EOF)
        putchar(ch);

    printf("\n---------------------\n");
    fclose(fp);
}

void writeFile() {
    char filename[100], data[500];
    printf("Enter file name to write: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "a");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    printf("Enter text to write (no spaces, or use underscores): ");
    scanf("%s", data);

    fprintf(fp, "%s\n", data);
    fclose(fp);

    printf("Data written successfully.\n");
}

void copyFile() {
    char src[100], dest[100];
    printf("Enter source file: ");
    scanf("%s", src);
    printf("Enter destination copy file: ");
    scanf("%s", dest);

    FILE *fs = fopen(src, "rb");
    if (!fs) {
        perror("Source file error");
        return;
    }

    FILE *fd = fopen(dest, "wb");
    if (!fd) {
        perror("Destination file error");
        fclose(fs);
        return;
    }

    char ch;
    while ((ch = fgetc(fs)) != EOF)
        fputc(ch, fd);

    fclose(fs);
    fclose(fd);

    printf("File copied successfully.\n");
}

void pasteFile() {
    char clipboard[100], dest[100];

    printf("Enter copied (source) file: ");
    scanf("%s", clipboard);
    printf("Enter location to paste (destination) file: ");
    scanf("%s", dest);

    FILE *fs = fopen(clipboard, "rb");
    if (!fs) {
        perror("Clipboard source error");
        return;
    }

    FILE *fd = fopen(dest, "wb");
    if (!fd) {
        perror("Paste destination error");
        fclose(fs);
        return;
    }

    char ch;
    while ((ch = fgetc(fs)) != EOF)
        fputc(ch, fd);

    fclose(fs);
    fclose(fd);

    printf("Paste completed.\n");
}

void truncateFile() {
    char filename[100];
    long size;

    printf("Enter file name to truncate: ");
    scanf("%s", filename);

    printf("Enter new size (in bytes): ");
    scanf("%ld", &size);

    if (truncate(filename, size) == 0)
        printf("File truncated successfully.\n");
    else
        perror("Error truncating file");
}

int main() {
    int choice;

    while (1) {
        printf("\n====== FILE OPERATIONS MENU ======\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Read File\n");
        printf("4. Write File\n");
        printf("5. Copy File\n");
        printf("6. Paste File\n");
        printf("7. Truncate File\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: createFile(); break;
        case 2: deleteFile(); break;
        case 3: readFile(); break;
        case 4: writeFile(); break;
        case 5: copyFile(); break;
        case 6: pasteFile(); break;
        case 7: truncateFile(); break;
        case 8: exit(0);
        default: printf("Invalid choice.\n");
        }
    }

    return 0;
}
