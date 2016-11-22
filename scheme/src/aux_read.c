/*
 aux_read.c
 
 
 Created by Jérémy Hraman on 01/10/2016.
 SICOM-A
 
 */

#include "aux_read.h"

/* SUPPRIMER LES ESPACES */

void SpaceCancel( char *input, uint *here ) {
    
    while ( isspace(input[*here]) ) {
        (*here)++;
    }
}


/* RECHERCHE D'UN SPECIAL INITIAL */

int is_special_initial(char input) {
    
    char special_initial[17] = "\'!$%&*/:<=>?^_~.@";
    
    int i;
    for ( i=0 ; i<17 ; i++ ) {
        if ( input == special_initial[i] ) {
            return 1;
        }
    }
    return 0;
}


/* CALCUL DU NOMBRE DE CHIFFRES */

int size_number ( int valeur ) {
    
    char char_int[16];
    
    sprintf(char_int,"%d",valeur);
    
    if ( strlen(char_int) == 0 ) {
        
        ERROR_MSG("Error number : lenght null");
    }
    
    return strlen(char_int);
}


/* CARACTERISATION DU TYPE DE L'ATOME */
/* Retourne le type selon les premiers caractères sinon si erreur NOTYPE */

uint typeInput(char *input, uint *here) {
    
    char first_char=input[*here];
    
    /* STRING */
    
    char guillemet = '\"' ;
    
    if ( first_char == guillemet ) {
        
        return SFS_STRING;
    }
    
    
    /* BOOLEAN - CHARACTER */
    
    if ( input[*here] == '#' ) {
        
        if ( ( input[*here+1] == 't' || input[*here+1] == 'f' ) && (isgraph(input[*here+2]) == 0 || input[*here+2] == ')' ) ) {
            
            return SFS_BOOLEAN;
        }
        
        
        else if ( input[*here+1] == '\\' ) {
            
            return SFS_CHARACTER;
        }
    }
    
    /* SYMBOL */
    
    char *p_end1;
    char *p_end2;
    strtol(input + *here, &p_end1, 10);
    strtod(input + *here, &p_end2);
    
    if ( isalpha(input[*here]) != 0 || is_special_initial(input[*here]) == 1 || (( input[*here] == '+' ||  input[*here] == '-' ) && ( ( !isspace(p_end1[0]) && !iscntrl(p_end1[0]) && p_end1[0] != ')' && p_end1[0] != '(' && p_end1[0] != '\"' ) || ( !isspace(p_end2[0]) && !iscntrl(p_end2[0]) && p_end2[0] != ')' && p_end2[0] != '(' && p_end2[0] != '\"' ) ) ) ) {
        
        return SFS_SYMBOL;
    }
    
    
    /* NUMBER */
    
    if ( isspace(p_end1[0]) || iscntrl(p_end1[0]) || p_end1[0] == ')' || p_end1[0] == '(' || p_end1[0] == '\"' || isspace(p_end2[0]) || iscntrl(p_end2[0]) || p_end2[0] == ')' || p_end2[0] == '(' || p_end2[0] == '\"') {
        return SFS_NUMBER;
    }
    
    
    /* NOT A READABLE TYPE */
    
    else {
        WARNING_MSG("TYPE_ERROR : not a readable type");
        (*here)++;
        return SFS_NOTYPE;
    }
}