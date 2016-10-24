
/*
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"

object eval_define( object input ) {
    
    if (cadr(input)->type != SFS_SYMBOL) {
        WARNING_MSG("EVAL_DEFINE WARNING : cannot use Define, not a symbol");
        return NULL;
    }
    
    if (is_in_Env(cadr(input)->this.symbol,toplevel)) {
        WARNING_MSG("EVAL_DEFINE WARNING : cannot use Define, variable already defined");
        return NULL;
    }
    
    string symbol;
    strcpy(symbol,cadr(input)->this.symbol);
    object valeur = sfs_eval(caddr(input));
    
    if (valeur == NULL) {
        WARNING_MSG("EVAL_DEFINE WARNING : cannot use Define, valeur is NULL");
        return NULL;
    }

    toplevel = newVarEnvironment( symbol, valeur, toplevel );
    return NULL;
}

object eval_set( object input ) {
    
    if (cadr(input)->type != SFS_SYMBOL) {
        WARNING_MSG("EVAL_SET WARNING : cannot use set, not a symbol");
        return NULL;
    }
    
    if (!is_in_Env(cadr(input)->this.symbol,toplevel)) {
        WARNING_MSG("EVAL_SET WARNING : cannot use set, variable not defined");
        return NULL;
    }
    
    string symbol;
    strcpy(symbol,cadr(input)->this.symbol);
    object valeur = sfs_eval(caddr(input));
    
    if (valeur == NULL) {
        WARNING_MSG("EVAL_SET WARNING : cannot use set, valeur is NULL");
        return NULL;
    }
    
    toplevel = changeVarEnvironment( symbol, valeur, toplevel );
    if (toplevel == NULL) {
        ERROR_MSG("EVAL_SET ERROR : problem with changeVarEnvironment");
    }
    return NULL;
}

object eval_if( object input ) {
    
    object o_eval=NULL;
    
    return o_eval;
}

object eval_and( object input ) {
    
    object o_eval=NULL;
    
    return o_eval;
}

object eval_or( object input ) {
    
    object o_eval=NULL;
    
    return o_eval;
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
        WARNING_MSG("Not a proper number to evaluate");
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
    

    
    return input;
}


/* FONCTION D'EVALUATION */

object sfs_eval( object input ) {
    
    object eval_car = car(input);
    object o_eval=NULL;
    
    if ( !is_symbol(input) && !is_pair(input) && (input->type != SFS_NIL) ) {
        return input;
    }
    
    if ( is_symbol(input) ) {
        
      /*  DEBUG_MSG("toplevel premiere variable %d",toplevel->this.pair.car->this.pair.car->this.pair.cdr->type); */

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
            WARNING_MSG("SFS_EVAL WARNING : not a defined symbol");
            return NULL;
        }
    }
    
    if ( is_pair(input) ) {
        
        if ( is_symbol(eval_car) ) {
            string function;
            strcpy( function, eval_car->this.symbol );
            
            if (is_define(function)) {
                return eval_define(input);
            }
            
            else if (is_set(function)) {
                return eval_set(input);
            }
                    
            else if (is_if(function)) {
                return eval_if(input);
            }
                
            else if (is_or(function)) {
                return eval_or(input);
            }
                    
            else if (is_and(function)) {
                return eval_and(input);
            }
            
            else if (is_calcul_operator(function)) {
                return eval_calc_operator(input);
            }
            else if (is_cmp_operator(function)) {
                return eval_cmp_operator(input);
            }
        }
        
        else {
            WARNING_MSG("SFS_EVAL WARNING : not evaluable");
            return NULL;
        }
    }
    
    else {
        return input;
    }
}
