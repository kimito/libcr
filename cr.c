#include<stdlib.h>
#include<ucontext.h>
#include"cr.h"

static cr_context *now_context = NULL;
static const unsigned int STACK_SIZE = 16*1024;


cr_context* create_context_for( void (*func)(void) )
{
  cr_context *ret = NULL;

  if( func == NULL ){
    return NULL;
  }

  ret = (cr_context*)malloc( sizeof(cr_context) );
  ret->parent = now_context;

  if( ret != NULL && getcontext( &(ret->to) ) == 0 ){
    ucontext_t *to = &(ret->to);
    
    if( (to->uc_stack.ss_sp = malloc( STACK_SIZE )) != NULL ){
      to->uc_stack.ss_size = STACK_SIZE;
      to->uc_link = &(ret->from);
      makecontext(to, func, 0);
    }
    else{
      free(ret);
    }

  }

  return ret;
  
}

void destroy_context( cr_context* context )
{
  if( context ){
    if( context->to.uc_stack.ss_sp ){
      free( context->to.uc_stack.ss_sp );
    }

    free( context );
  }
}

void resume( cr_context *context )
{
  now_context = context;
  swapcontext( &(context->from), &(context->to) );
}

void yield()
{
  if( now_context ){
    cr_context *tmp = now_context;

    now_context = tmp->parent;

    swapcontext( &(tmp->to), &(tmp->from) );
  }
}

