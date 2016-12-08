
/*
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"
#include "print.h"

/* FONCTION D'EVALUATION */
/**
 * @param object input, object meta_environment
 * @return object evaluated if correct else NULL
 * @brief this function will evaluate an expression in a given environment
 *
 * This function evaluates an expression in a given environment. As required by R5rs, speciale care has been with recursive calls (no goto)
 **/

object sfs_eval( object input, object meta_environment ) {
    DEBUG_MSG("eval input %p %d", input, input->type);
    uint root = 1;
    sfs_print(input,&root);
    printf("\n");
    
    if (input == NULL) {
        return NULL;
    }
    if ( !is_symbol(input) && !is_pair(input) ) {
        return input;
    }
    if ( is_symbol(input) ) {
        DEBUG_MSG("SFS EVAL ICI");
        return eval_symbol(input,meta_environment);
    }
    if ( is_pair(input) ) {
        
        object eval_car = car(input);

        if ( is_primitive(eval_car) ) {
            return eval_primitive(input,meta_environment);
        }
        
        if ( is_symbol(eval_car) ) {
            string function;
            strcpy( function, eval_car->this.symbol );
            
            if (is_quote(function)) {
                return eval_quote(input);
            }
            else if (is_define(function)) {
                return eval_define(input,meta_environment);
            }
            else if (is_set(function)) {
                return eval_set(input,meta_environment);
            }
            else if (is_if(function)) {
                return eval_if(input,meta_environment);
            }
            else if (is_or(function)) {
                return eval_or(input,meta_environment);
            }
            else if (is_and(function)) {
                return eval_and(input,meta_environment);
            }
            else if (is_begin(function)) {
                return eval_begin(input,meta_environment);
            }
            else if (is_lambda(function)) {
                return eval_lambda(input,meta_environment);
            }
            else if (is_let(function)) {
                return eval_let(input,meta_environment);
            }
            else if (is_compound(eval_car)){
                return eval_compound(input,meta_environment);
            }
            else {
                WARNING_MSG("Not a form/primitive");
                return NULL;
            }
        }
        if ( is_pair(eval_car) ) {
            if ( is_compound(sfs_eval(eval_car,meta_environment)) ) {
                DEBUG_MSG("EVAL COMPOUND PAIR");
                object compound = eval_lambda(eval_car,meta_environment);
                return eval_compound(compound, meta_environment);
            }
        }

        if ( is_nil(cdr(input))  ) {
            return eval_car;
        }
        else {
            WARNING_MSG("SFS_EVAL WARNING : not valid evaluable expression");
            return NULL;
        }
    }
    WARNING_MSG("SFS_EVAL WARNING : not valid evaluable expression");
    return NULL;
}
