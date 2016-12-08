/*
 is_functions.c
 
 
 Created by Jérémy Hraman on 20/10/2016.
 
 */

#include "is_functions.h"

/* FUNCTIONS - TYPE */

int is_pair ( object o ) {
    if ( o->type == SFS_PAIR ) {
        return 1;
    }
    return 0;
}
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

int is_compound ( object eval_car ) {
    if ( eval_car->type == SFS_COMPOUND ) {
        return 1;
    }
    return 0;
}

/* FUNCTIONS - FORM */

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
int is_begin( string function ) {
    if ( strcmp(function,"begin") == 0 ) {
        return 1;
    }
    return 0;
}
int is_lambda( string function ) {
    if ( strcmp(function,"lambda") == 0 ) {
        return 1;
    }
    return 0;
}
int is_let( string function ) {
    if ( strcmp(function,"let") == 0 ) {
        return 1;
    }
    return 0;
}

/* FUNCTION - PRIMITIVE */

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

/* FUNCTION - IN ENVIRONMENT - LEVELS */

int is_in_current_Env(string function, object meta_environment) {
    object EnvCopy = car(meta_environment);
    while ( !is_nil(EnvCopy) ) {
        DEBUG_MSG("CURRENT ENV");
        if ( strcmp(function,caar(EnvCopy)->this.symbol) == 0 ) {
            DEBUG_MSG("CURRENT ENV OUI");
            return 1;
        }
        EnvCopy = cdr(EnvCopy);
    }
    return 0;
}

int is_in_Env( string function, object meta_environment ) {
    
    object EnvCopyLevel = meta_environment;
    object EnvCopyArguments = car(EnvCopyLevel);
    
    while ( !is_nil( EnvCopyLevel ) ) {
        while ( !is_nil( EnvCopyArguments ) ) {
            if ( strcmp(function,caar(EnvCopyArguments)->this.symbol) == 0 ) {
                return 1;
            }
            EnvCopyArguments = cdr(EnvCopyArguments);
        }
        EnvCopyLevel = cdr(EnvCopyLevel);
        if ( !is_nil(EnvCopyLevel) ) {
            EnvCopyArguments = car(EnvCopyLevel);
        }
    }
    return 0;
}


