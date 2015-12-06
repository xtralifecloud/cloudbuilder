/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "input.h"
#include "output.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    Output *output;
    Input *input;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(419, 247);
        MainWindow->setMaximumSize(QSize(1000000, 1000000));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMaximumSize(QSize(100000, 100000));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(9);
        centralWidget->setFont(font);
        centralWidget->setCursor(QCursor(Qt::UpArrowCursor));
        centralWidget->setLayoutDirection(Qt::RightToLeft);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        output = new Output(centralWidget);
        output->setObjectName(QStringLiteral("output"));
        output->setMinimumSize(QSize(200, 100));
        output->setMaximumSize(QSize(1000000, 1000000));
        QFont font1;
        font1.setFamily(QStringLiteral("Lucida Console"));
        font1.setPointSize(9);
        font1.setKerning(true);
        output->setFont(font1);
        output->setFocusPolicy(Qt::NoFocus);
        output->setLayoutDirection(Qt::LeftToRight);
        output->setAutoFillBackground(true);
        output->setLineWidth(0);
        output->setLineWrapMode(QTextEdit::NoWrap);
        output->setOverwriteMode(true);
        output->setAcceptRichText(true);
        output->setCursorWidth(0);
        output->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(output, 0, 0, 1, 1);

        input = new Input(centralWidget);
        input->setObjectName(QStringLiteral("input"));
        input->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(input->sizePolicy().hasHeightForWidth());
        input->setSizePolicy(sizePolicy1);
        input->setMinimumSize(QSize(400, 31));
        input->setMaximumSize(QSize(100000, 31));
        QFont font2;
        font2.setFamily(QStringLiteral("Lucida Console"));
        font2.setPointSize(9);
        input->setFont(font2);
        input->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout->addWidget(input, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CLI", 0));
        output->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lucida Console'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
