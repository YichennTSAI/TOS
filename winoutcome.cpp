#include "winoutcome.h"
#include<QLabel>
#include<QIcon>
#include<qpushbutton.h>
winoutcome::winoutcome()
{
    this->setFixedSize(500, 400); // 設定螢幕尺寸
    this->setWindowTitle("outcome"); // 執行檔名
    QLabel *winLabel=new QLabel(this);
    winLabel->setStyleSheet("color: black; font-size: 50px;");
    winLabel->move(100,0);
    winLabel->setText("You Win");

}
