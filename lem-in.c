#include <stdio.h>
#include <stdlib.h>

int main()
{

    int number_of_ants;
    FILE *fichier = NULL;
    int caractereActuel = 0;

    fichier = fopen("../subject.map", "r");

    if (fichier != NULL)
    {
        caractereActuel = fgetc(fichier); // On lit le caractère
        while (caractereActuel != EOF)
        {
            printf("%c", caractereActuel);    // On l'affiche
            caractereActuel = fgetc(fichier); // On lit le caractère
        }

        fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }
}
