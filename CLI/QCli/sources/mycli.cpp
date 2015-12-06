#include	<iostream>
#include "mycli.h"

MyCLI::MyCLI(Output *output)
	: CLI(), _output(output)
{
}

void MyCLI::logger (const char *message, typelog kind)
{
	_output->printLine(QString(message), kind);
}

void MyCLI::stopActivity (eErrorCode ec)
{
	_output->_gReady = true;
	if (ec)
		this->logger(errorString(ec), kERR);
	else
		_output->done();
}

