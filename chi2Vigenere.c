// Coded by Pietro Squilla
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

// frequenze lettere italiano
double frequenze_italiano[26] = {
    11.74, 0.92, 4.50, 3.73, 11.79, 0.95, 1.64, 1.54, 11.28, 0.00, 
    0.00, 6.51, 2.51, 6.88, 9.83, 3.05, 0.51, 6.37, 4.98, 5.63, 
    3.01, 2.10, 0.00, 0.00, 0.00, 0.49
};

void frequenza(char *s, int *f){
    for(int i = 0; i < 26; i++)
        f[i] = 0;
    
    for(int i = 0; s[i] != '\0'; i++){
        if(isalpha(s[i]))
            f[s[i]-'A']++;
    }
}

double indice_di_coincidenza(char *s){
    int f[26] = {0};
    int len = 0;
    
    for(int i = 0; s[i] != '\0'; i++){
        if(isalpha(s[i])){
            f[s[i]-'A']++;
            len++;
        }
    }
    
    double ic = 0;
    for(int i = 0; i < 26; i++)
        ic += f[i]*(f[i]-1);
    
    return ic / (len*(len-1));
}

int trova_lunghezza_chiave(char *testo_cifrato, int max_lunghezza_chiave){
    double ic_italiano = 0.073;
    double min_diff = DBL_MAX;
    int min_n = 1;
    
    for(int n = 1; n <= max_lunghezza_chiave; n++){
        double ic_totale = 0;
        
        for(int i = 0; i < n; i++){
            char s[strlen(testo_cifrato)/n + 2];
            int j;
            
            for(j = 0; i + j*n < strlen(testo_cifrato); j++)
                s[j] = testo_cifrato[i + j*n];
            s[j] = '\0';
            
            ic_totale += indice_di_coincidenza(s);
        }
        
        double ic_medio = ic_totale / n;
        double diff = fabs(ic_medio - ic_italiano);
        
        if(diff < min_diff){
            min_diff = diff;
            min_n = n;
        }
    }
    
    return min_n;
}

double chi_quadrato(int *osservato, double *atteso, int n){
    double chi = 0;
    
    for(int i = 0; i < 26; i++)
        chi += (osservato[i] - n * atteso[i]/100.0) * (osservato[i] - n * atteso[i]/100.0) / (n * atteso[i]/100.0);
    
    return chi;
}

char *trova_chiave(char *testo_cifrato, int lunghezza_chiave){
    char *chiave = malloc((lunghezza_chiave + 1) * sizeof(char));
    int n = strlen(testo_cifrato);
    
    for(int i = 0; i < lunghezza_chiave; i++){
        char s[n/lunghezza_chiave + 2];
        int j;
        
        for(j = 0; i + j*lunghezza_chiave < n; j++)
            s[j] = testo_cifrato[i + j*lunghezza_chiave];
        s[j] = '\0';
        
        int f[26];
        frequenza(s, f);
        
        double min_chi = 1.0/0.0;
        int min_p = 0;
        
        for(int p = 0; p < 26; p++){
            int fp[26];
            for(int k = 0; k < 26; k++)
                fp[(k+p)%26] = f[k];
            double chi = chi_quadrato(fp, frequenze_italiano, n);  // Passare 'n' invece di 'j'
            if(chi < min_chi){
                min_chi = chi;
                min_p = p;
            }
        }
        
        chiave[i] = 'A' + min_p;
    }
    
    chiave[lunghezza_chiave] = '\0';
    return chiave;
}

char *decifra_testo(char *testo_cifrato, char *chiave){
    char *testo_in_chiaro = malloc((strlen(testo_cifrato) + 1) * sizeof(char));
    int lunghezza_chiave = strlen(chiave);
    
    for(int i = 0; i < strlen(testo_cifrato); i++)
        testo_in_chiaro[i] = ((testo_cifrato[i] - 'A') - (chiave[i%lunghezza_chiave] - 'A') + 26) % 26 + 'A';
    
    testo_in_chiaro[strlen(testo_cifrato)] = '\0';
    
    return testo_in_chiaro;
}

int testo_e_maiuscolo(char *s){
    
    for(int i = 0; s[i] != '\0'; i++){
        if(islower(s[i]) || !isalpha(s[i]))
            return 0;
    }
    
    return 1;
}

int main(){
    // lunghezza massima della chiave
    int max_lunghezza_chiave = 6;
    
    // testo cifrato
    char testo_cifrato[] = "GTEBQYPWGAIFRNPVZZNDMNVVTXZEAAPTWVAXEVNVICWBIPEIFTHPPPHMBYNDVZGUETFSSURKMBNECIFOPZWHTIDXVAFMEFTEYDNLYYKUIUFMADMDXBAPWYAGEYHBLEWYAGLPDMAESEUAL";
    
    if(!testo_e_maiuscolo(testo_cifrato)){
        printf("Errore: il testo deve essere tutto maiuscolo.\n");
        return 1;
    }
    
    int lunghezza_chiave = trova_lunghezza_chiave(testo_cifrato, max_lunghezza_chiave);
    printf("Lunghezza chiave stimata: %d\n", lunghezza_chiave);
    
    char *chiave = trova_chiave(testo_cifrato, lunghezza_chiave);
    printf("Chiave stimata:\n%s\n", chiave);
    
    char *testo_in_chiaro = decifra_testo(testo_cifrato, chiave);
    printf("Testo decrittato:\n%s\n", testo_in_chiaro);
    
    free(chiave);
    free(testo_in_chiaro);
    
    return 0;
}

