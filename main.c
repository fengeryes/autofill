#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#inlcude<string.h>
#define MAX_SEG 10
int main()
{
    FILE *fpRead,*fpWrite=NULL;
    char *buff;
    char *wbuff[80],*pwbuff;
    char mergebuff[30];
    char *pSegment[MAX_SEG];
    int length;
    int i,j,k,temp,segmentNum;
    int flag,round;
    if((fpRead=fopen("source","rb+"))==NULL)
    {
        printf("can not open template file\n");
        sleep(2);
        return 1;
    }
    printf("file read success\n");
    fseek(fpRead,0,SEEK_END);
    length=ftell(fpRead);
    buff=(char *)malloc(sizeof(char)*(length+1));
    fseek(fpRead,0,SEEK_SET);
    fgets(buff,length+1,fpRead);
    fclose(fpRead);
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
    segmentNum=i+1;
    /////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////
    if((fpRead=fopen("element","rb+"))==NULL)
    {
        printf("can not open element file\n");
        sleep(2);
        return 2;
    }
    round=0;
    mergebuff[0]=0;
    while(fgets(wbuff,sizeof(wbuff),fpRead))
    {
        i=0;
        pwbuff=wbuff;
        while(i<sizeof(wbuff)&&wbuff[i])
        {
            while(wbuff[i]&&wbuff[i]!=',')
                i++;
            wbuff[i]=0;
            strcat(mergebuff,pwbuff);
            pwbuff=pwbuff+i+1;
            if(fpWrite==NULL)
                fpWrite=fopen(mergebuff,"wb+");
            switch(mode)
            {
                case 0:break;//creat a new file;
                case 1:break;//file
            }
        }

    }

    return 0;
}
