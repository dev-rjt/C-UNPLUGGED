#include "album.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

album *createnewalbum(int id,char *name) {
    album *new = malloc(sizeof(album));
    if(new==NULL) {
        printf("COULDN'T CREATE NEW PROBLEM! ERROR!!\n");
        return NULL;
    }

    new->id = id;
    strcpy(new->name,name);
    new->numsongs = 0;
    new->head = NULL;
    new->next = NULL;

    printf("Successfully Created Album With Name %s.\n",new->name);

    return new;
}

void addsongtoalb(album *alb,song* s) {

    if(alb==NULL){
        printf("Album Doesn't Exist. Enter Valid Album ID.\n");
        return;
    }

    if(s==NULL) {
        printf("Song Doesn't Exist.\n");
        return;
    }


    songnode *new = malloc(sizeof(songnode));

    if(new==NULL) {
        printf("Memory allocation failed for song node!\n");
        return;
    }

    new->s = s;
    new->next = NULL;

    if (alb->head == NULL) {
        alb->head = new;
    } 

    else {
        songnode *temp = alb->head;

        while(temp->next!=NULL) {
            temp = temp->next;
        }

        temp->next = new;
    }

    alb->numsongs++;



}

int deletesongfromalb(album *alb,int songid) {
    if(alb==NULL) {
        return 0;
    }

    if(alb->head==NULL) {
        printf("NO SONGS IN ALBUM! CANNOT REMOVE SONG!\n");
        return 0;
    }

    songnode* temp = alb->head;
    songnode *prev = NULL;

    while(temp!=NULL) {
        if(temp->s->id == songid) {

            if(prev!=NULL) {
                prev->next = temp->next;
            }

            else{
                alb->head = temp->next;
            }

            free(temp);
            alb->numsongs -=1;
            return 1;
            
        }
        prev = temp;
        temp = temp->next;
        
    }

    printf("Song ID %d not found in album %s.\n", songid, alb->name);
    return 0;



}

void listallalb(album *head) {
    if(head==NULL) {
        printf("No Albums Present.Create a new album.\n");
        return;
    }

    album *temp = head;
    printf("\nAlbums in Library:\n");
    printf("----------------------------\n");

     while (temp!=NULL) {
        printf("ID: %d, Name: %s, Number of Songs: %d\n", temp->id, temp->name, temp->numsongs);
        temp = temp->next;
    }
}

void listsongsinalb(album *alb) {
    if(alb==NULL) {
        printf("Album doesn't Exist.");
        return;
    }

    printf("\nAlbum ID: %d, Name: %s, Total Songs: %d\n", alb->id, alb->name, alb->numsongs);
    printf("--------------------------------------------------------------------------------------------------\n\n");

    songnode *temp = alb->head;
    if(temp==NULL) printf("NO SONGS IN ALBUM\n");
    int count = 1;
    while (temp) {
        int min = temp->s->duration/60;
        int sec = temp->s->duration%60;
        printf("%d. %s by %s (%02d:%02d) with SongID %d\n", count, temp->s->name, temp->s->artist, min,sec,temp->s->id);
        temp = temp->next;
        count++;
    }
}

void savealbums(album *head,char *filename) {
    FILE *fp = fopen(filename,"w");

    if(fp==NULL) {
        printf("INVALID ALBUM FILES.CANNOT OVERWRITE!\n");
        return;
    }

    album *temp = head;
    
    while(temp!=NULL) {
        fprintf(fp,"%d %s %d ",temp->id,temp->name,temp->numsongs);

        songnode *songtemp = temp->head;

        while(songtemp!=NULL) {
            fprintf(fp,"%d ",songtemp->s->id);
            songtemp = songtemp->next;
            
        }
        fprintf(fp,"\n");
        temp = temp->next;
    }


    fclose(fp);
}

album* loadalbums(char *filename,song *library) {
    FILE *fp = fopen(filename,"r");

    if(fp==NULL) {
        printf("COULDN'T LOAD ALBUMS!\n");
            return NULL;
    }

    album* head = NULL;
    album *temp = NULL;

    int id;
    char albname[100];
    int numsongs;

    while(fscanf(fp, "%d %s %d ",&id,albname,&numsongs)==3) {

        album *newalbum = createnewalbum(id,albname);
        
        for(int i=0;i<numsongs;i++) {
            int songid;
            fscanf(fp,"%d ",&songid);
            song *s = findsong(library,songid);
            
            if(s==NULL) {
                printf("ERROR!\n");
                return NULL;
            }

            addsongtoalb(newalbum,s);
        }

        if(head==NULL) {
            head = newalbum;
            temp = head;
        }

        else{
            temp->next = newalbum;
            temp = temp->next;
        }
    }

    fclose(fp);
    printf("\nALL PREVIOUS STORED ALBUMS LOADED!!\n");
    return head;
}

void freeallalbums(album *head) {
    album *temp = head;

    while(temp!=NULL) {
        songnode *songtemp = temp->head;
        while(songtemp!=NULL) {
            songnode *next = songtemp->next;
            free(songtemp);
            songtemp = next;
        }

        album *nextalb = temp->next;
        free(temp);
        temp = nextalb;

    }
}

album *findalb(album *head,int id) {
    if(head==NULL) {
        printf("NO ALBUMS EXIST!\n");
        return NULL;
    }

    album *temp = head;

    while(temp!=NULL) {
        if(id == temp->id) {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}