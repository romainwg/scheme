
/*
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"


object sfs_eval( object input ) {
    
    object eval_car = input->this.pair.car;
    
    if ( is_symbol(eval_car) ) {
        string symbol;
        strcpy( symbol, eval_car->this.symbol );
        
        = eval 
        
        return
                
        }
    }

    return o_eval;
}
