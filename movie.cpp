// include library c++
#include <iostream>
#include <conio.h>
#include <string>

// include library buatan
#include "common.h"
#include "movie.h"

// using namespace
using namespace std;

// prosedur membuat list baru
void createList(listMovie &newListMovie) {
    // inisialisasi elemen pertama dengan null
    first(newListMovie) = NULL;
    // inisialisasi elemen terakhir dengan null
    last(newListMovie) = NULL;
}

// fungsi membuat data movie
movie createMovie(string title, string director, string actors, string genre, string runningTime, string releaseDate) {
    // inisialisasi id static agar otomatis bertambah saat membuat movie baru
    static int id = 0;

    // deklarasi variabel data movie
    movie newMovie;

    // inisialisasi variabel data movie
    newMovie.id = ++id;
    newMovie.title = title;
    newMovie.director = director;
    newMovie.actors = actors;
    newMovie.genre = genre;
    newMovie.runningTime = runningTime;
    newMovie.releaseDate = releaseDate;

    // kembalikan movie
    return newMovie;
}

// fungsi alokasi movie
addressMovie alokasiMovie(movie movie) {
    // deklarasi pointer movie
    addressMovie newAddressMovie;
    // instansiasi pointer dengan elemen movie
    newAddressMovie = new elementMovie();

    // inisialisasi data pada pointer dengan parameter movie
    data(newAddressMovie) = movie;
    // inisialisasi pointer menuju elemen selanjutnya dengan null
    next(newAddressMovie) = NULL;
    // inisialisasi pointer menuju elemen sebelumnya dengan null
    prev(newAddressMovie) = NULL;

    // kembalikan pointer
    return newAddressMovie;
}

// prosedur insert first movie
void insertFirst(listMovie &listMovie, addressMovie newAddressMovie) {
    // pengecekan jika list masih kosong
    if (first(listMovie) == NULL && last(listMovie) == NULL) {
        // inisialisasi elemen pertama dengan pointer movie baru
        first(listMovie) = newAddressMovie;
        // inisialisasi elemen terakhir dengan pointer movie baru
        last(listMovie) = newAddressMovie;
    } else {
        // inisialisasi variabel firstMovie dengan elemen pertama pada list
        addressMovie firstMovie = first(listMovie);
        // inisialisasi pointer movie baru menuju elemen selanjutnya dengan elemen pertama pada list
        next(newAddressMovie) = firstMovie;
        // inisialisasi pointer movie baru menuju elemen sebelumnya dengan null
        prev(newAddressMovie) = NULL;
        // inisialisasi pointer menuju elemen sebelumnya pada firstMovie dengan pointer movie baru
        prev(firstMovie) = newAddressMovie;
        // inisialisasi elemen pertama pada list dengan pointer movie baru
        first(listMovie) = newAddressMovie;
    }
}

// prosedur insert last movie
void insertLast(listMovie &listMovie, addressMovie newAddressMovie) {
    // pengecekan jika list masih kosong
    if (first(listMovie) == NULL && last(listMovie) == NULL) {
        // jika list kosong maka insert first
        insertFirst(listMovie, newAddressMovie);
    } else {
        // inisialisasi variabel lastMovie dengan elemen terakhir pada list
        addressMovie lastMovie = last(listMovie);
        // inisialisasi pointer movie baru menuju elemen sebelumnya dengan elemen terakhir pada list
        prev(newAddressMovie) = lastMovie;
        // inisialisasi pointer movie baru menuju elemen selanjutnya dengan null
        next(newAddressMovie) = NULL;
        // inisialisasi pointer menuju elemen selanjutnya pada lastMovie dengan pointer movie baru
        next(lastMovie) = newAddressMovie;
        // inisialisasi elemen terakhir pada list dengan pointer movie baru
        last(listMovie) = newAddressMovie;
    }
}

// prosedur update movie
void updateMovie(addressMovie movie, string newTitle, string newDirector, string newActors, string newGenre, string newRunningTime, string newReleaseDate) {
    // cek jika movie kosong
    if (movie == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // cek jika variabel baru tidak kosong
        if (!newTitle.empty()) {
            // jika tidak kosong maka update datanya
            data(movie).title = newTitle;
        }

        if (!newDirector.empty()) {
            data(movie).director = newDirector;
        }

        if (!newActors.empty()) {
            data(movie).actors = newActors;
        }

        if (!newGenre.empty()) {
            data(movie).genre = newGenre;
        }

        if (!newRunningTime.empty()) {
            data(movie).runningTime = newRunningTime;
        }

        if (!newReleaseDate.empty()) {
            data(movie).releaseDate = newReleaseDate;
        }
    }
}

