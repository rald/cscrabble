#ifndef PLAYER_H
#define PLAYER_H


#include <stdlib.h>
#include <stdbool.h>



#define PLAYERS_MAX 4



typedef struct Player Player;

struct Player {
	char *nick;
	int score;
	bool joined;
};



Player* Player_New(char *nick,int score,bool joined);
void Player_Free(Player **player);
void Players_Free(Player ***players,size_t *nplayers);
void Players_Add(Player ***players,size_t *nplayers,Player *player);
void Player_Remove(Player ***players,size_t *nplayers,size_t index);
ssize_t Player_IndexOf(Player **players,size_t nplayers,char *nick);


#ifdef PLAYER_IMPLEMENTATION



Player* Player_New(char *nick,int score,bool joined) {
	Player *player=malloc(sizeof(*player));
	if(player) {
		player->nick=strdup(nick);
		player->score=score;	
		player->joined=joined;			
	}
	return player;
}



void Player_Free(Player **player) {
	free((*player)->nick);
	(*player)->nick=NULL;
	free(*player);
	*player=NULL;
}



void Players_Free(Player ***players,size_t *nplayers) {
	for(size_t i=0;i<*nplayers;i++) {
		Player_Free(&(*players)[i]);
	}
	free(*players);
	*players=NULL;
	*nplayers=0;
}



void Player_Add(Player ***players,size_t *nplayers,Player *player) {
	*players=realloc(*players,sizeof(**players)*(*nplayers+1));
	(*players)[(*nplayers)++]=player;
}



void Player_Remove(Player ***players,size_t *nplayers,size_t index) {
	for(size_t i=index;i<(*nplayers)-1;i++) {
		players[i]=players[i+1];
	}
	*players=realloc(*players,sizeof(**players)*(*nplayers-1));
	(*nplayers)--;
}


ssize_t Player_IndexOf(Player **players,size_t nplayers,char *nick) {
	for(size_t i=0;i<nplayers;i++) {
		if(!strcasecmp(players[i]->nick,nick)) return i;
	}
	return -1;
}



#endif /* PLAYER_IMPLEMENTATION */



#endif


