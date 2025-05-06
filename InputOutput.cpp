#include "InputOutput.hpp"

InputOutput::InputOutput()
{
}

string InputOutput::askName()
{
    /*ask for the name of the image file that must be executed
     * returns a string
     */
    string file_name;
    cout<<"Tell me the file name without the extension: "<<endl;
    cin>>file_name;
    
    return file_name;
}

StackOperations* InputOutput::askOper()
{
    //returns a stack
    StackOperations* st = new StackOperations();
    char oper = 'R';
    
    //while the operation inserted by the user is one of the valid operations
    //this is done so that X or any other letter wont be stored in the stack
    while ((oper=='R')||(oper=='S')||(oper=='V')||(oper=='H')||(oper=='O'))
    {
        cout<<"Which operation do you want to do (in caps, just the letter)?: "<<endl;
        cout<<"R: reverse"<<endl;
        cout<<"S: sort"<<endl;
        cout<<"V: flip"<<endl;
        cout<<"H: flop"<<endl;
        cout<<"O: darken"<<endl;
        cout<<"X: exit"<<endl;
        cin>>oper;
        st->push(oper);
    }
    return st;
}

InputOutput::~InputOutput()
{
}

