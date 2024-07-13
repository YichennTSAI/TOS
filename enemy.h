#pragma once

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include<QLabel>
class Enemy : public QWidget {
    Q_OBJECT

private:
    QPixmap enemyPixmap;
    int attribute;

    int id;
QLabel *windowptr;

public:
    Enemy(  int roundnumber,QWidget* parent = nullptr);
    ~Enemy();

    void changeround(int,QWidget* parent);

     int attack;
    int calAttackToOthers();
    void receiveAttack(int damage,int k);
    void setId(int newId);
    int hp[3]={};
    int roundnumber;
    QLabel *enemyPixmapr1_1,*enemyPixmapr1_2,*enemyPixmapr1_3,*enemyPixmapr2_1,*enemyPixmapr2_2,*enemyPixmapr2_3,*enemyPixmapr3_1;
    void round1();
    void round2();
    void round3();
protected:
    //void paintEvent(QPaintEvent* event) override;
};
