#include "battle.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

Battle::Battle(bool* clicked, bool* spinning, bool* timeUp, int teamId[], int size, int* monsterHp, int* monsterAttack, int* kindArr,QWidget *parent) {
    round=1;
    windowptr=parent;
    initBattleBgFrame(parent);
    // 根据队伍大小显示选中的怪兽
    for (int i = 0; i < size; i++) {
        if (teamId[i] == 0) {
            continue;
        }
        switch (i) {
            case 0: showteamnumber1(teamId[i], parent); break;
            case 1: showteamnumber2(teamId[i], parent); break;
            case 2: showteamnumber3(teamId[i], parent); break;
            case 3: showteamnumber4(teamId[i], parent); break;
            case 4: showteamnumber5(teamId[i], parent); break;
            case 5: showteamnumber6(teamId[i], parent); break;
        }
    }
    enemy1= new Enemy(1,parent);
    for (int i = 0; i < size; i++) {
        int hp = monsterHp[teamId[i] - 1];
        int attack = monsterAttack[teamId[i] - 1];
        int kind = kindArr[teamId[i] - 1];
        playerTeam[i] = new Monster(teamId[i], hp, attack, kind);
    }
    initTeamHP(parent);
    initEnemyHp(parent);
    initTime(parent);
    clickedPtr = clicked;
    timeUpPtr = timeUp;
    spinningPtr = spinning;
   // playMusic();
    for (int i=0;i<size;i++)
    {
        IDnumber.push_back(teamId[i]);
        if(teamId[i]==1)
        {//火屬性腳色
            IDchar[3]++;
        }
        if(teamId[i]==2||teamId[i]==7)
        {
            IDchar[1]++;
        }
        if(teamId[i]==3||teamId[i]==9)
        {
            IDchar[4]++;
        }
        if(teamId[i]==4||teamId[i]==6)
        {
            IDchar[0]++;
        }
    }
}
void Battle::updatebattle2()
{
    round=2;
    qDebug()<<"updatebattle"<<round;
    enemy1->changeround(round,windowptr);

        maxEnemyHp1_1=100;
        maxEnemyHp1_2=300;
        maxEnemyHp1_3=100;
        enemy1Died=false;
        enemy2Died=false;
        enemy3Died=false;
        enemyHpBar1->setStyleSheet(
                                    "QProgressBar::chunk {"
                                    "    background-color: #FFFF00;" // 蓝色
                                    "    width: 20px;"
                                    "}"
                                );
        enemyHpBar2->setStyleSheet(
                    "QProgressBar::chunk {"
                    "    background-color: #FFA500;" // 蓝色
                    "    width: 20px;"
                    "}"
                    );
        enemyHpBar3->setStyleSheet(
                    "QProgressBar::chunk {"
                    "    background-color: #800080;" // 蓝色
                    "    width: 20px;"
                    "}"
                    );
        enemyHpBar2->setRange(0, maxEnemyHp1_2);
        enemyHpBar2->setValue(maxEnemyHp1_2);
        enemyHpText1->setText(QString::number(enemy1->hp[0]) + "/" + QString::number(maxEnemyHp1_1));
        enemyHpBar1->setValue(enemy1->hp[0]);
        enemyHpText2->setText(QString::number(enemy1->hp[1]) + "/" + QString::number(maxEnemyHp1_2));
        enemyHpBar2->setValue(enemy1->hp[1]);
        enemyHpText3->setText(QString::number(enemy1->hp[2]) + "/" + QString::number(maxEnemyHp1_3));
        enemyHpBar3->setValue(enemy1->hp[2]);

        qDebug()<<maxEnemyHp1_2;
        qDebug()<<"enemy1->hp[0]"<<enemy1->hp[0];

}

