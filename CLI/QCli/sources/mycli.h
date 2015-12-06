#ifndef MYCLI_H
#define MYCLI_H

#include    "cli.h"
#include    "output.h"

class MyCLI : public CLI
{
    Output      *_output;

public:
    MyCLI(Output *);

    virtual void    logger(const char *message, typelog kind);
    virtual void    stopActivity(eErrorCode ec);
};

#endif // MYCLI_H
