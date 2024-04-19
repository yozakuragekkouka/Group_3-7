#include "DxLib.h"
#include "../../Common.h"
#include "Scene.h"
//2309405 �F��˒g�I

#include "SceneTitle.h"
#include "../Input/Input.h"

#define TITLE_PATH "Data/Title/�^�C�g��.png"
#define PLAY_ROGO_PATH "Data/Title/PLAY1.png"
#define PLAY_ROGO2_PATH "Data/Title/PLAY2.png"
#define PLAY_ROGO_OFF_PATH "Data/Title/PLAY OFF.png"

TitleInfo titleInfo;
PlayRogoInfo playrogoInfo;

//�^�C�g��������
void SceneTitle::Init()
{
	//�^�C�g�������֘A
	titleInfo.TitleHndl= LoadGraph(TITLE_PATH);         //�^�C�g����ʏ�����
	titleInfo.PlaySceneFlag = false;                   //PLAYSCENE�ɍs�����߂̃t���O
	titleInfo.PlaySceneStopcount = 0;                //PLAYSCENE�ɍs���܂ł̕b��
	//�v���C���S�֘A
	playrogoInfo.PlayrogoHndl = LoadGraph(PLAY_ROGO_PATH);          //PLAYROGO������
	playrogoInfo.Playrogo2Hndl = LoadGraph(PLAY_ROGO2_PATH);         //PLAYROGO2������
	playrogoInfo.PlayrogoOffHndl= LoadGraph(PLAY_ROGO_OFF_PATH);     //PLAYROGO OFF������
	playrogoInfo.Playrogocount = 0;                                  //�`�悷��b��(Playrogo)


	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_TITLE;
}

//�^�C�g���ʏ폈��
void SceneTitle::Step()
{
	if (Input::PressAnyKey())
	{
		titleInfo.PlaySceneFlag = true;    //�t���O�𗧂Ă�
	}

	if (titleInfo.PlaySceneFlag == true)
	{
		titleInfo.PlaySceneStopcount++;   //�J�E���g�𑝂₷
		if (titleInfo.PlaySceneStopcount <= 10) {
			playrogoInfo.Playrogocount = 0;    //�J�E���g��߂�
		}
		if (titleInfo.PlaySceneStopcount >= 100) {
			titleInfo.PlaySceneFlag = true;
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;
		}
	}
}

//�^�C�g���`�揈��
void SceneTitle::Draw()
{
	//�^�C�g���`��
	DrawGraph(0, 0, titleInfo.TitleHndl, true);
	//PLAYROGO�`��
	if (playrogoInfo.Playrogocount <= 49) {
		DrawGraph(500, 550, playrogoInfo.PlayrogoHndl, true);    //��ڂ�`��
	}
	if (playrogoInfo.Playrogocount >= 50) {
		DrawGraph(500, 550, playrogoInfo.Playrogo2Hndl, true);    //��ڂ�`��
	}
	if (titleInfo.PlaySceneStopcount >= 1&& titleInfo.PlaySceneStopcount <= 10) {
		DrawGraph(500, 550, playrogoInfo.PlayrogoOffHndl, true);   //�N���b�N�����`��
	}
	if (playrogoInfo.Playrogocount >= 100) {
		playrogoInfo.Playrogocount = 0;    //�J�E���g��߂�
	}
	if (titleInfo.PlaySceneFlag == false) {
		playrogoInfo.Playrogocount++;   //�J�E���g�𑝂₷
	}
}

//�^�C�g���㏈��
void SceneTitle::Fin()
{
	playrogoInfo.Playrogocount = 0;
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_PLAY;
}