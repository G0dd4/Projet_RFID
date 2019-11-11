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

#include "SRC/rfid_rc522.h"
#include "SRC/soft_lcd.h"
#include "SRC/bdd.h"

int main(){

	/**********************************
	 * Connexion à la base de données *
	 **********************************/
	if(connexion("127.0.0.1","yannis","aissaoui","RFID") == -1){
		printf("connexion BDD imposible \n");
		exit(EXIT_FAILURE);
	}
	printf("connexion BDD réussie\n");

	/********************************
	 * initialisation du module LCD *
	 ********************************/
	lcd_t * lcd;
	lcd = lcd_create(9,8,0x27,2);
	if(lcd == NULL){
		printf("error\n");
		return -1;
	}

	/*********************************
	 * initialisation du module RFID *
	 *********************************/
	initRC522();
	PCD_Init();

	/********************************
	 * initialisation des variables *
	 ********************************/
	int k=0, i, tab[10];
	char chaine[10];

	while(1){
		//on efface tous les caractères du module LCD
		lcd_clear(lcd);


		if(!PICC_IsNewCardPresent()){
			continue;
		}

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
		printf("\n");

		for(i=0;i<k;i++){
			sprintf(chaine,"%s%X",chaine,tab[i]);
		}
		/***************************************
		 * Déclaration de la variable requette *
		 * et initialisation				   *
		 ***************************************/
		char* requette;
		//création d'un tableau de char pour stocker la requête
		requette = malloc(53+strlen(chaine)+2);

		//on initialise toutes les cases à 0
		for(int i = 0;i < 53+strlen(chaine)+2;i++)
			requette[i]=0;
		/**********************************
		 * Construction de la requête sql *
		 **********************************/
		strcat(requette,"SELECT nom,prenom FROM utilisateur WHERE numBadge = '");
		strcat(requette, chaine);
		strcat(requette,"';");
		printf("%s\n",requette);

		//on position le curseur au coordonnées 0 0
		lcd_pos(lcd, 0, 0);
		/**************************************
		 * Envoi de la requête au serveur SQL *
		 **************************************/
		switch(recupBdd(requette)){
		//imposible
		case(-1):break;
		//si la fonction recupBdd nous renvoie -2 alors on affiche N°Badge Inconnue
		case(-2):lcd_print(lcd,"N badge inconnue");break;
		//si la fonction recupBdd nous renvoie -3 alors on affiche N°Badge Inconnue
		case(-3):lcd_print(lcd,"N badge inconnue");break;
		//si la fonction recupBdd nous renvoie -4 alors la requête est vide
		case(-4):printf("requette vide");break;
		//si la fonction recupBdd nous renvoie 0 alors on affiche bienvenue \n nom de la personne
		case(0):;lcd_print(lcd,"Bienvenue");lcd_pos(lcd, 1, 0);lcd_print(lcd,reponse(1));
		}
		free(requette);
		//temporisation de 3 secondes
		delay(3000);
		k=0;
	}
	return 0;
}

