#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include "info.h"

/*===============================Variables===============================*/
char TurtleMotion[5][TURTLE_HEIGHT * TURTLE_WIDTH];
static int isLoadedTurtle = 0;
int turtleNum = 0;

typedef struct __turtle {
	COORD pos;
	char *turtleState;
	int isRight;
	int isLeft;
	int isDead;
}Turtle;
#define MAX_TURTLE_NUM 10

Turtle tt[MAX_TURTLE_NUM];		//Turtle °´Ã¼

/*===============================Functions===============================*/
void loadTurtle(char *fileName, int motion);
extern COORD getMarioPos();
void TurtleInitialize(int stage)
{


	loadTurtle("TurtleLeft.txt", 0);
	loadTurtle("TurtleRight.txt", 1);
	loadTurtle("TurtleLeftWalk.txt", 2);
	loadTurtle("TurtleRightWalk.txt", 3);

	for (int i = 0; i < MAX_TURTLE_NUM; i++)
	{
		tt[i].isDead = 0;
	}
	switch (stage)
	{
	case 1:

		turtleNum = 0;

		break;
	case 2:

		turtleNum = 0;

		for (int i = 0; i < turtleNum; i++)
		{
			tt[i].turtleState = TurtleMotion[0];
			tt[i].pos.X = 300 + i * 40;
			tt[i].pos.Y = 60;
			tt[i].isLeft = 0;
			tt[i].isRight = 1;
		}
		break;

	case 3:

		turtleNum = 1;

		for (int i = 0; i < turtleNum; i++)
		{
			tt[i].turtleState = TurtleMotion[0];
			tt[i].pos.X = 100 + i * 110;
			tt[i].pos.Y = 60;
			tt[i].isLeft = 0;
			tt[i].isRight = 1;
		}

		break;

	case 7:
		turtleNum = 1;
		for (int i = 0; i < turtleNum; i++)
		{
			tt[i].turtleState = TurtleMotion[0];
			tt[i].pos.X = 280 + i * 110;
			tt[i].pos.Y = 50;
			tt[i].isLeft = 1;
			tt[i].isRight = 0;
		}
		
		break;

	case 9:

		turtleNum = 2;

		for (int i = 0; i < turtleNum; i++)
		{
			tt[i].turtleState = TurtleMotion[0];
			tt[i].pos.X = 160 + i * 80;
			tt[i].pos.Y = 80;
			tt[i].isLeft = 0;
			tt[i].isRight = 1;
		}
		break;
	case 10:

		turtleNum = 0;

		for (int i = 0; i < turtleNum; i++)
		{
			tt[i].turtleState = TurtleMotion[0];
			tt[i].pos.X = 200 + i * 80;
			tt[i].pos.Y = 10;
			tt[i].isLeft = 0;
			tt[i].isRight = 1;
		}
		break;
	case 15:

		turtleNum = 0;
		break;

	case 115:

		turtleNum = 3;

		for (int i = 0; i < turtleNum; i++)
		{
			tt[i].turtleState = TurtleMotion[0];
			tt[i].pos.X = 100 + i * 100;
			tt[i].pos.Y = 16;
			tt[i].isLeft = 0;
			tt[i].isRight = 1;
		}
		break;

	case 22:
		turtleNum = 1;

		for (int i = 0; i < turtleNum; i++)
		{
			tt[i].turtleState = TurtleMotion[0];
			tt[i].pos.X = 3 * BRICK_WIDTH + 20;
			tt[i].pos.Y = HEIGHT - 3 * BRICK_HEIGHT;
			tt[i].isLeft = 1;
			tt[i].isRight = 0;
		}
		break;

	case 33:

		turtleNum = 2;

		for (int i = 0; i < turtleNum; i++)
		{
			tt[i].turtleState = TurtleMotion[0];
			tt[i].pos.X = (4 + 4 * i)*BRICK_WIDTH;
			tt[i].pos.Y = 3 * BRICK_HEIGHT;
			tt[i].isLeft = 0;
			tt[i].isRight = 1;
		}
		break;
	case 36:

		turtleNum = 3;

		for (int i = 0; i < turtleNum; i++)
		{
			tt[i].turtleState = TurtleMotion[0];
			tt[i].pos.X = (8 + 2 * i)*BRICK_WIDTH;
			tt[i].pos.Y = HEIGHT - 3 * BRICK_HEIGHT;
			tt[i].isLeft = 0;
			tt[i].isRight = 1;
		}
		break;



	default:
		turtleNum = 0;
		break;
	}
	

}

