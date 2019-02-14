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

	//�������ֻд��game��render������
	bool Render(ID2D1HwndRenderTarget* pRenderTarget, float fTime, float centre_x, float centre_y, int _width, int _height, FLOAT _alpha = 1.0F);

	bool Reset();
	
	bool Disable(); //��ʧ

	bool IsVisible();

	void SetFps(int _fps);//����FPS

	void SetCycles(int _cycles); //ѭ������

protected:


	//ʵ��λ��= SCREEN_WIDTH/MAX_WIDTH_UNIT*���λ��
	vector<D2DFrame>	m_frames;//����ͼƬ֡

	int					m_fps;//һ�����֡

	int					m_cycles;//ѭ�����ٴ�
	int					m_cyclenow;

	float				m_lastTime;

	int					m_framenow; //�����ǵڼ�֡ ������Ϊ-1

	bool				nextFrame();

};

