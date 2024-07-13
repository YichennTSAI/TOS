#include "loseoutcome.h"
#include<QLabel>
#include<QIcon>
#include<qpushbutton.h>
loseoutcome::loseoutcome()
{
    this->setFixedSize(500, 400); // 設定螢幕尺寸
    this->setWindowTitle("outcome"); // 執行檔名

    QLabel *loseLabel=new QLabel(this);
    loseLabel->setStyleSheet("color: black; font-size: 50px;");
    loseLabel->setText("You Lose");
    loseLabel->move(100,0);

}
