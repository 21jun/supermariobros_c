#include<stdio.h>
#include<string.h>
#include "info.h"

static int score = 0;
char Screen[HEIGHT * WIDTH];
char Numbers[10][NUMBER_HEIGHT * NUMBER_WIDTH];
char Letters[11][LETTER_HEIGHT * LETTER_WIDTH];

void loadTextScreen(char *fileName, int mapNum);
void loadChar(char *fileName, char *dist, int width, int height);
void drawScore();
void clearScreen();
void setObjectToScreen(char img[], int imageWidth, int imageHeight, int xoffset, int yoffset);
static char UIConvertor(char x);


void ScreenInitialize()
{

	loadTextScreen("GameOverScreen.txt", 1);
		
		
	for (int i = 0; i < 10; i++)
	{
		char num[8];
		char txt[8] = ".txt";
		num[0] = i + 48;
		num[1] = 0;
		strcat(num, txt);
		loadChar(num, Numbers[i], NUMBER_WIDTH, NUMBER_HEIGHT);
	}


	loadChar("W.txt", Letters[IW], LETTER_WIDTH, LETTER_HEIGHT);
	loadChar("O.txt", Letters[IO], LETTER_WIDTH, LETTER_HEIGHT);
	loadChar("R.txt", Letters[IR], LETTER_WIDTH, LETTER_HEIGHT);
	loadChar("L.txt", Letters[IL], LETTER_WIDTH, LETTER_HEIGHT);
	loadChar("D.txt", Letters[ID], LETTER_WIDTH, LETTER_HEIGHT);
	loadChar("-.txt", Letters[IDASH], LETTER_WIDTH, LETTER_HEIGHT);
	




	drawScore();

}

void loadTextScreen(char *fileName, int mapNum)
{
	char tmp;
	int k = 0;
	FILE *fp = fopen(fileName, "r");

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH + 1; x++)
		{
			fscanf(fp, "%c", &tmp);
			if (tmp >= '0' && tmp <= '9')
				Screen[x + WIDTH * y] = tmp;
		}
	}
	fclose(fp);
}

void loadChar(char *fileName, char *dist, int width, int height)
{
	char tmp;
	int k = 0;
	FILE *fp = fopen(fileName, "r");

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width + 1; x++)
		{
			fscanf(fp, "%c", &tmp);
			if ((tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9'))
				dist[x + width * y] = UIConvertor(tmp);
		}
	}
	fclose(fp);
}

extern char *MarioState;
extern int marioLife;
extern int stage;
void drawGameOverScreen()
{
	clearScreen();

	if (marioLife == 0) {
		// 완전게임오버때 그릴 화면...
	}
	else {
		setObjectToScreen(MarioState, MARIO_WIDTH, MARIO_HEIGHT, 200, 60);
		setObjectToScreen(Numbers[marioLife], NUMBER_WIDTH, NUMBER_HEIGHT, 250, 65);
		setObjectToScreen(Letters[IW], LETTER_WIDTH, LETTER_HEIGHT, 150, 30);
		setObjectToScreen(Letters[IO], LETTER_WIDTH, LETTER_HEIGHT, 170, 30);
		setObjectToScreen(Letters[IR], LETTER_WIDTH, LETTER_HEIGHT, 190, 30);
		setObjectToScreen(Letters[IL], LETTER_WIDTH, LETTER_HEIGHT, 210, 30);
		setObjectToScreen(Letters[ID], LETTER_WIDTH, LETTER_HEIGHT, 230, 30);

		setObjectToScreen(Numbers[((stage - 1) / 10) + 1], NUMBER_WIDTH, NUMBER_HEIGHT, 290, 30);
		setObjectToScreen(Letters[IDASH], NUMBER_WIDTH, NUMBER_HEIGHT, 310, 30);
		setObjectToScreen(Numbers[stage%10], NUMBER_WIDTH, NUMBER_HEIGHT, 330, 30);


	}

	setConsoleBuffer(Screen, WIDTH, HEIGHT, 0, 0);
}

void setObjectToScreen(char img[], int imageWidth, int imageHeight, int xoffset, int yoffset)
{
	char tmp;

	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			tmp = img[x + imageWidth * y];
			if (tmp == '0') {
				continue;
			}
			Screen[(x + xoffset) + WIDTH * (y + yoffset)] = tmp;
		}
	}

}

void clearScreen() {

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{

			Screen[x  + WIDTH * y] = '0';
		}
	}
}


void scoreUp(int add) 
{
	score += add;
	if (score >= 10) {
		Mario_LifeUP();
		score = 0;
	}
	drawScore();
}

void drawScore()
{
	deleteObjectFromMap(Numbers[score], NUMBER_WIDTH, NUMBER_HEIGHT, WIDTH - 40, 5);
	setObjectToMap(Numbers[score], NUMBER_WIDTH, NUMBER_HEIGHT, WIDTH - 40, 5);

	drawMap();
}


void drawStage()
{
	deleteObjectFromMap(Numbers[2], NUMBER_WIDTH, NUMBER_HEIGHT, WIDTH - 80, 5);
	setObjectToMap(Numbers[2], NUMBER_WIDTH, NUMBER_HEIGHT, WIDTH - 80, 5);
}

static char UIConvertor(char x)
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