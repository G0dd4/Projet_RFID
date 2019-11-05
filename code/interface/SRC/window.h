/*
 * window.h
 *
 *  Created on: 18 oct. 2019
 *      Author: yannis
 */

#ifndef __G_LIB_H__
#include <glib-2.0/glib.h>
#endif
#ifndef WINDOW_H_
#define WINDOW_H_
#define PATH "fileTest/test.csv"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/mman.h>
#include <math.h>



/**
 * @brief permet d'afilier chaque cologne à un numéro
 */
enum
{
  COL_NOM= 0,
  COL_PRENOM,
  COL_NUMBADGE,
  NUM_COLS
};


/***
 * @brief permet de controler l'ongler ajouter
 */
struct Ajout{

	GtkTextView* m_textView_log;
	GtkEntry* m_lineEdit_nom;
	GtkEntry* m_lineEdit_prenom;
	GtkEntry* m_lineEdit_NB;
	GtkButton* m_button_ajouter;
	GtkButton* m_button_effacer;
	GtkButton* m_button_getLast;
};
/***
 * @brief permet de controler l'ongler supprimer
 */
struct Supprimer{

	/* déclaration view */
	GtkWidget* m_view;

	/* déclaration bouton */
	GtkButton* m_buton_refresh;
	GtkButton* m_buton_remove;

	/* déclaration tree view */
	GtkTreeView* m_treeView;
	GtkTreeSelection* m_select;
	GtkListStore* m_data;
	//GtkTreeViewColumn* m_cologneNom;
	//GtkTreeViewColumn* m_colognePrenom;
	//GtkTreeViewColumn* m_cologneNumBadge;
	//GtkCellRenderer* m_renderNom;
	//GtkCellRenderer* m_renderPrenom;
	//GtkCellRenderer* m_renderNumBadge;


};
/***
 * @brief permet de controler l'ongler modifier
 */
struct Modifier{

	/* déclaration view */
	GtkWidget* m_view;
	/* déclaration lineEdit */
	GtkEntry* m_lineEdit_nom;
	GtkEntry* m_lineEdit_prenom;
	GtkEntry* m_lineEdit_NB;
	/* déclaration bouton */
	GtkButton* m_button_modifer;
	/* déclaration treeView */
	GtkTreeView* m_treeView;
	GtkTreeSelection* m_select;
	GtkListStore* m_data;

};

/**
 * @brief permet de controler la fenetre de controle
 */
struct windowControl{
	GtkWidget* m_window;
	struct Ajout ajout;
	struct Supprimer supprimer;
	struct Modifier modifier;
}* mainWindow;

void leave();


#endif /* WINDOW_H_ */
