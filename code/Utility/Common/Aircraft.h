#pragma once
#include "FlyingObject.h"

class Aircraft :public FlyingObject
{
public:
	Aircraft();
	Aircraft(char* PictureMap, int Name, double Width, double Height, double PosX, double PosY, double Speed, MOVEDIRECTION Direction, bool Exist, int Blood, int FirePower);
	Aircraft(const Aircraft& a);
	virtual ~Aircraft() {}
	/*virtual void EmitBullet() = 0;*/
protected:
	int m_Blood;
	//����������ֵ
	int m_FirePower;
	//�������ӵ�ɱ����
};