#include "coding_wizards.h"
#include<iostream>
#include "chessPlayer.h"
#include"ENUM.h"

#include <cmath>
#include "gameState.h"
#include "chess.h"
#include "coding_wizards.h"
#include<stdio.h>
#include<cstdlib>
using namespace std;

Coding_wizards::Coding_wizards(Color playerColor) :chessPlayer("Auto Player Name", playerColor)
{

}

int Coding_wizards::EvaluationFunctionforAI(gameState* state, Color myMaxPlayerColor)
{
    int sumweigthforW = 0;
    int sumweightforB = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {

            if (state->Board.board[i][j] == 6)
            {
                sumweigthforW = sumweigthforW + 100;
            }
            if (state->Board.board[i][j] == 5)
            {
                sumweigthforW = sumweigthforW + 9;

            }
            if (state->Board.board[i][j] == 4)
            {
                sumweigthforW = sumweigthforW + 5;

            }
            if (state->Board.board[i][j] == 1)
            {
                sumweigthforW = sumweigthforW + 1;

            }
            if (state->Board.board[i][j] == 2)
            {
                sumweigthforW = sumweigthforW + 3;

            }
            if (state->Board.board[i][j] == 3)
            {
                sumweigthforW = sumweigthforW + 4;

            }
            if (state->Board.board[i][j] == -6)
            {
                sumweightforB = sumweightforB - 100;
                sumweightforB = sumweightforB * -1;

            }
            if (state->Board.board[i][j] == -5)
            {
                sumweightforB = sumweightforB - 9;
                sumweightforB = sumweightforB * -1;

            }
            if (state->Board.board[i][j] == -4)
            {
                sumweightforB = sumweightforB - 5;
                sumweightforB = sumweightforB * -1;

            }
            if (state->Board.board[i][j] == -1)
            {
                sumweightforB = sumweightforB - 1;
                sumweightforB = sumweightforB * -1;

            }
            if (state->Board.board[i][j] == -2)
            {
                sumweightforB = sumweightforB - 3;
                sumweightforB = sumweightforB * -1;

            }
            if (state->Board.board[i][j] == -3)
            {
                sumweightforB = sumweightforB - 4;
                sumweightforB = sumweightforB * -1;

            }

        }
    }
    if (myMaxPlayerColor == Black)
    {
        return sumweightforB - sumweigthforW;
    }
    else
    {
        return sumweigthforW - sumweightforB;
    }
}

int* Coding_wizards::minimax_formove(int alpha, int beta, gameState* state, int s, action* move, Color myMaxPlayerColor, chess c, int maxDepth)
{

    /// s=1 for max player and s=0 for min player
    static int my_Arr[2];
    //o index : best move,1 : best evaluation 
    int totalmoves = state->Actions.getActionCount();//get count moves for the current state of the gme 

    ///Ai player wants to maximize his/her scores

    if (totalmoves == 0 || c.gameOver() == true || maxDepth == 0)///base case
    {

        int evaluationvalue = EvaluationFunctionforAI(state, myMaxPlayerColor);///end state pe return kary ga us state pe black  ya white ky scores
        my_Arr[1] = evaluationvalue;
        cout << evaluationvalue << endl;
        return my_Arr;

    }
    my_Arr[0] = rand() % totalmoves;

    ///////////////////////////////////////////////////////////////////////
    if (s == 1)///max player
    {
        my_Arr[1] = 0;
        for (int i = 0; i < totalmoves; i++)
        {
            gameState* tempstate = state;
            tempstate->Actions.getAction(i, move);
            // tempstate->applyMove(*move);
            int value = minimax_formove(alpha, beta, tempstate, 0, move, myMaxPlayerColor, c, maxDepth - 1)[1];
            //bool reset= tempstate->Actions.resetActions();
            if (alpha < value)
            {
                alpha = value;
            }

            if (value > my_Arr[1])
            {
                my_Arr[0] = i;
                my_Arr[1] = value;
            }

            if (beta <= alpha)
            {
                break;
            }
        }
        return my_Arr;
    }
    /// /minimizing done here
    ///////////////////////////////////////////////////////////////////////
    if (s == 0)
    {
        ///firstly get action then after applying move again to compute beta and then reset the previous move
        my_Arr[1] = 0;
        for (int i = 0; i < totalmoves; i++)
        {
            gameState* tempstate = state;
            tempstate->Actions.getAction(i, move);
            // tempstate->applyMove(*move);
            int  value = minimax_formove(alpha, beta, tempstate, 0, move, myMaxPlayerColor, c, maxDepth - 1)[1];
            //  bool reset = tempstate->Actions.resetActions();

            if (value > my_Arr[1])
            {
                my_Arr[0] = i;
                my_Arr[1] = value;
            }
            if (beta > value)
            {
                beta = value;
            }

            if (beta <= alpha)
            {
                break;
            }
        }

        return my_Arr;
    }
}

void Coding_wizards::decideMove(gameState* state, action* Move, int maxDepth)
{
    maxDepth = 3;
    int alpha = 0;
    int beta = 0;
    Color myMaxPlayercolor = state->getPlayer();
    int s = 1;
    int totalmoves = 0;
    chess c;

    //Best_move(state1, Move, b, al, be, bestmove,maxDepth);/////function to calculate the best move by minimax alpha beta procedure
    int* bestMoveandValue = minimax_formove(alpha, beta, state, s, Move, myMaxPlayercolor, c, maxDepth);
    int bestmove = bestMoveandValue[0];
    // state->applyMove(bestmoveandValue);
    state->Actions.getAction(bestmove, Move);

}
