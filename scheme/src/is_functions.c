//
//  is_functions.c
//  
//
//  Created by Jérémy Hraman on 20/10/2016.
//
//

#include "is_functions.h"

/* FONCTIONS VERIFICATION TYPE & SYMBOL */

int is_pair ( object o ) {
    if ( o->type == SFS_PAIR ) {
        return 1;
    }
    return 0;
}

int is_symbol ( object eval_car ) {
    if ( eval_car->type == SFS_SYMBOL ) {
        return 1;
    }
    return 0;
}