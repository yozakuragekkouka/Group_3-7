#include "DxLib.h"
#include "../../Common.h"
#include "Scene.h"
//2309405 宇賀塚暖紀

#include "SceneTitle.h"
#include "../Input/Input.h"

#define TITLE_PATH "Data/Title/タイトル.png"
#define PLAY_ROGO_PATH "Data/Title/PLAY1.png"
#define PLAY_ROGO2_PATH "Data/Title/PLAY2.png"
#define PLAY_ROGO_OFF_PATH "Data/Title/PLAY OFF.png"

TitleInfo titleInfo;
PlayRogoInfo playrogoInfo;

//タイトル初期化
void SceneTitle::Init()
{
	//タイトル処理関連
	titleInfo.TitleHndl= LoadGraph(TITLE_PATH);         //タイトル画面初期化
	titleInfo.PlaySceneFlag = false;                   //PLAYSCENEに行くためのフラグ
	titleInfo.PlaySceneStopcount = 0;                //PLAYSCENEに行くまでの秒数
	//プレイロゴ関連
	playrogoInfo.PlayrogoHndl = LoadGraph(PLAY_ROGO_PATH);          //PLAYROGO初期化
	playrogoInfo.Playrogo2Hndl = LoadGraph(PLAY_ROGO2_PATH);         //PLAYROGO2初期化
	playrogoInfo.PlayrogoOffHndl= LoadGraph(PLAY_ROGO_OFF_PATH);     //PLAYROGO OFF初期化
	playrogoInfo.Playrogocount = 0;                                  //描画する秒数(Playrogo)


	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_TITLE;
}

//タイトル通常処理
void SceneTitle::Step()
{
	if (Input::PressAnyKey())
	{
		titleInfo.PlaySceneFlag = true;    //フラグを立てる
	}

	if (titleInfo.PlaySceneFlag == true)
	{
		titleInfo.PlaySceneStopcount++;   //カウントを増やす
		if (titleInfo.PlaySceneStopcount <= 10) {
			playrogoInfo.Playrogocount = 0;    //カウントを戻す
		}
		if (titleInfo.PlaySceneStopcount >= 100) {
			titleInfo.PlaySceneFlag = true;
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;
		}
	}
}

//タイトル描画処理
void SceneTitle::Draw()
{
	//タイトル描画
	DrawGraph(0, 0, titleInfo.TitleHndl, true);
	//PLAYROGO描画
	if (playrogoInfo.Playrogocount <= 49) {
		DrawGraph(500, 550, playrogoInfo.PlayrogoHndl, true);    //一つ目を描画
	}
	if (playrogoInfo.Playrogocount >= 50) {
		DrawGraph(500, 550, playrogoInfo.Playrogo2Hndl, true);    //二つ目を描画
	}
	if (titleInfo.PlaySceneStopcount >= 1&& titleInfo.PlaySceneStopcount <= 10) {
		DrawGraph(500, 550, playrogoInfo.PlayrogoOffHndl, true);   //クリック処理描画
	}
	if (playrogoInfo.Playrogocount >= 100) {
		playrogoInfo.Playrogocount = 0;    //カウントを戻す
	}
	if (titleInfo.PlaySceneFlag == false) {
		playrogoInfo.Playrogocount++;   //カウントを増やす
	}
}

//タイトル後処理
void SceneTitle::Fin()
{
	playrogoInfo.Playrogocount = 0;
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_PLAY;
}