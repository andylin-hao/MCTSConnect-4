/***********************************************************************************
*        Filename :Policy.h
*        Description :Implementation of MCTS algorithm
*        Date:2019/5/8
*        Created by: <T> Andy Lin
*        All rights reserved
*
*       ChangeLog:
*       2014/5/8 12:33:29:
 *          Created!
************************************************************************************/
#ifndef POLICY_H_
#define POLICY_H_

#include <cstdlib>
#include <ctime>
#include <cmath>
#include "State.h"

class Policy
{
private:
	State* root; // Root state
	int start;   // Start time

	// Expand current state
	State* expandState(State* curState);
	// Select the best child state with UCT criterion
	State* bestChild(State* parent, double c);
	// Policy for MCTS Tree
	State* childrenPolicy(State* state);
	// Roll out the game
	double defaultPolicy(State* state);
	// Back propagate the acquired profit
	void backTrace(State* state, double profit);
	// Place pawn
	State* place(State* state);

public:
	Policy();
	~Policy();

	// The overall decision of MCTS algorithm
	State* gameDecision(State* state);
};

#endif

