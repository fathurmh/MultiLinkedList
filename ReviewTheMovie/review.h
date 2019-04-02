#ifndef REVIEW_H_INCLUDED
#define REVIEW_H_INCLUDED

// include library c++
#include <string>

// include library buatan
#include "list_reviewer.h"
#include "list_movie.h"

// using namespace
using namespace std;

// pointer menuju elemen reviewer
#define REVIEWER(p) p->reviewer
// pointer menuju elemen movie
#define MOVIE(p) p->movie

// pointer alamat memory review
typedef struct elementReview *addressReview;

// tipe bentukan data review
struct review {
    int id;
    int rating;
    string description;
};

// tipe bentukan elemen review
struct elementReview {
    // variabel data review pada elemen saat ini
    review data;
    // pointer menuju elemen selanjutnya
    addressReview next;
    // pointer menuju elemen reviewer
    AddressReviewer reviewer;
    // pointer menuju elemen movie
    AddressMovie movie;
};

// tipe bentukan list review
struct ListReview {
    // pointer menuju elemen pertama pada list
    addressReview first;
};

// prosedur membuat list baru
void createList(ListReview &ListReview);
// fungsi membuat data review
review createReview(int rating, string description);

// fungsi alokasi
addressReview allocate(review review, AddressReviewer addressReviewer, AddressMovie addressMovie);
// prosedur dealokasi
void deallocate(addressReview &addressReview);
// fungsi alokasi array
addressReview *allocate(int size);

// prosedur insert first
void insertFirst(ListReview &ListReview, addressReview newAddressReview);
// prosedur insert last
void insertLast(ListReview &ListReview, addressReview newAddressReview);

// prosedur update
void update(addressReview review, int newRating, string newDescription);

// prosedur delete first
void deleteFirst(ListReview &ListReview);
// prosedur delete last
void deleteLast(ListReview &ListReview);
// prosedur delete last
void deleteReview(ListReview &ListReview, addressReview deleteAddressReview);

// fungsi cari review by id pada list
addressReview findById(ListReview ListReview, int id);
// fungsi cari review by movie id pada list
void findByMovieId(ListReview &Result, ListReview ListReview, int id);
// fungsi hitung total elemen pada list
int count(ListReview ListReview);
// prosedur cetak data review
void cetak(addressReview addressReview);
// prosedur cetak list data review
void cetak(ListReview ListReview);

#endif // REVIEW_H_INCLUDED