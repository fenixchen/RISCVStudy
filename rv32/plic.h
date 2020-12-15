#ifndef _PLIC_H_
#define _PLIC_H_

#include <stdint.h>

// plic.c
void            plicinit(void);
void            plicinithart(void);
uint64_t        plic_pending(void);
int             plic_claim(void);
void            plic_complete(int);

#endif
