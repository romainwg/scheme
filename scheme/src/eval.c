
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
    
    DEBUG_MSG("eval_define after verif SFS_SYMBOL cadr(input)->this.symbol %s",cadr(input)->this.symbol);
    
    if (is_in_Env(cadr(input)->this.symbol,toplevel)) {
        WARNING_MSG("EVAL_DEFINE WARNING : cannot use Define, variable already defined");
        return NULL;
    }
    
    DEBUG_MSG("eval_define after verif is in Env");
    
    string symbol;
    strcpy(symbol,cadr(input)->this.symbol);
    
    DEBUG_MSG("eval_define valeur type(caddr(input)) %d",caddr(input)->type);
    
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
    object valeur = sfs_eval(cddr(input));
    
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


/* FONCTION D'EVALUATION */

object sfs_eval( object input ) {
    
    object eval_car = car(input);
    object o_eval=NULL;
    
    if ( !is_symbol(input) && !is_pair(input) && (input->type != SFS_NIL) ) {
        return input;
    }
    
    if ( is_symbol(input) ) {
        
        DEBUG_MSG("toplevel premiere variable %d",toplevel->this.pair.car->this.pair.car->this.pair.cdr->type);

        if ( is_in_Env(input->this.symbol,toplevel) ) {
            object EnvCopy = car(toplevel);
            
            
            while ( EnvCopy->type != SFS_NIL ) {
                if ( strcmp(input->this.symbol,caar(EnvCopy)->this.symbol) == 0 ) {
                    DEBUG_MSG("cdar(Envcopy) type %d",cdar(EnvCopy)->type);
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
                DEBUG_MSG("sfs_eval is define");
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
