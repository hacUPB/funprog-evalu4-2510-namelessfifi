#include <stdio.h>

int main() {
    float notas[4][4] = {
        {0.3, 0.3, 0.4, 0},  
        {4.5, 3.8, 4.0, 0},
        {2.5, 3.0, 2.8, 0},
        {3.9, 4.1, 4.5, 0}
    };

    for (int i = 1; i < 4; i++)
        for (int j = 0; j < 3; j++)
            notas[i][3] += notas[i][j] * notas[0][j];

    for (int i = 1; i < 4; i++)
        printf("Estudiante %d: %.2f\n", i, notas[i][3]);

    return 0;
}
