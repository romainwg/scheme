/*
 
 aux_eval.c
 
 
 Created by Jérémy Hraman on 12/10/2016.
 
 */

#include "aux_eval.h"
#include "print.h"

/* EVAL ARGUMENTS */

object eval_argument(object input, object meta_environment) {
    if ( input == NULL ) {
        WARNING_MSG("No argument, input is NULL");
        return NULL;
    }
    if ( !is_pair (input) ) {
        return sfs_eval( input, meta_environment );
    }
    
    object o_argument = make_pair();
    
    if ( is_pair(input) ) {
        if ( is_nil( cdr(input) ) ) {
            o_argument->this.pair.car = sfs_eval(car(input), meta_environment );
            o_argument->this.pair.cdr = make_nil();
            if (is_null(o_argument->this.pair.car)) return NULL;
        }
        else {
            o_argument->this.pair.car = sfs_eval(car(input), meta_environment );
            if (is_null(o_argument->this.pair.car)) return NULL;
            o_argument->this.pair.cdr = eval_argument(cdr(input), meta_environment );
            if (is_null(o_argument->this.pair.cdr)) return NULL;
        }
    }
    return o_argument;
}


/* EVAL PRIMITIVE */

object eval_primitive( object input, object meta_environment ) {
    
    object EnvCopy = car(toplevel);
    while ( !is_nil(EnvCopy) ) {
        if ( strcmp(car(input)->this.symbol,caar(EnvCopy)->this.symbol) == 0 && cdar(EnvCopy)->type == SFS_PRIMITIVE ) {
            input = cdr(input);
            input = eval_argument(input,meta_environment);
            DEBUG_MSG("eval primitive après eval argument");
            return cdar(EnvCopy)->this.primitive.function( input );
        }
        EnvCopy = cdr(EnvCopy);
    }
    return NULL;
    
}

/* EVAL FORMS */

object eval_lambda ( object input, object meta_environment ) {
    if ( cdddr(input) == NULL || is_nil(cddr(input)) ) {
        WARNING_MSG("Lambda form accepts at least 2 arguments");
        return NULL;
    }
    input = cdr(input);
    if ( car(input) == NULL || !is_pair(car(input)) ) {
        WARNING_MSG("Parameters of lambda form are not in the right format (lambda (<param>) <expr>)");
        return NULL;
    }
    object param = car(input);
    while ( !is_nil(param) ) {
        if ( !is_symbol(car(param)) ) {
            WARNING_MSG("Parameters are not symbols");
            return NULL;
        }
        param = cdr(param);
    }
    param = car(input);
    
    object compound = make_compound(param, cdr(input), meta_environment);
    return compound;
}

object eval_symbol ( object input, object meta_environment ) {
    
    print_environment(meta_environment);
    
    if ( is_in_Env(input->this.symbol, meta_environment) ) {
        DEBUG_MSG("iciciciciciciicicicicici");
        object EnvCopyLevel = meta_environment;
        object EnvCopyArguments = car(EnvCopyLevel);
        
        while ( !is_nil(EnvCopyLevel) ) {
            while ( !is_nil( EnvCopyArguments ) ) {
                DEBUG_MSG("EVAL SYMBOL ICI");
                if ( strcmp(input->this.symbol,caar(EnvCopyArguments)->this.symbol) == 0 ) {
                    DEBUG_MSG("Valeur symbol trouvé type %d",cdar(EnvCopyArguments)->type);
                    return cdar(EnvCopyArguments);
                }
                EnvCopyArguments = cdr(EnvCopyArguments);
            }
            EnvCopyLevel = cdr(EnvCopyLevel);
            if ( !is_nil(EnvCopyLevel) ) {
                EnvCopyArguments=car(EnvCopyLevel);
            }
        }
    }
    else {
        WARNING_MSG("Not a defined symbol");
        return NULL;
    }
    return NULL;
}

object eval_compound ( object input, object compound, object meta_environment ) {
    
