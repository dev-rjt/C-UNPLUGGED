#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct song {
    int id;
    char name[100];
    char artist[100];
    int duration;
    struct song* next;
} song;

song *loadsongsintoll(char *filename);

void listallsongs(song *head);

void freesongs(song *head);

song* findsong(song *head,int id);



#endif