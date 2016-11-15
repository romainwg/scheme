
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
	if ( o->type != SFS_PAIR ) {
        WARNING_MSG("cdr doesn't exist, not a pair");
        return NULL;
    }
    return o->this.pair.cdr ;
}
object cddr ( object o ) {
	return cdr(cdr(o));
}
object cdar ( object o ) {
	return cdr(car(o));
}
object cadr ( object o ) {
	return car(cdr(o));
}
object caar ( object o ) {
	return car(car(o));
}
object cdddr ( object o ) {
	return cdr(cddr(o));
}
object cddar ( object o ) {
	return cdr(cdar(o));
}
object cdadr ( object o ) {
	return cdr(cadr(o));
}
object cdaar ( object o ) {
	return cdr(caar(o));
}
object caddr ( object o ) {
	return car(cddr(o));
}
object cadar ( object o ) {
	return car(cdar(o));
}
object caadr ( object o ) {
	return car(cadr(o));
}
object caaar ( object o ) {
	return car(caar(o));
}
object cddddr ( object o ) {
	return cdr(cdddr(o));
}
object cdddar ( object o ) {
	return cdr(cddar(o));
}
object cddadr ( object o ) {
	return cdr(cdadr(o));
}
object cddaar ( object o ) {
	return cdr(cdaar(o));
}
object cdaddr ( object o ) {
	return cdr(caddr(o));
}
object cdadar ( object o ) {
	return cdr(cadar(o));
}
object cdaadr ( object o ) {
	return cdr(caadr(o));
}
object cdaaar ( object o ) {
	return cdr(caaar(o));
}
object cadddr ( object o ) {
	return car(cdddr(o));
}
object caddar ( object o ) {
	return car(cddar(o));
}
object cadadr ( object o ) {
	return car(cdadr(o));
}
object cadaar ( object o ) {
	return car(cdaar(o));
}
object caaddr ( object o ) {
	return car(caddr(o));
}
object caadar ( object o ) {
	return car(cadar(o));
}
object caaadr ( object o ) {
	return car(caadr(o));
}
object caaaar ( object o ) {
	return car(caaar(o));
}