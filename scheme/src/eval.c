
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
    
    object o_eval=NULL;
    
    object symbol = cadr(input);
    object valeur = sfs_eval(cddr(input));
    int hashkey = hash(symbol);
    
    return symbol;
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
                    o_eval = eval_define(input);
            }
            
            else if (is_set(function)) {
                    o_eval = eval_set(input);
            }
                    
            else if (is_if(function)) {
                    o_eval = eval_if(input);
            }
                
            else if (is_or(function)) {
                    o_eval = eval_or(input);
            }
                    
            else if (is_and(function)) {
                    o_eval = eval_and(input);
            }
        }
    }
    
    return input;
}
