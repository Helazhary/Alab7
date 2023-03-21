#include <iostream>
#include <string>
using namespace std;

string add(string x, string y);
string subt(string x, string y);
string pow(string x, string y);
void oddeven(string &x, string &y);
string karatsuba(string x, string y);

int main()
{

    cout << karatsuba("1234567891011", "123456789101112");
}

string add(string x, string y)
{
    int carry = 0;
    int sum;
    string result = "";
    int i = x.size() - 1;
    int j = y.size() - 1;

    while (i >= 0 || j >= 0 || carry != 0)
    {
        int digit1 = i >= 0 ? x[i] - '0' : 0;
        int digit2 = j >= 0 ? y[j] - '0' : 0;

        sum = digit1 + digit2 + carry;
        carry = sum / 10;
        sum %= 10;
        result = to_string(sum) + result;
        i--;
        j--;
    }

    return result;
}

string subt(string x, string y)
{
    int borrow = 0;
    int diff;
    string result = "";
    int i = x.size() - 1;
    int j = y.size() - 1;

    while (i >= 0 || j >= 0)
    {
        int digit1 = i >= 0 ? x[i] - '0' : 0;
        int digit2 = j >= 0 ? y[j] - '0' : 0;

        diff = digit1 - digit2 - borrow;
        borrow = diff < 0 ? 1 : 0;
        diff = diff < 0 ? diff + 10 : diff;
        result = to_string(diff) + result;
        i--;
        j--;
    }

    return result;
}

string pow(string x, string y)
{
    int y1 = stoi(y);
    for (int i = 0; i < y1; i++)
    {
        x.append("0");
    }
    return x;
}

void oddeven(string &x, string &y)
{
    int xs = x.size();
    int ys = y.size();
    while (x.size() != y.size())
    {
        x.size() < y.size() ? x.insert(0, "0") : y.insert(0, "0");
    }
}

string karatsuba(string x, string y)
{
    // base case
    if (x.size() == 1 && y.size() == 1)
    {
        return to_string(stoi(x) * stoi(y));
    }

    oddeven(x, y);

    int n = x.size();
    int mid = n / 2;

    string a = x.substr(0, mid);
    string b = x.substr(mid);
    string c = y.substr(0, mid);
    string d = y.substr(mid);

    // recursive calls
    string ac = karatsuba(a, c);
    string bd = karatsuba(b, d);
    string ad_bc = subt(karatsuba(add(a, b), add(c, d)), add(ac, bd));

    // combining
    string result = add(add(pow(ac, to_string(2 * (n - mid))), pow(ad_bc, to_string(n - mid))), bd);

    return result;
}