    object param = compound->this.compound.param;
    
    input = cdr(input);
    input = eval_argument(input,meta_environment);
    
    if (input == NULL) {
        return NULL;
    }

    object new_env = newEnvironment(meta_environment);

    while ( !is_nil(input) && !is_nil(param) ) {
        if (car(param) == NULL || car(input) == NULL ) {
            WARNING_MSG("Function haven't the same number of parameters");
            return NULL;
        }
        DEBUG_MSG("EVAL car(input) %d",car(input)->this.number.this.integer);
        if ( is_in_current_Env(car(param)->this.symbol,new_env) ) {
            changeVarEnvironment(car(param)->this.symbol, car(input), new_env);
        }
        else {
            DEBUG_MSG("NEW VAR ENVIRONMENT EVAL COMPOUND");
            newVarEnvironment(car(param)->this.symbol, car(input), new_env);
        }
        input = cdr(input);
        param = cdr(param);
    }
    
    print_environment(new_env);
    object o_body = eval_begin(compound->this.compound.body,new_env);
    if (o_body == NULL) {
        return NULL;
    }
    DEBUG_MSG("AVANT FIN EVAL COMPOUND");
    
    return o_body;
}

object eval_quote( object input ) {
    
    if ( cddr(input)==NULL || is_pair(cddr(input)) ) {
        WARNING_MSG("%s accepts only 1 argument",car(input)->this.symbol);
        return NULL;
     }
    return input->this.pair.cdr->this.pair.car;
}

object eval_define( object input, object meta_environment ) {
    
    if ( cdddr(input) == NULL || !is_nil(cdddr(input)) ) {
        WARNING_MSG("%s accepts only 2 arguments",car(input)->this.symbol);
        return NULL;
    }
    
    if ( cadr(input) != NULL && is_pair(cadr(input)) ) {
        if ( caadr(input) == NULL || !is_symbol(caadr(input)) ) {
            WARNING_MSG("Cannot use Define, one atom at least ");
            return NULL;
        }
        if ( is_in_Env(caadr(input)->this.symbol, meta_environment) ) {
            WARNING_MSG("Cannot use Define, symbol already defined");
            return NULL;
        }
        
       
        object symbol = caadr(input);
        DEBUG_MSG("caadr symbol type6 : %d",symbol->type);
        object body = caddr(input);
        DEBUG_MSG("cddr body type3 : %d",body->type);
        object param = cdadr(input);
        DEBUG_MSG("cdadr param type3 : %d",param->type);
        object env = newEnvironment(meta_environment);
    /*    uint root2 = 1;
        sfs_print(body,&root2);
        printf("\n"); */
        input = make_compound(param,body,env);
        newVarEnvironment(symbol->this.symbol, input, meta_environment);
        return make_notype();
    }
    
    if ( cadr(input) == NULL || !is_symbol(cadr(input)) ) {
        WARNING_MSG("Cannot use Define, not a symbol");
        return NULL;
    }
    if ( is_primitive(cadr(input)) ) {
        WARNING_MSG("%s is a primitive, cannot be defined",cadr(input)->this.symbol);
        return NULL;
    }
    if (is_in_Env(cadr(input)->this.symbol,meta_environment) ) {
        WARNING_MSG("Cannot use Define, variable already defined");
        return NULL;
    }
    
    string symbol;
    strcpy(symbol,cadr(input)->this.symbol);
    object valeur = sfs_eval(caddr(input),meta_environment);
    
    if (valeur == NULL) {
        WARNING_MSG("Cannot use Define, valeur is NULL");
        return NULL;
    }
    
    newVarEnvironment( symbol, valeur, meta_environment );
    object o = make_notype();
    return o;
}

object eval_set( object input, object meta_environment ) {
    
    if ( cdddr(input) == NULL || !is_nil(cdddr(input)) ) {
        WARNING_MSG("%s accepts only 1 symbol with 1 atom",car(input)->this.symbol);
        return NULL;
    }
    
