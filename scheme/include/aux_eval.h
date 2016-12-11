/*
 
  aux_eval.h


  Created by Jérémy Hraman on 12/10/2016.

*/

#ifndef aux_eval_h
#define aux_eval_h

#include <stdio.h>
#include "object.h"
#include "read_atom.h"
#include "is_functions.h"
#include "eval.h"

/* FONCTIONS AUXILIAIRES DE L'EVALUATION */

object eval_argument( object input, object meta_environment );
object eval_primitive( object input, object meta_environment );

/* FORMS */
object eval_symbol  ( object input, object meta_environment );
object eval_quote   ( object input ); /*prend en argument l'object input et renvoie l'object car(cdr(input)) sans l'évaluer*/
object eval_define  ( object input, object meta_environment );
object eval_set     ( object input, object meta_environment );
object eval_if      ( object input, object meta_environment );
object eval_and     ( object input, object meta_environment );
object eval_or      ( object input, object meta_environment );
object eval_begin   ( object input, object meta_environment );
object eval_lambda  ( object input, object meta_environment );
object eval_let     ( object input, object meta_environment );
object eval_map     ( object input, object meta_environment );
object eval_compound( object input, object compound, object meta_environment );


/* FONCTIONS ENVIRONNEMENTALES */
object newEnvironment     ( object levelInf              );
void newVarEnvironment    ( string symbol, object valeur, object meta_environment );
void changeVarEnvironment ( string symbol, object valeur, object meta_environment );
void changeVarAllEnvironment( string symbol, object valeur, object meta_environment );
void print_environment    ( object meta_environment      );
void print_all_env( object meta_environment );



#endif /* aux_eval_h */
