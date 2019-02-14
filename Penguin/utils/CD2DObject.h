#include "CD2D.h"
#include <vector>
#pragma once

#define DEFAULT_FPS 20


struct D2DFrame{
	ID2D1Bitmap* pBitmap;
	Shape<int> shape;
};

class CD2DObject{
public:

	CD2DObject();
	CD2DObject(int _fps);
	~CD2DObject();

	bool AddImage(CD2DImage _image, Shape<int> _shape);

	//这个函数只写在game的render函数里
	bool Render(ID2D1HwndRenderTarget* pRenderTarget, float fTime, float centre_x, float centre_y, int _width, int _height, FLOAT _alpha = 1.0F);

	bool Reset();
	
	bool Disable(); //消失

	bool IsVisible();

	void SetFps(int _fps);//设置FPS

	void SetCycles(int _cycles); //循环几次

protected:


	//实际位置= SCREEN_WIDTH/MAX_WIDTH_UNIT*相对位置
	vector<D2DFrame>	m_frames;//所有图片帧

	int					m_fps;//一秒多少帧

	int					m_cycles;//循环多少次
	int					m_cyclenow;

	float				m_lastTime;

	int					m_framenow; //现在是第几帧 结束了为-1

	bool				nextFrame();

};

