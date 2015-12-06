#ifndef OUTPUT_H
#define OUTPUT_H

#include    <QThread>
#include    <QTextEdit>
#include    <QElapsedTimer>

#include    "cli.h"
#include    "listener.h"

class MyCLI;

class Output : public QTextEdit
{
    Q_OBJECT

    QWidget         *_parent;
    QTextCursor     *_cursor;
    QTextCharFormat *_format;

    std::list<QString>              _history;
    std::list<QString>::iterator    _histIt;
    QString                         _currentLine;
    bool                            _onCurrentLine;

    QElapsedTimer                   _timer;

    MyCLI                           *_gCLI;

    QThread         *_thread;
    Listener        *_listener;
    int             _dotsCounter;
    bool            _clearDots;

public:
    bool                    _gReady;

public:
    Output(QWidget *parent = 0);
    ~Output();

    void    printLine(QString const &, CLI::typelog = CLI::kLOG);
    void    done();

private:
    void    initDisplay();
    void    launchThread();
    void    clearDots();
    void    outputLine(QString const &, CLI::typelog);

signals:
    void    replaceBy(QString const &);
    void    clearSig();

public slots:
    void    getLineSlot(QString const &);
    void    browseHistSlot(QString const &, int);
    void    idleSlot();
};

#endif // OUTPUT_H
