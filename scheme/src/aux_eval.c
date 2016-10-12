/*
 
  aux_eval.c
 

  Created by Jérémy Hraman on 12/10/2016.

*/

#include "aux_eval.h"


int hash( string chaine, int N ) {
    
    int A=31; /* Variable de Hash A */
    int hashkey=0;
    int i;
    
    for(i=strlen(chaine)-1;i>=0;i--) {
        
        hashkey=(hashkey*A+chaine[i])%N;
    }
    
    return hashkey;
}

object add_ahead( string symbol, object o ) {
    
    object new_o = make_object(SFS_PAIR);
    if ( new_o == NULL ) return NULL;
    
    
    
    
    return new_o;
}