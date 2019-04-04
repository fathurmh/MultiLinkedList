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

// fungsi alokasi array
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
void Deallocate(AddressReview *(&address_review))
{
    delete[] address_review;
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
        if (NEXT(FIRST(list_review)) == FIRST(list_review))
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

// prosedur delete all
void DeleteAll(ListReview &list_review)
{
    // cek jika elemen pertama null (list kosong)
    if (FIRST(list_review) != NULL)
    {
        // inisialisasi variabel current dengan elemen kedua pada list
        AddressReview current = NEXT(FIRST(list_review));

        // loop selama current tidak sama dengan elemen pertama
        while (current != FIRST(list_review))
        {
            AddressReview delete_current = current;
            current = NEXT(current);

            // delete current
            DeleteReview(list_review, delete_current);
        }

        // delete elemen pertama
        DeleteFirst(list_review);
    }
}

// prosedur delete reviewer with all reviews
void DeleteReviewerWithReview(ListReview &list_review, ListReviewer &list_reviewer, AddressReviewer address_reviewer)
{
    // inisialisasi array review by reviewer id
    AddressReview *reviewer_reviews = FindByReviewerId(list_review, DATA(address_reviewer).id);

    // inisialisasi panjang array
    int length = Count(reviewer_reviews);

    // jika reviewer mempunyai review
    if (length > 0)
    {
        // loop seluruh review
        for (int i = 0; i < length; i++)
        {
            // delete review
            DeleteReview(list_review, reviewer_reviews[i]);
        }
    }

    // delete reviewer
    DeleteReviewer(list_reviewer, address_reviewer);

    // dealokasi memory array karena sudah tidak digunakan
    Deallocate(reviewer_reviews);
}

// prosedur delete movie with all reviews
void DeleteMovieWithReview(ListReview &list_review, ListMovie &list_movie, AddressMovie address_movie)
{
    // inisialisasi array review by movie id
    AddressReview *movie_reviews = FindByMovieId(list_review, DATA(address_movie).id);

    // inisialisasi panjang array
    int length = Count(movie_reviews);

    // jika movie mempunyai review
    if (length > 0)
    {
        // loop seluruh review
        for (int i = 0; i < length; i++)
        {
            // delete review
            DeleteReview(list_review, movie_reviews[i]);
        }
    }

    // delete movie
    DeleteMovie(list_movie, address_movie);

    // dealokasi memory array karena sudah tidak digunakan
    Deallocate(movie_reviews);
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

// fungsi cari review by id pada array
AddressReview FindById(AddressReview *array_review, int id)
{
    // inisialisasi variabel ketemu
    bool ketemu = false;
    // inisialisasi variabel data_ketemu dengan null
    AddressReview data_ketemu = NULL;
    // hitung total_review
    int total_review = Count(array_review);

    // cek review lebih dari 0
    if (total_review > 0)
    {
        // loop selama tidak ketemu
        for (int i = 0; i < total_review && !ketemu; i++)
        {
            // jika id current sama dengan parameter id yang dicari maka ketemu
            if (DATA(array_review[i]).id == id)
            {
                ketemu = true;
                data_ketemu = array_review[i];
            }
        }
    }

    // kembalikan data
    return data_ketemu;
}

// fungsi cari review by movie id pada list
AddressReview *FindByMovieId(ListReview list_review, int id)
{
    // inisialisasi array hasil pencarian
    AddressReview *result = Allocate(Count(list_review));

    // cek jika elemen pertama tidak null (list berisi)
    if (FIRST(list_review) != NULL)
    {
        // inisialisasi variabel current dengan elemen pertama pada list
        AddressReview current = FIRST(list_review);
        int index = 0;
        do
        {
            // variabel current diisi dengan elemen selanjutnya
            current = NEXT(current);
            // inisialisasi current movie
            AddressMovie current_movie = MOVIE(current);

            // jika movie id ketemu
            if (DATA(current_movie).id == id)
            {
                // alokasi review dan insert pada list baru
                result[index++] = current;
            }
        } while (current != FIRST(list_review)); // loop selama current elemen tidak sama dengan elemen pertama
    }

    // kembalikan array hasil
    return result;
}

// fungsi cari review by reviewer id pada list
AddressReview *FindByReviewerId(ListReview list_review, int id)
{
    // inisialisasi array hasil pencarian
    AddressReview *result = Allocate(Count(list_review));

    // cek jika elemen pertama tidak null (list berisi)
    if (FIRST(list_review) != NULL)
    {
        // inisialisasi variabel current dengan elemen pertama pada list
        AddressReview current = FIRST(list_review);
        int index = 0;
        do
        {
            // variabel current diisi dengan elemen selanjutnya
            current = NEXT(current);
            // inisialisasi current reviewer
            AddressReviewer current_reviewer = REVIEWER(current);

            // jika reviewer id ketemu
            if (DATA(current_reviewer).id == id)
            {
                // alokasi review dan insert pada list baru
                result[index++] = current;
            }
        } while (current != FIRST(list_review)); // loop selama current elemen tidak sama dengan elemen pertama
    }

    // kembalikan array hasil
    return result;
}

// fungsi generate top 10 movie
ListMovie TopTenMovies(ListMovie list_movie, ListReview list_review)
{
    ListMovie top_movies;
    CreateList(top_movies);

    if (FIRST(list_movie) != NULL && LAST(list_movie) != NULL)
    {
        // inisialisasi total movie
        int total_movie = Count(list_movie);

        // alokasi array
        int *movie_reviews_count = Allocate(total_movie, 2);
        int index = 0;

        // inisialisasi variabel current dengan elemen pertama pada list
        AddressMovie current_movie = FIRST(list_movie);

        // hitung review selama current movie tidak sama dengan null
        while (current_movie != NULL)
        {
            // masukan id movie kedalam variabel
            int current_movie_id = DATA(current_movie).id;

            // inisialisasi array review by movie id
            AddressReview *current_movie_reviews = FindByMovieId(list_review, current_movie_id);
            // hitung total reviews;
            int total_reviews = Count(current_movie_reviews);

            // masukan id movie kedalam array kolom 0
            movie_reviews_count[index] = current_movie_id;
            // masukan total review kedalam array kolom 1
            movie_reviews_count[index + total_movie] = total_reviews;

            // dealokasi memory array
            Deallocate(current_movie_reviews);

            // next movie
            current_movie = NEXT(current_movie);
            index++;
        }

        // menggunakan algoritma bubble sort
        bool swapped;
        for (int i = 0; i < total_movie - 1; i++)
        {
            swapped = false;
            for (int j = 0; j < total_movie - i - 1; j++)
            {
                // cek jika review count ke j lebih kecil dari j+1 maka tukar
                if (movie_reviews_count[j+total_movie] < movie_reviews_count[j + total_movie + 1])
                {
                    // tukar movie id
                    Tukar(&movie_reviews_count[j], &movie_reviews_count[j + 1]);

                    // tukar review count
                    Tukar(&movie_reviews_count[j + total_movie], &movie_reviews_count[j + total_movie + 1]);

                    // tandai sudah ditukar
                    swapped = true;
                }
            }

            // jika tidak ada lagi yang ditukar
            if (swapped == false)
                break;
        }

        // insert ke list baru
        for (int i = 0; i < total_movie && i < 10; i++)
        {
            // address movie lama
            AddressMovie address_movie = FindById(list_movie, movie_reviews_count[i]);
            // alokasikan untuk list baru
            AddressMovie new_address_movie = Allocate(DATA(address_movie));
            // insert ke list top 10
            InsertLast(top_movies, new_address_movie);
        }

        // dealokasi memory array
        Deallocate(movie_reviews_count);
    }

    // kembalikan top movies
    return top_movies;
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

// fungsi hitung total elemen pada array
int Count(AddressReview *address_review)
{
    // inisialisasi count
    int count = 0;
    // hitung elemen array
    while (address_review[count++] != NULL) { }
    // kembalikan hasil hitung
    return --count;
}

// prosedur cetak data review
void Cetak(AddressReview address_review)
{
    // cetak data review
    cout << "ID         : " << DATA(address_review).id << endl
        << "Rating     : " << DATA(address_review).rating << endl
        << "Description: " << DATA(address_review).description << endl << endl;
}

// prosedur cetak data review with reviewer
void CetakWithReviewer(AddressReview address_review)
{
    // cetak data review with movie
    cout << "Reviewed by: " << DATA(REVIEWER(address_review)).name << endl;
    Cetak(address_review);
}

// prosedur cetak data review with movie
void CetakWithMovie(AddressReview address_review)
{
    // cetak data review with movie
    cout << "Reviews on : " << DATA(MOVIE(address_review)).title << endl;
    Cetak(address_review);
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

// prosedur cetak list data review dan reviewernya
void CetakReviewerWithReview(ListReview list_review, AddressReviewer address_reviewer)
{
    // inisialisasi array review by reviewer id
    AddressReview *reviewer_reviews = FindByReviewerId(list_review, DATA(address_reviewer).id);

    // inisialisasi panjang array
    int length = Count(reviewer_reviews);

    // cetak reviewer
    Cetak(address_reviewer);

    PrintTitle("LIST REVIEW");
    for (int i = 0; i < length; i++)
    {
        // cetak review with movie
        CetakWithMovie(reviewer_reviews[i]);
    }

    // cetak total review
    cout << "Total Review: " << length << endl;

    // dealokasi memory array karena sudah tidak digunakan
    Deallocate(reviewer_reviews);
}

// prosedur cetak list data review dan movienya
void CetakMovieWithReview(ListReview list_review, AddressMovie address_movie)
{
    // inisialisasi array review by movie id
    AddressReview *movie_reviews = FindByMovieId(list_review, DATA(address_movie).id);

    // inisialisasi panjang array
    int length = Count(movie_reviews);

    // cetak movie
    Cetak(address_movie);

    PrintTitle("LIST REVIEW");
    for (int i = 0; i < length; i++)
    {
        // cetak review with reviewer
        CetakWithReviewer(movie_reviews[i]);
    }

    // cetak total review
    cout << "Total Review: " << length << endl;

    // dealokasi memory array karena sudah tidak digunakan
    Deallocate(movie_reviews);
}