void Battle::updatebattle3()
{
    round=3;
    qDebug()<<"updatebattle"<<round;
    enemy1->changeround(round,windowptr);

    delete enemyHpBar1;
    delete enemyHpBar3;
    delete enemyHpText1;
    delete enemyHpText3;
    enemy2Died=false;
    maxEnemyHp1_2=700;
    enemyHpBar2->setStyleSheet(
                "QProgressBar::chunk {"
                "    background-color: #FF0000;" // 红色
                "    width: 20px;"
                "}"
                );
    enemyHpBar2->setRange(0, maxEnemyHp1_2);
    enemyHpBar2->setValue(maxEnemyHp1_2);
    enemyHpText2->setText(QString::number(enemy1->hp[1]) + "/" + QString::number(maxEnemyHp1_2));
    enemyHpBar2->setValue(enemy1->hp[1]);
    qDebug()<<maxEnemyHp1_2;

}

Battle::~Battle() {
    battleBgm->stop();
    stoneClear->stop();
    for (int i = 0; i < 3; i++) {
        delete playerTeam[i];
    }
    delete battleBgm;
    delete stoneClear;
}

void Battle::initBattleBgFrame(QWidget*parent) {
    /*battleBg = new QLabel(parent);
    battleBg->setPixmap(QPixmap(":/images/battle_bg_1.png"));
    battleBg->setGeometry(0, 0, 800, 600);*/
}

void Battle::initTeamHP(QWidget*parent) {
    currentTeamHp = maxteamhp;

    heart = new QLabel(parent);
    heart->setPixmap(QPixmap(":/images/heart1.png"));
    heart->setGeometry(5, 350, 20, 20);

    teamHpBar = new QProgressBar(parent);
    teamHpBar->setGeometry(17, 355, 425, 20);
    teamHpBar->setRange(0,maxteamhp);
    teamHpBar->setValue(currentTeamHp);

    teamHpText = new QLabel(parent);
    teamHpText->setText(QString::number(currentTeamHp) + "/" + QString::number(maxteamhp));
    teamHpText->setGeometry(350, 352, 100, 20);
}

void Battle::initTime(QWidget*parent) {
    timeBar = new QProgressBar(parent);
    timeBar->setGeometry(17, 385, 425, 20);
    timeBar->setRange(0, 10);
    timeBar->setValue(10);

    timeText = new QLabel(parent);
    timeText->setText("10s/10s");
    timeText->setGeometry(350, 382, 100, 20);

    timer = new QTimer(parent);
    connect(timer, &QTimer::timeout, this, &Battle::onTimeout);
    timer->start(1000);

    clc1=new QTimer(parent);
    connect(clc1, &QTimer::timeout, this, &Battle::clearDamagenum1);
    clc2=new QTimer(parent);
    connect(clc2, &QTimer::timeout, this, &Battle::clearDamagenum2);
    clc3=new QTimer(parent);
    connect(clc3, &QTimer::timeout, this, &Battle::clearDamagenum3);
    CDclc =new QTimer(parent);
    connect(CDclc, &QTimer::timeout, this, &Battle::clearCDs);
    damagenum1=new QLabel(parent);
    damagenum2=new QLabel(parent);
    damagenum3=new QLabel(parent);
    CDs=new QLabel(parent);
    CD =new QLabel(parent);
    CD->setText("CD " + QString::number(CDnum12));
    CD->setGeometry(200, 50, 100, 20);

    comboclc=new QTimer(parent);
    connect(comboclc, &QTimer::timeout, this, &Battle::clearcombo);
    combotxt=new QLabel(parent);

}

