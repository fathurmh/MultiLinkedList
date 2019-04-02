// include library c++
#include <iostream>
#include <conio.h>

// include library buatan
#include "common.h"
#include "review.h"

// prosedur membuat list baru
void createList(ListReview &ListReview) {
    // inisialisasi elemen pertama dengan null
    FIRST(ListReview) = NULL;
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
addressReview allocate(review newReview, addressReviewer addressReviewer, AddressMovie addressMovie) {
    // deklarasi pointer review
    addressReview newAddressReview;
    // instansiasi pointer dengan elemen review
    newAddressReview = new elementReview();

    // inisialisasi data pada pointer dengan parameter review
    DATA(newAddressReview) = newReview;
    // inisialisasi data reviewer pada pointer dengan parameter addressReviewer
    REVIEWER(newAddressReview) = addressReviewer;
    // inisialisasi data movie pada pointer dengan parameter addressMovie
    MOVIE(newAddressReview) = addressMovie;
    // inisialisasi pointer menuju elemen selanjutnya dengan null
    NEXT(newAddressReview) = NULL;

    // kembalikan pointer
    return newAddressReview;
}

// prosedur dealokasi
void deallocate(addressReview &addressReview) {
    delete addressReview;
}

addressReview *allocate(int size)
{
    // instansiasi pointer array
    addressReview *array = new addressReview[size];
    for (int i = 0; i < size; i++)
    {
        // setiap array diisikan null
        array[i] = NULL;
    }

    // kembalikan array
    return array;
}

// prosedur insert first
void insertFirst(ListReview &ListReview, addressReview newAddressReview) {
    // pengecekan jika list masih kosong
    if (FIRST(ListReview) == NULL) {
        // inisiasi elemen selanjutnya dengan elemen itu sendiri
        NEXT(newAddressReview) = newAddressReview;
        // inisialisasi elemen pertama dengan pointer review baru
        FIRST(ListReview) = newAddressReview;
    } else {
        // inisialisasi variabel lastReview dengan elemen pertama pada list
        addressReview lastReview = FIRST(ListReview);
        // cari pointer elemen terakhir yang menuju ke elemen pertama
        while(NEXT(lastReview) != FIRST(ListReview)) {
            lastReview = NEXT(lastReview);
        }
        // inisialisasi pointer elemen terakhir menuju elemen selanjutnya dengan elemen baru
        NEXT(lastReview) = newAddressReview;
        // inisialisasi pointer review baru menuju elemen selanjutnya dengan elemen pertama pada list
        NEXT(newAddressReview) = FIRST(ListReview);
        // inisialisasi elemen pertama pada list dengan pointer review baru
        FIRST(ListReview) = newAddressReview;
    }
}

// prosedur insert last
void insertLast(ListReview &ListReview, addressReview newAddressReview) {
    // pengecekan jika list masih kosong
    if (FIRST(ListReview) == NULL) {
        // jika list kosong maka insert first
        insertFirst(ListReview, newAddressReview);
    } else {
        // inisialisasi variabel lastReview dengan elemen pertama pada list
        addressReview lastReview = FIRST(ListReview);
        // cari pointer elemen terakhir yang menuju ke elemen pertama
        while(NEXT(lastReview) != FIRST(ListReview)) {
            lastReview = NEXT(lastReview);
        }
        // inisialisasi pointer review baru menuju elemen selanjutnya dengan elemen pertama pada list
        NEXT(newAddressReview) = FIRST(ListReview);
        // inisialisasi pointer elemen terakhir menuju elemen selanjutnya dengan elemen baru
        NEXT(lastReview) = newAddressReview;
    }
}

// prosedur update
void update(addressReview review, int newRating, string newDescription) {
    // cek jika review kosong
    if (review == NULL) {
        Warning("Tidak ada data.");
        getch();
    } else {
        // update data rating
        DATA(review).rating = newRating;

        // cek jika variabel baru tidak kosong
        if (!newDescription.empty()) {
            // jika tidak kosong maka update data description
            DATA(review).description = newDescription;
        }
    }
}

// prosedur delete first
void deleteFirst(ListReview &ListReview) {
    // cek jika elemen pertama null (list kosong)
    if (FIRST(ListReview) == NULL) {
        Warning("Tidak ada data.");
        getch();
    } else {
        // inisialisasi lastReview dan firstReview
        addressReview lastReview = FIRST(ListReview);
        addressReview firstReview = FIRST(ListReview);

        // jika list hanya mempunyai satu elemen
        if (NEXT(firstReview) == firstReview) {
            // delete
            FIRST(ListReview) = NULL;
            // dealokasi elemen pertama
            deallocate(firstReview);
        } else {
            // cari elemen terakhir
            while(NEXT(lastReview) != FIRST(ListReview)){
                lastReview = NEXT(lastReview);
            }
            // hubungkan elemen terakhir dengan elemen kedua
            NEXT(lastReview) = NEXT(firstReview);
            // elemen pertama diisi oleh elemen kedua
            FIRST(ListReview) = NEXT(firstReview);
            // dealokasi elemen pertama
            deallocate(firstReview);
        }
    }
}

// prosedur delete last
void deleteLast(ListReview &ListReview) {
    // cek jika elemen pertama null (list kosong)
    if (FIRST(ListReview) == NULL) {
        Warning("Tidak ada data.");
        getch();
    } else {
        // inisialisasi secondLastReview dan lastReview
        addressReview secondLastReview = FIRST(ListReview);
        addressReview lastReview = FIRST(ListReview);

        // jika list hanya mempunyai satu elemen
        if (NEXT(lastReview) == lastReview) {
            // delete first
            deleteFirst(ListReview);
        } else {
            // cari elemen terakhir dan kedua terakhir
            while(NEXT(lastReview) != FIRST(ListReview)){
                secondLastReview = lastReview;
                lastReview = NEXT(lastReview);
            }
            // hubungkan elemen kedua terakhir dengan elemen terakhir
            NEXT(secondLastReview) = NEXT(lastReview);
            // dealokasi elemen terakhir
            deallocate(lastReview);
        }
    }
}

// prosedur delete last
void deleteReview(ListReview &ListReview, addressReview deleteAddressReview) {
    // cek jika elemen pertama null (list kosong)
    if (FIRST(ListReview) == NULL) {
        Warning("Tidak ada data.");
        getch();
    } else if (deleteAddressReview != NULL){
        // jika list hanya mempunyai satu elemen
        if (NEXT(deleteAddressReview) == FIRST(ListReview)) {
            // delete first
            deleteFirst(ListReview);
        } else {
            // jika elemen yang dihapus adalah elemen pertama
            if (deleteAddressReview == FIRST(ListReview)) {
                // delete first
                deleteFirst(ListReview);
            } else if (NEXT(deleteAddressReview) == FIRST(ListReview)) {
                // jika elemen yang dihapus adalah elemen terakhir
                // delete last
                deleteLast(ListReview);
            } else {
                // inisialisasi variabel prevReview dengan elemen pertama pada list
                addressReview prevReview = FIRST(ListReview);
                // cari pointer elemen yang menuju ke elemen yang akan dihapus
                while(NEXT(prevReview) != deleteAddressReview) {
                    prevReview = NEXT(prevReview);
                }
                // inisialisasi elemen yang menuju ke elemen yang dihapus dengan elemen selanjutnya dari elemen yang dihapus
                NEXT(prevReview) = NEXT(deleteAddressReview);
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
    if (FIRST(ListReview) != NULL) {
        // inisialisasi variabel current dengan elemen pertama pada list
        addressReview current = FIRST(ListReview);
        do {
            // variabel current diisi dengan elemen selanjutnya
            current = NEXT(current);
            // jika id current sama dengan parameter id yang dicari maka ketemu
            if (DATA(current).id == id) {
                ketemu = true;
                dataKetemu = current;
            }
        } while (!ketemu && current != FIRST(ListReview)); // loop selama tidak ketemu dan current elemen tidak sama dengan elemen pertama
    }

    // kembalikan data
    return dataKetemu;
}

// fungsi cari review by movie id pada list
void findByMovieId(ListReview &Result, ListReview ListReview, int id) {
    // cek jika elemen pertama tidak null (list berisi)
    if (FIRST(ListReview) != NULL) {
        // convert to array
        int totalReview = count(ListReview);
        addressReview *arrayReview = allocate(totalReview);
        // inisialisasi variabel current dengan elemen pertama pada list
        addressReview current = FIRST(ListReview);
        AddressMovie currentMovie;
        addressReviewer currentReviewer;
        do {
            // variabel current diisi dengan elemen selanjutnya
            current = NEXT(current);
            currentMovie = MOVIE(current);
            currentReviewer = REVIEWER(current);
            if (DATA(currentMovie).id == id) {
                // alokasi review dan insert pada list baru
                addressReview newReview = allocate(DATA(current), REVIEWER(current), currentMovie);
                insertLast(Result, newReview);
            }
        } while (current != FIRST(ListReview)); // loop selama current elemen tidak sama dengan elemen pertama
    }
}

// fungsi hitung total elemen pada list
int count(ListReview ListReview) {
    // inisialisasi count
    int count = 0;

    // cek jika elemen pertama tidak null (list berisi)
    if (FIRST(ListReview) != NULL) {
        // inisialisasi variabel current dengan elemen pertama pada list
        addressReview current = FIRST(ListReview);
        do {
            // variabel current diisi dengan elemen selanjutnya
            current = NEXT(current);
            count++;
        } while (current != FIRST(ListReview)); // loop selama tidak ketemu dan current elemen tidak sama dengan elemen pertama
    }

    // kembalikan hasil hitung
    return count;
}

// prosedur cetak data review
void cetak(addressReview addressReview) {
    // cetak data review
    cout << "ID         : " << DATA(addressReview).id << endl
         << "Rating     : " << DATA(addressReview).rating << endl
         << "Description: " << DATA(addressReview).description << endl << endl;
}

// prosedur cetak list data review
void cetak(ListReview ListReview) {
    // inisialisasi count
    int count = 0;

    PrintTitle("VIEW LIST REVIEW");
    if (FIRST(ListReview) == NULL) {
        // cetak info tidak ada data
        Warning("Tidak ada data.");
        getch();
    } else {
        // inisialisasi variabel current dengan elemen pertama pada list
        addressReview current = FIRST(ListReview);
        do {
            // cetak review
            cetak(current);
            // variabel current diisi dengan elemen selanjutnya
            current = NEXT(current);
            count++;
        } while (current != FIRST(ListReview)); // loop selama tidak ketemu dan current elemen tidak sama dengan elemen pertama

        // cetak total review
        cout << "Total Review: " << count << endl;
    }
}