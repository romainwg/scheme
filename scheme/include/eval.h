
/**
 * @file eval.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:10:38 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#ifndef _EVAL_H_
#define _EVAL_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "object.h"
#include "aux_eval.h"
#include "is_functions.h"
    
/* SYMBOL */
object eval_define  ( object input );
object eval_set     ( object input );
object eval_if      ( object input );
object eval_and     ( object input );
object eval_or      ( object input );
    
/* OPERATOR */
object eval_calc_operator   ( object input );
object eval_cmp_operator    ( object input );
    
/* EVAL FUNCTION */
object sfs_eval( object input );

#ifdef __cplusplus
}
#endif

#endif /* _EVAL_H_ */
