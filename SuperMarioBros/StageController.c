#include<Windows.h>
#include<stdlib.h>
#include<stdio.h>
#include "info.h"

int stage =1;
int world=1;
int turn = 1;
void LoadStage(int stage)
{
	// 순서 바꾸지 말것
	playBackGroundMusic((stage - 1) / 10, turn);

	consoleBufferInitialize();
	marioInitialize(stage);
	
	GumbaInitialize(stage);
	PodobooInitialize(stage);
	TurtleInitialize(stage);
	KoopaInitialize(stage);
	BirdInitialize(stage);

	mapInitialize(stage);
	ItemInitialize(stage);


	ScreenInitialize();
}
