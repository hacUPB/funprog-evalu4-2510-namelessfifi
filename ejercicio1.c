#include <stdio.h>

int main() {
    int numeros[10]; 
    
    for (int i = 0; i < 10; i++) {
        numeros[i] = 11 + i;
    }

    printf("Números en orden descendente:\n");
    for (int i = 9; i >= 0; i--) { 
        printf("%d\n", numeros[i]);
    }

    return 0; 
}