// include library c++
#include <conio.h>
#include <iostream>
#include <sstream>
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
    bool username_sudah_ada;

    // inisialisasi variabel pengulangan input username
    int retry_username_count = 0;
    // inisialisasi variabel pengulangan input password
    int retry_password_count = 0;

    // cetak header
    PrintHeader();
    PrintTitle("SIGN UP");

    // input name
    cout << "Nama: ";
    getline(cin, name);

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

// view top 10 movie dengan ulasan terbanyak
void ViewTopTenMovie(ListMovie list_movie, ListReview list_review)
{
    // deklarasi variabel
    AddressMovie address_movie;
    int id;
    string pilih_id;

    // generate data top ten movie
    ListMovie top_movies = TopTenMovies(list_movie, list_review);

    // label view
ViewLabel:

    // cetak header
    PrintHeader();

    // cetak list movie
    PrintTitle("TOP 10 MOVIES");
    Cetak(top_movies);

    // jika terdapat movie dalam list
    if (FIRST(top_movies) != NULL)
    {
        // info
        Warning("\n- Masukan ID movie untuk melihat detail.");
        Warning("- Masukan 0 untuk kembali ke menu sebelumnya.\n");

        // input nomor untuk detail
        cout << "Input: ";
        getline(cin, pilih_id);

        // convert input string ke integer
        istringstream int_stream(pilih_id);
        int_stream >> id;

        // convert integer ke string stream
        stringstream stream;
        stream << id;

        // cek hasil convert
        if (pilih_id == "0")
        {
            // menuju exit label
            goto ExitLabel;
        }
        else if (pilih_id == stream.str() && id > 0)
        {
            // cetak header
            PrintHeader();
            PrintTitle("VIEW DETAIL DATA MOVIE");

            // cari movie by id
            address_movie = FindById(top_movies, id);

            // cek pointer movie
            if (address_movie == NULL)
            {
                Warning("Movie tidak ditemukan.");
            }
            else
            {
                CetakMovieWithReview(list_review, address_movie);
            }

            getch();

            // menuju view label
            goto ViewLabel;
        }
        else
        {
            // menuju view label
            goto ViewLabel;
        }
    }

ExitLabel:
    // delete all data to save memory
    DeleteAll(top_movies);
}