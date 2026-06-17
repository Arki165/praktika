#include <iostream>
#include <string>

using namespace std;

//объявляй функции здесь
string readFile(const string& path);
string readKey(const string& path);
//конеу объявления функций


//функции шифрования и ключей

//конец функций шифрования и ключей

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "Russian");
    
    if (argc ==1){
        cout << "Использование программы:\n";
        cout << "./cipher -in <файл> -out <запись_результата> -method <xor|xnor> -keyval <ключ_вручную>\n";
        cout << "ИЛИ\n";
        cout << "./cipher -in <файл> -out <запись_результата> -method <xor|xnor> -keyfile <файл_с_ключом>\n";
        return 0;
    }

    //переменные для хранения хранения натсроек из консоли
    string sourcePath = "";
    string destPath = "";
    string method = "";
    string keyString = "";
    bool isKeyFromFile = false;

    //читаем, что ввел пользователь
    for (int i = 1; i < argc; i++){
        string arg = argv[i];

        if (arg == "-in" && i + 1 < argc) sourcePath = argv[++i];
        else if (arg == "-out" && i+1 < argc) destPath = argv[++i];
        else if (arg == "-method" && i+1 < argc) method = argv[++i];
        else if (arg == "-keyval" && i+1 < argc){ keyString = argv[++i]; isKeyFromFile = false;
    }
    else if (arg == "-keyfile" && i+1 < argc){
        keyString = argv[++i]; isKeyFromFile = true;
        }
    }

    //проверка все ли введено
    if (sourcePath.empty() || destPath.empty() || method.empty() || keyString.empty()){
        cout <<"Ошибка: Переданы не все параметры!\n";
        return 1;
    }

    //основная работа
    //полуаем ключ
    string finalKey;
    if (isKeyFromFile){
        finalKey = readKey(keyString); //читаем 8 битный ключ из файла
    } else {
        finalKey = keyString; //юерем ключ, который ввели вручную
    }

    //читаем исходный файл
    string originalText = readFile(sourcePath);
    if (originalText.empty()){
        cout << "Ошибка: Исходный файл пуст или не найден"; return 1;
    }

    //шифрование и дешифрование
    

    
}