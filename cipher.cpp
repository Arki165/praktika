#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <random>

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

 //функция чтения ключа из файла
string readKey(const string& path) {
    ifstream file(path); //здесь не нужно считываение в бинарном режиме, у нас ключ подается изначально как набор 0 и 1
    if (!file.is_open()) {
        cout << "Не удалось открыть файл с ключом!";
        exit(1);
    }
    string bits;
    file >> bits;
    for (int i; i<bits.size(); i++) {
        if (bits[i] != '0' && bits[i] != '1') {
            cout << "Ключ содержит недопустимые символы!";
            exit(1);
        }
    }
    //ключ в файле должен быть строго равен 8 бит, по этому проверка
    if (bits.size() % 8 != 0 && bits.size() != 0) {
        cout << "Длина ключа должна быть кратна 8 бит!";
        exit(1);
    }
    file.close();
    return bits;
}

//функция записи в файл
void writeFile(const string& path, const string& data){
    ofstream file(path, ios::binary); //аналогично, только с записью
    if (!file.is_open()){
        cout << "Не удалось создать файл для сохранения!";
        exit(1);
    }
    file << data;
    file.close();
}

//функция генерации ключа
string generateKey (int lengh) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0,1);
    string key = "";
    for (int i = 0; i <lengh; i++) {
        key += (dist(gen) == 0) ? '0' : '1';
    }
    return key;
}

//функция метода кодировки xor
unsigned char encryptXOR(unsigned char textByte, unsigned char key) {
    return textByte ^ key;
}

//функция метода кодировки xnor
unsigned char encryptXNOR(unsigned char textByte, unsigned char key) {
    return ~(textByte ^ key);
}