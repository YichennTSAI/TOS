#include "setting.h"
#include "setting.h"
#include<QLabel>
#include<QIcon>
#include<qpushbutton.h>
#include"loseoutcome.h"
setting::setting()
{
    this->setFixedSize(500, 400); // 設定螢幕尺寸
    this->setWindowTitle("setting"); // 執行檔名
    QPushButton *back = new QPushButton(this);
    QPushButton *surrender = new QPushButton(this);
    back->setIcon(QIcon(":/dataset/back.png"));
    back->setIconSize(QSize(400, 200));
    back->setGeometry(200, 100, 150,100);
    back->setFlat(true); // To remove button borders
    surrender->setIcon(QIcon(":/dataset/sur.png"));
    surrender->setIconSize(QSize(400, 200));
    surrender->setGeometry(200, 200, 150, 100);
    surrender->setFlat(true); // To remove button borders
    connect( back, &QPushButton::clicked, [=]()
    {
        this->hide();
    });
    connect(surrender, &QPushButton::clicked, [=]()
    {
        loseoutcome *lout=new loseoutcome;
        lout->show();
    });
}
