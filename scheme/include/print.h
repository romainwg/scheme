
/**
 * @file print.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:12:52 2012
 * @brief Printing stuff for SFS.
 *
 * Printing stuff for SFS.
 */

#ifndef _PRINT_H_
#define _PRINT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"


void sfs_print      ( object o, uint *root  );

void sfs_print_atom ( object o              );
void sfs_print_pair ( object o, uint *root  );

#ifdef __cplusplus
}
#endif

#endif /* _PRINT_H_ */
