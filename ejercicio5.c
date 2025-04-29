#include <stdio.h>

int main() {
    float notas[24] = {2.5, 3.0, 4.2, 3.8, 1.9, 3.5, 2.7, 4.0,
                       3.3, 2.2, 4.5, 3.6, 3.9, 1.8, 4.1, 3.1,
                       2.8, 3.7, 3.4, 4.8, 3.2, 2.5, 4.0, 3.0};
    int i, aprobados = 0, reprobados = 0, notaAlta = 0;
    float suma = 0;

    for (i = 0; i < 24; i++) {
        suma += notas[i];
        if (notas[i] >= 4) notaAlta++;
        if (notas[i] >= 3) aprobados++;
        else reprobados++;
    }

    printf("Promedio: %.2f\nAprobados: %d\nReprobados: %d\nNotas >= 4: %d\n",
           suma / 24, aprobados, reprobados, notaAlta);
    return 0;
}
