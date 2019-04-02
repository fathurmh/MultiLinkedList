// include library c++
#include <conio.h>
#include <iostream>
#include <string>

// include library buatan
#include "common.h"

// using namespace
using namespace std;

// alokasi array
int *AllocateArray(int size)
{
    // alokasi array
    int *arr = new int[size];

    // semua array diisi 0
    for (int i = 0; i < size; i++)
        arr[i] = 0;

    // kembalikan array
    return arr;
}

// dealokasi array
void DeallocateArray(int &array)
{
    // hapus memory
    delete[] & array;
}

// prosedur menghapus text pada console
void ClearScreen() {
    system("cls");
}

// prosedur menghapus text pada console
// https://stackoverflow.com/questions/10058050/how-to-go-up-a-line-in-console-programs-c
void RemoveLastLine() {
    std::cout << "\x1b[A";
}

// prosedur cetak text header
void PrintHeader() {
    ClearScreen();

    // cetak header
    std::cout << "============================" << std::endl
              << "======= NUGI BANGSAT =======" << std::endl
              << "============================" << std::endl << std::endl;
}

// prosedur cetak text title
void PrintTitle(const char* text) {
    // cetak title
    printf("=== %s ===\n\n", text);
}

// prosedur cetak text failed
void Failed(const char* text) {
    // cetak text berwarna merah
    printf("\x1B[31m%s\033[0m\n", text);
}

// prosedur cetak text success
void Success(const char* text) {
    // cetak text berwarna hijau
    printf("\x1B[32m%s\033[0m\n", text);
}

// prosedur cetak text warning
void Warning(const char* text) {
    // cetak text berwarna jingga
    printf("\x1B[33m%s\033[0m\n", text);
}

// prosedur cetak text information
void Information(const char* text) {
    // cetak text berwarna biru
    printf("\x1B[34m%s\033[0m\n", text);
}

// fungsi agar input password menjadi simbol *
// http://www.cplusplus.com/articles/E6vU7k9E/
std::string GetPass(const char *prompt, bool show_asterisk) {
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
