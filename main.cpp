#include <bits/stdc++.h>
#include "bigreal.cpp"

using namespace std;

int main()
{
    bigreal s1("+123.115");
    bigreal s2("-1233.112");
    bigreal q("+123.123");
    bigreal w("+1234.123");
    cout << q + w << endl;

    // test 1
    bool bigger = (s2 > s1);
    cout << bigger << endl;

    // test 2
    bool lessthan = (s2 < s1);
    cout << lessthan << endl;

    // test 3
    bool equality = (s2 == s1);
    cout << equality << endl;

    // test 4
    cout << s1.checkReal() << endl;

    // test 5
    s2.setNumber("-+3124213.23214123");
    cout << s2.checkReal() << endl;

    // test 6
    s1.setNumber("+123.1234");
    s2.setNumber("+123.123");
    cout << s1 + s2 << endl;

    // test 7
    s1.setNumber("-321123321123.123321");
    s2.setNumber("-321321123321.123123");
    cout << s1 + s2 << endl;
}
