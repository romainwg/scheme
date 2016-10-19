/*
 
  aux_eval.c
 

  Created by Jérémy Hraman on 12/10/2016.

*/

#include "aux_eval.h"

/* FONCTIONS ENVIRONNEMENTALES */

object newEnvironment( object o ) {
    
    object newEnv = make_object(SFS_PAIR);
    
    


}

/* FONCTIONS DE HASHAGE */

int hash( string chaine ) {
    
    int A=31; /* Variable de Hash A */
    int N = 50;
    int hashkey=0;
    int i;
    
    for(i=strlen(chaine)-1;i>=0;i--) {
        hashkey=(hashkey*A+chaine[i])%N;
    }
    
    return hashkey;
}

object add_ahead( string symbol, object o, object cdr ) {
    
    object new_o = make_object(SFS_PAIR);
    if ( new_o == NULL ) return NULL;
    
    new_o->this.pair.car=make_object(SFS_PAIR);
    
    new_o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    strcpy(new_o->this.pair.car->this.pair.car->this.symbol,symbol);
    
    new_o->this.pair.car->this.pair.cdr = cdr;
    
    new_o->this.pair.cdr = o;
    
    return new_o;
}



