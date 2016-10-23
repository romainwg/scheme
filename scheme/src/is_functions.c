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

int is_in_Env( string function, object Env ) {
    
    DEBUG_MSG("is in Env begin function %s",function);
    
    object EnvCopy = cdr(Env);
    while ( EnvCopy->type != SFS_NIL ) {
        if ( strcmp(function,caar(EnvCopy)->this.symbol) == 0 ) {
            return 1;
        }
        EnvCopy = cdr(EnvCopy);
    }
    return 0;
}


