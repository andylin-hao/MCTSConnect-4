#include "Policy.h"




Policy::Policy()
{
	root = NULL;
	start = clock();
}

Policy::~Policy()
{
	delete root;
}

State* Policy::gameDecision(State* state)
{
	root = state;
	while (clock() - start <= 1300) {
		State* newState = childrenPolicy(root);
		double profit = defaultPolicy(newState);
		backTrace(newState, profit);
	}
	State* result = bestChild(root, 0);
	return result;
}

State* Policy::expandState(State* state)
{
	srand(int(time(0)));
	int i = rand() % state->expNum;
	int chosenY = state->expChildren[i];
	int chosenX = state->top[chosenY] - 1;
	if (chosenX == -1) return state;
	state->children[chosenY] = new State(state->width, state->height, state->board, state->top, chosenX, chosenY, state->isAITurn, state);
	state->children[chosenY]->board[chosenX][chosenY] = state->pawnType();
	state->children[chosenY]->top[chosenY]--;
	state->children[chosenY]->shiftTurn();

	int temp;
	state->expNum--;
	temp = state->expChildren[i];
	state->expChildren[i] = state->expChildren[state->expNum];
	state->expChildren[state->expNum] = temp;
	return state->children[chosenY];
}

State* Policy::bestChild(State* parent, double c=2.4)
{
	State* best = NULL;
	double maxProfit = -RAND_MAX;
	for (int i = 0; i < parent->width; i++) {
		if (parent->children[i] == NULL)
			continue;
		double profit = (parent->isAITurn ? 1 : -1) * parent->children[i]->profit;
		profit = profit / parent->children[i]->visitedTime + sqrt(2 * log(parent->visitedTime) / parent->children[i]->visitedTime) * c;
		if (profit > maxProfit) {
			maxProfit = profit;
			best = parent->children[i];
		}
	}
	return best;
}

State* Policy::childrenPolicy(State* state)
{
	while (state->gameProfitStatus() == UNFINISHED) {
		if (state->expNum > 0) {
			return expandState(state);
		}
		else {
			state = bestChild(state);
		}
	}
	return state;
}

double Policy::defaultPolicy(State* state)
{
	double profit = state->gameProfitStatus();
	while (profit == UNFINISHED) {
		state = place(state);
		profit = state->gameProfitStatus();
	}
	return profit;
}

void Policy::backTrace(State* state, double profit)
{
	State* p = state;
	while (p) {
		p->visitedTime++;
		p->profit += profit;
		p = p->parent;
	}
}

State* Policy::place(State* state)
{
	srand(int(time(0)));
	State* oldState = state;
	state = new State(state->width, state->height, state->board, state->top, state->lastX, state->lastY, state->isAITurn, state);
	state->lastY = rand() % state->width;
	while (state->top[state->lastY] == 0) {
		state->lastY = rand() % state->width;
	}

	state->lastX = --state->top[state->lastY];
	state->board[state->lastX][state->lastY] = state->pawnType();
	state->shiftTurn();
	oldState->rubbish.push_back(state);
	return state;
}
