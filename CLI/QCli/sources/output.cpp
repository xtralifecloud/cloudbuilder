#include	<QCoreApplication>
#include	<QDebug>
#include	<iostream>
#include	<sstream>
#include	"output.h"
#include	"mycli.h"

Output::Output(QWidget *parent)
	: QTextEdit(parent)
{
	initDisplay();
	_parent = parent;
	_cursor = new QTextCursor(textCursor());
	_gCLI = new MyCLI(this);
	_gReady = true;
	_dotsCounter = 0;
	_clearDots = false;
	_currentLine = "";
	_onCurrentLine = true;

	launchThread();
}

Output::~Output()
{
	delete _cursor;
	delete _gCLI;
	_thread->quit();
}

void		Output::initDisplay()
{
	setStyleSheet("background-color: black; color : white");
}

void		Output::launchThread()
{
	_listener = new Listener;
	_thread = new QThread;

	connect(_listener, SIGNAL(idleSig()), this, SLOT(idleSlot()));
	connect(_thread, SIGNAL(started()), _listener, SLOT(process()));

	_listener->moveToThread(_thread);
	_thread->start();
}

void		Output::printLine(QString const &line, CLI::typelog type)
{
	if (_clearDots == true)
		clearDots();
	_cursor->movePosition(QTextCursor::End, QTextCursor::MoveAnchor, 1);
	switch (type)
	{
	case CLI::kLOG:
		_cursor->insertText(line + "\n");
		break;
	case CLI::kERR:
		_cursor->insertHtml("<font color='red'>" + line + "</font><br>");
		break;
	case CLI::kCMD:
		_cursor->insertHtml("<font color='green'><b>" + line + "<\b></font><br>");
		break;
	case CLI::kSCRIPT:
		_cursor->insertHtml("<font color='#729FCF'><b>" + line + "<\b></font><br>");
		break;
	}
	ensureCursorVisible();
}

// SLOTS

void		Output::clearDots()
{
	_cursor->movePosition(QTextCursor::End, QTextCursor::MoveAnchor );
	_cursor->movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor );
	_cursor->movePosition(QTextCursor::End, QTextCursor::KeepAnchor );
	_cursor->removeSelectedText();
	_clearDots = false;
}

void		Output::getLineSlot(QString const &cmd)
{
	if (_gReady == true)
		emit clearSig();
	else
		return ;

	if (cmd.length() > 0)
	{
		_gReady = false;
		printLine(QString(QString::fromLatin1("-> ") + cmd), CLI::kCMD);
		if (_history.size() > 0)
		{
			if (cmd.compare(*_histIt) == 0)
				_history.splice(_history.begin(), _history, _histIt);
			else
				_history.push_front(cmd);
		}
		else
			_history.push_front(cmd);
		_histIt = _history.begin();
		if (cmd.compare("exit") == 0 || cmd.compare("quit") == 0)
			QCoreApplication::exit();
		_timer.start();
		CloudBuilder::eErrorCode ec = _gCLI->execute(cmd.toStdString().c_str());
		if (ec != enNoErr)
		{
			if (ec != -1)
				printLine(errorString(ec), CLI::kERR);
			_gReady = true;
		}
		else
			_dotsCounter = 0;
	}
}

void		Output::idleSlot()
{
	_gCLI->idle();
	if (_gReady == true)
		return ;
	if (++_dotsCounter % 5 == 0 && _gReady == false)
	{
		_clearDots = true;
		_cursor->insertText(".");
	}
	if (_dotsCounter >= 20)
	{
		clearDots();
		_dotsCounter = 0;
	}
}

void		Output::done()
{
	std::stringstream   ss;

	int  time = _timer.elapsed();
	if (_clearDots == true)
		clearDots();
	_cursor->movePosition(QTextCursor::End, QTextCursor::MoveAnchor, 1);

	ss << "(" << time / 1000 << "." << time % 1000 << " sec)";
	_cursor->insertHtml("<font color='green'>Done!</font>");
	_cursor->insertText("   ");
	_cursor->insertHtml("<font color='grey'>" + QString::fromStdString(ss.str()) + "</font><br>");

}

void		Output::browseHistSlot(const QString &currentLine, int key)
{
	if (_history.size() > 0)
	{
		if ((*_histIt).compare(currentLine) != 0)
		{
			_histIt = _history.begin();
			_currentLine = currentLine;
			_onCurrentLine = true;
		}
	}

	if (key == Qt::Key_Up && _history.size() > 0)
	{
		std::list<QString>::iterator i = _history.end();
		i--;
		if (_onCurrentLine == true)
		{
			emit replaceBy(*_histIt);
			_onCurrentLine = false;
		}
		else if (_histIt != i)
		{
			_histIt++;
			emit replaceBy(*_histIt);
			_onCurrentLine = false;
		}
	}
	if (key == Qt::Key_Down && _history.size() > 0)
	{
		if (_histIt != _history.begin())
		{
			_histIt--;
			emit replaceBy(*_histIt);
			_onCurrentLine = false;
		}
		else
		{
			emit replaceBy(_currentLine);
			_onCurrentLine = true;
		}
	}
}
