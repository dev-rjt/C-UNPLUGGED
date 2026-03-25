#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"
#include "album.h"
#include "playlist.h"

void commands() {
    printf("COMMAND MENU\n");
    printf("-----------------------------------------\n");
    printf("1.  List All Songs Present In Library\n");
    printf("2.  Create New Album\n");
    printf("3.  Add Song To Existing Album\n");
    printf("4.  Remove Song From Existing Album\n");
    printf("5.  List All Albums\n");
    printf("6.  List All Songs Present In An Album\n");
    printf("7.  Add Song To Playlist \n");
    printf("8.  Add Album To PLaylist\n");
    printf("9.  Start Playing From start\n");
    printf("10. Play Next Song\n");
    printf("11. Play Previous Song\n");
    printf("12. Remove Song From Playlist\n");
    printf("13. List All Songs In Playlist\n");
    printf("14. View History\n");
    printf("15. EXIT\n");
    
}

void logcommand(const char *command) {
    FILE *log = fopen("log.txt", "a");
    if(log==NULL) return;

    fprintf(log, "%s\n", command);

    fclose(log);
}

void displayhistory() {
    FILE *fp = fopen("log.txt", "r");
    if (fp == NULL) {
        printf("No history found.\n");
        return;
    }

    printf("\n----- Command History -----\n");

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}


int main() {
    printf("\n");
    printf("HI! WELCOME TO C-Unplugged!\n");
    song *library_head = loadsongsintoll("songs.txt");
    album *albums_head = loadalbums("album.txt",library_head);
    playlist *queue = newplaylist();


    int input=0;

    // number of albums present before
    int numalb = 0;
    album* temp = albums_head;

    while(temp!=NULL) {
        numalb++;
        temp = temp->next;
    }

    while(input!=15) {
        printf("\n");
        commands();
        printf("\nPLEASE INPUT COMMAND NUMBER - ");
        scanf("%d",&input);
        printf("\n");


        switch(input) {
            case 1 : 
            listallsongs(library_head);
            logcommand("1.List_All_Songs_Present_In_Library");
            break;

            case 2 :
            logcommand("2.Create_New_Album");
            int id = ++numalb;
            char albname[100];
            printf("Enter Album Name - ");
            scanf("%s",albname);
            album* new = createnewalbum(id,albname);

            if(albums_head == NULL) {
                albums_head = new;
            }

            else{
                album *t = albums_head;
                while(t->next) {
                    t = t->next;
                }
                t->next = new;
            }

            savealbums(albums_head,"album.txt");
            printf("Album saved successfully.\n");
            break;

            case 3:
            logcommand("3.Add_Song_To_Existing_Album");
            if(albums_head==NULL) {
                printf("No Albums Present.Create a new album.\n");
                break;
            }
            listallalb(albums_head);
            int albid;
            printf("\nENTER ALBUM ID : ");
            scanf("%d",&albid);
            printf("\n");
            album *alb = findalb(albums_head,albid);
            if(alb==NULL) {
                printf("Album Doesn't Exist\n");
                break;
            }
            listallsongs(library_head);
            int songid;
            printf("\n");
            printf("ENTER SONG ID :");
            scanf("%d",&songid);
            printf("\n");
            song *s = findsong(library_head,songid);
            if(s==NULL) {
                printf("Song Doesn't Exist!\n");
                break;
            }
            addsongtoalb(alb,s);
            savealbums(albums_head,"album.txt");
            printf("SONG ADDED SUCCESFULLY.");
            printf("\n");
            break;


            case 4:
            logcommand("4.Remove_Song_From_Existing_Album");
            if(albums_head==NULL) {
                printf("No Albums Present.Create a new album.\n");
                break;
            }
            listallalb(albums_head);
            int albid2;
            printf("\nENTER ALBUM ID :");
            scanf("%d",&albid2);
            printf("\n");
            album *alb2 = findalb(albums_head,albid2);
            if(alb2==NULL) {
                printf("Album Doesn't Exist.\n");
                break;
            }
            listsongsinalb(alb2);
            int songid2;
            printf("\n");
            printf("ENTER SONG ID :");
            scanf("%d",&songid2);
            printf("\n");
            int x = deletesongfromalb(alb2,songid2);
            savealbums(albums_head,"album.txt");
            if(x==1) printf("SONG REMOVED SUCCESFULLY.");
            printf("\n");
            break;


            case 5 :
            listallalb(albums_head);
            logcommand("5.List_All_Albums");
            break;
            
            case 6:
            logcommand("6.List_All_Songs_Present_In_An_Album");
            if(albums_head==NULL) {
                printf("No Albums Present.Create a new album.\n");
                break;
            }
            listallalb(albums_head);
            int albid3;
            printf("ENTER ALBUM ID :");
            scanf("%d",&albid3);
            printf("\n");
            album *alb3 = findalb(albums_head,albid3);
            if(alb3==NULL) {
                printf("ERROR\n");
                break;
            }
            listsongsinalb(alb3);
            break;


            case 7:
            logcommand("7.Add_Song_To_Playlist");
            listallsongs(library_head);
            int songid7;
            printf("\n");
            printf("ENTER SONG ID :");
            scanf("%d",&songid7);
            printf("\n");
            song *s7 = findsong(library_head,songid7);
            if(s7==NULL) {
                printf("INVALID SONG ID.\n");
                break;
            }

            addsongtoplaylist(queue,s7);
            printf("ADDED TO PLAYLIST!\n");
            break;

            
            case 8:
            logcommand("8.Add_Album_To_PLaylist");
            if(albums_head==NULL) {
                printf("No Albums Present.Create a new album.\n");
                break;
            }
            listallalb(albums_head);
            printf("\n");
            int albid8;
            printf("Enter Album Id:");
            scanf("%d",&albid8);
            album *alb8 = findalb(albums_head,albid8);
            if(alb8 == NULL) {
                printf("Album doesn't exist\n");
                break;
            }
            if(alb8->head==NULL) {
                printf("Album doesn't contain any songs.\n");
                break;
            }
            addalbumtoplaylist(queue,alb8);
            break;

            case 9:
            
            logcommand("9.Start_Playing_From_start");
            resetplaylist(queue);
            printf("\n");
            break;

            case 10 :
            logcommand("10.Play_Next_Song");
            playnextsong(queue);
            printf("\n");
            break;

            case 11:
            logcommand("11.Play_Previous_Song");
            playprevsong(queue);
            printf("\n");
            break;

            case 12:
            logcommand("12.Remove_Song_From_Playlist");
            if(queue->head == NULL) {
                printf("PLAYLIST IS EMPTY!\n");
                break;
            }
            listplaylist(queue);
            int songid12;
            printf("\n");
            printf("ENTER SONG ID :");
            scanf("%d",&songid12);
            printf("\n");
            removesongfromplaylist(queue,songid12);
            break;

            case 13:
            logcommand("13.List_All_Songs_In_Playlist");
            listplaylist(queue);
            printf("\n");
            break;

            case 14:
            logcommand("14.View History");
            displayhistory();
            break;

            case 15:
            logcommand("15.EXIT");
            FILE *log = fopen("log.txt", "a");
            if(log!=NULL) fprintf(log,"\n");
            fclose(log); 
            break;

            default :
            printf("INVALID COMMAND\n");

            
        }

    }

    if(queue){
        freeplaylist(queue); 
        queue = NULL; } 
    if(albums_head) {
        freeallalbums(albums_head);
        albums_head = NULL;
    } 
    if(library_head){
        freesongs(library_head); 
        library_head = NULL;
    } 
    printf("Bye!\n");
    
    return 0;

}