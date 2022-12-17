#include <bits/stdc++.h>

using namespace std;

class A {
  public:
    int a;
};
class B : public A {};

int main() {
    A *a = nullptr;
    delete a;
    // ofstream creater("test.dat", ios::out | ios::trunc);
    // creater.close();
    // fstream file("test.dat");
    // B *b = new B;
    // b->a = 2;
    // A *a = b;
    // file.seekp(0);
    // file.write(reinterpret_cast<char *>(a), sizeof(A));
    // delete a;
    // a = new A;
    // b = new B;
    // file.seekg(0);
    // file.read(reinterpret_cast<char *>(a), sizeof(A));
    // b = reinterpret_cast<B *>(a);
    // cout << b->a << endl;
    return 0;
}