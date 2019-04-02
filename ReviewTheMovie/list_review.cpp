// include library c++
#include <conio.h>
#include <iostream>
#include <string>

// include library buatan
#include "common.h"
#include "list_reviewer.h"
#include "list_movie.h"
#include "list_review.h"

// using namespace
using namespace std;

// prosedur membuat list baru
void CreateList(ListReview &list_review)
{
    // inisialisasi elemen pertama dengan null
    FIRST(list_review) = NULL;
}

// fungsi membuat data review
Review CreateReview(int rating, string description)
{
    // inisialisasi id static agar otomatis bertambah saat membuat review baru
    static int id = 0;

    // deklarasi variabel data review
    Review review;

    // inisialisasi variabel data review
    review.id = ++id;
    review.rating = rating;
    review.description = description;

    // kembalikan review
    return review;
}

// fungsi alokasi
AddressReview Allocate(Review review, AddressReviewer address_reviewer, AddressMovie address_movie)
{
    // instansiasi pointer
    AddressReview address_review = new ElementReview();

    // inisialisasi data pada pointer dengan parameter review
    DATA(address_review) = review;
    // inisialisasi data reviewer pada pointer dengan parameter address_reviewer
    REVIEWER(address_review) = address_reviewer;
    // inisialisasi data movie pada pointer dengan parameter address_movie
    MOVIE(address_review) = address_movie;
    // inisialisasi pointer menuju elemen selanjutnya dengan null
    NEXT(address_review) = NULL;

    // kembalikan pointer
    return address_review;
}

AddressReview *Allocate(int size)
{
    // instansiasi pointer array
    AddressReview *array = new AddressReview[size];
    for (int i = 0; i < size; i++)
    {
        // setiap array diisikan null
        array[i] = NULL;
    }

    // kembalikan array
    return array;
}

// prosedur dealokasi
void Deallocate(AddressReview &address_review)
{
    delete address_review;
}

// prosedur dealokasi array
void Deallocate(AddressReview *(&array_review))
{
    delete[] array_review;
}

// prosedur insert first
void InsertFirst(ListReview &list_review, AddressReview address_review)
{
    // pengecekan jika list masih kosong
    if (FIRST(list_review) == NULL)
    {
        // inisialisasi elemen pertama dengan pointer review baru
        FIRST(list_review) = address_review;
        // inisiasi elemen selanjutnya dengan elemen itu sendiri
        NEXT(address_review) = address_review;
    }
    else
    {
        // cari pointer elemen terakhir yang menuju ke elemen pertama
        AddressReview last_review = FIRST(list_review);
        while (NEXT(last_review) != FIRST(list_review))
        {
            last_review = NEXT(last_review);
        }
        // inisialisasi pointer elemen terakhir menuju elemen selanjutnya dengan elemen baru
        NEXT(last_review) = address_review;
        // inisialisasi pointer review baru menuju elemen selanjutnya dengan elemen pertama pada list
        NEXT(address_review) = FIRST(list_review);
        // inisialisasi elemen pertama pada list dengan pointer review baru
        FIRST(list_review) = address_review;
    }
}

// prosedur insert last
void InsertLast(ListReview &list_review, AddressReview address_review)
{
    // pengecekan jika list masih kosong
    if (FIRST(list_review) == NULL)
    {
        // jika list kosong maka insert first
        InsertFirst(list_review, address_review);
    }
    else
    {
        // cari pointer elemen terakhir yang menuju ke elemen pertama
        AddressReview last_review = FIRST(list_review);
        while (NEXT(last_review) != FIRST(list_review))
        {
            last_review = NEXT(last_review);
        }
        // inisialisasi pointer review baru menuju elemen selanjutnya dengan elemen pertama pada list
        NEXT(address_review) = FIRST(list_review);
        // inisialisasi pointer elemen terakhir menuju elemen selanjutnya dengan elemen baru
        NEXT(last_review) = address_review;
    }
}

// prosedur update review
void UpdateReview(AddressReview address_review, int new_rating, string new_description)
{
    // cek jika address_review kosong
    if (address_review == NULL)
    {
        Warning("Tidak ada data.");
        getch();
    }
    else
    {
        // update data rating
        DATA(address_review).rating = new_rating;

        // cek jika variabel baru tidak kosong
        if (!new_description.empty())
        {
            // jika tidak kosong maka update data description
            DATA(address_review).description = new_description;
        }
    }
}

// prosedur delete first
void DeleteFirst(ListReview &list_review)
{
    // cek jika elemen pertama null (list kosong)
    if (FIRST(list_review) == NULL)
    {
        Warning("Tidak ada data.");
        getch();
    }
    else
    {
        // inisialisasi first_review
        AddressReview first_review = FIRST(list_review);

        // jika list hanya mempunyai satu elemen
        if (NEXT(first_review) == first_review)
        {
            // delete
            FIRST(list_review) = NULL;
        }
        else
        {
            // cari elemen terakhir
            AddressReview last_review = FIRST(list_review);
            while (NEXT(last_review) != FIRST(list_review))
            {
                last_review = NEXT(last_review);
            }
            // hubungkan elemen terakhir dengan elemen kedua
            NEXT(last_review) = NEXT(first_review);
            // elemen pertama diisi oleh elemen kedua
            FIRST(list_review) = NEXT(first_review);
        }

        // dealokasi elemen pertama
        Deallocate(first_review);
    }
}

