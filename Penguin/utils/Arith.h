///////////////////////////////////
//								 //	
//		Arith 常用类型和公式	 //
//		版本号:20190214			 //
//		http://www.xyu.ink		 //
//		使用请保留出处信息		 //
//								 //
///////////////////////////////////

#include "math.h"

#pragma once

#ifndef max
	#define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
	#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

template<typename  T>
struct Point{

	Point(T _x = 0, T _y = 0) :x(_x), y(_y){}
	T x;
	T y;

};


//Shape和Point的定义是相同的，只是变量名不同
template<typename  T>
struct Shape{

	Shape(T _width = 0, T _height = 0) :width(_width), height(_height){}
	T width;
	T height;

};


template<typename  T>
struct Vector{

	Vector(T _x = 0, T _y = 0, T _length = 0) :x(_x), y(_y), length(_length){}
	T x;
	T y;
	T _length;

};


template<typename  T>
struct Line{
	Line(T a_x, T a_y, T b_x, T b_y) :a(Point(a_x, a_y), b(Point(b_x, b_y))){}
	Line(Point _a, Point _b) :a(_a), b(_b){}
	Point a;
	Point b;

};


template<typename  T>
struct Circle{
	Circle(T c_x, T c_y, T _r) :p(Point(c_x, c_y)), r(_r){}
	Circle(Point _c, T _r) :p(_c), r(_r){}
	Point c;
	T r;
};

enum Direction{
	null = 0,
	up,
	down,
	left,
	right,
	up_left,
	up_right,
	down_left,
	down_right
};



/*
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
*/