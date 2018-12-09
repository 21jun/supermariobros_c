#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

#include "info.h"

/*===============================Variables===============================*/
char *backGroundObjs[50];
static char SmallCloud[SMALL_CLOUD_HEIGHT * SMALL_CLOUD_WIDTH];
static char SmallBush[SMALL_BUSH_HEIGHT * SMALL_BUSH_WIDTH];
static char PipeBody[PIPE_BODY_HEIGHT*PIPE_BODY_WIDTH];
static char PipeTop[PIPE_TOP_HEIGHT*PIPE_TOP_WIDTH];
static char Koopa[KOOPA_HEIGHT*KOOPA_WIDTH];
static char Door[16 * 32];
static char DoorWhite[16 * 32];
static char DoorWhiteReverse[16 * 32];
static char DoorBoss[16 * 64];
static char Brick[BRICK_HEIGHT * BRICK_WIDTH];
static char Brick_Gray[BRICK_HEIGHT * BRICK_WIDTH];
static char Brick_Blue[BRICK_HEIGHT * BRICK_WIDTH];
static char Thorn[THORN_HEIGHT * THORN_WIDTH];
static char Hammer[16 * 32];
static char Star[ITEM_HEIGHT * ITEM_WIDTH];
static char Coin[ITEM_HEIGHT * ITEM_WIDTH];
static char Key[ITEM_HEIGHT * ITEM_WIDTH];
static char Flower[ITEM_HEIGHT * ITEM_WIDTH];
static char Princess[PRINCESS_HEIGHT * PRINCESS_WIDTH];
static char Barrier[4 * 4];
static char Castle[CASTLE_WIDTH * CASTLE_HEIGHT];
/*===============================Functions===============================*/
static void objectConvertor(char *obj, int width, int height);
void loadBackGroundObj(char *fileName, char *dist, int height, int width);

void BackGoundInitialize()
{

	loadBackGroundObj("SmallCloud.txt", SmallCloud, SMALL_CLOUD_WIDTH, SMALL_CLOUD_HEIGHT);
	backGroundObjs[SMALL_CLOUD] = SmallCloud;

	loadBackGroundObj("SmallBush.txt", SmallBush, SMALL_BUSH_WIDTH, SMALL_BUSH_HEIGHT);
	backGroundObjs[SMALL_BUSH] = SmallBush;

	loadBackGroundObj("pipe_top.txt", PipeTop, PIPE_TOP_WIDTH, PIPE_TOP_HEIGHT);
	objectConvertor(PipeTop, PIPE_TOP_WIDTH, PIPE_TOP_HEIGHT);
	backGroundObjs[PIPE_TOP] = PipeTop;

	loadBackGroundObj("pipe_body.txt", PipeBody, PIPE_BODY_WIDTH, PIPE_BODY_HEIGHT);
	objectConvertor(PipeBody, PIPE_BODY_WIDTH, PIPE_BODY_HEIGHT);
	backGroundObjs[PIPE_BODY] = PipeBody;

	loadBackGroundObj("brick.txt", Brick, BRICK_WIDTH, BRICK_HEIGHT);
	objectConvertor(Brick, BRICK_WIDTH, BRICK_HEIGHT);
	backGroundObjs[BRICK] = Brick;

	loadBackGroundObj("brick_gray.txt", Brick_Gray, BRICK_WIDTH, BRICK_HEIGHT);
	objectConvertor(Brick_Gray, BRICK_WIDTH, BRICK_HEIGHT);
	backGroundObjs[BRICK_GRAY] = Brick_Gray;

	loadBackGroundObj("brick_blue.txt", Brick_Blue, BRICK_WIDTH, BRICK_HEIGHT);
	objectConvertor(Brick_Blue, BRICK_WIDTH, BRICK_HEIGHT);
	backGroundObjs[BRICK_BLUE] = Brick_Blue;

	loadBackGroundObj("Thorn.txt", Thorn, BRICK_WIDTH, BRICK_HEIGHT);
	objectConvertor(Thorn, THORN_WIDTH, THORN_HEIGHT);
	backGroundObjs[THORN] = Thorn;

	loadBackGroundObj("Door.txt", Door, 32, 16);
	backGroundObjs[DOOR] = Door;

	loadBackGroundObj("DoorWhite.txt", DoorWhite, 32, 16);
	backGroundObjs[DOORWHITE] = DoorWhite;

	loadBackGroundObj("DoorWhiteReverse.txt", DoorWhiteReverse, 32, 16);
	backGroundObjs[DOORWHITEREVERSE] = DoorWhiteReverse;

	loadBackGroundObj("DoorBoss.txt", DoorBoss, 64, 16);
	backGroundObjs[DOORBOSS] = DoorBoss;

	loadBackGroundObj("Hammer.txt", Hammer, 32, 16);
	backGroundObjs[HAMMER] = Hammer;
	
	loadBackGroundObj("star.txt", Star, 32, 16);
	backGroundObjs[STAR] = Star;

	loadBackGroundObj("coin.txt", Coin, 32, 16);
	backGroundObjs[COIN] = Coin;

	loadBackGroundObj("key.txt", Key, 32, 16);
	backGroundObjs[KEY] = Key;

	loadBackGroundObj("flower.txt", Flower, 32, 16);
	backGroundObjs[FLOWER] = Flower;

	loadBackGroundObj("Princess.txt", Princess, PRINCESS_WIDTH, PRINCESS_HEIGHT);
	backGroundObjs[PRINCESS] = Princess;

	loadBackGroundObj("barrier.txt", Barrier, 4, 4);
	backGroundObjs[BARRIER] = Barrier;

	loadBackGroundObj("castle.txt", Castle, CASTLE_WIDTH, CASTLE_HEIGHT);
	backGroundObjs[CASTLE] = Castle;

}
static char bgConvertor(char x)
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

static void objectConvertor(char *obj, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (obj[x + width * y] == 'A' || obj[x + width * y] == 'a')
				obj[x + width * y] = '1';
		}
	}
}


void loadBackGroundObj(char *fileName, char *dist, int width, int height){
	char tmp;
	int k = 0;
	FILE *fp = fopen(fileName, "r");

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width + 1; x++)
		{
			fscanf(fp, "%c", &tmp);
			if ((tmp >= 'A' && tmp <= 'z') || (tmp >= '0' && tmp <= '9'))
				dist[x + width * y] = bgConvertor(tmp);
		}
	}
	fclose(fp);
}

char* getBackGroundObject(int obj_name)
{
	return backGroundObjs[obj_name];
}
