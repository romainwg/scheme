/*
 
  aux_eval.h


  Created by Jérémy Hraman on 12/10/2016.

*/

#ifndef aux_eval_h
#define aux_eval_h

#include <stdio.h>
#include "object.h"

/* FONCTIONS AUXILIAIRES DE L'EVALUATION */

/* Clé de hashage */

int hash( string chaine, int N );

/* Ajout tête */

object add_ahead( string symbol, object o );



#endif /* aux_eval_h */
