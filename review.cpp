// include library c++
#include <iostream>
#include <conio.h>
#include <string>

// include library buatan
#include "common.h"
#include "review.h"

// using namespace
using namespace std;

// prosedur membuat list baru
void createList(listReview &newListReview) {
    // inisialisasi elemen pertama dengan null
    first(newListReview) = NULL;
    // inisialisasi elemen terakhir dengan null
    last(newListReview) = NULL;
}

// fungsi membuat data review
review createReview(int rating, string description) {
    // inisialisasi id static agar otomatis bertambah saat membuat review baru
    static int id = 0;

    // deklarasi variabel data review
    review newReview;

    // inisialisasi variabel data review
    newReview.id = ++id;
    newReview.rating = rating;
    newReview.description = description;

    // kembalikan review
    return newReview;
}

// fungsi alokasi review
addressReview alokasiReview(review newReview, addressReviewer addressReviewer, addressMovie addressMovie) {
    // deklarasi pointer review
    addressReview newAddressReview;
    // instansiasi pointer dengan elemen review
    newAddressReview = new elementReview();

    // inisialisasi data pada pointer dengan parameter review
    data(newAddressReview) = newReview;
    // inisialisasi data reviewer pada pointer dengan parameter addressReviewer
    reviewer(newAddressReview) = addressReviewer;
    // inisialisasi data movie pada pointer dengan parameter addressMovie
    movie(newAddressReview) = addressMovie;
    // inisialisasi pointer menuju elemen selanjutnya dengan null
    next(newAddressReview) = NULL;
    // inisialisasi pointer menuju elemen sebelumnya dengan null
    prev(newAddressReview) = NULL;

    // kembalikan pointer
    return newAddressReview;
}

// prosedur insert first review
void insertFirst(listReview &listReview, addressReview newAddressReview) {
    // pengecekan jika list masih kosong
    if (first(listReview) == NULL && last(listReview) == NULL) {
        // inisialisasi elemen pertama dengan pointer review baru
        first(listReview) = newAddressReview;
        // inisialisasi elemen terakhir dengan pointer review baru
        last(listReview) = newAddressReview;
    } else {
        // inisialisasi variabel firstReview dengan elemen pertama pada list
        addressReview firstReview = first(listReview);
        // inisialisasi pointer review baru menuju elemen selanjutnya dengan elemen pertama pada list
        next(newAddressReview) = firstReview;
        // inisialisasi pointer review baru menuju elemen sebelumnya dengan null
        prev(newAddressReview) = NULL;
        // inisialisasi pointer menuju elemen sebelumnya pada firstReview dengan pointer review baru
        prev(firstReview) = newAddressReview;
        // inisialisasi elemen pertama pada list dengan pointer review baru
        first(listReview) = newAddressReview;
    }
}

// prosedur insert last review
void insertLast(listReview &listReview, addressReview newAddressReview) {
    // pengecekan jika list masih kosong
    if (first(listReview) == NULL && last(listReview) == NULL) {
        // jika list kosong maka insert first
        insertFirst(listReview, newAddressReview);
    } else {
        // inisialisasi variabel lastReview dengan elemen terakhir pada list
        addressReview lastReview = last(listReview);
        // inisialisasi pointer review baru menuju elemen sebelumnya dengan elemen terakhir pada list
        prev(newAddressReview) = lastReview;
        // inisialisasi pointer review baru menuju elemen selanjutnya dengan null
        next(newAddressReview) = NULL;
        // inisialisasi pointer menuju elemen selanjutnya pada lastReview dengan pointer review baru
        next(lastReview) = newAddressReview;
        // inisialisasi elemen terakhir pada list dengan pointer review baru
        last(listReview) = newAddressReview;
    }
}

// prosedur update review
void updateReview(addressReview review, int newRating, string newDescription) {
    // cek jika review kosong
    if (review == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        data(review).rating = newRating;

        // cek jika variabel baru tidak kosong
        if (!newDescription.empty()) {
            // jika tidak kosong maka update datanya
            data(review).description = newDescription;
        }
    }
}

// prosedur delete review
void deleteReview(listReview &listReview, addressReview review) {
    // cek jika list kosong
    if (first(listReview) == NULL && last(listReview) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else if (review != NULL){
        // jika elemen yang dihapus adalah elemen pertama
        if (first(listReview) == review) {
            // inisialisasi elemen pertama dengan elemen selanjutnya dari review yang akan dihapus
            first(listReview) = next(review);
        }

        // jika elemen yang dihapus adalah elemen terakhir
        if (last(listReview) == review) {
            // inisialisasi elemen terakhir dengan elemen sebelumnya dari review yang akan dihapus
            last(listReview) = prev(review);
        }

        // jika elemen yang dihapus bukan elemen pertama
        if (prev(review) != NULL) {
            // inisialisasi elemen selanjutnya dari elemen sebelumnya dari review yang akan dihapus dengan elemen selanjutnya dari review yang akan dihapus
            next(prev(review)) = next(review);
        }

        // jika elemen yang dihapus bukan elemen terakhir
        if (next(review) != NULL) {
            // inisialisasi elemen sebelumnya dari elemen selanjutnya dari review yang akan dihapus dengan elemen sebelumnya dari review yang akan dihapus
            prev(next(review)) = prev(review);
        }

        // hapus memory
        delete review;
    }
}

// prosedur delete all review
void deleteAll(listReview &listReview) {
    // cek jika list kosong
    if (first(listReview) == NULL && last(listReview) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // deklarasi variabel next
        addressReview next;
        // inisialisasi variabel iterator dengan elemen pertama pada list
        addressReview current = first(listReview);
        // loop delete review dalam list
        while(current != NULL) {
            next = next(current);
            deleteReview(listReview, current);
            current = next;
        }
    }
}

// prosedur delete first review
void deleteFirst(listReview &listReview) {
    // cek jika elemen pertama null (list kosong)
    if (first(listReview) == NULL && last(listReview) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // delete review
        deleteReview(listReview, first(listReview));
    }
}

// prosedur delete last review
void deleteLast(listReview &listReview) {
    // cek jika elemen pertama null (list kosong)
    if (first(listReview) == NULL && last(listReview) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // delete review
        deleteReview(listReview, last(listReview));
    }
}

// fungsi cari review by id pada list
addressReview searchById(listReview &listReview, int id) {
    // inisialisasi variabel ketemu
    bool ketemu = false;

    // inisialisasi variabel dataKetemu dengan null
    addressReview dataKetemu = NULL;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressReview current = first(listReview);

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
int countList(listReview listReview) {
    // inisialisasi count
    int count = 0;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressReview current = first(listReview);

    // hitung selama iterator tidak sama dengan null
    while (current != NULL) {
        count++;
        current = next(current);
    }

    // kembalikan hasil hitung
    return count;
}

// prosedur cetak data review
void cetakReview(addressReview addressReview) {
    // cetak data review
    cout << "ID         : " << data(addressReview).id << endl
         << "Rating     : " << data(addressReview).rating << endl
         << "Description: " << data(addressReview).description << endl << endl;
}

// prosedur cetak list data review
void cetakList(listReview listReview) {
    // inisialisasi count
    int count = 0;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressReview current = first(listReview);

    printTitle("VIEW LIST REVIEW");

    if (current == NULL) {
        // cetak info tidak ada data
        warning("Tidak ada data.");
        getch();
    } else {
        // loop cetak review dalam list
        while(current != NULL) {
            // cetak review
            cetakReview(current);

            // next iterator
            current = next(current);
            count++;
        }

        // cetak total review
        cout << "Total Review: " << count << endl;
    }
}