#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

#include "info.h"

/*===============================Variables===============================*/
int marioLife = 5;

char *MarioState;
char MarioMotion[10][MARIO_HEIGHT * MARIO_WIDTH];	//Max 10 motions now
char MarioFire[MARIO_FIRE_HEIGHT * MARIO_FIRE_WIDTH];
enum Motion { lSTAND, rSTAND, lWalk1, lWalk2, lWalk3, rWalk1, rWalk2, rWalk3, lJUMP, rJUMP };
static int isLoadedMario = 0;

// POSITION
COORD MarioPos = { 0,0 };
int isRunning = 0;
int isRight = 0;
int isLeft = 0;

// ITEM
int isStar = 0;
int isFlower = 0;
int isKey = 1;

// JUMP
int isGround = 0;
int isJumping = 0;
int jumpHeight = 0;
int jumpDirection = LEFT;
#define MAX_JUMP_HEIGHT 35
COORD jumpStartPos;

// ATTACK
#define MAX_FIRE_NUM 3
int fireNum = 0;
typedef struct __fireAttack
{
	COORD firePos;
	char *fireState;
	int isRight;
	int isLeft;
	int isUp;
	int isDown;
	int isDead;
	int bounceCount;
	int upCount;
	int downCount;
}FireAttack;
FireAttack fa;

/*===============================Functions===============================*/
void loadMario(char *fileName, int motion);
void Mario_Hit();
void Mario_Move(int direction);
void loadMarioFire(char *fileName);

void marioInitialize(int stage)
{
	if (!isLoadedMario) {
		loadMario("Mario_Stand_Right.txt", rSTAND);
		loadMario("Mario_Stand_Left.txt", lSTAND);
		loadMario("Mario_Walk_1_Right.txt", lWalk1);
		loadMario("Mario_Walk_2_Right.txt", lWalk2);
		loadMario("Mario_Jump_Left.txt", lJUMP);
		loadMario("Mario_Jump_Right.txt", rJUMP);
		loadMarioFire("Mario_Fire.txt");
		isLoadedMario = 1;
	}
	MarioPos.X = 0;
	MarioPos.Y = 66;
	isStar = 0;
	isFlower = 0;
	isKey = 1;
	fa.isDead = 1;
	MarioState = MarioMotion[rSTAND];	// initial motion is right stand
}


char* getMarioState()
{
	return MarioState;
}

void setMarioPos(int x, int y)
{
	MarioPos.X = x;
	MarioPos.Y = y;
}

void loadMario(char *fileName, int motion)
{
	char tmp;
	int k = 0;
	FILE *fp = fopen(fileName, "r");

	for (int y = 0; y < MARIO_HEIGHT; y++)
	{
		for (int x = 0; x < MARIO_WIDTH + 1; x++)
		{
			fscanf(fp, "%c", &tmp);
			if ((tmp >= 'A' && tmp <= 'z') || (tmp >= '0' && tmp <= '0'))
				MarioMotion[motion][x + MARIO_WIDTH * y] = tmp;
		}
	}
	fclose(fp);
}

void loadMarioFire(char *fileName) {
	char tmp;
	int k = 0;
	FILE *fp = fopen(fileName, "r");

	for (int y = 0; y < MARIO_FIRE_HEIGHT; y++)
	{
		for (int x = 0; x < MARIO_FIRE_WIDTH + 1; x++)
		{
			fscanf(fp, "%c", &tmp);
			if (tmp == '!' || ((tmp >= 'A' && tmp <= 'z') || (tmp >= '0' && tmp <= '0')))
			{
				MarioFire[x + MARIO_FIRE_WIDTH * y] = tmp;
			}
		}
	}
	fclose(fp);
}

void setMarioMotion(int motion)
{
	MarioState = MarioMotion[motion];
}

void setMarioDirection(int direction)
{
	if (direction == DIRT_LEFT)
	{
		isLeft = 1;
		isRight = 0;
		//MarioState = MarioMotion[lSTAND];
		setMarioMotion(lSTAND);

	}
	else {
		isRight = 1;
		isLeft = 0;
		//MarioState = MarioMotion[rSTAND];
		setMarioMotion(rSTAND);
	}
}

