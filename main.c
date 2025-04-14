/*UVM - Lógica y programación estructurada - Proyecto integrador*/
/*Prof. Aldo Rosales*/
/*Estudiante: ID:*/
/*Estudiante: ID:*/
/*Directivas del procesador*/
/*Son las únicas que no llevan ;*/
#include <stdio.h>
#include <string.h> // Para usar strcmp, strcpy
#include <ctype.h>  // Para usar tolower
#include <time.h>   // Para obtener el año actual para validación

/*Declaraciones globales*/
#define MAX_VIDEOGAMES 100

// Estructura para almacenar los datos de un videojuego
typedef struct {
    char name[50];
    char genre[30];     // Género del videojuego
    char platform[30];  // Plataforma principal
    int releaseYear;    // Año de lanzamiento
    int rating;         // Calificación del 1 al 10
} VideoGame;

// Arreglo global para el catálogo y contador global
VideoGame catalog[MAX_VIDEOGAMES];
int count = 0; // Indica la cantidad actual de videojuegos y la próxima posición libre

/* Prototipos de funciones */
void displayMenu();
void addVideoGame();
void deleteVideoGame();
void updateVideoGame();
void searchVideoGame();

/*Inicio del programa*/
int main() {
    int option;
    do {
        displayMenu();
        // Valida que se ingrese un número para la opción
        if (scanf("%d", &option) != 1) {
             printf("\nOpción inválida. Por favor ingrese un número del menú.\n");
             // Limpia el buffer de entrada en caso de error
             while (getchar() != '\n');
             option = 0; // Asigna un valor inválido para que el switch vaya a default
        }

        // Consume cualquier carácter restante en la línea (como Enter)
        // Especialmente importante después de leer números antes de leer cadenas
        while (getchar() != '\n');

        switch (option) {
            case 1:
                addVideoGame(); // Llama a la función de Agregar
                break;
            case 2:
                deleteVideoGame(); // Llama a la función de Eliminar
                break;
            case 3:
                updateVideoGame(); // Llama a la función de Modificar Videojuego
                break;
            case 4:
                searchVideoGame(); // Llama a la función de Buscar
                break;
            case 5:
                printf("\nSaliendo del programa...\n");
                break;
            default:
                // El mensaje de opción inválida se maneja durante la entrada si no es un número
                // Aquí se manejan los números fuera del rango esperado
                if (option != 0) { // Si la opción es 0, el error por no ser número ya se mostró
                   printf("\nOpción no válida. Por favor, elija una opción del 1 al 5.\n");
                }
                break;
        }
        // Pausa simple para permitir leer la salida antes de mostrar el menú de nuevo
        if (option != 5) {
            printf("\nPresione Enter para continuar...");
            // Espera a que el usuario presione Enter
            getchar(); // Espera el Enter
        }

    } while (option != 5); // El bucle continúa hasta que se elige la opción 5

    return 0; // Termina el programa
}

/**
 * @brief Agrega un nuevo videojuego al catálogo.
 * Solicita nombre, género, plataforma, año de lanzamiento y calificación, valida la entrada,
 * y lo guarda si hay espacio.
 */
