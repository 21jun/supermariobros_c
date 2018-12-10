#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include "info.h"

/*===============================Variables===============================*/
char BirdMotion[5][BIRD_HEIGHT * BIRD_WIDTH];
int birdNum = 0;

typedef struct __bird {
	COORD pos;
	char *birdState;
	int isRight;
	int isLeft;
	int isDead;
}Bird;

#define MAX_BIRD_NUM 10

Bird bd[MAX_BIRD_NUM];      //Turtle °´Ã¼

							/*===============================Functions===============================*/
void loadBird(char *fileName, int motion);
extern COORD getMarioPos();
void BirdInitialize(int stage)
{
	loadBird("BirdLeft1.txt", 0);
	loadBird("BirdRight1.txt", 1);
	loadBird("BirdLeft2.txt", 2);
	loadBird("BirdRight2.txt", 3);

	for (int i = 0; i < MAX_BIRD_NUM; i++)
	{
		bd[i].isDead = 0;
	}
	switch (stage)
	{

	/*case 4:
		birdNum = 2;

		for (int i = 0; i < birdNum; i++)
		{
			bd[i].birdState = BirdMotion[1];
			bd[i].pos.X = 50 + i * 200;
			bd[i].pos.Y = 30;
			bd[i].isLeft = 0;
			bd[i].isRight = 1;
		}
		bd[1].isLeft = 1;
		bd[1].isRight = 0;
		break;

	case 5:
		birdNum = 1;
		int i = 0;
		bd[i].birdState = BirdMotion[1];
		bd[i].pos.X = 50 + i * 200;
		bd[i].pos.Y = 15;
		bd[i].isLeft = 0;
		bd[i].isRight = 1;
		break;*/
	case 21:
		birdNum = 2;

		for (int i = 0; i < birdNum; i++)
		{
			bd[i].birdState = BirdMotion[1];
			bd[i].pos.X = 50 + i * 200;
			bd[i].pos.Y = 30 + i * 30;
			if (i % 2 == 0)
			{
				bd[i].isLeft = 0;
				bd[i].isRight = 1;
			}
			else
			{
				bd[i].isLeft = 1;
				bd[i].isRight = 0;
			}

		}
		break;


	case 24:
		birdNum = 2;

		for (int i = 0; i < birdNum; i++)
		{
			bd[i].birdState = BirdMotion[1];
			bd[i].pos.X = 50 + i * 300;
			bd[i].pos.Y = 20 + i * 60;
			if (i % 2 == 0)
			{
				bd[i].isLeft = 0;
				bd[i].isRight = 1;
			}
			else
			{
				bd[i].isLeft = 1;
				bd[i].isRight = 0;
			}

		}
		break;


	case 25:
		birdNum = 3;

		for (int i = 0; i < birdNum; i++)
		{
			bd[i].birdState = BirdMotion[1];
			bd[i].pos.X = 50 + i * 150;
			bd[i].pos.Y = 20 + i * 20;
			if (i % 2 == 0)
			{
				bd[i].isLeft = 0;
				bd[i].isRight = 1;
			}
			else
			{
				bd[i].isLeft = 1;
				bd[i].isRight = 0;
			}

		}
		break;

	case 139:
		birdNum = 2;
		for (int i = 0; i < birdNum; i++)
		{
			bd[i].birdState = BirdMotion[1];
			bd[i].pos.X = 150 + i * 150;
			bd[i].pos.Y = 20 + i * 20;
			if (i % 2 == 0)
			{
				bd[i].isLeft = 0;
				bd[i].isRight = 1;
			}
			else
			{
				bd[i].isLeft = 1;
				bd[i].isRight = 0;
			}

		}
		break;
	default:
		birdNum = 0;
		break;
	}



}

