#ifndef CLASS_H
#define CLASS_H

#include <bits/stdc++.h>

using namespace std;

class bigreal
{
    string number;
    int size = number.size();
    bool isValidReal();
    char sign;
    string intPart = "";
    string fracPart = "";
    int fracPlace = 0;

public:
    bigreal();
    virtual ~bigreal();
    bigreal(string newNumber);
    string getNumber()
    {
        return number;
    }
    void setNumber(string number)
    {
        this->number = number;
        findFrac();
        assignIntPart();
        assignFracPart();
        assign();
    }
    bool checkReal();
    bool operator>(bigreal b2);
    bool operator<(bigreal b2);
    bool operator==(bigreal b2);
    friend ostream &operator<<(ostream &os, const bigreal &number);
    bigreal operator-(bigreal &b2);
    bigreal operator+(bigreal &b2);
    void assign();
    void findFrac();
    void assignIntPart();
    void assignFracPart();
    void removeSign();
};

#endif // CLASS_H