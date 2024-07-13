/*#pragma once
#include "state.h"
#include "battlestate.h"
#include "teamselectionstate.h"
#include <QStack>
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QLabel>

class MainMenuState : public State
{
    Q_OBJECT

private:

    QLabel *main_main_bg;
    QPushButton *start_button;
    QLabel *start_button_txt;

public:
    MainMenuState(QStack<State*> *states, QWidget *parent = nullptr);
    virtual ~MainMenuState();

    void updateEvent(QEvent *event) override;
    void update() override;
    void render(QPainter &painter) override;
    void endState() override;

private slots:
    void onStartButtonClicked();
};
*/
