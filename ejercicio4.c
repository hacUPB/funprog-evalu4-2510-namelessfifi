#include <stdio.h>

int main() {
    int primeros[5]; 
    int ultimos[5];  
    int combinados[10]; 
    
    printf("Introduce 10 números:\n");
    for (int i = 0; i < 10; i++) {
        int numero;
        scanf("%d", &numero); 

        
        if (i < 5) {
            primeros[i] = numero;
        } else { 
            ultimos[i - 5] = numero;
        }
    }

  
    for (int i = 0; i < 5; i++) {
        combinados[i] = primeros[i]; 
        combinados[i + 5] = ultimos[i]; 
    }

    
    printf("\nContenido del arreglo combinado:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d\n", combinados[i]);o
    }

    return 0; 
}