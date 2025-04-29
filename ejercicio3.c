#include <stdio.h>

int main() {
    int numeros[10]; 
    int suma = 0; 
    int resta = 0; 
    int multiplicacion = 1; 

    
    printf("Introduce 10 números:\n");
    for (int i = 0; i < 10; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &numeros[i]); 

        suma += numeros[i]; 
        if (i == 0) {
            resta = numeros[i]; 
        } else {
            resta -= numeros[i];
        }
        multiplicacion *= numeros[i]; 
    }

   
    printf("\nResultados:\n");
    printf("Suma: %d\n", suma);
    printf("Resta acumulada: %d\n", resta);
    printf("Multiplicación acumulada: %d\n", multiplicacion);

    return 0; 
}