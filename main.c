#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)
#include <string.h>
#include <ctype.h> 
#define SIZE 51

void get_input(char* buffer);
void encrypt_decrypt(char* pass, char* key, int len);
void string_transfer(char* pass, char* encrypted, int size);
typedef struct passwords {
    char password[SIZE];
    char site[SIZE];
    int length;
} passwords;
int main(void)
{
    int input = 0;
    char buffer[SIZE];
    passwords* tmp = (passwords*)malloc(sizeof(passwords));
    char* key = (char*)malloc(SIZE * sizeof(char));
    char* key1 = (char*)malloc(SIZE * sizeof(char));
    char* primitive_pass = (char*)malloc(SIZE * sizeof(char));
    printf("Enter the master key for your passwords and STORE IT SOMEWHERE SAFE!:(max 50 characters)");
    get_input(key); 
    while (input != 5) {
        printf("Enter option number as below to choose an action\n1. Search for password\n2. Add new password\n");
        printf("3. Print your passwords of all sites\n4. Clear the password's list\n5. Quit the program\n");
        fgets(buffer, SIZE, stdin);
        sscanf(buffer, "%d", &input);
        if (input == 1) {
            FILE* read;
            char site_name[SIZE];
            int found = 0;
            printf("What is the site of the password you want to find?");
            get_input(site_name);
            read = fopen("passwords.txt", "rb");
            if (read == NULL) {
                printf("Cannot find such file!\n");
                exit(1);
            }
            while (fread(tmp, sizeof(passwords), 1, read)) {
                if (strcmp(tmp->site, site_name) == 0) {
                    printf("Enter master key:(max 50 characters)");
                    get_input(key1);
                    string_transfer(primitive_pass, tmp->password, tmp->length);
                    encrypt_decrypt(primitive_pass, key1, tmp->length);
                    puts(primitive_pass);
                    found = 1;
                }
            }
            memset(primitive_pass, '\0', sizeof(primitive_pass));
            fclose(read); 
            if (!found) {
                printf("Password not found! You haven't saved the password for this site.\n"); 
            }
        }
        else if (input == 2) {
            FILE* add;
            add = fopen("passwords.txt", "ab");
            printf("Enter the website name(max 50 characters):");
            get_input(tmp->site);
            printf("Enter the password for this site(max 50 characters):");
            get_input(tmp->password);
            tmp->length = (int)strlen(tmp->password);
            encrypt_decrypt(tmp->password, key, tmp->length);
            printf("Password is saved!\n");
            fwrite(tmp, sizeof(passwords), 1, add);
            fclose(add);
        }
        else if (input == 3) {
            FILE* read;
            read = fopen("passwords.txt", "rb");
            if (read == NULL) {
                printf("Cannot find such file!\n");
                exit(1);
            }
            printf("Enter master key:(max 50 characters)");
            get_input(key1);
            printf("%-50s%-50s\n", "Site", "Password");
            while (fread(tmp, sizeof(passwords), 1, read)) {
                string_transfer(primitive_pass, tmp->password, tmp->length);
                encrypt_decrypt(primitive_pass, key1, tmp->length);
                printf("%-50s%-50s\n", tmp->site, primitive_pass);
                memset(primitive_pass, '\0', sizeof(primitive_pass));
            }
            fclose(read);
        }
        else if (input == 4) {
            FILE* clear;
            clear = fopen("passwords.txt", "w");
            printf("Your passwords are removed.\n");
            fclose(clear);
        }
        else if (input == 5) {
            printf("Quitting the program...\n");
        }
        else {
            printf("Invalid input!\n");
        }
    }
    free(tmp);
    free(key);
    free(key1);
    free(primitive_pass);
    return 0;
}

void get_input(char *buffer) {
    int count;
    do {
        count = 0;
        do {
            fgets(buffer, SIZE, stdin);
            count++;
        } while (strchr(buffer, '\n') == NULL);
        if (count > 1) {
            fputs("Try again, too long!", stdout);
        }
    } while (count > 1);
    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }
}

void encrypt_decrypt(char* pass, char* key, int len) {
    int a = 0;
    for (int i = 0; i < len; i++) {
        pass[i] = pass[i] ^ key[a];
        //puts(encryt);
        a++;
        if (a == (int)strlen(key)) {
            a = 0;
        }
        if (i == (len - 1)) {
            pass[i + 1] = '\0';
        }
    }
}

void string_transfer(char* pass, char* encrypted, int size) {
    for (int i = 0; i <= size; i++) {
        pass[i] = encrypted[i];
    }
}