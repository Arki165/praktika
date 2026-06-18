#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

string readFile(const string& path) {
    ifstream file(path, ios::binary); //открываем файлы в бинарном режиме, чтобы ничего не сломалось
    if (!file.is_open()) {
        cout << "Не удалось открыть файл с исходным текстом!";
        exit(1);
    }
    //чтение файла в одну строку, итератор ходит по байтам файла, конструктор
    //проходит по каждому байту файла и складывая каждый байт в строку
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

//функция записи
void writeFile(const string& path, const string& data){
    ofstream file(path, ios::binary);
    if (!file.is_open()){
        cout << "Не удалось создать файл для сохранения!";
        exit(1);
    }
    file << data;
    file.close();
}

string readKey(const string& path) {
    ifstream file(path); //здесь не нужно считываение в бинарном режиме, у нас ключ подается изначально как набор 0 и 1
    if (!file.is_open()) {
        cout << "Не удалось открыть файл с ключом!";
        exit(1);
    }
    string bits;
    file >> bits;
    if (bits.size() != 8) {
        throw runtime_error("Ключ должен быть 8 бит!");
    }
    unsigned char res = (unsigned char)stoi(bits, nullptr, 2);
    file.close();
    return bits;

}

unsigned char encryptXOR(unsigned char textByte, unsigned char key) {
    return textByte ^ key;
}

unsigned char encryptXNOR(unsigned char textByte, unsigned char key) {
    return ~(textByte ^ key);
}