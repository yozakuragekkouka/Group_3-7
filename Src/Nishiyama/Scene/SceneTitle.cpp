#include "DxLib.h"
#include "../../Common.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "../Input/Input.h"

#define TITLE_PATH "Data/Title/タイトル（仮置き用）.png"
#define PLAY_ROGO_PATH "Data/Title/PLAY　仮置き.png"
#define PLAY_ROGO2_PATH "Data/Title/PLAY　仮置き2.png"

int TitleHndl;
int PlayrogoHndl;
int Playrogo2Hndl;
int Playrogocount=0;

//タイトル初期化
void SceneTitle::Init()
{
	TitleHndl= LoadGraph(TITLE_PATH);             //タイトル画面初期化
	PlayrogoHndl = LoadGraph(PLAY_ROGO_PATH);     //PLAYROGO初期化
	Playrogo2Hndl = LoadGraph(PLAY_ROGO2_PATH);     //PLAYROGO2初期化
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_TITLE;
}

//タイトル通常処理
void SceneTitle::Step()
{
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;
	}
}

//タイトル描画処理
void SceneTitle::Draw()
{
	//タイトル描画
	DrawGraph(0, 0, TitleHndl, true);
	//PLAYROGO描画
	if (Playrogocount >= 0) {
		DrawGraph(500, 550, PlayrogoHndl, true);
	}
	if (Playrogocount >= 50) {
		DrawGraph(500, 550, Playrogo2Hndl, true);
	}
	if (Playrogocount >= 100) {
		Playrogocount = 0;
	}

	Playrogocount++;
}

//タイトル後処理
void SceneTitle::Fin()
{
	Playrogocount = 0;
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_PLAY;
}