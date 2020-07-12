#pragma once
#include "FlyingObject.h"

class Bullet :public FlyingObject
{
public:
	Bullet();
	Bullet(char* PictureMap, int Name, double Width, double Height, double PosX, double PosY, double Speed, MOVEDIRECTION Direction, bool Exist, int ObjectType, bool Release, bool Display);
	Bullet(const Bullet& b);
	virtual ~Bullet() {	}
	//virtual void Collision() = 0;
	//virtual void Disappear() = 0;

	int GetObjectType();
	void SetObjectType(int ObjectType);
	bool GetRelease();
	void SetRelease(bool Release);
	bool GetDisplay();
	void SetDisplay(bool Display);
protected:
	int m_ObjectType;
	//�����ӵ��ķ���������
	bool m_Release, m_Display;
	//�Ƿ��Ѿ������ӵ����ӵ��Ƿ���ʾ
};