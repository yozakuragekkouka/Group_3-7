#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"
#include "../Score/Score.h"
#include "../Sound/Sound.h"

//BGM�֘A
BGM_Data bgmdata;
int bgmcount = 0;

//�v���C�V�[��������
void ScenePlay::Init()
{
	Score::Init();     //�O���V���{���G���[�����E�E�E�@�������ς�

	gameOverCount = 0;

	BG_Image.RectInit(LoadGraph(PLAY_SCENE_BG_PATH), VGet(0.0f, 0.0f, 0.0f), 1280, 720);
	GO_BG_Image.RectInit(LoadGraph(PLAY_SCENE_GAMEOVER_BG_PATH), VGet(0.0f, 0.0f, 0.0f), 1280, 720);
	GO_TEXT_Image.RectInit(LoadGraph(PLAY_SCENE_GAMEOVER_TEXT_PATH), VGet((float)SCREEN_SIZE_X / 2.0f, (float)SCREEN_SIZE_Y / 2.0f, 0.0f), 609, 92);
	mino.Init();
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//�v���C�V�[���ʏ폈��
void ScenePlay::Step()
{
	mino.Step();
	if (mino.GetgameOverFlag())
	{
		if (gameOverCount < 60)
		{
			gameOverCount++;
		}
		else
		{
			if (Input::PressAnyKey())
			{
				SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
			}
		}
	}
	if (bgmcount == 0) {
		bgmdata.BGMInit(BGM_PLAY);  //BGM�𗬂�
		bgmcount++;   //���₷
	}
}

//�v���C�V�[���`�揈��
void ScenePlay::Draw()
{
	BG_Image.DrawRect();

	mino.PredictionDraw();
	mino.FieldDraw();

	mino.NextDraw();
	mino.UIDraw();

	if (mino.GetgameOverFlag())
	{
		GO_BG_Image.DrawRect();
		GO_TEXT_Image.DrawRect_Rota_Center();
	}
}

//�v���C�V�[���㏈��
//���g���C���ǂ�����Ԃ�
void ScenePlay::Fin()
{
	BG_Image.RectFin();
	mino.Fin();
	bgmdata.FinBGM();
	SoundEffect::Fin();
	bgmcount = 0;     //�߂�
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_RESULT;
}
