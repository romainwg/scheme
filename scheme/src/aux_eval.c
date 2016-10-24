/*
 
  aux_eval.c
 

  Created by Jérémy Hraman on 12/10/2016.

*/

#include "aux_eval.h"

/* FONCTIONS CAR/CDR */

object car ( object o ) {
    return o->this.pair.car ;
}

object cdr ( object o ) {
    return o->this.pair.cdr ;
}

object cadr ( object o ) {
    return o->this.pair.cdr->this.pair.car ;
}

object cddr ( object o ) {
    return o->this.pair.cdr->this.pair.cdr ;
}

object caar ( object o ) {
    return o->this.pair.car->this.pair.car ;
}

object cdar ( object o ) {
    return o->this.pair.car->this.pair.cdr ;
}

object caddr ( object o ) {
    return o->this.pair.cdr->this.pair.cdr->this.pair.car ;
}

object cdddr ( object o ) {
    return o->this.pair.cdr->this.pair.cdr->this.pair.cdr ;
}

/* FONCTIONS ENVIRONNEMENTALES */

object newEnvironment( object toplevel ) {
    
    object newEnv = make_pair();
    newEnv->this.pair.car = make_nil();
    newEnv->this.pair.cdr = toplevel;

    return newEnv;
}


object newVarEnvironment( string symbol, object valeur, object Env ) {
    
    object newPair = make_pair();
    
    uint i=0;
    newPair->this.pair.car = make_pair();
    newPair->this.pair.car->this.pair.car = read_atom_symbol(symbol,&i);
    newPair->this.pair.car->this.pair.cdr = valeur;
    newPair->this.pair.cdr = Env->this.pair.car;
    Env->this.pair.car = newPair;
    
    return Env;
}

object changeVarEnvironment( string symbol, object valeur, object Env ) {
    
    object EnvCopy = car(Env);
    while ( EnvCopy->type != SFS_NIL ) {
        if ( strcmp(symbol,caar(EnvCopy)->this.symbol) == 0 ) {
            EnvCopy->this.pair.car->this.pair.cdr=valeur;
            return Env;
        }
        EnvCopy = cdr(EnvCopy);
    }
    return NULL;
    
}





