
/**
 * @file read.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:30:11 2012
 * @brief Read routine for SFS.
 *
 * Read routine for SFS.
 */

#ifndef _READ_H_
#define _READ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "object.h"

enum {S_OK, S_KO, S_END};

uint   sfs_get_sexpr( string input, FILE *fp );

object sfs_read     (   char *input, uint *here );
object sfs_read_atom(   char *input, uint *here );
object sfs_read_pair(   char *stream, uint *i   );

/*************************************************************/
/* AJOUT QUOTE */

/**
* Prend en paramètre deux chaînes de caractère et la position de leur curseur
* change les apostrophes par des ouvertures de quote : "quote("
* La chaîne input est inchangée
*/
void ouverture_apostrophe_quote(char * input, char * inputModif, int * here, int * hereModif);


/**
* Prend en paramètre deux chaînes de caractère et la position de leur curseur
* Est chargé après l'ouverture de quote et va fermer la parenthèse du quote
* La chaîne input est inchangée
*/
void fermeture_apostrophe_quote(char * input, char * inputModif, int * here, int * hereModif);

/*************************************************************/


#ifdef __cplusplus
}
#endif

#endif /* _READ_H_ */
