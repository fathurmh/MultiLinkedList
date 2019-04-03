#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

// include library c++
#include <string>

// using namespace
using namespace std;

// DEFINE MACRO FUNCTION

// pointer menuju data pada elemen
#define DATA(p) p->data
// pointer menuju elemen selanjutnya
#define NEXT(p) p->next
// pointer menuju elemen sebelumnya
#define PREV(p) p->prev
// pointer menuju elemen pertama
#define FIRST(r) (r).first
// pointer menuju elemen terakhir
#define LAST(r) (r).last

#define getch() _getch()

// default admin username
const char ADMIN_USERNAME[] = "admin";
// default admin password
const char ADMIN_PASSWORD[] = "a";
// maksimal mengulang kesalahan input
const int MAX_RETRY_COUNT = 3;

// enum tipe login user
enum LoginUser {
    // login user guest
    GUEST,
    // login user administrator
    ADMINISTRATOR,
    // login user reviewer
    REVIEWER
};

// alokasi array 2 dimensi
int **Allocate(int row, int col);
// dealokasi array 2 dimensi
void Deallocate(int **arr);

// prosedur tukar nilai
void Tukar(int *nilai_a, int *nilai_b);

// prosedur menghapus text pada console
void ClearScreen();
// prosedur menghapus console last line
void RemoveLastLine();

// prosedur cetak text header
void PrintHeader();
// prosedur cetak text title
void PrintTitle(const char* text);
// prosedur cetak text failed
void Failed(const char* text);
// prosedur cetak text success
void Success(const char* text);
// prosedur cetak text warning
void Warning(const char* text);
// prosedur cetak text information
void Information(const char* text);

// fungsi agar input password menjadi simbol *
string GetPassword(const char *prompt, bool show_asterisk = true);

#endif // COMMON_H_INCLUDED
