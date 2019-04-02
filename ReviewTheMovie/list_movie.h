#ifndef LIST_MOVIE_H_INCLUDED
#define LIST_MOVIE_H_INCLUDED

// include library c++
#include <string>

// using namespace
using namespace std;

// pointer alamat memory movie
typedef struct ElementMovie *AddressMovie;

// tipe bentukan data movie
struct Movie {
    int id;
    string title;
    string director;
    string actors;
    string genre;
    string running_time;
    string release_date;
};

// tipe bentukan elemen movie
struct ElementMovie {
    // variabel data movie pada elemen saat ini
    Movie data;
    // pointer menuju elemen sebelumnya
    AddressMovie prev;
    // pointer menuju elemen selanjutnya
    AddressMovie next;
};

// tipe bentukan list movie
struct ListMovie {
    // pointer menuju elemen pertama pada list
    AddressMovie first;
    // pointer menuju elemen terakhir pada list
    AddressMovie last;
};

// prosedur membuat list baru
void CreateList(ListMovie &list_movie);
// fungsi membuat data movie
Movie CreateMovie(string title, string director, string actors, string genre, string running_time, string release_date);

// fungsi alokasi
AddressMovie Allocate(Movie movie);
// fungsi dealokasi
void Deallocate(AddressMovie &address_movie);

// prosedur insert first movie
void InsertFirst(ListMovie &list_movie, AddressMovie address_movie);
// prosedur insert last movie
void InsertLast(ListMovie &list_movie, AddressMovie address_movie);

// prosedur update movie
void UpdateMovie(AddressMovie address_movie, string new_title, string new_director, string new_actors, string new_genre, string new_running_time, string new_release_date);

// prosedur delete first movie
void DeleteFirst(ListMovie &list_movie);
// prosedur delete last movie
void DeleteLast(ListMovie &list_movie);
// prosedur delete movie
void DeleteMovie(ListMovie &list_movie, AddressMovie address_movie);

// fungsi cari movie by title pada list
AddressMovie FindByTitle(ListMovie &list_movie, string title);
// fungsi cari movie by id pada list
AddressMovie FindById(ListMovie &list_movie, int id);

// fungsi hitung total elemen pada list
int Count(ListMovie list_movie);

// prosedur cetak data movie
void Cetak(AddressMovie address_movie);
// prosedur cetak list data movie
void Cetak(ListMovie list_movie);

#endif // LIST_MOVIE_H_INCLUDED