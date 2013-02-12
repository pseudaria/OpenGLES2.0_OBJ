#include<stdio.h>

void main()
{
  FILE *fp;
  int i = 1;
  char s[256];
  fp = fopen("cup.obj","r");
  if(fp == NULL)
    return;
  while(1)
    {
      fgets(s,31,fp);
      if(feof(fp))
	break;
      printf("%04d: %s", i, s);
      i++;
  }
  fclose(fp);
}
