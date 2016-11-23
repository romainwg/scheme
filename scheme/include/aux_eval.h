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

object eval_primitive( object input );

/* SYMBOL */
object eval_symbol  ( object input );
object eval_quote   ( object input ); /*prend en argument l'object input et renvoie l'object car(cdr(input)) sans l'évaluer*/
object eval_define  ( object input );
object eval_set     ( object input );
object eval_if      ( object input );
object eval_and     ( object input );
object eval_or      ( object input );

/* OPERATOR */
object eval_calc_operator   ( object input );
object eval_cmp_operator    ( object input );


/* FONCTIONS ENVIRONNEMENTALES */
object newEnvironment     ( object levelInf              );
void newVarEnvironment    ( string symbol, object valeur );
void changeVarEnvironment ( string symbol, object valeur );
void print_environment    ( object meta_environment      );



#endif /* aux_eval_h */
