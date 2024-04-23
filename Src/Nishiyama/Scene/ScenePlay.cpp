#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"
#include "../Score/Score.h"
#include "../Sound/Sound.h"

//BGM関連
BGM_Data bgmdata;
int bgmcount = 0;

//プレイシーン初期化
void ScenePlay::Init()
{
	Score::Init();     //外部シンボルエラー発生・・・　※解消済み

	gameOverCount = 0;

	BG_Image.RectInit(LoadGraph(PLAY_SCENE_BG_PATH), VGet(0.0f, 0.0f, 0.0f), 1280, 720);
	GO_BG_Image.RectInit(LoadGraph(PLAY_SCENE_GAMEOVER_BG_PATH), VGet(0.0f, 0.0f, 0.0f), 1280, 720);
	GO_TEXT_Image.RectInit(LoadGraph(PLAY_SCENE_GAMEOVER_TEXT_PATH), VGet((float)SCREEN_SIZE_X / 2.0f, (float)SCREEN_SIZE_Y / 2.0f, 0.0f), 609, 92);
	mino.Init();
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//プレイシーン通常処理
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
		bgmdata.BGMInit(BGM_PLAY);  //BGMを流す
		bgmcount++;   //増やす
	}
}

//プレイシーン描画処理
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

//プレイシーン後処理
//リトライかどうかを返す
void ScenePlay::Fin()
{
	BG_Image.RectFin();
	mino.Fin();
	bgmdata.FinBGM();
	SoundEffect::Fin();
	bgmcount = 0;     //戻す
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_RESULT;
}
