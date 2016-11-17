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
    make_primitive( "list?"      , &prim_is_list       );
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
	/* GESTION actuelle :
	 * var non déclarée
	 * evaluation des terms
	 * un ou multi arg
	 * entrée/sortie : int et real
	 */
	
		double sommeDouble = 0; /*VOIR SI ON NE PEUT PAS DIRECTEMENT RESTER SUR DOUBLE (condition sur la taille du double)*/
		int sommeInt = 0;
		int integerOuDouble = 0; /*0 si integer passe a 1 si presence d'un double*/
		
		object obj_temp = o; /* "Curseur" de déplacement en object */
		object obj_eval = NULL; /* Var object d'évaluation */
		
	if(car(o)!=NULL){
		obj_eval = sfs_eval(car(obj_temp));
		
		/* verification que l'évaluation donne quelque chose */
		if ( obj_eval == NULL){
			WARNING_MSG("Erreur d'évaluation : la variable n'est peut être pas définie");
			return NULL;
		}
		/* verification que l'évaluation donne bien un nombre */
		if ( !is_number(obj_eval) ) {
			WARNING_MSG("only accepts number");
			return NULL;
		}
		
		if(obj_eval->type == SFS_NUMBER){
			/* Si le premier chiffre est un double -> SWITCH en sortie flottante*/
			if(obj_eval->this.number.numtype == NUM_REAL){
				integerOuDouble = 1;
			}
			
			/* Si int ou double : choix var */
			if(integerOuDouble){
				sommeDouble = obj_eval->this.number.this.real;
			}else{
				sommeInt = obj_eval->this.number.this.integer;
			}
			
		}else{
			WARNING_MSG("PRIM_PLUS WARNING : not evaluable nonumber type");
			return NULL;
		}
		
		while(!is_nil(cdr(obj_temp))){
			obj_eval = sfs_eval(cadr(obj_temp));
			
			/* verification que l'évaluation donne quelque chose */
			if ( obj_eval == NULL){
				WARNING_MSG("Erreur d'évaluation : la variable n'est peut être pas définie");
				return NULL;
			}
			/* verification que l'évaluation donne bien un nombre */
			if ( !is_number(obj_eval) ) {
				WARNING_MSG("only accepts number");
				return NULL;
			}
			
			if(obj_eval->type == SFS_NUMBER){
				/* Si un chiffre est un double -> SWITCH en sortie flottante // cette opération ne peut se faire qu'une fois */
				if(obj_eval->this.number.numtype == NUM_REAL && integerOuDouble != 1){
					integerOuDouble = 1;
					sommeDouble = sommeInt; /* Changement de variable : int -> double*/
				}
				
				/* Adaptation du calcul : int ou double d'après les chiffres antécédants */
				if(integerOuDouble){
					/* On travaille avec une sortie en Double mais les entrées peuvent encore etre int*/
					if(obj_eval->this.number.numtype == NUM_REAL){
						sommeDouble += obj_eval->this.number.this.real;
					}else{
						sommeDouble += obj_eval->this.number.this.integer;
					}
					
				}else{
					sommeInt += obj_eval->this.number.this.integer;
				}
			
			}else{
				WARNING_MSG("PRIM_PLUS WARNING : not evaluable nonumber type");
				return NULL;
			}
			
			obj_temp = cdr(obj_temp);
		}
		
		/* Creation de la sortie en fonction du type de sortie calculé */
		if(integerOuDouble){
			obj_temp = make_real(sommeDouble);
		}else{
			obj_temp = make_integer(sommeInt);
		}
		
	}
	
    return obj_temp;
}

object prim_minus ( object o ) {
    /* GESTION actuelle :
	 * var non déclarée
	 * evaluation des terms
	 * un ou multi arg
	 * entrée/sortie : int et real
	 */
	
	double sommeDouble = 0; /*VOIR SI ON NE PEUT PAS DIRECTEMENT RESTER SUR DOUBLE (condition sur la taille du double)*/
	int sommeInt = 0;
	int integerOuDouble = 0; /*0 si integer passe a 1 si presence d'un double*/
		
	object obj_temp = o; /* "Curseur" de déplacement en object */
	object obj_eval = NULL; /* Var object d'évaluation */
		
