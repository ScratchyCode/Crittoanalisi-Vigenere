/*
Coded by ScratchyCode;

Vigenere = Vernam se:
    - chiave lunga quanto il testo in chiaro
    - chiave con lettere casuali
    - chiave one time pad
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 10000

void checkChar(char *stringa);
void pulizia(char *stringa);

char const VIGENERE[26][26] = {
{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'},
{'B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A'},
{'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B'},
{'D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C'},
{'E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D'},
{'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E'},
{'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F'},
{'H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G'},
{'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H'},
{'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I'},
{'K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J'},
{'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K'},
{'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L'},
{'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M'},
{'O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N'},
{'P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'},
{'Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'},
{'R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q'},
{'S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R'},
{'T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S'},
{'U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'},
{'V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'},
{'W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V'},
{'X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W'},
{'Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X'},
{'Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y'},
};

int main(){
    unsigned long long int i, j = 0;
    int const asciiOffset = 65;
    char *testo = calloc(DIM,sizeof(char));
    char *chiave = calloc(DIM,sizeof(char));
    char *cifrato = calloc(DIM,sizeof(char));
    char *decifrato = calloc(DIM,sizeof(char));
    
    printf("Testo: ");
    fgets(testo,DIM,stdin);
    testo[strlen(testo)-1] = '\0';
    
    printf("Chiave: ");
    fgets(chiave,DIM,stdin);
    chiave[strlen(chiave)-1] = '\0';
    
    // controllo sui char (tutti maiuscoli)
    checkChar(testo);
    checkChar(chiave);
    
    // cifratura
    printf("\n");
    printf("Cifrato:\n");
    for(i=0; i<strlen(testo); i++){
        cifrato[i] = VIGENERE[testo[i] - asciiOffset][chiave[i%strlen(chiave)] - asciiOffset];
        printf("%c",cifrato[i]);
    }
    
    printf("\n");
    
    // decifratura
    printf("Decifrato:\n");
    for(i=0; i<strlen(cifrato); i++){
        // ricerco il char cifrato nella riga data dalla chiave per trovare l'indice j del testo in chiaro
        j = 0;
        while(VIGENERE[j][chiave[i%strlen(chiave)] - asciiOffset] != testo[i]){
            j++;
            if(j > 26) break;
        }
        decifrato[i] = VIGENERE[0][j];
        printf("%c",decifrato[i]);
    }
    printf("\n");
    
    // pulisco la memoria
    pulizia(testo);
    pulizia(chiave);
    pulizia(cifrato);
    pulizia(decifrato);
    i = 0;
    j = 0;
    free(testo);
    free(chiave);
    free(cifrato);
    free(decifrato);
    
    return 0;
}

void checkChar(char *stringa){
    unsigned long long int i;
    
    for(i=0; i<strlen(stringa); i++){
        if(stringa[i] < 65 || stringa[i] > 90){ // appartenenza alfabeto maiuscolo
            printf("Charset non valido!\nUscita...\n");
            exit(0);
        }
    }
    
    return;
}

void pulizia(char *stringa){
    unsigned long long int i;
    
    for(i=0; i<strlen(stringa); i++){
        stringa[i] = 0;
    }
    
    return;
}