// prosedur delete last
void DeleteLast(ListReview &list_review)
{
    // cek jika elemen pertama null (list kosong)
    if (FIRST(list_review) == NULL)
    {
        Warning("Tidak ada data.");
        getch();
    }
    else
    {
        // inisialisasi last_review
        AddressReview last_review = FIRST(list_review);

        // jika list hanya mempunyai satu elemen
        if (NEXT(last_review) == last_review)
        {
            // delete
            FIRST(list_review) = NULL;
        }
        else
        {
            // cari elemen kedua terakhir dan terakhir
            AddressReview second_last_review = FIRST(list_review);
            while (NEXT(last_review) != FIRST(list_review))
            {
                second_last_review = last_review;
                last_review = NEXT(last_review);
            }
            // hubungkan elemen kedua terakhir dengan elemen pertama
            NEXT(second_last_review) = FIRST(list_review);
        }

        // dealokasi elemen terakhir
        Deallocate(last_review);
    }
}

// prosedur delete last
void DeleteReview(ListReview &list_review, AddressReview address_review)
{
    // cek jika elemen pertama null (list kosong)
    if (FIRST(list_review) == NULL)
    {
        Warning("Tidak ada data.");
        getch();
    }
    else if (address_review != NULL)
    {
        // jika list hanya mempunyai satu elemen
        if (NEXT(address_review) == FIRST(list_review))
        {
            // delete first
            DeleteFirst(list_review);
        }
        else
        {
            // jika elemen yang dihapus adalah elemen pertama
            if (address_review == FIRST(list_review))
            {
                // delete first
                DeleteFirst(list_review);
            }
            else if (NEXT(address_review) == FIRST(list_review))
            {
                // jika elemen yang dihapus adalah elemen terakhir
                // delete last
                DeleteLast(list_review);
            }
            else
            {
                // inisialisasi variabel prev_review dengan elemen pertama pada list
                AddressReview prev_review = FIRST(list_review);
                // cari pointer elemen yang menuju ke elemen yang akan dihapus
                while (NEXT(prev_review) != address_review)
                {
                    prev_review = NEXT(prev_review);
                }
                // inisialisasi elemen yang menuju ke elemen yang dihapus dengan elemen selanjutnya dari elemen yang dihapus
                NEXT(prev_review) = NEXT(address_review);

                // dealokasi elemen
                Deallocate(address_review);
            }
        }
    }
}

// fungsi cari review by id pada list
AddressReview FindById(ListReview list_review, int id)
{
    // inisialisasi variabel ketemu
    bool ketemu = false;
    // inisialisasi variabel data_ketemu dengan null
    AddressReview data_ketemu = NULL;

    // cek jika elemen pertama tidak null (list berisi)
    if (FIRST(list_review) != NULL)
    {
        // inisialisasi variabel current dengan elemen pertama pada list
        AddressReview current = FIRST(list_review);
        do
        {
            // variabel current diisi dengan elemen selanjutnya
            current = NEXT(current);
            // jika id current sama dengan parameter id yang dicari maka ketemu
            if (DATA(current).id == id)
            {
                ketemu = true;
                data_ketemu = current;
            }
        } while (!ketemu && current != FIRST(list_review)); // loop selama tidak ketemu dan current elemen tidak sama dengan elemen pertama
    }

    // kembalikan data
    return data_ketemu;
}

// fungsi cari review by movie id pada list
void FindByMovieId(ListReview &result, ListReview list_review, int id)
{
    // cek jika elemen pertama tidak null (list berisi)
    if (FIRST(list_review) != NULL)
    {
        // inisialisasi variabel current dengan elemen pertama pada list
        AddressReview current = FIRST(list_review);
        do
        {
            // variabel current diisi dengan elemen selanjutnya
            current = NEXT(current);
            
            // inisialisasi current movie dan current reviewer
            AddressMovie current_movie = MOVIE(current);
            AddressReviewer current_reviewer = REVIEWER(current);

            // jika movie id ketemu
            if (DATA(current_movie).id == id)
            {
                // alokasi review dan insert pada list baru
                AddressReview address_review = Allocate(DATA(current), current_reviewer, current_movie);
                InsertLast(result, address_review);
            }
        } while (current != FIRST(list_review)); // loop selama current elemen tidak sama dengan elemen pertama
    }
}

// fungsi hitung total elemen pada list
int Count(ListReview list_review)
{
    // inisialisasi count
    int count = 0;

    // cek jika elemen pertama tidak null (list berisi)
    if (FIRST(list_review) != NULL)
    {
        // inisialisasi variabel current dengan elemen pertama pada list
        AddressReview current = FIRST(list_review);
        do
        {
            // variabel current diisi dengan elemen selanjutnya
            current = NEXT(current);
            count++;
        } while (current != FIRST(list_review)); // loop selama tidak ketemu dan current elemen tidak sama dengan elemen pertama
    }

    // kembalikan hasil hitung
    return count;
}

// prosedur cetak data review
void Cetak(AddressReview address_review)
{
    // cetak data review
    cout << "ID         : " << DATA(address_review).id << endl
        << "Rating     : " << DATA(address_review).rating << endl
        << "Description: " << DATA(address_review).description << endl << endl;
}

// prosedur cetak list data review
void Cetak(ListReview list_review)
{
    // inisialisasi count
    int count = 0;

    PrintTitle("VIEW LIST REVIEW");
    if (FIRST(list_review) == NULL)
    {
        // cetak info tidak ada data
        Warning("Tidak ada data.");
        getch();
    }
    else
    {
        // inisialisasi variabel current dengan elemen pertama pada list
        AddressReview current = FIRST(list_review);
        do
        {
            // cetak review
            Cetak(current);
            // variabel current diisi dengan elemen selanjutnya
            current = NEXT(current);
            count++;
        } while (current != FIRST(list_review)); // loop selama tidak ketemu dan current elemen tidak sama dengan elemen pertama

        // cetak total review
        cout << "Total Review: " << count << endl;
    }
}