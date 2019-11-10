#include "modifier.h"
#include "bdd.h"
/*
 * modifier.c
 *
 *  Created on: 19 oct. 2019
 *      Author: yannis
 */
void  initModifier(GtkBuilder* builder){
	/* data */
	mainWindow->modifier.m_data = gtk_list_store_new (3,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	/* tree view */
	mainWindow->modifier.m_treeView =GTK_TREE_VIEW(gtk_builder_get_object(builder,"m_treeView_modifier"));
	// selection
	mainWindow->modifier.m_select= GTK_TREE_SELECTION(gtk_builder_get_object(builder,"m_select_modifier"));

	/* lineEdit */
	mainWindow->modifier.m_lineEdit_nom = gtk_builder_get_object(builder,"m_lineEdit_nomM");
	mainWindow->modifier.m_lineEdit_prenom = gtk_builder_get_object(builder,"m_lineEdit_prenomM");
	mainWindow->modifier.m_lineEdit_NB = gtk_builder_get_object(builder,"m_lineEdit_nbM");

	/* bouton */
	mainWindow->modifier.m_button_modifer = gtk_builder_get_object(builder,"m_boutton_modifierM");
	mainWindow->modifier.m_button_refresh = gtk_builder_get_object(builder,"m_boutton_refreshM");


	GtkCellRenderer* renderer;

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (mainWindow->modifier.m_treeView),
			-1,
			"Nom",
			renderer,
			"text", COL_NOM,
			NULL);

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (mainWindow->modifier.m_treeView),
			-1,
			"Prenom",
			renderer,
			"text", COL_PRENOM,
			NULL);

	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (mainWindow->modifier.m_treeView),
			-1,
			"N° Badge",
			renderer,
			"text", COL_NUMBADGE,
			NULL);

	gtk_tree_view_set_model (GTK_TREE_VIEW (mainWindow->modifier.m_treeView), mainWindow->modifier.m_data);

}

void updateModif(){
	GtkTreeIter iter;
	//requéte pour selectionner le tableau des utilisateur
	// SELECT NOM,PRENOM,NUMBADGE, FROM USER;
	gtk_list_store_clear(mainWindow->modifier.m_data);
	switch(	recupBdd("SELECT nom,prenom,numBadge FROM utilisateur")){
	case(-1):return;break;
	case(-2):return;break;
	case(-3):return;break;
	case(-4):return;break;
	}
	do{
		gtk_list_store_append (mainWindow->modifier.m_data, &iter);
		gtk_list_store_set (mainWindow->modifier.m_data, &iter,
				COL_NOM , reponse(0),
				COL_PRENOM , reponse(1),
				COL_NUMBADGE ,reponse(2),
				-1);
	}while(newLine() == 0);
	gtk_tree_view_set_model (GTK_TREE_VIEW (mainWindow->modifier.m_treeView), mainWindow->modifier.m_data);
}
void modifier(){
	mainWindow->modifier.m_select= gtk_tree_view_get_selection(GTK_TREE_VIEW(mainWindow->modifier.m_treeView));

	char* nom;
	char* numBadge;
	GtkTreeIter iter;

	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(mainWindow->modifier.m_select), &mainWindow->modifier.m_data, &iter) == FALSE){
		g_print("error\n");
		return;
	}
	gtk_tree_model_get(mainWindow->modifier.m_data, &iter, COL_NOM, &nom,  -1);
	gtk_tree_model_get(mainWindow->modifier.m_data, &iter, COL_NUMBADGE, &numBadge,  -1);


	char* requette1;
	char* requette2;
	char* requette3;

	requette1 = malloc(56 + strlen(gtk_entry_get_text(mainWindow->modifier.m_lineEdit_nom)) + 20 + strlen(numBadge) +3);
	requette2 = malloc(56 + strlen(gtk_entry_get_text(mainWindow->modifier.m_lineEdit_prenom)) + 20 + strlen(numBadge) +3);
	requette3 = malloc(56 + strlen(gtk_entry_get_text(mainWindow->modifier.m_lineEdit_NB)) + 20 + strlen(numBadge) +3);
	printf("%s\n", nom);
	printf("%s\n",numBadge);

	if(strcmp(gtk_entry_get_text(mainWindow->modifier.m_lineEdit_nom),"") != 0){
		// 56 + strlen(gtk_entry_get_text(mainWindow->modifier.m_lineEdit_nom)) + 20 + strlen(numBadge) +3
		for(int i = 0; i < 56 + strlen(gtk_entry_get_text(mainWindow->modifier.m_lineEdit_nom)) + 20 + strlen(numBadge) +3;i++)
			requette1[i]=0;
		strcat(requette1,"UPDATE utilisateur SET nom = '");
		strcat(requette1,gtk_entry_get_text(mainWindow->modifier.m_lineEdit_nom));
		strcat(requette1,"' WHERE numBadge = '");
		strcat(requette1,numBadge);
		strcat(requette1,"';");
		ecrirBdd(requette1);

	}
	if(strcmp(gtk_entry_get_text(mainWindow->modifier.m_lineEdit_prenom),"") != 0){
		// 56 + strlen(gtk_entry_get_text(mainWindow->modifier.m_lineEdit_prenom)) + 20 + strlen(numBadge) +3
		for(int i = 0; i < 56 + strlen(gtk_entry_get_text(mainWindow->modifier.m_lineEdit_prenom)) + 20 + strlen(numBadge) +3;i++)
			requette2[i]=0;
		strcat(requette2,"UPDATE utilisateur SET prenom = '");
		strcat(requette2,gtk_entry_get_text(mainWindow->modifier.m_lineEdit_prenom));
		strcat(requette2,"' WHERE numBadge = '");
		strcat(requette2,numBadge);
		strcat(requette2,"';");
		ecrirBdd(requette2);
	}
	if(strcmp(gtk_entry_get_text(mainWindow->modifier.m_lineEdit_NB),"") != 0){
		// 56 + strlen(gtk_entry_get_text(mainWindow->modifier.m_lineEdit_NB)) + 20 + strlen(numBadge) +3
		for(int i = 0; 56 + strlen(gtk_entry_get_text(mainWindow->modifier.m_lineEdit_NB)) + 20 + strlen(numBadge) +3;i++)
			requette3[i]=0;

		strcat(requette2,"UPDATE utilisateur SET prenom = '");
		strcat(requette2,gtk_entry_get_text(mainWindow->modifier.m_lineEdit_NB));
		strcat(requette2,"' WHERE numBadge = '");
		strcat(requette2,numBadge);
		strcat(requette2,"';");
		ecrirBdd(requette2);
	}




	free(requette1);
	free(requette2);
	free(requette3);

	updateModif();
}




