#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string readFile(const string& path) {
    ifstream file(path, ios::binary); //открываем файлы в бинарном режиме, чтобы ничего не сломалось
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + path);
    }
    //чтение файла в одну строку, итератор ходит по байтам файла, конструктор
    //проходит по каждому байту файла и складывая каждый байт в строку
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

unsigned char readKey(const string& path) {
    ifstream file(path); //здесь не нужно считываение в бинарном режиме, у нас ключ подается изначально как набор 0 и 1
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + path);
    }
    string bits;
    file >> bits;
    if (bits.size != 8) {
        throw runtime_error("Ключ должен быть 8 бит!");
    }
    unsigned char res = (unsigned char)stoi(bits, nullptr, 2);
    file.close();
    return res;

}

unsigned char encryptXOR(unsigned char textByte, unsigned char key) {
    return textByte ^ key;
}

unsigned char encryptXNOR(unsigned char textByte, unsigned char key) {
    return ~(textByte ^ key);
}
