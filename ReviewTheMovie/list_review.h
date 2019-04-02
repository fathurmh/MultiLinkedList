#ifndef LIST_REVIEW_H_INCLUDED
#define LIST_REVIEW_H_INCLUDED

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
typedef struct ElementReview *AddressReview;

// tipe bentukan data review
struct Review {
    int id;
    int rating;
    string description;
};

// tipe bentukan elemen review
struct ElementReview {
    // variabel data review pada elemen saat ini
    Review data;
    // pointer menuju elemen selanjutnya
    AddressReview next;
    // pointer menuju elemen reviewer
    AddressReviewer reviewer;
    // pointer menuju elemen movie
    AddressMovie movie;
};

// tipe bentukan list review
struct ListReview {
    // pointer menuju elemen pertama pada list
    AddressReview first;
};

// prosedur membuat list baru
void CreateList(ListReview &list_review);
// fungsi membuat data review
Review CreateReview(int rating, string description);

// fungsi alokasi
AddressReview Allocate(Review review, AddressReviewer address_reviewer, AddressMovie address_movie);
// fungsi alokasi array
AddressReview *Allocate(int size);
// prosedur dealokasi
void Deallocate(AddressReview &address_review);
// prosedur dealokasi array
void Deallocate(AddressReview *(&array_review));

// prosedur insert first
void InsertFirst(ListReview &list_review, AddressReview address_review);
// prosedur insert last
void InsertLast(ListReview &list_review, AddressReview address_review);

// prosedur update review
void UpdateReview(AddressReview address_review, int new_rating, string new_description);

// prosedur delete first
void DeleteFirst(ListReview &list_review);
// prosedur delete last
void DeleteLast(ListReview &list_review);
// prosedur delete last
void DeleteReview(ListReview &list_review, AddressReview address_review);

// fungsi cari review by id pada list
AddressReview FindById(ListReview list_review, int id);
// fungsi cari review by movie id pada list
void FindByMovieId(ListReview &result, ListReview list_review, int id);

// fungsi hitung total elemen pada list
int Count(ListReview list_review);

// prosedur cetak data review
void Cetak(AddressReview address_review);
// prosedur cetak list data review
void Cetak(ListReview list_review);

#endif // LIST_REVIEW_H_INCLUDED
