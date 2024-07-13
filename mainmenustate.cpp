/*#include "mainmenustate.h"
#include <QVBoxLayout>
#include <QPixmap>
#include <QFontDatabase>
#include <QDebug>

MainMenuState::MainMenuState(QStack<State*> *states_stack_ptr, QWidget *parent)
    : State(states_stack_ptr)
{
    statesptr = states_stack_ptr;

}

MainMenuState::~MainMenuState()
{
    delete main_main_bg;
    delete start_button;
    delete start_button_txt;
}*/
/*
void MainMenuState::updateEvent(QEvent *event)
{
    // No event handling needed as we use QPushButton signal-slot mechanism
}

void MainMenuState::update()
{
    // No update logic needed for the main menu state
}

void MainMenuState::render(QPainter &painter)
{
    // Rendering is handled by Qt widgets
}

void MainMenuState::endState()
{
    // Clean up when state ends
}

void MainMenuState::onStartButtonClicked()
{
    statesptr->push(new TeamSelectionState(statesptr));
}
*/
