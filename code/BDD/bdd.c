/*
 * bdd.c
 *
 *  Created on: 8 nov. 2019
 *      Author: yannis
 */
#include "bdd.h"

int connexion(char* ip,char* id ,char* mdp, char* nom){
 m_lien=mysql_init(NULL);	
if(mysql_real_connect(m_lien,ip,id,mdp,nom,3306,NULL,0) == NULL)
	{
		return -1;
	}
	else{
		return 0;
	}
}
void deconnexion(){
    mysql_close(m_lien);
}

int ecrirBdd(char* requete){
	if(strcmp(requete,"") == 0){
		return -2;
	}
	else{
		int size= strlen(requete);
		if(mysql_real_query(m_lien,requete, size) != 0){
			return -1;
		}
		return 0;
	}
}
int recupBdd(char* requete){
	if(strcmp(requete,"") == 0){
		return -4;
	}
	else{
	
		if(mysql_query(m_lien,requete) != 0){
			return -1;
		}
		m_result = mysql_store_result(m_lien);
		if(m_result == NULL)
			return -2;

		m_lignes = mysql_fetch_row(m_result);
		if(m_lignes == NULL){
			mysql_free_result(m_result);
			return -3;
		}
		return 0;
	}
}
char* reponse(int indice){
	return m_lignes[indice];
}

int newLine(){
	m_lignes = mysql_fetch_row(m_result);
	if(m_lignes == NULL){
		mysql_free_result(m_result);
		return -1;
	}
	return 0;
}


