/*
 
  aux_eval.h


  Created by Jérémy Hraman on 12/10/2016.

*/

#ifndef aux_eval_h
#define aux_eval_h

#include <stdio.h>
#include "object.h"
#include "read_atom.h"

/* FONCTIONS AUXILIAIRES DE L'EVALUATION */

/* CAR/CDR */
object car  ( object o );
object cdr  ( object o );
object cadr ( object o );
object cddr ( object o );
object caar ( object o );
object cdar ( object o );


/* FONCTIONS ENVIRONNEMENTALES */
object newEnvironment       ( object levelInf                               );
object newVarEnvironment    ( string symbol, object valeur, object Env      );
object changeVarEnvironment ( string symbol, object valeur, object toplevel );



#endif /* aux_eval_h */
