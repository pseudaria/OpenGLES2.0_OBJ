#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void objtovert2(float vertex[][3])
{
  int i=0;
  FILE *fp;
  char c;
  char s[256];
  float buffer[3];
  fp = fopen("cup.obj","r");
  if(fp==NULL)
    return;
  while(1)
    {
     if(feof(fp))
	break;
     fgets(s,40,fp);
     if(s[0] == 'v') //|| s[0] == 'f')
       {
	 sscanf(s,"%c %f %f %f",&c,buffer,buffer+1,buffer+2);
	 printf("%c %f %f %f\n",c,buffer[0],buffer[1],buffer[2]);
	 vertex[i][0] = buffer[0];
	 vertex[i][1] = buffer[1];
	 vertex[i][2] = buffer[2];
	 i++
       }
    }
  
  fclose(fp);
}
