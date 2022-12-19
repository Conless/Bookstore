#include <bits/stdc++.h>

using namespace std;

typedef unordered_set<int> test_1;
typedef unordered_multiset<int> test_2;
typedef unordered_map<int, int> test_3;
typedef unordered_multimap<int, int> test_4;

int main() {
    test_1 a1;
    test_2 a2;
    test_3 a3;
    test_4 a4;
    a2.insert(1);
    a2.insert(1);
    a2.erase(a2.find(1));
    cout << a2.size() << endl;
    return 0;
}
