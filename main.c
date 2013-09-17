#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    char *buff;
    int length;
    if((fp=fopen("source","rb+"))==NULL)
        return 1;
    printf("file read success\n");
    fseek(fp,0,SEEK_END);
    length=ftell(fp);
    buff=(char *)malloc(sizeof(char)*(length+1));
    fseek(fp,0,SEEK_SET);
    fgets(buff,length+1,fp);
    puts(buff);
    return 0;
}
