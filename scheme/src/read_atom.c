/*
 read_atom.c
 
 
 Created by Jérémy Hraman on 15/09/2016.
 SICOM-A
 
 */

#include "read_atom.h"
#include "aux_read.h"

/* FONCTIONS READ_ATOM */

/* READ ATOM NUMBER */
/* Tous les nombres sont considérés comme entier */
/* On stocke le nombre dans atom_number */
/* Make_integer crée l'entier et retourne l'object atom sinon si erreur NULL */


object read_atom_number(char * input, uint *here) {
    
    char *p_end=NULL;
    char *p_end1=NULL;
    char *p_end2=NULL;
    object atom = NULL;
    num atom_number;
    
    if (input[*here] == '+') {
        (*here)++;
    }
    
    DEBUG_MSG("read atom");
    
    strtol(input + *here, &p_end1, 10);
    strtod(input + *here, &p_end2);
    
    if ( isspace(p_end1[0]) || iscntrl(p_end1[0]) || p_end1[0] == ')' || p_end1[0] == '(' || p_end1[0] == '\"') {
        
        atom_number.numtype = NUM_INTEGER;
        atom_number.this.integer = strtol(input + *here, &p_end, 10);
        *here = *here + size_number( atom_number.this.integer );
        atom = make_integer( atom_number.this.integer );
    }
    
    else if ( isspace(p_end2[0]) || iscntrl(p_end2[0]) || p_end2[0] == ')' || p_end2[0] == '(' || p_end2[0] == '\"' ) {
        char *p_end;
        atom_number.numtype = NUM_REAL;
        atom_number.this.real = strtod(input + *here, &p_end);
        *here = *here + (p_end - (input + *here));
        atom = make_real( atom_number.this.real );
    }
    else {
        WARNING_MSG("Error atom : not a number");
    }
    
    return atom;
}


/* READ ATOM CHAINE */
/* Lecture de la chaîne à partir de *here */
/* On stocke la chaîne dans la variable chaine */
/* Make_string crée la chaîne et retourne l'object atom sinon si erreur NULL */

object read_atom_chaine(char *input, uint *here){
    
    object atom = NULL;
    char chaine[256];
    chaine[0]='\"';
    int i=1;
    (*here) = (*here)+1;
    
    if ( input[*here] == '"' ) {
        DEBUG_MSG("READ CHAINE");
        (*here)++;
        return NULL;
    }
    
    while ( input[*here] != '\"') {
        if ( input[*here] == '\\' && input[*here+1] == '\"') {
            
            chaine[i]=input[*here];
            chaine[i+1]=input[*here+1];
            i++;
            (*here)++;
        }
        
        else {
            chaine[i]=input[*here];
        }
        (*here)++;
        i++;
    }
    
    chaine[i]='\"';
    (*here)++;
    i++;
    
    atom = make_string(chaine,i);
    return atom;
}

/* READ ATOM CHARACTER */
/* Lecture de la chaîne à partir de *here */
/* On stocke la chaîne dans la variable character */
/* Make_character crée la chaîne et retourne l'object atom sinon si erreur NULL */

object read_atom_character(char *input,uint *here){
    
    object atom = NULL;
    char character='\0';
    int i=1;
    (*here) = (*here) + 2;
    
    if ( input[*here] == 'n' ) {
        char ch1[7];
        (*here)++;
        
        if ( isspace(input[*here]) != 0 || iscntrl(input[*here]) != 0
            || input[*here] == ')' || input[*here] == '(' ) {
            
            character = 'n';
            atom = make_character(character);
            return atom;
        }
        
        ch1[0] = 'n';
        
        while ( i<7 ) {
            ch1[i]=input[*here];
            (*here)++;
            i++;
        }
        
        if ( strncmp (ch1,"newline",7) == 0 ) {
            character = '\n';
        }
        
        else {
            WARNING_MSG("Error read_atom_character : not a character");
            return NULL;
        }
    }
    
    else if ( input[*here] == 's' ) {
        (*here)++;
        
        if ( isspace(input[*here]) != 0 || iscntrl(input[*here]) != 0
            || input[*here] == ')' || input[*here] == '(' ) {
            
            character = 's';
            atom = make_character(character);
            return atom;
        }
        
        char ch2[5];
        ch2[0] = 's';
        
        while ( i<5 ) {
            ch2[i]=input[*here];
            (*here)++;
            i++;
        }
        
        if ( strncmp(ch2,"space",5) == 0 ) {
            character = ' ';
        }
        
        else {
            WARNING_MSG("Error read_atom_character : not a character");
            return NULL;
        }
    }
    
    else {
        if ( input[*here+1] == ')' || input[*here+1] == '(' || isspace(input[*here+1]) ) {
            character = input[*here];
            (*here)++;
            atom = make_character(character);
            return atom;
        }
        else {
            WARNING_MSG("Error read_atom_character : not a character");
            return NULL;
        }
    }
    
    atom = make_character(character);
    return atom;
}

/* READ ATOM BOOLEAN */
/* Lecture de la chaîne à partir de *here */
/* On stocke le booléen dans la variable boolean */
/* Make_boolean crée la chaîne et retourne l'object atom sinon si erreur NULL */

object read_atom_boolean(char *input, uint *here){
    
    object atom = NULL;
    char boolean[2];
    
    boolean[0]=input[*here];
    boolean[1]=input[*here+1];
    
    *here = *here + 2;
    
    if ( strcmp("#t",boolean) == 0 ) {
        atom = make_boolean ( TRUE );
    }
    
    if ( strcmp("#f",boolean) == 0 ) {
        atom = make_boolean ( FALSE );
    }
    
    return atom;
}

object read_atom_symbol(char *input, uint *here){
    
    object atom = NULL;
    
    int i=0;
    int current_here = *here;
    
    string symbol;
    
    if ( input[*here] == '\'') {
        DEBUG_MSG("input [*here] %c",input[*here]);
        strncpy(symbol,"quote",5);
        atom = make_symbol(symbol,5);
        (*here)++;
        DEBUG_MSG("Atom symbol : %s",atom->this.symbol);
        return atom;
    }
    
    while ( isalnum(input[current_here]) != 0 || is_special_initial(input[current_here]) != 0
           || input[current_here] == '+' || input[current_here] == '-' ) {
        
        symbol[i]=input[current_here];
        
        current_here++;
        i++;
    }
    
    *here = current_here;
    
    atom = make_symbol(symbol,i);
    
    return atom;
}