void Battle::initEnemyHp(QWidget*parent) {
    enemyHpBar1 = new QProgressBar(parent);
    enemyHpBar1->setGeometry(50, 250, 100, 20);
    enemyHpBar1->setRange(0, maxEnemyHp1_1);
    enemyHpBar1->setValue(maxEnemyHp1_1);

    enemyHpText1 = new QLabel(parent);
    enemyHpText1->setText(QString::number(maxEnemyHp1_1) + "/" + QString::number(maxEnemyHp1_1));
    enemyHpText1->setGeometry(90, 250, 100, 20);

    enemyHpBar2 = new QProgressBar(parent);
    enemyHpBar2->setGeometry(200, 250, 100, 20);
    enemyHpBar2->setRange(0, maxEnemyHp1_2);
    enemyHpBar2->setValue(maxEnemyHp1_2);

    enemyHpText2 = new QLabel(parent);
    enemyHpText2->setText(QString::number(maxEnemyHp1_2) + "/" + QString::number(maxEnemyHp1_2));
    enemyHpText2->setGeometry(240, 250, 100, 20);

    enemyHpBar3 = new QProgressBar(parent);
    enemyHpBar3->setGeometry(360, 250, 100, 20);
    enemyHpBar3->setRange(0, maxEnemyHp1_3);
    enemyHpBar3->setValue(maxEnemyHp1_3);

    enemyHpText3 = new QLabel(parent);
    enemyHpText3->setText(QString::number(maxEnemyHp1_3) + "/" + QString::number(maxEnemyHp1_3));
    enemyHpText3->setGeometry(400, 250, 100, 20);

    enemyHpBar3->setStyleSheet(
        "QProgressBar::chunk {"
        "    background-color: #90EE90;" //淺綠
        "    width: 20px;"
        "}"
    );
    enemyHpBar2->setStyleSheet(
                "QProgressBar::chunk {"
                "    background-color: #FF0000;" // 红色
                "    width: 20px;"
                "}"
            );
    enemyHpBar1->setStyleSheet(
            "QProgressBar::chunk {"
            "    background-color: #0000FF;" // 蓝色
            "    width: 20px;"
            "}"
        );
}
void Battle::showCD()
{
    if(round==3)
    {
        CD->setText("CD " + QString::number(CDnum3));
    }
    else
    {
        CD->setText("CD " + QString::number(CDnum12));
    }


}

