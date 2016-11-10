
/**
 * @file repl.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:13:02 2012
 * @brief Main REPL for SFS.
 *
 * Main REPL for SFS.
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"

/* mode d'interaction avec l'interpreteur (exemple)*/
typedef enum {INTERACTIF,SCRIPT} inter_mode;


void usage_error( char *command ) {

    fprintf( stderr, "Usage: %s [file.scm]\n   If no file is given, executes in Shell mode.\n", command );
}


object nil=NULL;
object vrai=NULL;
object faux=NULL;
object toplevel=NULL;

void init_interpreter ( void ) {

    nil         = make_nil()            ;
    vrai        = make_boolean( TRUE )  ;
    faux        = make_boolean( FALSE ) ;
    toplevel    = make_pair()           ;
    toplevel->this.pair.car = make_nil();
    toplevel->this.pair.cdr = make_nil();

}



/**
* Prend en paramètre deux chaînes de caractère et la position de leur curseur
* change les apostrophes par des ouvertures de quote : "quote("
* La chaîne input est inchangée
*/
void ouverture_apostrophe_quote(char * input, char * inputModif, int * here, int * hereModif){
	
	
	/*ouverture du quote*/
	inputModif[(*hereModif)] = '(';
	inputModif[(*hereModif)+1] = 'q';
	inputModif[(*hereModif)+2] = 'u';
	inputModif[(*hereModif)+3] = 'o';
	inputModif[(*hereModif)+4] = 't';
	inputModif[(*hereModif)+5] = 'e';
	inputModif[(*hereModif)+6] = ' ';

	/*increment du curseur quote modif*/
	(*hereModif)+=6;

	/*fermeture du quote*/
	fermeture_apostrophe_quote(input, inputModif, here, hereModif);
	return;
}


/**
* Prend en paramètre deux chaînes de caractère et la position de leur curseur
* Est chargé après l'ouverture de quote et va fermer la parenthèse du quote
* La chaîne input est inchangée
*/
void fermeture_apostrophe_quote(char * input, char * inputModif, int * here, int * hereModif){
	/*le curseur est placé apres l'apostrophe/l'ouverture*/
/*
	*here++;
	*hereModif++;
*/
	
	/*
	* si 
	*/
	return;
}



