#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include    <QMainWindow>
#include    "input.h"
#include    "output.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    Output          *_output;
    Input           *_input;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
