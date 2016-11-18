
/**
 * @file object.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 17:49:46 2012
 * @brief Object definition for SFS.
 *
 * Object definition for SFS.
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"
#include <ctype.h>

typedef struct object_t {

    uint type;

    union {

        num              number;
        char          character;
        string           string;
        string           symbol;

        struct pair_t {
            struct object_t *car;
            struct object_t *cdr;
        }                pair;

        struct object_t *special;
        
        struct {
            struct object_t * (*function)( struct object_t * );
        } primitive;

    } this;

} *object;



object make_object      ( uint type           );
object make_nil         ( void                );
object make_pair        ( void                );
object make_integer     ( int valeur          );
object make_real        ( double valeur       );
object make_string      ( char* chaine, int i );
object make_character   ( char character      );
object make_boolean     ( int b               );
object make_symbol      ( char* symbol, int i );

object make_primitive   ( string symbol, object (*function)(object) );


    /* CAR/CDR */
    object car    ( object o );
    object cdr    ( object o );
	
    object cddr   ( object o );
    object cdar   ( object o );
    object cadr   ( object o );
    object caar   ( object o );
	
	object cdddr  ( object o );
	object cddar  ( object o );
	object cdadr  ( object o );
	object cdaar  ( object o );
    object caddr  ( object o );
    object cadar  ( object o );
	object caadr  ( object o );
	object caaar  ( object o );
	
    object cddddr ( object o );
	object cdddar ( object o );
	object cddadr ( object o );
	object cddaar ( object o );
	object cdaddr ( object o );
	object cdadar ( object o );
	object cdaadr ( object o );
	object cdaaar ( object o );
    object cadddr ( object o );
	object caddar ( object o );
	object cadadr ( object o );
	object cadaar ( object o );
	object caaddr ( object o );
	object caadar ( object o );
	object caaadr ( object o );
	object caaaar ( object o );

#define SFS_NUMBER       0x00
#define SFS_CHARACTER    0x01
#define SFS_STRING       0x02
#define SFS_PAIR         0x03
#define SFS_NIL          0x04
#define SFS_BOOLEAN      0x05
#define SFS_SYMBOL       0x06
#define SFS_NOTYPE       0x07
#define SFS_PRIMITIVE    0x08
#define SFS_FLOAT        0x09


extern object nil;
extern object vrai;
extern object faux;
extern object toplevel;

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
