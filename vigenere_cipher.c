#include <stdio.h>
#include <string.h>

int additive_inverse(int num, int m){
    while(num < 0){
        num += m;
    }
	return (m - num%m) % m;
}

char* vigenere_cipher_encrypt(char* str, char* key, int n){
    int x = 0;
    for(int i = 0 ; i < strlen(str) ; i++){
        str[i] = (((str[i] - 'a') + (key[x] - 'a')) % 26) + 'a';
        x = (x+1) % n;
    }
    return str;
}

char* vigenere_cipher_decrypt(char* cipher, char* key, int n){
    int x = 0;
    for(int i = 0 ; i < strlen(cipher) ; i++){
        int k = additive_inverse((key[x] - 'a'), 26);
        cipher[i] = (((cipher[i] - 'a') + k) % 26) + 'a';
        x = (x+1) % n;
    }
    return cipher;
}

int main(){
    printf("Enter a String: ");
    char str[10000]; char key[10000];
    scanf("%s", str);

    printf("\n-------------------Vigenere Cipher-------------------\n\n");

    printf("Enter Vigenere key: ");
    scanf("%s", key);

    int keylen = strlen(key);
    
    char* ans = vigenere_cipher_encrypt(str, key, keylen);
    
    printf("\nVigenere Cipher: %s\n\n", ans);

    ans = vigenere_cipher_decrypt(ans, key, keylen);

    printf("Vigenere Decrypt: %s\n\n", ans);

    printf("--------------------------------------------------\n\n");

    return 0;
}
