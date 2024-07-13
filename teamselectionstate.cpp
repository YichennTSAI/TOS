#include "teamselectionstate.h"

TeamSelectionState::TeamSelectionState(QWidget *parent)

{
    setWindowTitle("start");
    setFixedSize(450, 700);
    setFocusPolicy(Qt::StrongFocus);


    teamSelectionBg = new QLabel(this);
    teamSelectionBg->setPixmap(QPixmap(":/images/team_selection.jpg"));
    teamSelectionBg->setGeometry(0, 0, 800, 700);

    battleButton = new QPushButton(this);
    battleButton->setIcon(QIcon(":/images/play_button.png"));
    battleButton->setIconSize(QSize(150, 50));
    battleButton->setGeometry(50, 500, 100, 30);
    battleButton->raise(); // 确保按钮在最前面

    deleteButton = new QPushButton(this);
    deleteButton->setIcon(QIcon(":/images/clear_button.png"));
    deleteButton->setIconSize(QSize(150, 50));
    deleteButton->setGeometry(300, 500, 100, 30);
    connect(deleteButton, &QPushButton::clicked, this, [=](){
        for (int i = 0; i < 6; i++) {
            characterSelectedArray[i] = 0;
        }
        isDeleted = true;
        isClicked = false;
        click = 0;
        updateSelectedMonsters();
    });

    QFont font(":/fonts/AncientModernTales-a7Po.ttf");

    battleButtonTxt = new QLabel(this);
    battleButtonTxt->setFont(font);
    battleButtonTxt->setGeometry(battleButton->geometry().x() + 25, battleButton->geometry().y() + 25, 100, 20);

    teamSelectionTxt = new QLabel(this);
    teamSelectionTxt->setFont(font);
    teamSelectionTxt->setGeometry(15, 75, 200, 30);

    instructionTxt = new QLabel("Click the monsters to add to your team", this);
    instructionTxt->setFont(QFont(":/fonts/Montserrat-ExtraLight.ttf"));
    instructionTxt->setGeometry(15, 110, 300, 20);

    yourTeamTxt = new QLabel("Your Team", this);
    yourTeamTxt->setFont(font);
    yourTeamTxt->setGeometry(15, 470, 150, 35);

    clearTxt = new QLabel("CLEAR", this);
    clearTxt->setFont(QFont(":/fonts/Montserrat-ExtraLight.ttf"));
    clearTxt->setGeometry(330, 505, 50, 15);

    int j = -1;
    for (int i = 0; i < 9; ++i)
    {
        std::string filePathToImage = ":/images/team" + std::to_string(i+1) + ".png";
        monsterCatalogPixmaps[i] = QPixmap(filePathToImage.c_str());

        monsterCatalog[i] = new QLabel(this);
        monsterCatalog[i]->setPixmap(monsterCatalogPixmaps[i]);
        monsterSelected[i] = new QLabel(this);
        monsterSelected[i]->setPixmap(monsterCatalogPixmaps[i]);

        int x = 53 + ((i % 3) * 134);
        if (i % 3 == 0) j++;
        int y = 50 + j * 85;

        monsterCatalog[i]->setGeometry(x, y, 64, 64);
    }

    for (int i = 0; i < 6; ++i) {
        characterSelectedArray[i] = 0;
    }
    click = 0;
    isClicked = false;
    isDeleted = false;
    isEmpty = false;

    for (int i = 0; i < 9; ++i)
    {
       // std::cout << "Monster " << i + 1 << ": " << monsterName[i].toStdString() << "\n";
        //std::cout << "HP: " << monsterHp[i] << "\t Attack: " << monsterAttack[i] << "\n";
    }
   // std::cout << "\n";
}

TeamSelectionState::~TeamSelectionState()
{
    delete teamSelectionBg;
    delete battleButton;
    delete deleteButton;
    delete battleButtonTxt;
    delete teamSelectionTxt;
    delete instructionTxt;
    delete yourTeamTxt;
    delete clearTxt;

    for (int i = 0; i < 9; ++i) {
        delete monsterCatalog[i];
        delete monsterSelected[i];
    }
}

