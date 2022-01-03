#include "stdafx.h"
#include "Omok.h"

void Omok::Initialize()
{
	count = 0;

	for (int y = 0; y < BOARD_SIZE_Y; ++y)
	{
		for (int x = 0; x < BOARD_SIZE_X; ++x)
		{
			board[y][x] = NONE;
		}
	}
}

VECPOS Omok::markerSlot(char board[BOARD_SIZE_Y][BOARD_SIZE_X], char marker)
{
	VECPOS slots;
	for (int y = 0; y < BOARD_SIZE_Y; ++y)
	{
		for (int x = 0; x < BOARD_SIZE_X; ++x)
		{
			if (board[y][x] == marker)
				slots.push_back(make_pair(y, x));
		}
	}

	return slots;
}

VECPOS Omok::availableSlot(char board[BOARD_SIZE_Y][BOARD_SIZE_X])
{
	VECPOS slots;
	for (int y = 0; y < BOARD_SIZE_Y; ++y)
	{
		for (int x = 0; x < BOARD_SIZE_X; ++x)
		{
			if (board[y][x] == NONE)
				slots.push_back(make_pair(y, x));
		}
	}

	return slots;
}

bool Omok::Check_AvaliablePick(VECPOS avaliableSlot, POS pick)
{
	for (int i = 0; i < avaliableSlot.size(); ++i)
	{
		if (pick.first == avaliableSlot[i].first && pick.second == avaliableSlot[i].second)
			return true;
	}

	return false;

}

bool Omok::Check_Strike(char board[BOARD_SIZE_Y][BOARD_SIZE_X], VECPOS markerSlot, char marker)
{
	for (int i = 0; i < markerSlot.size(); ++i)
	{
		int count = 0;

		POS slot = markerSlot[i];

		for (int j = 0; j < WINSTRIKE; ++j) // ����
		{
			if (j + slot.second == BOARD_SIZE_X)
			{
				count = 0;
				break;
			}

			if (board[slot.first][slot.second + j] == marker)
				++count;
			else
			{
				count = 0;
				break;
			}

			if (count == WINSTRIKE)
				return true;
		}


		for (int j = 0; j < WINSTRIKE; ++j) // ����
		{
			if (j + slot.first == BOARD_SIZE_X)
			{
				count = 0;
				break;
			}

			if (board[slot.first + j][slot.second] == marker)
				++count;
			else
			{
				count = 0;
				break;
			}

			if (count == WINSTRIKE)
				return true;
		}

		if (BOARD_SIZE_Y - slot.first < WINSTRIKE) // �밢 �˻�� ���� �밢 ���̰� �ȳ����� ����
			continue;

		for (int j = 0; j < WINSTRIKE; ++j) // �»���� �밢
		{
			if (j + slot.first == BOARD_SIZE_Y || j + slot.second == BOARD_SIZE_X)
			{
				count = 0;
				break;
			}

			if (board[slot.first + j][slot.second + j] == marker)
				++count;
			else
			{
				count = 0;
				break;
			}

			if (count == WINSTRIKE)
				return true;
		}

		for (int j = 0; j < WINSTRIKE; ++j) // ������� �밢
		{
			if (slot.first + j == BOARD_SIZE_Y || slot.second - j < 0)
			{
				count = 0;
				break;
			}

			if (board[slot.first + j][slot.second - j] == marker)
				++count;
			else
			{
				count = 0;
				break;
			}

			if (count == WINSTRIKE)
				return true;
		}

	}

	return false;
}

bool Omok::Board_Full(char board[BOARD_SIZE_Y][BOARD_SIZE_X])
{
	for (int y = 0; y < BOARD_SIZE_X; ++y)
	{
		for (int x = 0; x < BOARD_SIZE_X; ++x)
		{
			if (board[y][x] == NONE)
				return false;
		}
	}
	return true;
}

