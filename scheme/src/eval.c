
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
    
    return o_eval;
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
            
            switch (symbol) {
                case 'define':
                    o_eval = eval_define(input);
                    break;
                    
                case 'set!':
                    o_eval = eval_set(input);
                    break;
                    
                case 'if':
                    o_eval = eval_if(input);
                    break;
                
                case 'or':
                    o_eval = eval_or(input);
                    break;
                    
                case 'and':
                    o_eval = eval_and(input);
                    break;
            }
        }
    }
    
    return o_eval;
}
