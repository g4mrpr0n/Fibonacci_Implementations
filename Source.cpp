#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;


class BigInt {
    string number;
public:
    BigInt() :number("0") {}
    BigInt(const string nr) : number(nr) {}

    BigInt operator+(const BigInt& other) const {
        std::string result;
        int carry = 0;
        int i = number.length() - 1;
        int j = other.number.length() - 1;
        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;
            if (i >= 0) {
                sum += number[i] - '0';
                i--;
            }
            if (j >= 0) {
                sum += other.number[j] - '0';
                j--;
            }
            carry = sum / 10;
            result = std::to_string(sum % 10) + result;
        }
        return BigInt(result);
    }

    BigInt operator*(const BigInt& b) const {
        std::string num1 = number, num2 = b.number;
        int n1 = num1.size(), n2 = num2.size();
        std::vector<int> result(n1 + n2, 0);

        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());

        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                result[i + j] += (num1[i] - '0') * (num2[j] - '0');
                result[i + j + 1] += result[i + j] / 10;
                result[i + j] %= 10;
            }
        }

        while (result.size() > 1 && result.back() == 0)
            result.pop_back();

        std::reverse(result.begin(), result.end());

        std::string res = "";
        for (int i : result)
            res += (i + '0');

        return BigInt(res);
    }
    friend ostream& operator<<(ostream& o, BigInt bigint)
    {
        o << bigint.number;
        return o;
    }
    void assign(BigInt x)
    {
        number = x.number;
    }
    string getter()
    {
        return number;
    }
};


struct Node
{
    BigInt number;
    Node* next;
    Node* prev;

    Node(BigInt number, Node* next = nullptr, Node* prev = nullptr)
        : number(number), next(next), prev(prev)
    {
    }
};


//Memoization recursive
BigInt fibrecmem(int n, BigInt* t)
{
    BigInt a("0");
    if (n == 0)
    {
        BigInt b("0");
        a.assign(b);
        return a;
    }
    if (n == 1)
    {
        BigInt b("1");
        a.assign(b);
        return a;
    }

    if (t[n].getter().length() > 1 && n > 1)
    {

        return t[n];
    }
    else {

        t[n] = fibrecmem(n - 1, t) + fibrecmem(n - 2, t);
        return t[n];
    }
}


//Simple recursive
BigInt fibrec(int n)
{
    BigInt a("0");
    if (n == 0)
    {
        BigInt b("0");
        a.assign(b);
        return a;
    }
    if (n == 1)
    {
        BigInt b("1");
        a.assign(b);
        return a;
    }
    else return fibrec(n - 1) + fibrec(n - 2);
}



//Iterative method
BigInt fibiter(int n)
{
    BigInt first("0");
    BigInt second("1");
    BigInt final("0");
    for (int i = 0; i < n; i++)
    {
        final = first + second;
        first = second;
        second = final;
    }
    return final;
}



//Binet method
double fibbin(int n) {
    double sqrt5 = sqrt(5.0);
    double phi = (1 + sqrt5) / 2;
    return ((pow(phi, n) - pow(-phi, -n)) / sqrt5);
}


//Doubly linked list
void generate(Node* V, int n)
{
    if (!V)
        return;
    if (n == 0)
        return;
    V->next = new Node(V->number + V->prev->number, nullptr, V);
    generate(V->next, n - 1);
}
void print(Node* x)
{
    if (!x)
        return;
    if (x->next == nullptr)
        cout << x->number;
    print(x->next);
}


BigInt fib(int n) {
    BigInt a("1"), b("0"), c("0"), d("1"), t;
    if (n == 0)
    {
        BigInt b("0");
        return b;
    }
    n = n - 1;
    while (n > 0) {
        if (n % 2 == 1) {
            t = d * (b + a) + c * b;
            a = d * b + c * a;
            b = t;
        }
        t = d * (BigInt("2") * c + d);
        c = c * c + d * d;
        d = t;
        n = n / 2;
    }
    return a + b;
}


int main()
{
    BigInt t[1151];
    int n = 20;
    Node* root = new Node(BigInt("0"), nullptr, nullptr);
    Node* firstEl = new Node(BigInt("1"), nullptr, root);
    root->next = firstEl;
    generate(firstEl, n-1);
    cout << "Recursive with memoization(top-down): " << fibrecmem(n, t) << "\n\n";
    cout << "Iterative: " << fibiter(n-1) << "\n\n";
    cout << "Binet: " << fibbin(n) << "\n\n";    
    cout << "Doubly-linked list iterative optimisation: ";
    print(root);
    cout << "\n\nRecursive: " << fibrec(n);
    cout << "\n\nMatrix multiplication: " << fib(n) << "\n";
}
