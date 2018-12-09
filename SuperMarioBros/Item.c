#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include "info.h"

/*===============================Variables===============================*/
static char Items[5][ITEM_HEIGHT * ITEM_WIDTH];
int itemNum = 0;
typedef struct __item {
	COORD pos;
	char *type;
	int name;
	int isDead;
}Item;

#define MAX_ITEM_NUM 10
Item item[MAX_ITEM_NUM];		

/*===============================Functions===============================*/
void loadItem(char *fileName, int motion);
static char itemConvertor(char x);
void Item_die();
void setItem(int itemIndex, int type, int x, int y);


extern int isStar;
extern int isKey;
extern int isFlower;
/*
	[주위사항]
	KEY를 세팅할 스테이지에서는 isKey = 0 설정해야함

*/
void ItemInitialize(int stage)
{

	for (int i = 0; i < itemNum; i++)
	{
		item[i].isDead = 0;
	}

	switch (stage)
	{
	//=====================================[WORLD 1]=====================================
	case 1:
		itemNum = 2;
		isKey = 0;
		setItem(0, COIN, 100, 30);
		setItem(1, KEY, 200, 30);
		break;

	case 2:
		itemNum = 1;
		setItem(0, STAR, 0, 30);
		break;

	case 3:

		itemNum = 1;
		setItem(0, FLOWER, 0, 30);
		break;
	//=====================================[WORLD 2]=====================================

	case 12:

		isKey = 0;

		itemNum = 1;
		setItem(0, KEY, 7 * BRICK_WIDTH, 1 * BRICK_HEIGHT);

		break;

	case 13:

		isKey = 0;

		itemNum = 1;
		setItem(0, KEY, 9 * BRICK_WIDTH, 5 * BRICK_HEIGHT);

		break;

	case 14:

		itemNum = 7;
		for (int i = 0; i < itemNum; i++)
		{
			setItem(i, COIN, 64 + i * 64, HEIGHT - 4 * BRICK_HEIGHT);
		}

		break;

	case 15:
		isKey = 0;
		itemNum = 2;
		setItem(0, KEY, 420, 30);
		setItem(1, FLOWER, 420, HEIGHT- 2 * 16);
		break;

	//=====================================[WORLD 4]=====================================
	case 32:
		itemNum = 1;
		setItem(0, COIN, BRICK_WIDTH, HEIGHT - 6 * BRICK_HEIGHT);
		break;

	case 36:
		itemNum = 7;
		for (int i = 0; i < 6; i++)
		{
			if (i < 3)
				setItem(i, COIN, 3 * BRICK_WIDTH + i * ITEM_WIDTH, 2 * BRICK_HEIGHT);
			else
				setItem(i, COIN, 7 * BRICK_WIDTH + i * ITEM_WIDTH, 2 * BRICK_HEIGHT);
		}
		setItem(6, FLOWER, 2 * BRICK_WIDTH, 5 * BRICK_HEIGHT);

		break;
	case 37:
		itemNum = 1;
		setItem(0, STAR, 32, HEIGHT - 6 * BRICK_HEIGHT);
		break;

	default:
		itemNum = 0;
		break;
	}

}

void setItem(int idx, int type, int x, int y)
{
	item[idx].type = Items[type];
	item[idx].name = type;
	item[idx].pos.X = x;
	item[idx].pos.Y = y;
	setObjectToMap(getBackGroundObject(type), ITEM_WIDTH, ITEM_HEIGHT, x, y);
}


void loadItem(char *fileName, int type)
{
	char tmp;
	int k = 0;
	FILE *fp = fopen(fileName, "r");

	for (int y = 0; y < ITEM_HEIGHT; y++)
	{
		for (int x = 0; x < ITEM_WIDTH + 1; x++)
		{
			fscanf(fp, "%c", &tmp);
			if ((tmp >= 'A' && tmp <= 'z') || (tmp >= '0' && tmp <= '0'))
				Items[type][x + ITEM_WIDTH * y] = itemConvertor(tmp);
		}
	}
	fclose(fp);
}


static char itemConvertor(char x)
{
	switch (x)
	{

	case 'A':
		return 'a';
	case 'B':
		return 'b';
	case 'C':
		return 'c';
	case 'D':
		return 'd';
	case 'E':
		return 'e';
	case 'F':
		return 'f';
	case 'G':
		return 'g';
	case 'H':
		return 'h';
	case 'I':
		return 'i';
	case 'J':
		return 'j';
	case 'K':
		return 'k';
	case 'L':
		return 'l';
	case 'M':
		return 'm';
	case 'N':
		return 'n';
	case 'O':
		return 'o';
	case 'P':
		return 'p';

	default:
		return x;
		break;
	}

	return 0;
}

extern int stage;
void Item_die()
{
	for (int i = 0; i < itemNum; i++)
	{

		if (item[i].isDead) continue;
		if (ItemDetectCollisionObject(item[i].type, ITEM_WIDTH, ITEM_HEIGHT, item[i].pos.X, item[i].pos.Y))
		{
			deleteObjectFromMap(item[i].type, ITEM_WIDTH, ITEM_HEIGHT, item[i].pos.X, item[i].pos.Y);
			if (item[i].name == COIN) {
				playCoinSound();
				scoreUp(1);
				item[i].isDead = 1;
				return;
			}
			else if (item[i].name == STAR)
			{
				playStarSound();
				isStar = 1;
				item[i].isDead = 1;
				return;
			}
			else if (item[i].name == KEY)
			{
				playPowerUpSound();
				isKey = 1;
				item[i].isDead = 1;

				if (stage == 13)
				{
					GumbaInitialize(113);
				}

				if (stage == 15)
				{
					TurtleInitialize(115);
				}

				return;
			}
			else if (item[i].name == FLOWER)
			{
				playPowerUpSound();
				isFlower = 1;
				item[i].isDead = 1;
				return;
			}
		}
	}
}