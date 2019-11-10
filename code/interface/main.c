#include "SRC/ajout.h"
#include "SRC/modifier.h"
#include "SRC/supprimer.h"
#include "SRC/bdd.h"

int main(int argc, char *argv [])
{

	if(connexion("127.0.0.1","root" ,"beartooth", "RFID") == -1){
		printf("impossible de se connecter à la base de données \n");
		exit(EXIT_FAILURE);
	}
	mainWindow = malloc(sizeof(struct windowControl));
	GtkBuilder *builder = NULL;
	GError *error = NULL;
	gchar *filename = NULL;

	/* Initialisation de la librairie Gtk. */
	gtk_init(&argc, &argv);

	/* Ouverture du fichier Glade de la fenêtre principale */
	builder = gtk_builder_new();

	/* Création du chemin complet pour accéder au fichier test.glade. */
	filename =  g_build_filename ("GUI/gui_RFID.glade", NULL);

	gtk_builder_add_from_file (builder, filename, &error);
	g_free (filename);
	if (error)
	{
		gint code = error->code;
		g_printerr("%s\n", error->message);
		g_error_free (error);
		return code;
	}

	/***
	 * initialisation mainWindow
	 */
	mainWindow->m_window = GTK_WIDGET(gtk_builder_get_object(builder, "m_window"));

	/***
	 * initialisation de ajout
	 */
	initAjout(builder);
	/***
	 * initialisation de supprimer
	 */
	initSupprimer(builder);
	/***
	 * initialisation de modifier
	 */
	initModifier(builder);



	/* Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
	/* fermeture de la fenêtre. */
	g_signal_connect (G_OBJECT (mainWindow->m_window), "destroy", (GCallback)leave, NULL);
	g_signal_connect (G_OBJECT (mainWindow->ajout.m_button_ajouter),"clicked",(GCallback)ajouterUser,NULL);
	g_signal_connect (G_OBJECT (mainWindow->ajout.m_button_effacer),"clicked",(GCallback)effacerChamp,NULL);
	g_signal_connect (G_OBJECT (mainWindow->supprimer.m_buton_refresh),"clicked",(GCallback)refresh,NULL);
	g_signal_connect (G_OBJECT (mainWindow->supprimer.m_buton_remove), "clicked",(GCallback)supprimer,NULL);
	g_signal_connect (G_OBJECT (mainWindow->modifier.m_button_modifer), "clicked",(GCallback)modifier,NULL);
	g_signal_connect (G_OBJECT (mainWindow->modifier.m_button_refresh), "clicked",(GCallback)updateModif,NULL);


	/* Affichage de la fenêtre principale. */
	gtk_widget_show_all (mainWindow->m_window);

	gtk_main();

	return 0;

}

void leave(){
	free(mainWindow);
	deconnexion();
	gtk_main_quit();

}
