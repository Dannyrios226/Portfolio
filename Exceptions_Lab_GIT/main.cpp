#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;






class InvalidSize :public invalid_argument {
public:
    InvalidSize( const char * invalid) : invalid_argument(invalid)
    {}
};

class StackFull :public runtime_error {
    public:
    StackFull ( int arg, const char * errorMSG) : argument(arg), runtime_error (errorMSG)
    {}
    
    int getValue() const  {return argument;}

    private:
    int argument;
};
        
class StackEmpty :public runtime_error {
public:
    StackEmpty(const char* message) : runtime_error(message) {}
};






class IntStack
{
public:
    // MaxSize should be an unsigned int, but for the sake of example...
    IntStack(int MaxSize)
    {
        if (MaxSize < 0)
        {
            throw InvalidSize("Can not create a negative Sized Stack");
        }

        data.resize(MaxSize);
        cur_index = 0;
    }

    void push(int new_data)
    {
        if (cur_index == data.size())
        {
            throw StackFull( new_data, "Push to full stack");
        }
        else
        {
            data.at(cur_index) = new_data;
            cur_index++;
        }
    }

    int pop()
    {
        if (cur_index == 0)
        {
            throw StackEmpty("Pop from empty stack");
           
        }
        else
        {
            // pop off the int and return it
            cur_index--;
            return data.at(cur_index);
        }
    }

private:
    vector<int> data;
    unsigned int cur_index;
};

int main()
{
    try{
        // Testing Constructor
        IntStack c_test(-10);
        
        c_test.push(3);
        c_test.push(4);
        c_test.pop();
        c_test.pop();
    }
    catch (const InvalidSize& E)
    { cerr << E.what() << endl;}
        // Testing push
        IntStack push_test(5);
    try {
            for (unsigned int i = 0; i < 7; i++) {
                
                push_test.push(i);
            }
        }   catch (const StackFull& E)
            { cerr << E.what() << " Value = " << E.getValue() << endl;}
     
        
        // Testing pop
    try {
        IntStack pop_test(2);
        
        pop_test.push(1);
        pop_test.push(2);
        pop_test.pop();
        pop_test.pop();
        pop_test.pop();
    }
    catch(const StackEmpty& E)
    {cerr << E.what() << endl;}
    
        cout << "Completed!" << endl;
        

    return 0;
}



