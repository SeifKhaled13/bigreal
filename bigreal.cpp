#include "bigreal.h"
#include <bits/stdc++.h>
using namespace std;

bigreal::bigreal()
{
    // ctor
}

bigreal::~bigreal()
{
    // dtor
}

bool bigreal::isValidReal()
{
    string newNumber = number;
    int numberOfDots = 0;
    int numberOfSigns = 0;
    int numberOfNumbers = 0;
    int numberOfSpaces = 0;
    int size = newNumber.size();
    for (int i = 0; i < size; i++)
    {
        if (newNumber[i] == '.')
            numberOfDots++; // to make sure we have one dot only
        if (newNumber[i] == '-' || newNumber[i] == '+')
            numberOfSigns++; // to make sure we have one sign or 0
        if (newNumber[i] <= '9' && newNumber[i] >= '0')
            numberOfNumbers++; // to make sure if we have numbers or no
        if (newNumber[i] == ' ')
            numberOfSpaces++;
    }
    if (numberOfSigns > 1)
        return false;
    if (numberOfSigns == 1 && (newNumber[0] != '+' && newNumber[0] != '-'))
        return false;
    if (numberOfDots > 1)
        return false;
    if (numberOfNumbers == 0)
        return false;
    if (numberOfSpaces > 0)
        return false;
    return true;
}

bigreal::bigreal(string theNumber)
{
    number = theNumber;
    findFrac();
    assignIntPart();
    assignFracPart();
    assign();
}

bool bigreal::checkReal()
{
    return isValidReal();
}

void bigreal::assign()
{
    if (number[0] == '-' || number[0] == '+')
    {
        sign = number[0];
    }
    else
    {
        sign = '+';
    }
}

void bigreal::findFrac()
{
    for (int i = 0; i < number.size(); i++)
    {
        if (number[i] == '.')
        {
            fracPlace = i;
            break;
        }
    }
}

void bigreal::assignIntPart()
{
    for (int i = (number[0] == '+' || number[0] == '-'); i < fracPlace; i++)
        intPart.push_back(number[i]);
}

void bigreal::assignFracPart()
{
    for (int i = fracPlace + 1; i < number.size(); i++)
    {
        fracPart += number[i];
    }
}

void bigreal::removeSign()
{
    if (number[0] == '+' || number[0] == '-')
    {
        number = number.substr(1);
    }
}

