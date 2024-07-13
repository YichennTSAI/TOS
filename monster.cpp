#include "monster.h"
#include <QDebug>

Monster::Monster(QWidget *parent)
    : QLabel(parent)
{
}

Monster::Monster(int id, int hp, int attack, int kind, QWidget *parent)
    : QLabel(parent), hp(hp), attack(attack), kind(kind)
{
    QString kind_string_arr[6] = {"Water", "Earth", "Heart", "Dark", "Fire", "Light"};
    QString file_path_to_image = QString(":/images/%1.png").arg(id);
    monster_pixmap.load(file_path_to_image);
    setPixmap(monster_pixmap);
    setScaledContents(true);  // Scale the pixmap to the size of the label
    kind_string = kind_string_arr[kind];
    qDebug()<<"id="<<id;
    qDebug()<<"stone kind"<<kind;
}

Monster::~Monster()
{
}

int Monster::getHp()
{
    return hp;
}

void Monster::draw(QPainter &painter)
{
    painter.drawPixmap(pos(), monster_pixmap);
}

int Monster::calAttackToOthers(int attribute, int numofb)
{
    if (attribute == this->kind && numofb != 0)
    {
        int newattackmulti = 100 + (numofb - 3) * 25;
        int newattack = attack * (float)newattackmulti / 100;
        qDebug() << "Calculating for " << kind_string << " stone";
        qDebug() << "Original Player Attack:" << attack;
        qDebug() << "Damaged Done Due to Extra Stone:" << newattack;
        return newattack;
    }
    else
    {
        return 0;
    }
}
