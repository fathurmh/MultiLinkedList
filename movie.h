#ifndef MOVIE_H
#define MOVIE_H

// include library c++
#include <string>

// using namespace
using namespace std;

// pointer alamat memory movie
typedef struct elementMovie *addressMovie;

// tipe bentukan data movie
struct movie {
	int id;
    string title;
    string director;
    string actors;
	string genre;
	string runningTime;
	string releaseDate;
};

// tipe bentukan elemen movie
struct elementMovie {
	// variabel data movie pada elemen saat ini
	movie data;
	// pointer menuju elemen sebelumnya
	addressMovie prev;
	// pointer menuju elemen selanjutnya
	addressMovie next;
};

// tipe bentukan list movie
struct listMovie {
	// pointer menuju elemen pertama pada list
	addressMovie first;
	// pointer menuju elemen terakhir pada list
	addressMovie last;
};

// prosedur membuat list baru
void createList(listMovie &newListMovie);
// fungsi membuat data movie
movie createMovie(string title, string director, string actors, string genre, string runningTime, string releaseDate);
// fungsi alokasi movie
addressMovie alokasiMovie(movie newMovie);
// prosedur insert first movie
void insertFirst(listMovie &listMovie, addressMovie newAddressMovie);
// prosedur insert last movie
void insertLast(listMovie &listMovie, addressMovie newAddressMovie);
// prosedur update movie
void updateMovie(addressMovie movie, string newTitle, string newDirector, string newActors, string newGenre, string newRunningTime, string newReleaseDate);
// prosedur delete movie
void deleteMovie(listMovie &listMovie, addressMovie movie);
// prosedur delete all movie
void deleteAll(listMovie &listMovie);
// prosedur delete first movie
void deleteFirst(listMovie &listMovie);
// prosedur delete last movie
void deleteLast(listMovie &listMovie);
// fungsi cari movie by id pada list
addressMovie searchById(listMovie &listMovie, int id);
// fungsi hitung total elemen pada list
int countList(listMovie listMovie);
// prosedur cetak data movie
void cetakMovie(addressMovie addressMovie);
// prosedur cetak list data movie
void cetakList(listMovie listMovie);

#endif // MOVIE_H