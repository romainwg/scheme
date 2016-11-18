/*
  primitive.c
  

  Created by Jérémy Hraman on 15/11/2016.

*/

#include "primitive.h"

void init_primitive ( void ) {
    
    make_primitive( "+"         , &prim_plus     );
    make_primitive( "-"         , &prim_minus    );
    make_primitive( "*"         , &prim_times    );
    make_primitive( "/"         , &prim_divide   );
    make_primitive( "quotient"  , &prim_quotient );
    make_primitive( "modulo"    , &prim_modulo   );
    
    make_primitive( "sin"   , &prim_sin  );
    make_primitive( "cos"   , &prim_cos  );
    make_primitive( "tan"   , &prim_tan  );
    make_primitive( "abs"   , &prim_abs  );
    make_primitive( "exp"   , &prim_exp  );
    make_primitive( "sqrt"  , &prim_sqrt );
    
    make_primitive( "boolean?"   , &prim_is_boolean    );
    make_primitive( "null?"      , &prim_is_null       );
    make_primitive( "string?"    , &prim_is_string     );
    make_primitive( "pair?"      , &prim_is_pair       );
    make_primitive( "symbol?"    , &prim_is_symbol     );
    make_primitive( "char?"      , &prim_is_char       );
    make_primitive( "number?"    , &prim_is_number     );
    make_primitive( "procedure?" , &prim_is_procedure  );
    
    make_primitive( "integer->char" , &prim_int_char         );
    make_primitive( "char->integer" , &prim_char_int         );
    make_primitive( "number->string", &prim_num_string       );
    make_primitive( "string->number", &prim_string_num       );
    make_primitive( "symbol->string", &prim_symbol_string    );
    make_primitive( "string->symbol", &prim_string_symbol    );
    make_primitive( "string->list"  , &prim_string_list      );
    
}



object prim_plus ( object o ) {
    return o;
}
object prim_minus ( object o ) {
    return o;
}
object prim_times ( object o ) {
    return o;
}
object prim_divide ( object o ) {
    return o;
}
object prim_quotient ( object o ) {
    return o;
}
object prim_modulo ( object o ) {
    return o;
}



object prim_sin ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("sin must have 1 and just 1 argument");
        return NULL;
    }
    
    o = sfs_eval(car(o));
    
    if ( !is_number(o) ) {
        WARNING_MSG("sin only accepts number");
        return NULL;
    }
    
    double out_sin;
    if ( is_integer(o) ) {
        out_sin = sin( o->this.number.this.integer );
    }
    else {
        out_sin = sin( o->this.number.this.real );
    }
    o = make_real ( out_sin );
    return o;
}
object prim_cos ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("cos must have 1 and just 1 argument");
        return NULL;
    }
    
    o = sfs_eval(car(o));
    if ( !is_number(o) ) {
        WARNING_MSG("cos only accepts number");
        return NULL;
    }
    
    double out_cos;
    if ( is_integer(o) ) {
        out_cos = cos( o->this.number.this.integer );
    }
    else {
        out_cos = cos( o->this.number.this.real );
    }
    o = make_real ( out_cos );
    return o;
}
object prim_tan ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("tan must have 1 and just 1 argument");
        return NULL;
    }
    
    o = sfs_eval(car(o));
    if ( !is_number(o) ) {
        WARNING_MSG("tan only accepts number");
        return NULL;
    }
    
    double out_tan;
    if ( is_integer(o) ) {
        out_tan = tan( o->this.number.this.integer );
    }
    else {
        out_tan = tan( o->this.number.this.real );
    }
    o = make_real ( out_tan );
    return o;
}
object prim_abs ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("abs must have 1 and just 1 argument");
        return NULL;
    }
    
    o = sfs_eval(car(o));
    if ( !is_number(o) ) {
        WARNING_MSG("abs only accepts number");
        return NULL;
    }
    
    int out_abs;
    if ( is_integer(o) ) {
        out_abs = abs( o->this.number.this.integer );
    }
    else {
        out_abs = fabs( o->this.number.this.real );
    }
    o = make_integer ( out_abs );
    return o;
}
object prim_exp ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("exp must have 1 and just 1 argument");
        return NULL;
    }
    
    o = sfs_eval(car(o));
    if ( !is_number(o) ) {
        WARNING_MSG("exp only accepts number");
        return NULL;
    }
    
    double out_exp;
    if ( is_integer(o) ) {
        out_exp = exp( o->this.number.this.integer );
    }
    else {
        out_exp = exp( o->this.number.this.real );
    }
    o = make_real ( out_exp );
    return o;
}
object prim_sqrt ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("sqrt must have 1 and just 1 argument");
        return NULL;
    }
    
    o = sfs_eval(car(o));
    if ( !is_number(o) ) {
        WARNING_MSG("sqrt only accepts number");
        return NULL;
    }
    
    double out_sqrt;
    if ( is_integer(o) ) {
        out_sqrt = sqrt( o->this.number.this.integer );
    }
    else {
        out_sqrt = sqrt( o->this.number.this.real );
    }
    o = make_real ( out_sqrt );
    return o;
}