int main ( int argc, char *argv[] ) {
    
    char     input[BIGSTRING];
    uint     here = 0;
    uint     root = 1;
    object   output = NULL;
    object   sexpr = NULL;
    inter_mode mode;
    FILE *   fp = NULL; /* le flux dans lequel les commande seront lues : stdin (mode shell) ou un fichier */

    /* exemples d'utilisation des macros du fichier notify.h */
    /* WARNING_MSG : sera toujours affiche */
/*    WARNING_MSG("Un message WARNING_MSG !"); */

    /* macro INFO_MSG : uniquement si compil avec -DVERBOSE. Cf Makefile*/
 /*   INFO_MSG("Un message INFO_MSG : Debut du programme %s", argv[0]); */

    /* macro DEBUG_MSG : uniquement si compil avec -DDEBUG (ie : compil avec make debug). Cf Makefile */
 /*   DEBUG_MSG("Un message DEBUG_MSG !"); */

    /* La ligne suivante provoquerait l'affichage du message
       puis la sortie du programme avec un code erreur non nul (EXIT_FAILURE) */
    /* ERROR_MSG("Erreur. Arret du programme"); */

    if ( argc > 2 ) {
        usage_error( argv[0] );
        exit( EXIT_FAILURE );
    }
    if(argc == 2 && strcmp(argv[1], "-h") == 0) {
        usage_error( argv[0] );
        exit( EXIT_SUCCESS );
    }

    init_interpreter();

    /*par defaut : mode shell interactif */
    fp = stdin;
    mode = INTERACTIF;
    if(argc == 2) {
        /* mode fichier de commandes */
        fp = fopen( argv[1], "r" );
        if ( fp == NULL ) {
            perror( "fopen" );
            exit( EXIT_FAILURE );
        }
        mode = SCRIPT;
    }


    while ( 1 ) {
        input[0]='\0';
        here = 0;
        root = 1;
        output = NULL;
        sexpr = NULL;
        uint Sexpr_err;

        Sexpr_err = sfs_get_sexpr( input, fp );

        if ( S_OK != Sexpr_err) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                if (Sexpr_err==S_END) {
                    /* Cas fin de fichier script */
                    exit(EXIT_SUCCESS);
                }
                /* Cas S-Expression mal formee dans le fichier script */
                ERROR_MSG("Malformed S-expression --- Aborts");
            }
            /*sinon on rend la main à l'utilisateur*/
            continue;
        }

        if ( 0 == strlen( input ) ) {
            continue;
        }

        /* Pour le step 0 on se contente d'afficher */
        /* la S-Expression lue */
        /* puis d'en lire une autre */
        /* METTRE EN COMMENTAIRE LES DEUX LIGNES SUIVANTES */
        /* POUR PASSER A L'INCREMENT 1 */
  /*      printf("%s\n", input );
        continue;*/
		/**************************************************************/
		
		/*creation chaine bis afin de stocker les modifications*/
		char inputQuoteModif[BIGSTRING];
		
		
		/*initialisation variable*/
		int varDebugQuote = 1;		
		int varCountForQuote = 0;
		int hereQuoteModif = 0;
		int numero_apostrophe = 0;
		int count_apostrophe_quote = 0;
		
		/*mise à zero de tout les caractères de la chaine modif*/
		for(varCountForQuote=0;varCountForQuote<BIGSTRING;varCountForQuote++){
			inputQuoteModif[varCountForQuote]=0;
		}
		
		/*DEBUG*/
		if(varDebugQuote){
			printf("\n\n\n|");
			for(varCountForQuote=0 ; input[varCountForQuote]!=0 && varCountForQuote<BIGSTRING ; varCountForQuote++){
			
				printf("%c",input[varCountForQuote]);
			
			}
			printf("|\n\n\n");
		}
		
		/*	- on compte le nombre d'apostrophe
		*	- on alloue une place suffisante à l'ajout (quote ) -> 8-1 par '
		*	- parcours de la chaîne
		*	- estimation du remplacement : 'abc ; '(set! a b) ; '" abc a" ; '
		*	- remplacement
		*/
		
		/*Comptage du nombre d apostrophe dans la chaine*/
		for(varCountForQuote=0 ; input[varCountForQuote]!=0 && varCountForQuote<BIGSTRING ; varCountForQuote++){
			/*l'on compte le nombre d'aopostrophe dans la chaîne*/
			if(input[varCountForQuote] == '\''){
				count_apostrophe_quote++;
			}
		}
		
		/*Vérification si présence ou non ; si non, saut de la procédure de remplacement*/
		if( count_apostrophe_quote != 0){
			
			/*verification si la chaine d'acceuil de longueur BIGSTRING sera suffisante après ajout du quote et des parenthèses
			* ' -> "(quote " + ")" soit 7 caractères supplémentaires par apostrophes
			*/
			if(strlen(input)+7*count_apostrophe_quote>=BIGSTRING){
				/* Pas assez de place pour le remplacement ! */
				
				
			}else{
				/* OK : assez de place pour le remplacement ! */
				/*parcours de la chaine à la recherche des apostrophes*/
				for(varCountForQuote=0 ; input[varCountForQuote]!=0 && varCountForQuote<BIGSTRING /*&& numero_apostrophe!=count_apostrophe_quote*/ ; varCountForQuote++){
										
					
					

					/*ouverture du quote*/
					if(input[varCountForQuote]=='\''){
						/*ouverture du quote a la position du curseur*/
						ouverture_apostrophe_quote(input, inputQuoteModif, &varCountForQuote, &hereQuoteModif);
						
						/*incrementation du nombre d apostrophe modifie*/
						numero_apostrophe++;
						
					}else{
						/*copie du caractere a la position du curseur*/
						inputQuoteModif[hereQuoteModif] = input[varCountForQuote];
					}

					hereQuoteModif++;					
				}
				
			}
		}
		
		/*DEBUG*/
		if(varDebugQuote){
			printf("\n\n\n|");
			for(varCountForQuote=0 ; inputQuoteModif[varCountForQuote]!=0 && varCountForQuote<BIGSTRING ; varCountForQuote++){
								
				printf("%c",inputQuoteModif[varCountForQuote]);
			
			}
			printf("|\n\n\n");
			printf("here : %d ; hereModif : %d", varCountForQuote, hereQuoteModif);
		}

		/**************************************************************/
        here  = 0;
        sexpr = sfs_read( input, &here );
        if ( NULL == sexpr ) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
                ERROR_MSG("Invalid S-expression --- Aborts");
            }
            /*sinon on rend la main à l'utilisateur*/
            continue ;
        }
        
        output = sfs_eval( sexpr );
        if( NULL == output) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
                ERROR_MSG("Error while evaluating input --- Aborts");
            }
            /*sinon on rend la main à l'utilisateur*/
            continue ;
        }

        printf( "==> " );
        sfs_print( output , &root );
        printf( "\n" );
    }

    if (mode == SCRIPT) {
        fclose( fp );
    }
    exit( EXIT_SUCCESS );
}
