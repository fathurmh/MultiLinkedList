// include library c++
#include <conio.h>
#include <iostream>
#include <string>

// include library buatan
#include "common.h"
#include "list_reviewer.h"

// using namespace
using namespace std;

// prosedur membuat list baru
void CreateList(ListReviewer &list_reviewer)
{
    // inisialisasi elemen pertama dengan null
    FIRST(list_reviewer) = NULL;
    // inisialisasi elemen terakhir dengan null
    LAST(list_reviewer) = NULL;
}

// fungsi membuat data reviewer
Reviewer CreateReviewer(string name, string username, string password)
{
    // inisialisasi id static agar otomatis bertambah saat membuat reviewer baru
    static int id = 0;

    // deklarasi variabel data reviewer
    Reviewer new_reviewer;

    // inisialisasi variabel data reviewer
    new_reviewer.id = ++id;
    new_reviewer.name = name;
    new_reviewer.username = username;
    new_reviewer.password = password;

    // kembalikan reviewer
    return new_reviewer;
}

// fungsi alokasi reviewer
AddressReviewer Allocate(Reviewer reviewer)
{
    // instansiasi pointer
    AddressReviewer address_reviewer = new ElementReviewer();

    // inisialisasi data pada pointer dengan parameter reviewer
    DATA(address_reviewer) = reviewer;
    // inisialisasi pointer menuju elemen selanjutnya dengan null
    NEXT(address_reviewer) = NULL;
    // inisialisasi pointer menuju elemen sebelumnya dengan null
    PREV(address_reviewer) = NULL;

    // kembalikan pointer
    return address_reviewer;
}

// fungsi dealokasi
void Deallocate(AddressReviewer &address_reviewer)
{
    // hapus memory
    delete address_reviewer;
}

// prosedur insert first reviewer
void InsertFirst(ListReviewer &list_reviewer, AddressReviewer address_reviewer)
{
    // pengecekan jika list masih kosong
    if (FIRST(list_reviewer) == NULL && LAST(list_reviewer) == NULL)
    {
        // inisialisasi elemen pertama dengan pointer reviewer baru
        FIRST(list_reviewer) = address_reviewer;
        // inisialisasi elemen terakhir dengan pointer reviewer baru
        LAST(list_reviewer) = address_reviewer;
    }
    else
    {
        // inisialisasi variabel first_reviewer dengan elemen pertama pada list
        AddressReviewer first_reviewer = FIRST(list_reviewer);
        // inisialisasi pointer reviewer baru menuju elemen selanjutnya dengan elemen pertama pada list
        NEXT(address_reviewer) = first_reviewer;
        // inisialisasi pointer reviewer baru menuju elemen sebelumnya dengan null
        PREV(address_reviewer) = NULL;
        // inisialisasi pointer menuju elemen sebelumnya pada first_reviewer dengan pointer reviewer baru
        PREV(first_reviewer) = address_reviewer;
        // inisialisasi elemen pertama pada list dengan pointer reviewer baru
        FIRST(list_reviewer) = address_reviewer;
    }
}

// prosedur insert last reviewer
void InsertLast(ListReviewer &list_reviewer, AddressReviewer address_reviewer)
{
    // pengecekan jika list masih kosong
    if (FIRST(list_reviewer) == NULL && LAST(list_reviewer) == NULL)
    {
        // jika list kosong maka insert first
        InsertFirst(list_reviewer, address_reviewer);
    }
    else
    {
        // inisialisasi variabel last_reviewer dengan elemen terakhir pada list
        AddressReviewer last_reviewer = LAST(list_reviewer);
        // inisialisasi pointer reviewer baru menuju elemen sebelumnya dengan elemen terakhir pada list
        PREV(address_reviewer) = last_reviewer;
        // inisialisasi pointer reviewer baru menuju elemen selanjutnya dengan null
        NEXT(address_reviewer) = NULL;
        // inisialisasi pointer menuju elemen selanjutnya pada last_reviewer dengan pointer reviewer baru
        NEXT(last_reviewer) = address_reviewer;
        // inisialisasi elemen terakhir pada list dengan pointer reviewer baru
        LAST(list_reviewer) = address_reviewer;
    }
}

// prosedur update reviewer
void UpdateReviewer(AddressReviewer address_reviewer, string new_name, string new_username, string new_password)
{
    // cek jika address_reviewer kosong
    if (address_reviewer == NULL)
    {
        Warning("Tidak ada data.");
        getch();
    }
    else
    {
        // cek jika variabel baru tidak kosong
        if (!new_name.empty())
        {
            // jika tidak kosong maka update datanya
            DATA(address_reviewer).name = new_name;
        }

        if (!new_username.empty())
        {
            DATA(address_reviewer).username = new_username;
        }

        if (!new_password.empty())
        {
            DATA(address_reviewer).password = new_password;
        }
    }
}

// prosedur delete first reviewer
void DeleteFirst(ListReviewer &list_reviewer)
{
    // cek jika elemen pertama null (list kosong)
    if (FIRST(list_reviewer) == NULL && LAST(list_reviewer) == NULL)
    {
        Warning("Tidak ada data.");
        getch();
    }
    else
    {
        // inisialisasi first_reviewer
        AddressReviewer first_reviewer = FIRST(list_reviewer);

        // jika list hanya mempunyai satu elemen
        if (NEXT(first_reviewer) == NULL)
        {
            // delete
            FIRST(list_reviewer) = NULL;
            LAST(list_reviewer) = NULL;
        }
        else
        {
            // inisialisasi elemen pertama dengan elemen selanjutnya dari reviewer yang akan dihapus
            FIRST(list_reviewer) = NEXT(first_reviewer);
            // inisialisasi elemen sebelumnya dari elemen pertama yang baru dengan null
            PREV(FIRST(list_reviewer)) = NULL;
        }

        // dealokasi elemen pertama
        Deallocate(first_reviewer);
    }
}

