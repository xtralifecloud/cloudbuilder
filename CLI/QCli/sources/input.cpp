#include	<iostream>
#include	<QKeyEvent>
#include	"input.h"

Input::Input(QWidget *parent)
	: QLineEdit(parent)
{
}

Input::~Input()
{
}

void		Input::keyPressEvent(QKeyEvent *e)
{
	int	 key = e->key();

	if (key == Qt::Key_Return)
		emit sendLine(text());
	else if (key == Qt::Key_Up || key == Qt::Key_Down)
		emit browseHist(text(), key);
	else
		QLineEdit::keyPressEvent(e);
}

// SLOTS

void		Input::replaceBySlot(QString const &line)
{
	selectAll();
	del();
	insert(line);
}

void		Input::clearSlot()
{
	clear();
}
