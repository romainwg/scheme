//
//  primitive.c
//  
//
//  Created by Jérémy Hraman on 15/11/2016.
//
//

#include "primitive.h"

void init_primitive () {
    
    make_primitive( "+"         , prim_plus     );
    make_primitive( "-"         , prim_minus    );
    make_primitive( "*"         , prim_times    );
    make_primitive( "/"         , prim_divide   );
    make_primitive( "quotient"  , prim_quotient );
    make_primitive( "modulo"    , prim_modulo   );
    
    make_primitive( "sin"   , prim_sin  );
    make_primitive( "cos"   , prim_cos  );
    make_primitive( "tan"   , prim_tan  );
    make_primitive( "abs"   , prim_abs  );
    make_primitive( "exp"   , prim_exp  );
    make_primitive( "sqrt"  , prim_sqrt );
    
    make_primitive( "boolean?"   , prim_is_boolean    );
    make_primitive( "null?"      , prim_is_null       );
    make_primitive( "string?"    , prim_is_string     );
    make_primitive( "pair?"      , prim_is_pair       );
    make_primitive( "symbol?"    , prim_is_symbol     );
    make_primitive( "char?"      , prim_is_char       );
    make_primitive( "number?"    , prim_is_number     );
    make_primitive( "list?"      , prim_is_list       );
    make_primitive( "procedure?" , prim_is_procedure  );
    
    make_primitive( "integer->char" , prim_int_char         );
    make_primitive( "char->integer" , prim_char_int         );
    make_primitive( "number->string", prim_num_string       );
    make_primitive( "string->number", prim_string_num       );
    make_primitive( "symbol->string", prim_symbol_string    );
    make_primitive( "string->symbol", prim_string_symbol    );
    make_primitive( "string->list"  , prim_string_to_list   );
    
}
