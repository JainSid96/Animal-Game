//BasicIO.c - Dan Mane - Basic IO utilities
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

char* getLine(FILE *fp);
char* getWord(FILE *fp);
int getYesNo();


char *getLine(FILE *fp){
    static char *buf = NULL;
    static size_t buf_size=0;
    
    if (buf==NULL){
    buf_size=512;
    buf = (char *) calloc (buf_size,sizeof(char));
    assert(buf!=NULL);
    }

    int ch;

    while(isspace (ch=fgetc(fp))){
        if (ch==EOF)
            return NULL;
    } //Scans past whitespace preceding the line

    int index=0;

    while(ch!='\n' && ch != EOF){
    //invariants:
    //index < buf_size
    //buf points to buffer of size buf_size
    //buf[0]..buf[index-1] consists of preceding characters in the line
        buf[index++]=ch;
    
        if (index==buf_size){
            buf_size*=2;
            buf=realloc(buf,buf_size);
            assert (buf!=NULL);
        }
    ch=fgetc(fp); 
    }

    buf[index]='\0';
    return buf;
}

char *getWord(FILE *fp){
    static char *buf = NULL;
    static size_t buf_size=0;
    
    if (buf==NULL){
    buf_size=128;
    buf = (char *) calloc (buf_size,sizeof(char));
    assert(buf!=NULL);
    }

    int ch;

    while(isspace (ch=fgetc(fp))){
        if (ch==EOF)
            return NULL;
    } //Scans past whitespace preceding the line


    int index=0;

    while(!isspace(ch) && ch != EOF){
    //invariants:
    //index < buf_size
    //buf points to buffer of size buf_size
    //buf[0]..buf[index-1] consists of preceding characters in the line
        buf[index++]=ch;
    
        if (index==buf_size){
            buf_size*=2;
            buf=realloc(buf,buf_size);
            assert (buf!=NULL);
        }
    ch=fgetc(fp); 
    }

    buf[index]='\0';
    return buf;
}


int getYesNo(){
    int ch;
    printf(" (y/n): ");
    while ( (ch=getchar()) != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')
        ;
    if (ch == 'y' || ch=='Y')
        return 1;
    else
        return 0;
}