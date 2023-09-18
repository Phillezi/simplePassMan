#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../include/AES.h"
#include "../include/base64.h"

#define PASSWORD_FILEPATH "./res/passwords.dat" // Default path, (from the out folder to the passwords.dat file)

char **getPasswords(int *nrOfPasswords, const char *key) {
    FILE *fp = fopen(PASSWORD_FILEPATH, "rb");
    (*nrOfPasswords) = 0;
    char **passwords = (char **) malloc(sizeof(char *));
    char buffer[1024];
    if(fp != NULL) {
        while(!feof(fp)) {
            fscanf(fp, "%1023[^\n]%*c", buffer);
            if(!strlen(buffer))
                continue;
            char *decoded = base64_decode(buffer);
            memset(buffer, 0, sizeof(buffer));
            decrypt(decoded, key, buffer);
            if(decoded)
                free(decoded);
            if(strlen(buffer)>0) {
                char **new_passwords = (char **) realloc(passwords, ((*nrOfPasswords)+1)*sizeof(char *));
                if(new_passwords){
                    passwords = new_passwords;
                    passwords[*nrOfPasswords] = (char *) malloc((strlen(buffer)+1) * sizeof(char));
                    if(passwords[*nrOfPasswords]){
                        strcpy(passwords[*nrOfPasswords], buffer);
                        (*nrOfPasswords)++;
                    }
                } else perror("COULD NOT REALLOC!\n");
                memset(buffer, 0, sizeof(buffer));
            }
            
        }
        fclose(fp);
    } else {
        perror("Failed to open the file\n");
    }
    return passwords;
}

void destroyPasswordsList(char **passwords, int nrOfPasswords) {
    if(passwords != NULL) {
        for(int i = 0; i < nrOfPasswords; i++) {
            free(passwords[i]);
        }
        free(passwords);
    }
}

void addPassword(const char *password, const char *key) {
    char encrypted[1024];
    encrypt(password, key, encrypted);
    char *encoded = base64_encode((const unsigned char *)encrypted, AES_BLOCK_SIZE);

    FILE *fp = fopen(PASSWORD_FILEPATH, "ab");
    if (fp != NULL) {
        fwrite(encoded, sizeof(char), strlen(encoded), fp);
        //fwrite(encrypted, sizeof(char), AES_BLOCK_SIZE, fp);
        fwrite("\n", sizeof(char), 1, fp);
        fclose(fp);
        printf("Password added Successfully\n");
    }
    else {
        perror("Failed to open the file\n");
    }
    if(encoded)
        free(encoded);
}

int putPasswordsInFile(const char *filename, const char *encryptionKey) {
    int nrOfPasswords = 0;
    char **list = getPasswords(&nrOfPasswords, encryptionKey);
    FILE *fp = fopen(filename, "w+");
    if(fp!=NULL) {
        for(int i = 0; i < nrOfPasswords; i++) {
            fprintf(fp, "%s\n", list[i]);
        }
        fclose(fp);
    } else {
        destroyPasswordsList(list, nrOfPasswords);
        return 1;
    }
    destroyPasswordsList(list, nrOfPasswords);
    return 0;
}

void viewPasswords(const char *encryptionKey) {
    int passListLen = 0;
    char **passList = getPasswords(&passListLen, encryptionKey);
    if(passListLen > 0) {
        printf("\n\nPasswords:\n");
        printf("__________________________\n");
    } else {
        printf("No passwords\n");
    }
    for (int i = 0; i < passListLen; i++) {
        printf("\t%d: %s\n", i + 1, passList[i]);
    }
    printf("__________________________\n\n");
    destroyPasswordsList(passList, passListLen);
}

void getPasswordToAdd(const char *encryptionKey) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    fflush(stdin);
    printf("\n\nEnter the password you want to add\n");
    printf("\t\t: ");
    scanf("%1023[^\n]%*c", buffer);
    addPassword(buffer, encryptionKey);
}

void menu(const char *encryptionKey) {
    int run = 1;
    int action = 0;
    while(run) {
        do {
        printf("Select action:\n\t1: Enter a password\n\t2: View Passwords\n\t3: QUIT\n\t\t: ");
        scanf("%d", &action);
        } while(action<1 || action > 3);
        switch(action) {
            case 1 : getPasswordToAdd(encryptionKey); break;
            case 2 : viewPasswords(encryptionKey); break;
            case 3 : run = 0; break;
            default: break;
        }
    }
}

void test(const char *encryptionKey) {
    char buffer[512];
    FILE *fp = fopen("res/testpass.txt", "r");
    if(fp != NULL) {
        while(!feof(fp)) {
            memset(buffer, 0, sizeof(buffer));
            fscanf(fp, " %511[^\n]*c", buffer);
            if(strlen(buffer)) {
                addPassword(buffer, encryptionKey);
            }
        }
        fclose(fp);
    }
}

// Example encryption key: "4BD34B2F2D3DB9AA2B80FB8B172654079AA11284A6EDDE4E37BC89A4CB9A76F3"
// Replace with your actual encryption key, you can run AES_Key_gen to generate a key

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <Encryption_key> [File_Location]\n", argv[0]);
        return 1;
    }

    const char *encryptionKey = argv[1];

    if (argc == 3) {
        const char *fileLocation = argv[2];
        printf("Encryption key: %s\nFile Location: %s\n", encryptionKey, fileLocation);
        if(putPasswordsInFile(fileLocation, encryptionKey)) {
            printf("ERROR: File wasnt found\n");
            return 1;
        }
    } else if (argc == 2) {
        printf("Encryption key: %s\n", encryptionKey);
        menu(encryptionKey);
    } else {
        printf("Usage: %s <Encryption_key> [File_Location]\n", argv[0]);
        return 1;
    }

    return 0;
}