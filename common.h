#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

// include library c++
#include <string>

// pointer menuju data pada elemen
#define data(p) p->data
// pointer menuju elemen selanjutnya
#define next(p) p->next
// pointer menuju elemen sebelumnya
#define prev(p) p->prev
// pointer menuju elemen reviewer
#define reviewer(p) p->reviewer
// pointer menuju elemen movie
#define movie(p) p->movie
// pointer menuju elemen pertama
#define first(r) (r).first
// pointer menuju elemen terakhir
#define last(r) (r).last

// default admin username
const char ADMIN_USERNAME[] = "admin";
// default admin password
const char ADMIN_PASSWORD[] = "a";
// maksimal mengulang kesalahan input
const int MAX_RETRY_COUNT = 3;

// enum tipe login user
enum loginUser {
    // login user administrator
    Administrator,
    // login user reviewer
    Reviewer,
    // login user guest
    Guest
};

// prosedur cetak text header
void printHeader();
// prosedur cetak text title
void printTitle(const char* text);
// prosedur menghapus text pada console
void clearScreen();
// prosedur menghapus console last line
void removeLastLine();
// prosedur cetak text failed
void failed(const char* text);
// prosedur cetak text success
void success(const char* text);
// prosedur cetak text warning
void warning(const char* text);
// prosedur cetak text information
void information(const char* text);
// fungsi agar input password menjadi simbol *
std::string getPass(const char *prompt, bool show_asterisk = true);

#endif // COMMON_H_INCLUDED
