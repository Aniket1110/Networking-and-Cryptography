#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void trng(char* key, int n){
    srand(time(0));
    for(int i = 0 ; i < n ; i++) key[i] = (rand() % 26) + 'a';
}

void bitstream(char* source, int n, int* dest){
    for(int i = 0 ; i < n ; i++){
        int p = source[i]-'a';
        for(int j = 7 ; j >= 0 ; j--){
            int r = (p&1);
            p = p >> 1;
            dest[(i*8)+j] = r;
        }
    }
}

void printstream(int* src, int n){
    for(int i = 0 ; i < n ; i++) printf("%d", src[i]);
    printf("\n");
}

char* decrypt_char(int* src, int n, char* dest){
    for(int i = 0 ; i < n ; i++){
        int p = 1;
        int ans = 0;
        for(int j = 7 ; j >= 0 ; j--){
            ans += p*src[(i*8)+j];
            p = p << 1;
        }
        dest[i] = ans + 'a';
    }
    return dest;
}

int* otp_cipher_encrypt_decrypt(int* str, int* key, int n, int* cipher){
    for(int i = 0 ; i < n ; i++){
        //self-invertible xor
        cipher[i] = str[i] ^ key[i];
    }
    return cipher;
}

int main(){
    printf("Enter a String (lowercase & no spaces): ");
    char str[10000];
    scanf("%s", str);

    printf("\n-------------------OTP Cipher-------------------\n\n");

    //random key generation
    int n = strlen(str);
    char key[n];
    trng(key, n);
    printf("Key Generated: %s\n", key);

    int bitsrc[100000]; bitstream(str, n, bitsrc);
    printf("\nSource Bitstream: "); printstream(bitsrc, 8*n);
    int bitcip[100000];
    int bitkey[100000]; bitstream(key, n, bitkey);
    printf("\nKey Bitstream: "); printstream(bitkey, 8*n);
    
    int* ans = otp_cipher_encrypt_decrypt(bitsrc, bitkey, 8*n, bitcip);
    
    printf("\nOTP Cipher Bitstream: "); printstream(ans, 8*n);

    ans = otp_cipher_encrypt_decrypt(bitcip, bitkey, 8*n, bitsrc);

    printf("\nOTP Decrypt Bitstream: "); printstream(ans, 8*n);

    char dest[100000];
    char* output = decrypt_char(ans, n, dest);

    printf("\nOTP Decryption: %s\n", output);

    printf("--------------------------------------------------\n\n");

    return 0;
}

//convert file/english sentence to bitsream and then perform xor on otp(one time pad) cipher.
