#include <iostream>
#include "Matrix.h"
#include "sharedTypes.h"
#include "Network.h"
using namespace std;

int main() {

    Network n({3, 2, 3}, 0.5);

    n.printWeights();
    try {
        n.feedForward({1, 1, 0});
    } catch (const char * msg) {
        cout << msg << endl;
    }
    n.printNodes();


    return 0;
}
