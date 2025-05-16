#include <stdio.h>

int main() {
    int pares[5]; 

    
    for (int i = 0; i < 5; i++) {
        pares[i] = 2 + (i * 2); 
    }

    
    printf("Números pares desde 2 hasta 10 en orden ascendente:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d\n", pares[i]); 
    }

    return 0; 
}