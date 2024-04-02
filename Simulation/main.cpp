#include <iostream>

#include "StreetPoker.h"

using namespace std;

const int ITERATIONS = 1e6;

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie (0);
    cout.tie (0);

    StreetPoker sp;
    Strategy st;
    cout << sp.simulate(st, ITERATIONS) << "\n";

}   