#include <iostream>
#include <string>

using namespace std;

//функции ятения с файлов здесь
string readFile(const string& path);
string readKey(const string& path);
//конец функций чтения

//функция записи в файл
void writeFile(const string& path, const string& data);
//конец функции записи в файл

//функции шифрования
unsigned char encryptXOR(unsigned char textByte, unsigned char key);
unsigned char encryptXNOR(unsigned char textByte, unsigned char key);
//конец функций шифрования

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
    string resultText = "";
    int keyLength = finalKey.length();
    int bitPosition = 0; //счетчик для нарезки ключа

    cout << "Процесс запущен...\n";

    //проход по каждому символу
    for (size_t i = 0; i < originalText.length(); i++){
        unsigned char textByte = originalText[i];

        //формируем 8 битовый ключ для текущего символа
        string currentKeyBits = "";
        for (int j = 0; j < 8; j++){
            currentKeyBits += finalKey[bitPosition % keyLength];
            bitPosition++;
        }
        //переводим 8 нулей и единиц в настоящий байт
        unsigned char keyByte = (unsigned char)stoi(currentKeyBits, nullptr, 2);

        unsigned char encryptedByte;
        if (method == "xor"){
            encryptedByte = encryptXOR(textByte, keyByte);
        } else if (method == "xnor"){
            encryptedByte = encryptXNOR(textByte, keyByte);
        } else {
            cout << "Неизвестный метод!"; return 1;
        }
        //добавляем результат
        resultText += encryptedByte;
    }
    //сохраняем в файл
    writeFile(destPath, resultText);
    cout << "Успешно! Результат сохранен в файл: " << destPath << "\n";

}