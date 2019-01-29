///////////////////////////
//								  //	
//		Arith 常用数学公式		  //
//		版本号:20180211			  //
//		CopyRight XY.2018-2020	  //
//								  //
///////////////////////////

#include "math.h"

#ifndef _H_ARITH_H
#define _H_ARITH_H
#pragma once

#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))


struct Point{
	Point(int nx=0, int ny=0):x(nx),y(ny){}
	int x;
	int y;
};


struct fPoint{
	fPoint(float fx = 0, float fy = 0) :x(fx), y(fy){}
	float x;
	float y;
};

struct dPoint{
	dPoint(double dx = 0, double dy = 0) :x(dx), y(dy){}
	double x;
	double y;
};

struct Vector{

	Vector(Point P) :x(P.x),y(P.y){}
	Vector(int nx=0, int ny=0) :x(nx), y(ny){}
	int x;
	int y;
};

struct fVector{
	fVector(fPoint P) :x(P.x), y(P.y){}
	fVector(float fx = 0, float fy = 0) :x(fx), y(fy){}
	float x;
	float y;
};

struct Line{
	Line(Point P1, Point P2) :a(P1), b(P2){}
	Point a;
	Point b;

};

struct fLine{
	fLine(fPoint P1,fPoint P2) :a(P1), b(P2){}
	fPoint a;
	fPoint b;

};

struct Circle{
	Circle(Point nPCenter, int nR) :p(nPCenter), r(nR){}
	Point p;
	int r;
};

struct fCircle{
	fCircle(fPoint fPCenter, float fR) :p(fPCenter), r(fR){}
	fPoint p;
	float r;
};

enum Direction
{
	nodirection=0,
	up,
	down,
	left,
	right,
	up_left,
	up_right,
	down_left,
	down_right
};




class fRect;//前向声明

namespace Arith{
/////////////////////////////////////
//												//
//												//
//												//
//        namespace Arith						//
//												//
//												//
//												//
/////////////////////////////////////
	
	bool Random(float _probability);

	float XMult(fPoint fp1, fPoint fp2, fPoint fp0);//fp0是参考点 计算两个向量fp0fp1和fp0fp2的叉乘
	float Distance(fPoint fP1,fPoint fP2);
	float Distance(fPoint fP, fLine fL);
	bool  Collision(fRect fR1,fRect fR2);

/////////////////////////////////////
//												//
//												//
//												//
//        namespace Arith						//
//												//
//												//
//												//
/////////////////////////////////////
};

class fRect{
public:
	//左上角的点，宽*高
	fRect(fPoint fPos, fVector fSize);
	//left,top,right,bottom
	fRect(float fp1_x = 0, float fp1_y = 0, float fp2_x = 0, float fp2_y = 0);
	fRect(const fRect &SrcRect);
	~fRect();

	friend bool Arith::Collision(fRect fR1, fRect fR2);
protected:
	fPoint m_P1;
	fPoint m_P2;
	float m_fWidth;
	float m_fHeight;
	fPoint m_fPCenter;

};

#endif