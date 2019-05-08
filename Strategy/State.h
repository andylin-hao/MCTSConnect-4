/***********************************************************************************
*        Filename :State.h
*        Description :Data structure of MCTS Tree
*        Date:2019/5/8
*        Created by: <T> Andy Lin
*        All rights reserved
*
*       ChangeLog:
*       2014/5/8 12:33:29:
 *          Created!
************************************************************************************/

#ifndef STATE_H_
#define STATE_H_

#include <iostream>
#include <cstring>
#include <vector>

#include "Judge.h"

using namespace std;

#define UNFINISHED  -2
#define HUMAN_WIN	-1
#define AI_WIN		 1
#define TIE			 0

#define HUMAN_PAWN   1
#define AI_PAWN      2

class State
{
public:
	State* parent;
	State** children;
	vector<State*> rubbish;  // For collecting rubbish memory

	int* expChildren;        // Expandable child states
	int expNum;              // Number of expandable child states
	int visitedTime;         // A counter of visit time

	int width, height;       // The scale of chess board
	int lastX, lastY;        // The position of last placed pawn
	bool isAITurn;           // Playing turn
	int** board;             // The chess board
	int* top;                // The array for top position of every column

	double profit;           // The profit of current state

	State(int w, int h, int** currentBoard, int* currentTop, int x = -1, int y = -1, bool isAI = true, State* parentState = NULL);
	~State();

	// Shift player
	void shiftTurn();
	// Current pawn type
	int pawnType();
	// Current game profit
	int gameProfitStatus();
	// Clean memory occupation
	void clearMemory();
};

#endif