void Battle::updateTeamHP(bool* launchAttack, int* numOfStoneDeleted, int size,int combo,QWidget*parent) {
    comboo=0;
    comboo=combo;
    qDebug() << "updateTeamHP Water\tEarth\tHeart\tDark\tFire\tLight";
    for (int arri = 0; arri < 6; arri++) {
        qDebug() << numOfStoneDeleted[arri] << "\t";
    }


        //Attack += playerTeam[j]->calAttackToOthers(i, numOfStoneDeleted[i]);

        int totalAttack=0;
        if(round==3)
        {
            for(int i=0;i<6;i++)
            {
                if(i==2)
                {//家生命
                    totalAttack=round3damage(numOfStoneDeleted[i],i);
                    currentTeamHp=currentTeamHp+totalAttack;
                }else if(enemy1->hp[1]>0)
                {
                    totalAttack=round3damage(numOfStoneDeleted[i],i);
                    enemy1->receiveAttack(totalAttack,2);
                    if(totalAttack>0)
                   { damagenum2->setText(QString::number(totalAttack));
                    showdamagenum2();}
                }
            }
        }
        if(round==1)
        {
            for(int i=0;i<6;i++)
            {
                if(i==2)
                {//家生命
                    totalAttack=round3damage(numOfStoneDeleted[i],i);
                    currentTeamHp=currentTeamHp+totalAttack;

                }else{
                srand(time(0));
                int k=rand()%3;
                for(int i=0;i==-1;k=rand()%3)
                {//隨機選一個生命不為0的敵人
                    if(enemy1->hp[k]>0)
                    {
                        qDebug()<<"k="<<k;
                        i=-1;
                    }
                }
                if(k==0 &&enemy1->hp[k]>0)
                {//敵人是水
                    totalAttack=round1_1damage(numOfStoneDeleted[i],i);
                    enemy1->receiveAttack(totalAttack,1);
                    if(totalAttack>0)
                    {damagenum1->setText(QString::number(totalAttack));
                    showdamagenum1();}
                }
                if(k==1 &&enemy1->hp[k]>0)
                {//敵人是火
                    totalAttack=round1_2damage(numOfStoneDeleted[i],i);
                    enemy1->receiveAttack(totalAttack,2);
                    if(totalAttack>0)
                    { damagenum2->setText(QString::number(totalAttack));
                    showdamagenum2();}
                }
                if(k==2 &&enemy1->hp[k]>0)
                {//敵人是木
                    totalAttack=round1_3damage(numOfStoneDeleted[i],i);
                    enemy1->receiveAttack(totalAttack,3);
                    if(totalAttack>0)
                    {damagenum3->setText(QString::number(totalAttack));
                    showdamagenum3();}
                }

                qDebug()<<"totalAttack"<<totalAttack;
                }
            }
        }
        if(round==2)
        {
            for(int i=0;i<6;i++)
            {
                if(i==2)
                {//家生命
                    totalAttack=round3damage(numOfStoneDeleted[i],i);
                    currentTeamHp=currentTeamHp+totalAttack;

                }else{
                srand(time(0));
                int k=rand()%3;
                for(int i=0;i==-1;k=rand()%3)
                {//隨機選一個生命不為0的敵人
                    if(enemy1->hp[k]>0)
                    {
                        qDebug()<<"k="<<k;
                        i=-1;
                    }
                }
                if(k==0 &&enemy1->hp[k]>0)
                {//敵人是光
                    totalAttack=round2_1damage(numOfStoneDeleted[i],i);
                    enemy1->receiveAttack(totalAttack,1);
                    if(totalAttack>0)
                    {damagenum1->setText(QString::number(totalAttack));
                    showdamagenum1();}
                }
                if(k==1 &&enemy1->hp[k]>0)
                {//敵人是木
                    totalAttack=round2_2damage(numOfStoneDeleted[i],i);
                    enemy1->receiveAttack(totalAttack,2);
                    if(totalAttack>0)
                    {damagenum2->setText(QString::number(totalAttack));
                    showdamagenum2();}
                }
                if(k==2 &&enemy1->hp[k]>0)
                {//敵人是案
                    totalAttack=round2_3damage(numOfStoneDeleted[i],i);
                    enemy1->receiveAttack(totalAttack,3);
                    if(totalAttack>0)
                    {damagenum3->setText(QString::number(totalAttack));
                    showdamagenum3();}
                }
                }
            }
        }

           // currentTeamHp -= enemy1->attack;//攻擊用，看你要加在哪，attack是三隻加起來


    teamHpText->setText(QString::number(currentTeamHp) + "/" + QString::number(maxteamhp));
    teamHpBar->setValue(currentTeamHp);
    if(enemy1->hp[0]<=0)
        enemy1->hp[0]=0;
    if(enemy1->hp[1]<=0)
        enemy1->hp[1]=0;
    if(enemy1->hp[2]<=0)
        enemy1->hp[2]=0;

     if(round==3)
     {
         enemyHpText2->setText(QString::number(enemy1->hp[1]) + "/" + QString::number(maxEnemyHp1_2));
        enemyHpBar2->setValue(enemy1->hp[1]);
     }
     else
     {
         enemyHpText1->setText(QString::number(enemy1->hp[0]) + "/" + QString::number(maxEnemyHp1_1));
         enemyHpBar1->setValue(enemy1->hp[0]);
         enemyHpText2->setText(QString::number(enemy1->hp[1]) + "/" + QString::number(maxEnemyHp1_2));
        enemyHpBar2->setValue(enemy1->hp[1]);
        enemyHpText3->setText(QString::number(enemy1->hp[2]) + "/" + QString::number(maxEnemyHp1_3));
        enemyHpBar3->setValue(enemy1->hp[2]);

     }
     if (enemy1->hp[0] <= 0) {
                enemy1Died = true;
            }
     if (enemy1->hp[1] <= 0) {
                enemy2Died = true;
            }
     if (enemy1->hp[2] <= 0) {
                enemy3Died = true;
            }
         if(round==1||round==2)
         {
              CDnum12= CDnum12-1;
         }
         else if( round==3)
         {
              CDnum3= CDnum3-1;
         }


         if(round==1&&CDnum12==0)
         {
             currentTeamHp=currentTeamHp-600;
             CDnum12=3;
             showCDs();

         }
         if(round==2&&CDnum12==0)
         {
             currentTeamHp=currentTeamHp-600;
             CDnum12=3;
             showCDs();

         }
         if(round==3&&CDnum3==0)
         {
             currentTeamHp=currentTeamHp-400;
             CDnum12=5;
             showCDs();

         }
         showCD();
         if(comboo>0)
         {
             showcombo();
             comboo=0;
         }
}
void Battle::showcombo()
{
    combotxt->setText("Combo "+QString::number(comboo));
    combotxt->setGeometry(340, 50, 200, 20);
    combotxt->show();

           // Start the timer to clear the number after 'duration' milliseconds
    comboclc->start(3000);
}
void Battle::clearcombo()
{
    combotxt->clear();
    combotxt->hide();
}
void Battle::showCDs()
{
    CDs->setText("You are attacked!");
    CDs->setGeometry(60, 50, 200, 20);
    CDs->show();

           // Start the timer to clear the number after 'duration' milliseconds
    CDclc->start(3000);
}
void Battle::clearCDs()
{
    CDs->clear();
    CDs->hide();
}
void Battle::showdamagenum1()
{
    damagenum1->setGeometry(60, 70, 20, 20);
    damagenum1->show();

           // Start the timer to clear the number after 'duration' milliseconds
    clc1->start(3000);
}
void Battle::clearDamagenum1() {
    damagenum1->clear();
    damagenum1->hide();
}
void Battle::showdamagenum2()
{
    damagenum2->setGeometry(200, 70, 20, 20);
    damagenum2->show();

           // Start the timer to clear the number after 'duration' milliseconds
    clc2->start(3000);
}
void Battle::clearDamagenum2() {
    damagenum2->clear();
    damagenum2->hide();
}
void Battle::showdamagenum3()
{
    damagenum3->setGeometry(340, 70, 20, 20);
    damagenum3->show();

           // Start the timer to clear the number after 'duration' milliseconds
    clc3->start(3000);
}
void Battle::clearDamagenum3() {
    damagenum3->clear();
    damagenum3->hide();
}
int Battle::round3damage(int stonehurt, int stonetype)
{
    int returndamage=0;
    if(stonetype==0)
    {//水石頭
        returndamage=stonehurt*2*IDchar[0];
    }
    if(stonetype==1)
    {//木石頭
        returndamage=stonehurt*0.5*IDchar[1];
    }
    if(stonetype==2)
    {//心石頭
        returndamage=stonehurt*IDnumber.size();
    }
    if(stonetype==3)
    {//案石頭
        returndamage=stonehurt*1*IDchar[2];
    }
    if(stonetype==4)
    {//火石頭
        returndamage=stonehurt*1*IDchar[3];
    }
    if(stonetype==5)
    {//火石頭
        returndamage=stonehurt*1*IDchar[4];
    }
}
int Battle::round1_1damage(int stonehurt, int stonetype)
{
   qDebug()<<"1 stonehurt="<<stonehurt<<"stonetype:"<<stonetype;

    int returndamage=0;
    if(stonetype==0)
    {//水石頭
        returndamage=stonehurt*1*IDchar[0];
    }
    if(stonetype==1)
    {//木石頭
        returndamage=stonehurt*0.5*IDchar[1];
    }
    if(stonetype==2)
    {//心石頭
        returndamage=stonehurt*IDnumber.size();
    }
    if(stonetype==3)
    {//案石頭
        returndamage=stonehurt*1*IDchar[2];
    }
    if(stonetype==4)
    {//火石頭
        returndamage=stonehurt*2*IDchar[3];
    }
    if(stonetype==5)
    {//光石頭
        returndamage=stonehurt*1*IDchar[4];
    }

}
int Battle::round1_2damage(int stonehurt, int stonetype)
{
    qDebug()<<"2 stonehurt="<<stonehurt<<"stonetype:"<<stonetype;
    int returndamage=0;
    if(stonetype==0)
    {//水石頭
        returndamage=stonehurt*2*IDchar[0];
    }
    if(stonetype==1)
    {//木石頭
        returndamage=stonehurt*0.5*IDchar[1];
    }
    if(stonetype==2)
    {//心石頭
        returndamage=stonehurt*IDnumber.size();
    }
    if(stonetype==3)
    {//案石頭
        returndamage=stonehurt*1*IDchar[2];
    }
    if(stonetype==4)
    {//火石頭
        returndamage=stonehurt*1*IDchar[3];
    }
    if(stonetype==5)
    {//光石頭
        returndamage=stonehurt*1*IDchar[4];
    }

}
int Battle::round1_3damage(int stonehurt, int stonetype)
{
  qDebug()<<"3 stonehurt="<<stonehurt<<"stonetype:"<<stonetype;

    int returndamage=0;
    if(stonetype==0)
    {//水石頭
        returndamage=stonehurt*0.5*IDchar[0];
    }
    if(stonetype==1)
    {//木石頭
        returndamage=stonehurt*1*IDchar[1];
    }
    if(stonetype==2)
    {//心石頭
        returndamage=stonehurt*IDnumber.size();
    }
    if(stonetype==3)
    {//案石頭
        returndamage=stonehurt*1*IDchar[2];
    }
    if(stonetype==4)
    {//火石頭
        returndamage=stonehurt*2*IDchar[3];
    }
    if(stonetype==5)
    {//光石頭
        returndamage=stonehurt*1*IDchar[4];
    }

}
int Battle::round2_1damage(int stonehurt, int stonetype)
{
    int returndamage=0;
    if(stonetype==0)
    {//水石頭
        returndamage=stonehurt*1*IDchar[0];
    }
    if(stonetype==1)
    {//木石頭
        returndamage=stonehurt*1*IDchar[1];
    }
    if(stonetype==2)
    {//心石頭
        returndamage=stonehurt*IDnumber.size();
    }
    if(stonetype==3)
    {//案石頭
        returndamage=stonehurt*2*IDchar[2];
    }
    if(stonetype==4)
    {//火石頭
        returndamage=stonehurt*1*IDchar[3];
    }
    if(stonetype==5)
    {//光石頭
        returndamage=stonehurt*1*IDchar[4];
    }

}
int Battle::round2_2damage(int stonehurt, int stonetype)
{
    int returndamage=0;
    if(stonetype==0)
    {//水石頭
        returndamage=stonehurt*2*IDchar[0];
    }
    if(stonetype==1)
    {//木石頭
        returndamage=stonehurt*1*IDchar[1];
    }
    if(stonetype==2)
    {//心石頭
        returndamage=stonehurt*IDnumber.size();
    }
    if(stonetype==3)
    {//案石頭
        returndamage=stonehurt*1*IDchar[2];
    }
    if(stonetype==4)
    {//火石頭
        returndamage=stonehurt*0.5*IDchar[3];
    }
    if(stonetype==5)
    {//光石頭
        returndamage=stonehurt*1*IDchar[4];
    }

}
int Battle::round2_3damage(int stonehurt, int stonetype)
{
    int returndamage=0;
    if(stonetype==0)
    {//水石頭
        returndamage=stonehurt*1*IDchar[0];
    }
    if(stonetype==1)
    {//木石頭
        returndamage=stonehurt*1*IDchar[1];
    }
    if(stonetype==2)
    {//心石頭
        returndamage=stonehurt*IDnumber.size();
    }
    if(stonetype==3)
    {//案石頭
        returndamage=stonehurt*1*IDchar[2];
    }
    if(stonetype==4)
    {//火石頭
        returndamage=stonehurt*1*IDchar[3];
    }
    if(stonetype==5)
    {//光石頭
        returndamage=stonehurt*2*IDchar[4];
    }

}
void Battle::showteamnumber1(int number1,QWidget *parent)
{
    qDebug() <<"showteamnumber1 ";
    teamnumber1 = new QLabel(parent);
    for(int i=0;i<9;i++)
    {
        if(number1==i+1)
        {
            QString imagePath1 = QString(":/images/%1.png").arg(number1);
            teamnumber1->setPixmap(QPixmap(imagePath1));
        }
    }
    teamnumber1->setGeometry(0, 435, 80, 80);
    teamnumber1->raise();
}
void Battle::showteamnumber2(int number2,QWidget *parent)
{
    qDebug() <<"showteamnumber2 ";
    teamnumber2 = new QLabel(parent);
    for(int i=0;i<9;i++)
    {
        if(number2==i+1)
        {
            QString imagePath2 = QString(":/images/%1.png").arg(number2);
            teamnumber2->setPixmap(QPixmap(imagePath2));
        }
    }
    teamnumber2->setGeometry(90, 435, 80, 80);
    teamnumber2->raise();
}
void Battle::showteamnumber3(int number3,QWidget *parent)
{
    qDebug() <<"showteamnumber3 ";
    teamnumber3 = new QLabel(parent);
    for(int i=0;i<9;i++)
    {
        if(number3==i+1)
        {
            QString imagePath3 = QString(":/images/%1.png").arg(number3);
            teamnumber3->setPixmap(QPixmap(imagePath3));
        }
    }
    teamnumber3->setGeometry(180, 435, 80, 80);
    teamnumber3->raise();
}

