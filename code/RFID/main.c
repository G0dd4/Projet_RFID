#include <stdio.h>
#include <stdlib.h>

int main()
{
    int tab[4]={2,18,0,88}; // Données qu'on reçoit du RFID
    int tab2[50];
    char chaine[50]; // Tableau qui va contenir la chaine de caractères
    int i;

    for(i = 0; i < 4; ++i){ // On regarde case par case jusqu'à Byte.size
      if(tab[i] < 0x10){ // Si le nombre de la case est supérieur à 10
        printf("0"); // On met un 0 avant
        printf("%X",tab[i]); // Puis on écrit le nombre en hexa
      }
      else{
        printf("%X",tab[i]); // Sinon on écrit directement le nombre à 2 chiffres
      }
    }

    sprintf(chaine,"\n%x%x%x%x",tab[0],tab[1],tab[2],tab[3]); // Convertion en chaine de caractères
    printf("%s",chaine); // Affichage de la chaine
    return 0;
}

