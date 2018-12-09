#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>


int isGameOver = 0;
int nextStage = 0;
int isGameClear = 0;
extern int marioLife;
extern int stage;
DWORD WINAPI InputProcess(LPVOID);
DWORD WINAPI EnemyProcess(LPVOID);
DWORD WINAPI ScreenProcess(LPVOID);
DWORD WINAPI MarioProcess(LPVOID);


int main() 
{
	/*===============================Initialize===============================*/
	BackGoundInitialize();
	LoadStage(stage);

	/*===============================Thread===============================*/
	HANDLE hThrd_input;
	HANDLE hThrd_Enemy;
	HANDLE hThrd_Screen;
	HANDLE hThrd_Mario;
	DWORD threadId;
	int i = 0;

	hThrd_input = CreateThread(NULL,
		0,
		InputProcess, 
		(LPVOID)1,
		0,
		&threadId);
	if (hThrd_input)
	{
		printf("Thread launched %d\n", i);
		CloseHandle(hThrd_input);
	}

	hThrd_Enemy = CreateThread(NULL,
		0,
		EnemyProcess, 
		(LPVOID)2, 
		0,
		&threadId);
	if (hThrd_Enemy)
	{
		printf("Thread launched %d\n", i);
		CloseHandle(hThrd_Enemy);
	}


	hThrd_Mario = CreateThread(NULL,
		0,
		MarioProcess,
		(LPVOID)1,
		0,
		&threadId);
	if (hThrd_Mario)
	{
		printf("Thread launched %d\n", i);
		CloseHandle(hThrd_Mario);
	}

	//hThrd_Screen = CreateThread(NULL,
	//	0,
	//	ScreenProcess,
	//	(LPVOID)1,
	//	0,
	//	&threadId);
	//if (hThrd_Screen)
	//{
	//	printf("Thread launched %d\n", i);
	//	CloseHandle(hThrd_Screen);
	//}



	// Wait for threads to complete.
	while (marioLife)
	{
		if (isGameOver == 1) {
			marioLife -= 1;

			playMarioDieSound();

			LoadStage(stage);
			drawGameOverScreen();
			Sleep(3000);
			isGameOver = 0;

			if (marioLife == 0) {
				playGameOverSound();
				Sleep(3000);
				return;
			}

			drawMap();
		}

		if (nextStage == 1)
		{
			if (stage == 15) stage = 20;
			if (stage == 25) stage = 30;
			if (stage == 39) stage = 40;
			LoadStage(++stage);
			drawGameOverScreen();
			Sleep(3000);
			nextStage = 0;

			drawMap();
		}


	}

	playGameOverSound();
	return;
}



DWORD WINAPI InputProcess(LPVOID i)
{
	runGame();
}

DWORD WINAPI EnemyProcess(LPVOID j)
{
	while(1)
	{
		Bird_Die();
		Gumba_Die();
		Turtle_Die();

		Gumba_Move();
		Gumba_Gravity();

		Bird_Move();

		Turtle_Move();
		Turtle_Gravity();

		Podoboo_Move();
		Podoboo_Gravity();

		Koopa_Move();

		Item_die();

		Sleep(100);
		if (isGameOver||nextStage) {
			Sleep(3000);
		}

	
	}
}

DWORD WINAPI MarioProcess(LPVOID i)
{
	while(1)
	{
		Mario_Hit();
		Mario_Gravity();
		Mario_Jump();
		Mario_Fire_Attack();
		drawMap();
		Sleep(10);
		if (isGameOver|| nextStage) {
			Sleep(2000);
		}
		if (marioLife == 0) {
			return;
		}
	}
}


// 필요한가?
DWORD WINAPI ScreenProcess(LPVOID i)
{
	while (1)
	{
		//drawMap();
		//Sleep(1000 / 60);
	}
}