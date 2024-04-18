#include "../Input/Input.h"
#include "Mino.h"

Mino::~Mino()
{
	for (int i = 0; i < (int)MINO_TYPE::KIND_NUM + 1; i++)
	{
		if (!(BlockHandle[i] == NULL))
			DeleteGraph(BlockHandle[i]);
	}
}

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
		if (j == FIELD_SIZE_H - 1)
		{
			for (int i = 0; i < FIELD_SIZE_W; i++)
			{
				field[i][j] = true;
			}
		}
		else
		{
			field[0][j] = true;
			field[FIELD_SIZE_W - 1][j] = true;
		}
	}

	for (int i = 0; i < NEXT_MINO_NUM; i++)
	{
		newMino[i] = (MINO_TYPE)(randomer() % (int)MINO_TYPE::KIND_NUM);
	}
	currentMino = MINO_TYPE::TYPE_NONE;
	currentAngle = MINO_ANGLE::ANGLE_0;
	currentPosX = MINO_DEFAULT_POS_X;
	currentPosY = MINO_DEFAULT_POS_Y;

	MinoReset();

	dropCount = 0;
	stopCount = 0;
	currentSpeed = 1;

	for (int i = 0; i < (int)MINO_TYPE::KIND_NUM; i++)
	{
		BlockHandle[i] = LoadGraph(BLOCK_IMAGE_PATH[i]);
	}
	BlockHandle[(int)MINO_TYPE::KIND_NUM] = LoadGraph(WALL_BLOCK_IMAGE_PATH);
}

void Mino::Step()
{
	if (Input::IsKeyPush(KEY_INPUT_A))
	{
		if (!MinoHit(currentPosX - 1, currentPosY, currentAngle))
		{
			currentPosX--;
		}
	}
	if (Input::IsKeyPush(KEY_INPUT_D))
	{
		if (!MinoHit(currentPosX + 1, currentPosY, currentAngle))
		{
			currentPosX++;
		}
	}
	if (Input::IsKeyPush(KEY_INPUT_E))
	{
		int newAngle = (int)currentAngle - 1;
		if (newAngle < 0)
		{
			newAngle = (int)MINO_ANGLE::KIND_NUM - 1;
		}

		if (!MinoHit(currentPosX, currentPosY, (MINO_ANGLE)newAngle))
		{
			currentAngle = (MINO_ANGLE)newAngle;
		}
		else
		{
			for (int xMove = -1; xMove <= 1; xMove++)
			{
				for (int yMove = -1; yMove <= 1; yMove++)
				{
					if (!MinoHit(currentPosX + xMove, currentPosY + yMove, (MINO_ANGLE)newAngle))
					{
						currentPosX += xMove;
						currentPosY += yMove;
						currentAngle = (MINO_ANGLE)newAngle;
					}
				}
			}
		}
	}
	if (Input::IsKeyPush(KEY_INPUT_Q))
	{
		int newAngle = (int)currentAngle + 1;
		if (newAngle >= (int)MINO_ANGLE::KIND_NUM)
		{
			newAngle = 0;
		}

		if (!MinoHit(currentPosX, currentPosY, (MINO_ANGLE)newAngle))
		{
			currentAngle = (MINO_ANGLE)newAngle;
		}
		else
		{
			for (int xMove = 1; xMove >= -1; xMove--)
			{
				for (int yMove = -1; yMove <= 1; yMove++)
				{
					if (!MinoHit(currentPosX + xMove, currentPosY + yMove, (MINO_ANGLE)newAngle))
					{
						currentPosX += xMove;
						currentPosY += yMove;
						currentAngle = (MINO_ANGLE)newAngle;
					}
				}
			}
		}
	}

	if (dropCount >= DROP_FRAME - currentSpeed)
	{
		if (MinoHit(currentPosX, currentPosY + 1, currentAngle))
		{
			stopCount++;
		}
		else
		{
			currentPosY++;
			stopCount = 0;
		}
		dropCount = 0;
	}
	else
	{
		dropCount++;
	}
	
	if (stopCount >= STOP_NUM)
	{
		MinoStop();
		for (int i = FIELD_SIZE_H - 2; i >= 0; i--)
		{
			if (DeleteJudge(i))
			{
				Delete(i);
			}
		}
		MinoReset();
	}
}

void Mino::Fin()
{
	for (int i = 0; i < (int)MINO_TYPE::KIND_NUM + 1; i++)
	{
		DeleteGraph(BlockHandle[i]);
		BlockHandle[i] = NULL;
	}
}

