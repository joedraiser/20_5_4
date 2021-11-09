#include <iostream>
#include <fstream>

enum banknoteVal
        {
            bv100,
            bv200,
            bv500,
            bv1000,
            bv2000,
            bv5000
        };

int main()
{
    std::cout << "Input '+' to fulfil ATM or '-' to withdraw: ";
    std::string input;
    std::cin >> input;

    std::fstream ATM_Storage("ATM.txt");
    
    return 0;
}
