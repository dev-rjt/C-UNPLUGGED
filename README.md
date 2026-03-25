C-Unplugged

A CLI-based Music Library, Album Manager, and Playlist Player in C

C-Unplugged is a command-line music application written in C that allows users to browse songs, manage albums, build their playlist, and keep a persistent log of all commands across sessions.
The application uses text files for persistent storage and a clean CLI to give users full control over their music library.

Features

Song & Library Management

1. Load songs from a text file containing all data
2. Display all songs available in the library
3. Store songs in structured formats for easy access


Album Management

1. View all albums in the user’s library
2. Create new albums                          
3. Add songs to an album
4. Delete songs from an album

# NOTE - 
Album name input should not contain spaces. 
Wrong - Liked Songs
Right - Liked_Songs (Use underscore instead of spaces)

Added some few basic albums for your convenience.

5. Albums are persistent — saved to file and automatically loaded next time the program runs

Playlist System (Queue)

1. Create and manage a single active music playlist
2. Add albums (entire album) to playlist
3. Add individual songs to playlist
4. Remove songs from playlist
5. Playlist behaves like a looped queue
   When reaching the end → cycles back to the first song
6. Supports next, previous, and replay from start of playlist

# NOTE -
Playlist is queue of songs and is not persistent across runs.

Command Logging (Persistent Log File)

1. Every command run by the user is written to a log.txt file
2. The log file persists across sessions
3. Allows user to view history of all operations across all runs of the application

CLI Interface
A clean command-line interface guides the user through:

1. Viewing songs
2. Managing albums
3. Managing playlist
4. Playing songs
5. Viewing command history

C-Unplugged/
│── main.c               # CLI + program flow
│── library.c            # Song loading & listing
│── album.c              # Album creation, adding, deleting songs
│── playlist.c           # Playlist queue implementation
│── library.h
│── album.h
│── playlist.h
│── songs.txt            # Song database (input)
│── album.txt            # Persistent album storage
│── log.txt              # Persistent command history
│── Makefile
│── README.md

To compile and run -
1. make
or
2. gcc main.c playlist.c album.c library.c -o main
   ./main

CLI COMMANDS-

1.  List All Songs Present In Library
2.  Create New Album
3.  Add Song To Existing Album
4.  Remove Song From Existing Album
5.  List All Albums
6.  List All Songs In An Album
7.  Add Song To Playlist
8.  Add Album To Playlist
9.  Start Playing From Start
10. Play Next Song
11. Play Previous Song
12. Remove Song From Playlist
13. List All Songs In Playlist
14. View History
15. EXIT

Data Persistence

1. Songs
Loaded from songs.txt. #songs.txt is made like -         Song Id     Song Name     Artist Name     Duration

2. Albums
Saved to album.txt upon changes, loaded on program start.  
# NOTE:  
albums.txt is saved in this format -     Album Id    Album Name    Total Number of Songs     Song Ids of Song

3. Playlist
Stored in memory during runtime. Loops cyclically.

4. Command Logs
Stored in log.txt permanently.
Option 14 displays the entire history in CLI.