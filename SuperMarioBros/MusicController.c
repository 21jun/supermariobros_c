#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "Digitalv.h"
#pragma comment(lib,"winmm.lib")


/*
*	TODO: ���ݻ�Ȳ: �ݺ������ �ȵ�,
*					�뷡�� ������϶� '�ٸ�' wav ������ �����Ű�� ���ļ� ���� (���� �̸��� ������ ����ȵ�)
*
*/

void playBackGroundMusic(int world, int turn)
{
	MCI_OPEN_PARMS mciOpen;   

	DWORD Sound1, Sound2;


	mciOpen.lpstrDeviceType = TEXT("waveaudio");  // mpegvideo : mp3, waveaudio : wav, avivideo : avi
	switch (world)
	{
	case 0:
		mciOpen.lpstrElementName = TEXT("MainMusic.wav");
		break;
	case 1:
		mciOpen.lpstrElementName = TEXT("MainMusic.wav");
		break;
	case 2:
		mciOpen.lpstrElementName = TEXT("MainMusic.wav");
		break;
	case 3:
		mciOpen.lpstrElementName = TEXT("MainMusic.wav");
		break;
	case 4:
		mciOpen.lpstrElementName = TEXT("Castle.wav");
		break;
	default:
		break;
	}
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
	MCI_PLAY_PARMS mciPlay;
	DWORD dwID = mciOpen.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
	//mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);

	//MCI_NOTIFY : �⺻, MCI_DGV_PLAY_REPEAT : �ݺ�

}

void stopBackGroundMusic(int world, int turn)
{
	MCI_OPEN_PARMS mciOpen;

	DWORD Sound1, Sound2;


	mciOpen.lpstrDeviceType = TEXT("waveaudio");  // mpegvideo : mp3, waveaudio : wav, avivideo : avi
	switch (world)
	{
	case 0:
		mciOpen.lpstrElementName = TEXT("MainMusic.wav");
		break;
	case 1:
		mciOpen.lpstrElementName = TEXT("MainMusic.wav");
		break;
	case 2:
		mciOpen.lpstrElementName = TEXT("MainMusic.wav");
		break;
	case 3:
		mciOpen.lpstrElementName = TEXT("MainMusic.wav");
		break;
	case 4:
		mciOpen.lpstrElementName = TEXT("Castle.wav");
		break;
	default:
		break;
	}
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
	MCI_PLAY_PARMS mciPlay;
	DWORD dwID = mciOpen.wDeviceID;

	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);

}

void playTest2()
{
	MCI_OPEN_PARMS mciOpen;   // MCI_OPEN_PARAMS ����ü ���� 
	mciOpen.lpstrDeviceType = TEXT("waveaudio");  // mpegvideo : mp3, waveaudio : wav, avivideo : avi
	mciOpen.lpstrElementName = TEXT("Castle.wav");
	
	mciSendCommand(0, MCI_OPEN,
		MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen);

	// ���
	MCI_PLAY_PARMS mciPlay;
	DWORD dwID = mciOpen.wDeviceID;



	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);

	//MCI_NOTIFY : �⺻, MCI_DGV_PLAY_REPEAT : �ݺ�

	//�ٽý���
	//mciSendCommandW(dwID, MCI_RESUME, 0, NULL);

	// �Ͻ�����
	//mciSendCommand(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);

	// ����
	//mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);

}



void playJumpSound()
{
	PlaySound(TEXT("Jump.wav"), NULL, SND_ASYNC);
}

void playCoinSound()
{
	PlaySound(TEXT("Coin.wav"), NULL, SND_ASYNC);
}

void playMarioDieSound()
{
	PlaySound(TEXT("Mario dies.wav"), NULL, SND_ASYNC);
}

void playGameOverSound()
{
	PlaySound(TEXT("Game over.wav"), NULL, SND_ASYNC);
}