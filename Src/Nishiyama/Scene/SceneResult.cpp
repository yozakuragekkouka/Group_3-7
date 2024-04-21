#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "SceneResult.h"

#define BLACK_PATH "Data/Result/�����w�i.png"
#define SCOAE_PATH "Data/Result/�X�R�A.png"    //�X�R�A����

ResultInfo result;

//�N���A������
void SceneResult::Init()
{
	result.BlackHandle= LoadGraph(BLACK_PATH);         //���w�i������
	result.scoae = LoadGraph(SCOAE_PATH);

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_RESULT;
}

//�N���A�ʏ폈��
void SceneResult::Step()
{
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_RESULT;
	}
}

//�N���A�`�揈��
void SceneResult::Draw()
{
	//���w�i�`��
	DrawGraph(0, 0, result.BlackHandle, true);
	DrawGraph(500, 200, result.scoae, true);

}

//�N���A�㏈��
void SceneResult::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;
}
