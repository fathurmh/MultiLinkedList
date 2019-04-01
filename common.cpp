// include library c++
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <string>

// prosedur menghapus text pada console
void clearScreen() {
    system("cls");
}

// prosedur menghapus text pada console
// https://stackoverflow.com/questions/10058050/how-to-go-up-a-line-in-console-programs-c
void removeLastLine() {
    std::cout << "\x1b[A";
}

// prosedur cetak text header
void printHeader() {
    clearScreen();

    // cetak header
    std::cout << "============================" << std::endl
              << "======= NUGI BANGSAT =======" << std::endl
              << "============================" << std::endl << std::endl;
}

// prosedur cetak text title
void printTitle(const char* text) {
    // cetak title
    printf("=== %s ===\n\n", text);
}

// prosedur cetak text failed
void failed(const char* text) {
    // cetak text berwarna merah
    printf("\x1B[31m%s\033[0m\n", text);
}

// prosedur cetak text success
void success(const char* text) {
    // cetak text berwarna hijau
    printf("\x1B[32m%s\033[0m\n", text);
}

// prosedur cetak text warning
void warning(const char* text) {
    // cetak text berwarna jingga
    printf("\x1B[33m%s\033[0m\n", text);
}

// prosedur cetak text information
void information(const char* text) {
    // cetak text berwarna biru
    printf("\x1B[34m%s\033[0m\n", text);
}

// fungsi agar input password menjadi simbol *
// http://www.cplusplus.com/articles/E6vU7k9E/
std::string getPass(const char *prompt, bool show_asterisk = true) {
    const char BACKSPACE = 8;
    const char RETURN = 13;
    unsigned char ch=0;

    std::string password;
    std::cout << prompt;

    while((ch = getch()) != RETURN) {
        if(ch == BACKSPACE) {
            if(password.length() != 0) {
                if(show_asterisk) {
                    std::cout << "\b \b";
                }
                password.resize(password.length() - 1);
            }
        } else if(ch == 0 || ch == 224) {
            getch();
            continue;
        } else {
            password += ch;
            if(show_asterisk) {
                std::cout << '*';
            }
        }
    }

    std::cout << std::endl;

    return password;
}
