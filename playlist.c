#include <stdio.h>
#include "playlist.h"
#include <stdlib.h>
#include <string.h>

playlist *newplaylist() {
    playlist *queue = malloc(sizeof(playlist));

    if(queue==NULL) {
        printf("COULDNT CREATE NEW PLAYLIST! ERROR!!\n");
        return NULL;
    }
    queue->head = NULL;
    queue->curr = NULL;
    queue->last = NULL;

    return queue;
}

void addsongtoplaylist(playlist* queue,song *s) {

    if(queue==NULL) {
        printf("PLAYLIST DOESN'T EXIST!");
        return;
    }

    if(s==NULL) {
        return;
    }

    if(queue->head ==NULL) {
        queue->head = malloc(sizeof(pnode));


        if(queue->head == NULL) {
            printf("ERROR in Memory Allocation (playlist.c <25>)");
            return;
        }

        queue->head->s = s;
        queue->head->next = queue->head;
        queue->last = queue->head;
        queue->curr = queue->head;
        return;
    }

    pnode *new = malloc(sizeof(pnode));
    new->s = s;
    new->next = queue->head;

    queue->last->next = new;
    queue->last = new;

}

void addalbumtoplaylist(playlist *queue,album *alb) {
    if(queue==NULL) {
        printf("PLAYLIST DOESN'T EXIST! COULDN'T ADD ALBUM TO PLAYLIST\n");
        return;
    }

    if(alb==NULL) {
        printf("ALBUM DOESN'T EXIST! COULDN'T ADD ALBUM TO PLAYLIST\n");
        return;
    }

    if(alb->head == NULL) {
        return;
    }

    songnode *temp = alb->head;

    while(temp!=NULL) {
        addsongtoplaylist(queue,temp->s);
        temp = temp->next;
    }

    printf("\nADDED ALBUM %s TO PLAYLIST\n",alb->name);
}

void resetplaylist(playlist* queue) {
    if (queue == NULL) {
        printf("Playlist doesn't Exist\n");
        return;
    } 
    if(queue->head == NULL){
        printf("PLAYLIST DOESN'T CONTAIN SONGS! KINDLY ADD SONGS.\n");
        return;
    }
        
    queue->curr = queue->head;
    printf("PLAYING %s by %s\n",queue->curr->s->name,queue->curr->s->artist);

}

void playnextsong(playlist *queue) {

    if(queue==NULL) {
        printf("PLAYLIST DOESN'T EXIST! COULDN'T PLAY\n");
        return;
    }

    if(queue->head == NULL) {
        printf("PLAYLIST DOESN'T CONTAIN SONGS! KINDLY ADD SONGS\n");
        return;
    } 

    queue->curr = queue->curr->next;
    printf("\nPLAYING %s by %s\n",queue->curr->s->name,queue->curr->s->artist);
}

void playprevsong(playlist *queue){

    if(queue == NULL) {
        printf("PLAYLIST DOESN'T EXIST! COULDN'T PLAY\n");
        return;
    }

    if(queue->head == NULL) {
        printf("PLAYLIST DOESN'T CONTAIN SONGS! KINDLY ADD SONGS\n");
        return;
    }

    if(queue->head == queue->head->next) {
        printf("\nPLAYING %s by %s\n",queue->curr->s->name,queue->curr->s->artist);
        return;
    }

    pnode *temp = queue->head;

    while(temp->next!=queue->curr) {
        temp = temp->next;
    }

    queue->curr = temp;

    printf("\nPLAYING %s by %s\n",queue->curr->s->name,queue->curr->s->artist);
}

void removesongfromplaylist(playlist *queue, int songid){

    if(queue == NULL || queue->head == NULL){
        printf("PLAYLIST IS EMPTY! COULDN'T REMOVE SONG.\n");
        return;
    }

    pnode *temp = queue->head;
    pnode *prev = queue->last;
    pnode *todelete = NULL;

    if (queue->head == queue->last) {
        if (queue->head->s->id == songid) {
            todelete = queue->head;
            queue->head = NULL;
            queue->curr = NULL;
            queue->last = NULL;
            free(todelete);
            printf("SONG WITH ID %d REMOVED. PLAYLIST IS NOW EMPTY\n", songid);
            return;
        }
        printf("SONG NOT FOUND IN PLAYLIST\n");
        return;
    }

    if (queue->head->s->id == songid) {
        todelete = queue->head;
        queue->head = queue->head->next;
        queue->last->next = queue->head;   
        queue->curr = queue->head;
        free(todelete);
        printf("REMOVED SONG ID %d FROM PLAYLIST.\n", songid);
        return;
    }

    do {
        if (temp->s->id == songid) {
            todelete= temp;
            prev->next= temp->next;

            if(todelete == queue->last) {
                queue->last= prev;
            }

            queue->curr= queue->head;

            free(todelete);
            printf("REMOVED SONG ID %d FROM PLAYLIST\n", songid);
            return;
        }

        prev = temp;
        temp = temp->next;

    } while(temp!=queue->head);

    printf("SONG ID %d NOT FOUND IN PLAYLIST.\n", songid);
}

void listplaylist(playlist *queue){

     if(queue == NULL || queue->head == NULL){
        printf("PLAYLIST IS EMPTY!\n");
        return;
    }

    printf("\n%-5s %-25s %-20s %-10s\n", "ID", "Title", "Artist", "Duration");
    printf("-------------------------------------------------------------------------------\n");

    pnode *temp= queue->head;

    do {
        int minutes = temp->s->duration/60;
        int seconds = temp->s->duration%60;

        printf("%-5d %-25s %-20s %02d:%02d\n",temp->s->id,temp->s->name,temp->s->artist,minutes,seconds);
        temp= temp->next;
    } while(temp!=queue->head);

}

void freeplaylist(playlist *queue){
    if (queue== NULL)
        return;

    pnode *head1 = queue->head;
    if (head1!= NULL) {
        pnode *start = head1->next;
        pnode *temp = start->next;
        

        while (temp!= start) {
            pnode *next = temp->next;
            free(temp);
            temp = next;
        }

        free(start);
    }

    free(queue);
}


