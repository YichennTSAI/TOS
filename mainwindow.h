#pragma once

#include <QMainWindow>
#include <QTimer>
//#include "Game.h"  // 包含你的 Game 类的头文件
#include "battlestate.h"
#include "teamselectionstate.h"
#include <QStack>
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QFontDatabase>
#include <QDebug>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    QLabel *main_main_bg;
    QPushButton *start_button;
    QLabel *start_button_txt;

private slots:
  //  void update();  // 用于更新游戏状态的槽函数

private:  // 你的游戏对象
    QTimer* timer;  // 用于驱动游戏更新的定时器
};
