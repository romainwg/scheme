
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
        WARNING_MSG("EVAL_DEFINE WARNING : cannot use Define, not a symbol.");
        return NULL;
    }
    
    if (is_in_Env(cadr(input)->this.symbol,toplevel)) {
        WARNING_MSG("EVAL_DEFINE WARNING : cannot use Define, variable already defined.");
        return NULL;
    }
    
    string symbol;
    strcpy(symbol,cadr(input)->this.symbol);
    object valeur = sfs_eval(cddr(input));

    toplevel = newVarEnvironment( symbol, valeur, toplevel );
    return NULL;
}

object eval_set( object input ) {
    
    object o_eval=NULL;
    
    return o_eval;
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


/* FONCTION D'EVALUATION */

object sfs_eval( object input ) {
    
    object eval_car = car(input);
    object o_eval=NULL;
    
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
        }
    }
    
    else {
        return input;
    }
}
