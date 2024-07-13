#include "enemy.h"

Enemy::Enemy(int roundnumber,QWidget* parent) : QWidget(parent) {
    // Load texture
    //windowptr=parent;
    enemyPixmapr1_1 = new QLabel(parent);
     enemyPixmapr1_2 = new QLabel(parent);
     enemyPixmapr1_3 = new QLabel(parent);
    if(roundnumber==1)
    {
        round1();
        //attribute還沒處理
         hp[0]=100;
          hp[1]=100;
           hp[2]=100;
        attack=300;//把三隻加在一起，因為CD一樣
    }

}
void Enemy::changeround(int roundnumber,QWidget* parent)
{   if(roundnumber==2)
    {
        round2();
           //attribute還沒處理
        hp[0]=100;
        hp[1]=300;
        hp[2]=100;
        attack=500;
    }
    if(roundnumber==3)
    {
        delete enemyPixmapr1_1 ;
        delete enemyPixmapr1_3;
        round3();
           //attribute還沒處理
       hp[0]=0;
        hp[1]=700;
        hp[2]=0;
        attack=700;
    }
}
Enemy::~Enemy() {
    // Destructor logic if needed
}
void Enemy::round1()
{

    enemyPixmapr1_1->setPixmap(QPixmap(":/dataset/enemy/96n.png"));
    enemyPixmapr1_1->setGeometry(50, 100, 100, 100);
    enemyPixmapr1_1->raise();


    enemyPixmapr1_2->setPixmap(QPixmap(":/dataset/enemy/98n.png"));
    enemyPixmapr1_2->setGeometry(190, 100, 100, 100);
    enemyPixmapr1_2->raise();


    enemyPixmapr1_3->setPixmap(QPixmap(":/dataset/enemy/100n.png"));
    enemyPixmapr1_3->setGeometry(330, 100, 100, 100);
    enemyPixmapr1_3->raise();
}
void Enemy::round2()
{
    enemyPixmapr1_1->setPixmap(QPixmap(":/dataset/enemy/102n.png"));

    enemyPixmapr1_2->setPixmap(QPixmap(":/dataset/enemy/267n.png"));

    enemyPixmapr1_3->setPixmap(QPixmap(":/dataset/enemy/104n.png"));
}
void Enemy::round3()
{
    enemyPixmapr1_2->setPixmap(QPixmap(":/dataset/enemy/180n.png"));
}
int Enemy::calAttackToOthers() {
    return attack;
}

void Enemy::receiveAttack(int damage,int k) {
    if(k==1)
        hp[0] -= damage;
    else  if(k==2)
        hp[1] -= damage;
    else if(k==3)
        hp[2] -= damage;

}
/*
void Enemy::setId(int newId) {
    id = newId;
    switch (id) {
        case 1:
            hp = 300;
            attribute = 0;
            attack = 20;
            break;
        // Add cases for other IDs if necessary
        default:
            break;
    }
}
*/
/*void Enemy::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, 100,100,enemyPixmap);
}
*/
