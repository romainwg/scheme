/*
 primitive.h
 
 
 Created by Jérémy Hraman on 15/11/2016.
 
 */

#ifndef primitive_h
#define primitive_h

#include <stdio.h>
#include "object.h"
#include "is_functions.h"
#include "eval.h"
#include "math.h"
#include "read_atom.h"
#include "read.h"
#include "aux_read.h"

void init_primitive ( void );

object prim_plus ( object o );
object prim_minus ( object o );
object prim_times ( object o );
object prim_divide ( object o );
object prim_quotient ( object o );
object prim_modulo ( object o );


object prim_inferior ( object o );
object prim_superior ( object o );
object prim_equal    ( object o );
object prim_eq_inf   ( object o );
object prim_eq_sup   ( object o );


object prim_sin ( object o );
object prim_cos ( object o );
object prim_tan ( object o );
object prim_abs ( object o );
object prim_exp ( object o );
object prim_sqrt( object o );


object prim_is_boolean ( object o );
object prim_is_char ( object o );
object prim_is_null ( object o );
object prim_is_number ( object o );
object prim_is_symbol ( object o );
object prim_is_pair ( object o );
object prim_is_procedure ( object o );
object prim_is_string ( object o );


object prim_int_char ( object o );
object prim_char_int ( object o );
object prim_num_string ( object o );
object prim_string_num ( object o );
object prim_symbol_string ( object o );
object prim_string_symbol ( object o );
object prim_string_list ( object o );

object prim_car ( object o );
object prim_cdr ( object o );
object prim_cons ( object o );
object prim_set_car ( object o );
object prim_set_cdr ( object o );
object prim_list ( object o );

#endif /* primitive_h */