bool bigreal ::operator>(bigreal b2)
{
    // عشان يشتغل صح مع الاشارات لازم ادخل الاشاره مع الرقم ##

    // integer part and fraction part
    if (sign == '-' && b2.sign == '+')
    {
        return false;
    }
    else if (sign == '+' && b2.sign == '-')
    {
        return true;
    }

    string integer1 = number.substr(0, number.find("."));
    string fraction1 = number.substr(integer1.size() + 1, number.size() - 1);
    string integer2 = b2.number.substr(0, b2.number.find("."));
    string fraction2 = b2.number.substr(integer2.size() + 1, b2.number.size() - 1);
    // compare the number of digit first

    if (integer1.size() > integer2.size())
    {
        return true;
    }
    else if (integer1.size() < integer2.size())
    {
        return false;
    }
    else if (integer1.size() == integer2.size())
    {
        if (fraction1.size() > fraction2.size())
            return true;
        else if (fraction1.size() < fraction2.size())
            return false;
    }

    for (int i = 0; i < integer1.size(); i++)
    {
        if (integer1[i] > integer2[i])
        {
            return true;
        }
        else if (integer1[i] == integer2[i])
        {
            if (fraction1[i] > fraction2[i])
            {
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
}

// less than
bool bigreal::operator<(bigreal b2)
{

    // integer part and fraction part
    if (sign == '-' && b2.sign == '+')
    {
        return true;
    }
    else if (sign == '+' && b2.sign == '-')
    {
        return false;
    }
    string integer1 = number.substr(0, number.find("."));
    string fraction1 = number.substr(integer1.size() + 1, number.size() - 1);
    string integer2 = b2.number.substr(0, b2.number.find("."));
    string fraction2 = b2.number.substr(integer2.size() + 1, b2.number.size() - 1);
    // compare the number of digit first

    if (integer1.size() < integer2.size())
    {
        return true;
    }
    else if (integer1.size() > integer2.size())
    {
        return false;
    }
    else if (integer1.size() == integer2.size())
    {
        if (fraction1.size() < fraction2.size())
            return true;
        else if (fraction1.size() > fraction2.size())
            return true;
    }

    for (int i = 0; i < integer1.size(); i++)
    {

        if (integer1[i] < integer2[i])
        {
            return true;
        }
        else if (integer1[i] == integer2[i])
        {
            if (fraction1[i] < fraction2[i])
            {
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
}

// equal
bool bigreal::operator==(bigreal b2)
{

    // integer part and fraction part
    string integer1 = number.substr(0, number.find("."));
    string fraction1 = number.substr(integer1.size() + 1, number.size() - 1);
    string integer2 = b2.number.substr(0, b2.number.find("."));
    string fraction2 = b2.number.substr(integer2.size() + 1, b2.number.size() - 1);
    if (integer1 == integer2 && fraction1 == fraction2)
    {
        return true;
    }

    else
        return false;
}

bigreal bigreal::operator+(bigreal &b2)
{
    bigreal result;
    int carry = 0;
    string frac = "";
    string nPart = "";

    while (intPart.size() < b2.intPart.size())
        intPart = '0' + intPart;
    while (intPart.size() > b2.intPart.size())
        b2.intPart = '0' + b2.intPart;
    while (fracPart.size() < b2.fracPart.size())
        fracPart += '0';
    while (fracPart.size() > b2.fracPart.size())
        b2.fracPart += '0';
    if (b2.sign == '+' && sign == '+')
    {
        for (int i = 0; i < fracPart.size(); i++)
        {
            int d1 = fracPart[i] - '0';
            int d2 = b2.fracPart[i] - '0';
            int sum = d1 + d2 + carry;
            carry = sum / 10;
            frac += to_string(sum % 10);
        }
        for (int i = 0; i < intPart.size(); i++)
        {
            int d1 = intPart[i] - '0';
            int d2 = b2.intPart[i] - '0';
            int sum = d1 + d2 + carry;
            carry = sum / 10;
            nPart += to_string(sum % 10);
        }
        if (carry > 0)
        {
            result.intPart = to_string(carry) + result.intPart;
        }
        result.sign = '+';
        result.number = result.sign + nPart + '.' + frac;
        return result;
    }
    else if (b2.sign == '+' && sign == '-')
    {
        return (b2 - *this);
    }
    else if (b2.sign == '-' && sign == '+')
    {
        return (*this - b2);
    }
    else if (b2.sign == '-' && sign == '-')
    {
        for (int i = 0; i < fracPart.size(); i++)
        {
            int d1 = fracPart[i] - '0';
            int d2 = b2.fracPart[i] - '0';
            int sum = d1 + d2 + carry;
            carry = sum / 10;
            frac += to_string(sum % 10);
        }
        for (int i = 0; i < intPart.size(); i++)
        {
            int d1 = intPart[i] - '0';
            int d2 = b2.intPart[i] - '0';
            int sum = d1 + d2 + carry;
            carry = sum / 10;
            nPart += to_string(sum % 10);
        }
        if (carry > 0)
        {
            result.intPart = to_string(carry) + result.intPart;
        }
        result.sign = '-';
        result.number = result.sign + nPart + '.' + frac;
        return result;
    }

    return result;
}

bigreal bigreal::operator-(bigreal &b2)
{
    // Similar to the addition logic, but handle subtraction instead
    string integer1 = number.substr(1, number.find("."));
    string fraction1 = number.substr(integer1.size() + 1, number.size() - 1);
    string integer2 = b2.number.substr(1, b2.number.find("."));
    string fraction2 = b2.number.substr(integer2.size() + 1, b2.number.size() - 1);

    // Pad the numbers with zeros to make them equal in size
    while (integer1.size() < integer2.size())
        integer1 = "0" + integer1;
    while (integer2.size() < integer1.size())
        integer2 = "0" + integer2;

    while (fraction1.size() < fraction2.size())
        fraction1 += "0";
    while (fraction2.size() < fraction1.size())
        fraction2 += "0";

    bigreal result;
    result.number = (number[0] == b2.number[0] ? "" : "-") + integer1 + "." + fraction1;

    // Subtract the integer and fraction parts separately
    // case 1

    if ((number[0] == '+' && b2.number[0] == '+'))
    {

        for (int i = 1; i < result.number.size(); i++)
        {
            if (result.number[i] == '.')
                continue;
            result.number[i] = '0' + ((number[i] - '0') - (b2.number[i] - '0'));
        }
    }

    // case 2
    else if ((number[0] == '+' && b2.number[0] == '-'))
    {

        for (int i = 1; i < result.number.size(); i++)
        {
            if (result.number[i] == '.')
                continue;
            result.number[i] = '0' + ((number[i] - '0') + (b2.number[i] - '0'));
        }
    }

    // case 3
    else if ((number[0] == '-' && b2.number[0] == '-'))
    {

        for (int i = 1; i < result.number.size(); i++)
        {
            if (result.number[i] == '.')
                continue;
            // the sign
            result.number[i] = '0' + (b2.number[i] - '0') - (number[i] - '0');
        }
    }

    // case 4
    else if ((number[0] == '-' && b2.number[0] == '+'))
    {

        for (int i = 1; i < result.number.size(); i++)
        {
            if (result.number[i] == '.')
                continue;
            result.number[i] = '0' + ((number[i] - '0') + (b2.number[i] - '0'));
        }
    }
    // Handle borrow in the fraction part
    for (int i = result.number.size() - 1; i >= 0; i--)
    {
        if (result.number[i] == '.')
            continue;

        if (result.number[i] < '0')
        {
            result.number[i] += 10;
            result.number[i - 1]--;
        }
    }

    return result;
}

ostream &operator<<(ostream &os, const bigreal &number)
{
    string backup = number.number;
    if (number.number[0] == '+')
        backup = number.number.substr(1);
    os << backup;
    return os;
}
