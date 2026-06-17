#include <iostream>
#include <string>

using namespace std;

//Заглушки для функций

//функция для шифровния и дешифрования файла
void processFile(int mode){
    string sourcePath, destPath, keyString;
    int methodChoice, keySourceChoice;

    cout << "\n-----Настройка операции-----\n";
    cout << "Введите путь к исходному файлу: "; cin >> sourcePath;
    cout << "\nВведите путь для сохранения результата: "; cin >> destPath;

    cout << "\nВыберите метод логической операции:\n";
    cout << "1. Сложение по модулю 2 (XOR)\n";
    cout << "2. Логическая эквивалентность (XNOR)\n";
    cout << "Ваш выбор: "; cin >> methodChoice;

    cout << "\nВыберите способ ввода ключа: \n";
    cout << "1. Из текстового файла (8 бит)\n";
    cout << "2. Ручной ввод (минимум 3 бита)\n";
    cout << "Ваш выбор: "; cin >> keySourceChoice;


    //место для чтения файла и генерация ключа
}

int main(){
    setlocale(LC_ALL, "Russian");
    
    int choice = 0;
     while (choice != 0){
        cout <</n
     }
}