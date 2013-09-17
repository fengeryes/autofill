#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#define MAX_SEG 10
int main()
{
    FILE *fpReadTemplate,*fpReadElement,*fpWrite;
    char *buff;
    char *pSegment[MAX_SEG];
    int length;
    int i,j,k,temp;
    int flag;
    if((fpReadTemplate=fopen("source","rb+"))==NULL)
    {
        printf("can not open template file\n");
        sleep(2);
        return 1;
    }
    printf("file read success\n");
    fseek(fpReadTemplate,0,SEEK_END);
    length=ftell(fpReadTemplate);
    buff=(char *)malloc(sizeof(char)*(length+1));
    fseek(fpReadTemplate,0,SEEK_SET);
    fgets(buff,length+1,fpReadTemplate);
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
    /////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////
    if((fpReadElement=fopen("element","rb+"))==NULL)
    {
        printf("can not open element file\n");
        sleep(2);
        return 2;
    }
    for(j=0;j<=i;j++)
    puts(pSegment[j]);
    return 0;
}
