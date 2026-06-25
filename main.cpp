#include <iostream>
#include <string>

using namespace std;

//ОБЪЯВЛЕНИЕ ФУНКЦИЙ
//функции справки
void printHelp();
void printDetHelp(const string& topic);

//функции чтения с файлов
string readFile(const string& path);
string readKey(const string& path);

//функция записи в файл
void writeFile(const string& path, const string& data);

//функция генерации ключа
string generateKey (int lengh);

//функции шифрования
unsigned char encryptXOR(unsigned char textByte, unsigned char key);
unsigned char encryptXNOR(unsigned char textByte, unsigned char key);

//ГЛАВНАЯ ПРОГРАММА
int main(int argc, char* argv[]){ //main получает аргументы из консоли (количество слов и массив введенных слов)

#ifdef _WIN32
    setlocale(LC_ALL, "Russian");
    system("chcp 1251 > nul");
    system("cls");
#else
    setlocale(LC_ALL, "Russian");
#endif

    //подсказки
    if (argc == 1){
       printHelp();
       return 0;
    }
    //расширенные подсказки
    if (argc == 3 && string(argv[1]) == "-help") {
        printDetHelp(argv[2]);
        return 0;
    }

    //переменные для хранения настроек из консоли
    string sourcePath = "";//путь к исходному файлу
    string destPath = "";//путь для сохранения результата
    string method = "";//метод шифрования
    string keyString = "";//строка введеннного ключа или путь к файлу ключа
    int blockLength = 0;//для хранения длины блочного ключа

    //флаги режимов
    bool isKeyFromFile = false;//флаг - метод считывания ключа
    bool isAutoKey = false;//флаг - метод генерации ключа
    bool isBlockKey = false;//флаг - метод ключа заданной длины

    //читаем, что ввел пользователь
    //если находим флаг (например -in), берем следующее слово
    for (int i = 1; i < argc; i++){
        string arg = argv[i];//берем текущие слово из консоли

        //если нашли флаг и после него есть еще слова (защиты от выхода за пределы)
        //сохраняем данные в наши переменные
        if (arg == "-in" && i + 1 < argc) sourcePath = argv[++i];
        else if (arg == "-out" && i+1 < argc) destPath = argv[++i];
        else if (arg == "-method" && i+1 < argc) method = argv[++i];
        else if (arg == "-keyval" && i+1 < argc) { keyString = argv[++i]; isKeyFromFile = false;}
        else if (arg == "-keyfile" && i+1 < argc) {keyString = argv[++i]; isKeyFromFile = true;}
        else if (arg == "-keyauto" && i+1 < argc) {keyString = argv[++i]; isAutoKey = true;}
        else if (arg == "-keyblock" && i+2 < argc) {blockLength = stoi(argv[++i]); keyString = argv[++i]; isBlockKey = true;}
    }

    //проверка: нет ли пустой строки
    if (sourcePath.empty() || destPath.empty() || method.empty() || keyString.empty()){
        cout <<"Ошибка: Переданы не все параметры!\n";
        return 1;
    }

    //читаем исходный файл
    string originalText = readFile(sourcePath);//читаем файл в бинарном режиме
    if (originalText.empty()){
        cout << "Ошибка: Исходный файл пуст или не найден\n"; 
        return 1;
    }

    //получаем ключ
    string finalKey;
    if (isAutoKey) {//режим шифра длина ключа = длине файла
        int neededBits = originalText.length() * 8;
        cout << "Генерация уникального ключа на " << neededBits << " бит...\n";
        finalKey = generateKey(neededBits);
        writeFile(keyString, finalKey);
        cout << "Ключ сохранен в файл: " << keyString <<"\n";
    }

    else if (isBlockKey){
        if (blockLength % 8 != 0){
            cout << "Ошибка: Длина блочного ключа должна быть кратна 8!\n";
            return 1;
        }
        cout << "Генерация блочного ключа на " << blockLength << " бит...\n";
        finalKey = generateKey(blockLength);
        writeFile(keyString, finalKey);
        cout << "Ключ сохранен в файл: " << keyString <<"\n";
        }

    else if (isKeyFromFile){//если выбрано чтение ключа из файла
        finalKey = readKey(keyString); //читаем 8 битный ключ из файла
    }
    else {//иначе в переменной kyeString уже лежит введенный ключ
        finalKey = keyString; //берем ключ, который ввели вручную
    }

    //ОСНОВНАЯ РАБОТА ПРОГРАММЫ
    //шифрование и расшифрование
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