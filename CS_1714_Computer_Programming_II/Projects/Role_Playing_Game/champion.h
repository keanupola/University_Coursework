#ifndef CHAMPION_H
#define CHAMPION_H

//role enum
typedef enum {
	MAGE = 'M',
	FIGHTER = 'F',
	SUPPORT = 'S',
	TANK = 'T'
} ChampionRole;

//Champion obj
typedef struct Champion {
	ChampionRole role;	
	int level;
	struct Champion *next;
} Champion;

//function prototypes
Champion* createChampion();
Champion* addChampion(Champion *head, Champion *c);
Champion* buildChampionList(int n);
void printChampionList(Champion *head);
Champion* removeChampion(Champion *head);
Champion* destroyChampionList(Champion *head);
const char *roleToString(ChampionRole role);
void playRound(Champion **player1Head, Champion **player2Head);

//	**Game Rules and Logic**
//For the playRound() function, rules and matchups are as follows:
//Mage vs Mage ->
//	Player with the higher “level” wins. The winning player gains a new champion, and the
//	losing player loses one champion. In a tie, nothing happens.
//Mage vs Fighter ->
//	Player with the higher “level” wins. If MAGE wins, they gain a new champion, and the
//	FIGHTER loses with no penalty. If FIGHTER wins, they gain no reward, but the MAGE
//	loses one champion. In a tie, nothing happens.
//Mage vs Support -> 
//	Player with the higher “level” wins. If MAGE wins, they gain one new champion, and
//	the SUPPORT loses two champions. Whereas, if SUPPORT wins, they get two new
//	champions, and the MAGE loses one champion. In a tie, nothing happens.
//Mage vs Tank -> 
//	TANK loses one champion. MAGE gains a new champion.
//Fighter vs Fighter ->
//	Both players gain a new champion.
//Fighter vs Support ->
//	Player with higher “level” wins. If SUPPORT wins, they gain one //champion, and the
//	FIGHTER loses but with no penalty. If FIGHTER wins, they gain no //reward, but the
//	SUPPORT loses one champion. In a tie, nothing happens. 
//Fighter vs Tank ->
//	TANK player loses but with no penalty.FIGHTER player wins and gains a new champion
//Support vs Support ->
//	Both players lose one champion.
//Support vs Tank ->
//	TANK player wins and gets a new champion. SUPPORT player loses but //with no penalty.
//Tank vs Tank ->
//	Nothing happens – no penalty or reward.

#endif

