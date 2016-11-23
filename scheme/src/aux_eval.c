/*
 
 aux_eval.c
 
 
 Created by Jérémy Hraman on 12/10/2016.
 
 */

#include "aux_eval.h"

object eval_symbol ( object input, object meta_environment ) {
    
    if ( is_in_Env(input->this.symbol, meta_environment) ) {
        object EnvCopy = car(meta_environment);
        while ( !is_nil(EnvCopy) ) {
            if ( strcmp(input->this.symbol,caar(EnvCopy)->this.symbol) == 0 ) {
                return cdar(EnvCopy);
            }
            EnvCopy = cdr(EnvCopy);
        }
    }
    else {
        WARNING_MSG("Not a defined symbol");
        return NULL;
    }
    return NULL;
}

object eval_quote( object input ) {
    
    /*if ( !is_nil(cddr(input)) ) {
     WARNING_MSG("%s accepts only 1 argument",car(input)->this.symbol);
     return NULL;
     }*/
    return input->this.pair.cdr->this.pair.car;
}

object eval_define( object input, object meta_environment ) {
    
    if ( cdddr(input) == NULL || !is_nil(cdddr(input)) ) {
        WARNING_MSG("%s accepts only 1 symbol with 1 atom",car(input)->this.symbol);
        return NULL;
    }
    
    if ( cadr(input) == NULL || !is_symbol(cadr(input)) ) {
        WARNING_MSG("Cannot use Define, not a symbol");
        return NULL;
    }
    
    if ( is_primitive(cadr(input)) ) {
        WARNING_MSG("%s is a primitive, cannot be defined",cadr(input)->this.symbol);
    }
    
    if (is_in_Env(cadr(input)->this.symbol,meta_environment)) {
        WARNING_MSG("Cannot use Define, variable already defined");
        return NULL;
    }
    
    string symbol;
    strcpy(symbol,cadr(input)->this.symbol);
    object valeur = sfs_eval(caddr(input),meta_environment);
    
    if (valeur == NULL) {
        WARNING_MSG("Cannot use Define, valeur is NULL");
        return NULL;
    }
    
    newVarEnvironment( symbol, valeur, meta_environment );
    object o = make_notype();
    return o;
}

object eval_set( object input, object meta_environment ) {
    
    if ( cdddr(input) == NULL || !is_nil(cdddr(input)) ) {
        WARNING_MSG("%s accepts only 1 symbol with 1 atom",car(input)->this.symbol);
        return NULL;
    }
    
    if ( cadr(input) == NULL || !is_symbol(cadr(input)) ) {
        WARNING_MSG("Cannot use set, not a symbol");
        return NULL;
    }
    
    if ( is_primitive(cadr(input)) ) {
        WARNING_MSG("%s is a primitive, cannot be set!",cadr(input)->this.symbol);
    }
    
    if (!is_in_Env(cadr(input)->this.symbol,meta_environment) ) {
        WARNING_MSG("Cannot use set, variable not defined");
        return NULL;
    }
    
    string symbol;
    strcpy(symbol,cadr(input)->this.symbol);
    object valeur = sfs_eval(caddr(input),meta_environment);
    
    if (valeur == NULL) {
        WARNING_MSG("Cannot use set, valeur is NULL");
        return NULL;
    }
    
    changeVarEnvironment( symbol, valeur, meta_environment );
    if (meta_environment == NULL) {
        ERROR_MSG("Problem with changeVarEnvironment");
    }
    object o = make_notype();
    return o;
}

object eval_if( object input, object meta_environment ) {
    
    
    if ( cdddr(input) == NULL ) {
        WARNING_MSG("%s-operator must have at least 1 expression",car(input)->this.symbol);
        return NULL;
    }
    if ( !is_nil(cdddr(input)) && !is_pair(cdddr(input)) ) {
        WARNING_MSG("%s-operator must have valid expression",car(input)->this.symbol);
        return NULL;
    }
    
    object o_first_arg = sfs_eval(cadr(input),meta_environment);
    
    if (o_first_arg->type != SFS_BOOLEAN) {
        WARNING_MSG("EVAL_IF cannot be used, first argument is not a boolean");
        return NULL;
    }
    
