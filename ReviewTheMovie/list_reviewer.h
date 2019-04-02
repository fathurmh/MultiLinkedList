#ifndef LIST_REVIEWER_H_INCLUDED
#define LIST_REVIEWER_H_INCLUDED

// include library c++
#include <string>

// using namespace
using namespace std;

// pointer alamat memory reviewer
typedef struct ElementReviewer *AddressReviewer;

// tipe bentukan data reviewer
struct Reviewer
{
    int id;
    string name;
    string username;
    string password;
};

// tipe bentukan elemen reviewer
struct ElementReviewer
{
    // variabel data reviewer pada elemen saat ini
    Reviewer data;
    // pointer menuju elemen sebelumnya
    AddressReviewer prev;
    // pointer menuju elemen selanjutnya
    AddressReviewer next;
};

// tipe bentukan list reviewer
struct ListReviewer
{
    // pointer menuju elemen pertama pada list
    AddressReviewer first;
    // pointer menuju elemen terakhir pada list
    AddressReviewer last;
};

// prosedur membuat list baru
void CreateList(ListReviewer &list_reviewer);
// fungsi membuat data reviewer
Reviewer CreateReviewer(string name, string username, string password);

// fungsi alokasi reviewer
AddressReviewer Allocate(Reviewer reviewer);
// fungsi dealokasi
void Deallocate(AddressReviewer &address_reviewer);

// prosedur insert first reviewer
void InsertFirst(ListReviewer &list_reviewer, AddressReviewer address_reviewer);
// prosedur insert last reviewer
void InsertLast(ListReviewer &list_reviewer, AddressReviewer address_reviewer);

// prosedur update reviewer
void UpdateReviewer(AddressReviewer address_reviewer, string new_name, string new_username, string new_password);

// prosedur delete first reviewer
void DeleteFirst(ListReviewer &list_reviewer);
// prosedur delete last reviewer
void DeleteLast(ListReviewer &list_reviewer);
// prosedur delete reviewer
void DeleteReviewer(ListReviewer &list_reviewer, AddressReviewer address_reviewer);

// fungsi cari reviewer by username pada list
AddressReviewer FindByUsername(ListReviewer &list_reviewer, string username);
// fungsi cari reviewer by id pada list
AddressReviewer FindById(ListReviewer &list_reviewer, int id);

// fungsi hitung total elemen pada list
int Count(ListReviewer list_reviewer);

// prosedur cetak data reviewer
void Cetak(AddressReviewer address_reviewer);
// prosedur cetak list data reviewer
void Cetak(ListReviewer list_reviewer);

#endif // LIST_REVIEWER_H_INCLUDED
