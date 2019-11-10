/*
 * ajout.c
 *
 *  Created on: 19 oct. 2019
 *      Author: yannis
 */
#include "ajout.h"
#include <glib-2.0/glib.h>


void initAjout(GtkBuilder* builder){
	mainWindow->ajout.m_button_ajouter = gtk_builder_get_object(builder,"m_buton_ajouterA");
	mainWindow->ajout.m_button_effacer = gtk_builder_get_object(builder,"m_buton_effacerA");
	mainWindow->ajout.m_button_getLast = gtk_builder_get_object(builder,"m_buton_getLastA");
	mainWindow->ajout.m_lineEdit_prenom = gtk_builder_get_object(builder,"m_lineEdit_prenomA");
	mainWindow->ajout.m_lineEdit_nom = gtk_builder_get_object(builder,"m_lineEdit_nomA");
	mainWindow->ajout.m_lineEdit_NB = gtk_builder_get_object(builder,"m_lineEdit_nbA");
	mainWindow->ajout.m_textView_log = gtk_builder_get_object(builder,"m_textView_logA");
	mainWindow->ajout.m_data = gtk_text_buffer_new (NULL);

}

void ajouterUser(){
	char* nom;
	char* prenom;
	char* numBadge;
	char* requette;
	char* data;


	if(verifChamp() == -1){
		gtk_text_buffer_set_text (mainWindow->ajout.m_data, "Un champ est vide", -1);
		gtk_text_view_set_buffer (mainWindow->ajout.m_textView_log,mainWindow->ajout.m_data);
		return;
	}


	nom = gtk_entry_get_text(mainWindow->ajout.m_lineEdit_nom);
	prenom = gtk_entry_get_text(mainWindow->ajout.m_lineEdit_prenom);
	numBadge = gtk_entry_get_text(mainWindow->ajout.m_lineEdit_NB);

	if(verifNumBadge(numBadge) == -1){

		gtk_text_buffer_set_text (mainWindow->ajout.m_data, "Numero de badge incorrect", -1);
		gtk_text_view_set_buffer (mainWindow->ajout.m_textView_log,mainWindow->ajout.m_data);
		return;

	}

	data = malloc((strlen(nom) + strlen(prenom) + strlen(numBadge) + 11) );
	requette = malloc(strlen(nom)+ strlen(prenom)+strlen(numBadge)+58);

	for(int i = 0; i < (strlen(nom) + strlen(prenom) + strlen(numBadge))+11;i++)
		data[i]=0;

	for(int i = 0; i < (strlen(nom)+ strlen(prenom)+strlen(numBadge)+58+6);i++)
		requette[i]= 0;

	strcat(data,nom);
	strcat(data," | ");
	strcat(data,prenom);
	strcat(data," | ");
	strcat(data,numBadge);
	strcat(data," | \n");
	g_print("%s",data);



	//INSERT "INTO utilisateur(nom,prenom,numBadge) VALUE('' ,'' ,'' );
	strcat(requette,"INSERT INTO utilisateur(nom,prenom,numBadge) VALUE('");
	strcat(requette,nom);
	strcat(requette,"' ,'");
	strcat(requette,prenom);
	strcat(requette,"' ,'");
	strcat(requette,numBadge);
	strcat(requette,"');");

	printf("%s",requette);
	printf("%ld\n",strlen(requette));


 	ecrirBdd(requette);

	gtk_text_buffer_set_text (mainWindow->ajout.m_data, data, -1);
	gtk_text_view_set_buffer (mainWindow->ajout.m_textView_log,mainWindow->ajout.m_data);
	effacerChamp();
	free(data);
	free(requette);

}

void effacerChamp(){
	gtk_entry_set_text(mainWindow->ajout.m_lineEdit_prenom,"");
	gtk_entry_set_text(mainWindow->ajout.m_lineEdit_NB,"");
	gtk_entry_set_text(mainWindow->ajout.m_lineEdit_nom,"");
}

int verifChamp(){

	if(strcmp(gtk_entry_get_text(mainWindow->ajout.m_lineEdit_nom),"") == 0){
		return -1;
	}
	else if(strcmp(gtk_entry_get_text(mainWindow->ajout.m_lineEdit_prenom),"") == 0){
		return -1;
	}
	else if(strcmp(gtk_entry_get_text(mainWindow->ajout.m_lineEdit_NB),"")== 0){
		return -1;
	}
	return 0;
}

int verifNumBadge(char* data){
	if(strlen(data)!= 8){
		g_print("error\n");
		return -1;
	}
	for(int i = 0; i < 8;i++){
		switch(data[i]){
		case('0'):break;
		case('1'):break;
		case('2'):break;
		case('3'):break;
		case('4'):break;
		case('5'):break;
		case('6'):break;
		case('7'):break;
		case('8'):break;
		case('9'):break;
		case('A'):break;
		case('B'):break;
		case('C'):break;
		case('D'):break;
		case('E'):break;
		case('F'):break;
		case('a'):data[i]-=32;break;
		case('b'):data[i]-=32;break;
		case('c'):data[i]-=32;break;
		case('d'):data[i]-=32;break;
		case('e'):data[i]-=32;break;
		case('f'):data[i]-=32;break;
		default:return -1;break;
		}
	}
	return 0;
}