void addVideoGame() {
    if (count >= MAX_VIDEOGAMES) {
        printf("El catálogo está lleno. No se pueden agregar más videojuegos.\n");
        return;
    }

    printf("\n--- Agregar Videojuego ---\n");
    VideoGame newGame; // Variable temporal para almacenar los datos

    printf("Ingrese el nombre del videojuego: ");
    scanf(" %[^\n]", newGame.name); // Lee hasta encontrar un salto de línea

    printf("Ingrese el género del videojuego: ");
    scanf(" %[^\n]", newGame.genre); // Lee hasta encontrar un salto de línea

    printf("Ingrese la plataforma principal del videojuego: ");
    scanf(" %[^\n]", newGame.platform); // Lee hasta encontrar un salto de línea

    // Obtener año actual para validación
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentYear = tm.tm_year + 1900;
    int year_temp = -1;

    // Validar año de lanzamiento
    while (year_temp < 1970 || year_temp > currentYear) { // Rango razonable
        printf("Ingrese el año de lanzamiento (%d-%d): ", 1970, currentYear);
        if (scanf("%d", &year_temp) != 1) {
             printf("Entrada inválida. Por favor ingrese un número.\n");
             while (getchar() != '\n'); // Limpiar buffer de entrada
             year_temp = -1; // Resetear para volver a pedir
        } else if (year_temp < 1970 || year_temp > currentYear) {
            printf("Año fuera de rango. Debe ser entre %d y %d.\n", 1970, currentYear);
        }
        // Limpiar buffer después de leer un número si la siguiente lectura es una cadena o carácter
         while (getchar() != '\n');
    }
    newGame.releaseYear = year_temp;

    int rating_temp = -1;
    // Validar que la calificación esté en el rango 1-10
    while (rating_temp < 1 || rating_temp > 10) {
        printf("Ingrese la calificación del videojuego (1-10): ");
        if (scanf("%d", &rating_temp) != 1) {
             printf("Entrada inválida. Por favor ingrese un número.\n");
             while (getchar() != '\n'); // Limpiar buffer de entrada
             rating_temp = -1; // Resetear para volver a pedir
        } else if (rating_temp < 1 || rating_temp > 10) {
            printf("Calificación fuera de rango. Debe ser entre 1 y 10.\n");
        }
        // Limpiar buffer después de leer un número
         while (getchar() != '\n');
    }
    newGame.rating = rating_temp;

    // Copia el juego nuevo al catálogo y aumenta el contador
    catalog[count] = newGame;
    printf("\nVideojuego agregado con éxito:\n");
    printf("  Nombre: %s\n", catalog[count].name);
    printf("  Género: %s\n", catalog[count].genre);
    printf("  Plataforma: %s\n", catalog[count].platform);
    printf("  Año: %d\n", catalog[count].releaseYear);
    printf("  Calificación: %d\n", catalog[count].rating);
    count++; // Incrementar el contador de videojuegos
}

/**
 * @brief Elimina un videojuego del catálogo.
 * Busca el videojuego por nombre, pide confirmación y reordena el arreglo.
 */
void deleteVideoGame() {
    if (count == 0) {
        printf("\nEl catálogo está vacío. No hay videojuegos para eliminar.\n");
        return;
    }

    char nameToDelete[50];
    printf("\n--- Eliminar Videojuego ---\n");
    printf("Ingrese el nombre del videojuego a eliminar: ");
    scanf(" %[^\n]", nameToDelete);
    while (getchar() != '\n'); // Limpiar buffer

    int foundIndex = -1;
    // Busca el videojuego en el catálogo
    for (int i = 0; i < count; i++) {
        // Usar strcasecmp para comparación insensible a mayúsculas/minúsculas podría ser útil
        // if (strcasecmp(catalog[i].name, nameToDelete) == 0) {
        if (strcmp(catalog[i].name, nameToDelete) == 0) {
            foundIndex = i;
            break; // Sale del bucle una vez encontrado
        }
    }

    // Caso 1: Videojuego encontrado
    if (foundIndex != -1) {
        printf("\nVideojuego encontrado:\n");
        printf("  Nombre: %s\n", catalog[foundIndex].name);
        printf("  Género: %s\n", catalog[foundIndex].genre);
        printf("  Plataforma: %s\n", catalog[foundIndex].platform);
        printf("  Año: %d\n", catalog[foundIndex].releaseYear);
        printf("  Calificación: %d\n", catalog[foundIndex].rating);

        char confirmation;
        printf("¿Estás seguro de que deseas eliminar este videojuego? (s/n): ");
        scanf(" %c", &confirmation); // El espacio antes de %c consume el salto de línea previo
        while (getchar() != '\n'); // Limpiar buffer

        if (tolower(confirmation) == 's') {
            // Realiza el reordenamiento del arreglo
            // Desplaza todos los elementos subsecuentes una posición hacia atrás
            for (int i = foundIndex; i < count - 1; i++) {
                catalog[i] = catalog[i + 1]; // Copia la estructura completa
            }
            count--; // Decrementa el contador de videojuegos
            printf("Videojuego eliminado correctamente.\n");
        } else {
            printf("Eliminación cancelada.\n");
        }
    }
    // Caso 2: Videojuego no encontrado
    else {
        printf("Videojuego '%s' no encontrado en el catálogo.\n", nameToDelete);
    }
}

