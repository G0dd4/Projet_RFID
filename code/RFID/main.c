#include <stdio.h>
#include <stdlib.h>

int main()
{
    int tab[4]={12,20,20,12}; // Données qu'on reçoit du RFID
    int tab2[50];
    char chaine[50]; // Tableau qui va contenir la chaine de caractère
    int i,k=0;

    for(i = 0; i < 4; ++i){ // On regarde case par case jusqu'à Byte.size
      if(tab[i] < 0x10){ // Si le nombre de la case est supérieur à 10
        printf("0"); // On met un 0 avant
        printf("%X",tab[i]); // Puis on écrit le nombre en hexa
        tab2[k]=0;
        tab2[k+1]=tab[i];
        k=k+2;
      }
      else{
        printf("%X",tab[i]); // Sinon on écrit directement le nombre à 2 chiffre
        tab2[k]=tab[i];
        k=k+1;
      }
    }

    sprintf(chaine,"\n%X%X%X%X%X%X",tab2[0],tab2[1],tab2[2],tab2[3],tab2[4],tab2[5],tab2[6]); // Convertion en chaine de caractères
    printf("%s",chaine); // Affichage de la chaine
    return 0;
}


