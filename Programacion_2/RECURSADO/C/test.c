#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
  char nombre[]="MICAEla";
   char *pChar;
  int index = 0;
  for (index = 0; nombre[index]  != '\0' ; index++){
      printf ("\n En el [índice %d] de nombre hay %c \n", index, nombre[index]);
  }
  printf("\n Fin del segundo recorrido ");
  getchar();
}