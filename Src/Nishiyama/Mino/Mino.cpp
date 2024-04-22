#include "../Input/Input.h"
#include "Mino.h"
#include "../Score/Score.h"

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

	keepMino = MINO_TYPE::TYPE_NONE;
	keepUseFlag = false;

	currentMino = MINO_TYPE::TYPE_NONE;
	currentAngle = MINO_ANGLE::ANGLE_0;
	currentPosX = MINO_DEFAULT_POS_X;
	currentPosY = MINO_DEFAULT_POS_Y;

	MinoReset();

	LmoveCount = 0;
	RmoveCount = 0;
	accelerationCount = 0;

	AddSpeedCount = 0;

	dropCount = 0;
	stopCount = 0;
	currentSpeed = 1;

	renCount = 0;
	doujiCount = 0;

	gameOverFlag = false;

	UI_Number.Init();
	UI_Number.SetNumberFont(Number_16_32_blue);
	UI_Number.Set_posX(NEXT_MINO_POS_X);
	UI_Number.Set_posY(NEXT_MINO_POS_Y + 500);

	for (int i = 0; i < (int)MINO_TYPE::KIND_NUM; i++)
	{
		BlockHandle[i] = LoadGraph(BLOCK_IMAGE_PATH[i]);
	}
	BlockHandle[(int)MINO_TYPE::KIND_NUM] = LoadGraph(WALL_BLOCK_IMAGE_PATH);

	for (int i = 0; i < (int)MINO_TYPE::KIND_NUM; i++)
	{
		MinoHandle[i] = LoadGraph(MINO_IMAGE_PATH[i]);
	}
}

