#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#define MAX_SEG 100
int main()
{
    FILE *fpRead,*fpWrite=NULL;
    char *buff;
    char wbuff[128],*pwbuff;
    char mergebuff[300];
    char *pSegment[MAX_SEG];
    int length;
    int i,j,k,temp,segmentNum;
    int flag,round;
    if((fpRead=fopen("source","rb+"))==NULL)
    {
        printf("can not open template file\n");
    //    sleep(2);
        getchar();
        return 1;
    }
    fseek(fpRead,0,SEEK_END);
    length=ftell(fpRead);
    buff=(char *)malloc(sizeof(char)*(length+1));
    fseek(fpRead,0,SEEK_SET);
    printf("length %d\n",length);
   // fgets(buff,length+1,fpRead);
    fread(buff,sizeof(char),length,fpRead);
    fclose(fpRead);
 //   puts(buff);
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
 //       sleep(2);
        getchar();
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
            while(i<sizeof(wbuff)&&wbuff[i]!=','&&wbuff[i]!='.')
                i++;
            if(wbuff[i]==','||wbuff[i]=='.')
                flag=1;
            else
                flag=0;
            wbuff[i]=0;
            i++;
            while(i<sizeof(wbuff)&&wbuff[i])
                if(wbuff[i]==10||wbuff[i]==13)
                    i++;
                else
                    break;
            strcat(mergebuff,pwbuff);
            pwbuff=wbuff+i;
            if(flag)
            {
                if(fpWrite==NULL)
                {
                    fpWrite=fopen(mergebuff,"wb+");
                    fputs(pSegment[0],fpWrite);
                    fputs(mergebuff,fpWrite);
                    mergebuff[0]=0;
                    round=1;
                }
                else
                    if(round<segmentNum-2)
                    {
                        fputs(pSegment[round++],fpWrite);
                        fputs(mergebuff,fpWrite);
                        mergebuff[0]=0;
                    }
                    else
                        {
                            fputs(pSegment[round++],fpWrite);
                            fputs(mergebuff,fpWrite);
                            mergebuff[0]=0;
                            fputs(pSegment[round],fpWrite);
                            fclose(fpWrite);
                            fpWrite=NULL;
                        }
            }
        }
    }
    return 0;
}
