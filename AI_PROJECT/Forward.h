#ifndef FORWARD_H
#define FORWARD_H

#include "Forward.h"
using namespace std;

class Forward {
public:
    Forward();
    void run_forward();
    NewForward();
private:
    void check_instantiation(void);
    void search(void);
    void instantiate(void);
};

#endif

