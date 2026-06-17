#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string readFile(const string& path) {
    ifstream file(path, ios::binary);
    char ch;
    while (file.get(ch)) {
        cout << ch;
    }
    cout << endl;
    file.close();
}