void Mino::Step()
{
	if (gameOverFlag)
		return;

	//ƒL[ƒv
	if (keepUseFlag == false)
	{
		if (Input::IsKeyPush(KEY_INPUT_R))
		{
			if (keepMino == MINO_TYPE::TYPE_NONE)
			{
				keepMino = currentMino;
				MinoReset();
				keepUseFlag = true;
			}
			else
			{
				MINO_TYPE buf = keepMino;
				keepMino = currentMino;
				currentMino = buf;

				currentAngle = MINO_ANGLE::ANGLE_0;
				currentPosX = MINO_DEFAULT_POS_X;
				currentPosY = MINO_DEFAULT_POS_Y;

				keepUseFlag = true;
			}
		}
	}

	//¶ˆÚ“®
	if (Input::IsKeyDown(KEY_INPUT_A))
	{
		if (LmoveCount >= MOVE_FRAME)
		{
			if (!MinoHit(currentPosX - 1, currentPosY, currentAngle))
			{
				currentPosX--;
			}
			LmoveCount = 0;
		}
		else
		{
			LmoveCount++;
		}
	}
	else
	{
		LmoveCount = MOVE_FRAME;
	}
	//‰EˆÚ“®
	if (Input::IsKeyDown(KEY_INPUT_D))
	{
		if (RmoveCount >= MOVE_FRAME)
		{
			if (!MinoHit(currentPosX + 1, currentPosY, currentAngle))
			{
				currentPosX++;
			}
			RmoveCount = 0;
		}
		else
		{
			RmoveCount++;
		}
	}
	else
	{
		RmoveCount = MOVE_FRAME;
	}
	//‰Á‘¬
	if (Input::IsKeyDown(KEY_INPUT_S))
	{
		if (accelerationCount >= ACCELERATION_FRAME)
		{
			if (!MinoHit(currentPosX, currentPosY + 1, currentAngle))
			{
				currentPosY++;
			}
			accelerationCount = 0;
		}
		else
		{
			accelerationCount++;
		}
	}
	else
	{
		accelerationCount = ACCELERATION_FRAME;
	}
	//‰E‰ñ“]
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
			bool NewAngle_Success = false;
			for (int xMove = 1; xMove >= -2; xMove--)
			{
				for (int yMove = -1; yMove <= 1; yMove++)
				{
					if (!MinoHit(currentPosX + xMove, currentPosY + yMove, (MINO_ANGLE)newAngle))
					{
						currentPosX += xMove;
						currentPosY += yMove;
						currentAngle = (MINO_ANGLE)newAngle;

						NewAngle_Success = true;
						break;
					}
				}
				if (NewAngle_Success)
					break;
			}
		}
	}
	//¶‰ñ“]
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
			bool NewAngle_Success = false;
			for (int xMove = -1; xMove <= 2; xMove++)
			{
				for (int yMove = -1; yMove <= 1; yMove++)
				{
					if (!MinoHit(currentPosX + xMove, currentPosY + yMove, (MINO_ANGLE)newAngle))
					{
						currentPosX += xMove;
						currentPosY += yMove;
						currentAngle = (MINO_ANGLE)newAngle;

						NewAngle_Success = true;
						break;
					}
				}
				if (NewAngle_Success)
					break;
			}
		}
	}

	//‘¦—Ž‰º
	if (Input::IsKeyPush(KEY_INPUT_W))
	{
		if (MinoHit(currentPosX, currentPosY + 1, currentAngle))
		{
			stopCount = STOP_NUM;
			dropCount = -1;
		}
		else
		{
			for (int i = currentPosY; i < FIELD_SIZE_H; i++)
			{
				if (MinoHit(currentPosX, i, currentAngle))
				{
					currentPosY = i - 1;
					stopCount = STOP_NUM;
					dropCount = -1;
					break;
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
			if (!Input::IsKeyDown(KEY_INPUT_S))
			{
				currentPosY++;
			}
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
		doujiCount = 0;
		bool renFlag = false;
		for (int i = FIELD_SIZE_H - 2; i >= 0; i--)
		{
			if (DeleteJudge(i))
			{
				Delete(i);
				i++;

				doujiCount++;
				if (renFlag == false)
				{
					renCount++;
					renFlag = true;
				}
			}
		}
		if (renFlag == false)
		{
			renCount = 0;
		}
		else
		{
			Score::AddScore(DEFAULT_SCORE * doujiCount * renCount);
		}

		if (keepUseFlag == true)
		{
			keepUseFlag = false;
		}
		MinoReset();

		if (currentSpeed < DROP_FRAME - 5)
		{
			AddSpeedCount++;
			if (AddSpeedCount > 10)
			{
				AddSpeedCount = 0;
				currentSpeed++;
				if (currentSpeed >= DROP_FRAME - 5)
				{
					currentSpeed = DROP_FRAME - 5;
				}
			}
		}
	}
}

void Mino::Fin()
{
	UI_Number.Fin();

	for (int i = 0; i < (int)MINO_TYPE::KIND_NUM + 1; i++)
	{
		DeleteGraph(BlockHandle[i]);
		BlockHandle[i] = NULL;
	}
	for (int i = 0; i < (int)MINO_TYPE::KIND_NUM; i++)
	{
		DeleteGraph(MinoHandle[i]);
	}
}

void Mino::PredictionDraw()
{
	if (MinoHit(currentPosX, currentPosY + 1, currentAngle))
	{
		for (int H_index = 0; H_index < MINO_SIZE_H; H_index++)
		{
			for (int W_index = 0; W_index < MINO_SIZE_W; W_index++)
			{
				if (minoShapes[(int)currentMino][(int)currentAngle][H_index][W_index] == true)
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
					DrawExtendGraph(FIELD_POS_X + (BLOCK_IMAGE_SIZE + 1) * (currentPosX + W_index),
						FIELD_POS_Y + (BLOCK_IMAGE_SIZE + 1) * (currentPosY + H_index),
						FIELD_POS_X + (BLOCK_IMAGE_SIZE + 1) * (currentPosX + W_index + 1),
						FIELD_POS_Y + (BLOCK_IMAGE_SIZE + 1) * (currentPosY + H_index + 1),
						BlockHandle[(int)currentMino],
						true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
			}
		}
	}
	else
	{
		for (int PreY = currentPosY; PreY < FIELD_SIZE_H; PreY++)
		{
			if (MinoHit(currentPosX, PreY, currentAngle))
			{
				for (int H_index = 0; H_index < MINO_SIZE_H; H_index++)
				{
					for (int W_index = 0; W_index < MINO_SIZE_W; W_index++)
					{
						if (minoShapes[(int)currentMino][(int)currentAngle][H_index][W_index] == true)
						{
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
							DrawExtendGraph(FIELD_POS_X + (BLOCK_IMAGE_SIZE + 1) * (currentPosX + W_index),
								FIELD_POS_Y + (BLOCK_IMAGE_SIZE + 1) * (PreY - 1 + H_index),
								FIELD_POS_X + (BLOCK_IMAGE_SIZE + 1) * (currentPosX + W_index + 1),
								FIELD_POS_Y + (BLOCK_IMAGE_SIZE + 1) * (PreY - 1 + H_index + 1),
								BlockHandle[(int)currentMino],
								true);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						}
					}
				}
				break;
			}
		}
	}
}

void Mino::NextDraw()
{
	for (int i = 0; i < NEXT_MINO_NUM; i++)
	{
		DrawFormatString(NEXT_MINO_POS_X, NEXT_MINO_POS_Y - 50 + NEXT_MINO_OFFSET * i, GetColor(255, 30, 255), "NEXT %d", i + 1);
		DrawRotaGraph(NEXT_MINO_POS_X, NEXT_MINO_POS_Y + NEXT_MINO_OFFSET * i, 1.0, 0.0, MinoHandle[(int)newMino[i]], true);
	}

	if (keepMino != MINO_TYPE::TYPE_NONE)
	{
		DrawFormatString(NEXT_MINO_POS_X - 700, NEXT_MINO_POS_Y - 50, GetColor(255, 30, 255), "KEEP");

		if (keepUseFlag)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		DrawRotaGraph(NEXT_MINO_POS_X - 700, NEXT_MINO_POS_Y, 1.0, 0.0, MinoHandle[(int)keepMino], true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Mino::UIDraw()
{
	if (renCount > 0)
	{
		DrawFormatString(NEXT_MINO_POS_X, NEXT_MINO_POS_Y + 350, GetColor(255, 30, 255), "REN");
		UI_Number.Set_posY(NEXT_MINO_POS_Y + 400);
		UI_Number.Draw_int(renCount);
	}
	DrawFormatString(NEXT_MINO_POS_X, NEXT_MINO_POS_Y + 450, GetColor(255, 30, 255), "SCORE");
	UI_Number.Set_posY(NEXT_MINO_POS_Y + 500);
	UI_Number.Draw_int(Score::GetScore());
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
			if (minoShapes[(int)currentMino][(int)currentAngle][H_index][W_index] == true)
			{
				Draw_Buf_field[currentPosX + W_index][currentPosY + H_index] = true;
				Draw_Buf_field_Mino[currentPosX + W_index][currentPosY + H_index] = currentMino;
			}
		}
	}

	//ü‚Ì•`‰æ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
	for (int i = 0; i < FIELD_SIZE_W; i++)
	{
		DrawLine(FIELD_POS_X + (BLOCK_IMAGE_SIZE + 1) * i,
			FIELD_POS_Y,
			FIELD_POS_X + (BLOCK_IMAGE_SIZE + 1)* i,
			FIELD_POS_Y + BLOCK_IMAGE_SIZE * FIELD_SIZE_H,
			GetColor(255, 255, 255));
	}
	for (int i = 0; i < FIELD_SIZE_H; i++)
	{
		DrawLine(FIELD_POS_X,
			FIELD_POS_Y + (BLOCK_IMAGE_SIZE + 1) * i,
			FIELD_POS_X + BLOCK_IMAGE_SIZE * FIELD_SIZE_W,
			FIELD_POS_Y + (BLOCK_IMAGE_SIZE + 1) * i,
			GetColor(255, 255, 255));
	}
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//ƒuƒƒbƒN‚Ì•`‰æ
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

	if (MinoHit(currentPosX, currentPosY, currentAngle))
	{
		gameOverFlag = true;
	}
}

void Mino::MinoStop()
{
	for (int H_index = 0; H_index < MINO_SIZE_H; H_index++)
	{
		for (int W_index = 0; W_index < MINO_SIZE_W; W_index++)
		{
			if (currentMino == MINO_TYPE::TYPE_S)
			{
				int a = 1;
			}
			if (minoShapes[(int)currentMino][(int)currentAngle][H_index][W_index] == true)
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
			if (field[minoPosX + i][minoPosY + j] && minoShapes[(int)currentMino][(int)minoAngle][j][i])
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