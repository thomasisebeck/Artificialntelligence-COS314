#include <iostream>
#include <vector>
#include "Network.h"
using namespace std;

int main() {

    Network n({2, 3, 2}, 1);
    n.setTargetVals({0.1, 0.4});
    n.setInputVals({0.5, 0.1});

    try {
        for (int i = 0; i < 100; i++) {
            n.feedForward();
            n.backPropagate();
        }
        n.testNetwork();
    } catch (const char* msg) {
        cout << msg << endl;
    }

    return 0;
}