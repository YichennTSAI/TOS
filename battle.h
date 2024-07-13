#pragma once
#include <QString>
#include <QMainWindow>
#include <QTimer>
#include <QPixmap>
#include <QLabel>
#include <QProgressBar>
#include <QMediaPlayer>
#include <iostream>
#include <vector>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include "monster.h"
#include "enemy.h"

class Battle : public QWidget {
    Q_OBJECT

private:
    QLabel *battleBg, *battleUpperFrame, *battleLowerFrame, *heart, *timeLabel;
    QProgressBar *teamHpBar, *enemyHpBar1, *timeBar;
    QProgressBar *enemyHpBar2,*enemyHpBar3;
    QLabel *teamHpText, *enemyHpText1, *timeText;
    QMediaPlayer *battleBgm, *stoneClear;
    QLabel *enemyHpText2,*enemyHpText3;
    QTimer *timer,*clc1,*clc2,*clc3,*CDclc,*comboclc;
    Monster* playerTeam[6];
    Enemy*enemy1,*enemy2,*enemy3;
    int  currentTeamHp;
    int maxEnemyHp;


   QLabel *damagenum1,*damagenum2,*damagenum3,*CD,*CDs,*combotxt;

    bool *clickedPtr, *timeUpPtr, *spinningPtr;
   int maxteamhp=2000;
    int maxEnemyHp1_1=100,maxEnemyHp1_2=100,maxEnemyHp1_3=100;
        int maxEnemyHp2_1=100,maxEnemyHp2_2=300,maxEnemyHp2_3=100;
        int maxEnemyHp3_1=700;
        int normalCD=3,FireCD=5;
        int enemypower1_1=200,enemypower1_2=200,enemypower1_3=200;
        int enemypower2_1=200,enemypower2_2=200,enemypower2_3=200;
        int enemypower3_1=400;

        QWidget *windowptr;
        std::vector<int> IDnumber;
        int IDchar[5]={0,0,0,0,0};
        int CDnum12=3;
        int CDnum3=5;
        int comboo;
public:
    Battle(bool*, bool*, bool*, int[], int, int*, int*, int*,QWidget *parent);
    ~Battle();

    void updatebattle2();
    void updatebattle3();

    int round1_1damage(int,int);
    int round1_2damage(int,int);
    int round1_3damage(int,int);
    int round2_1damage(int,int);
    int round2_2damage(int,int);
    int round2_3damage(int,int);

    int round3damage(int,int);

    void showdamagenum1();
    void showdamagenum2();
    void showdamagenum3();

    void clearDamagenum1();
    void clearDamagenum2();
    void clearDamagenum3();

    void showCD();

    void showCDs();
    void clearCDs();

    void showcombo();
    void clearcombo();



    void showteamnumber1(int,QWidget *parent);
    void showteamnumber2(int,QWidget *parent);
    void showteamnumber3(int,QWidget *parent);
    void showteamnumber4(int,QWidget *parent);
    void showteamnumber5(int,QWidget *parent);
    void showteamnumber6(int,QWidget *parent);
    bool enemy1Died,enemy2Died,enemy3Died;
    void initBattleBgFrame(QWidget*parent);
    void initTeamHP(QWidget*parent);
    void initTime(QWidget*parent);
    void initEnemyHp(QWidget*parent);
    void updateTeamHP(bool*, int*, int,int,QWidget*parent);
    void updateTime(bool*);
    void drawAll();
    void playMusic();
    int  getCurrentTeamHP();
    void setCurrentTeamHP(int new_teamhp);
    bool getEnemyDied();
    int round;
    int w=0;
    QLabel *teamnumber1,*teamnumber2,*teamnumber3,*teamnumber4,*teamnumber5,*teamnumber6;
private slots:
    void onTimeout();
};
