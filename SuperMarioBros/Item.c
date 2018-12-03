#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include "info.h"

/*===============================Variables===============================*/
static char Items[3][ITEM_HEIGHT * ITEM_WIDTH];
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
		itemNum = 1;
		setItem(0, COIN, 100, 30);
		break;

	case 2:
		itemNum = 1;
		setItem(0, STAR, 0, 30);
		break;

	case 43:
		itemNum = 1;
		setItem(0, STAR, 0, 30);
		break;

	case 44:
		itemNum = 7;
		for (int i = 0; i < 7; i++)
		{
			setItem(i, COIN, 200 + i* ITEM_WIDTH, 106);
		}
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

extern int isStar;
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
		}
	}
}