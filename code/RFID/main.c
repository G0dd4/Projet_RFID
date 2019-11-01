#include <stdio.h>
#include <stdlib.h>

int main()
{
    int tab[4]={2,18,0,88};
    int tab2[50];
    char chaine[50];
    int i;

    for(i = 0; i < 4; ++i){
      if(tab[i] < 0x10){
        printf("0");
        printf("%X",tab[i]);
      }
      else{
      //  printf(" ");
        printf("%X",tab[i]);
      }
    }

    sprintf(chaine,"\n%x%x%x%x",tab[0],tab[1],tab[2],tab[3]);
    printf("%s",chaine);
    return 0;
}