    if ( is_nil(cdddr(input)) ) {
        if ( o_first_arg == vrai ) {
            return sfs_eval(caddr(input),meta_environment);
        }
        else {
            return faux;
        }
    }
    
    else if ( cddddr(input) != NULL && is_nil(cddddr(input)) ) {
        if ( o_first_arg == vrai ) {
            return sfs_eval(caddr(input),meta_environment);
        }
        else {
            if ( is_nil(cdddr(input)) ) {
                return faux;
            }
            else {
                return sfs_eval(cadddr(input),meta_environment);
            }
        }
    }
    WARNING_MSG("%s-operator isn't in the right format",car(input)->this.symbol);
    return NULL;
}

object eval_and( object input, object meta_environment ) {
    
    if ( is_nil(cdr(input)) ) {
        return faux;
    }
    
    object o_and = input;
    
    while ( !is_nil(cddr(o_and)) ) {
        o_and = cdr(o_and);
        
        if ( sfs_eval(car(o_and),meta_environment) == NULL
            || sfs_eval(car(o_and),meta_environment)->type != SFS_BOOLEAN ) {
            WARNING_MSG("EVAL_AND cannot be used, 1 argument is not a boolean");
            return NULL;
        }
        
        if ( sfs_eval(car(o_and),meta_environment) == faux ) {
            return faux;
        }
    }
    if (sfs_eval(cadr(o_and),meta_environment) == faux) {
        return faux;
    }
    return vrai;
}

object eval_or( object input, object meta_environment ) {
    
    if ( is_nil(cdr(input)) ) {
        return vrai;
    }
    
    object o_or = input;
    
    while ( !is_nil(cddr(o_or)) ) {
        o_or = cdr(o_or);
        
        if ( sfs_eval(car(o_or),meta_environment) == NULL
            || sfs_eval(car(o_or),meta_environment)->type != SFS_BOOLEAN ) {
            WARNING_MSG("EVAL_OR cannot be used, 1 argument is not a boolean");
            return NULL;
        }
        
        if ( sfs_eval(car(o_or),meta_environment) == vrai ) {
            return vrai;
        }
    }
    if (sfs_eval(cadr(o_or),meta_environment) == vrai) {
        return vrai;
    }
    return faux;
}



object eval_primitive( object input ) {
    
    object EnvCopy = car(toplevel);
    while ( !is_nil(EnvCopy) ) {
        if ( strcmp(car(input)->this.symbol,caar(EnvCopy)->this.symbol) == 0 && cdar(EnvCopy)->type == SFS_PRIMITIVE ) {
            return cdar(EnvCopy)->this.primitive.function( cdr(input) );
        }
        EnvCopy = cdr(EnvCopy);
    }
    return NULL;
    
}

/* FONCTIONS ENVIRONNEMENTALES */

object newEnvironment( object meta_environment ) {
    
    object newEnv = make_pair();
    newEnv->this.pair.car = make_nil();
    newEnv->this.pair.cdr = meta_environment;
    
    return newEnv;
}


void newVarEnvironment( string symbol, object valeur, object meta_environment ) {
    
    object newPair = make_pair();
    
    uint i=0;
    newPair->this.pair.car = make_pair();
    newPair->this.pair.car->this.pair.car = read_atom_symbol(symbol,&i);
    newPair->this.pair.car->this.pair.cdr = valeur;
    newPair->this.pair.cdr = meta_environment->this.pair.car;
    meta_environment->this.pair.car = newPair;
}

void changeVarEnvironment( string symbol, object valeur, object meta_environment ) {
    
    object EnvCopy = car(meta_environment);
    while ( !is_nil(EnvCopy) ) {
        if ( strcmp(symbol,caar(EnvCopy)->this.symbol) == 0 ) {
            EnvCopy->this.pair.car->this.pair.cdr=valeur;
        }
        EnvCopy = cdr(EnvCopy);
    }
}

void print_environment( object meta_environment ) {
    
    object EnvCopy = car(meta_environment);
    while ( !is_nil(EnvCopy) ) {
        printf("%s          \n",caar(EnvCopy)->this.symbol);
        EnvCopy = cdr(EnvCopy);
    }
    
}
