#include "Cards.h"
#include "Map.h"
#include "OrdersDriver.h"
#include "Orders.h"

#include <iostream>
#include <vector>

using namespace std;
using std::cout;
using std::endl;

int testing(){
    return 123;
}

void printVector(vector<int> vector) {
    cout << "Vector: ";
    for(int num: vector) {
        cout << " " << num;
    }
    cout << endl;
}

int main()
{
    testOrdersLists();
}
