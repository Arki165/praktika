#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//функция чтения текстового файла
string readFile(const string& path) {
    ifstream file(path, ios::binary); //открываем файлы в бинарном режиме, 
                                      //чтобы ничего не сломалось
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

//функция чтения файла ключа
string readKey(const string& path) {
    ifstream file(path); //здесь не нужно считываение в бинарном режиме, 
                         //у нас ключ подается изначально как набор 0 и 1
    if (!file.is_open()) {
        cout << "Не удалось открыть файл с ключом!";
        exit(1);
    }
    string bits;
    file >> bits;
    //ключ в файле должен быть строго равен 8 бит, по этому проверка
    if (bits.size() != 8) {
        cout << "Ключ должен быть 8 бит!";
        exit(1)
    }
    file.close();
    return bits;
}

//функция записи
void writeFile(const string& path, const string& data){
    ofstream file(path, ios::binary); //аналогично, только с записью
    if (!file.is_open()){
        cout << "Не удалось создать файл для сохранения!";
        exit(1);
    }
    file << data;
    file.close();
}

//функция шифрования/дешифрования XOR
unsigned char encryptXOR(unsigned char textByte, unsigned char key) {
    return textByte ^ key;
}

//функция шифрования/дешифрования XNOR
unsigned char encryptXNOR(unsigned char textByte, unsigned char key) {
    return ~(textByte ^ key);
}