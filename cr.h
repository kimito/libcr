#ifndef CR_CONTEXT_H
#define CR_CONTEXT_H


struct ucontext;
typedef struct ucontext cr_context;


cr_context* create_context_for( void (*func)(void) );

void destroy_context( cr_context* context );

void resume( cr_context *context );

void yield();


#endif /*CR_CONTEXT_H*/
