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
void createList(ListReview &ListReview) {
    // inisialisasi elemen pertama dengan null
    first(ListReview) = NULL;
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

// fungsi alokasi
addressReview allocate(review newReview, addressReviewer addressReviewer, addressMovie addressMovie) {
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

    // kembalikan pointer
    return newAddressReview;
}

// prosedur dealokasi
void deallocate(addressReview &addressReview) {
    delete addressReview;
}

// prosedur insert first
void insertFirst(ListReview &ListReview, addressReview newAddressReview) {
    // pengecekan jika list masih kosong
    if (first(ListReview) == NULL) {
        // inisiasi elemen selanjutnya dengan elemen itu sendiri
        next(newAddressReview) = newAddressReview;
        // inisialisasi elemen pertama dengan pointer review baru
        first(ListReview) = newAddressReview;
    } else {
        // inisialisasi variabel lastReview dengan elemen pertama pada list
        addressReview lastReview = first(ListReview);
        // cari pointer elemen terakhir yang menuju ke elemen pertama
        while(next(lastReview) != first(ListReview)) {
            lastReview = next(lastReview);
        }
        // inisialisasi pointer elemen terakhir menuju elemen selanjutnya dengan elemen baru
        next(lastReview) = newAddressReview;
        // inisialisasi pointer review baru menuju elemen selanjutnya dengan elemen pertama pada list
        next(newAddressReview) = first(ListReview);
        // inisialisasi elemen pertama pada list dengan pointer review baru
        first(ListReview) = newAddressReview;
    }
}

// prosedur insert last
void insertLast(ListReview &ListReview, addressReview newAddressReview) {
    // pengecekan jika list masih kosong
    if (first(ListReview) == NULL) {
        // jika list kosong maka insert first
        insertFirst(ListReview, newAddressReview);
    } else {
        // inisialisasi variabel lastReview dengan elemen pertama pada list
        addressReview lastReview = first(ListReview);
        // cari pointer elemen terakhir yang menuju ke elemen pertama
        while(next(lastReview) != first(ListReview)) {
            lastReview = next(lastReview);
        }
        // inisialisasi pointer review baru menuju elemen selanjutnya dengan elemen pertama pada list
        next(newAddressReview) = first(ListReview);
        // inisialisasi pointer elemen terakhir menuju elemen selanjutnya dengan elemen baru
        next(lastReview) = newAddressReview;
    }
}

// prosedur update
void update(addressReview review, int newRating, string newDescription) {
    // cek jika review kosong
    if (review == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // update data rating
        data(review).rating = newRating;

        // cek jika variabel baru tidak kosong
        if (!newDescription.empty()) {
            // jika tidak kosong maka update data description
            data(review).description = newDescription;
        }
    }
}

// prosedur delete first
void deleteFirst(ListReview &ListReview) {
    // cek jika elemen pertama null (list kosong)
    if (first(ListReview) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // inisialisasi lastReview dan firstReview
        addressReview lastReview = first(ListReview);
        addressReview firstReview = first(ListReview);

        // jika list hanya mempunyai satu elemen
        if (next(firstReview) == firstReview) {
            // delete
            first(ListReview) = NULL;
            // dealokasi elemen pertama
            deallocate(firstReview);
        } else {
            // cari elemen terakhir
            while(next(lastReview) != first(ListReview)){
                lastReview = next(lastReview);
            }
            // hubungkan elemen terakhir dengan elemen kedua
            next(lastReview) = next(firstReview);
            // elemen pertama diisi oleh elemen kedua
            first(ListReview) = next(firstReview);
            // dealokasi elemen pertama
            deallocate(firstReview);
        }
    }
}

// prosedur delete last
void deleteLast(ListReview &ListReview) {
    // cek jika elemen pertama null (list kosong)
    if (first(ListReview) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // inisialisasi secondLastReview dan lastReview
        addressReview secondLastReview = first(ListReview);
        addressReview lastReview = first(ListReview);

        // jika list hanya mempunyai satu elemen
        if (next(lastReview) == lastReview) {
            // delete first
            deleteFirst(ListReview);
        } else {
            // cari elemen terakhir dan kedua terakhir
            while(next(lastReview) != first(ListReview)){
                secondLastReview = lastReview;
                lastReview = next(lastReview);
            }
            // hubungkan elemen kedua terakhir dengan elemen terakhir
            next(secondLastReview) = next(lastReview);
            // dealokasi elemen terakhir
            deallocate(lastReview);
        }
    }
}

// prosedur delete last
void deleteReview(ListReview &ListReview, addressReview deleteAddressReview) {
    // cek jika elemen pertama null (list kosong)
    if (first(ListReview) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else if (deleteAddressReview != NULL){
        // jika list hanya mempunyai satu elemen
        if (next(deleteAddressReview) == first(ListReview)) {
            // delete first
            deleteFirst(ListReview);
        } else {
            // jika elemen yang dihapus adalah elemen pertama
            if (deleteAddressReview == first(ListReview)) {
                // delete first
                deleteFirst(ListReview);
            } else if (next(deleteAddressReview) == first(ListReview)) {
                // jika elemen yang dihapus adalah elemen terakhir
                // delete last
                deleteLast(ListReview);
            } else {
                // inisialisasi variabel prevReview dengan elemen pertama pada list
                addressReview prevReview = first(ListReview);
                // cari pointer elemen yang menuju ke elemen yang akan dihapus
                while(next(prevReview) != deleteAddressReview) {
                    prevReview = next(prevReview);
                }
                // inisialisasi elemen yang menuju ke elemen yang dihapus dengan elemen selanjutnya dari elemen yang dihapus
                next(prevReview) = next(deleteAddressReview);
                // dealokasi elemen yang dihapus
                deallocate(deleteAddressReview);
            }
        }
    }
}

// fungsi cari review by id pada list
addressReview findById(ListReview ListReview, int id) {
    // inisialisasi variabel ketemu
    bool ketemu = false;
    // inisialisasi variabel dataKetemu dengan null
    addressReview dataKetemu = NULL;

    // cek jika elemen pertama tidak null (list berisi)
    if (first(ListReview) != NULL) {
        // inisialisasi variabel current dengan elemen pertama pada list
        addressReview current = first(ListReview);
        do {
            // variabel current diisi dengan elemen selanjutnya
            current = next(current);
            // jika id current sama dengan parameter id yang dicari maka ketemu
            if (data(current).id == id) {
                ketemu = true;
                dataKetemu = current;
            }
        } while (!ketemu && current != first(ListReview)); // loop selama tidak ketemu dan current elemen tidak sama dengan elemen pertama
    }

    // kembalikan data
    return dataKetemu;
}

// fungsi hitung total elemen pada list
int count(ListReview ListReview) {
    // inisialisasi count
    int count = 0;

    // cek jika elemen pertama tidak null (list berisi)
    if (first(ListReview) != NULL) {
        // inisialisasi variabel current dengan elemen pertama pada list
        addressReview current = first(ListReview);
        do {
            // variabel current diisi dengan elemen selanjutnya
            current = next(current);
            count++;
        } while (current != first(ListReview)); // loop selama tidak ketemu dan current elemen tidak sama dengan elemen pertama
    }

    // kembalikan hasil hitung
    return count;
}

// prosedur cetak data review
void cetak(addressReview addressReview) {
    // cetak data review
    cout << "ID         : " << data(addressReview).id << endl
         << "Rating     : " << data(addressReview).rating << endl
         << "Description: " << data(addressReview).description << endl << endl;
}

// prosedur cetak list data review
void cetak(ListReview ListReview) {
    // inisialisasi count
    int count = 0;

    printTitle("VIEW LIST REVIEW");
    if (first(ListReview) == NULL) {
        // cetak info tidak ada data
        warning("Tidak ada data.");
        getch();
    } else {
        // inisialisasi variabel current dengan elemen pertama pada list
        addressReview current = first(ListReview);
        do {
            // cetak review
            cetak(current);
            // variabel current diisi dengan elemen selanjutnya
            current = next(current);
            count++;
        } while (current != first(ListReview)); // loop selama tidak ketemu dan current elemen tidak sama dengan elemen pertama

        // cetak total review
        cout << "Total Review: " << count << endl;
    }
}