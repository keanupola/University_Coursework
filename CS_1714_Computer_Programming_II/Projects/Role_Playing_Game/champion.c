#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "champion.h"

int level_range[4][2] = {{5, 8}, {1, 4}, {3, 6}, {1, 8}};
//create Champion obj, return ptr to obj
Champion* createChampion() {
        Champion *new_champion = (Champion *)malloc(sizeof(Champion));
        char roles[] = {'M', 'F', 'S', 'T'};
        int random_role = rand() % 4;

        //assign obj vals
        new_champion->role = (ChampionRole)roles[random_role]; //typecast
        //rand % (upper - lower + 1) + lower
        new_champion->level = rand() % (level_range[random_role][1] - level_range[random_role][0] + 1) + level_range[random_role][0];
        new_champion->next = NULL;

        return new_champion;
}

//add champion obj (sorted by level in descending order) to linked list, return head
Champion* addChampion(Champion *head, Champion *c) {
	//head node check
	if (head == NULL || c->level > head->level) {
		c->next = head;
		return c;
	}
	//initialize ptr to traverse list
	Champion *current = head;
	//check EO List and next champion level
	while (current->next != NULL && current->next->level >= c->level) {
		current = current->next;
	}
	//update c b/w current and current->next
	c->next = current->next;
	current->next = c;

	return head;
}

//build list of champions, create and return head
Champion* buildChampionList(int n) {
	Champion *head = NULL;

	for (int i = 0; i < n; i++) {
		Champion *new_champion = createChampion();
		head = addChampion(head, new_champion);
	}
	return head;
}

//traverse list and print champions
void printChampionList(Champion *head) {
    Champion *current = head;
    while (current != NULL) {
        printf("%c%d ", current->role, current->level);
        current = current->next;
    }
    printf("\n");
}

//remove champion at head, return new head if != NULL
Champion* removeChampion(Champion *head) {
	if (head == NULL) {
		return NULL;
	}

	Champion *new_head = head->next;
	free(head); //free space for old head

	return new_head;
}

//remove all champions for list and return NULL
Champion* destroyChampionList(Champion *head) {
    while (head != NULL) {
        head = removeChampion(head);
    }

    return NULL;
}

//convert enum to string
const char *roleToString(ChampionRole role) {
    switch (role) {
        case MAGE:
            return "MAGE";
        case FIGHTER:
            return "FIGHTER";
        case SUPPORT:
            return "SUPPORT";
        case TANK:
            return "TANK";
    }
    return "UNKNOWN";
}


