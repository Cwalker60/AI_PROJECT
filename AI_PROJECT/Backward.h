#ifndef BACKWARD_H
#define BACKWARD_H

#include "Backward.h"

using namespace std;

class Backward{
public:
    void run_backward();
    Backward();
private:

    void init(void);
    void determine_member_concl_list(void);
    void push_on_stack(void);
    void instantiate(void);
    void ifSwitch();
    void thenSwitch(void);
    void recursive_search(void);
    void printStack(void);
    void log_data(void);
};

#endif
