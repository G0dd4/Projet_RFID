#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void delay(int ms){
#ifdef WIN32
  Sleep(ms);
#else
  usleep(ms*1000);
#endif
}

#include "rfid_rc522.h"

int main(){
  initRC522();
  PCD_Init();
  int k=0,tab[50];
  char chaine[50];

  while(1){
    // Look for a card
    if(!PICC_IsNewCardPresent())
      continue;

    if( !PICC_ReadCardSerial())
      continue;

    // Print UID
    for(byte i = 0; i < uid.size; ++i){
      if(uid.uidByte[i] < 0x10){
    printf(" 0");
    printf("%X",uid.uidByte[i]);
    
    tab[k]=0; // on met un zéro avant d'écrire le chiffre en hexa
    tab[k+1]=uid.Byte[i]; // on met le chiffre en hexa après la case corresponant au zéro
    k=k+2; // incrément l'indice du 2ème tableau 
      }
      else{
    printf(" ");
    printf("%X", uid.uidByte[i]);
    
    tab[k]=uid.Byte[i]; // on écrit le nombre dans la correspondante à l'indice i 
    k=k+1; // incrémente l'indice du 2ème tableau
      }

    }
    sprintf(chaine,"\n%X%X%X%X%X%X%X",tab[0],tab[1],tab[2],tab[3],tab[4],tab[5],tab[6],tab[7]); // Convertion en chaine de caractères
    printf("%s",chaine); // Affichage de la chaine
    printf("\n");
    delay(1000);
    k=0;
  }
  return 0;
}