	if(car(o)!=NULL){
		obj_eval = sfs_eval(car(obj_temp));
		
		/* verification que l'évaluation donne quelque chose */
		if ( obj_eval == NULL){
			WARNING_MSG("Erreur d'évaluation : la variable n'est peut être pas définie");
			return NULL;
		}
		/* verification que l'évaluation donne bien un nombre */
		if ( !is_number(obj_eval) ) {
			WARNING_MSG("only accepts number");
			return NULL;
		}
		
		if(obj_eval->type == SFS_NUMBER){
			/* Si le premier chiffre est un double -> SWITCH en sortie flottante*/
			if(obj_eval->this.number.numtype == NUM_REAL){
				integerOuDouble = 1;
			}
			
			/* Si int ou double : choix var */
			if(integerOuDouble){
				sommeDouble = obj_eval->this.number.this.real;
			}else{
				sommeInt = obj_eval->this.number.this.integer;
			}
			
		}else{
			WARNING_MSG("PRIM_PLUS WARNING : not evaluable nonumber type");
			return NULL;
		}
		
		
		if(!is_nil(cdr(obj_temp))){ /*si il y plusieurs arguments : boucle ; sinon sortie = -arg1*/
			while(!is_nil(cdr(obj_temp))){
				obj_eval = sfs_eval(cadr(obj_temp));
				
				/* verification que l'évaluation donne quelque chose */
				if ( obj_eval == NULL){
					WARNING_MSG("Erreur d'évaluation : la variable n'est peut être pas définie");
					return NULL;
				}
				/* verification que l'évaluation donne bien un nombre */
				if ( !is_number(obj_eval) ) {
					WARNING_MSG("only accepts number");
					return NULL;
				}
				
				if(obj_eval->type == SFS_NUMBER){
					/* Si un chiffre est un double -> SWITCH en sortie flottante // cette opération ne peut se faire qu'une fois */
					if(obj_eval->this.number.numtype == NUM_REAL && integerOuDouble != 1){
						integerOuDouble = 1;
						sommeDouble = sommeInt; /* Changement de variable : int -> double*/
					}
					
					/* Adaptation du calcul : int ou double d'après les chiffres antécédants */
					if(integerOuDouble){
						/* On travaille avec une sortie en Double mais les entrées peuvent encore etre int*/
						if(obj_eval->this.number.numtype == NUM_REAL){
							sommeDouble -= obj_eval->this.number.this.real;
						}else{
							sommeDouble -= obj_eval->this.number.this.integer;
						}
						
					}else{
						sommeInt -= obj_eval->this.number.this.integer;
					}
				
				}else{
					WARNING_MSG("PRIM_PLUS WARNING : not evaluable nonumber type");
					return NULL;
				}
				
				obj_temp = cdr(obj_temp);
			}
		}else{ /*si il y plusieurs arguments : boucle ; sinon sortie = -arg1*/
			if(integerOuDouble){
				sommeDouble = -sommeDouble;
			}else{
				sommeInt = -sommeInt;
			}
		}
		
		/* Creation de la sortie en fonction du type de sortie calculé */
		if(integerOuDouble){
			obj_temp = make_real(sommeDouble);
		}else{
			obj_temp = make_integer(sommeInt);
		}
		
	}
	
    return obj_temp;
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
    
    o = sfs_eval(car(o));
    if ( is_pair(o) ) {
        WARNING_MSG("sin must have 1 and just 1 argument");
        return NULL;
    }
    
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
    o = sfs_eval(car(o));
    if ( is_pair(o) ) {
        WARNING_MSG("cos must have 1 and just 1 argument");
        return NULL;
    }
    
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
    o = sfs_eval(car(o));
    if ( is_pair(o) ) {
        WARNING_MSG("tan must have 1 and just 1 argument");
        return NULL;
    }
    
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
    o = sfs_eval(car(o));
    if ( is_pair(o) ) {
        WARNING_MSG("abs must have 1 and just 1 argument");
        return NULL;
    }
    
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
    o = sfs_eval(car(o));
    if ( is_pair(o) ) {
        WARNING_MSG("exp must have 1 and just 1 argument");
        return NULL;
    }
    
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
    o = sfs_eval(car(o));
    if ( is_pair(o) ) {
        WARNING_MSG("sqrt must have 1 and just 1 argument");
        return NULL;
    }
    
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
    return o;
}
object prim_is_char ( object o ) {
    return o;
}
object prim_is_list ( object o ) {
    return o;
}
object prim_is_null ( object o ) {
    return o;
}
object prim_is_symbol ( object o ) {
    return o;
}
object prim_is_number ( object o ) {
    return o;
}
object prim_is_pair ( object o ) {
    return o;
}
object prim_is_procedure ( object o ) {
    return o;
}
object prim_is_string ( object o ) {
    return o;
}




object prim_int_char ( object o ) {
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








