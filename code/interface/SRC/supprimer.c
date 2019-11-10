
/*
 * supprimer.c
 *
 *  Created on: 19 oct. 2019
 *      Author: yannis
 */
#include "supprimer.h"

void initSupprimer(GtkBuilder* builder){

	/* view */
	mainWindow->supprimer.m_view = GTK_WIDGET(gtk_builder_get_object(builder,"m_Supprimer_view"));

	/* data */
	mainWindow->supprimer.m_data = gtk_list_store_new (3,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

	/* tree view */
	mainWindow->supprimer.m_treeView = GTK_TREE_VIEW(gtk_builder_get_object(builder,"m_treeView_supprimerS"));
	//select
	mainWindow->supprimer.m_select= GTK_TREE_SELECTION(gtk_builder_get_object(builder,"m_select_supprimerS"));

	/* bouton */
	mainWindow->supprimer.m_buton_refresh= gtk_builder_get_object(builder,"m_bouton_refreshS");
	mainWindow->supprimer.m_buton_remove=gtk_builder_get_object(builder,"m_bouton_removeS");



	GtkCellRenderer* renderer;
	/* --- Column #NOM --- */
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (mainWindow->supprimer.m_treeView),
			-1,
			"Nom",
			renderer,
			"text", COL_NOM,
			NULL);

	/* --- Column #PRENOM--- */
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (mainWindow->supprimer.m_treeView),
			-1,
			"Prenom",
			renderer,
			"text", COL_PRENOM,
			NULL);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (mainWindow->supprimer.m_treeView),
			-1,
			"N° Badge",
			renderer,
			"text", COL_NUMBADGE,
			NULL);
	gtk_tree_view_set_model (GTK_TREE_VIEW (mainWindow->supprimer.m_treeView), mainWindow->supprimer.m_data);

}

void refresh(){

	updateSupp();
}
void updateSupp(){
	GtkTreeIter iter;
	gtk_list_store_clear(mainWindow->supprimer.m_data);

	switch(recupBdd("SELECT nom,prenom,numBadge FROM utilisateur")){
	case(-1):return;break;
	case(-2):return;break;
	case(-3):return;break;
	case(-4):return;break;
	}


	do{
		gtk_list_store_append (mainWindow->supprimer.m_data, &iter);
		gtk_list_store_set (mainWindow->supprimer.m_data, &iter,
				COL_NOM , reponse(0),
				COL_PRENOM , reponse(1),
				COL_NUMBADGE ,reponse(2),
				-1);
	}while(newLine() == 0);

	gtk_tree_view_set_model (GTK_TREE_VIEW (mainWindow->supprimer.m_treeView), mainWindow->supprimer.m_data);
}
void fillData(){


}

void supprimer(){
	mainWindow->supprimer.m_select= gtk_tree_view_get_selection(GTK_TREE_VIEW(mainWindow->supprimer.m_treeView));


	char* requette;
	char* nom;
	char* numBadge;
	GtkTreeIter iter;

	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(mainWindow->supprimer.m_select), &mainWindow->supprimer.m_data, &iter) == FALSE){
		g_print("error\n");
		return;
	}
	gtk_tree_model_get(mainWindow->supprimer.m_data, &iter, COL_NOM, &nom,  -1);
	gtk_tree_model_get(mainWindow->supprimer.m_data, &iter, COL_NUMBADGE, &numBadge,  -1);

	requette = malloc(56 + strlen(nom)+strlen(numBadge) + 4);
	for(int i = 0; i < 56 + strlen(nom)+strlen(numBadge)+4;i++)
		requette[i]=0;

	printf("%s\n", nom);
	printf("%s\n",numBadge);

	strcat(requette,"DELETE FROM utilisateur WHERE nom = '");
	strcat(requette,nom);
	strcat(requette,"' AND numBadge = '");
	strcat(requette,numBadge);
	strcat(requette,"' ;");

	printf("%s\n",requette);
	ecrirBdd(requette);
	free(requette);
	refresh();
}
