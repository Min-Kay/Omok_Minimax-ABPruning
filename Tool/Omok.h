#pragma once
#include "stdafx.h"
#include "Include.h"

class Omok
{

public:
	void Initialize();

public:
	VECPOS markerSlot(char board[BOARD_SIZE_Y][BOARD_SIZE_X], char marker);

	VECPOS availableSlot(char board[BOARD_SIZE_Y][BOARD_SIZE_X]);
	
	bool Check_AvaliablePick(VECPOS avaliableSlot, POS pick);

	bool Check_Strike(char board[BOARD_SIZE_Y][BOARD_SIZE_X], VECPOS markerSlot, char marker);
	
	bool Board_Full(char board[BOARD_SIZE_Y][BOARD_SIZE_X]);

	STATE Check_Marker_State(char board[BOARD_SIZE_Y][BOARD_SIZE_X], char marker);

	STATE Check_Game_State(char board[BOARD_SIZE_Y][BOARD_SIZE_X]);
	
	bool ScoreAdder(SCORE& score, int count, int op_count);
	
	SCORE Check_Marker_Score(char board[BOARD_SIZE_Y][BOARD_SIZE_X], char marker);
	
	SCOREPOS MinimaxNon(char board[BOARD_SIZE_Y][BOARD_SIZE_X], char marker, int depth);
	SCOREPOS Minimax(char board[BOARD_SIZE_Y][BOARD_SIZE_X], char marker, int depth, int alpha, int beta);

public:
	const int& Get_Count() const { return count; }
	void Set_Count(int i = 0) { count = i; }
	void Add_Count(int i = 1) { count += i; }

private:
	char board[BOARD_SIZE_Y][BOARD_SIZE_X];
	int count = 0;
};

