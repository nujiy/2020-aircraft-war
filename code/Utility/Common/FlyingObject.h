#pragma once
#include "Global.h"
#include <vector>

class FlyingObject
{
public:
	FlyingObject();
	FlyingObject(char* PictureMap, int Name, double Width, double Height, double PosX, double PosY, double Speed, MOVEDIRECTION Direction, bool Exist);
	FlyingObject(const FlyingObject& fo);
	virtual ~FlyingObject() {}
	
	//virtual void Collision() = 0;
	//virtual void Disappear() = 0;

	void SetName(int Name);
	int GetName();
	void SetPictureMap(char* PictureMap, int Choice);
	std::vector<char*> GetPictureMap();
	void SetSize(double Width, double Height);
	double GetWidth();
	double GetHeight();
	void SetPosition(double x, double y);
	double GetPositionX();
	double GetPositionY();
	void SetSpeed(double Speed);
	double GetSpeed();
	void SetDirection(MOVEDIRECTION Direction);
	MOVEDIRECTION GetDirection();
	void SetExist(bool Exist);
	bool GetExist();
	
protected:
	std::vector<char*> m_PictureMap;
	//����ͼ��������ʾ����
	int m_Name;
	//�������ƣ����ڱ�ʶ�������ͣ���ң�Npc���ӵ���
	double m_Width, m_Height;
	//�����С��������ײ��⣬�������ʾ��������
	double m_PosX, m_PosY;
	//����λ��(x,y)����
	double m_Speed;
	//�����ƶ��ٶ�
	MOVEDIRECTION m_Direction;
	//�����ƶ�����
	bool m_Exist;
	//�����Ƿ���ڡ����磬�ɻ�����ֵ�Ƿ����0�� �ӵ��Ƿ����Ŀ��
};