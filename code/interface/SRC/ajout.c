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

}

void ajouterUser(){
	char* nom;
	char* prenom;
	char* numBadge;

	GtkTextBuffer *buffer;
	GtkTextIter start, end;
	GtkTextIter iter;
	if(verifChamp() == -1){
		return;
	}

	nom = gtk_entry_get_text(mainWindow->ajout.m_lineEdit_nom);
	prenom = gtk_entry_get_text(mainWindow->ajout.m_lineEdit_prenom);
	numBadge = gtk_entry_get_text(mainWindow->ajout.m_lineEdit_NB);
	g_print("nom : %s , prenom : %s , NB : %s \n",nom,prenom,numBadge);

	strcat(nom," | ");
	strcat(nom,prenom);
	strcat(nom," | ");
	strcat(nom,numBadge);
	strcat(nom," | \n");
	g_print("%s",nom);


	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mainWindow->ajout.m_textView_log));
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
	gtk_text_buffer_insert(buffer, &iter, nom, -1);


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


