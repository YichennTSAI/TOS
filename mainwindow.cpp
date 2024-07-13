#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    // 设置窗口标题和大小
    qDebug() << "Welcome To Tower of Saviors";
    this->setWindowTitle("Tower of Saviors");
       this->resize(450, 800);
    // Set up background
    main_main_bg = new QLabel(this);
    main_main_bg->setPixmap(QPixmap(":/images/main_menu.jpg"));
    main_main_bg->setScaledContents(true);
    main_main_bg->setGeometry(0, 0, 450, 800);

    // Set up start button
    start_button = new QPushButton(this);
    start_button->setIcon(QIcon(":/images/start_button1.png"));
    start_button->setIconSize(QSize(200, 50));
    start_button->setGeometry(125, 640, 200, 50);
    start_button->setFlat(true); // To remove button borders

    // Set up start button text
    start_button_txt = new QLabel("START", this);
    int id = QFontDatabase::addApplicationFont(":/fonts/AncientModernTales-a7Po.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family, 20, QFont::Bold);
    start_button_txt->setFont(font);
    start_button_txt->setStyleSheet("QLabel { color : white; }");
    start_button_txt->setGeometry(start_button->x() + 53, start_button->y() + 12, 100, 30);

    // Connect button click signal to the slot
    connect(start_button, &QPushButton::clicked, [=]()
    {
        delete main_main_bg;
        delete start_button;
        delete start_button_txt;
            TeamSelectionState *gamescene=new TeamSelectionState;
                gamescene->show();
    });

}

MainWindow::~MainWindow() {
    delete timer;
}
/*
void MainWindow::update() {
    game.run();  // 调用游戏的更新方法

    // 你可以在这里添加额外的更新逻辑，例如重绘窗口
    // update();  // 调用 Qt 的更新方法以触发窗口重绘
}
*/
