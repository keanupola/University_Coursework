#include <stdio.h>
#include <string.h>
#include "PlaylistNode.h"

void CreatePlaylistNode(PlaylistNode* thisNode, char id[], char name[], char artist[], int length, PlaylistNode* nextNode) {
    strcpy(thisNode->uniqueID, id);
    strcpy(thisNode->songName, name);
    strcpy(thisNode->artistName, artist);
    thisNode->songLength = length;
    thisNode->nextNodePtr = nextNode;
}

void InsertPlaylistNodeAfter(PlaylistNode* thisNode, PlaylistNode* newNode) {
    newNode->nextNodePtr = thisNode->nextNodePtr;
    thisNode->nextNodePtr = newNode;
}

void SetNextPlaylistNode(PlaylistNode* thisNode, PlaylistNode* newNode) {
    thisNode->nextNodePtr = newNode;
}

PlaylistNode* GetNextPlaylistNode(PlaylistNode* thisNode) {
    return thisNode->nextNodePtr;
}

void PrintPlaylistNode(PlaylistNode* thisNode) {
    printf("Unique ID: %s\n", thisNode->uniqueID);
    printf("Song Name: %s\n", thisNode->songName);
    printf("Artist Name: %s\n", thisNode->artistName);
    printf("Song Length (in seconds): %d\n", thisNode->songLength);
}

