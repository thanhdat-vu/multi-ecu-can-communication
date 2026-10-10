#ifndef LIS331HHIF_TYPES_H
#define LIS331HHIF_TYPES_H
#include "Std_Types.h"
typedef struct {
    sint16 x;
    sint16 y; 
    sint16 z; 
} Lis331hhIf_AxesType;

typedef Lis331hhIf_AxesType LIS331HH_Axes_t;
#endif