void loadBird(char *fileName, int motion)
{
	char tmp;
	int k = 0;
	FILE *fp = fopen(fileName, "r");

	for (int y = 0; y < BIRD_HEIGHT; y++)
	{
		for (int x = 0; x < BIRD_WIDTH + 1; x++)
		{
			fscanf(fp, "%c", &tmp);
			if ((tmp >= 'A' && tmp <= 'z') || (tmp >= '0' && tmp <= '0'))
				BirdMotion[motion][x + BIRD_WIDTH * y] = tmp;
		}
	}
	fclose(fp);
}

void setBirdMotion(int bdidx, int direction)
{
	if (bd[bdidx].isLeft == 0) {
		if (direction == 1) {
			bd[bdidx].birdState = BirdMotion[1];
		}
		else
			bd[bdidx].birdState = BirdMotion[3];
	}
	else {
		if (direction == 1) {
			bd[bdidx].birdState = BirdMotion[2];
		}
		else
			bd[bdidx].birdState = BirdMotion[0];
	}
}

void Bird_Move()
{
	static int d = 0;
	d++;
	for (int i = 0; i < birdNum; i++)
	{
		COORD mp = getMarioPos();

		if (bd[i].isDead)
			continue;

		if (bd[i].isLeft == 1) {
			if (detectCollisionMap(bd[i].birdState, BIRD_WIDTH, BIRD_HEIGHT, bd[i].pos.X - 3, bd[i].pos.Y))
			{
				bd[i].isLeft = 0;
				bd[i].isRight = 1;
				continue;
			}
			deleteObjectFromMap(bd[i].birdState, BIRD_WIDTH, BIRD_HEIGHT, bd[i].pos.X, bd[i].pos.Y);
			setBirdMotion(i, d % 2);
			bd[i].pos.X -= 3;
			setObjectToMap(bd[i].birdState, BIRD_WIDTH, BIRD_HEIGHT, bd[i].pos.X, bd[i].pos.Y);

		}
		else if (bd[i].isRight == 1) {
			if (detectCollisionMap(bd[i].birdState, BIRD_WIDTH, BIRD_HEIGHT, bd[i].pos.X + 3, bd[i].pos.Y))
			{
				bd[i].isLeft = 1;
				bd[i].isRight = 0;
				continue;
			}
			deleteObjectFromMap(bd[i].birdState, BIRD_WIDTH, BIRD_HEIGHT, bd[i].pos.X, bd[i].pos.Y);
			setBirdMotion(i, d % 2);
			bd[i].pos.X += 3;
			setObjectToMap(bd[i].birdState, BIRD_WIDTH, BIRD_HEIGHT, bd[i].pos.X, bd[i].pos.Y);
		}
		else {

		}


	}
	//drawMap();
}

extern int isStar;
void Bird_Die()
{
	for (int i = 0; i < birdNum; i++)
	{
		if (bd[i].isDead) {
			deleteObjectFromMap(bd[i].birdState, BIRD_WIDTH, BIRD_HEIGHT, bd[i].pos.X, bd[i].pos.Y);
			continue;
		}

		int op = EnemyDetectCollisionObject(bd[i].birdState, BIRD_WIDTH, BIRD_HEIGHT, bd[i].pos.X, bd[i].pos.Y);

		if (op == 1)
		{
			deleteObjectFromMap(bd[i].birdState, BIRD_WIDTH, BIRD_HEIGHT, bd[i].pos.X, bd[i].pos.Y);
			bd[i].isDead = 1;
		}
		else if (op == 2)
		{
			if (isStar == 1)
			{
				deleteObjectFromMap(bd[i].birdState, BIRD_WIDTH, BIRD_HEIGHT, bd[i].pos.X, bd[i].pos.Y);
				bd[i].isDead = 1;
			}
		}
		else if (op == 3)
		{
			deleteObjectFromMap(bd[i].birdState, BIRD_WIDTH, BIRD_HEIGHT, bd[i].pos.X, bd[i].pos.Y);
			bd[i].isDead = 1;
		}
	}
}