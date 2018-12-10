#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include "info.h"

/*===============================Variables===============================*/
char GumbaMotion[3][GUMBA_HEIGHT * GUMBA_WIDTH];
static int isLoadedGumba = 0;
int gumbaNum = 0;
typedef struct __gumba {
	COORD pos;
	char *gumbaState;
	int isRight;
	int isLeft;
	int isDead;
}Gumba;
#define MAX_GUMBA_NUM 10

Gumba gb[MAX_GUMBA_NUM];		//±À¹Ù °´Ã¼

/*===============================Functions===============================*/
void loadGumba(char *fileName, int motion);

void GumbaInitialize(int stage) 
{


	loadGumba("GumbaLeft.txt", 0);
	loadGumba("GumbaRight.txt", 1);


	for (int i = 0; i < MAX_GUMBA_NUM; i++)
	{
		gb[i].isDead = 0;
	}


	switch (stage)
	{
	//=====================================[WORLD 1]=====================================
	case 1:
		gumbaNum = 3;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = 45 + i * 140;
			gb[i].pos.Y = 60;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}

		break;

	case 2:
		gumbaNum = 5;
		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = 45 + i * 60;
			gb[i].pos.Y = 75;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}
		break;

	case 3:
		gumbaNum = 2;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = 185 + i * 140;
			gb[i].pos.Y = 15;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}

		break;
	case 4:
		gumbaNum = 2;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = 185 + i * 140;
			gb[i].pos.Y = 55 + i * 30;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}

		break;
	case 7:
		gumbaNum = 3;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = 45 + i * 140;
			gb[i].pos.Y = 55;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}

		break;
	case 9:
		gumbaNum = 3;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = 45 + i * 140;
			gb[i].pos.Y = 15;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}

		break;
	case 10:
		gumbaNum = 2;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = 45 + i * 240;
			gb[i].pos.Y = 15;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}

		break;
	//=====================================[WORLD 2]=====================================
	case 11:
		gumbaNum = 1;

		
		gb[0].gumbaState = GumbaMotion[0];
		gb[0].pos.X = 400;
		gb[0].pos.Y = 70;
		gb[0].isLeft = 0;
		gb[0].isRight = 1;

		break;
	case 12:
		gumbaNum = 1;


		gb[0].gumbaState = GumbaMotion[0];
		gb[0].pos.X = 400;
		gb[0].pos.Y = 70;
		gb[0].isLeft = 0;
		gb[0].isRight = 1;

		break;

	case 113:
		gumbaNum = 5;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = 200 + i * 50;
			gb[i].pos.Y = 15;


			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}

		break;

	case 14:
		gumbaNum = 5;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = 80 + i * 80;
			gb[i].pos.Y = 95;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}

		break;
		//=====================================[WORLD 3]=====================================

	case 21:
		gumbaNum = 2;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = 180 + i * 180;
			gb[i].pos.Y = HEIGHT - 2 * BRICK_HEIGHT;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}

		break;


	case 23:
		gumbaNum = 2;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = 200 + i * 80;
			gb[i].pos.Y = 0 + i * 60;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}

		break;
		//=====================================[WORLD 4]=====================================
	case 32:
		gumbaNum = 2;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = (7 + 3 * i)*BRICK_WIDTH;
			gb[i].pos.Y = HEIGHT - 2 * BRICK_HEIGHT;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}
		break;


	case 35:
		gumbaNum = 1;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = (9)*BRICK_WIDTH;
			gb[i].pos.Y = HEIGHT - 2 * BRICK_HEIGHT;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}
		break;

	case 37:
		gumbaNum = 2;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = (5 + 2 * i)*BRICK_WIDTH;
			gb[i].pos.Y = HEIGHT - 7 * BRICK_HEIGHT;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}
		break;


	case 38:
		gumbaNum = 1;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = 13 * BRICK_WIDTH;
			gb[i].pos.Y = HEIGHT - 4 * BRICK_HEIGHT;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}
		break;
	case 39:
		gumbaNum = 3;

		for (int i = 0; i < gumbaNum; i++)
		{
			gb[i].gumbaState = GumbaMotion[0];
			gb[i].pos.X = (2 * i + 9)*BRICK_WIDTH;
			gb[i].pos.Y = HEIGHT - 2 * BRICK_HEIGHT;
			gb[i].isLeft = 0;
			gb[i].isRight = 1;
		}
		break;
	default:
		gumbaNum = 0;
		break;
	}

}

void loadGumba(char *fileName, int motion)
{
	char tmp;
	int k = 0;
	FILE *fp = fopen(fileName, "r");

	for (int y = 0; y < GUMBA_HEIGHT; y++)
	{
		for (int x = 0; x < GUMBA_WIDTH + 1; x++)
		{
			fscanf(fp, "%c", &tmp);
			if ((tmp >= 'A' && tmp <= 'z') || (tmp >= '0' && tmp <= '0'))
				GumbaMotion[motion][x + GUMBA_WIDTH * y] = tmp;
		}
	}
	fclose(fp);
}


void setGumbaMotion(int gbidx, int direction)
{
	if (direction == 1) {
		gb[gbidx].gumbaState = GumbaMotion[1];
	}
	else {
		gb[gbidx].gumbaState = GumbaMotion[0];
	}
}

void Gumba_Gravity()
{
	for (int i = 0; i < gumbaNum; i++)
	{
		if (gb[i].isDead)
			continue;
		if (detectCollisionMap(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X, gb[i].pos.Y + 1))
		{
			continue;
		}
		deleteObjectFromMap(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X, gb[i].pos.Y);
		gb[i].pos.Y++;
		setObjectToMap(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X, gb[i].pos.Y);
	}

}


void Gumba_Move()
{

	static int d = 0;	//Gumba Motion change
	d++;
	for (int i = 0; i < gumbaNum; i++)
	{
		if (gb[i].isDead)
			continue;
		if (gb[i].isLeft == 1) {
			if (detectCollisionMap(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X - 1, gb[i].pos.Y))
			{
				gb[i].isLeft = 0;
				gb[i].isRight = 1;
				continue;
			}

			deleteObjectFromMap(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X, gb[i].pos.Y);
			setGumbaMotion(i, d % 2);
			gb[i].pos.X--;
			setObjectToMap(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X, gb[i].pos.Y);

		}
		else if (gb[i].isRight == 1) {
			if (detectCollisionMap(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X + 1, gb[i].pos.Y))
			{
				gb[i].isLeft = 1;
				gb[i].isRight = 0;
				continue;
			}

			deleteObjectFromMap(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X, gb[i].pos.Y);
			setGumbaMotion(i, d % 2);
			gb[i].pos.X++;
			setObjectToMap(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X, gb[i].pos.Y);
		}
		else {

		}

	}

}

extern int isStar;
void Gumba_Die()
{
	for (int i = 0; i < gumbaNum; i++)
	{
		if (gb[i].isDead)
			continue;

		int op = EnemyDetectCollisionObject(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X, gb[i].pos.Y);

		if (op == 1)
		{
			deleteObjectFromMap(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X, gb[i].pos.Y);
			gb[i].isDead = 1;
		}
		else if (op == 2)
		{
			if (isStar == 1)
			{
				deleteObjectFromMap(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X, gb[i].pos.Y);
				gb[i].isDead = 1;
			}
		}
		else if (op == 3)
		{
			deleteObjectFromMap(gb[i].gumbaState, GUMBA_WIDTH, GUMBA_HEIGHT, gb[i].pos.X, gb[i].pos.Y);
			gb[i].isDead = 1;
		}
	}
}