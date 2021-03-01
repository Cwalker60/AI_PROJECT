/*---------------------------------------------------
    Program written by Charles Walker, Dakota Ruhl, and Kalin Ybarra

*/

#include <iostream>
#include <list>
#include <queue>
#include <string.h>
#include <vector>
#include "Forward.h"
#include "NewBackward.h"

using namespace std;
// Forward Chaining
void treatment() {
    // Initialization
    // Variable List Initialization
    list<string> varlist;


}

// Backward chaining
void diagnosis() {
    // Initialization

    list<string> varlist;
    list<string> conclusionlist;

    // Variable List Initialization


    // Inserting conclusion variables.



}

int main(int argc, const char* argv[]) {
    NewBackward b;
    Forward f;

    b.run_backward(); // Run backward diagnosis
    f.run_forward(); // Run forward treatment

    return 0;
}
