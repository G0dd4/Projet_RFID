#include <stdio.h>
#include <stdlib.h>

int main()
{
    int tab[4]={12,20,20,12}; // Données qu'on reçoit du RFID
    int tab2[50];
    char chaine[50]; // Tableau qui va contenir la chaine de caractère
    int i,k=0;// i=indice de la case k= est un indice qui s'incrémente

    for(i = 0; i < 4; ++i){ // On regarde case par case jusqu'à Byte.size
      if(tab[i] < 0x10){ // Si le nombre de la case est supérieur à 10
        printf("0"); // On met un 0 avant
        printf("%X",tab[i]); // Puis on écrit le nombre en hexa
        tab2[k]=0; // on met un zéro avant d'écrire le chiffre en hexa
        tab2[k+1]=tab[i]; // on met le chiffre en hexa après la case corresponant au zéro
        k=k+2; // incrément l'indice du 2ème tableau 
      }
      else{
        printf("%X",tab[i]); // Sinon on écrit directement le nombre à 2 chiffre
        tab2[k]=tab[i]; // on écrit le nombre dans la correspondante à l'indice i 
        k=k+1; // incrémente l'indice du 2ème tableau
      }
    }

    sprintf(chaine,"\n%X%X%X%X%X%X",tab2[0],tab2[1],tab2[2],tab2[3],tab2[4],tab2[5],tab2[6]); // Convertion en chaine de caractères
    printf("%s",chaine); // Affichage de la chaine
    return 0;
}