STATE Omok::Check_Marker_State(char board[BOARD_SIZE_Y][BOARD_SIZE_X], char marker)
{
	VECPOS aval;
	aval = markerSlot(board, marker);
	if (Check_Strike(board, aval, marker))
		return WIN;

	char opponent = marker == PLAYER_MARKER ? AI_MARKER : PLAYER_MARKER;

	VECPOS avalOp;
	avalOp = markerSlot(board, opponent);
	if (Check_Strike(board, avalOp, opponent))
		return LOSE;

	return DRAW;
}

STATE Omok::Check_Game_State(char board[BOARD_SIZE_Y][BOARD_SIZE_X])
{
	VECPOS avalPlayer;
	avalPlayer = markerSlot(board, PLAYER_MARKER);
	if (Check_Strike(board, avalPlayer, PLAYER_MARKER))
		return WIN;

	VECPOS avalAI;
	avalAI = markerSlot(board, AI_MARKER);
	if (Check_Strike(board, avalAI, AI_MARKER))
		return LOSE;

	if (Board_Full(board))
		return DRAW;

	return DRAW;
}

bool Omok::ScoreAdder(SCORE& score, int count, int op_count)
{
	switch (count)
	{
	case 5:
		score = WIN;
		return true;
	case 4:
		if (op_count == 0)
			score += 10;
		break;
	case 3:
		if (op_count == 0)
			score += 5;
		break;
	case 2:
		if (op_count == 0)
			score += 1;
		break;
	case 1:
		if (op_count == 2)
			score += 1;
		else if (op_count >= 3)
			score += 2;
		break;
	case 0:
		if (op_count == 5)
		{
			score = LOSE;
			return true;
		}
		break;
	}

	return false;
}

SCORE Omok::Check_Marker_Score(char board[BOARD_SIZE_Y][BOARD_SIZE_X], char marker)
{
	SCORE score = 0;
	int count = 0;
	int op_count = 0;

	char opponenet_marker = marker == AI_MARKER ? PLAYER_MARKER : AI_MARKER;

	for (int y = 0; y < BOARD_SIZE_Y; ++y) // ���� ����
	{
		count = 0;
		op_count = 0;

		for (int x = 0; x < BOARD_SIZE_X; ++x)
		{
			if (board[y][x] == marker)
				++count;
			else if (board[y][x] == opponenet_marker)
				++op_count;
		}

		if (ScoreAdder(score, count, op_count))
			return score;
	}

	for (int x = 0; x < BOARD_SIZE_X; ++x) // ���� ����
	{
		count = 0;
		op_count = 0;

		for (int y = 0; y < BOARD_SIZE_Y; ++y)
		{
			if (board[y][x] == marker)
				++count;
			else if (board[y][x] == opponenet_marker)
				++op_count;
		}

		if (ScoreAdder(score, count, op_count))
			return score;
	}

	count = 0;
	op_count = 0;
	for (int i = 0; i < WINSTRIKE; ++i)
	{
		if (board[i][i] == marker)
			++count;
		else if (board[i][i] == opponenet_marker)
			++op_count;
	}

	if (ScoreAdder(score, count, op_count))
		return score;

	count = 0;
	op_count = 0;

	for (int i = 0; i < WINSTRIKE; ++i)
	{
		if (board[i][BOARD_SIZE_X - 1 - i] == marker)
			++count;
		else if (board[i][BOARD_SIZE_X - 1 - i] == opponenet_marker)
			++op_count;
	}

	if (ScoreAdder(score, count, op_count))
		return score;

	return score;
}

