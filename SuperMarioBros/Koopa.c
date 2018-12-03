#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include "info.h"

#define MAX_KOOPA_NUM 1

/*===============================Variables===============================*/
char KoopaMotion[8][KOOPA_HEIGHT * KOOPA_WIDTH];
int KoopaNum = 0;

typedef struct __koopa {
	COORD pos;
	char *KoopaState;
	int isShooting;
	int isRight;
	int isLeft;
}Koopa;

Koopa Kp[2];		//Koopa °´Ã¼

void loadKoopa(char *fileName, int motion);

void KoopaInitialize(int stage)
{
		//loadKoopa("Koopa.txt", 0);

	loadKoopa("KoopaLeftStand1.txt", 0);
	loadKoopa("KoopaLeftStand2.txt", 1);
	loadKoopa("KoopaRightStand1.txt", 2);
	loadKoopa("KoopaRightStand2.txt", 3);
	loadKoopa("KoopaLeftAttack1.txt", 4);
	loadKoopa("KoopaLeftAttack2.txt", 5);
	loadKoopa("KoopaRightAttack1.txt", 6);
	loadKoopa("KoopaRightAttack2.txt", 7);


	switch (stage)
	{
	case 49:
		KoopaNum = 1;

		Kp[0].KoopaState = KoopaMotion[0];
		Kp[0].pos.X = BRICK_WIDTH*6;
		Kp[0].pos.Y = HEIGHT-3*BRICK_HEIGHT;
		Kp[0].isShooting = 0;
		Kp[0].isLeft = 1;
		Kp[0].isRight = 0;

		break;
	default:
		KoopaNum = 0;
		break;
	}
}

void loadKoopa(char *fileName, int motion)
{
	char tmp;
	int k = 0;
	FILE *fp = fopen(fileName, "r");

	for (int y = 0; y < KOOPA_HEIGHT; y++)
	{
		for (int x = 0; x < KOOPA_WIDTH + 1; x++)
		{
			fscanf(fp, "%c", &tmp);
			if ((tmp >= 'A' && tmp <= 'z') || (tmp >= '0' && tmp <= '0'))
				KoopaMotion[motion][x + KOOPA_WIDTH * y] = tmp;
		}
	}
	fclose(fp);
}

void setKoopaMotion(int m)
{
	Kp[0].KoopaState = KoopaMotion[m];
	/*if (k.isRight== 1) {
		if(k.isShooting==1)
			Kp.KoopaState = KoopaMotion[6];
		else
			Kp.KoopaState = KoopaMotion[2];
	}
	
	else // if (k.isLeft== 1)
	{	
		if (k.isShooting == 1)
			Kp.KoopaState = KoopaMotion[4];
		else
			Kp.KoopaState = KoopaMotion[0];
	}*/
}

int getKoopaMotion(Koopa k)
{
	if (k.isRight == 1) {
		if (k.isShooting == 1)
			return 6;
		else
			return 2;
	}

	else // if (k.isLeft== 1)
	{
		if (k.isShooting == 1)
			return 4;
		else
			return 0;
	}
}

void Koopa_Gravity()
{
	if (KoopaNum == 0) return;
	if (detectCollisionMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X, Kp[0].pos.Y + 1))
	{
		return;
	}
	deleteObjectFromMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X, Kp[0].pos.Y);
	Kp[0].pos.Y++;
	setObjectToMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X, Kp[0].pos.Y);
}

void Koopa_Move()
{
	
	if (KoopaNum == 0) return;

	static int d = 0;	//Koopa Motion change
	static int d_base;
	d++;
		if (Kp[0].isLeft == 1) {
			Kp[0].isShooting = 0;
			if (detectCollisionMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X - 1, Kp[0].pos.Y))
			{
				setKoopaMotion(2);
				d_base = 2;
				Kp[0].isLeft = 0;
				Kp[0].isRight = 1;
				return;
			}

			if (Kp[0].pos.X > 300 && Kp[0].pos.X < 320 || Kp[0].pos.X > 220 && Kp[0].pos.X < 240)
			{
				Kp[0].isShooting = 1;
				deleteObjectFromMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X, Kp[0].pos.Y);
				setKoopaMotion(4 + d % 2);
				Kp[0].pos.X -= 2;
				setObjectToMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X, Kp[0].pos.Y);
				return;
			}

			deleteObjectFromMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X, Kp[0].pos.Y);
			setKoopaMotion(d_base + d % 2);
			Kp[0].pos.X -= 2;
			setObjectToMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X, Kp[0].pos.Y);

		}
		else if (Kp[0].isRight == 1) {
			Kp[0].isShooting = 0;
			if (detectCollisionMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X+1, Kp[0].pos.Y) || Kp[0].pos.X+KOOPA_WIDTH>430)
			{
				setKoopaMotion(0);
				d_base = 0;
				Kp[0].isLeft = 1;
				Kp[0].isRight = 0;
				return;
			}
			if (Kp[0].pos.X > 200 && Kp[0].pos.X < 220 || Kp[0].pos.X > 300 && Kp[0].pos.X < 320)
			{
				Kp[0].isShooting = 1;
				deleteObjectFromMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X, Kp[0].pos.Y);
				setKoopaMotion(6 + d % 2);
				Kp[0].pos.X += 2;
				setObjectToMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X, Kp[0].pos.Y);
				return;
			}
			deleteObjectFromMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X, Kp[0].pos.Y);
			setKoopaMotion(d_base + d % 2);
			Kp[0].pos.X+=2;
			setObjectToMap(Kp[0].KoopaState, KOOPA_WIDTH, KOOPA_HEIGHT, Kp[0].pos.X, Kp[0].pos.Y);
		}
		else {

		}

	//drawMap();
}
