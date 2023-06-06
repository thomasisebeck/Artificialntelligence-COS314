#include <iostream>
#include "Matrix.h"
#include "Network.h"
using namespace std;

int main() {

    Network n({2, 3, 1}, 1);

    vector<vector<double>> targetInputs = {
            {0.0, 0.0},
            {1.0, 1.0},
            {1.0, 0.0},
            {0.0, 1.0},
    };

    vector<vector<double>> targetOutputs = {
            {0.0},
            {0.0},
            {1.0},
            {1.0},
    };

    const int EPOCHS = 100000;

    cout << "training started..." << endl;

    int index = 0;

    for (int i = 0; i < EPOCHS; i++) {
        index += 1;
        if (index == 4)
            index = 0;
        n.feedForward(targetInputs[index]);
        n.backProp(targetOutputs[index]);
    }

    cout << "Training complete..." << endl;

    for (auto input : targetInputs) {
        n.feedForward(input);
        auto predictions = n.getOutputValues();
        cout << input[0] << " " << input[1] << " -> " << predictions[0] << endl;
    }



    return 0;
}