void Mino::FieldDraw()
{
	bool Draw_Buf_field[FIELD_SIZE_W][FIELD_SIZE_H];
	memcpy_s(Draw_Buf_field, sizeof(Draw_Buf_field),
			field, sizeof(Draw_Buf_field));

	MINO_TYPE Draw_Buf_field_Mino[FIELD_SIZE_W][FIELD_SIZE_H];
	memcpy_s(Draw_Buf_field_Mino, sizeof(Draw_Buf_field_Mino),
			field_Mino, sizeof(Draw_Buf_field_Mino));

	for (int H_index = 0; H_index < MINO_SIZE_H; H_index++)
	{
		for (int W_index = 0; W_index < MINO_SIZE_W; W_index++)
		{
			if (minoShapes[(int)currentMino][(int)currentAngle][W_index][H_index] == true)
			{
				Draw_Buf_field[currentPosX + W_index][currentPosY + H_index] = true;
				Draw_Buf_field_Mino[currentPosX + W_index][currentPosY + H_index] = currentMino;
			}
		}
	}

	for (int i = 0; i < FIELD_SIZE_H; i++)
	{
		for (int j = 0; j < FIELD_SIZE_W; j++)
		{
			if (Draw_Buf_field[j][i])
			{
				//•Ç‚Ì•`‰æ
				if (i == FIELD_SIZE_H - 1 ||
					j == 0 ||
					j == FIELD_SIZE_W - 1)
				{
					DrawExtendGraph(FIELD_POS_X + (BLOCK_IMAGE_SIZE + 1) * j,
						FIELD_POS_Y + (BLOCK_IMAGE_SIZE + 1) * i,
						FIELD_POS_X + (BLOCK_IMAGE_SIZE + 1) * (j + 1),
						FIELD_POS_Y + (BLOCK_IMAGE_SIZE + 1) * (i + 1),
						BlockHandle[(int)MINO_TYPE::KIND_NUM],
						true);
				}
				//’Êí‚Ìƒ~ƒm‚Ì•`‰æ
				else
				{
					//ƒGƒ‰[ƒuƒƒbƒN
					if (Draw_Buf_field_Mino[j][i] == MINO_TYPE::TYPE_NONE)
					{
						DrawBox(FIELD_POS_X + (BLOCK_IMAGE_SIZE + 1) * j,
							FIELD_POS_Y + (BLOCK_IMAGE_SIZE + 1) * i,
							FIELD_POS_X + (BLOCK_IMAGE_SIZE + 1) * (j + 1),
							FIELD_POS_Y + (BLOCK_IMAGE_SIZE + 1) * (i + 1),
							GetColor(255, 255, 255),
							true);
					}
					//’Êí‚Ìƒ~ƒm
					else
					{
						DrawExtendGraph(FIELD_POS_X + (BLOCK_IMAGE_SIZE + 1) * j,
							FIELD_POS_Y + (BLOCK_IMAGE_SIZE + 1) * i,
							FIELD_POS_X + (BLOCK_IMAGE_SIZE + 1) * (j + 1),
							FIELD_POS_Y + (BLOCK_IMAGE_SIZE + 1) * (i + 1),
							BlockHandle[(int)Draw_Buf_field_Mino[j][i]],
							true);
					}
				}
			}
		}
	}
}

void Mino::MinoReset()
{
	currentAngle = MINO_ANGLE::ANGLE_0;
	currentPosX = MINO_DEFAULT_POS_X;
	currentPosY = MINO_DEFAULT_POS_Y;

	int NextMinoNum = randomer() % NEXT_MINO_NUM;
	currentMino = newMino[NextMinoNum];

	newMino[NextMinoNum] = (MINO_TYPE)(randomer() % (int)MINO_TYPE::KIND_NUM);
}

void Mino::MinoStop()
{
	for (int H_index = 0; H_index < MINO_SIZE_H; H_index++)
	{
		for (int W_index = 0; W_index < MINO_SIZE_W; W_index++)
		{
			if (minoShapes[(int)currentMino][(int)currentAngle][W_index][H_index] == true)
			{
				field[currentPosX + W_index][currentPosY + H_index] = true;
				field_Mino[currentPosX + W_index][currentPosY + H_index] = currentMino;
			}
		}
	}
	stopCount = 0;
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

bool Mino::DeleteJudge(int JudgeHeight)
{
	for (int i = 1; i < FIELD_SIZE_W - 1; i++)
	{
		if (!field[i][JudgeHeight])
		{
			return false;
		}
	}
	return true;
}

void Mino::Delete(int JudgeHeight)
{
	for (int i = JudgeHeight; i > 0; i--)
	{
		for (int j = 1; j < FIELD_SIZE_W - 1; j++)
		{
			field[j][i] = field[j][i - 1];
			field_Mino[j][i] = field_Mino[j][i - 1];
		}
	}
	for (int j = 1; j < FIELD_SIZE_W - 1; j++)
	{
		field[j][0] = false;
		field_Mino[j][0] = MINO_TYPE::TYPE_NONE;
	}
}