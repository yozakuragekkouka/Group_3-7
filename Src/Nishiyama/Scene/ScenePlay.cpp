#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"
#include "../Score/Score.h"

//プレイシーン初期化
void ScenePlay::Init()
{
	Score::Init();

	mino.Init();
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//プレイシーン通常処理
void ScenePlay::Step()
{
	mino.Step();
	if (Input::IsKeyPush(KEY_INPUT_RETURN))
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
	}
}

//プレイシーン描画処理
void ScenePlay::Draw()
{
	mino.PredictionDraw();
	mino.FieldDraw();

	mino.NextDraw();
}

//プレイシーン後処理
//リトライかどうかを返す
void ScenePlay::Fin()
{
	mino.Fin();
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_RESULT;
}
