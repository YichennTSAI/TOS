#include "grid.h"
#include <cstdlib>
#include <ctime>
#include <QDebug>

Grid::Grid(QWidget *parent) : QWidget(parent) {
    srand(time(0));

    // Load Background and Runestones textures
    bgPixmap.load(":/images/background.png");
    runestonesPixmap.load(":/images/diamonds.png");

    // Set up Offset for stones to move them down
    gridOffset = QPoint(0, 510);

    // Set up all runestones
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            grid[i][j].kind = rand() % 6;
            grid[i][j].col = j;
            grid[i][j].row = i;
            grid[i][j].x = j * ts;
            grid[i][j].y = i * ts;
        }
    }

    while (checkMatch()) {
        deleteMatchedAndCollectNumber();
        dropGems();
        fillEmptyGrid();
    }

    for (int i = 0; i < 6; i++) {
        numberofstonedeleted[i] = 0;
    }
}

Grid::~Grid() {}
//改過
void Grid::deleteMatchedAndCollectNumber() {
    bool matched = false;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
           {
                grid[i][j].alpha = 0;
                numberofstonedeleted[grid[i][j].kind]++;
                 matched = true;
            }
        }
    }//combo數

}
void Grid::dropGems() {
    for (int j = 0; j < 6; j++) {
        int emptyCount = 0;
        for (int i = 4; i >= 0; i--) {
            if (grid[i][j].match) {
                emptyCount++;
            } else if (emptyCount > 0) {
                grid[i + emptyCount][j].kind = grid[i][j].kind;
                grid[i + emptyCount][j].alpha = grid[i][j].alpha;
                grid[i][j].match = true;  // 将空位置标记为匹配
            }
        }
        // 填补空位的新石头
        for (int i = 0; i < emptyCount; i++) {
            grid[i][j].kind = rand() % 6;
            grid[i][j].alpha = 255;
            grid[i][j].match = 0;
        }
    }
}
bool Grid::checkMatch() {
    bool matched = false;
    // Check tiles vertically
    for (int j = 0; j < 6; j++) { // for every column
        for (int i = 0; i < 3; i++) { // check till last three stones
            if (!grid[i][j].match) {
                if (grid[i][j].kind == grid[i + 1][j].kind && grid[i][j].kind == grid[i + 2][j].kind) {
                    for (int z = i; z < i + 3; z++) {
                        qDebug() << "Stone (" << j << "," << z << ") is matched";
                        grid[z][j].match = 1;
                    }
                    matched = true;
                    if (i != 2) {
                        int n = i + 3;
                        while (grid[i][j].kind == grid[n][j].kind && n != 5) {
                            qDebug() << "Stone (" << j << "," << n << ") is matched";
                            grid[n][j].match = 1;
                            n++;
                        }
                    }
                }
            }
        }
    }
    // Check tiles horizontally
    for (int i = 0; i < 5; i++) { // check every row
        for (int j = 0; j < 4; j++) { // check till stone 3
            if (!grid[i][j].match) {
                if (grid[i][j].kind == grid[i][j + 1].kind && grid[i][j + 1].kind == grid[i][j + 2].kind) {
                    for (int z = j; z < j + 3; z++) {
                        qDebug() << "Stone (" << z << "," << i << ") is matched";
                        grid[i][z].match = 1;
                    }
                    matched = true;
                    if (j != 3) {
                        int n = j + 3;
                        while (grid[i][j].kind == grid[i][n].kind && n != 6) {
                            qDebug() << "Stone (" << n << "," << i << ") is matched";
                            grid[i][n].match = 1;
                            n++;
                        }
                    }
                }
            }
        }
    }
    return matched;
}

void Grid::fillEmptyGrid() {
    for (int j = 0; j < 6; j++) {
        int newStonesCount = 0;
        for (int i = 4; i >= 0; i--) {
            if (grid[i][j].match) {
                grid[i][j].kind = rand() % 6;
                grid[i][j].alpha = 255;
                grid[i][j].match = 0;
                grid[i][j].y = 510 - ((4 - newStonesCount) + 1) * ts;  // 将新石头放置在顶部以模拟从顶部掉落
                newStonesCount++;
            }
        }
    }
}





void Grid::updateGrid(QPoint mouse_clicked, QPoint mouse_dragging) {
    if ((clicked && released) || time_up) {
        int i = 1;
        while (checkMatch()) {
            deleteMatchedAndCollectNumber();
            dropGems();  // 掉落石头
            fillEmptyGrid();  // 从顶部生成新石头
            qDebug() << "Dissolved " << i << " time";
            comboCount = i;
            qDebug() << "comboCount= " << comboCount << " time";
            i++;
            qDebug() << "Water\tEarth\tHeart\tDark\tFire\tLight";
            for (int arri = 0; arri < 6; arri++) {
                qDebug() << numberofstonedeleted[arri] << "\t";
            }
            qDebug() << "\n\n";
        }

        for (int i = 0; i < 6; i++) {
            numberofstonedeleted[i] = numberofstonedeleted[i] * comboCount;
        }
        launchattack = true;
        clicked = false;
        released = false;
        time_up = false;
    } else if (clicked && spinning) {
        x = (mouse_dragging.x() - gridOffset.x()) / ts;
        y = (mouse_dragging.y() - gridOffset.y()) / ts;
        // 如果移动到另一个网格
        if (x0 >= 0 && x0 <= 5 && y0 >= 0 && y0 <= 4) {
            if (x >= 0 && x <= 5 && y >= 0 && y <= 4) {
                if (x != x0 || y != y0) {
                    swapStone(grid[y][x], grid[y0][x0]);
                    x0 = x;
                    y0 = y;
                }
            }
        }
    } else if (clicked && !spinning) {
        x0 = (mouse_clicked.x() - gridOffset.x()) / ts;
        y0 = (mouse_clicked.y() - gridOffset.y()) / ts;
        if (x0 >= 0 && x0 <= 5 && y0 >= 0 && y0 <= 4)
            spinning = true;
    }
}


void Grid::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // 绘制背景

    // 绘制宝石网格
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            Piece &p = grid[i][j];
            QRect sourceRect(p.kind * ts, 0, ts, ts);
            QRect targetRect(p.x, p.y, ts, ts);  // 访问 x 和 y 作为成员变量
            painter.drawPixmap(targetRect, runestonesPixmap, sourceRect);

            // 动画掉落的石头
            if (p.y < 510 + i * ts) {
                p.y += 1;  // 调整这个值以控制掉落速度
                if (p.y > 510 + i * ts) {
                    p.y = 510 + i * ts;  // 确保石头停在正确的位置
                }
                update();  // 请求重新绘制以动画掉落的石头
            }
        }
    }
}
/*
void Grid::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        clicked = true;
        released = false;
        mouseRectOffset = event->pos();
    }
}

void Grid::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        spinning = false;
        released = true;
        updateGrid(mouseRectOffset, event->pos());
    }
}

void Grid::mouseMoveEvent(QMouseEvent *event) {
    if (clicked && spinning) {
        updateGrid(mouseRectOffset, event->pos());
    }
}*/

void Grid::swapStone(Piece &stone1, Piece &stone2) {
    std::swap(stone1.kind, stone2.kind);
}
