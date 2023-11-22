#include <iostream>
#include <fstream>
#include <filesystem>

std::string getCharRange(char data[], int a, int b) {
    std::string buffer = "";
    for (int i = a; i < b + 1; i++) {
        buffer += data[i];
    }
    return buffer;
}

int main (int argc, char* argv[]) {
    std::string supported[8] = {"XFBIN", "DDS", "ACF", "NUS3CONF", "ACB", "AWB", "CPK", "EXE"};
    std::cout << "!IMPORTANT - Only the following file types are known to be supported by this tool:\n";
    for (int i = 0; i < 8; i++) {
        std::cout << "\t- " << supported[i] << '\n';
    }
    std::cout << '\n';

    std::filesystem::path filePath = argv[1];
    std::string fileName = filePath.stem().string() + filePath.extension().string();

    std::ifstream input(filePath, std::ios::binary);
    char data[20];
    input.read(data, sizeof(data));

    int typeLength = 0;

    std::string fileType = getCharRange(data, 0, 1);
    if (fileType == "MZ") {
        typeLength = 2;
    }
    
    fileType = getCharRange(data, 0, 2);
    if (fileType == "DDS" || fileType == "CPK") {
        typeLength = 3;
    }
    
    fileType = getCharRange(data, 0, 3);
    if (fileType == "CRID" || fileType == "AFS2" || fileType == "NUS3" || fileType == "@UTF" || fileType == "NUCC") {
        typeLength = 4;
    }

    fileType = getCharRange(data, 0, typeLength - 1);
    if (typeLength == 0) {
        std::cout << "File \"" << fileName << "\" is encrypted.\nConsider using a different decrypter/unpacker.\n";
    } else {
        std::cout << "Package type \"" << fileType << "\" detected.\n";
        std::cout << "File \"" << fileName << "\" is not encrypted.\n";
    }

    std::cout << "\n";
    system("pause");
}