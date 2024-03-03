#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

vector<unsigned char> Encode(vector<unsigned char> text, string key) {
    vector<unsigned char> code;
    for (int i = 0; i < text.size(); i++) {
        int index = (text[i] + key[i % key.length()]) % 256;
        code.push_back(index);
    }
    return code;
}

vector<unsigned char> Decode(vector<unsigned char> text, string key) {
    vector<unsigned char> code;
    for (int i = 0; i < text.size(); i++) {
        int index = (text[i] - key[i % key.length()] + 256) % 256;
        code.push_back(index);
    }
    return code;
}

int main(int argc, char** argv) {
    string action, inputnamefile, outputnamefile, key;
    ifstream inputfile;
    ofstream outputfile;
    vector<unsigned char> input, output;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc != 5) {
        cout << "Неправильно введены данные" << endl;
        return 1;
    }

    action = argv[1];
    inputnamefile = argv[2];
    outputnamefile = argv[3];
    key = argv[4];

    inputfile.open(inputnamefile, ios_base::binary);
    if (!inputfile.is_open()) {
        cout << "Ошибка открытия входного файла" << endl;
        return 1;
    }

    outputfile.open(outputnamefile, ios_base::binary);
    if (!outputfile.is_open()) {
        cout << "Ошибка открытия выходного файла" << endl;
        return 1;
    }

    if (action.compare("encode") == 0) {
        while (inputfile.good()) {
            char ch;
            inputfile.read(&ch, sizeof(ch));
            input.push_back(ch);
        }
        output = Encode(input, key);
        outputfile.write((char*)output.data(), output.size());
    }
    else if (action.compare("decode") == 0) {
        while (inputfile.good()) {
            char ch;
            inputfile.read(&ch, sizeof(ch));
            input.push_back(ch);
        }
        output = Decode(input, key);
        outputfile.write((char*)output.data(), output.size());
    }
    else {
        cout << "Неправильная команда" << endl;
        return 1;
    }

    return 0;
}