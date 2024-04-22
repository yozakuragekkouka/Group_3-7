#include "DxLib.h"
#include"Score.h"     //2309405‰F‰ê’Ë’g‹I
#include"../NumberFont/NumberFont.h"
#include"../NumberFont/NumberFontData.h"

Score score;
ScoreInfo scoreinfo;

void Score::ScoreInit()
{
	scoreinfo.numberHundle[10] = {0};
	LoadDivGraph("Data/Image/Number/number16x32_06.png", 10, 10, 1, 16, 32, scoreinfo.numberHundle);
}

void Score::Draw()
{
	int sumscore = 100;
	int count = 0;
	while (sumscore > 0) {
		int num = sumscore % 10;
		sumscore = sumscore / 10;
		DrawRotaGraph(730 - count * 16 * 4, 370, 4.0, 0.0, scoreinfo.numberHundle[num], true);
		count++;
	}
}