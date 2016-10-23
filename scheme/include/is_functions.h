/*
 is_functions.h
 
 
 Created by Jérémy Hraman on 20/10/2016.
 
 */

#ifndef is_functions_h
#define is_functions_h

#include <stdio.h>
#include "object.h"
#include "aux_eval.h"

/* IS_FUNCTIONS - TYPE */
int is_pair     ( object o        );
int is_symbol   ( object eval_car );

/* IS_FUNCTIONS - SPECIAL SYMBOL */
int is_define   ( string function );
int is_set      ( string function );
int is_if       ( string function );
int is_or       ( string function );
int is_and      ( string function );

int is_in_Env( string function, object Env );

#endif /* is_functions_h */
