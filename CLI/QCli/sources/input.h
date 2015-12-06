#ifndef INPUT_H
#define INPUT_H

#include    <QLineEdit>

class Input : public QLineEdit
{
    Q_OBJECT

public:
    Input(QWidget *parent = 0);
    ~Input();

    void        keyPressEvent(QKeyEvent *);
    void        replaceBy(QString const &);

signals:
    void        sendLine(QString const &);
    void        browseHist(QString const &, int);

public slots:
    void        replaceBySlot(QString const &);
    void        clearSlot();
};

#endif // INPUT_H
