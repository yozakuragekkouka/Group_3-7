#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "SceneResult.h"

#define BLACK_PATH "Data/Result/薄黒背景.png"
#define SCOAE_PATH "Data/Result/スコア.png"    //スコア文字

ResultInfo result;

//クリア初期化
void SceneResult::Init()
{
	result.BlackHandle= LoadGraph(BLACK_PATH);         //黒背景初期化
	result.scoae = LoadGraph(SCOAE_PATH);

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_RESULT;
}

//クリア通常処理
void SceneResult::Step()
{
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_RESULT;
	}
}

//クリア描画処理
void SceneResult::Draw()
{
	//黒背景描画
	DrawGraph(0, 0, result.BlackHandle, true);
	DrawGraph(500, 200, result.scoae, true);

}

//クリア後処理
void SceneResult::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;
}