    if ( cadr(input) == NULL || !is_symbol(cadr(input)) ) {
        WARNING_MSG("Cannot use set, not a symbol");
        return NULL;
    }
    
    if ( is_primitive(cadr(input)) ) {
        WARNING_MSG("%s is a primitive, cannot be set!",cadr(input)->this.symbol);
    }
    
    print_all_env(meta_environment);
    
    if (!is_in_Env(cadr(input)->this.symbol,meta_environment) ) {
        WARNING_MSG("Cannot use set, variable '%s' not defined",cadr(input)->this.symbol);
        return NULL;
    }
    
    string symbol;
    strcpy(symbol,cadr(input)->this.symbol);
    object valeur = sfs_eval(caddr(input),meta_environment);
    
    if (valeur == NULL) {
        WARNING_MSG("Cannot use set, valeur is NULL");
        return NULL;
    }
    
    changeVarAllEnvironment( symbol, valeur, meta_environment );
    if (meta_environment == NULL) {
        ERROR_MSG("Problem with changeVarEnvironment");
    }
    object o = make_notype();
    return o;
}


object eval_if( object input, object meta_environment ) {
    
    
    if ( cdddr(input) == NULL ) {
        WARNING_MSG("%s-operator must have at least 1 expression",car(input)->this.symbol);
        return NULL;
    }
    if ( !is_nil(cdddr(input)) && !is_pair(cdddr(input)) ) {
        WARNING_MSG("%s-operator must have valid expression",car(input)->this.symbol);
        return NULL;
    }
    
    object o_first_arg = sfs_eval(cadr(input),meta_environment);
    
    if (o_first_arg->type != SFS_BOOLEAN) {
        WARNING_MSG("EVAL_IF cannot be used, first argument is not a boolean");
        return NULL;
    }
    
    if ( is_nil(cdddr(input)) ) {
        if ( o_first_arg == vrai ) {
            return sfs_eval(caddr(input),meta_environment);
        }
        else {
            return faux;
        }
    }
    
    else if ( cddddr(input) != NULL && is_nil(cddddr(input)) ) {
        if ( o_first_arg == vrai ) {
            return sfs_eval(caddr(input),meta_environment);
        }
        else {
            if ( is_nil(cdddr(input)) ) {
                return faux;
            }
            else {
                return sfs_eval(cadddr(input),meta_environment);
            }
        }
    }
    WARNING_MSG("%s-operator isn't in the right format",car(input)->this.symbol);
    return NULL;
}

object eval_and( object input, object meta_environment ) {
    
    if ( is_nil(cdr(input)) ) {
        return faux;
    }
    
    object o_and = input;
    
    while ( !is_nil(cddr(o_and)) ) {
        o_and = cdr(o_and);
        
        if ( sfs_eval(car(o_and),meta_environment) == NULL
            || sfs_eval(car(o_and),meta_environment)->type != SFS_BOOLEAN ) {
            WARNING_MSG("EVAL_AND cannot be used, 1 argument is not a boolean");
            return NULL;
        }
        
        if ( sfs_eval(car(o_and),meta_environment) == faux ) {
            return faux;
        }
    }
    if (sfs_eval(cadr(o_and),meta_environment) == faux) {
        return faux;
    }
    return vrai;
}

object eval_or( object input, object meta_environment ) {
    
    if ( is_nil(cdr(input)) ) {
        return vrai;
    }
    
    object o_or = input;
    
    while ( !is_nil(cddr(o_or)) ) {
        o_or = cdr(o_or);
        
        if ( sfs_eval(car(o_or),meta_environment) == NULL
            || sfs_eval(car(o_or),meta_environment)->type != SFS_BOOLEAN ) {
            WARNING_MSG("EVAL_OR cannot be used, 1 argument is not a boolean");
            return NULL;
        }
        
        if ( sfs_eval(car(o_or),meta_environment) == vrai ) {
            return vrai;
        }
    }
    if (sfs_eval(cadr(o_or),meta_environment) == vrai) {
        return vrai;
    }
    return faux;
}