void loadTurtle(char *fileName, int motion)
{
	char tmp;
	int k = 0;
	FILE *fp = fopen(fileName, "r");

	for (int y = 0; y < TURTLE_HEIGHT; y++)
	{
		for (int x = 0; x < TURTLE_WIDTH + 1; x++)
		{
			fscanf(fp, "%c", &tmp);
			if ((tmp >= 'A' && tmp <= 'z') || (tmp >= '0' && tmp <= '0'))
				TurtleMotion[motion][x + TURTLE_WIDTH * y] = tmp;
		}
	}
	fclose(fp);
}

void setTurtleMotion(int gbidx, int direction)
{
	if (tt[gbidx].isLeft == 0) {
		if (direction == 1) {
			tt[gbidx].turtleState = TurtleMotion[1];
		}
		else
			tt[gbidx].turtleState = TurtleMotion[3];
	}
	else {
		if (direction == 1) {
			tt[gbidx].turtleState = TurtleMotion[2];
		}
		else
			tt[gbidx].turtleState = TurtleMotion[0];
	}
}

void Turtle_Gravity()
{
	for (int i = 0; i < turtleNum; i++)
	{
		if (detectCollisionMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X, tt[i].pos.Y + 1))
		{
			continue;
		}
		deleteObjectFromMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X, tt[i].pos.Y);
		tt[i].pos.Y++;
		setObjectToMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X, tt[i].pos.Y);
	}

}


void Turtle_Move()
{

	static int d = 0;	//Turtle Motion change
	d++;
	for (int i = 0; i < turtleNum; i++)
	{

		COORD mp = getMarioPos();
		if (mp.X > tt[i].pos.X) {
			tt[i].isLeft = 0;
			tt[i].isRight = 1;
		}
		else {
			tt[i].isLeft = 1;
			tt[i].isRight = 0;
		}

		if (tt[i].isDead)
			continue;


		if (tt[i].isLeft == 1) {
			if (detectCollisionMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X - 1, tt[i].pos.Y))
			{
				tt[i].isLeft = 0;
				tt[i].isRight = 1;
				continue;
			}
			deleteObjectFromMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X, tt[i].pos.Y);
			setTurtleMotion(i, d % 2);
			tt[i].pos.X--;
			setObjectToMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X, tt[i].pos.Y);

		}
		else if (tt[i].isRight == 1) {
			if (detectCollisionMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X + 1, tt[i].pos.Y))
			{
				tt[i].isLeft = 1;
				tt[i].isRight = 0;
				continue;
			}

			deleteObjectFromMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X, tt[i].pos.Y);
			setTurtleMotion(i, d % 2);
			tt[i].pos.X++;
			setObjectToMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X, tt[i].pos.Y);
		}
		else {

		}


	}
	//drawMap();
}

extern int isStar;
void Turtle_Die()
{
	for (int i = 0; i < turtleNum; i++)
	{
		if (tt[i].isDead) {
			deleteObjectFromMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X, tt[i].pos.Y);
			continue;
		}

		int op = EnemyDetectCollisionObject(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X, tt[i].pos.Y);

		if (op == 1)
		{
			deleteObjectFromMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X, tt[i].pos.Y);
			tt[i].isDead = 1;
		}
		else if (op == 2)
		{
			if (isStar == 1)
			{
				deleteObjectFromMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X, tt[i].pos.Y);
				tt[i].isDead = 1;
			}
		}
		else if (op == 3)
		{
			deleteObjectFromMap(tt[i].turtleState, TURTLE_WIDTH, TURTLE_HEIGHT, tt[i].pos.X, tt[i].pos.Y);
			tt[i].isDead = 1;
		}
	}
}