object prim_is_boolean ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("boolean? must have 1 and just 1 argument");
        return NULL;
    }
    
    o = sfs_eval(car(o));
    if ( is_boolean (o) ) {
        o = vrai;
    }
    else {
        o = faux;
    }
    return o;
}
object prim_is_char ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("char? must have 1 and just 1 argument");
        return NULL;
    }
    
    o = sfs_eval(car(o));
    if ( is_char (o) ) {
        o = vrai;
    }
    else {
        o = faux;
    }
    return o;
}
object prim_is_null ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("null? must have 1 and just 1 argument");
        return NULL;
    }
    
    o = sfs_eval(car(o));
    if ( o==NULL ) {
        o = vrai;
    }
    else {
        o = faux;
    }
    return o;
}
object prim_is_symbol ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("symbol? must have 1 and just 1 argument");
        return NULL;
    }
    
    o = sfs_eval(car(o));
    if ( is_symbol(o) ) {
        o = vrai;
    }
    else {
        o = faux;
    }
    return o;
}
object prim_is_number ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("number? must have 1 and just 1 argument");
        return NULL;
    }
    
    o = sfs_eval(car(o));
    if ( is_number(o) ) {
        o = vrai;
    }
    else {
        o = faux;
    }
    return o;
}
object prim_is_pair ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("number? must have 1 and just 1 argument");
        return NULL;
    }

    if ( is_pair(o) ) {
        o = vrai;
    }
    else {
        o = faux;
    }
    return o;
}
object prim_is_procedure ( object o ) {
    WARNING_MSG("Procedure : not evaluable for the moment (Increment4)");
    return NULL;
}
object prim_is_string ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("string? must have 1 and just 1 argument");
        return NULL;
    }
    
    o = sfs_eval(car(o));
    if ( is_string(o) ) {
        o = vrai;
    }
    else {
        o = faux;
    }
    return o;
}




object prim_int_char ( object o ) {
    if ( cdr(o)==NULL || is_pair(cdr(o)) ) {
        WARNING_MSG("integer->char must have 1 and just 1 argument");
        return NULL;
    }
    
    o=sfs_eval(car(o));
    
    if ( is_integer(o) ) {
        char integer = o->this.number.this.integer;
        o = make_character(integer);
    }
    else {
        WARNING_MSG("integer->char only evaluates number");
        return NULL;
    }
    
    return o;
}
object prim_char_int ( object o ) {
    return o;
}
object prim_num_string ( object o ) {
    return o;
}
object prim_string_num ( object o ) {
    return o;
}
object prim_symbol_string ( object o ) {
    return o;
}
object prim_string_symbol ( object o ) {
    return o;
}
object prim_string_list ( object o ) {
    return o;
}