// prosedur delete last reviewer
void DeleteLast(ListReviewer &list_reviewer)
{
    // cek jika elemen pertama null (list kosong)
    if (FIRST(list_reviewer) == NULL && LAST(list_reviewer) == NULL)
    {
        Warning("Tidak ada data.");
        getch();
    }
    else
    {
        // inisialisasi last_reviewer
        AddressReviewer last_reviewer = LAST(list_reviewer);

        // jika list hanya mempunyai satu elemen
        if (PREV(last_reviewer) == NULL)
        {
            // delete
            FIRST(list_reviewer) = NULL;
            LAST(list_reviewer) = NULL;
        }
        else
        {
            // inisialisasi elemen terakhir dengan elemen sebelumnya dari reviewer yang akan dihapus
            LAST(list_reviewer) = PREV(last_reviewer);
            // inisialisasi elemen selanjutnya dari elemen terakhir yang baru dengan null
            NEXT(LAST(list_reviewer)) = NULL;
        }

        // dealokasi elemen terakhir
        Deallocate(last_reviewer);
    }
}

// prosedur delete reviewer
void DeleteReviewer(ListReviewer &list_reviewer, AddressReviewer address_reviewer)
{
    // cek jika list kosong
    if (FIRST(list_reviewer) == NULL && LAST(list_reviewer) == NULL)
    {
        Warning("Tidak ada data.");
        getch();
    }
    else if (address_reviewer != NULL)
    {
        // inisialisasi first_reviewer
        AddressReviewer first_reviewer = FIRST(list_reviewer);
        // inisialisasi last_movie
        AddressReviewer last_movie = LAST(list_reviewer);

        // jika elemen yang dihapus adalah elemen pertama
        if (address_reviewer == first_reviewer)
        {
            // delete first
            DeleteFirst(list_reviewer);
        }
        else if (address_reviewer == last_movie)
        {
            // delete last
            DeleteLast(list_reviewer);
        }
        else
        {
            // inisialisasi elemen selanjutnya dari elemen sebelumnya dari reviewer yang akan dihapus dengan elemen selanjutnya dari movie yang akan dihapus
            NEXT(PREV(address_reviewer)) = NEXT(address_reviewer);
            // inisialisasi elemen sebelumnya dari elemen selanjutnya dari reviewer yang akan dihapus dengan elemen sebelumnya dari movie yang akan dihapus
            PREV(NEXT(address_reviewer)) = PREV(address_reviewer);

            Deallocate(address_reviewer);
        }
    }
}

// fungsi cari reviewer by username pada list
AddressReviewer FindByUsername(ListReviewer &list_reviewer, string username)
{
    // inisialisasi variabel ketemu
    bool ketemu = false;

    // inisialisasi variabel data_ketemu dengan null
    AddressReviewer data_ketemu = NULL;

    // inisialisasi variabel current dengan elemen pertama pada list
    AddressReviewer current = FIRST(list_reviewer);

    // loop selama tidak ketemu dan current tidak sama dengan null
    while (!ketemu && current != NULL)
    {
        // jika username current sama dengan parameter username maka ketemu
        if (DATA(current).username == username)
        {
            ketemu = true;
            data_ketemu = current;
        }
        // variabel current diisi dengan elemen selanjutnya
        current = NEXT(current);
    }

    // kembalikan data
    return data_ketemu;
}

// fungsi cari reviewer by id pada list
AddressReviewer FindById(ListReviewer &list_reviewer, int id)
{
    // inisialisasi variabel ketemu
    bool ketemu = false;

    // inisialisasi variabel data_ketemu dengan null
    AddressReviewer data_ketemu = NULL;

    // inisialisasi variabel current dengan elemen pertama pada list
    AddressReviewer current = FIRST(list_reviewer);

    // loop selama tidak ketemu dan current tidak sama dengan null
    while (!ketemu && current != NULL)
    {
        // jika username current sama dengan parameter username maka ketemu
        if (DATA(current).id == id)
        {
            ketemu = true;
            data_ketemu = current;
        }
        // variabel current diisi dengan elemen selanjutnya
        current = NEXT(current);
    }

    // kembalikan data
    return data_ketemu;
}

// fungsi hitung total elemen pada list
int Count(ListReviewer list_reviewer)
{
    // inisialisasi count
    int count = 0;

    // inisialisasi variabel current dengan elemen pertama pada list
    AddressReviewer current = FIRST(list_reviewer);

    // hitung selama current tidak sama dengan null
    while (current != NULL)
    {
        count++;
        current = NEXT(current);
    }

    // kembalikan hasil hitung
    return count;
}

// prosedur cetak data reviewer
void Cetak(AddressReviewer address_reviewer)
{
    // cetak data reviewer
    cout << "ID      : " << DATA(address_reviewer).id << endl
        << "Nama    : " << DATA(address_reviewer).name << endl
        << "Username: " << DATA(address_reviewer).username << endl << endl;
}

// prosedur cetak list data reviewer
void Cetak(ListReviewer list_reviewer)
{
    // inisialisasi count
    int count = 0;

    // inisialisasi variabel current dengan elemen pertama pada list
    AddressReviewer current = FIRST(list_reviewer);

    PrintTitle("VIEW LIST REVIEWER");

    if (current == NULL)
    {
        // cetak info tidak ada data
        Warning("Tidak ada data.");
        getch();
    }
    else
    {
        // loop cetak reviewer dalam list
        while (current != NULL)
        {
            // cetak reviewer
            Cetak(current);

            // next current
            current = NEXT(current);
            count++;
        }

        // cetak total reviewer
        cout << "Total Reviewer: " << count << endl;
    }
}