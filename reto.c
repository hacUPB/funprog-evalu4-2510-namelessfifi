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
void  calcular_estadisticas(const char *txt, long tam, long *caracteres, long *palabras, long *espacios, long *lineas);
void  contar_vocales(const char *txt, long tam, long v[5]);
char *reemplazar_palabra(const char *txt, const char *buscada, const char *nueva, long *nuevo_tam);
void  guardar_resultados(const char *nombre, long caracteres, long palabras, long espacios, long lineas, long v[5], const char *texto);

int main(void)
{
    char nombre_in[80], nombre_out[80];
    char palabra_busca[50], palabra_nueva[50];
    char *texto = NULL, *texto_mod = NULL;
    long tam = 0, tam_mod = 0;
    long caracteres, palabras, espacios, lineas;
    long voc[5];
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
            calcular_estadisticas(texto, tam, &caracteres, &palabras, &espacios, &lineas);
            printf("\nCaracteres: %ld\nPalabras: %ld\nEspacios: %ld\nLineas: %ld\n", caracteres, palabras, espacios, lineas);
            break;
        case 2:
            contar_vocales(texto, tam, voc);
            printf("\na: %ld\ne: %ld\ni: %ld\no: %ld\nu: %ld\n", voc[0], voc[1], voc[2], voc[3], voc[4]);
            break;
        case 3:
            printf("Palabra a buscar: ");
            scanf("%49s", palabra_busca);
            printf("Palabra nueva: ");
            scanf("%49s", palabra_nueva);
            texto_mod = reemplazar_palabra(texto, palabra_busca, palabra_nueva, &tam_mod);
            if (texto_mod) {
                hay_reemplazo = 1;
                puts("Reemplazo completado.");
            }
            break;
        case 4:
            printf("Nombre del archivo de salida: ");
            scanf("%79s", nombre_out);
            if (hay_reemplazo) {
                calcular_estadisticas(texto_mod, tam_mod, &caracteres, &palabras, &espacios, &lineas);
                contar_vocales(texto_mod, tam_mod, voc);
                guardar_resultados(nombre_out, caracteres, palabras, espacios, lineas, voc, texto_mod);
            } else {
                calcular_estadisticas(texto, tam, &caracteres, &palabras, &espacios, &lineas);
                contar_vocales(texto, tam, voc);
                guardar_resultados(nombre_out, caracteres, palabras, espacios, lineas, voc, texto);
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

char *leer_archivo(const char *nombre, long *tam)
{
    FILE *fp = fopen(nombre, "rb");
    char *buf;
    if (!fp) return NULL;
    fseek(fp, 0, SEEK_END);
    *tam = ftell(fp);
    rewind(fp);

    buf = (char *)malloc((*tam + 1) * sizeof(char));
    if (!buf) {
        fclose(fp);
        return NULL;
    }
    fread(buf, 1, *tam, fp);
    buf[*tam] = '\0';
    fclose(fp);
    return buf;
}

void calcular_estadisticas(const char *txt, long tam, long *car, long *pal, long *esp, long *lin)
{
    int en_palabra = 0;
    *car = *pal = *esp = *lin = 0;

    for (long i = 0; i < tam; i++) {
        char c = txt[i];
        if (c != '\n') (*car)++;
        if (isspace((unsigned char)c)) {
            if (c == ' ') (*esp)++;
            if (c == '\n') (*lin)++;
            en_palabra = 0;
        } else {
            if (!en_palabra) {
                (*pal)++;
                en_palabra = 1;
            }
        }
    }
    if (tam > 0 && txt[tam-1] != '\n') (*lin)++;
}

void contar_vocales(const char *txt, long tam, long v[5])
{
    for (int i = 0; i < 5; i++) v[i] = 0;
    for (long i = 0; i < tam; i++) {
        char c = tolower((unsigned char)txt[i]);
        if (c == 'a') v[0]++;
        else if (c == 'e') v[1]++;
        else if (c == 'i') v[2]++;
        else if (c == 'o') v[3]++;
        else if (c == 'u') v[4]++;
    }
}

char *reemplazar_palabra(const char *txt, const char *busca, const char *nueva, long *nuevo_tam)
{
    size_t len_orig = strlen(busca);
    size_t len_new  = strlen(nueva);
    size_t extra    = 0;
    const char *tmp = txt;

    if (len_orig == 0) return NULL;

    while ((tmp = strstr(tmp, busca))) {
        extra++;
        tmp += len_orig;
    }
    if (extra == 0) return NULL;

    *nuevo_tam = strlen(txt) + extra * (len_new - len_orig);
    char *res = (char *)malloc(*nuevo_tam + 1);
    if (!res) return NULL;

    const char *p = txt;
    char *q = res;
    while ((tmp = strstr(p, busca))) {
        size_t bytes = tmp - p;
        memcpy(q, p, bytes);        q += bytes;
        memcpy(q, nueva, len_new);  q += len_new;
        p = tmp + len_orig;
    }
    strcpy(q, p);
    return res;
}

void guardar_resultados(const char *nombre, long car, long pal, long esp, long lin, long v[5], const char *texto)
{
    FILE *fp = fopen(nombre, "w");
    if (!fp) return;

    fprintf(fp, "=== Estadísticas ===\n");
    fprintf(fp, "Caracteres: %ld\n", car);
    fprintf(fp, "Palabras  : %ld\n", pal);
    fprintf(fp, "Espacios  : %ld\n", esp);
    fprintf(fp, "Líneas    : %ld\n\n", lin);

    fprintf(fp, "=== Frecuencia de vocales ===\n");
    fprintf(fp, "a: %ld\ne: %ld\ni: %ld\no: %ld\nu: %ld\n\n", v[0], v[1], v[2], v[3], v[4]);

    fprintf(fp, "=== Texto (posible reemplazo aplicado) ===\n");
    fputs(texto, fp);
    fclose(fp);
}
