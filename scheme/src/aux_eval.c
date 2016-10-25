/*
 
  aux_eval.c
 

  Created by Jérémy Hraman on 12/10/2016.

*/

#include "aux_eval.h"

object eval_symbol ( object input ) {

    if ( is_in_Env(input->this.symbol ) ) {
        object EnvCopy = car(toplevel);
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
    
    if ( !is_nil(cddr(input)) ) {
        WARNING_MSG("%s accepts only 1 argument",car(input)->this.symbol);
        return NULL;
    }
    return input->this.pair.cdr->this.pair.car;
}

object eval_define( object input ) {
    
    if ( cdddr(input) == NULL || !is_nil(cdddr(input)) ) {
        WARNING_MSG("%s accepts only 1 symbol with 1 atom",car(input)->this.symbol);
        return NULL;
    }
    
    if ( cadr(input) == NULL || !is_symbol(cadr(input)) ) {
        WARNING_MSG("Cannot use Define, not a symbol");
        return NULL;
    }
    
    if (is_in_Env(cadr(input)->this.symbol)) {
        WARNING_MSG("Cannot use Define, variable already defined");
        return NULL;
    }
    
    string symbol;
    strcpy(symbol,cadr(input)->this.symbol);
    object valeur = sfs_eval(caddr(input));
    
    if (valeur == NULL) {
        WARNING_MSG("Cannot use Define, valeur is NULL");
        return NULL;
    }
    
    newVarEnvironment( symbol, valeur );
    return NULL;
}

object eval_set( object input ) {
    
    if ( !is_nil(cdddr(input)) ) {
        WARNING_MSG("%s accepts only 1 symbol with 1 atom",car(input)->this.symbol);
        return NULL;
    }
    
    if ( !is_symbol(cadr(input)) ) {
        WARNING_MSG("Cannot use set, not a symbol");
        return NULL;
    }
    
    if (!is_in_Env(cadr(input)->this.symbol)) {
        WARNING_MSG("Cannot use set, variable not defined");
        return NULL;
    }
    
    string symbol;
    strcpy(symbol,cadr(input)->this.symbol);
    object valeur = sfs_eval(caddr(input));
    
    if (valeur == NULL) {
        WARNING_MSG("Cannot use set, valeur is NULL");
        return NULL;
    }
    
    changeVarEnvironment( symbol, valeur );
    if (toplevel == NULL) {
        ERROR_MSG("Problem with changeVarEnvironment");
    }
    return NULL;
}

object eval_if( object input ) {
    
    
    if ( cdddr(input) == NULL ) {
        WARNING_MSG("%s-operator must have at least 1 expression",car(input)->this.symbol);
        return NULL;
    }
    if ( !is_nil(cdddr(input)) && !is_pair(cdddr(input)) ) {
        WARNING_MSG("%s-operator must have valid expression",car(input)->this.symbol);
        return NULL;
    }
    
    object o_first_arg = sfs_eval(cadr(input));
    
    if (o_first_arg->type != SFS_BOOLEAN) {
        WARNING_MSG("EVAL_IF cannot be used, first argument is not a boolean");
        return NULL;
    }
    
    if ( is_nil(cdddr(input)) ) {
        if ( o_first_arg == vrai ) {
            return sfs_eval(caddr(input));
        }
        else {
            return faux;
        }
    }
    
    else if ( cddddr(input) != NULL && is_nil(cddddr(input)) ) {
        if ( o_first_arg == vrai ) {
            return sfs_eval(caddr(input));
        }
        else {
            if ( is_nil(cdddr(input)) ) {
                return faux;
            }
            else {
                return sfs_eval(cadddr(input));
            }
        }
    }
    WARNING_MSG("%s-operator isn't in the right format",car(input)->this.symbol);
    return NULL;
}

object eval_and( object input ) {
    
    if ( is_nil(cdr(input)) ) {
        return faux;
    }
    
    object o_and = input;
    
    while ( !is_nil(cddr(o_and)) ) {
        o_and = cdr(o_and);
        
        if ( sfs_eval(car(o_and)) == NULL
            || sfs_eval(car(o_and))->type != SFS_BOOLEAN ) {
            WARNING_MSG("EVAL_AND cannot be used, 1 argument is not a boolean");
            return NULL;
        }
        
        if ( sfs_eval(car(o_and)) == faux ) {
            return faux;
        }
    }
    if (cadr(o_and) == faux) {
        return faux;
    }
    return vrai;
}

object eval_or( object input ) {
    
    if ( is_nil(cdr(input)) ) {
        return vrai;
    }
    
    object o_or = input;
    
    while ( !is_nil(cddr(o_or)) ) {
        o_or = cdr(o_or);
        
        if ( sfs_eval(car(o_or)) == NULL
            || sfs_eval(car(o_or))->type != SFS_BOOLEAN ) {
            WARNING_MSG("EVAL_OR cannot be used, 1 argument is not a boolean");
            return NULL;
        }
        
        if ( sfs_eval(car(o_or)) == vrai ) {
            return vrai;
        }
    }
    if (cadr(o_or) == vrai) {
        return vrai;
    }
    return faux;
}

object eval_calc_operator( object input ) {
    