/**
 * @brief Modifica los datos de un videojuego existente (excepto el nombre).
 * Busca por nombre, luego permite elegir qué campo actualizar.
 */
void updateVideoGame() {
     if (count == 0) {
        printf("\nEl catálogo está vacío. No hay videojuegos para modificar.\n");
        return;
    }

    char nameToUpdate[50];
    printf("\n--- Modificar Videojuego ---\n");
    printf("Ingrese el nombre del videojuego a modificar: ");
    scanf(" %[^\n]", nameToUpdate);
    while (getchar() != '\n'); // Limpiar buffer

    int foundIndex = -1;
    // Busca el videojuego
    for (int i = 0; i < count; i++) {
        if (strcmp(catalog[i].name, nameToUpdate) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("\nVideojuego encontrado:\n");
        printf("  Nombre: %s\n", catalog[foundIndex].name);
        printf("  Género: %s\n", catalog[foundIndex].genre);
        printf("  Plataforma: %s\n", catalog[foundIndex].platform);
        printf("  Año: %d\n", catalog[foundIndex].releaseYear);
        printf("  Calificación actual: %d\n", catalog[foundIndex].rating);

        int choice = 0;
        printf("\n¿Qué campo desea modificar?\n");
        printf("1. Género\n");
        printf("2. Plataforma\n");
        printf("3. Año de Lanzamiento\n");
        printf("4. Calificación\n");
        printf("5. Cancelar\n");
        printf("Seleccione una opción: ");

        if (scanf("%d", &choice) != 1) {
             printf("Entrada inválida. Operación cancelada.\n");
             while (getchar() != '\n'); // Limpiar buffer de entrada
             return; // Salir si la entrada no es un número
        }
        while (getchar() != '\n'); // Limpiar buffer después de leer el número

        switch(choice) {
            case 1: { // Modificar Género
                char newGenre[30];
                printf("Ingrese el nuevo género: ");
                scanf(" %[^\n]", newGenre);
                while (getchar() != '\n'); // Limpiar buffer
                strcpy(catalog[foundIndex].genre, newGenre);
                printf("Género actualizado correctamente.\n");
                break;
            }
            case 2: { // Modificar Plataforma
                char newPlatform[30];
                printf("Ingrese la nueva plataforma principal: ");
                scanf(" %[^\n]", newPlatform);
                 while (getchar() != '\n'); // Limpiar buffer
                strcpy(catalog[foundIndex].platform, newPlatform);
                printf("Plataforma actualizada correctamente.\n");
                break;
            }
            case 3: { // Modificar Año de Lanzamiento
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                int currentYear = tm.tm_year + 1900;
                int newYear = -1;
                // Validar año de lanzamiento
                while (newYear < 1970 || newYear > currentYear) {
                    printf("Ingrese el nuevo año de lanzamiento (%d-%d): ", 1970, currentYear);
                    if (scanf("%d", &newYear) != 1) {
                         printf("Entrada inválida. Por favor ingrese un número.\n");
                         while (getchar() != '\n'); // Limpiar buffer de entrada
                         newYear = -1; // Resetear para volver a pedir
                    } else if (newYear < 1970 || newYear > currentYear) {
                        printf("Año fuera de rango. Debe ser entre %d y %d.\n", 1970, currentYear);
                    }
                    while (getchar() != '\n'); // Limpiar buffer después de leer número
                }
                catalog[foundIndex].releaseYear = newYear;
                printf("Año de lanzamiento actualizado correctamente.\n");
                break;
            }
            case 4: { // Modificar Calificación
                int newRating = -1;
                int oldRating = catalog[foundIndex].rating;
                // Validar que la calificación esté en el rango 1-10
                while (newRating < 1 || newRating > 10) {
                    printf("Ingrese la nueva calificación del videojuego (1-10): ");
                    if (scanf("%d", &newRating) != 1) {
                         printf("Entrada inválida. Por favor ingrese un número.\n");
                         while (getchar() != '\n'); // Limpiar buffer de entrada
                         newRating = -1; // Resetear para volver a pedir
                    } else if (newRating < 1 || newRating > 10) {
                        printf("Calificación fuera de rango. Debe ser entre 1 y 10.\n");
                    }
                    while (getchar() != '\n'); // Limpiar buffer después de leer número
                }
                catalog[foundIndex].rating = newRating;
                printf("Calificación actualizada correctamente.\n");
                printf("La diferencia con la calificación anterior es: %d\n", newRating - oldRating);
                break;
            }
            case 5:
                printf("Modificación cancelada.\n");
                break;
            default:
                printf("Opción inválida. No se realizaron cambios.\n");
                break;
        }

        // Mostrar datos actualizados (opcional pero útil)
        if (choice >= 1 && choice <= 4) {
            printf("\nDatos actualizados del videojuego:\n");
            printf("  Nombre: %s\n", catalog[foundIndex].name);
            printf("  Género: %s\n", catalog[foundIndex].genre);
            printf("  Plataforma: %s\n", catalog[foundIndex].platform);
            printf("  Año: %d\n", catalog[foundIndex].releaseYear);
            printf("  Calificación: %d\n", catalog[foundIndex].rating);
        }

    } else {
        printf("Videojuego '%s' no encontrado.\n", nameToUpdate);
    }
}


/**
 * @brief Busca un videojuego por nombre en el catálogo y muestra sus detalles.
 */
void searchVideoGame() {
     if (count == 0) {
        printf("\nEl catálogo está vacío. No hay videojuegos para buscar.\n");
        return;
    }

    char nameToSearch[50];
    printf("\n--- Buscar Videojuego ---\n");
    printf("Ingrese el nombre del videojuego a buscar: ");
    scanf(" %[^\n]", nameToSearch);
    while (getchar() != '\n'); // Limpiar buffer

    int found = 0;
    // Busca el videojuego
    for (int i = 0; i < count; i++) {
        if (strcmp(catalog[i].name, nameToSearch) == 0) {
            printf("\nVideojuego encontrado:\n");
            printf("  Nombre: %s\n", catalog[i].name);
            printf("  Género: %s\n", catalog[i].genre);
            printf("  Plataforma: %s\n", catalog[i].platform);
            printf("  Año: %d\n", catalog[i].releaseYear);
            printf("  Calificación: %d\n", catalog[i].rating);
            found = 1;
            break; // Sale del bucle si se encuentra
        }
    }

    if (!found) {
        printf("Videojuego '%s' no encontrado en el catálogo.\n", nameToSearch);
        printf("¿Desea agregarlo? (s/n): ");
        char option;
        scanf(" %c", &option);
        if (option == 's' || option == 'S') {
            addVideoGame();
        }
    }
}

/**
 * @brief Muestra las opciones del menú principal (Interfaz de usuario en español).
 */
void displayMenu() {
    // Limpiar pantalla (opcional, depende del sistema operativo)
    // system("cls"); // Para Windows
    // system("clear"); // Para Linux/macOS
    printf("\n\n--- Catálogo de Videojuegos --- \n"); // Agregué saltos de línea para claridad
    printf("Menú principal (%d/%d juegos)\n", count, MAX_VIDEOGAMES); // Muestra ocupación
    printf("1. Agregar Videojuego\n");
    printf("2. Eliminar Videojuego\n");
    printf("3. Modificar Videojuego\n");
    printf("4. Buscar Videojuego\n");
    // printf("X. Mostrar Todos\n"); // Opción futura si se necesita
    printf("5. Salir\n");
    printf("-------------------------------\n");
    printf("Seleccione una opción: ");
}