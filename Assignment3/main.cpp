#include <iostream>
#include <vector>
#include "Network.h"
using namespace std;

int main() {

    Network n({2, 3, 2});
    n.setTargetVals({2, 3});
    n.setInputVals({1, 2});

    try {
        n.feedForward();
    } catch (const char* msg) {
        cout << msg << endl;
    }

    return 0;
}