    object o_first_arg = sfs_eval(cadr(input));
    if ( o_first_arg->type != SFS_NUMBER ) {
        WARNING_MSG("CALC_OPERATOR : Not a proper number to evaluate");
        return NULL;
    }
    
    object atom_number = NULL;
    int first_arg = o_first_arg->this.number.this.integer;
    int res;
    if ( is_nil(cddr(input)) ) {
        if ( strcmp( car(input)->this.symbol, "+" ) == 0 ) {
            res = first_arg;
        }
        else if ( strcmp( car(input)->this.symbol, "-" ) == 0 ) {
            res = -first_arg;
        }
        else {
            WARNING_MSG("%s-operator doesn't accept only 1 argument", car(input)->this.symbol);
            return NULL;
        }
        atom_number = make_integer(res);
        return atom_number;
    }
                        
    
    if ( !is_nil(cdddr(input)) ) {
        WARNING_MSG("%s operator accepts only 2 arguments",car(input)->this.symbol);
        return NULL;
    }
    
    object o_second_arg = sfs_eval(caddr(input));
    if ( o_second_arg->type != SFS_NUMBER ) {
        WARNING_MSG("CALC_OPERATOR : Not a proper number to evaluate");
        return NULL;
    }
    
    int second_arg = o_second_arg->this.number.this.integer;
    
    if ( strcmp( car(input)->this.symbol, "+" ) == 0 ) {
        res = first_arg + second_arg;
    }
    else if ( strcmp( car(input)->this.symbol, "-" ) == 0 ) {
        res = first_arg - second_arg;
    }
    else if ( strcmp( car(input)->this.symbol, "*" ) == 0 ) {
        res = first_arg * second_arg;
    }
    else {
        if ( second_arg == 0 ) {
            WARNING_MSG("Cannot divide by 0");
            return NULL;
        }
        res = first_arg / second_arg;
    }
    
    atom_number = make_integer(res);
    return atom_number;
}

object eval_cmp_operator( object input ) {
    
    if ( !is_nil(cdddr(input)) ) {
        WARNING_MSG("%s operator accepts only 2 arguments",car(input)->this.symbol);
        return NULL;
    }
    
    object atom_boolean = NULL;
    
    object o_first_arg = sfs_eval(cadr(input));
    object o_second_arg = sfs_eval(caddr(input));
    
    if ( o_first_arg->type != SFS_NUMBER || o_second_arg->type != SFS_NUMBER ) {
        WARNING_MSG("CMP_OPERATOR : Not a proper number to evaluate");
        return NULL;
    }
    
    int first_arg = o_first_arg->this.number.this.integer;
    int second_arg = o_second_arg->this.number.this.integer;
    int res=FALSE;
    
    if ( strcmp( car(input)->this.symbol, ">" ) == 0 ) {
        if ( first_arg > second_arg ) {
            res = TRUE;
        }
    }
    else if ( strcmp( car(input)->this.symbol, "<" ) == 0 ) {
        if ( first_arg < second_arg ) {
            res = TRUE;
        }
    }
    else if ( strcmp( car(input)->this.symbol, "=" ) == 0 ) {
        if ( first_arg == second_arg ) {
            res = TRUE;
        }
    }
    else if ( strcmp( car(input)->this.symbol, ">=" ) == 0 ) {
        if ( first_arg >= second_arg ) {
            res = TRUE;
        }
    }
    else if ( strcmp( car(input)->this.symbol, "<=" ) == 0 ) {
        if ( first_arg == second_arg ) {
            res = TRUE;
        }
    }
    else if ( strcmp( car(input)->this.symbol, "!=" ) == 0 ) {
        if ( first_arg != second_arg ) {
            res = TRUE;
        }
    }
    atom_boolean = make_boolean(res);
    return atom_boolean;
}

/* FONCTIONS ENVIRONNEMENTALES */

object newEnvironment( object toplevel ) {
    
    object newEnv = make_pair();
    newEnv->this.pair.car = make_nil();
    newEnv->this.pair.cdr = toplevel;

    return newEnv;
}


void newVarEnvironment( string symbol, object valeur ) {
    
    object newPair = make_pair();
    
    uint i=0;
    newPair->this.pair.car = make_pair();
    newPair->this.pair.car->this.pair.car = read_atom_symbol(symbol,&i);
    newPair->this.pair.car->this.pair.cdr = valeur;
    newPair->this.pair.cdr = toplevel->this.pair.car;
    toplevel->this.pair.car = newPair;
}

void changeVarEnvironment( string symbol, object valeur ) {
    
    object EnvCopy = car(toplevel);
    while ( !is_nil(EnvCopy) ) {
        if ( strcmp(symbol,caar(EnvCopy)->this.symbol) == 0 ) {
            EnvCopy->this.pair.car->this.pair.cdr=valeur;
        }
        EnvCopy = cdr(EnvCopy);
    }
}
