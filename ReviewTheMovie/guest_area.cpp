// include library c++
#include <conio.h>
#include <iostream>
#include <string>

// include library buatan
#include "common.h"
#include "list_reviewer.h"
#include "list_movie.h"
#include "list_review.h"
#include "guest_area.h"

// using namespace
using namespace std;

// fungsi sign in
LoginUser SignIn(ListReviewer list_reviewer)
{
    // deklarasi variabel
    string username;
    string password;
    AddressReviewer reviewer;

    // inisialisasi login user guest
    LoginUser login_user = GUEST;

    // cetak header
    PrintHeader();
    PrintTitle("SIGN IN");

    // input username
    cout << "Username: ";
    getline(cin, username);

    // input password
    password = GetPassword("Password: ");

    // cek jika user adalah administrator
    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
    {
        // login user diisi administrator
        login_user = ADMINISTRATOR;
    }
    else
    {
        // cari reviewer dengan username yang diinputkan
        reviewer = FindByUsername(list_reviewer, username);

        // cek jika reviewer tidak sama dengan null dan passwordnya sama dengan yang diinputkan
        if (reviewer != NULL && DATA(reviewer).password == password)
        {
            // login user diisi reviewer
            login_user = REVIEWER;
        }
    }

    return login_user;
}

// prosedur sign up
void SignUp(ListReviewer &list_reviewer)
{
    // deklarasi variabel
    Reviewer reviewer;
    AddressReviewer address_reviewer;
    string name;
    string username;
    string password;
    string retype_password;
    int retry_password_count;
    int retry_username_count;
    bool username_sudah_ada;

    // cetak header
    PrintHeader();
    PrintTitle("SIGN UP");

    // input name
    cout << "Nama: ";
    getline(cin, name);

    // inisialisasi variabel pengulangan input username
    retry_username_count = 0;

    // label input username
InputUsernameLabel:

    // cetak header akan menghapus console sebelumnya
    PrintHeader();
    PrintTitle("SIGN UP");

    // cetak data yang diinputkan sebelumnya
    cout << "Nama: " << name << endl;

    // input username
    cout << "Username: ";
    getline(cin, username);

    // cek username didalam list
    username_sudah_ada = FindByUsername(list_reviewer, username) != NULL;

    // cek username jika sama dengan admin atau sudah ada didalam list atau tidak menginputkan karakter
    if (username == ADMIN_USERNAME || username_sudah_ada || username.empty())
    {
        // cek username jika tidak menginputkan karakter
        if (username.empty())
        {
            // cetak bahwa username tidak boleh kosong
            Warning("\nUsername tidak boleh kosong.");
        }
        else
        {
            // cetak bahwa username sudah ada didalam list
            Failed("\nUsername sudah ada.");
        }

        getch();

        // cek maksimal mengulang kesalahan input
        if (++retry_username_count < MAX_RETRY_COUNT)
        {
            // mengulang menginput username
            goto InputUsernameLabel;
        }
        else
        {
            // menuju final label
            goto FinalLabel;
        }
    }

    // inisialisasi variabel pengulangan input password
    retry_password_count = 0;

    // label input username
InputPasswordLabel:

    // cetak header akan menghapus console sebelumnya
    PrintHeader();
    PrintTitle("SIGN UP");

    // cetak data yang diinputkan sebelumnya
    cout << "Nama: " << name << endl;
    cout << "Username: " << username << endl;

    // input password
    password = GetPassword("Password: ");

    // input retype password
    retype_password = GetPassword("Retype Password: ");

    // cek apakah variabel password dan retype_password tidak sama atau tidak menginputkan karakter
    if (password != retype_password || password.empty())
    {
        // cek password jika tidak menginputkan karakter
        if (password.empty())
        {
            // cetak bahwa username tidak boleh kosong
            Warning("\nPassword tidak boleh kosong.");
        }
        else
        {
            // cetak bahwa password dan retype password tidak sama
            Failed("\nPassword tidak sama.");
        }

        getch();

        // cek maksimal mengulang kesalahan input
        if (++retry_password_count < MAX_RETRY_COUNT)
        {
            // mengulang menginput username
            goto InputPasswordLabel;
        }
        else
        {
            // menuju final label
            goto FinalLabel;
        }
    }

FinalLabel:
    // cek jika maksimal mengulang kesalahan input tercapai
    if (retry_password_count == MAX_RETRY_COUNT || retry_username_count == MAX_RETRY_COUNT)
    {
        // sign up dinyatakan gagal
        Failed("Sign Up gagal.");
    }
    else
    {
        // data sign up dibuat menjadi elemen reviewer
        reviewer = CreateReviewer(name, username, password);
        // elemen reviewer dialokasikan pada memory
        address_reviewer = Allocate(reviewer);
        // alamat memory reviewer dimasukan kedalam list dengan metode insert last
        InsertLast(list_reviewer, address_reviewer);

        // cetak bahwa sign up berhasil
        PrintHeader();
        PrintTitle("DATA REVIEWER");
        Cetak(address_reviewer);
        Success("Sign Up berhasil.");
        Success("Silahkan melakukan Sign In.");
    }
}

int findIndex(AddressMovie *arrayMovie, int arraySize, AddressMovie searchMovie)
{
    for (int i = 0; i < arraySize; i++)
    {
        if (DATA(arrayMovie[i]).id == DATA(searchMovie).id)
            return i;
    }
    return -1;
}

int compare(const void *pa, const void *pb)
{
    int *a = (int *)pa;
    int *b = (int *)pb;
    if (a[0] == b[0])
        return a[1] - b[1];
    else
        return a[0] - b[0];
}

// view top 10 movie dengan ulasan terbanyak
void ViewTopTenMovie(ListReview listReview, ListMovie listMovie)
{
    //if (FIRST(listMovie) != NULL && LAST(listMovie) != NULL){
    //    // preprocessing
    //    int totalMovie = Count(listMovie), i = 0;
    //    addressMovie arrayMovie[totalMovie] = { NULL };
    //    addressMovie temp = FIRST(listMovie);

    //    while(temp != NULL){
    //        arrayMovie[i] = temp;
    //        temp = NEXT(temp);
    //        i++;
    //    }


    //    ListReview result;
    //    CreateList(result);
    //    FindByMovieId(result, listReview, 1);

    //    // process
    //    int idxMovie = 0;
    //    int arrayMovieReviewCount[totalMovie][2] = { 0 };

    //    for(int i = 0; i < totalMovie; i++)
    //    {

    //    }


    //    // AddressReview current = first(ListReview);
    //    // addressMovie currentMovie = movie(current);
    //    // do {
    //    //     current = next(current);
    //    //     currentMovie = movie(current);
    //    //     idxMovie = findIndex(arrayMovie, totalMovie, currentMovie);
    //    //     arrayMovieReviewCount[idxMovie][0]++;
    //    //     arrayMovieReviewCount[idxMovie][1] = idxMovie;
    //    // } while (current != first(ListReview));

    //    for(i = 0; i < totalMovie; i++){
    //        printf("Count: %d\tIndex: %d\n", arrayMovieReviewCount[i][0], arrayMovieReviewCount[i][1]);
    //    }

    //    qsort(arrayMovieReviewCount, totalMovie, sizeof(*arrayMovieReviewCount), compare);

    //    printf("\n\ndata\tindex\n");
    //    for(i = 0; i < totalMovie; i++){
    //        printf("Count: %d\tIndex: %d\n", arrayMovieReviewCount[i][0], arrayMovieReviewCount[i][1]);
    //    }

    //    getch();
    //}
}