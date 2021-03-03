/*---------------------------------------------------
    Program written by Charles Walker, Dakota Ruhl, and Kalin Ybarra.

*/

#include <iostream>
#include <list>
#include <queue>
#include <string.h>
#include <vector>
#include "Forward.h"
#include "Backward.h"

using namespace std;
// Forward Chaining
void treatment() {
    Forward f;
    f.run_forward(); // Run forward treatment


}

// Backward chaining
void diagnosis() {
    Backward b;

    b.run_backward();

}

int main(int argc, const char* argv[]) {
    string s; // Buffer string for inputs;

    diagnosis();
    cout << "Enter YES to continue to treatment, or NO to close the program." << endl;

    do  {
        cin >> s;
        if (s != "YES") {
            if (s != "NO") {
             cout << "ERROR: Enter only YES or NO\n";
            }
        }
    } while ((s != "YES") && (s != "NO")); // input verification
    cout << "\n";

    if (s == "YES") {
        treatment();
    }

    return 0;
}
