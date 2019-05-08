#include "State.h"




State::State(int w, int h, int** currentBoard, int* currentTop, int x, int y, bool isAI, State* parentState):
	width(w), height(h), lastX(x), lastY(y), isAITurn(isAI), parent(parentState)
{
	// copy current board
	board = new int* [h];
	for (int i = 0; i < h; i++) {
		board[i] = new int[w];
		memcpy(board[i], currentBoard[i], w * sizeof(int));
	}

	// copy top array
	top = new int[w];
	memcpy(top, currentTop, w * sizeof(int));

	children = new State * [w];
	memset(children, NULL, w * sizeof(State*));

	expNum = 0;
	expChildren = new int[w];
	for (int i = 0; i < w; i++) {
		if (currentTop[i] != 0)
			expChildren[expNum++] = i;
	}

	visitedTime = 0;
	profit = 0;
}

State::~State()
{
}

void State::shiftTurn()
{
	isAITurn = !isAITurn;
}

int State::pawnType()
{
	if (isAITurn) return AI_PAWN;
	return HUMAN_PAWN;
}

int State::gameProfitStatus()
{
	if (lastX == -1 && lastY == -1) {
		return UNFINISHED;
	}
	if (isAITurn && userWin(lastX, lastY, height, width, board)) {
		return HUMAN_WIN;
	}
	if (!isAITurn && machineWin(lastX, lastY, height, width, board)) {
		return AI_WIN;
	}
	if (isTie(width, top)) {
		return TIE;
	}
	return UNFINISHED;
}

void State::clearMemory()
{
	for (int i = 0; i < height; i++) {
		delete[] board[i];
	}
	delete[] board;
	delete[] top;
	delete[] expChildren;
	for (int i = 0; i < width; i++) {
		if (children[i]) {
			children[i]->clearMemory();
			delete children[i];
		}
	}
	delete[] children;
	for (int i = 0; i < rubbish.size(); i++) {
		rubbish[i]->clearMemory();
		delete rubbish[i];
	}
}
