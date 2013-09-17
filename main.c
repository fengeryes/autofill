#include <stdio.h>
#include <stdlib.h>
#define MAX_SEG 10
int main()
{
    FILE *fpRead,*fpWrite;
    char *buff;
    char *pSegment[MAX_SEG];
    int length;
    int i,j,k,temp;
    int flag;
    if((fpRead=fopen("source","rb+"))==NULL)
        return 1;
    printf("file read success\n");
    fseek(fpRead,0,SEEK_END);
    length=ftell(fpRead);
    buff=(char *)malloc(sizeof(char)*(length+1));
    fseek(fpRead,0,SEEK_SET);
    fgets(buff,length+1,fpRead);
    i=0;
    j=1;
    pSegment[i]=buff;
    while(buff[j])
    {
       if(buff[j]=='#')
       {
           flag=1;
           temp=j++;
           for(k=0;(k<3)&&buff[j];k++,j++)
           {
               if(buff[j]!='$')
               {
                   flag=0;
                   j--;
                   break;
               }
           }
           if(flag)
           {
               buff[temp]=0;
               pSegment[++i]=buff+j;
           }
       }
        j++;
    }
    for(j=0;j<=i;j++)
    puts(pSegment[j]);
    return 0;
}
