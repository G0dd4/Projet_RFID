/*
 * bdd.h
 *
 *  Created on: 8 nov. 2019
 *      Author: yannis
 */

#ifndef SRC_BDD_H_
#define SRC_BDD_H_
#include <mysql/mysql.h>
#include <string.h>
MYSQL* m_lien;
MYSQL_RES* m_result;
MYSQL_ROW m_lignes;

/**
 * @brief permet de se connecter à une Base de donées
 * @param ip = adresse IP de la BDD
 * @param id = identifiant de la base de données
 * @param mdp = mot de passe de l'id
 * @param nom = nom de la base de données
 * @return  0 = connecter | -1 = échouer
 */
int connexion(char* ip,char* id ,char* mdp, char* nom);

/**
 * @brief permet de se déconnecter de la base de données
 * @return 0 = déconexion réussie | -1 connexion échouer
 */
void deconnexion();
/**
* @brief Permet d'envoyer une requête pour interroger la base de données
* @param requete
* @return  -4 = le paramètre requete est NULL | -3 aucun élément trouvé | -2 = élément non stocké | -1 = mauvaise requète | 0 = bien passé
*/
int ecrirBdd(char* requete);

/**
 * @brief Permet d'envoyer une requête pour interroger la base de données
 * @param requete
 * @return  -4 = le paramètre requete est NULL | -3 aucun élément trouvé | -2 = élément non stocké | -1 = mauvaise requète | 0 = bien passé
 */
int recupBdd(char* requette);
/**
 * @brief Permet de passer à la ligne suivante lorsque nous avons fait une requête
 * @return -1 = plus de ddonnées  | 0 = saut de ligne effectuer
 */
int newLine();
/**
 * @brief Permet de récupérer la réponse que nous a renvoyé la base de données
 * @param i = Correspond à la colonne que nous souhaitons récupérer
 * @return la réponse de notre requête
 */
char* reponse(int indice);


#endif /* SRC_BDD_H_ */
