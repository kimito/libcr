#include<stdlib.h>
#include<ucontext.h>
#include"cr.h"

static cr_context context_main;
static cr_context *now_context = NULL;
static const unsigned int STACK_SIZE = 16*1024;


cr_context* create_context_for( void (*func)(void) )
{
  cr_context *ctx = NULL;

  if( func == NULL ){
    return NULL;
  }

  ctx = (cr_context*)malloc(sizeof(cr_context));

  if( ctx != NULL && getcontext(ctx) == 0 ){
    
    if( (ctx->uc_stack.ss_sp = malloc(STACK_SIZE)) != NULL ){
      ctx->uc_stack.ss_size = STACK_SIZE;
      ctx->uc_link = &context_main;
      makecontext(ctx, func, 0);
    }
    else{
      free(ctx);
    }

  }

  return ctx;
  
}

void destroy_context( cr_context* context )
{
  if( context ){
    free( context );
  }
}

void resume( cr_context *context )
{
  now_context = context;
  swapcontext(&context_main, context);
}

void yield()
{
  if( now_context ){
    swapcontext(now_context, &context_main);
  }
}