//implement game rules, see "champion.h" for details
void playRound(Champion **player1Head, Champion **player2Head) {
	ChampionRole role1 = (*player1Head)->role;
	int level1 = (*player1Head)->level;
	ChampionRole role2 = (*player2Head)->role;
	int level2 = (*player2Head)->level;
	
	//discard head (card played)
	*player1Head = removeChampion(*player1Head);
	*player2Head = removeChampion(*player2Head);

	//main game logic
	//mage matchups
	if (role1 == MAGE) {
		if (role2 == MAGE) {
			if (level1 == level2) {
				printf("Nothing happens - no penalty or reward.\n");
			} else if (level1 > level2) {
				*player1Head = addChampion(*player1Head, createChampion());
				*player2Head = removeChampion(*player2Head);
				printf("Player 1 (MAGE) wins and gains a new champion.\n");
				printf("Player 2 (MAGE) loses a champion.\n");
			} else {
				*player1Head = removeChampion(*player1Head);
				*player2Head = addChampion(*player2Head, createChampion());
				printf("Player 1 (MAGE) loses a champion.\n");
				printf("Player 2 (MAGE) wins and gains a new champion.\n");
			}
		} else if (role2 == FIGHTER) {
			if (level1 > level2) {
				*player1Head = addChampion(*player1Head, createChampion());
				printf("Player 1 (MAGE) wins and gains a new champion.\n");
				printf("Player 2 (FIGHTER) loses but with no penalty.\n");
			} else if (level1 < level2) {
				*player1Head = removeChampion(*player1Head);
				printf("Player 1 (MAGE) loses a champion.\n");
				printf("Player 2 (FIGHTER) wins but with no reward.\n");
			} else {
				printf("Nothing happens - no penalty or reward.\n");
			}
		} else if (role2 == SUPPORT) {
			if (level1 > level2) {
				*player1Head = addChampion(*player1Head, createChampion());
				*player2Head = removeChampion(*player2Head);
				*player2Head = removeChampion(*player2Head);
				printf("Player 1 (MAGE) wins and gains a new champion.\n");
				printf("Player 2 (SUPPORT) loses two champions.\n");
			} else if (level1 < level2) {
				*player1Head = removeChampion(*player1Head);
				*player2Head = addChampion(*player2Head, createChampion());
				*player2Head = addChampion(*player2Head, createChampion());
				printf("Player 1 (MAGE) loses a champion.\n");
				printf("Player 2 (SUPPORT) wins and gains two new champions.\n");
			} else {
				printf("Nothing happens - no penalty or reward.\n");
			}
		} else { // role2 == TANK
			*player1Head = addChampion(*player1Head, createChampion());
			*player2Head = removeChampion(*player2Head);
			printf("Player 1 (MAGE) wins and gains a new champion.\n");
			printf("Player 2 (TANK) loses a champion.\n");
		}
	}
	//fighter matchups
	else if (role1 == FIGHTER) {
		if (role2 == MAGE) {
			if (level1 > level2) {
				*player2Head = removeChampion(*player2Head);
				printf("Player 1 (FIGHTER) wins but with no reward.\n");
				printf("Player 2 (MAGE) loses a champion.\n");
			} else if (level1 < level2) {
				*player1Head = removeChampion(*player1Head);
				printf("Player 1 (FIGHTER) loses but with no penalty.\n");
				printf("Player 2 (MAGE) wins and gains a new champion.\n");
			} else {
				printf("Nothing happens - no penalty or reward.\n");
			}
		} else if (role2 == FIGHTER) {
			if (level1 == level2) {
				*player1Head = addChampion(*player1Head, createChampion());
				*player2Head = addChampion(*player2Head, createChampion());
				printf("Player 1 (FIGHTER) ties and gains a new champion.\n");
				printf("Player 2 (FIGHTER) ties and gains a new champion.\n");
			} else if (level1 > level2) {
				*player1Head = addChampion(*player1Head, createChampion());
				*player2Head = removeChampion(*player2Head);
				printf("Player 1 (FIGHTER) wins and gains a new champion.\n");
				printf("Player 2 (FIGHTER) loses a champion.\n");
			} else {
				*player1Head = removeChampion(*player1Head);
				*player2Head = addChampion(*player2Head, createChampion());
				printf("Player 1 (FIGHTER) loses a champion.\n");
				printf("Player 2 (FIGHTER) wins and gains a new champion.\n");
			}
		} else if (role2 == SUPPORT) {
			if (level1 > level2) {
				*player2Head = removeChampion(*player2Head);
				printf("Player 1 (FIGHTER) wins but with no reward.\n");
				printf("Player 2 (SUPPORT) loses a champion.\n");
			} else if (level1 < level2) {
				*player1Head = removeChampion(*player1Head);
				printf("Player 1 (FIGHTER) loses but with no penalty.\n");
				printf("Player 2 (SUPPORT) wins and gains a new champion.\n");
			} else {
				printf("Nothing happens - no penalty or reward.\n");
			}
		} else { // role2 == TANK
			*player1Head = addChampion(*player1Head, createChampion());
			printf("Player 1 (FIGHTER) wins and gains a new champion.\n");
			printf("Player 2 (TANK) loses but with no penalty.\n");
		}
	}
	//support matchups
	else if (role1 == SUPPORT) {
		if (role2 == MAGE) {
			if (level1 > level2) {
				*player1Head = addChampion(*player1Head, createChampion());
				*player1Head = addChampion(*player1Head, createChampion());
				*player2Head = removeChampion(*player2Head);
				printf("Player 1 (SUPPORT) wins and gains two new champions.\n");
				printf("Player 2 (MAGE) loses a champion.\n");
			} else if (level1 < level2) {
				*player1Head = removeChampion(*player1Head);
				*player1Head = removeChampion(*player1Head);
				*player2Head = addChampion(*player2Head, createChampion());
				printf("Player 1 (SUPPORT) loses two champions.\n");
				printf("Player 2 (MAGE) wins and gains a new champion.\n");
			} else {
				printf("Nothing happens - no penalty or reward.\n");
			}
		} else if (role2 == FIGHTER) {
			if (level1 > level2) {
				*player1Head = addChampion(*player1Head, createChampion());
				printf("Player 1 (SUPPORT) wins and gains a new champion.\n");
				printf("Player 2 (FIGHTER) loses but with no penalty.\n");
			} else if (level1 < level2) {
				*player1Head = removeChampion(*player1Head);
				printf("Player 1 (SUPPORT) loses a champion.\n");
				printf("Player 2 (FIGHTER) wins but with no reward.\n");
			} else {
				printf("Nothing happens - no penalty or reward.\n");
			}
		} else if (role2 == SUPPORT) {
			if (level1 == level2) {
				*player1Head = removeChampion(*player1Head);
				*player2Head = removeChampion(*player2Head);
				printf("Player 1 (SUPPORT) ties and loses a champion.\n");
				printf("Player 2 (SUPPORT) ties and loses a champion.\n");
			} else if (level1 > level2) {
				*player1Head = addChampion(*player1Head, createChampion());
				*player2Head = removeChampion(*player2Head);
				printf("Player 1 (SUPPORT) wins and gains a new champion.\n");
				printf("Player 2 (SUPPORT) loses a champion.\n");
			} else {
				*player1Head = removeChampion(*player1Head);
				*player2Head = addChampion(*player2Head, createChampion());
				printf("Player 1 (SUPPORT) loses a champion.\n");
				printf("Player 2 (SUPPORT) wins and gains a new champion.\n");
			}
		} else { // role2 == TANK
			*player2Head = addChampion(*player2Head, createChampion());
			printf("Player 1 (SUPPORT) loses but with no penalty.\n");
			printf("Player 2 (TANK) wins and gains a new champion.\n");
		}
	}
	//tank matchups
	else {
		if (role2 == MAGE) {
			*player1Head = removeChampion(*player1Head);
			*player2Head = addChampion(*player2Head, createChampion());
			printf("Player 1 (TANK) loses a champion.\n");
			printf("Player 2 (MAGE) wins and gains a new champion.\n");
		} else if (role2 == FIGHTER) {
			*player2Head = addChampion(*player2Head, createChampion());
			printf("Player 1 (TANK) wins but with no reward.\n");
			printf("Player 2 (FIGHTER) loses a champion.\n");
		} else if (role2 == SUPPORT) {
			*player1Head = addChampion(*player1Head, createChampion());
			printf("Player 1 (TANK) wins and gains a new champion.\n");
			printf("Player 2 (SUPPORT) loses but with no penalty.\n");
		} else { // role2 == TANK
			printf("Nothing happens - no penalty or reward.\n");
		}
	}
}













