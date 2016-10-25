/*
 
  aux_eval.c
 

  Created by Jérémy Hraman on 12/10/2016.

*/

#include "aux_eval.h"

object eval_symbol ( object input, object toplevel ) {

    if ( is_in_Env(input->this.symbol,toplevel) ) {
        object EnvCopy = car(toplevel);
        while ( EnvCopy->type != SFS_NIL ) {
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
    /*mettre cdr(input) à la place de car(input) et affecter fin de liste à cdr(input) ???*/
    
    /*printf("\ninput : %d", input->type);
    printf("\ncar input : %d", input->this.pair.car->type);
    printf("\ncdr input : %d", input->this.pair.cdr->type);*/
    
    return input->this.pair.cdr->this.pair.car;
}

object eval_define( object input ) {
    
    if ( cdddr(input)->type != SFS_NIL ) {
        WARNING_MSG("%s accepts only 1 symbol with 1 atom",car(input)->this.symbol);
        return NULL;
    }
    
    if (cadr(input)->type != SFS_SYMBOL) {
        WARNING_MSG("Cannot use Define, not a symbol");
        return NULL;
    }
    
    if (is_in_Env(cadr(input)->this.symbol,toplevel)) {
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
    
    toplevel = newVarEnvironment( symbol, valeur, toplevel );
    return NULL;
}

object eval_set( object input ) {
    
    if ( cdddr(input)->type != SFS_NIL ) {
        WARNING_MSG("%s accepts only 1 symbol with 1 atom",car(input)->this.symbol);
        return NULL;
    }
    
    if (cadr(input)->type != SFS_SYMBOL) {
        WARNING_MSG("Cannot use set, not a symbol");
        return NULL;
    }
    
    if (!is_in_Env(cadr(input)->this.symbol,toplevel)) {
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
    
    toplevel = changeVarEnvironment( symbol, valeur, toplevel );
    if (toplevel == NULL) {
        ERROR_MSG("Problem with changeVarEnvironment");
    }
    return NULL;
}

object eval_if( object input ) {
    
    if ( cdddr(input)->type != SFS_NIL || cddddr(input)->type != SFS_NIL ) {
        WARNING_MSG("%s accepts only 1 predicat with 1 or 2 expression(s)",car(input)->this.symbol);
        return NULL;
    }
    
    object o_first_arg = sfs_eval(cadr(input));
    
    if (o_first_arg->type != SFS_BOOLEAN) {
        WARNING_MSG("EVAL_IF cannot be used, first argument is not a boolean");
        return NULL;
    }
    
    if ( o_first_arg == vrai ) {
        return sfs_eval(caddr(input));
    }
    else {
        if ( cdddr(input)->type == SFS_NIL ) {
            return faux;
        }
        else {
            return sfs_eval(cadddr(input));
        }
    }
    return NULL;
}

object eval_and( object input ) {
    
    if ( cdddr(input)->type != SFS_NIL ) {
        WARNING_MSG("%s accepts only 2 arguments",car(input)->this.symbol);
        return NULL;
    }
    
    object o_first_arg = sfs_eval(cadr(input));
    object o_second_arg = sfs_eval(caddr(input));
    
    if (o_first_arg->type != SFS_BOOLEAN || o_second_arg->type != SFS_BOOLEAN ) {
        WARNING_MSG("EVAL_AND cannot be used, 1 argument is not a boolean");
        return NULL;
    }
    
    if ( o_first_arg == vrai && o_second_arg == vrai ) {
        return vrai;
    }
    return faux;
}

object eval_or( object input ) {
    
    if ( cdddr(input)->type != SFS_NIL ) {
        WARNING_MSG("%s accepts only 2 arguments",car(input)->this.symbol);
        return NULL;
    }
    object o_first_arg = sfs_eval(cadr(input));
    object o_second_arg = sfs_eval(caddr(input));
    
    if (o_first_arg->type != SFS_BOOLEAN || o_second_arg->type != SFS_BOOLEAN ) {
        WARNING_MSG("EVAL_AND cannot be used, 1 argument is not a boolean");
        return NULL;
    }
    
    if ( o_first_arg == faux && o_second_arg == faux ) {
        return faux;
    }
    return vrai;
}

object eval_calc_operator( object input ) {
    
    if ( cdddr(input)->type != SFS_NIL ) {
        WARNING_MSG("%s operator accepts only 2 arguments",car(input)->this.symbol);
        return NULL;
    }
    
    object atom_number = NULL;
    
    object o_first_arg = sfs_eval(cadr(input));
    object o_second_arg = sfs_eval(caddr(input));
    
    if ( o_first_arg->type != SFS_NUMBER || o_second_arg->type != SFS_NUMBER ) {
        WARNING_MSG("CALC_OPERATOR : Not a proper number to evaluate");
        return NULL;
    }
    
    int first_arg = o_first_arg->this.number.this.integer;
    int second_arg = o_second_arg->this.number.this.integer;
    int res;
    
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
    
    if ( cdddr(input)->type != SFS_NIL ) {
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


object newVarEnvironment( string symbol, object valeur, object Env ) {
    
    object newPair = make_pair();
    
    uint i=0;
    newPair->this.pair.car = make_pair();
    newPair->this.pair.car->this.pair.car = read_atom_symbol(symbol,&i);
    newPair->this.pair.car->this.pair.cdr = valeur;
    newPair->this.pair.cdr = Env->this.pair.car;
    Env->this.pair.car = newPair;
    
    return Env;
}

object changeVarEnvironment( string symbol, object valeur, object Env ) {
    
    object EnvCopy = car(Env);
    while ( EnvCopy->type != SFS_NIL ) {
        if ( strcmp(symbol,caar(EnvCopy)->this.symbol) == 0 ) {
            EnvCopy->this.pair.car->this.pair.cdr=valeur;
            return Env;
        }
        EnvCopy = cdr(EnvCopy);
    }
    return NULL;
    
}
