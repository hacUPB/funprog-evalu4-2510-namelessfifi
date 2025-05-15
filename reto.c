#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void mostrarMenu() {
    printf("\n--- MENÚ DE ANÁLISIS DE TEXTO ---\n");
    printf("1. Mostrar estadísticas del texto\n");
    printf("2. Mostrar frecuencia de vocales\n");
    printf("3. Reemplazar palabra\n");
    printf("4. Guardar resultados en archivo\n");
    printf("5. Salir\n");
    printf("Seleccione una opción: ");
}

//  memoria dinámica

char* cargarArchivo(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        perror("Error al abrir el archivo.\n");
        return NULL;
    }

    fseek(archivo, 0, SEEK_END);
    long tamaño = ftell(archivo);
    rewind(archivo);

  
    char* buffer = (char*)malloc((tamaño + 1) * sizeof(char));
    if (!buffer) {
        perror("Error al asignar memoria.\n");
        fclose(archivo);
        return NULL;
    }

   
    fread(buffer, sizeof(char), tamaño, archivo);
    buffer[tamaño] = '\0';  

    fclose(archivo);
    return buffer;
}