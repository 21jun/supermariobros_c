#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include"info.h"


/*===============================Variables===============================*/
static HANDLE wHnd;
static HANDLE rHnd;

/* Window size coordinates, be sure to start index at zero! */
SMALL_RECT static windowSize = { 0, 0, WIDTH - 1, HEIGHT - 1 };
SMALL_RECT static windowSize2 = { 0, 0, WIDTH * 2, HEIGHT * 2 };

/* A COORD struct for specificying the console's screen buffer dimensions */
COORD static bufferSize = { WIDTH, HEIGHT };

/* Setting up different variables for passing to WriteConsoleOutput */
COORD static characterBufferSize = { WIDTH, HEIGHT };
COORD static characterPosition = { 0, 0 };
SMALL_RECT static consoleWriteArea = { 0, 0, WIDTH - 1, HEIGHT - 1 };

/* A CHAR_INFO structure containing data about a single character */
CHAR_INFO static consoleBuffer[WIDTH * HEIGHT];


/*===============================Functions===============================*/


static void RemoveCursor(void);
void clearBuffer();
void reDrawScreen();

void consoleBufferInitialize() {

	/* initialize handles */
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	/* Set the window size */
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize2);

	/* Set the screen's buffer size */
	SetConsoleScreenBufferSize(wHnd, bufferSize);

	/* Clear Buffer */
	clearBuffer();

	/* Remove Cursor */
	RemoveCursor();

	/* Draw Screen */
	reDrawScreen();
}


HANDLE getReadHandle() {
	return rHnd;
}

HANDLE getWriteHandle() {
	return wHnd;
}

static void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void reDrawScreen()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}



void drawRandomPixelScreen()
{
	int x, y;

	for (y = 0; y < HEIGHT; ++y)
	{
		for (x = 0; x < WIDTH; ++x)
		{
			consoleBuffer[x + WIDTH * y].Char.AsciiChar = (unsigned char)' ';
			consoleBuffer[x + WIDTH * y].Attributes = rand() % 256;
		}
	}

	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void clearBuffer() {
	int j;
	for (j = 0; j < (WIDTH * HEIGHT); j++)
	{
		consoleBuffer[j].Char.AsciiChar = ' ';
		consoleBuffer[j].Attributes =
			BACKGROUND_BLUE |
			BACKGROUND_GREEN |
			BACKGROUND_RED |
			BACKGROUND_INTENSITY;
	}
}

int colorConvertor(char x)
{
	// return 0 ~ 225 color value
	switch (x)
	{

	//MAP
	case '0':
		return 0;
	case '1':
		return 0;
	case '2':
		return 176;
	case '3':
		return 0;

	case '8':
		return 224;
	case '9':
		return 0;
	
	case 'W':			//하얀문
		return 240;

	//NPC COLOR
	case 'A':
		return 0;
	case 'B':
		return 16;
	case 'C':
		return 32;
	case 'D':
		return 48;
	case 'E':
		return 64;
	case 'F':
		return 80;
	case 'G':
		return 96;
	case 'H':
		return 112;
	case 'I':
		return 128;
	case 'J':
		return 144;
	case 'K':
		return 160;
	case 'L':
		return 176;
	case 'M':
		return 192;
	case 'N':
		return 208;
	case 'O':
		return 224;
	case 'P':
		return 240;

	//BackGround Color
	case 'a':
		return 0;
	case 'b':
		return 16;
	case 'c':
		return 32;
	case 'd':
		return 48;
	case 'e':
		return 64;
	case 'f':
		return 80;
	case 'g':
		return 96;
	case 'h':
		return 112;
	case 'i':
		return 128;
	case 'j':
		return 144;
	case 'k':
		return 160;
	case 'l':
		return 176;
	case 'm':
		return 192;
	case 'n':
		return 208;
	case 'o':
		return 224;
	case 'p':
		return 240;

	case 'T':			//공주 테두리
		return 0;

	//MARIO COLOR
	case 'X':
		return 192;
	case 'Y':
		return 96;
	case 'Z':
		return 224;
	case '!':
		return 192;
	case 'q': 
		return 224;

	default:
		break;
	}

	return 0;
}

/* Use this function only for map drawing... */
void setConsoleBuffer(char img[], int imageWidth, int imageHeight, int xoffset, int yoffset)
{
	int x, y;
	int palette;

	for (y = 0; y < imageHeight; ++y)
	{
		for (x = 0; x < imageWidth; ++x)
		{
			//consoleBuffer[(x + xoffset) + WIDTH * (y + yoffset)].Char.AsciiChar = (unsigned char)' ';
			//consoleBuffer[(x + xoffset) + WIDTH * (y + yoffset)].Attributes = colors[x + imageWidth * y];

			consoleBuffer[(x + xoffset) + WIDTH * (y + yoffset)].Attributes = colorConvertor(img[x + imageWidth * y]);
		}

	}


	//consider to delete...(just set write = YES...?)
	reDrawScreen();
	return;
}