// prosedur delete movie
void deleteMovie(listMovie &listMovie, addressMovie movie) {
    // cek jika list kosong
    if (first(listMovie) == NULL && last(listMovie) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else if (movie != NULL){
        // jika elemen yang dihapus adalah elemen pertama
        if (first(listMovie) == movie) {
            // inisialisasi elemen pertama dengan elemen selanjutnya dari movie yang akan dihapus
            first(listMovie) = next(movie);
        }

        // jika elemen yang dihapus adalah elemen terakhir
        if (last(listMovie) == movie) {
            // inisialisasi elemen terakhir dengan elemen sebelumnya dari movie yang akan dihapus
            last(listMovie) = prev(movie);
        }

        // jika elemen yang dihapus bukan elemen pertama
        if (prev(movie) != NULL) {
            // inisialisasi elemen selanjutnya dari elemen sebelumnya dari movie yang akan dihapus dengan elemen selanjutnya dari movie yang akan dihapus
            next(prev(movie)) = next(movie);
        }

        // jika elemen yang dihapus bukan elemen terakhir
        if (next(movie) != NULL) {
            // inisialisasi elemen sebelumnya dari elemen selanjutnya dari movie yang akan dihapus dengan elemen sebelumnya dari movie yang akan dihapus
            prev(next(movie)) = prev(movie);
        }

        // hapus memory
        delete movie;
    }
}

// prosedur delete all movie
void deleteAll(listMovie &listMovie) {
    // cek jika list kosong
    if (first(listMovie) == NULL && last(listMovie) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // deklarasi variabel next
        addressMovie next;
        // inisialisasi variabel iterator dengan elemen pertama pada list
        addressMovie current = first(listMovie);
        // loop delete movie dalam list
        while(current != NULL) {
            next = next(current);
            deleteMovie(listMovie, current);
            current = next;
        }
    }
}

// prosedur delete first movie
void deleteFirst(listMovie &listMovie) {
    // cek jika elemen pertama null (list kosong)
    if (first(listMovie) == NULL && last(listMovie) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // delete movie
        deleteMovie(listMovie, first(listMovie));
    }
}

// prosedur delete last movie
void deleteLast(listMovie &listMovie) {
    // cek jika elemen pertama null (list kosong)
    if (first(listMovie) == NULL && last(listMovie) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // delete movie
        deleteMovie(listMovie, last(listMovie));
    }
}

// fungsi cari movie by id pada list
addressMovie searchById(listMovie &listMovie, int id) {
    // inisialisasi variabel ketemu
    bool ketemu = false;

    // inisialisasi variabel dataKetemu dengan null
    addressMovie dataKetemu = NULL;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressMovie current = first(listMovie);

    // loop selama tidak ketemu dan iterator tidak sama dengan null
    while (!ketemu && current != NULL) {
        // jika username iterator sama dengan parameter username maka ketemu
        if (data(current).id == id) {
            ketemu = true;
            dataKetemu = current;
        }
        // variabel iterator diisi dengan elemen selanjutnya
        current = next(current);
    }

    // kembalikan data
    return dataKetemu;
}

// fungsi hitung total elemen pada list
int countList(listMovie listMovie) {
    // inisialisasi count
    int count = 0;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressMovie current = first(listMovie);

    // hitung selama iterator tidak sama dengan null
    while (current != NULL) {
        count++;
        current = next(current);
    }

    // kembalikan hasil hitung
    return count;
}

// prosedur cetak data movie
void cetakMovie(addressMovie addressMovie) {
    // cetak data movie
    cout << "ID          : " << data(addressMovie).id << endl
         << "Title       : " << data(addressMovie).title << endl
         << "Director    : " << data(addressMovie).director << endl
         << "Actors      : " << data(addressMovie).actors << endl
         << "Genre       : " << data(addressMovie).genre << endl
         << "Running Time: " << data(addressMovie).runningTime << endl
         << "Release Date: " << data(addressMovie).releaseDate << endl << endl;
}

// prosedur cetak list data movie
void cetakList(listMovie listMovie) {
    // inisialisasi count
    int count = 0;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressMovie current = first(listMovie);

    printTitle("VIEW LIST MOVIE");

    if (current == NULL) {
        // cetak info tidak ada data
        warning("Tidak ada data.");
        getch();
    } else {
        // loop cetak movie dalam list
        while(current != NULL) {
            // cetak movie
            cetakMovie(current);

            // next iterator
            current = next(current);
            count++;
        }

        // cetak total movie
        cout << "Total Movie: " << count << endl;
    }
}