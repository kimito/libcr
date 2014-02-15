#include<stdio.h>
#include<stdlib.h>
#include"cr.h"

int i = 0;

void gchild_func()
{
  int k = 0;

  printf("k = %d\n", k);
  yield();

  k++;
  printf("k = %d\n", k);
  yield();
  
}

void child_func()
{
  cr_context *ctx_gchild_func = create_context_for( gchild_func );
  int j = 0;


  printf("j = %d\n", j);
  i++;
  resume( ctx_gchild_func );

  yield();

  i++;
  j++;
  printf("j = %d\n", j);
  resume( ctx_gchild_func );

  destroy_context( ctx_gchild_func );

  yield();

  printf("never come\n", j);
}


int main(int argc, char *argv[]){
  cr_context *ctx_child_func = create_context_for( child_func );

  if( !ctx_child_func ){
    return -1;
  }

  printf("start\ni = %d\n", i);

  resume( ctx_child_func );

  printf("i = %d\n", i);

  resume( ctx_child_func );
  
  printf("i = %d\n", i);

  destroy_context( ctx_child_func );

  return 0;
}
