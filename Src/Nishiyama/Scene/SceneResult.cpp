#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "SceneResult.h"
#include"../Score/Score.h"

#define RESULT_PATH "Data/PlayScene/青背景.jpg"  //青背景
#define BLACK_PATH "Data/Result/薄黒背景.png"  //黒背景
#define SCOAE_PATH "Data/Result/スコア.png"    //スコア文字

ResultInfo result;

//クリア初期化
void SceneResult::Init()
{
	result.resultHandle= LoadGraph(RESULT_PATH);         //背景初期化
	result.BlackHandle= LoadGraph(BLACK_PATH);         //黒背景初期化
	result.scoae = LoadGraph(SCOAE_PATH);              //スコア文字初期化
	result.numberHundle[10] = { 0 };                   //スコア初期化
	LoadDivGraph("Data/Image/Number/number12x24_06.png", 10, 10, 1, 12, 24, result.numberHundle);

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
	//青背景描画
	DrawGraph(0, 0, result.resultHandle, true);
	//黒背景描画
	DrawGraph(0, 0, result.BlackHandle, true);
	//スコア文字表示
	DrawGraph(500, 200, result.scoae, true);
	//スコア描画
	int sumscore = Score::GetScore();
		int count = 0;
		while (sumscore > 0) {
			int num = sumscore % 10;
			sumscore = sumscore / 10;
			DrawRotaGraph(710 - count * 12 * 4, 370, 4.0, 0.0, result.numberHundle[num], true);
			count++;
		}

}

//クリア後処理
void SceneResult::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;
}