void TeamSelectionState::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (battleButton->geometry().contains(event->pos()))
        {
            qDebug() << "Battle button clicked";
            if (click >= 1 && click <= 6)
            {
                delete teamSelectionBg;
                delete battleButton;
                delete deleteButton;
                delete battleButtonTxt;
                delete teamSelectionTxt;
                delete instructionTxt;
                delete yourTeamTxt;
                delete clearTxt;

                for (int i = 0; i < 9; ++i) {
                    delete monsterCatalog[i];
                    delete monsterSelected[i];
                }
                BattleState* batt = new BattleState(characterSelectedArray, click, monsterHp, monsterAttack, kind);
                batt->show();
            }
            else
            {
                qDebug() << "You must select between 1 and 6 monsters for your team before proceeding to the battle.\n";
            }
        }
        else if (!isClicked)
        {
            if (click >= 6)
            {
                //std::cout << "You have selected 6 monsters" << std::endl;
            }
            else
            {
                for (int i = 0; i < 9; ++i)
                {
                    if (monsterCatalog[i]->geometry().contains(event->pos()))
                    {
                        if (checkSelected(i + 1))
                        {
                            if (click >= 0 && click < 6)
                            {
                                characterSelectedArray[click] = i + 1;
                                updateSelectedMonsters();
                            }
                            click++;
                            isClicked = true;
                            isDeleted = false;
                        }
                    }
                }
            }
        }

        if (deleteButton->geometry().contains(event->pos()))
        {
            for (int i = 0; i < 6; ++i)
            {
                characterSelectedArray[i] = 0;
            }
            isDeleted = true;
            isClicked = false;
            click = 0;
        }
    }
}

void TeamSelectionState::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        isClicked = false;
    }
}
/*
void TeamSelectionState::paintEvent(QPaintEvent* event)
{
    QPainter painter;

    teamSelectionBg->repaint();
    battleButton->repaint();
    deleteButton->repaint();

    for (int i = 0; i < 9; ++i)
    {
        monsterCatalog[i]->repaint();
    }

    painter.setPen(Qt::yellow);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(38, 513, 380, 86);

    battleButtonTxt->repaint();
    teamSelectionTxt->repaint();
    instructionTxt->repaint();
    yourTeamTxt->repaint();
    clearTxt->repaint();

    if (!isDeleted)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (characterSelectedArray[i] != 0)
            {
                monsterSelected[characterSelectedArray[i] - 1]->setGeometry(53 + i * 134, 515, 64, 64);
                monsterSelected[characterSelectedArray[i] - 1]->repaint();
            }
        }
    }
}
*/
void TeamSelectionState::update()
{
    // Logic to update game state if needed.
}

void TeamSelectionState::endState()
{
    // Logic to clean up state if needed.
}

bool TeamSelectionState::checkSelected(int searchKey) {
    int count = 0;
    for (int i = 0; i < 6; ++i) {
        if (characterSelectedArray[i] == searchKey) {
            count++;
        }
    }
    // 如果 count 小于等于 2（或任何您想要的重复次数），则允许选择
    return count <= 6; // 允许最多选择两个相同的怪物
}

void TeamSelectionState::updateEvent(QEvent* event) {
    // 实现函数的具体内容
    qDebug() << "TeamSelectionState::updateEvent called";
}

void TeamSelectionState::render(QPainter& painter) {
    // 实现函数的具体内容
    painter.drawText(50, 50, "Rendering in TeamSelectionState");
}
void TeamSelectionState::updateSelectedMonsters() {
    // 隱藏所有怪物
    for (int i = 0; i < 9; ++i) {
        monsterSelected[i]->hide();
    }

    // 更新選中的怪物位置和顯示
    for (int i = 0; i < 6; ++i) {
        if (characterSelectedArray[i] != 0) {
            int index = characterSelectedArray[i] - 1;
            int row = (i < 3) ? 300 : 400; // 設定行位置
            int col = 53 + ((i % 3) * 134); // 設定列位置，使用模數操作來使i介於3-5時與0-2時相同
            monsterSelected[index]->setGeometry(col, row, 64, 64);
            monsterSelected[index]->show();
        }
    }
}