object eval_begin( object input, object meta_environment ) {
    if ( input == NULL || is_nil(input) ) {
        WARNING_MSG("begin form needs at least one argument");
        return NULL;
    }
    object o_begin = input;
    o_begin = eval_argument(o_begin,meta_environment);
    
    if (o_begin == NULL) {
            return NULL;
        }

    while ( is_pair(cdr(o_begin)) ) {

        o_begin = cdr(o_begin);

    }
    return car(o_begin);
}

object eval_let( object input, object meta_environment ) {
    return input;
}


/* FONCTIONS ENVIRONNEMENTALES */

object newEnvironment( object meta_environment ) {
    
    object newEnv = make_pair();
    newEnv->this.pair.car = make_nil();
    newEnv->this.pair.cdr = meta_environment;
    
    return newEnv;
}


void newVarEnvironment( string symbol, object valeur, object meta_environment ) {
    
    object newPair = make_pair();
    
    uint i=0;
    newPair->this.pair.car = make_pair();
    newPair->this.pair.car->this.pair.car = read_atom_symbol(symbol,&i);
    newPair->this.pair.car->this.pair.cdr = valeur;
    newPair->this.pair.cdr = meta_environment->this.pair.car;
    meta_environment->this.pair.car = newPair;
}

void changeVarEnvironment( string symbol, object valeur, object meta_environment ) {
    
    object EnvCopy = car(meta_environment);
    while ( !is_nil(EnvCopy) ) {
        if ( strcmp(symbol,caar(EnvCopy)->this.symbol) == 0 ) {
            EnvCopy->this.pair.car->this.pair.cdr=valeur;
        }
        EnvCopy = cdr(EnvCopy);
    }
}

void changeVarAllEnvironment( string symbol, object valeur, object meta_environment) {
    object EnvCopyLevel = meta_environment;
    object EnvCopyArguments = car(EnvCopyLevel);
    
    while ( !is_nil(EnvCopyLevel) ) {
        DEBUG_MSG("ChangeVarAllEnvironment p_Env %p",EnvCopyLevel);
        while ( !is_nil( EnvCopyArguments ) ) {
            if ( strcmp(symbol,caar(EnvCopyArguments)->this.symbol) == 0 ) {
                EnvCopyArguments->this.pair.car->this.pair.cdr=valeur;
            }
            EnvCopyArguments = cdr(EnvCopyArguments);
        }
        EnvCopyLevel = cdr(EnvCopyLevel);
        if ( !is_nil(EnvCopyLevel) ) {
            EnvCopyArguments=car(EnvCopyLevel);
        }
    }
}

void print_environment( object meta_environment ) {
    DEBUG_MSG("***********************");
    DEBUG_MSG("Environnement");
    object EnvCopy = car(meta_environment);
    while ( !is_nil(EnvCopy) ) {
        DEBUG_MSG("%s    type %d",caar(EnvCopy)->this.symbol,cdar(EnvCopy)->type);
        EnvCopy = cdr(EnvCopy);
    }
    DEBUG_MSG("***********************");
}

void print_all_env( object meta_environment ) {
    int i = 1;
    object EnvCopyLevel= meta_environment;
    object EnvCopyArguments = car(meta_environment);
    while ( !is_nil(EnvCopyLevel) ) {
        DEBUG_MSG("***********************");
        DEBUG_MSG("Environnement %d",i);
        while (!is_nil(EnvCopyArguments)) {
            DEBUG_MSG("%s    type %d",caar(EnvCopyArguments)->this.symbol,cdar(EnvCopyArguments)->type);
            EnvCopyArguments = cdr(EnvCopyArguments);
        }
        EnvCopyLevel=cdr(EnvCopyLevel);
        DEBUG_MSG("***********************");
        if ( !is_nil(EnvCopyLevel) ) {
            EnvCopyArguments=car(EnvCopyLevel);
            i++;
        }
    }
    
}
