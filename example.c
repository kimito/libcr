#include<stdio.h>
#include<stdlib.h>
#include"cr.h"

int i = 0;

void func()
{
  int j = 3;

  i++;

  yield();

  i+=2;
  j++;

  printf("j = %d\n", j);

  yield();

  printf("never come\n", j);
}


int main(int argc, char *argv[]){
  cr_context *ctx_func = create_context_for( func );

  if( !ctx_func ){
    return -1;
  }

  printf("start : i = %d\n", i);

  resume( ctx_func );

  printf("i = %d\n", i);

  resume( ctx_func );
  
  printf("i = %d\n", i);

  destroy_context( ctx_func );

  return 0;
}
