#include "battlestate.h"
#include "loseoutcome.h"
BattleState::BattleState( int teamId[], int size, int* monsterHp, int* monsterAttack, int* kindArr, QWidget* parent)
 : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QVBoxLayout *layout1 = new QVBoxLayout(this);

    setWindowTitle("Battle");
    resize(540,960);
    settingbutton = new QPushButton(this);
    settingbutton->setIcon(QIcon("://dataset/setting.png"));
    settingbutton->setIconSize(QSize(100, 50));
    settingbutton->setGeometry(440, 0, 100, 30);
    connect(settingbutton, &QPushButton::clicked, [=]()
    {

        setting *set=new  setting;
        set ->show();

    });


    /* a->setPixmap(QPixmap(":/images/background.png"));
    a->setGeometry(0, 510, 540,450);
   a->hide();
*/
    grid1 = new Grid(this);
    battle = new Battle(&(grid1->clicked), &(grid1->spinning), &(grid1->time_up), teamId, size, monsterHp, monsterAttack, kindArr,this);
    layout->addWidget(grid1);
    //layout1->addWidget(enemy1);
    // 设置布局
    mainLayout->addLayout(layout);
    //mainLayout->addLayout(layout1);

    // 设置主布局为窗口的布局
    setLayout(mainLayout);
    QTimer* timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &BattleState::update);
    timer->start(16);  // Approximately 60 FPS
}

BattleState::~BattleState() {
    delete battle;
    delete grid1;
}

void BattleState::mousePressEvent(QMouseEvent* event) {

    if (event->button() == Qt::LeftButton) {//&&a->geometry().contains(event->pos()
        mouseClicked = event->pos();
        grid1-> mouseRectOffset = event->pos();
        grid1->clicked = true;
        grid1->released = false;
        grid1-> updateGrid(grid1->mouseRectOffset, event->pos());
    }
}

void BattleState::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        grid1->spinning = false;
        grid1->released = true;
        grid1-> updateGrid(grid1->mouseRectOffset, event->pos());
    }

}

void BattleState::mouseMoveEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {

        grid1-> updateGrid(grid1->mouseRectOffset, event->pos());
    }
    mouseDragging = event->pos();
}


void BattleState::update() {

    grid1->updateGrid(mouseClicked, mouseDragging);
    battle->updateTime(&(grid1->time_up));
    if (grid1->launchattack==true)
    {
        grid1->launchattack = false;
        battle->updateTeamHP(&(grid1->launchattack), grid1->numberofstonedeleted, 6,grid1->comboCount,this);
    }
        if (battle->getCurrentTeamHP() <= 0) {
        qDebug() << "YOU DIED sss";

        if(q==1){
      loseoutcome *lose=new loseoutcome;
      lose->show();
      q=0;
        }
    }
        if(battle->round==1||battle->round==2){
            if (battle->enemy1Died && battle->enemy2Died&&battle->enemy3Died)
            {
                qDebug() << "ENEMY DIED, YOU WIN";
                if(battle->round==1)
                {
                    battle->round=2;
                    battle->updatebattle2();
                    battle->enemy1Died=false;
                    battle->enemy2Died=false;
                    battle->enemy3Died=false;
                }
                else if(battle->round==2)
                {
                    battle->round=3;
                    battle->updatebattle3();
                    battle->enemy1Died=false;
                    battle->enemy2Died=false;
                    battle->enemy3Died=false;
                }
            }
            else if(battle->round==3&&battle->enemy2Died) {
                if(q==1){
                    loseoutcome *loose=new loseoutcome;
                    loose->show();
                    q=0;
                }
            }
            qDebug()<<"round"<< battle->round;
            // BattleState *batt=new  BattleState( characterSelectedArray, 3, monsterHp, monsterAttack, kind);
            //batt->show();
        }

   repaint();// Trigger a redraw of the UI
}

void BattleState::endState() {
    close();  // Close the current window
}

void BattleState::updateEvent(QEvent* event) {
    // Handle specific events if necessary
}

void BattleState::render(QPainter& painter) {
    // Implement rendering logic here
}
