#ifndef FLIGHTVEHICLE_H
#define FLIGHTVEHICLE_H

#include "flyer.h"
#include "unflyer.h"

class FlightVehicle : public Flyer
{
    Q_OBJECT
public:
    FlightVehicle(qreal blood, qreal w, qreal h, qreal speed, const QPixmaps &pixs, QGraphicsScene *scene, QGraphicsItem *parent = 0)
        :Flyer(w, h, speed, pixs, scene, parent), m_blood(blood) {

    }
    virtual ~FlightVehicle() {}
    virtual void strike() = 0;
    virtual void shoot() = 0;
protected:
    qreal m_blood;//Ѫ��
signals:
    //��������ķ�����Ϣ������ʾ�� ע�͵���һ�����
    void sig_score(int score);
    //void sig_blood(int blood);
    //void sig_bomb(int bomb);
    void sig_fall();
};

#endif // FLIGHTVEHICLE_H