void setMarioJump(int isJump)
{
	/* isGround만으로 체크하면 쓰레드간의 동기화 문제로 이중점프 가능함 그러므로 바닥과의 충돌검사 필요*/
	if (!detectCollisionMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y + 1)) {

		return;
	}
	if (isGround) {
		playJumpSound();
		//jumpStartPos = MarioPos;
		jumpHeight = 0;
		isJumping = isJump;
	}
}

void setMarioJumpDirection(int dir)
{
	switch (dir)
	{
	case LEFT:
		jumpDirection = LEFT;
		break;
	case RIGHT:
		jumpDirection = RIGHT;
		break;
	case UP:
		jumpDirection = UP;
		break;
	default:
		break;
	}
}

#define JUMPSPEED 1.5
void Mario_Jump()
{
	for (int i = 0; i < JUMPSPEED; i++)
	{
		if (!isGround || !isJumping) {
			return;
		}

		if (jumpHeight >= MAX_JUMP_HEIGHT) {
			jumpHeight = 0;
			isJumping = 0;
			return;
		}

		if (detectCollisionMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y - 2))
		{
			isJumping = 0;
			return;
		}



		jumpHeight++;


		// Set to Map
		deleteObjectFromMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y);
		MarioPos.Y -= 2;

		// Direction Check
		switch (jumpDirection)
		{
		case LEFT:
			if (detectCollisionMap(MarioMotion[lJUMP], MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X - 2, MarioPos.Y)) break;
			MarioPos.X -= 2;
			setMarioMotion(lJUMP);

			break;
		case RIGHT:
			if (detectCollisionMap(MarioMotion[rJUMP], MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X + 2, MarioPos.Y)) break;
			MarioPos.X += 2;
			setMarioMotion(rJUMP);

			break;
		case UP:
			if (isRight) {
				if (detectCollisionMap(MarioMotion[rJUMP], MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y)) break;
				setMarioMotion(rJUMP);
			}
			else {
				if (detectCollisionMap(MarioMotion[lJUMP], MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y)) break;
				setMarioMotion(lJUMP);
			}
			break;
		default:
			break;
		}

		setObjectToMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y);
	}

	//drawMap();
}

#define DROPSPEED 1.2
void Mario_Gravity()
{
	if (isJumping)
		return;

	for (int i = 0; i < DROPSPEED; i++)
	{
		if (detectCollisionMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y + 1))
		{
			isGround = 1;
			if (isRight)
				setMarioMotion(rSTAND);
			else
				setMarioMotion(lSTAND);

			break;
		}
		isGround = 0;
		deleteObjectFromMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y);
		//Collision Check!!
		MarioPos.Y++;
		setObjectToMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y);
	}

	//drawMap();
}

#define MOVESPEED 3
void Mario_Move(int direction)
{

	for (int i = 0; i < MOVESPEED; i++)
	{
		switch (direction)
		{
		case L:
			if (detectCollisionMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X - 1, MarioPos.Y))
			{
				break;
			}

			deleteObjectFromMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y);
			setMarioDirection(DIRT_LEFT);
			//Collision Check!!
			MarioPos.X -= 1;
			setObjectToMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y);
			break;
		case R:

			if (detectCollisionMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X + 1, MarioPos.Y))
			{
				break;
			}

			deleteObjectFromMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y);
			setMarioDirection(DIRT_RIGHT);
			//Collision Check!!
			MarioPos.X += 1;
			setObjectToMap(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y);
			break;
		default:
			break;
		}
	}

	//drawMap();
}

extern int isGameOver;
extern int isGameClear;
extern int nextStage;
void Mario_Hit()
{
	/* NPC/절벽 충돌은 양옆 4칸씩 여유줌 */
	if (detectCollisionObject(MarioState, MARIO_WIDTH - 4, MARIO_HEIGHT, MarioPos.X + 4, MarioPos.Y) == 1 && isStar == 0) {
		isGameOver = 1;
	}
	else if (detectCollisionObject(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y) == 2)
	{
		if (isKey == 1) {
			// ~ 다음단계 함수 부르기
			nextStage = 1;
		}
	}
	else if (detectCollisionObject(MarioState, MARIO_WIDTH, MARIO_HEIGHT, MarioPos.X, MarioPos.Y) == 5)
	{
		isGameClear = 1;
	}

}