void Battle::showteamnumber4(int number4, QWidget *parent)
{
    qDebug() << "showteamnumber4 ";
    teamnumber4 = new QLabel(parent);
    for(int i = 0; i < 9; i++)
    {
        if(number4 == i + 1)
        {
            QString imagePath4 = QString(":/images/%1.png").arg(number4);
            teamnumber4->setPixmap(QPixmap(imagePath4));
        }
    }
    teamnumber4->setGeometry(270, 435, 80, 80);
    teamnumber4->raise();
}

void Battle::showteamnumber5(int number5, QWidget *parent)
{
    qDebug() << "showteamnumber5 ";
    teamnumber5 = new QLabel(parent);
    for(int i = 0; i < 9; i++)
    {
        if(number5 == i + 1)
        {
            QString imagePath5 = QString(":/images/%1.png").arg(number5);
            teamnumber5->setPixmap(QPixmap(imagePath5));
        }
    }
    teamnumber5->setGeometry(360, 435, 80, 80);
    teamnumber5->raise();
}

void Battle::showteamnumber6(int number6, QWidget *parent)
{
    qDebug() << "showteamnumber6 ";
    teamnumber6 = new QLabel(parent);
    for(int i = 0; i < 9; i++)
    {
        if(number6 == i + 1)
        {
            QString imagePath6 = QString(":/images/%1.png").arg(number6);
            teamnumber6->setPixmap(QPixmap(imagePath6));
        }
    }
    teamnumber6->setGeometry(450, 435, 80, 80);
    teamnumber6->raise();
}
void Battle::updateTime(bool* timeUp) {
    if (timeBar->value()>10 )
    {
        timer->start(10000);
        timeBar->setValue(10);
        *timeUp = true;
        qDebug()<<"timeup111111111111111111";
    }
    else if (*clickedPtr && *spinningPtr) {
        timeBar->setValue(10 - timer->remainingTime() / 1000);
        qDebug()<<timeBar->value()<<"kkkkkkkkkkkkkkkkk";
    } else {

        {



        }
        timer->start(10000);
        timeBar->setValue(10);
        qDebug()<<"timeup1";

    }

}

void Battle::drawAll() {
    // This method can be omitted in Qt as the components are automatically rendered
}
/*
void Battle::playMusic() {
    battleBgm = new QMediaPlayer(this);
    battleBgm->setMedia(QUrl::fromLocalFile(":/music/battle.wav"));
    battleBgm->play();

    stoneClear = new QMediaPlayer(this);
    stoneClear->setMedia(QUrl::fromLocalFile(":/music/stone_clear.wav"));
}
*/
void Battle::onTimeout() {

    if (*clickedPtr && *spinningPtr) {
        timeBar->setValue(timeBar->value() - 1);
    } else {
        timer->start(10000);
        timeBar->setValue(10);
    }
}

int  Battle::getCurrentTeamHP()
{
    return currentTeamHp;
}
/*
void Battle::setCurrentTeamHP(int new_teamhp)
{
    if (new_teamhp < 0)
        currentTeamHp = 0;
    else
        currentTeamHp = new_teamhp;
}*/
/*
bool Battle::getEnemyDied()
{
    return enemy1Died;
}
*/
