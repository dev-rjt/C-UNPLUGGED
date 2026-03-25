#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

song* loadsongsintoll(char* filename) {

    FILE *fp = fopen(filename,"r");

    if(fp==NULL) {
        printf("ERROR!/Invalid Input");
        return NULL; 
    }

        song *head = NULL;
        song* temp = NULL;
        int id;
        char songname[100];
        char artist[100];
        int time;
        
        while(fscanf(fp,"%d %s %s %d",&id,songname,artist,&time)!=EOF) {
            song *new = malloc(sizeof(song));
            new->id = id;
            strcpy(new->name,songname);
            strcpy(new->artist,artist);
            new->duration = time;
            new->next = NULL;

            if(head==NULL) {
                head = new;
                temp = head;
            }

            else{
                temp->next = new;
                temp = temp->next;
            }

        }
        fclose(fp);
        printf("\nLOADED SONGS FROM BACKEND!!\n");
        return head;
    }

void listallsongs(song *head) {
    if(head==NULL) {
        printf("NO SONG IN LIBRARY!");
        return;
    }

    printf("\n%-5s %-25s %-20s %-10s\n", "ID", "Title", "Artist", "Duration");
    printf("-------------------------------------------------------------------------------\n");

    song *temp = head;

    while (temp!=NULL) {
        int minutes = temp->duration/60;
        int seconds = temp->duration%60;

        printf("%-5d %-25s %-20s %02d:%02d\n",temp->id, temp->name, temp->artist,minutes, seconds);

        temp = temp->next;
    }

}

song* findsong(song *head, int id) {
    song *temp = head;
    while (temp!=NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void freesongs(song *head) {
    song *temp;
    while (head!=NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}



