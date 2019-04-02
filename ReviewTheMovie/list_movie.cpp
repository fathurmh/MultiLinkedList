// include library c++
#include <conio.h>
#include <iostream>
#include <string>

// include library buatan
#include "common.h"
#include "list_movie.h"

// using namespace
using namespace std;

// prosedur membuat list baru
void CreateList(ListMovie &list_movie)
{
    // inisialisasi elemen pertama dengan null
    FIRST(list_movie) = NULL;
    // inisialisasi elemen terakhir dengan null
    LAST(list_movie) = NULL;
}

// fungsi membuat data movie
Movie CreateMovie(string title, string director, string actors, string genre, string running_time, string release_date)
{
    // inisialisasi id static agar otomatis bertambah saat membuat movie baru
    static int id = 5;

    // deklarasi variabel data movie
    Movie movie;

    // inisialisasi variabel data movie
    movie.id = ++id;
    movie.title = title;
    movie.director = director;
    movie.actors = actors;
    movie.genre = genre;
    movie.running_time = running_time;
    movie.release_date = release_date;

    // kembalikan movie
    return movie;
}

// fungsi alokasi movie
AddressMovie Allocate(Movie movie)
{
    // instansiasi pointer
    AddressMovie address_movie = new ElementMovie();

    // inisialisasi data pada pointer dengan parameter movie
    DATA(address_movie) = movie;
    // inisialisasi pointer menuju elemen selanjutnya dengan null
    NEXT(address_movie) = NULL;
    // inisialisasi pointer menuju elemen sebelumnya dengan null
    PREV(address_movie) = NULL;

    // kembalikan pointer
    return address_movie;
}

// fungsi dealokasi
void Deallocate(AddressMovie &address_movie)
{
    // hapus memory
    delete address_movie;
}

// prosedur insert first movie
void InsertFirst(ListMovie &list_movie, AddressMovie address_movie)
{
    // pengecekan jika list masih kosong
    if (FIRST(list_movie) == NULL && LAST(list_movie) == NULL)
    {
        // inisialisasi elemen pertama dengan pointer movie baru
        FIRST(list_movie) = address_movie;
        // inisialisasi elemen terakhir dengan pointer movie baru
        LAST(list_movie) = address_movie;
    }
    else
    {
        // inisialisasi variabel first_movie dengan elemen pertama pada list
        AddressMovie first_movie = FIRST(list_movie);
        // inisialisasi pointer movie baru menuju elemen selanjutnya dengan elemen pertama pada list
        NEXT(address_movie) = first_movie;
        // inisialisasi pointer movie baru menuju elemen sebelumnya dengan null
        PREV(address_movie) = NULL;
        // inisialisasi pointer menuju elemen sebelumnya pada first_movie dengan pointer movie baru
        PREV(first_movie) = address_movie;
        // inisialisasi elemen pertama pada list dengan pointer movie baru
        FIRST(list_movie) = address_movie;
    }
}

// prosedur insert last movie
void InsertLast(ListMovie &list_movie, AddressMovie address_movie)
{
    // pengecekan jika list masih kosong
    if (FIRST(list_movie) == NULL && LAST(list_movie) == NULL)
    {
        // jika list kosong maka insert first
        InsertFirst(list_movie, address_movie);
    }
    else
    {
        // inisialisasi variabel last_movie dengan elemen terakhir pada list
        AddressMovie last_movie = LAST(list_movie);
        // inisialisasi pointer movie baru menuju elemen sebelumnya dengan elemen terakhir pada list
        PREV(address_movie) = last_movie;
        // inisialisasi pointer movie baru menuju elemen selanjutnya dengan null
        NEXT(address_movie) = NULL;
        // inisialisasi pointer menuju elemen selanjutnya pada last_movie dengan pointer movie baru
        NEXT(last_movie) = address_movie;
        // inisialisasi elemen terakhir pada list dengan pointer movie baru
        LAST(list_movie) = address_movie;
    }
}

// prosedur update movie
void UpdateMovie(AddressMovie address_movie, string new_title, string new_director, string new_actors, string new_genre, string new_running_time, string new_release_date)
{
    // cek jika address_movie kosong
    if (address_movie == NULL)
    {
        Warning("Tidak ada data.");
        getch();
    }
    else
    {
        // cek jika variabel baru tidak kosong
        if (!new_title.empty())
        {
            // jika tidak kosong maka update datanya
            DATA(address_movie).title = new_title;
        }

        if (!new_director.empty())
        {
            DATA(address_movie).director = new_director;
        }

        if (!new_actors.empty())
        {
            DATA(address_movie).actors = new_actors;
        }

        if (!new_genre.empty())
        {
            DATA(address_movie).genre = new_genre;
        }

        if (!new_running_time.empty())
        {
            DATA(address_movie).running_time = new_running_time;
        }

        if (!new_release_date.empty())
        {
            DATA(address_movie).release_date = new_release_date;
        }
    }
}

