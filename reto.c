#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void mostrar_menu() {
    puts("\nMENÚ");
    puts("1. Ver estadísticas");
    puts("2. Ver frecuencia de vocales");
    puts("3. Reemplazar palabra");
    puts("4. Guardar resultados");
    puts("0. Salir");
    printf("Opción: ");
}


char *leer_archivo(const char *nombre, long *tam);
void  calcular_estadisticas(const char *txt, long tam,
                            long *caracteres, long *palabras,
                            long *espacios,   long *lineas);
void  contar_vocales(const char *txt, long tam, long v[5]);
char *reemplazar_palabra(const char *txt,
                         const char *buscada,
                         const char *nueva,
                         long *nuevo_tam);
void  guardar_resultados(const char *nombre,
                         long caracteres, long palabras,
                         long espacios,   long lineas,
                         long v[5], const char *texto);


int main(void)
{
    char nombre_in[80], nombre_out[80];
    char palabra_busca[50], palabra_nueva[50];
    char *texto = NULL, *texto_mod = NULL;
    long tam = 0, tam_mod = 0;
    long caracteres, palabras, espacios, lineas;
    long voc[5]; /* a,e,i,o,u */
    int opcion, hay_reemplazo = 0;

    printf("Nombre del archivo de entrada (.txt): ");
    scanf("%79s", nombre_in);

    texto = leer_archivo(nombre_in, &tam);
    if (!texto) return 1;

    do {
        mostrar_menu();
        if (scanf("%d", &opcion) != 1) opcion = 0;

        switch (opcion) {
        case 1:
            calcular_estadisticas(texto, tam,
                                   &caracteres, &palabras,
                                   &espacios,   &lineas);
            printf("\nCaracteres: %ld\nPalabras: %ld\nEspacios: %ld\nLineas: %ld\n",
                   caracteres, palabras, espacios, lineas);
            break;

        case 2:
            contar_vocales(texto, tam, voc);
            printf("\na: %ld\ne: %ld\ni: %ld\no: %ld\nu: %ld\n",
                   voc[0], voc[1], voc[2], voc[3], voc[4]);
            break;

        case 3:
            printf("Palabra a buscar: ");
            scanf("%49s", palabra_busca);
            printf("Palabra nueva: ");
            scanf("%49s", palabra_nueva);
            texto_mod = reemplazar_palabra(texto, palabra_busca,
                                           palabra_nueva, &tam_mod);
            if (texto_mod) {
                hay_reemplazo = 1;
                puts("Reemplazo completado.");
            }
            break;

        case 4:
            printf("Nombre del archivo de salida: ");
            scanf("%79s", nombre_out);
            if (hay_reemplazo) {
                calcular_estadisticas(texto_mod, tam_mod,
                                       &caracteres, &palabras,
                                       &espacios,   &lineas);
                contar_vocales(texto_mod, tam_mod, voc);
                guardar_resultados(nombre_out, caracteres, palabras,
                                   espacios, lineas, voc, texto_mod);
            } else {
                calcular_estadisticas(texto, tam,
                                       &caracteres, &palabras,
                                       &espacios,   &lineas);
                contar_vocales(texto, tam, voc);
                guardar_resultados(nombre_out, caracteres, palabras,
                                   espacios, lineas, voc, texto);
            }
            puts("Resultados guardados.");
            break;

        case 0:
            puts("¡Adiós!");
            break;

        default:
            puts("Opción inválida.");
        }
    } while (opcion != 0);

    free(texto);
    free(texto_mod);
    return 0;
}