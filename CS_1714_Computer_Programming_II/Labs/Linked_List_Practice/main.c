#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PlaylistNode.h"

void PrintMenu(char playlistTitle[]);
PlaylistNode* ExecuteMenu(char userChoice, char playlistTitle[], PlaylistNode* headNode);

int main(void) {
    char playlistTitle[50];
    char menuChoice;

    printf("Enter playlist's title:\n");
    fgets(playlistTitle, 50, stdin);
    playlistTitle[strcspn(playlistTitle, "\n")] = '\0';

    // Remove '\n' character
    PrintMenu(playlistTitle);

    while (1) {
        printf("Choose an option:\n");
        scanf(" %c", &menuChoice);

        if (menuChoice == 'q') {
            break;
        }

        // Call ExecuteMenu function with user choice
        // Implement other menu options in ExecuteMenu function
    }

    return 0;
}

void PrintMenu(char playlistTitle[]) {
    printf("\n%s PLAYLIST MENU\n", playlistTitle);
    printf("a - Add song\n");
    printf("r - Remove song\n");
    printf("c - Change position of song\n");
    printf("s - Output songs by specific artist\n");
    printf("t - Output total time of playlist (in seconds)\n");
    printf("o - Output full playlist\n");
    printf("q - Quit\n");
}

PlaylistNode* ExecuteMenu(char choice, char* playlistTitle, PlaylistNode* head) {
    PlaylistNode* currentNode;
    PlaylistNode* previousNode;
    PlaylistNode* newNode;
    char uniqueID[50];
    char songName[50];
    char artistName[50];
    int songLength;
    int currentPosition, newPosition;
    int i;

    switch (choice) {
        case 'a':
            printf("ADD SONG\n");
            printf("Enter song's unique ID:\n");
            scanf("%s", uniqueID);
            printf("Enter song's name:\n");
            scanf("%s", songName);
            printf("Enter artist's name:\n");
            scanf("%s", artistName);
            printf("Enter song's length (in seconds):\n");
            scanf("%d", &songLength);

            newNode = (PlaylistNode*) malloc(sizeof(PlaylistNode));
            CreatePlaylistNode(newNode, uniqueID, songName, artistName, songLength, NULL);

            if (head == NULL) {
                head = newNode;
            } else {
                currentNode = head;
                while (currentNode->nextNodePtr != NULL) {
                    currentNode = currentNode->nextNodePtr;
                }
                currentNode->nextNodePtr = newNode;
            }
            break;
        case 'r':
            // Remove song implementation
	    printf("REMOVE SONG\n");
            printf("Enter song's unique ID:\n");
            scanf("%s", uniqueID);

            currentNode = head;
            previousNode = NULL;

            while (currentNode != NULL && strcmp(currentNode->uniqueID, uniqueID) != 0) {
                previousNode = currentNode;
                currentNode = currentNode->nextNodePtr;
            }

            if (currentNode == NULL) {
                printf("Song not found.\n");
            } else {
                if (previousNode == NULL) {
                    head = head->nextNodePtr;
                } else {
                    previousNode->nextNodePtr = currentNode->nextNodePtr;
                }
                printf("\"%s\" removed.\n", currentNode->songName);
                free(currentNode);
            }
            break;
        case 'c':
		int currentPosition, newPosition;
    printf("CHANGE POSITION OF SONG\n");
    printf("Enter song's current position:\n");
    scanf("%d", &currentPosition);
    printf("Enter new position for song:\n");
    scanf("%d", &newPosition);

    PlaylistNode* current = head;
    PlaylistNode* prev = NULL;
    PlaylistNode* temp;
    int count = 1;

    if (currentPosition == newPosition) {
        break;
    }

    while (current != NULL && count < currentPosition) {
        prev = current;
        current = current->nextNodePtr;
        count++;
    }

    if (current == NULL) {
        printf("Invalid position. No changes were made.\n");
        break;
    }

    if (prev != NULL) {
        prev->nextNodePtr = current->nextNodePtr;
    } else {
        head = current->nextNodePtr;
    }

    PlaylistNode* newPrev = NULL;
    temp = head;
    count = 1;

    while (temp != NULL && count < newPosition) {
        newPrev = temp;
        temp = temp->nextNodePtr;
        count++;
    }

    if (newPrev != NULL) {
        current->nextNodePtr = newPrev->nextNodePtr;
        newPrev->nextNodePtr = current;
    } else {
        current->nextNodePtr = head;
        head = current;
    }

    printf("\"%s\" moved to position %d\n", current->songName, newPosition);
    break;
}

        case 's':
            // Output songs by specific artist implementation
		printf("OUTPUT SONGS BY SPECIFIC ARTIST\n");
            printf("Enter artist's name:\n");
            scanf("%s", artistName);

            currentNode = head;
            count = 1;
            while (currentNode != NULL) {
                if (strcmp(currentNode->artistName, artistName) == 0) {
                    printf("%d.\n", count);
                    PrintPlaylistNode(currentNode);
                    printf("\n");
                }
                currentNode = currentNode->nextNodePtr;
                count++;
            }
            break;
        case 't':
            // Output total time of playlist implementation
	printf("OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n");

            currentNode = head;
            totalTime = 0;
            while (currentNode != NULL) {
                totalTime += currentNode->songLength;
                currentNode = currentNode->nextNodePtr;
            }

            printf("Total time: %d seconds\n", totalTime);
            break;

        case 'o':
            // Output full playlist implementation
		printf("%s - OUTPUT FULL PLAYLIST\n", playlistTitle);
            if (head == NULL) {
                printf("Playlist is empty\n");
            } else {
                currentNode = head;
                count = 1;
                while (currentNode != NULL) {
                    printf("%d.\n", count);
                    PrintPlaylistNode(currentNode);
                    printf("\n");
                    currentNode = currentNode->nextNodePtr;
                    count++;
                }
            }
            break;
        case 'q':
            // Quit implementation
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
    return head;
}

