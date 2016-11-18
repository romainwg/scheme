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

int is_primitive ( object o ) {
    
    object EnvCopy = car(toplevel);
    while ( !is_nil(EnvCopy) ) {
        if ( strcmp(o->this.symbol,caar(EnvCopy)->this.symbol) == 0 && cdar(EnvCopy)->type == SFS_PRIMITIVE ) {
            return 1;
        }
        EnvCopy = cdr(EnvCopy);
    }
    return 0;
}

/*NUMBER*/
int is_number ( object o ) {
    if ( o->type == SFS_NUMBER ) {
        return 1;
    }
    return 0;
}
int is_integer ( object o ) {
    
    DEBUG_MSG("o->this.number.numtype : %d",o->this.number.numtype);
    if ( o->this.number.numtype == NUM_INTEGER ) {
        return 1;
    }
    return 0;
}
int is_real ( object o ) {
    if ( o->this.number.numtype == NUM_REAL ) {
        return 1;
    }
    return 0;
}

/*OTHER*/
int is_boolean ( object eval_car ) {
    if ( eval_car->type == SFS_BOOLEAN ) {
        return 1;
    }
    return 0;
}

int is_char ( object eval_car ) {
    if ( eval_car->type == SFS_CHARACTER ) {
        return 1;
    }
    return 0;
}

int is_string ( object eval_car ) {
    if ( eval_car->type == SFS_STRING ) {
        return 1;
    }
    return 0;
}

int is_null ( object eval_car ) {
    if ( eval_car == NULL ) {
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

int is_nil ( object eval_car ) {
    if ( eval_car->type == SFS_NIL ) {
        return 1;
    }
    return 0;
}

int is_quote( string function ) {
    if ( strcmp(function,"quote") == 0 ) {
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
    DEBUG_MSG("is_if ?");
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


int is_in_Env( string function ) {
    
    object EnvCopy = car(toplevel);
    while ( !is_nil(EnvCopy) ) {
        if ( strcmp(function,caar(EnvCopy)->this.symbol) == 0 ) {
            return 1;
        }
        EnvCopy = cdr(EnvCopy);
    }
    return 0;
}


