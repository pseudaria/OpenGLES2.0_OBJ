#include<stdio.h>
#include<stdlib.h>
#include<string.h>



void objtovert(float vertex[][3])
{
  FILE *fp;
  char s[256];
  float buffer[3];
  char buffer_string[36];
  int i = 1;
  int t = 0;
  char *p;
  char *endptr;
  fp = fopen("cup.obj","r");
  if(fp == NULL)
    return;
  while(1)
    {
      t = 0;
      fgets(s,36,fp);
      if(feof(fp))
	break;

      if(s[0]=='v')
	{
	  //printf("This is %04dth vertex\n",i);
	  p = s+2;
	while(p)
	  {
	    buffer[t] = (float)atof(p);
	    //printf("%f\n",buffer[t]);
	    p = strchr(p+1,' ');
	    t += 1;
	  }
	vertex[i][0] = buffer[0];
	vertex[i][1] = buffer[1];
	vertex[i][2] = buffer[2];
	i++;
	}
  }
  fclose(fp);
}

void main()
{
  float vertex[161][3];
  objtovert(vertex);
  int i;
  for(i=0;i<162;i++)
    {
      printf("%04dth Vertex : (%f, %f, %f)\n",i,vertex[i][0],vertex[i][1],vertex[i][2]);
    }  
}
