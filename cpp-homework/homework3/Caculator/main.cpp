#include "Calculator.h"
#include <iostream>

using namespace std;
int main() {
    // Calculator calculator;
    // cout << calculator.calculate("5 + 3 * ( 6 + 7 ) - 2") << endl;

    // Calculator calculator;
    // calculator.registerConstant("pi", 3.1415);
    // cout << calculator.calculate("2 * 2 * pi");
    // return 0;

    // Calculator calculator;
    // cout << calculator.calculate("5 + 3 * ( 6 + 7 ) - 2") << endl;

    // Calculator calculator;
    // calculator.registerConstant("pi", 3.1415);
    // cout << calculator.calculate("2 * 2 * pi");
    // return 0;

    Calculator calculator;
    calculator.registerConstant("x", 2);
    calculator.registerOperator("h ^ l = h * l / x", 5);
    calculator.registerConstant("h", 2);
    calculator.registerConstant("l", 2);
    cout << calculator.calculate("h ^ l") << endl;
    cout << calculator.calculate("h * 2 ^ l") << endl;
    cout << calculator.calculate("h * 2 ^ l") << endl;

    // Calculator calculator;
    // calculator.registerConstant("x", 2);
    // calculator.registerOperator("h ^ l = h * l / x", 5);
    // calculator.registerConstant("h", 2);
    // calculator.registerConstant("l", 2);
    // cout << calculator.calculate("h ^ l") << endl;
    // calculator.registerConstant("h", 3);
    // calculator.registerConstant("l", 3);
    // cout << calculator.calculate("h ^ l") << endl;
}