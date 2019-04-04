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
#include "admin_area.h"

// using namespace
using namespace std;

// prosedur menu admin
void MenuAdmin(ListReviewer &list_reviewer, ListMovie &list_movie, ListReview &list_review)
{
    // deklarasi variabel
    char main_menu;

    // label main menu
MainMenuLabel:

    // cetak header
    PrintHeader();

    // cetak menu utama
    PrintTitle("MAIN MENU");
    cout << "1. Input Data Movie" << endl
        << "2. Update Data Movie" << endl
        << "3. View Data Movie" << endl
        << "4. Delete Data Movie" << endl << endl
        << "5. View Data Reviewer" << endl
        << "6. Delete Data Reviewer" << endl << endl
        << "9. Sign Out" << endl
        << "0. Exit" << endl << endl;
    cout << "Pilih Menu: ";

    // input pilihan menu
    cin >> main_menu;
    cin.ignore();

    // check kondisi pilihan
    switch (main_menu)
    {
    case '1': // Input Data Movie
    {
        InputDataMovie(list_movie);

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '2': // Update Data Movie
    {
        UpdateDataMovie(list_movie);

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '3': // View Data Movie
    {
        ViewDataMovie(list_movie, list_review);

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '4': // Delete Data Movie
    {
        DeleteDataMovie(list_review, list_movie);

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '5': // View Data Reviewer
    {
        ViewDataReviewer(list_reviewer, list_review);

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '6': // Delete Data Reviewer
    {
        DeleteDataReviewer(list_review, list_reviewer);

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '9': // Sign Out
    {
        cout << endl;
        Success("Signed out, see you next time.");
        getch();
    }
    break;
    case '0': // Exit
    {
        cout << endl;
        Success("Good bye, see you next time.");
        getch();

        // delete all data to save memory
        DeleteAll(list_reviewer);
        DeleteAll(list_movie);
        DeleteAll(list_review);

        exit(0);
    }
    break;
    default:
    {
        // menuju label main menu
        goto MainMenuLabel;
    }
    }
}

// prosedur input data movie
void InputDataMovie(ListMovie &list_movie)
{
    // deklarasi variabel
    Movie movie;
    AddressMovie address_movie;
    string title;
    string director;
    string actors;
    string genre;
    string running_time;
    string release_date;
    int retry_title_count;
    bool title_sudah_ada;

    // inisialisasi variabel pengulangan input username
    retry_title_count = 0;

    // label input title
InputTitleLabel:

    // cetak header
    PrintHeader();
    PrintTitle("INPUT DATA MOVIE");

    // input title
    cout << "Title: ";
    getline(cin, title);

    // cek title didalam list
    title_sudah_ada = FindByTitle(list_movie, title) != NULL;

    // cek title jika sudah ada didalam list atau tidak menginputkan karakter
    if (title_sudah_ada || title.empty())
    {
        // cek title jika tidak menginputkan karakter
        if (title.empty())
        {
            // cetak bahwa title tidak boleh kosong
            Warning("\nTitle tidak boleh kosong.");
        }
        else
        {
            // cetak bahwa title sudah ada didalam list
            Failed("\nTitle sudah ada.");
        }

        getch();

        // cek maksimal mengulang kesalahan input
        if (++retry_title_count < MAX_RETRY_COUNT)
        {
            // mengulang menginput username
            goto InputTitleLabel;
        }
        else
        {
            // menuju final label
            goto FinalLabel;
        }
    }

    // input director
    cout << "Director: ";
    getline(cin, director);

    // input actors
    cout << "Actors: ";
    getline(cin, actors);

    // input genre
    cout << "Genre: ";
    getline(cin, genre);

    // input running_time
    cout << "Running Time: ";
    getline(cin, running_time);

    // input release_date
    cout << "Release Date: ";
    getline(cin, release_date);

FinalLabel:
    // cek jika maksimal mengulang kesalahan input tercapai
    if (retry_title_count == MAX_RETRY_COUNT)
    {
        // sign up dinyatakan gagal
        Failed("Input Data gagal.");
    }
    else
    {
        // data hasil input dibuat menjadi elemen movie
        movie = CreateMovie(title, director, actors, genre, running_time, release_date);

        // elemen movie dialokasikan pada memory
        address_movie = Allocate(movie);

        // alamat memory movie dimasukan kedalam list dengan metode insert last
        InsertLast(list_movie, address_movie);

        // cetak bahwa input data berhasil
        PrintHeader();
        PrintTitle("DATA MOVIE");
        Cetak(address_movie);
        Success("Input Data berhasil.");
    }
    getch();
}

// prosedur update data movie
void UpdateDataMovie(ListMovie &list_movie)
{
    // deklarasi variabel
    AddressMovie address_movie;
    int id;
    string pilih_id;
    string title;
    string director;
    string actors;
    string genre;
    string running_time;
    string release_date;
    string ensure_update;

    // label view
ViewLabel:

    // cetak header
    PrintHeader();

    // cetak list movie
    Cetak(list_movie);

    // jika terdapat movie dalam list
    if (FIRST(list_movie) != NULL)
    {
        // info
        Warning("\n- Masukan ID movie yang akan diupdate.");
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
            PrintTitle("UPDATE DATA MOVIE");

            // cari movie by id
            address_movie = FindById(list_movie, id);

            // cek pointer movie
            if (address_movie == NULL)
            {
                Warning("Movie tidak ditemukan.");
            }
            else
            {
                // cetak detail movie
                Warning("Jangan inputkan data untuk mengisi field seperti default.\n");
                Warning("Default data:");
                Cetak(address_movie);

                // input title
                cout << "Title: ";
                getline(cin, title);

                // cek jika inputan kosong, tampilkan default
                if (title.empty())
                {
                    RemoveLastLine();
                    cout << "Title: " << DATA(address_movie).title << endl;
                }

                // input director
                cout << "Director: ";
                getline(cin, director);

                // cek jika inputan kosong, tampilkan default
                if (director.empty())
                {
                    RemoveLastLine();
                    cout << "Director: " << DATA(address_movie).director << endl;
                }

                // input actors
                cout << "Actors: ";
                getline(cin, actors);

                // cek jika inputan kosong, tampilkan default
                if (actors.empty())
                {
                    RemoveLastLine();
                    cout << "Actors: " << DATA(address_movie).actors << endl;
                }

                // input genre
                cout << "Genre: ";
                getline(cin, genre);

                // cek jika inputan kosong, tampilkan default
                if (genre.empty())
                {
                    RemoveLastLine();
                    cout << "Genre: " << DATA(address_movie).genre << endl;
                }

                // input running_time
                cout << "Running Time: ";
                getline(cin, running_time);

                // cek jika inputan kosong, tampilkan default
                if (running_time.empty())
                {
                    RemoveLastLine();
                    cout << "Running Time: " << DATA(address_movie).running_time << endl;
                }

                // input release_date
                cout << "Release Date: ";
                getline(cin, release_date);

                // cek jika inputan kosong, tampilkan default
                if (release_date.empty())
                {
                    RemoveLastLine();
                    cout << "Release Date: " << DATA(address_movie).release_date << endl;
                }

                // ensure
                Warning("\nAnda yakin ingin mengupdate?");
                cout << "Jawaban (y/n): ";
                getline(cin, ensure_update);

                // update jika jawaban Y atau y
                if (ensure_update == "Y" || ensure_update == "y")
                {
                    // update movie
                    UpdateMovie(address_movie, title, director, actors, genre, running_time, release_date);
                    Success("\nData berhasil diupdate.");
                }
                else
                {
                    Success("\nData tidak diupdate.");
                }
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

ExitLabel:;
}

// prosedur view data movie
void ViewDataMovie(ListMovie list_movie, ListReview list_review)
{
    // deklarasi variabel
    AddressMovie address_movie;
    int id;
    string pilih_id;

    // label view
ViewLabel:

    // cetak header
    PrintHeader();

    // cetak list movie
    Cetak(list_movie);

    // jika terdapat movie dalam list
    if (FIRST(list_movie) != NULL)
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
            address_movie = FindById(list_movie, id);

            // cek pointer movie
            if (address_movie == NULL)
            {
                Warning("Movie tidak ditemukan.");
            }
            else
            {
                // cetak movie with review
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

ExitLabel:;
}

// prosedur delete data movie
void DeleteDataMovie(ListReview &list_review, ListMovie &list_movie)
{
    // deklarasi variabel
    int id;
    string pilih_id;
    string ensure_update;
    AddressMovie address_movie;

    // label view
ViewLabel:

    // cetak header
    PrintHeader();

    // cetak list movie
    Cetak(list_movie);

    // jika terdapat movie dalam list
    if (FIRST(list_movie) != NULL)
    {
        // info
        Warning("\n- Masukan ID movie yang akan dihapus.");
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
            PrintTitle("DELETE DATA MOVIE");

            // cari movie by id
            address_movie = FindById(list_movie, id);

            // cek pointer movie
            if (address_movie == NULL)
            {
                Warning("Movie tidak ditemukan.");
            }
            else
            {
                // cetak detail movie
                CetakMovieWithReview(list_review, address_movie);

                // ensure
                Warning("\nReview yang telah diberikan akan terhapus.");
                Warning("Anda yakin ingin menghapus?");
                cout << "Jawaban (y/n): ";
                getline(cin, ensure_update);

                // hapus jika jawaban Y atau y
                if (ensure_update == "Y" || ensure_update == "y")
                {
                    // delete movie with review
                    DeleteMovieWithReview(list_review, list_movie, address_movie);
                    Success("\nData berhasil dihapus.");
                }
                else
                {
                    Success("\nData tidak dihapus.");
                }
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

ExitLabel:;
}

// prosedur view data reviewer
void ViewDataReviewer(ListReviewer list_reviewer, ListReview list_review)
{
    // deklarasi variabel
    int id;
    string pilih_id;
    AddressReviewer address_reviewer;

    // label view
ViewLabel:

    // cetak header
    PrintHeader();

    // cetak list reviewer
    Cetak(list_reviewer);

    // jika terdapat reviewer dalam list
    if (FIRST(list_reviewer) != NULL)
    {
        // info
        Warning("\n- Masukan ID reviewer untuk melihat detail.");
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
            PrintTitle("VIEW DETAIL DATA REVIEWER");

            // cari reviewer by id
            address_reviewer = FindById(list_reviewer, id);

            // cek pointer reviewer
            if (address_reviewer == NULL)
            {
                Warning("Reviewer tidak ditemukan.");
            }
            else
            {
                // cetak reviewer with review
                CetakReviewerWithReview(list_review, address_reviewer);
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

ExitLabel:;
}

// prosedur delete data reviewer
void DeleteDataReviewer(ListReview &list_review, ListReviewer &list_reviewer)
{
    // deklarasi variabel
    int id;
    string pilih_id;
    string ensure_update;
    AddressReviewer address_reviewer;

    // label view
ViewLabel:

    // cetak header
    PrintHeader();

    // cetak list reviewer
    Cetak(list_reviewer);

    // jika terdapat reviewer dalam list
    if (FIRST(list_reviewer) != NULL)
    {
        // info
        Warning("\n- Masukan ID reviewer yang akan dihapus.");
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
            PrintTitle("DELETE DATA REVIEWER");

            // cari reviewer by id
            address_reviewer = FindById(list_reviewer, id);

            // cek pointer reviewer
            if (address_reviewer == NULL)
            {
                Warning("Reviewer tidak ditemukan.");
            }
            else
            {
                // cetak detail reviewer
                CetakReviewerWithReview(list_review, address_reviewer);

                // ensure
                Warning("\nReview yang telah diberikan akan terhapus.");
                Warning("Anda yakin ingin menghapus?");
                cout << "Jawaban (y/n): ";
                getline(cin, ensure_update);

                // hapus jika jawaban Y atau y
                if (ensure_update == "Y" || ensure_update == "y")
                {
                    // delete reviewer with review
                    DeleteReviewerWithReview(list_review, list_reviewer, address_reviewer);
                    Success("\nData berhasil dihapus.");
                }
                else
                {
                    Success("\nData tidak dihapus.");
                }
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

ExitLabel:;
}
