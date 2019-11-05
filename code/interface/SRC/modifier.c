#include "modifier.h"
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

	updateModif();

}

void updateModif(){
	GtkTreeIter iter;
	//requéte pour selectionner le tableau des utilisateur
	// SELECT NOM,PRENOM,NUMBADGE, FROM USER;
	gtk_list_store_clear(mainWindow->modifier.m_data);
	// boucle for
	// my sql fetch row;
	gtk_list_store_append (mainWindow->modifier.m_data, &iter);
	gtk_list_store_set (mainWindow->modifier.m_data, &iter,
			COL_NOM , "Aissoaui",
			COL_PRENOM , "Yannis",
			COL_NUMBADGE ,"1F34D201",
			-1);
	gtk_list_store_append (mainWindow->modifier.m_data, &iter);
	gtk_list_store_set (mainWindow->modifier.m_data, &iter,
			COL_NOM , "Vu",
			COL_PRENOM , "Tylan",
			COL_NUMBADGE ,"1E304560",
			-1);
	gtk_list_store_append (mainWindow->modifier.m_data, &iter);
	gtk_list_store_set (mainWindow->modifier.m_data, &iter,
			COL_NOM , "Khan",
			COL_PRENOM , "Naghman",
			COL_NUMBADGE ,"1C5060D4",
			-1);

	gtk_tree_view_set_model (GTK_TREE_VIEW (mainWindow->modifier.m_treeView), mainWindow->modifier.m_data);
}
void modifier(){
	mainWindow->modifier.m_select= gtk_tree_view_get_selection(GTK_TREE_VIEW(mainWindow->modifier.m_treeView));
	gchar *value;
	GtkTreeIter iter;

	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(mainWindow->modifier.m_select), &mainWindow->modifier.m_data, &iter) == FALSE){
		g_print("error\n");
		return;
	}
	gtk_tree_model_get(mainWindow->modifier.m_data, &iter, COL_NOM , &value,  -1);
	g_print("col 0 = %s; \n", value);
	gtk_tree_model_get(mainWindow->modifier.m_data, &iter, COL_NUMBADGE , &value,  -1);
	g_print("col 0 = %s; \n", value);
	//DROM FROM user WHERE numBadge="numBadge";
}




