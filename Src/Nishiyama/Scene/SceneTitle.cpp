#include "DxLib.h"
#include "../../Common.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "../Input/Input.h"

#define TITLE_PATH "Data/Title/�^�C�g���i���u���p�j.png"
#define PLAY_ROGO_PATH "Data/Title/PLAY�@���u��.png"
#define PLAY_ROGO2_PATH "Data/Title/PLAY�@���u��2.png"

int TitleHndl;
int PlayrogoHndl;
int Playrogo2Hndl;
int Playrogocount=0;

//�^�C�g��������
void SceneTitle::Init()
{
	TitleHndl= LoadGraph(TITLE_PATH);             //�^�C�g����ʏ�����
	PlayrogoHndl = LoadGraph(PLAY_ROGO_PATH);     //PLAYROGO������
	Playrogo2Hndl = LoadGraph(PLAY_ROGO2_PATH);     //PLAYROGO2������
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_TITLE;
}

//�^�C�g���ʏ폈��
void SceneTitle::Step()
{
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;
	}
}

//�^�C�g���`�揈��
void SceneTitle::Draw()
{
	//�^�C�g���`��
	DrawGraph(0, 0, TitleHndl, true);
	//PLAYROGO�`��
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

//�^�C�g���㏈��
void SceneTitle::Fin()
{
	Playrogocount = 0;
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_PLAY;
}