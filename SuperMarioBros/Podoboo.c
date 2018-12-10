#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include"info.h"

/*===============================Variables===============================*/
char PodobooMotion[4][PODOBOO_HEIGHT * PODOBOO_WIDTH];
int PodobooNum = 0;


typedef struct __podoboo {
	COORD pos;
	char *PodobooState;
	int isUp;
	int isDown;
	int type;
	int height;
	int startPos;
}Podoboo;
#define MAX_PODOBOO_NUM 10

Podoboo PDB[MAX_PODOBOO_NUM];
enum PDB_TYPE { FIRE, WATER };
enum PDB_MOTION { FIRE_UP, FIRE_DOWN, WATER_UP, WATER_DOWN };
/*===============================Functions===============================*/
void loadPodoboo(char *fileName, int motion);
void setPodoboo(int i ,int type, int height, int startPos, int x, int y);

void PodobooInitialize(int stage)
{

	loadPodoboo("PodobooUp.txt", 0);
	loadPodoboo("PodobooDown.txt", 1);
	loadPodoboo("WaterBallUp.txt", 2);
	loadPodoboo("WaterBallDown.txt", 3);


	switch (stage)
	{

	case 11:

		PodobooNum = 2;

		setPodoboo(0, WATER, 7, HEIGHT - 4 * BRICK_HEIGHT, 3 * BRICK_WIDTH + 20, HEIGHT - 4 * BRICK_HEIGHT);
	
		setPodoboo(1, WATER, 7, HEIGHT - 4 * BRICK_HEIGHT, 8 * BRICK_WIDTH + 20, HEIGHT - 4 * BRICK_HEIGHT);

		break;

	case 12:

		PodobooNum = 2;

		setPodoboo(0, WATER, 8, HEIGHT- 16, 4 * BRICK_WIDTH , 16);

		setPodoboo(1, WATER, 8, HEIGHT- 16, 8 * BRICK_WIDTH , 16);

		break;

	case 14:

		PodobooNum = 3;
		for (int i = 0; i < PodobooNum; i++)
		{
			setPodoboo(i, WATER, 7, HEIGHT, 32 + 4 * i * BRICK_WIDTH, 30 + i * BRICK_HEIGHT);
		}

		break;


	case 22:

		PodobooNum = 1;

		setPodoboo(0, WATER, 7, HEIGHT - PIPE_TOP_HEIGHT - 2 * PIPE_BODY_HEIGHT - BRICK_HEIGHT, 220, HEIGHT - 5 * BRICK_HEIGHT);

		break;


	case 24:

		PodobooNum = 1;


		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].type = WATER;
			PDB[i].PodobooState = PodobooMotion[FIRE_UP];
			PDB[i].pos.X = (12)*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT - 3 * BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
			PDB[i].height = 3;
			PDB[i].startPos = HEIGHT;
		}
		break;

	case 25:

		PodobooNum = 3;
		setPodoboo(0, WATER, 7, HEIGHT, 4 * BRICK_WIDTH, HEIGHT - 1 * BRICK_HEIGHT);
		setPodoboo(1, WATER, 7, HEIGHT, 5 * BRICK_WIDTH, HEIGHT - 2 * BRICK_HEIGHT);
		setPodoboo(2, WATER, 7, HEIGHT, 6 * BRICK_WIDTH, HEIGHT - 1 * BRICK_HEIGHT);

		break;
	case 31:
		PodobooNum = 2;

		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].type = FIRE;
			PDB[i].PodobooState = PodobooMotion[FIRE_UP];
			PDB[i].pos.X = (5 + 4 * i)*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT - 2 * BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
			PDB[i].height = 3;
			PDB[i].startPos = HEIGHT;

		}
		break;
	case 32:
		PodobooNum = 1;

		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].type = FIRE;
			PDB[i].PodobooState = PodobooMotion[FIRE_UP];
			PDB[i].pos.X = (3)*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT - 2 * BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
			PDB[i].height = 3;
			PDB[i].startPos = HEIGHT;

		}
		break;
	case 35:
		PodobooNum = 2;

		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].type = FIRE;
			PDB[i].PodobooState = PodobooMotion[FIRE_UP];
			PDB[i].pos.X = (3.5 + 3 * i)*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT - 2 * BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
			PDB[i].height = 3;
			PDB[i].startPos = HEIGHT;

		}
		break;
	case 38:
		PodobooNum = 2;

		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].type = FIRE;
			PDB[i].PodobooState = PodobooMotion[FIRE_UP];
			PDB[i].pos.X = (4.5 + 3 * i)*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT - 2 * BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
			PDB[i].height = 3;
			PDB[i].startPos = HEIGHT;

		}
		break;
	default:
		PodobooNum = 0;
		break;
	}

}

