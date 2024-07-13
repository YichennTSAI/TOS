#pragma once

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>

class Grid : public QWidget {
    Q_OBJECT

public:
    struct Piece {
        int x = 0, y = 0, col = 0, row = 0, kind = 0, match = 0, alpha = 255;
    } grid[10][10];

    QPixmap bgPixmap;
    QPixmap runestonesPixmap;
    QPoint gridOffset;
    QPoint mouseRectOffset;
    int ts = 90;
    int x0, y0;
    int x, y;

public:
    int comboCount;
    bool spinning = false;
    bool clicked = false, released = false;
    bool time_up = false;
    bool launchattack = false;
void dropGems() ;
    int numberofstonedeleted[6] = {};

    Grid(QWidget *parent = nullptr);
    virtual ~Grid();
    void deleteMatchedAndCollectNumber();
    bool checkMatch();
    void fillEmptyGrid();
    void updateGrid(QPoint, QPoint);

protected:
    void paintEvent(QPaintEvent *event) override;
   /* void mousePressEvent(QMouseEvent *event) ;
    void mouseReleaseEvent(QMouseEvent *event) ;
    void mouseMoveEvent(QMouseEvent *event) ;
*/
private:
    void swapStone(Piece &, Piece &);
};
