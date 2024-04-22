#include "DxLib.h"     //2309405�F��˒g�I
#include "../../Common.h"
#include "../Input/Input.h"
#include "SceneResult.h"
#include"../Score/Score.h"

#define RESULT_PATH "Data/PlayScene/�w�i.jpg"  //�w�i
#define BLACK_PATH "Data/Result/�����w�i.png"  //���w�i
#define SCOAE_PATH "Data/Result/�X�R�A.png"    //�X�R�A����

ResultInfo result;

//�N���A������
void SceneResult::Init()
{
	result.resultHandle= LoadGraph(RESULT_PATH);         //�w�i������
	result.BlackHandle= LoadGraph(BLACK_PATH);         //���w�i������
	result.scoae = LoadGraph(SCOAE_PATH);              //�X�R�A����������
	result.numberHundle[10] = { 0 };                   //�X�R�A������
	LoadDivGraph("Data/Image/Number/number12x24_06.png", 10, 10, 1, 12, 24, result.numberHundle);

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
	//�w�i�`��
	DrawGraph(0, 0, result.resultHandle, true);
	//���w�i�`��
	DrawGraph(0, 0, result.BlackHandle, true);
	//�X�R�A�����\��
	DrawGraph(500, 200, result.scoae, true);
	//�X�R�A�`��
	int sumscore = Score::GetScore();
		int count = 0;
		while (sumscore > 0) {
			int num = sumscore % 10;
			sumscore = sumscore / 10;
			DrawRotaGraph(710 - count * 12 * 4, 370, 4.0, 0.0, result.numberHundle[num], true);
			count++;
		}

}

//�N���A�㏈��
void SceneResult::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;
}
