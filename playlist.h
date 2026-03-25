#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "album.h"

typedef struct pnode {
    song*s;
    struct pnode *next;
} pnode;

typedef struct playlist {
    pnode *head;
    pnode *curr;
    pnode *last;

} playlist;

playlist *newplaylist();

void addsongtoplaylist(playlist *queue,song *s);

void addalbumtoplaylist(playlist *queue,album* alb);

void resetplaylist(playlist *queue);

void playnextsong(playlist *queue); 

void playprevsong(playlist* queue);

void removesongfromplaylist(playlist *queue,int songid);

void listplaylist(playlist *queue);

void freeplaylist(playlist *queue);

#endif