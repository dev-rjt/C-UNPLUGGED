#ifndef ALBUM_H
#define ALBUM_H

#include "library.h"

typedef struct songnode {
    song* s;
    struct songnode *next;
} songnode;

typedef struct album {
    int id;
    char name[100];
    int numsongs;
    songnode *head;
    struct album *next;
} album;

album *createnewalbum(int id,char* name);

void addsongtoalb(album *alb,song *s);

int deletesongfromalb(album *alb,int songid);

void listallalb(album *head);

void listsongsinalb(album *alb);

void savealbums(album *head,char *filename);

album *loadalbums(char*filename, song *library);

void freeallalbums(album *head);

album* findalb(album *head, int id);

#endif 