#ifndef BOSS_H
#define BOSS_H

#include "enemyplane.h"

class Boss : public EnemyPlane
{
public:
    Boss(qreal angle, qreal blood, qreal w, qreal h, qreal speed, const QPixmaps &pixs, QGraphicsScene *scene, QGraphicsItem *parent = 0);
    ~Boss();
    void advance(int);
    void doCollide();
    void fall();
    void shoot();
private:
    int flag;//�������bossͼƬ�任
};

#endif // BOSS_H
