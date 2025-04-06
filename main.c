/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.
  
  Alumnos: Vicente, Alberto
 
*******************************************************************************/
#include <stdio.h>
#include <string.h>

#define MAX_VIDEOGAMES 100

typedef struct {
    char name[50];
    int rating;
} VideoGame;

VideoGame catalog[MAX_VIDEOGAMES];
int count = 0;

void addVideoGame() {
    if (count < MAX_VIDEOGAMES) {
        printf("Ingrese el nombre del videojuego: ");
        scanf(" %[^\n]", catalog[count].name);
        printf("Ingrese la calificación del videojuego (1-10): ");
        scanf("%d", &catalog[count].rating);
        count++;
    } else {
        printf("El catálogo está lleno.\n");
    }
}

void classifyVideoGame() {
    char name[50];
    int newRating, oldRating, diff;
    printf("Ingrese el nombre del videojuego a clasificar: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < count; i++) {
        if (strcmp(catalog[i].name, name) == 0) {
            printf("Ingrese la nueva calificación del videojuego (1-10): ");
            scanf("%d", &newRating);
            oldRating = catalog[i].rating;
            catalog[i].rating = newRating;
            diff = newRating - oldRating;
            printf("La diferencia con la calificación anterior es: %d\n", diff);
            return;
        }
    }
    printf("Videojuego no encontrado.\n");
}

void searchVideoGame() {
    char name[50];
    printf("Ingrese el nombre del videojuego a buscar: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < count; i++) {
        if (strcmp(catalog[i].name, name) == 0) {
            printf("Videojuego encontrado: %s\n", catalog[i].name);
            return;
        }
    }
    printf("Videojuego no encontrado. ¿Desea agregarlo? (s/n): ");
    char option;
    scanf(" %c", &option);
    if (option == 's' || option == 'S') {
        addVideoGame();
    }
}

void displayMenu() {
    printf("Catálogo de Videojuegos\n");
    printf("1. Agregar Videojuego\n");
    printf("2. Clasificar Videojuego\n");
    printf("3. Modificar Calificación\n");
    printf("4. Buscar Videojuego\n");
    printf("5. Salir\n");
    printf("Seleccione una opción: ");
}

int main() {
    int option;
    do {
        displayMenu();
        scanf("%d", &option);
        switch (option) {
            case 1:
                addVideoGame();
                break;
            case 2:
                classifyVideoGame();
                break;
            case 3:
                classifyVideoGame();
                break;
            case 4:
                searchVideoGame();
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (option != 5);
    return 0;
}