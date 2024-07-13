#pragma once

#include <QWidget>
#include <QStack>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QPainter>
#include <QMouseEvent>
#include <QRect>

//#include "state.h"
#include "battlestate.h"

class TeamSelectionState :public QWidget
{
    Q_OBJECT

private:

    QLabel* teamSelectionBg;
    QPushButton* battleButton;
    QPushButton* deleteButton;

    QPixmap monsterCatalogPixmaps[9];
    QLabel* monsterCatalog[9];
    QLabel* monsterSelected[9];

    QString monsterName[9];
    int monsterHp[9] = { 90, 100, 90, 80, 100, 90, 90, 80, 100 };
    int monsterAttack[9] = {50, 40, 60, 60, 40, 50, 50, 70, 50};
    int kind[9] = { 4, 1, 5, 0, 3, 0, 1, 3, 5};

    QLabel* battleButtonTxt;
    QLabel* teamSelectionTxt;
    QLabel* instructionTxt;
    QLabel* yourTeamTxt;
    QLabel* clearTxt;

    int characterSelectedArray[6];
    int click;
    bool isClicked;
    bool isDeleted;
    bool isEmpty;

public:
    TeamSelectionState( QWidget *parent = nullptr);
        ~TeamSelectionState();
    void updateSelectedMonsters();

    void endState() ;
        void updateEvent(QEvent* event) ;
        void update();
        void render(QPainter& painter) ;
    bool checkSelected(int);

protected:
   ///* void paintEvent(QPaintEvent* event) ;
    void mousePressEvent(QMouseEvent* event) ;
    void mouseReleaseEvent(QMouseEvent* event) ;
};