//푸두부 이미지 저장
void loadPodoboo(char *fileName, int motion)
{
	char tmp;
	int k = 0;
	FILE *fp = fopen(fileName, "r");

	for (int y = 0; y < PODOBOO_HEIGHT; y++)
	{
		for (int x = 0; x < PODOBOO_WIDTH + 1; x++)
		{
			fscanf(fp, "%c", &tmp);
			if ((tmp >= 'A' && tmp <= 'z') || (tmp >= '0' && tmp <= '0'))
				PodobooMotion[motion][x + PODOBOO_WIDTH * y] = tmp;
		}
	}
	fclose(fp);
}

void setPodoboo(int i, int type, int height, int startPos, int x, int y) {
	PDB[i].type = type;
	if(type == FIRE)
		PDB[i].PodobooState = PodobooMotion[FIRE_UP];
	else
		PDB[i].PodobooState = PodobooMotion[WATER_UP];

	PDB[i].startPos = startPos;
	PDB[i].pos.X = x;
	PDB[i].pos.Y = y;
	PDB[i].isUp = 0;
	PDB[i].isDown = 1;
	PDB[i].height = height;
}


void setPodobooMotion(int PDBidx, int direction)
{


	switch (direction)
	{
	case FIRE_UP:
		PDB[PDBidx].PodobooState = PodobooMotion[FIRE_UP];
		break;
	case FIRE_DOWN:
		PDB[PDBidx].PodobooState = PodobooMotion[FIRE_DOWN];
		break;
	case WATER_UP:
		PDB[PDBidx].PodobooState = PodobooMotion[WATER_UP];
		break;
	case WATER_DOWN:
		PDB[PDBidx].PodobooState = PodobooMotion[WATER_DOWN];
		break;
	default:
		PDB[PDBidx].PodobooState = PodobooMotion[WATER_DOWN];
		break;
	}
}

void Podoboo_Gravity()
{
	for (int i = 0; i < PodobooNum; i++)
	{
		if (PDB[i].PodobooState == PodobooMotion[FIRE_UP] || PDB[i].PodobooState == PodobooMotion[WATER_UP])      //올라가고있으면
		{
			deleteObjectFromMap(PDB[i].PodobooState, PODOBOO_WIDTH, PODOBOO_HEIGHT, PDB[i].pos.X, PDB[i].pos.Y);
			PDB[i].pos.Y--;
			setObjectToMap(PDB[i].PodobooState, PODOBOO_WIDTH, PODOBOO_HEIGHT, PDB[i].pos.X, PDB[i].pos.Y);
		}
		else
		{
			deleteObjectFromMap(PDB[i].PodobooState, PODOBOO_WIDTH, PODOBOO_HEIGHT, PDB[i].pos.X, PDB[i].pos.Y);
			PDB[i].pos.Y++;
			setObjectToMap(PDB[i].PodobooState, PODOBOO_WIDTH, PODOBOO_HEIGHT, PDB[i].pos.X, PDB[i].pos.Y);
		}

	}

}



void Podoboo_Move()
{
	for (int i = 0; i < PodobooNum; i++)
	{
		if (PDB[i].isUp == 1) {
			if (PDB[i].pos.Y <= HEIGHT - (16 * PDB[i].height))
			{
				PDB[i].isUp = 0;
				PDB[i].isDown = 1;
				return;
			}

			deleteObjectFromMap(PDB[i].PodobooState, PODOBOO_WIDTH, PODOBOO_HEIGHT, PDB[i].pos.X, PDB[i].pos.Y);
			
			if (PDB[i].type == FIRE)
				setPodobooMotion(i, FIRE_UP);
			else
				setPodobooMotion(i, WATER_UP);

			PDB[i].pos.Y -= 2;
			setObjectToMap(PDB[i].PodobooState, PODOBOO_WIDTH, PODOBOO_HEIGHT, PDB[i].pos.X, PDB[i].pos.Y);

		}
		else if (PDB[i].isDown == 1) {
			if (PDB[i].pos.Y >= PDB[i].startPos)
			{
				if (PDB[i].type == FIRE)
					playPodobooSound();
				else
					playWaterBallSound();
				PDB[i].isUp = 1;
				PDB[i].isDown = 0;
			
				return;
			}

			deleteObjectFromMap(PDB[i].PodobooState, PODOBOO_WIDTH, PODOBOO_HEIGHT, PDB[i].pos.X, PDB[i].pos.Y);
			
			if (PDB[i].type == FIRE)
				setPodobooMotion(i, FIRE_DOWN);
			else
				setPodobooMotion(i, WATER_DOWN);
			
			PDB[i].pos.Y += 2;
			setObjectToMap(PDB[i].PodobooState, PODOBOO_WIDTH, PODOBOO_HEIGHT, PDB[i].pos.X, PDB[i].pos.Y);
		}
		else
		{

		}
	}

}