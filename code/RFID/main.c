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
  int k=0, i, tab[10];
  char chaine[10];

  while(1){
    // Look for a card
    if(!PICC_IsNewCardPresent())
      continue;

    if( !PICC_ReadCardSerial())
      continue;
    
    // Initialisation tableau (à mettre dans une fonction)
    for (i=0; i<10; i++){
      tab[i]=0;
      chaine[i]=0;
    }
    // Print UID
    for(byte i = 0; i < uid.size; ++i){
      if(uid.uidByte[i] < 0x10){
    printf("0");
    printf("%X ",uid.uidByte[i]);
        
    // Stockage dans le buffer
    tab[k]=0; // on met un zéro avant d'écrire le chiffre en hexa
    tab[k+1]=uid.uidByte[i]; // on met le chiffre en hexa après la case corresponant au zéro
    k=k+2; // incrément l'indice du 2ème tableau 
      }
      
      else{
    // Print UID 
    printf("%X ", uid.uidByte[i]);
        
    // Stockage dans le buffer
    tab[k]=uid.uidByte[i]; // on écrit le nombre dans la correspondante à l'indice i 
    k=k+1; // incrémente l'indice du 2ème tableau
      }

    }
    // Création de la chaine de caractère
    for(i=0;i<k;i++){
    sprintf(chaine,"%s%X",chaine,tab[i]); 
    }
    printf("%s",chaine); // Affichage de la chaine (pour test)
    printf("\n");
    delay(1000);
    k=0;
  }
  return 0;
}