COORD getMarioPos()
{
	return MarioPos;
}

void Mario_LifeUP()
{
	play1UpSound();
	marioLife++;
	if (marioLife > 9)
		marioLife = 9;
}



void setMario_Fire_Attack()
{
	if (!isFlower) return;
	if (!isGround) return;

	if (fa.isDead) {
		//if (!fa1.isDead) return;

		playKickSound();


		fa.upCount = 0;
		fa.downCount = 0;

		if (isLeft)
		{
			fa.firePos.X = MarioPos.X;
			fa.firePos.Y = MarioPos.Y + 6;
			fa.isLeft = 1;
			fa.isRight = 0;
			fa.isUp = 0;
			fa.isDown = 1;
			fa.isDead = 0;
			fa.fireState = MarioFire;
			fa.bounceCount = 60;

		}
		else if (isRight)
		{
			fa.firePos.X = MarioPos.X + MARIO_WIDTH;
			fa.firePos.Y = MarioPos.Y + 6;
			fa.isLeft = 0;
			fa.isRight = 1;
			fa.isUp = 0;
			fa.isDown = 1;
			fa.isDead = 0;
			fa.fireState = MarioFire;
			fa.bounceCount = 60;
		}
		else
		{

		}
	}

}

void Mario_Fire_Attack()
{
	static int d = 0;
	int dy = 2;

	if (fa.isDead) return;

	if (fa.isDown)
	{
		dy = 2;
	}
	else if (fa.isUp)
	{
		dy = -2;
	}

	if (fa.isLeft)
	{
		fa.bounceCount--;


		if (detectCollisionMap(fa.fireState, MARIO_FIRE_WIDTH, MARIO_FIRE_HEIGHT, fa.firePos.X - 3, fa.firePos.Y) || fa.bounceCount < 0) {
			deleteObjectFromMap(fa.fireState, MARIO_FIRE_WIDTH, MARIO_FIRE_HEIGHT, fa.firePos.X, fa.firePos.Y);
			fa.isDead = 1;
			return;
		}


		deleteObjectFromMap(fa.fireState, MARIO_FIRE_WIDTH, MARIO_FIRE_HEIGHT, fa.firePos.X, fa.firePos.Y);
		fa.firePos.X -= 3;
		fa.firePos.Y += dy;
		setObjectToMap(fa.fireState, MARIO_FIRE_WIDTH, MARIO_FIRE_HEIGHT, fa.firePos.X, fa.firePos.Y);


	}
	else if (fa.isRight)
	{
		fa.bounceCount--;

		if (detectCollisionMap(fa.fireState, MARIO_FIRE_WIDTH, MARIO_FIRE_HEIGHT, fa.firePos.X + 3, fa.firePos.Y) || fa.bounceCount < 0) {
			deleteObjectFromMap(fa.fireState, MARIO_FIRE_WIDTH, MARIO_FIRE_HEIGHT, fa.firePos.X, fa.firePos.Y);
			fa.isDead = 1;
			return;
		}

		deleteObjectFromMap(fa.fireState, MARIO_FIRE_WIDTH, MARIO_FIRE_HEIGHT, fa.firePos.X, fa.firePos.Y);
		fa.firePos.X += 3;
		fa.firePos.Y += dy;
		setObjectToMap(fa.fireState, MARIO_FIRE_WIDTH, MARIO_FIRE_HEIGHT, fa.firePos.X, fa.firePos.Y);

	}

	if (fa.isDown)
	{
		fa.downCount++;
	}
	if (fa.isUp)
	{
		fa.upCount++;
	}


	int tmp;

	if (fa.isDown && fa.downCount == 3) {
		tmp = fa.isDown;
		fa.isDown = fa.isUp;
		fa.isUp = tmp;
		fa.downCount = 0;
	}
	else if (fa.isUp &&fa.upCount == 3) {
		tmp = fa.isDown;
		fa.isDown = fa.isUp;
		fa.isUp = tmp;
		fa.upCount = 0;
	}
	else {
		
	}

}
