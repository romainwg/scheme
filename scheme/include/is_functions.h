/*
 is_functions.h
 
 
 Created by Jérémy Hraman on 20/10/2016.
 
 */

#ifndef is_functions_h
#define is_functions_h

#include <stdio.h>
#include "object.h"
#include "aux_eval.h"

/* FUNCTIONS - TYPE */
int is_pair     ( object o        );
int is_symbol   ( object eval_car );
int is_nil      ( object eval_car );
int is_boolean  ( object eval_car );
int is_char     ( object eval_car );
int is_string   ( object eval_car );
int is_null     ( object eval_car );

int is_number   ( object o );
int is_integer  ( object o );
int is_real     ( object o );

int is_compound ( object o );

/* FUNCTIONS - FORMS */
int is_quote	( string function );
int is_define   ( string function );
int is_set      ( string function );
int is_if       ( string function );
int is_or       ( string function );
int is_and      ( string function );
int is_begin    ( string function );
int is_lambda   ( string function );
int is_let      ( string function );
int is_map      ( string function );

/* FUNCTION - PRIMITIVE */
int is_primitive( object o );

/* FUNCTION - IN ENVIRONMENT - LEVELS */
int is_in_current_Env(string function, object meta_environment);
int is_in_Env( string function, object meta_environment );

#endif /* is_functions_h */
