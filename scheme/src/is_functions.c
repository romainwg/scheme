/*
  is_functions.c


  Created by Jérémy Hraman on 20/10/2016.

*/

#include "is_functions.h"

/* FONCTIONS VERIFICATION TYPE & SYMBOL */

int is_pair ( object o ) {
    if ( o->type == SFS_PAIR ) {
        return 1;
    }
    return 0;
}

int is_symbol ( object eval_car ) {
    if ( eval_car->type == SFS_SYMBOL ) {
        return 1;
    }
    return 0;
}

int is_quote( string function ) {
    if ( strcmp(function,"quote") == 0 ) { /* la guillemet devra être changé en (quote *) avant d'utiliser cette fonction */
        return 1;
    }
    return 0;
}

int is_define( string function ) {
    if ( strcmp(function,"define") == 0 ) {
        return 1;
    }
    return 0;
}

int is_set( string function ) {
    if ( strcmp(function,"set!") == 0 ) {
        return 1;
    }
    return 0;
}

int is_if( string function ) {
    if ( strcmp(function,"if") == 0 ) {
        return 1;
    }
    return 0;
}

int is_or( string function ) {
    if ( strcmp(function,"or") == 0 ) {
        return 1;
    }
    return 0;
}

int is_and( string function ) {
    if ( strcmp(function,"and") == 0 ) {
        return 1;
    }
    return 0;
}

int is_calcul_operator( string input ) {
    if ( strcmp(input, "+") == 0 || strcmp(input, "-") == 0
        || strcmp(input, "*") == 0 || strcmp(input, "/") == 0 ) {
        return 1;
    }
    else {
        return 0;
    }
}

int is_cmp_operator( string input ) {
    if ( strcmp(input, ">") == 0 || strcmp(input, "<") == 0
        || strcmp(input, "=") == 0 || strcmp(input, "<=") == 0
        || strcmp(input, ">=") == 0 || strcmp(input, "!=") == 0) {
        return 1;
    }
    else {
        return 0;
    }
}


int is_in_Env( string function, object Env ) {
    
    object EnvCopy = car(Env);
    while ( EnvCopy->type != SFS_NIL ) {
        if ( strcmp(function,caar(EnvCopy)->this.symbol) == 0 ) {
            return 1;
        }
        EnvCopy = cdr(EnvCopy);
    }
    return 0;
}


