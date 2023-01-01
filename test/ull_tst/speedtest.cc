#include <bits/stdc++.h>
#include <ctime>

using namespace std;

int main() {
    freopen("speedtest.out", "w", stdout);
    ofstream os("speedtest.dat", ios::trunc);
    fstream file("speedtest.dat");
    int T = 50000;
    for (int i = 0; i < T; i++) {
        char s[61];
        sprintf(s, "%060d", i);
        int pos = rand() % T * sizeof(s);
        file.seekp(pos);
        file.write(reinterpret_cast<char *>(s), sizeof(s));
    }
    file.seekg(0);
    for (int i = 0; i < T; i++) {
        char data[61];
        int pos = rand() % T * sizeof(data);
        file.seekg(pos);
        file.read(reinterpret_cast<char *>(data), sizeof(data));
        printf("%d: %s\n", i, data);
    }
    return 0;
}
