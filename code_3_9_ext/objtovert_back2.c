#include<stdio.h>

void main()
{
  FILE *fp;
  char s[256];
  int i = 1;
  fp = fopen("cup.obj","r");
  if(fp == NULL)
    return;
  while(1)
    {
      fgets(s,36,fp);
      if(feof(fp))
	break;

      if(s[0]=='v')
	{
	printf("%s",s);
	printf("This is %04dth vertex\n",i);
	i++;
	}
  }
  fclose(fp);
}
