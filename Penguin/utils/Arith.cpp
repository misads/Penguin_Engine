#include "stdafx.h"
#include "Arith.h"
#include <time.h>
using namespace Arith;





fRect::fRect(fPoint fPos, fVector fSize) :m_P1(fPos),
m_P2(fPoint(fPos.x + fSize.x, fPos.y + fSize.y)), m_fWidth(fSize.x), m_fHeight(fSize.y),
m_fPCenter(fPoint(fPos.x+fSize.x*0.5f,fPos.y+fSize.y*0.5f)){

}

//left,top,right,bottom
fRect::fRect(float fp1_x, float fp1_y, float fp2_x, float fp2_y){
	fRect(fPoint(fp1_x, fp1_y), fVector(fp2_x - fp1_x, fp2_y - fp1_y));
}
fRect::fRect(const fRect &SrcRect){
	fRect(SrcRect.m_P1, fVector(SrcRect.m_fWidth, SrcRect.m_fHeight));
}

fRect::~fRect(){


}

namespace Arith{

	bool Random(float _probability){
		static bool bseed = false;
		int t;
		float fRandom;

		if (!bseed) { bseed = true; srand(time(0)); }

		fRandom = rand() / (RAND_MAX * 1.0f);

		if (fRandom < _probability)return true;
		return false;
	}
	//fp0是参考点 计算两个向量fp0fp1和fp0fp2的叉乘
	float XMult(fPoint fp1, fPoint fp2, fPoint fp0){
		return (fp1.x - fp0.x)*(fp2.y - fp0.y) - (fp2.x - fp0.x)*(fp1.y - fp0.y);
	}

	float Distance(fPoint fp1, fPoint fp2){
		return sqrt((fp1.x - fp2.x)*(fp1.x - fp2.x) + (fp1.y - fp2.y)*(fp1.y - fp2.y));
	}
	float Distance(fPoint fP, fLine fL){

		return fabs(XMult(fP, fL.a, fL.b)) / Distance(fL.a, fL.b);
	}
	//边界不算 两矩形是否碰撞
	bool Collision(fRect fR1, fRect fR2){
		bool bx = fabs((fR1.m_fWidth + fR2.m_fWidth)*0.5f) > fabs(fR1.m_fPCenter.x - fR2.m_fPCenter.x);
		bool by = fabs((fR1.m_fHeight + fR2.m_fHeight)*0.5f) > fabs(fR1.m_fPCenter.y - fR2.m_fPCenter.y);
		return (bx && by);
	}
};