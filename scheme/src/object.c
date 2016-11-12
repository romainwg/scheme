
/**
 * @file object.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:02:57 2012
 * @brief Object definitions for SFS.
 *
 * Object definitions for SFS.
 */

#include "object.h"
#include "mem.h"

object make_object( uint type ) {

    object t = sfs_malloc( sizeof( *t ) );

    t->type = type;

    return t;
}

object make_nil( void ) {
    
    if (nil == NULL) {
        object t = make_object( SFS_NIL );
        
        t->this.special = t;
        
        return t;
    }
    else return nil;

}

object make_pair( void ) {
    
    object o = NULL;
    
    o = make_object(SFS_PAIR);
    
    o->this.pair.car = NULL;
    o->this.pair.cdr = NULL;
    
    return o;
}

object make_integer( int valeur ) {
    
    object o = NULL;
    o = make_object(SFS_NUMBER);
    
    o->this.number.this.integer = valeur;
    
    return o;
}

object make_string ( char* chaine, int i ) {
    
    object o = NULL;
    o = make_object(SFS_STRING);
    
    strncpy (o->this.string, chaine, i);
    
    return o;
}

object make_character ( char character ) {
    
    object o = NULL;
    o = make_object(SFS_CHARACTER);
    
    o->this.character = character;
    
    return o;
}

object make_boolean ( int b ) {
    
    if (b == FALSE) {
        if (faux == NULL) {
            object o = NULL;
            o = make_object(SFS_BOOLEAN);
            o->this.special = o;
            
            return o;
        }
        else return faux;
    }
    
    if (b == TRUE) {
        if (vrai == NULL) {
            object o = NULL;
            o = make_object(SFS_BOOLEAN);
            o->this.special = o;
            
            return o;
        }
        else return vrai;
    }
    
    return NULL;
}

object make_symbol ( char* symbol , int i ) {
    
    object o = NULL;
    o = make_object(SFS_SYMBOL);
    
    strncpy(o->this.symbol,symbol,i);
    
    return o;
}

/* FONCTIONS CAR/CDR */

object car ( object o ) {
    if ( o->type != SFS_PAIR ) {
        WARNING_MSG("car doesn't exist, not a pair");
        return NULL;
    }
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
object cadddr ( object o ) {
    return o->this.pair.cdr->this.pair.cdr->this.pair.cdr->this.pair.car ;
}
object cddddr ( object o ) {
    return o->this.pair.cdr->this.pair.cdr->this.pair.cdr->this.pair.cdr ;
}