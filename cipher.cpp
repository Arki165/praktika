#include <iostream>
#include <fstream>
using namespace std;

void readFile(const string& path) {
    ifstream file(path, ios::binary);
    char ch;
    while (file.get(ch)) {
        cout << ch;
    }
    cout << endl;
    file.close();
}
