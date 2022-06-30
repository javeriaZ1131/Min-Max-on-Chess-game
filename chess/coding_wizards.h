#pragma once
#pragma once
#include"chessPlayer.h"
#include "ENUM.h"

#include<iostream>
#include <cmath>
#include "chessBoard.h"
#include "chess.h"
#include "coding_wizards.h"
#include<cstdlib>

class Coding_wizards :public chessPlayer
{
public:

	int EvaluationFunctionforAI(gameState* s, Color myMaxPlayerColor);
	Coding_wizards(Color playerColor = White);
	void decideMove(gameState *state, action *Move, int maxDepth);
	int* minimax_formove(int alpha, int beta, gameState* state, int s, action* move, Color myMaxPlayerColor, chess c, int maxDepth);

};