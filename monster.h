#pragma once
#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QLabel>

class Monster : public QLabel
{
    Q_OBJECT

private:
    QPixmap monster_pixmap;
    QString kind_string;

public:
    int hp, kind, attack;

    Monster(QWidget *parent = nullptr);
    Monster(int id, int hp, int attack, int kind, QWidget *parent = nullptr);
    virtual ~Monster();

    int getHp();
    void draw(QPainter &painter);
    int calAttackToOthers(int attribute, int numofb);
};
