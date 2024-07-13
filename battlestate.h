#pragma once

#include <QMainWindow>
#include <QStack>
#include <QMouseEvent>
#include <QTimer>
#include "battle.h"
#include "grid.h"
#include <QVBoxLayout>
 #include"QPushButton"
#include"winoutcome.h"
#include"setting.h"
class BattleState: public QWidget  {
    Q_OBJECT

private:
   // QStack<State*>* statesPtr;
    Battle* battle;
    Grid* grid1;
    Enemy*enemy1;
    QPoint mouseClicked, mouseDragging;
    QPushButton *settingbutton;
    int monsterHp[9] = { 90, 100, 90, 80, 100, 90, 90, 80, 100 };
    int monsterAttack[9] = {50, 40, 60, 60, 40, 50, 50, 70, 50};
    int kind[9] = { 4, 1, 5, 0, 3, 0, 1, 3, 5};
   // QLabel *start_button_txt;
   int q=1;
public:
    BattleState(int teamId[], int size, int* monsterHp, int* monsterAttack, int* kindArr, QWidget* parent = nullptr);
    ~BattleState();
    QLabel  *a;

protected:
    void mousePressEvent(QMouseEvent* event) ;
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event) ;

private slots:
    void update() ;
    void endState() ;
    void updateEvent(QEvent* event) ;
    void render(QPainter& painter) ;
};

