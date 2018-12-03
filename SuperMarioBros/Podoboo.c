#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include"info.h"

/*===============================Variables===============================*/
char PodobooMotion[2][PODOBOO_HEIGHT * PODOBOO_WIDTH];
int PodobooNum = 0;


typedef struct __podoboo {
	COORD pos;
	char *PodobooState;
	int isUp;
	int isDown;
}Podoboo;
#define MAX_PODOBOO_NUM 10

Podoboo PDB[MAX_PODOBOO_NUM];		

/*===============================Functions===============================*/
void loadPodoboo(char *fileName, int motion);

void PodobooInitialize(int stage)
{

	loadPodoboo("PodobooUp.txt", 0);
	loadPodoboo("PodobooDown.txt", 1);


	switch (stage)
	{
	
	case 1:
		PodobooNum = 1;

		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].PodobooState = PodobooMotion[1];
			PDB[i].pos.X = (5 + 4 * i)*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT - 2 * BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
		}
		break;

	case 22:

		PodobooNum = 1;


		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].PodobooState = PodobooMotion[1];
			PDB[i].pos.X = (11)*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT - 3 * BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
		}
		break;


	case 24:

		PodobooNum = 1;


		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].PodobooState = PodobooMotion[1];
			PDB[i].pos.X = (12)*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT - 3 * BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
		}
		break;

	case 25:
		PodobooNum = 1;
		

		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].PodobooState = PodobooMotion[1];
			PDB[i].pos.X = ( 5)*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT - 3* BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
		}
		break;
	case 41:
		PodobooNum = 2;

		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].PodobooState = PodobooMotion[1];
			PDB[i].pos.X = (5 + 4 * i)*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT- 2*BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
		}
		break;
	case 42:
		PodobooNum = 1;

		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].PodobooState = PodobooMotion[1];
			PDB[i].pos.X = (3)*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT - 2 * BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
		}
		break;
	case 45:
		PodobooNum = 2;

		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].PodobooState = PodobooMotion[1];
			PDB[i].pos.X = (3.5 +3*i )*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT - 2 * BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
		}
		break;
	case 48:
		PodobooNum = 2;

		for (int i = 0; i < PodobooNum; i++)
		{
			PDB[i].PodobooState = PodobooMotion[1];
			PDB[i].pos.X = (4.5 + 3 * i)*BRICK_WIDTH;
			PDB[i].pos.Y = HEIGHT - 2 * BRICK_HEIGHT;
			PDB[i].isUp = 0;
			PDB[i].isDown = 1;
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

void setPodobooMotion(int PDBidx, int direction)
{
	//1 : DOWN     0 : UP
	if (direction == 1) {
		PDB[PDBidx].PodobooState = PodobooMotion[1];
	}
	else {
		PDB[PDBidx].PodobooState = PodobooMotion[0];
	}
}

void Podoboo_Gravity()
{
	for (int i = 0; i < PodobooNum; i++)
	{
		if (PDB[i].PodobooState==PodobooMotion[0])		//올라가고있으면
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
			if (PDB[i].pos.Y<=HEIGHT-(16*3))
			{
				PDB[i].isUp = 0;
				PDB[i].isDown = 1;
				return;
			}

			deleteObjectFromMap(PDB[i].PodobooState, PODOBOO_WIDTH, PODOBOO_HEIGHT, PDB[i].pos.X, PDB[i].pos.Y);
			setPodobooMotion(i, 0);
			PDB[i].pos.Y-=2;
			setObjectToMap(PDB[i].PodobooState, PODOBOO_WIDTH, PODOBOO_HEIGHT, PDB[i].pos.X, PDB[i].pos.Y);

		}
		else if (PDB[i].isDown == 1) {
			if (PDB[i].pos.Y >=HEIGHT)
			{
				playPodobooSound();
				PDB[i].isUp = 1;
				PDB[i].isDown = 0;
				//Sleep(1000);
				return;
			}

			deleteObjectFromMap(PDB[i].PodobooState, PODOBOO_WIDTH, PODOBOO_HEIGHT, PDB[i].pos.X, PDB[i].pos.Y);
			setPodobooMotion(i, 1);
			PDB[i].pos.Y+=2;
			setObjectToMap(PDB[i].PodobooState, PODOBOO_WIDTH, PODOBOO_HEIGHT, PDB[i].pos.X, PDB[i].pos.Y);
		}
		else
		{

		}
	}
	//drawMap();
}
