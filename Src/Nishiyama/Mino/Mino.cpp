#include "../Input/Input.h"
#include "Mino.h"

void Mino::Init()
{
	for (int i = 0; i < FIELD_SIZE_W; i++)
	{
		for (int j = 0; j < FIELD_SIZE_H; j++)
		{
			field[i][j] = false;
			field_Mino[i][j] = MINO_TYPE::TYPE_NONE;
		}
	}

	for (int j = 0; j < FIELD_SIZE_H; j++)
	{
		field[0][j] = true;
		field[FIELD_SIZE_H - 1][j] = true;
	}

	for (int i = 0; i < NEXT_MINO_NUM; i++)
	{
		newMino[i] = (MINO_TYPE)(randomer() % (int)MINO_TYPE::TYPE_NONE);
	}
	currentMino = MINO_TYPE::TYPE_NONE;
	currentAngle = MINO_ANGLE::ANGLE_0;
	currentPosX = 0;
	currentPosY = 0;

	stopCount = 0;
	currentSpeed = 1;
}

void Mino::Step()
{
	if (Input::IsKeyPush(KEY_INPUT_LEFT))
	{

	}
	if (Input::IsKeyPush(KEY_INPUT_RIGHT))
	{

	}
	for (int i = currentSpeed; i > 0; i--)
	{

	}
}

void Mino::Fin()
{
	return;
}

void Mino::MinoReset()
{
	currentAngle = MINO_ANGLE::ANGLE_0;
	currentPosX = 0;
	currentPosY = 0;

	stopCount = 0;

	int NextMinoNum = randomer() % NEXT_MINO_NUM;
	currentMino = newMino[NextMinoNum];

	newMino[NextMinoNum] = (MINO_TYPE)(randomer() % (int)MINO_TYPE::TYPE_NONE);
}

bool Mino::MinoHit(int minoPosX, int minoPosY, MINO_ANGLE minoAngle)
{
	for (int i = 0; i < MINO_SIZE_W; i++)
	{
		for (int j = 0; j < MINO_SIZE_H; j++)
		{
			if (field[minoPosX + i][minoPosY + j] && minoShapes[(int)currentMino][(int)minoAngle][i][j])
			{
				return true;
			}
		}
	}
	return false;
}