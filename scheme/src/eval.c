
/*
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"

int is_symbol( object eval_car ) {
    
    if ( eval_car->type == SFS_SYMBOL ) {
        return 1;
    }
    return 0;
}

object sfs_eval( object input ) {
    
    object eval_car = input->this.pair.car;
    
    if ( is_symbol(eval_car) ) {
        string symbol;
        strcpy( symbol, eval_car->this.symbol );
        
        switch (symbol) {
            case 'define' :
                
                
        }
    }

    return o_eval;
}
