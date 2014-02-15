#ifndef CR_CONTEXT_H
#define CR_CONTEXT_H

#include<ucontext.h>

typedef struct tag_cr_context{
  struct tag_cr_context *parent;
  ucontext_t from;
  ucontext_t to;
} cr_context;


cr_context* create_context_for( void (*func)(void) );

void destroy_context( cr_context* context );

void resume( cr_context *context );

void yield();


#endif /*CR_CONTEXT_H*/
