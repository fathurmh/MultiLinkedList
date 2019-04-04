// include library c++
#include <conio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// include library buatan
#include "common.h"

// using namespace
using namespace std;

// alokasi array 2 dimensi
int *Allocate(int row, int col)
{
    // instansiasi baris array
    int *arr = new int [row * col + 1];

    // kembalikan array
    return arr;
}

// dealokasi array 2 dimensi
void Deallocate(int *(&arr))
{
    // dealokasi memory baris array
    delete[] arr;
}

void Tukar(int *nilai_a, int *nilai_b)
{
    int temp = *nilai_a;
    *nilai_a = *nilai_b;
    *nilai_b = temp;
}

// prosedur menghapus text pada console
void ClearScreen()
{
    system("cls");
}

// prosedur menghapus text pada console
// https://stackoverflow.com/questions/10058050/how-to-go-up-a-line-in-console-programs-c
void RemoveLastLine()
{
    cout << "\x1b[A";
    cout << "                                                                           ";
    cout << "\r";
}

// prosedur cetak text header
void PrintHeader()
{
    ClearScreen();

    // cetak header
    cout << "============================" << endl
        << "======= NUGI BANGSAT =======" << endl
        << "============================" << endl << endl;
}

// prosedur cetak text title
void PrintTitle(const char *text)
{
    // cetak title
    printf("=== %s ===\n\n", text);
}

// prosedur cetak text failed
void Failed(const char *text)
{
    // cetak text berwarna merah
    printf("\x1B[31m%s\033[0m\n", text);
}

// prosedur cetak text success
void Success(const char *text)
{
    // cetak text berwarna hijau
    printf("\x1B[32m%s\033[0m\n", text);
}

void Success(const vector<string> &params)
{
    stringstream stream;
    for (size_t i = 0; i < params.size(); ++i)
    {
        stream << params[i];
    }

    Success(stream.str().c_str());
}

// prosedur cetak text warning
void Warning(const char *text)
{
    // cetak text berwarna jingga
    printf("\x1B[33m%s\033[0m\n", text);
}

void Warning(const vector<string> &params)
{
    stringstream stream;
    for (size_t i = 0; i < params.size(); ++i)
    {
        stream << params[i];
    }

    Warning(stream.str().c_str());
}

// prosedur cetak text information
void Information(const char *text)
{
    // cetak text berwarna biru
    printf("\x1B[34m%s\033[0m\n", text);
}

// fungsi agar input password menjadi simbol *
// http://www.cplusplus.com/articles/E6vU7k9E/
string GetPassword(const char *prompt, bool show_asterisk)
{
    const char BACKSPACE = 8;
    const char RETURN = 13;
    unsigned char ch = 0;

    string password;
    cout << prompt;

    while ((ch = getch()) != RETURN)
    {
        if (ch == BACKSPACE)
        {
            if (password.length() != 0)
            {
                if (show_asterisk)
                {
                    cout << "\b \b";
                }
                password.resize(password.length() - 1);
            }
        }
        else if (ch == 0 || ch == 224)
        {
            getch();
            continue;
        }
        else
        {
            password += ch;
            if (show_asterisk)
            {
                cout << '*';
            }
        }
    }

    cout << endl;

    return password;
}
