#include <iostream>
#include <string>

using namespace std;

//ОБЪЯВЛЕНИЕ ФУНКЦИЙ
//функции чтения с файлов
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

//ГЛАВНАЯ ПРОГРАММА
int main(int argc, char* argv[]){ //main получает аргументы из консоли (количество слов и массив введенных слов)

    setlocale(LC_ALL, "Russian");
    system("chcp 1251 > nul"); //кодировка в консоли для винды
    system("cls");

    //подсказки
    if (argc == 1){
        cout << "Использование программы:\n";
        cout << "./cipher -in <файл> -out <запись_результата> -method <xor|xnor> -keyval <ключ_вручную>\n";
        cout << "ИЛИ\n";
        cout << "./cipher -in <файл> -out <запись_результата> -method <xor|xnor> -keyfile <файл_с_ключом>\n";
        return 0;
    }

    //переменные для хранения настроек из консоли
    string sourcePath = "";//путь к исходному файлу
    string destPath = "";//путь для сохранения результата
    string method = "";//метод шифрования
    string keyString = "";//строка введеннного ключа или путь к файлу ключа
    bool isKeyFromFile = false;//флаг - метод считывания ключа

    //читаем, что ввел пользователь
    //если находим флаг (например -in), берем следующее слово
    for (int i = 1; i < argc; i++){
        string arg = argv[i];//берем текущие слово из консоли

        //если нашли флаг и после него есть еще слова (защиты от выхода за пределы)
        //сохраняем данные в наши переменные
        if (arg == "-in" && i + 1 < argc) sourcePath = argv[++i];
        else if (arg == "-out" && i+1 < argc) destPath = argv[++i];
        else if (arg == "-method" && i+1 < argc) method = argv[++i];
        else if (arg == "-keyval" && i+1 < argc){ keyString = argv[++i]; isKeyFromFile = false;}
        else if (arg == "-keyfile" && i+1 < argc){keyString = argv[++i]; isKeyFromFile = true;}
    }

    //проверка: нет ли пустой строки
    if (sourcePath.empty() || destPath.empty() || method.empty() || keyString.empty()){
        cout <<"Ошибка: Переданы не все параметры!\n";
        return 1;
    }

    //ОСНОВНАЯ РАБОТА ПРОГРАММЫ
    //полуаем ключ
    string finalKey;
    if (isKeyFromFile){//если выбрано чтение ключа из файла
        finalKey = readKey(keyString); //читаем 8 битный ключ из файла
    } else {//иначе в переменной kyeString уже лежит введенный ключ
        finalKey = keyString; //берем ключ, который ввели вручную
    }

    //читаем исходный файл
    string originalText = readFile(sourcePath);//читаем файл в бинарном режиме
    if (originalText.empty()){
        cout << "Ошибка: Исходный файл пуст или не найден"; return 1;
    }

    //шифрование и дешифрование
    string resultText = "";//сюда собирается по частям зашифрованный текст
    int keyLength = finalKey.length();//узнаем длину ключа
    int bitPosition = 0; //счетчик для отслеживания текущего бита

    cout << "Процесс запущен...\n";

    //проход по каждому символу в исходном тексте
    for (size_t i = 0; i < originalText.length(); i++){ //size_t, чтобы избежать пеерполнения int
        //берем один байт текста, unsigned чтобы получить символы от 0 до 255 без знака
        unsigned char textByte = originalText[i];

        //формируем 8 битовый ключ для текущего символа
        string currentKeyBits = "";
        for (int j = 0; j < 8; j++){ //остаток от деления заставляет индекс бегать по кругу ключа
            currentKeyBits += finalKey[bitPosition % keyLength];
            bitPosition++;//сдвигаем счетчик на 1 бит вперед
        }
        //переводим 8 нулей и единиц в настоящий байт
        unsigned char keyByte = (unsigned char)stoi(currentKeyBits, nullptr, 2);

        unsigned char encryptedByte;//переменная для хранения итога
        if (method == "xor"){
            encryptedByte = encryptXOR(textByte, keyByte);
        } else if (method == "xnor"){
            encryptedByte = encryptXNOR(textByte, keyByte);
        } else {
            cout << "Неизвестный метод!"; return 1;
        }
        //приклеиваем зашифрованный или расшифрованный байт к итоговой строке
        resultText += encryptedByte;
    }
    //сохраняем результат в файл
    writeFile(destPath, resultText);//побайтовая запись в файл
    cout << "Успешно! Результат сохранен в файл: " << destPath << "\n";

}