SCOREPOS Omok::Minimax(char board[BOARD_SIZE_Y][BOARD_SIZE_X], char marker, int depth, int alpha, int beta)
{
	STATE best_score = (marker == AI_MARKER) ? LOSE : WIN; // �⺻ ���� ����
	POS best_move = POS(DEFAULT, DEFAULT); 
	++count;

	if (Board_Full(board) || DRAW != Check_Marker_State(board, AI_MARKER) || // �¹��� ������
		depth == 5 || // ���̷� ���� - �ڿ����� ���
		(depth != 0 && (Check_Marker_Score(board, AI_MARKER) > Check_Marker_Score(board, PLAYER_MARKER)))) // �¹��а� ���� ���� �ʾ�����, AI�� ���� �� ���� ��� - ����ī���� Ʈ�� Ž���� ��ġ �Ǵ�
	{
		best_score = (DRAW != Check_Marker_State(board, AI_MARKER)) ? Check_Marker_State(board, AI_MARKER) : Check_Marker_Score(board, AI_MARKER) - Check_Marker_Score(board, PLAYER_MARKER); // ���� ���ο� ���� ���� ��ȯ
		return make_pair(best_score, best_move);
	}

	VECPOS aval;
	aval = availableSlot(board);

	for (int i = 0; i < aval.size(); ++i)
	{
		POS curr = aval[i];
		board[curr.first][curr.second] = marker;

		if (marker == AI_MARKER)
		{
			SCORE score = Minimax(board, PLAYER_MARKER, depth + 1, alpha, beta).first;
			if (best_score < score)
			{
				best_score = score - depth * DEPTH_MULTI;
				best_move = curr;
				board[curr.first][curr.second] = NONE;
				alpha = max(alpha, best_score);
				if (beta <= alpha)
					break;
			}
		}
		else if(marker == PLAYER_MARKER)
		{
			SCORE score = Minimax(board, AI_MARKER, depth + 1, alpha, beta).first;
			if (best_score > score)
			{
				best_score = score + depth * DEPTH_MULTI;
				best_move = curr;
				board[curr.first][curr.second] = NONE;
				beta = min(beta, best_score);
				if (beta <= alpha)
					break;
			}
		}

		board[curr.first][curr.second] = NONE;

		if (best_move == POS(DEFAULT, DEFAULT))
			best_move = curr;
	}

	return make_pair(best_score, best_move);
}

SCOREPOS Omok::MinimaxNon(char board[BOARD_SIZE_Y][BOARD_SIZE_X], char marker, int depth)
{
	STATE best_score = (marker == AI_MARKER) ? LOSE : WIN;
	POS best_move = POS(DEFAULT, DEFAULT);
	++count;

	if (Board_Full(board) || DRAW != Check_Marker_State(board, AI_MARKER) || // �¹��� ������
		depth == 5 || // ���̷� ���� - �ڿ����� ���
		(depth != 0 && (Check_Marker_Score(board, AI_MARKER) > Check_Marker_Score(board, PLAYER_MARKER)))) // �¹��а� ���� ���� �ʾ�����, AI�� ���� �� ���� ��� - ����ī���� Ʈ�� Ž���� ��ġ �Ǵ�
	{
		best_score = (DRAW != Check_Marker_State(board, AI_MARKER)) ? Check_Marker_State(board, AI_MARKER) : Check_Marker_Score(board, AI_MARKER) - Check_Marker_Score(board, PLAYER_MARKER); // ���� ���ο� ���� ���� ��ȯ
		return make_pair(best_score, best_move);
	}

	VECPOS aval;
	aval = availableSlot(board);

	for (int i = 0; i < aval.size(); ++i)
	{
		POS curr = aval[i];
		board[curr.first][curr.second] = marker;

		if (marker == AI_MARKER)
		{
			SCORE score = MinimaxNon(board, PLAYER_MARKER, depth + 1).first;
			if (best_score < score)
			{
				best_score = score - depth * DEPTH_MULTI;
				best_move = curr;
			}
		}
		else
		{
			SCORE score = MinimaxNon(board, AI_MARKER, depth + 1).first;
			if (best_score > score)
			{
				best_score = score + depth * DEPTH_MULTI;
				best_move = curr;
			}
		}

		board[curr.first][curr.second] = NONE;

		if (best_move == POS(DEFAULT, DEFAULT))
			best_move = curr;
	}

	return make_pair(best_score, best_move);
}
