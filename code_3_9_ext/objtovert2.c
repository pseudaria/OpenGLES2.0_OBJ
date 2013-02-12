#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"openglsb.h"
//Do it & 만들고 실행된후 수정해봐라.
void objtovert2(float vertex[][3],GLubyte p_tri[][3],GLubyte p_quad[][4])
{
  int i=0;
  int k=0;
  int p=0;
  int count=0;
  FILE *fp;
  char c;
  char s[256];
  float bufferf[3];
  int error_check;
  int buffer3d[3];
  int buffer4d[4];
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
	 sscanf(s,"%c %f %f %f",&c,bufferf,bufferf+1,bufferf+2);
	 printf("%d,%c %f %f %f\n",i,c,bufferf[0],bufferf[1],bufferf[2]);
	 //printf("%d :: %c %f %f %f\n",i,c,bufferf[0],bufferf[1],bufferf[2]);
	 vertex[i][0] = bufferf[0];
	 vertex[i][1] = bufferf[1];
	 vertex[i][2] = bufferf[2];
	 i++;
       }
     if(s[0] == 'f')
       {
	 error_check=sscanf(s,"%c %d %d %d %d",&c,buffer4d,buffer4d+1,buffer4d+2,buffer4d+3);
	 if(error_check == 4 && p<32)
	   {
	     sscanf(s,"%c %d %d %d",&c,buffer3d,buffer3d+1,buffer3d+2);
	     p_tri[p][0] = buffer3d[0]-1;
	     p_tri[p][1] = buffer3d[1]-1;
	     p_tri[p][2] = buffer3d[2]-1;
	     // printf("3 %d :: %c %d %d %d\n",p,c,p_tri[p][0],p_tri[p][1],p_tri[p][2]);
	     p++;
	   }
	 else if(error_check == 5 && k<128)
	   {
	     //printf("%d\n",error_check);
	     p_quad[k][0] = buffer4d[0]-1;
	     p_quad[k][1] = buffer4d[1]-1;
	     p_quad[k][2] = buffer4d[2]-1;
	     p_quad[k][3] = buffer4d[3]-1;

	     // printf("4 %d :: %c %d %d %d %d\n",k,c,p_quad[k][0],p_quad[k][1],p_quad[k][2],p_quad[k][3]);
	     k++;
	   }
	 else
	   {
	     printf("Index Read Fail Or End \n");
	     s[0]='x';
	   }
       }
    }
  fclose(fp);
}
