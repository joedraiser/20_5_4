#include <iostream>
#include <fstream>
#include <ctime>

int banknotes[] = {100, 200, 500, 1000, 2000, 5000};

bool banknotes2withdraw(int* storage, int* withdraw, int money, int i=5)
{
    int temp;

    if(i<0&&money>0)
        return false;

    for(int j=money/banknotes[i];j>=0;j--)
    {
        *(withdraw+i)=j;
        temp=money-banknotes[i]*j;
        if(*(withdraw+i)>*(storage+i))
            continue;
        else if(temp==0)
            return true;
        else if(banknotes2withdraw(storage, withdraw, temp, i-1))
            return true;
    }

    return false;
}

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
    std::srand(std::time(nullptr));
    int storage[] = {0, 0, 0, 0, 0, 0};

    std::cout << "Input '+' to fulfil ATM or '-' to withdraw: ";
    std::string input;
    std::cin >> input;

    std::fstream ATM_Storage;

    if(input=="+")
    {
        ATM_Storage.open("ATM.txt", std::ios::binary | std::fstream::out);

        for (int i = 0; i < 1000; i++)
        {
            storage[rand() % 6]++;
        }

        ATM_Storage.write((char*)storage, sizeof(storage));

        ATM_Storage.close();
    }

    else if(input=="-")
    {
        ATM_Storage.open("ATM.txt", std::ios::binary | std::ios::in);

        if(!ATM_Storage.is_open())
        {
            std::cout << "File is not opened";
            exit(EXIT_FAILURE);
        }

        std::cout << "Input value to withdraw: ";
        int money;
        std::cin >> money;

        int withdraw[6] = {0,0,0,0,0,0};

        ATM_Storage.read((char*)storage, sizeof(storage));
        ATM_Storage.close();

        if(money%100!=0)
        {
            std::cout << "This value cannot be withdrawn";
            exit(EXIT_FAILURE);
        }

        if(banknotes2withdraw(storage, withdraw, money))
        {
            storage[bv5000]-=withdraw[bv5000];
            storage[bv2000]-=withdraw[bv2000];
            storage[bv1000]-=withdraw[bv1000];
            storage[bv500]-=withdraw[bv500];
            storage[bv200]-=withdraw[bv200];
            storage[bv100]-=withdraw[bv100];
            std::cout << "Money withdrawn";
            ATM_Storage.open("ATM.txt", std::ios::binary | std::ios::out);
            if(!ATM_Storage.is_open())
            {
                std::cout << "File is not opened";
                exit(EXIT_FAILURE);
            }
            ATM_Storage.write((char*)storage, sizeof(storage));
            ATM_Storage.close();
        }
        else
        {
            std::cout << "Not enough banknotes in ATM";
        }

    }

    return 0;
}
