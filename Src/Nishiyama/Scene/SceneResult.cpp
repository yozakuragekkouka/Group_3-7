#include "DxLib.h"     //2309405‰F‰ê’Ë’g‹I
#include "../../Common.h"
#include "../Input/Input.h"
#include "SceneResult.h"
#include"../Score/Score.h"

#define RESULT_PATH "Data/PlayScene/Â”wŒi.jpg"  //Â”wŒi
#define BLACK_PATH "Data/Result/”–•”wŒi.png"  //•”wŒi
#define SCOAE_PATH "Data/Result/ƒXƒRƒA.png"    //ƒXƒRƒA•¶š

ResultInfo result;

//ƒNƒŠƒA‰Šú‰»
void SceneResult::Init()
{
	result.resultHandle= LoadGraph(RESULT_PATH);         //”wŒi‰Šú‰»
	result.BlackHandle= LoadGraph(BLACK_PATH);         //•”wŒi‰Šú‰»
	result.scoae = LoadGraph(SCOAE_PATH);              //ƒXƒRƒA•¶š‰Šú‰»
	result.numberHundle[10] = { 0 };                   //ƒXƒRƒA‰Šú‰»
	LoadDivGraph("Data/Image/Number/number12x24_06.png", 10, 10, 1, 12, 24, result.numberHundle);

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_RESULT;
}

//ƒNƒŠƒA’Êíˆ—
void SceneResult::Step()
{
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_RESULT;
	}
}

//ƒNƒŠƒA•`‰æˆ—
void SceneResult::Draw()
{
	//Â”wŒi•`‰æ
	DrawGraph(0, 0, result.resultHandle, true);
	//•”wŒi•`‰æ
	DrawGraph(0, 0, result.BlackHandle, true);
	//ƒXƒRƒA•¶š•\¦
	DrawGraph(500, 200, result.scoae, true);
	//ƒXƒRƒA•`‰æ
	int sumscore = Score::GetScore();
		int count = 0;
		while (sumscore > 0) {
			int num = sumscore % 10;
			sumscore = sumscore / 10;
			DrawRotaGraph(710 - count * 12 * 4, 370, 4.0, 0.0, result.numberHundle[num], true);
			count++;
		}

}

//ƒNƒŠƒAŒãˆ—
void SceneResult::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;
}