// prosedur delete first movie
void DeleteFirst(ListMovie &list_movie)
{
    // cek jika elemen pertama null (list kosong)
    if (FIRST(list_movie) == NULL && LAST(list_movie) == NULL)
    {
        Warning("Tidak ada data.");
        getch();
    }
    else
    {
        // inisialisasi first_movie
        AddressMovie first_movie = FIRST(list_movie);

        // jika list hanya mempunyai satu elemen
        if (NEXT(first_movie) == NULL)
        {
            // delete
            FIRST(list_movie) = NULL;
            LAST(list_movie) = NULL;
        }
        else
        {
            // inisialisasi elemen pertama dengan elemen selanjutnya dari movie yang akan dihapus
            FIRST(list_movie) = NEXT(first_movie);
            // inisialisasi elemen sebelumnya dari elemen pertama yang baru dengan null
            PREV(FIRST(list_movie)) = NULL;
        }

        // dealokasi elemen pertama
        Deallocate(first_movie);
    }
}

// prosedur delete last movie
void DeleteLast(ListMovie &list_movie)
{
    // cek jika elemen pertama null (list kosong)
    if (FIRST(list_movie) == NULL && LAST(list_movie) == NULL)
    {
        Warning("Tidak ada data.");
        getch();
    }
    else
    {
        // inisialisasi last_movie
        AddressMovie last_movie = LAST(list_movie);

        // jika list hanya mempunyai satu elemen
        if (PREV(last_movie) == NULL)
        {
            // delete
            FIRST(list_movie) = NULL;
            LAST(list_movie) = NULL;
        }
        else
        {
            // inisialisasi elemen terakhir dengan elemen sebelumnya dari movie yang akan dihapus
            LAST(list_movie) = PREV(last_movie);
            // inisialisasi elemen selanjutnya dari elemen terakhir yang baru dengan null
            NEXT(LAST(list_movie)) = NULL;
        }

        // dealokasi elemen terakhir
        Deallocate(last_movie);
    }
}

// prosedur delete movie
void DeleteMovie(ListMovie &list_movie, AddressMovie address_movie)
{
    // cek jika list kosong
    if (FIRST(list_movie) == NULL && LAST(list_movie) == NULL)
    {
        Warning("Tidak ada data.");
        getch();
    }
    else if (address_movie != NULL)
    {
        // inisialisasi first_movie
        AddressMovie first_movie = FIRST(list_movie);
        // inisialisasi last_movie
        AddressMovie last_movie = LAST(list_movie);

        // jika elemen yang dihapus adalah elemen pertama
        if (address_movie == first_movie)
        {
            // delete first
            DeleteFirst(list_movie);
        }
        else if (address_movie == last_movie)
        {
            // delete last
            DeleteLast(list_movie);
        }
        else
        {
            // inisialisasi elemen selanjutnya dari elemen sebelumnya dari movie yang akan dihapus dengan elemen selanjutnya dari movie yang akan dihapus
            NEXT(PREV(address_movie)) = NEXT(address_movie);
            // inisialisasi elemen sebelumnya dari elemen selanjutnya dari movie yang akan dihapus dengan elemen sebelumnya dari movie yang akan dihapus
            PREV(NEXT(address_movie)) = PREV(address_movie);

            Deallocate(address_movie);
        }
    }
}

// fungsi cari movie by title pada list
AddressMovie FindByTitle(ListMovie &list_movie, string title)
{
    // inisialisasi variabel ketemu
    bool ketemu = false;

    // inisialisasi variabel data_ketemu dengan null
    AddressMovie data_ketemu = NULL;

    // inisialisasi variabel current dengan elemen pertama pada list
    AddressMovie current = FIRST(list_movie);

    // loop selama tidak ketemu dan current tidak sama dengan null
    while (!ketemu && current != NULL)
    {
        // jika title current sama dengan parameter title maka ketemu
        if (DATA(current).title == title)
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

// fungsi cari movie by id pada list
AddressMovie FindById(ListMovie &list_movie, int id)
{
    // inisialisasi variabel ketemu
    bool ketemu = false;

    // inisialisasi variabel data_ketemu dengan null
    AddressMovie data_ketemu = NULL;

    // inisialisasi variabel current dengan elemen pertama pada list
    AddressMovie current = FIRST(list_movie);

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
int Count(ListMovie list_movie)
{
    // inisialisasi count
    int count = 0;

    // inisialisasi variabel current dengan elemen pertama pada list
    AddressMovie current = FIRST(list_movie);

    // hitung selama current tidak sama dengan null
    while (current != NULL)
    {
        count++;
        current = NEXT(current);
    }

    // kembalikan hasil hitung
    return count;
}

// prosedur cetak data movie
void Cetak(AddressMovie address_movie)
{
    // cetak data movie
    cout << "ID          : " << DATA(address_movie).id << endl
        << "Title       : " << DATA(address_movie).title << endl
        << "Director    : " << DATA(address_movie).director << endl
        << "Actors      : " << DATA(address_movie).actors << endl
        << "Genre       : " << DATA(address_movie).genre << endl
        << "Running Time: " << DATA(address_movie).running_time << endl
        << "Release Date: " << DATA(address_movie).release_date << endl << endl;
}

// prosedur cetak list data movie
void Cetak(ListMovie list_movie)
{
    // inisialisasi count
    int count = 0;

    // inisialisasi variabel current dengan elemen pertama pada list
    AddressMovie current = FIRST(list_movie);

    PrintTitle("VIEW LIST MOVIE");

    if (current == NULL)
    {
        // cetak info tidak ada data
        Warning("Tidak ada data.");
        getch();
    }
    else
    {
        // loop cetak movie dalam list
        while (current != NULL)
        {
            // cetak movie
            Cetak(current);

            // next current
            current = NEXT(current);
            count++;
        }

        // cetak total movie
        cout << "Total Movie: " << count << endl;
    }
}