
/*
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"

/* FONCTION D'EVALUATION */
/**
 * @param
 * @return
 * @brief this function will evaluate an expression in a given environment
 *
 * This function evaluates an expression in a fiven environem. As required by Rnrs, speciale care has been with recursive calls (no goto) 
 **/

object sfs_eval( object input ) {
    DEBUG_MSG("input %p %d", input, input->type);

    object eval_car = car(input);
    
    if (input == NULL) {
        return NULL;
    }
    
    if ( !is_symbol(input) && !is_pair(input)
        && (input->type != SFS_NIL) ) {
        return input;
    }
    
    if ( is_symbol(input) ) {
        return eval_symbol(input);
    }
    
    if ( is_pair(input) ) {
        
        if ( is_primitive(eval_car) ) {
            return input->this.primitive.function( cdr(input) );
        }
        
        if ( is_symbol(eval_car) ) {
            string function;
            strcpy( function, eval_car->this.symbol );
            
            if (is_quote(function)) {
                return eval_quote(input);
            }
            else if (is_define(function)) {
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
       /*     else if (is_calcul_operator(function)) {
                return eval_calc_operator(input);
            }
            else if (is_cmp_operator(function)) {
                return eval_cmp_operator(input);
            } */
        }
        
        else {
            WARNING_MSG("SFS_EVAL WARNING : not evaluable (for the moment ...)");
            return NULL;
        }
    }
    return input;
}
