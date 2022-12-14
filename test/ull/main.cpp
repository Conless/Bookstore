#include <iostream>
#include <set>
using namespace std;
set<pair<string, int>> s;
int main() {
    int n;
    cin >> n;
    while (n--) {
        string opt, A;
        int B;
        cin >> opt;
        if (opt == "insert") {
            cin >> A >> B;
            s.insert(make_pair(A, B));
        } else if (opt == "delete") {
            cin >> A >> B;
            if (s.count(make_pair(A, B)))
                s.erase(make_pair(A, B));
        } else {
            cin >> A;
            auto x = s.lower_bound(make_pair(A, 0));
            if (x == s.end() || x->first != A) {
                cout << "null" << endl;
                continue;
            }
            for (x; x != s.end() && x->first == A; ++x)
                cout << x->second << " ";
            cout << endl;
        }
    }
    return 0;
}