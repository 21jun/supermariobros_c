#include <windows.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
#include <process.h>

#include "info.h"

/*===============================Variables===============================*/

extern HANDLE  hRunMutex;

INPUT_RECORD *eventBuffer;
extern isRunning;

/*===============================Functions===============================*/


DWORD getInput(INPUT_RECORD **eventBuffer)
{
	
	DWORD numEvents = 0;

	DWORD numEventsRead = 0;

	GetNumberOfConsoleInputEvents(getReadHandle(), &numEvents);

	if (numEvents) 
	{
		*eventBuffer = malloc(sizeof(INPUT_RECORD) * numEvents);
		ReadConsoleInput(getReadHandle(), *eventBuffer, numEvents, &numEventsRead);
	}

	return numEventsRead;
}
extern int isGameOver;
extern int nextStage;
void runGame() {

	DWORD i;

	int write = NO;

	DWORD numEventsRead = 0;

	// if write == YES, then re-draw screen... (flick) 
	//write = YES;

	while (1)
	{

		/*===============================SETUP===============================*/
		if (isGameOver || nextStage) {
			Sleep(3000);
			//continue;
		}

		//WaitForSingleObject(hRunMutex,1);


		/*===============================INPUT===============================*/
		numEventsRead = getInput(&eventBuffer);

		if (numEventsRead)
		{

			for (i = 0; i < numEventsRead; i++)
			{
				switch (eventBuffer[i].EventType)
				{

				case KEY_EVENT:
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode)
					{

					case VK_ESCAPE:
						return 0;

					case 'Q':
						drawRandomPixelScreen();
						break;
					case 'M':
						if (eventBuffer[i].Event.KeyEvent.bKeyDown == 0)
						{
							scoreUp(1);
							//nextStage = 1;
						}
						//drawMap();
						break;
					case 'K':
						if (eventBuffer[i].Event.KeyEvent.bKeyDown == 0)
						{
							setMario_Fire_Attack();
						}
						break;
					case 'C':
						clearBuffer();
						break;
					case 'D':
						Mario_Move(R);
						setMarioJumpDirection(RIGHT);
						if (eventBuffer[i].Event.KeyEvent.bKeyDown == 0)
						{
							setMarioJumpDirection(UP);
						}
						break;
					case 'A':
						Mario_Move(L);
						setMarioJumpDirection(LEFT);
						if (eventBuffer[i].Event.KeyEvent.bKeyDown == 0)
						{
							setMarioJumpDirection(UP);
						}
						break;

					case 'L':
						if (eventBuffer[i].Event.KeyEvent.bKeyDown != 0)
						{
							setMarioJump(YES);
						}
						break;
					case 'R':
						reDrawScreen();
						break;
					case 'X':

						isRunning = 1;

						/* If keypress was a keydown event, not keyup */
						if (eventBuffer[i].Event.KeyEvent.bKeyDown == 0)
						{
							isRunning = 0;
						}
						break;
					}
					break;

				}
			}

			free(eventBuffer);
		}

		/*===============================DRAW===============================*/

		if (write)
		{
			//WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
			reDrawScreen();
			write = NO;
		}
	}
}