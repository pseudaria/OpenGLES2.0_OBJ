#include <stdio.h>

void main(void)
{
  char s[6];
  float f_r=0.0;
  float f_g=0.0;
  float f_b=0.0;
  int i;
  printf("Input RGB data RRGGBB , 6 char\nRRGGBB = ");
  gets(s);
  for(i = 0; i<6; i++)
    {
      if( 47<s[i] && s[i]<58 )
	{
	  s[i]=s[i]-48;
	}
      else if( 64<s[i] && s[i]<71 )
	{
	  s[i]=s[i]-55;
	}
      else
	return;
    }
  f_r = (float)s[0]*16+(float)s[1];
  f_g = (float)s[2]*16+(float)s[3];
  f_b = (float)s[4]*16+(float)s[5];
  printf("R  ,G  ,B \n%f , %f, %f \n",f_r,f_g,f_b);
  f_r = f_r/255;
  f_g = f_g/255;
  f_b = f_b/255;
  printf("R  ,G  ,B \n%f , %f, %f \n",f_r,f_g,f_b);
}
