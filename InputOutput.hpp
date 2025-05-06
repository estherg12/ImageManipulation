#ifndef INPUTOUTPUT_HPP
#define INPUTOUTPUT_HPP
#include "StackOperations.hpp"
#include "ElementStack.hpp"

#include <string>
using std::string;

#include <iostream>
using namespace std;

class InputOutput
{
public:
    InputOutput();
    ~InputOutput();
    string askName();
    StackOperations* askOper();

};

#endif // INPUTOUTPUT_HPP
