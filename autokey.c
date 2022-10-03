#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#include "functions.h"
#define MOD 26

void encrypt(char *s, char a, char *k)
{
    int len = strlen(s);

    k[0] = a;
    for (int i = 1; i < len; i++)
    {
        k[i] = s[i - 1];
    }
    k[len] = '\0';

    printf("  Key:\n");
    printf("    ");
    for (int i = 0; i < len; i++)
    {
        printf(" %c  ", k[i]);
    }
    printf("\n    ");
    for (int i = 0; i < len; i++)
    {
        printf("%2d  ", k[i] - 'A');
    }
    printf("\n\n");

    for (int i = 0; i < len; i++)
    {
        char c = s[i];
        int c_n = c - 'A';
        char r = k[i];
        int r_n = r - 'A';
        int add_n = c_n + r_n;
        int enc_n = mod_26(add_n);
        char enc = enc_n + 'A';
        s[i] = enc;
    }
}

void decrypt(char *s, char *k)
{
    int len = strlen(k);

    for (int i = 0; i < len; i++)
    {
        char c = s[i];
        int c_n = c - 'A';
        char r = k[i];
        int r_n = r - 'A';
        int sub_n = c_n - r_n;
        int enc_n = mod_26(sub_n);
        char enc = enc_n + 'A';
        s[i] = enc;
    }
}

int main(int argc, char *argv[])
{
    char s[256];
    char a;
    char k[256];

    int repeat;
    do
    {
        printf("Enter the plaintext (A-Z) to encrypt: ");
        scanf("%s", s);
        repeat = 0;
        for (int i = 0; s[i] != '\0'; i++)
        {
            if (s[i] < 'A' || s[i] > 'Z')
            {
                printf("  Invalid string, retry\n");
                repeat = 1;
                break;
            }
        }
    } while (repeat);
    do
    {
        printf("Enter auto key: ");
        scanf(" %c", &a);
        repeat = 0;
        if (a < 'A' || a > 'Z')
        {
            printf("  Invalid key, retry\n");
            repeat = 1;
            break;
        }
    } while (repeat);
    encrypt(s, a, k);
    printf("\nEncrypted string: %s\n", s);
    decrypt(s, k);
    printf("\nDecrypted string: %s\n", s);
    printf("\n");
}
