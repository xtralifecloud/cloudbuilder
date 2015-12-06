#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->input, SIGNAL(sendLine(QString const &)), ui->output, SLOT(getLineSlot(QString const &)));
	connect(ui->input, SIGNAL(browseHist(QString const &, int)), ui->output, SLOT(browseHistSlot(QString const &, int)));
	connect(ui->output, SIGNAL(replaceBy(QString const &)), ui->input, SLOT(replaceBySlot(QString const &)));
	connect(ui->output, SIGNAL(clearSig()), ui->input, SLOT(clearSlot()));
	ui->input->setFocus();
	resize(1000, 600);
	ui->output->printLine("Welcome to CloudBuilder CLI\n\nType help to get lists of commands\n\n");
}

MainWindow::~MainWindow()
{
	delete ui;
}
