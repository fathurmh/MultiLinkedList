// include library c++
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

// include library buatan
#include "common.h"
#include "list_reviewer.h"
#include "list_movie.h"
#include "review.h"
#include "admin_area.h"

// using namespace
using namespace std;

// prosedur menu admin
void menuAdmin(ListReviewer &listReviewer, ListMovie &listMovie, ListReview listReview) {
    // deklarasi variabel
    char mainMenu;

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
    cin >> mainMenu;
    cin.ignore();

    // check kondisi pilihan
    switch (mainMenu) {
        case '1' : { // Input Data Movie
            inputDataMovie(listMovie);

            // menuju label main menu
            goto MainMenuLabel;
        }
        case '2' : { // Update Data Movie
            updateDataMovie(listMovie);

            // menuju label main menu
            goto MainMenuLabel;
        }
        case '3' : { // View Data Movie
            viewDataMovie(listMovie, listReview);

            // menuju label main menu
            goto MainMenuLabel;
        }
        case '4' : { // Delete Data Movie
            deleteDataMovie(listMovie);

            // menuju label main menu
            goto MainMenuLabel;
        }
        case '5' : { // View Data Reviewer
            viewDataReviewer(listReviewer);

            // menuju label main menu
            goto MainMenuLabel;
        }
        case '6' : { // Delete Data Reviewer
            deleteDataReviewer(listReviewer);

            // menuju label main menu
            goto MainMenuLabel;
        }
        case '9' : { // Sign Out
            cout << endl;
            Success("Signed out, see you next time.");
            getch();
        }
        break;
        case '0' : { // Exit
            cout << endl;
            Success("Good bye, see you next time.");
            getch();
            exit(0);
        }
        break;
        default : {
            // menuju label main menu
            goto MainMenuLabel;
        }
    }
}

// prosedur input data movie
void inputDataMovie(ListMovie listMovie) {
    // deklarasi variabel
    Movie movie;
    AddressMovie addressMovie;
    string title;
    string director;
    string actors;
    string genre;
    string runningTime;
    string releaseDate;
    int retryTitleCount;
    bool titleSudahAda;

    // inisialisasi variabel pengulangan input username
    retryTitleCount = 0;

    // label input title
    InputTitleLabel:

    // cetak header
    PrintHeader();
    PrintTitle("INPUT DATA MOVIE");

    // input title
    cout << "Title: ";
    getline(cin, title);

    // cek title didalam list
    titleSudahAda = FindByTitle(listMovie, title) != NULL;

    // cek title jika sudah ada didalam list atau tidak menginputkan karakter
    if (titleSudahAda || title.empty()) {
        // cek title jika tidak menginputkan karakter
        if (title.empty()) {
            // cetak bahwa title tidak boleh kosong
            Warning("\nTitle tidak boleh kosong.");
        } else {
            // cetak bahwa title sudah ada didalam list
            Failed("\nTitle sudah ada.");
        }

        getch();

        // cek maksimal mengulang kesalahan input
        if (++retryTitleCount < MAX_RETRY_COUNT) {
            // mengulang menginput username
            goto InputTitleLabel;
        } else {
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

    // input runningTime
    cout << "Running Time: ";
    getline(cin, runningTime);

    // input releaseDate
    cout << "ReleaseDate: ";
    getline(cin, releaseDate);

    FinalLabel:
    // cek jika maksimal mengulang kesalahan input tercapai
    if (retryTitleCount == MAX_RETRY_COUNT) {
        // sign up dinyatakan gagal
        Failed("Input Data gagal.");
    } else {
        // data hasil input dibuat menjadi elemen movie
        movie = CreateMovie(title, director, actors, genre, runningTime, releaseDate);

        // elemen movie dialokasikan pada memory
        addressMovie = Allocate(movie);

        // alamat memory movie dimasukan kedalam list dengan metode insert last
        InsertLast(listMovie, addressMovie);

        // cetak bahwa input data berhasil
        PrintHeader();
        PrintTitle("DATA MOVIE");
        Cetak(addressMovie);
        Success("Input Data berhasil.");
    }
    getch();
}

// prosedur update data movie
void updateDataMovie(ListMovie listMovie) {
    // deklarasi variabel
    int id;
    string pilihId;
    string title;
    string director;
    string actors;
    string genre;
    string runningTime;
    string releaseDate;
    string ensureUpdate;
    AddressMovie movie;

    // label view
    ViewLabel:

    // cetak header
    PrintHeader();

    // cetak list movie
    Cetak(listMovie);

    // jika terdapat movie dalam list
    if (FIRST(listMovie) != NULL) {
        // info
        Warning("\n- Masukan ID movie yang akan diupdate.");
        Warning("- Masukan 0 untuk kembali ke menu sebelumnya.\n");

        // input nomor untuk detail
        cout << "Input: ";
        getline(cin, pilihId);

        // convert input string ke integer
        istringstream intStream(pilihId);
        intStream >> id;

        // convert integer ke string stream
        stringstream stream;
        stream << id;

        // cek hasil convert
        if (pilihId == "0") {
            // menuju exit label
            goto ExitLabel;
        } else if (pilihId == stream.str() && id > 0) {
            // cetak header
            PrintHeader();
            PrintTitle("UPDATE DATA MOVIE");

            // cari movie by id
            movie = FindById(listMovie, id);

            // cek pointer movie
            if (movie == NULL) {
                Warning("Movie tidak ditemukan.");
            } else {
                // cetak detail movie
                Warning("Jangan inputkan data untuk mengisi field seperti default.\n");
                Warning("Default data:");
                Cetak(movie);

                // input title
                cout << "Title: ";
                getline(cin, title);

                // cek jika inputan kosong, tampilkan default
                if (title.empty()) {
                    RemoveLastLine();
                    cout << "Title: " << DATA(movie).title << endl;
                }

                // input director
                cout << "Director: ";
                getline(cin, director);

                // cek jika inputan kosong, tampilkan default
                if (director.empty()) {
                    RemoveLastLine();
                    cout << "Director: " << DATA(movie).director << endl;
                }

                // input actors
                cout << "Actors: ";
                getline(cin, actors);

                // cek jika inputan kosong, tampilkan default
                if (actors.empty()) {
                    RemoveLastLine();
                    cout << "Actors: " << DATA(movie).actors << endl;
                }

                // input genre
                cout << "Genre: ";
                getline(cin, genre);

                // cek jika inputan kosong, tampilkan default
                if (genre.empty()) {
                    RemoveLastLine();
                    cout << "Genre: " << DATA(movie).genre << endl;
                }

                // input runningTime
                cout << "Running Time: ";
                getline(cin, runningTime);

                // cek jika inputan kosong, tampilkan default
                if (runningTime.empty()) {
                    RemoveLastLine();
                    cout << "Running Time: " << DATA(movie).running_time << endl;
                }

                // input releaseDate
                cout << "Release Date: ";
                getline(cin, releaseDate);

                // cek jika inputan kosong, tampilkan default
                if (releaseDate.empty()) {
                    RemoveLastLine();
                    cout << "Release Date: " << DATA(movie).release_date << endl;
                }

                // ensure
                Warning("Anda yakin ingin mengupdate?");
                cout << "Jawaban (y/n): ";
                getline(cin, ensureUpdate);

                // update jika jawaban Y atau y
                if (ensureUpdate == "Y" || ensureUpdate == "y") {
                    // update movie
                    UpdateMovie(movie, title, director, actors, genre, runningTime, releaseDate);
                    Success("\nData berhasil diupdate.");
                } else {
                    Success("\nData tidak diupdate.");
                }
            }

            getch();

            // menuju view label
            goto ViewLabel;
        } else {
            // menuju view label
            goto ViewLabel;
        }
    }

    ExitLabel: ;
}

// prosedur view data movie
void viewDataMovie(ListMovie listMovie, ListReview listReview) {
    // deklarasi variabel
    int id;
    string pilihId;
    AddressMovie movie;

    // label view
    ViewLabel:

    // cetak header
    PrintHeader();

    // cetak list movie
    Cetak(listMovie);

    // jika terdapat movie dalam list
    if (FIRST(listMovie) != NULL) {
        // info
        Warning("\n- Masukan ID movie untuk melihat detail.");
        Warning("- Masukan 0 untuk kembali ke menu sebelumnya.\n");

        // input nomor untuk detail
        cout << "Input: ";
        getline(cin, pilihId);

        // convert input string ke integer
        istringstream intStream(pilihId);
        intStream >> id;

        // convert integer ke string stream
        stringstream stream;
        stream << id;

        // cek hasil convert
        if (pilihId == "0") {
            // menuju exit label
            goto ExitLabel;
        } else if (pilihId == stream.str() && id > 0) {
            // cetak header
            PrintHeader();
            PrintTitle("VIEW DETAIL DATA MOVIE");

            // cari movie by id
            movie = FindById(listMovie, id);

            // cek pointer movie
            if (movie == NULL) {
                Warning("Movie tidak ditemukan.");
            } else {
                // deklarasi review
                ListReview listReviewByMovie;
                createList(listReviewByMovie);

                // cari review berdasarkan movie id
                findByMovieId(listReviewByMovie, listReview, id);

                // cetak detail movie
                Cetak(movie);
                cetak(listReviewByMovie);
            }

            getch();

            // menuju view label
            goto ViewLabel;
        } else {
            // menuju view label
            goto ViewLabel;
        }
    }

    ExitLabel: ;
}

// prosedur delete data movie
void deleteDataMovie(ListMovie &listMovie) {
    // deklarasi variabel
    int id;
    string pilihId;
    string ensureUpdate;
    AddressMovie movie;

    // label view
    ViewLabel:

    // cetak header
    PrintHeader();

    // cetak list movie
    Cetak(listMovie);

    // jika terdapat movie dalam list
    if (FIRST(listMovie) != NULL) {
        // info
        Warning("\n- Masukan ID movie yang akan dihapus.");
        Warning("- Masukan 0 untuk kembali ke menu sebelumnya.\n");

        // input nomor untuk detail
        cout << "Input: ";
        getline(cin, pilihId);

        // convert input string ke integer
        istringstream intStream(pilihId);
        intStream >> id;

        // convert integer ke string stream
        stringstream stream;
        stream << id;

        // cek hasil convert
        if (pilihId == "0") {
            // menuju exit label
            goto ExitLabel;
        } else if (pilihId == stream.str() && id > 0) {
            // cetak header
            PrintHeader();
            PrintTitle("DELETE DATA MOVIE");

            // cari movie by id
            movie = FindById(listMovie, id);

            // cek pointer movie
            if (movie == NULL) {
                Warning("Movie tidak ditemukan.");
            } else {
                // cetak detail movie
                Cetak(movie);

                // ensure
                Warning("Anda yakin ingin menghapus?");
                cout << "Jawaban (y/n): ";
                getline(cin, ensureUpdate);

                // hapus jika jawaban Y atau y
                if (ensureUpdate == "Y" || ensureUpdate == "y") {
                    // delete movie
                    DeleteMovie(listMovie, movie);
                    Success("\nData berhasil dihapus.");
                } else {
                    Success("\nData tidak dihapus.");
                }
            }

            getch();

            // menuju view label
            goto ViewLabel;
        } else {
            // menuju view label
            goto ViewLabel;
        }
    }

    ExitLabel: ;
}

// prosedur view data reviewer
void viewDataReviewer(ListReviewer listReviewer) {
    // deklarasi variabel
    int id;
    string pilihId;
    AddressReviewer reviewer;

    // label view
    ViewLabel:

    // cetak header
    PrintHeader();

    // cetak list reviewer
    Cetak(listReviewer);

    // jika terdapat reviewer dalam list
    if (FIRST(listReviewer) != NULL) {
        // info
        Warning("\n- Masukan ID reviewer untuk melihat detail.");
        Warning("- Masukan 0 untuk kembali ke menu sebelumnya.\n");

        // input nomor untuk detail
        cout << "Input: ";
        getline(cin, pilihId);

        // convert input string ke integer
        istringstream intStream(pilihId);
        intStream >> id;

        // convert integer ke string stream
        stringstream stream;
        stream << id;

        // cek hasil convert
        if (pilihId == "0") {
            // menuju exit label
            goto ExitLabel;
        } else if (pilihId == stream.str() && id > 0) {
            // cetak header
            PrintHeader();
            PrintTitle("VIEW DETAIL DATA REVIEWER");

            // cari reviewer by id
            reviewer = FindById(listReviewer, id);

            // cek pointer reviewer
            if (reviewer == NULL) {
                Warning("Reviewer tidak ditemukan.");
            } else {
                // cetak detail reviewer
                Cetak(reviewer);
            }

            getch();

            // menuju view label
            goto ViewLabel;
        } else {
            // menuju view label
            goto ViewLabel;
        }
    }

    ExitLabel: ;
}

// prosedur delete data reviewer
void deleteDataReviewer(ListReviewer &listReviewer) {
    // deklarasi variabel
    int id;
    string pilihId;
    string ensureUpdate;
    AddressReviewer reviewer;

    // label view
    ViewLabel:

    // cetak header
    PrintHeader();

    // cetak list reviewer
    Cetak(listReviewer);

    // jika terdapat reviewer dalam list
    if (FIRST(listReviewer) != NULL) {
        // info
        Warning("\n- Masukan ID reviewer yang akan dihapus.");
        Warning("- Masukan 0 untuk kembali ke menu sebelumnya.\n");

        // input nomor untuk detail
        cout << "Input: ";
        getline(cin, pilihId);

        // convert input string ke integer
        istringstream intStream(pilihId);
        intStream >> id;

        // convert integer ke string stream
        stringstream stream;
        stream << id;

        // cek hasil convert
        if (pilihId == "0") {
            // menuju exit label
            goto ExitLabel;
        } else if (pilihId == stream.str() && id > 0) {
            // cetak header
            PrintHeader();
            PrintTitle("DELETE DATA REVIEWER");

            // cari reviewer by id
            reviewer = FindById(listReviewer, id);

            // cek pointer reviewer
            if (reviewer == NULL) {
                Warning("Reviewer tidak ditemukan.");
            } else {
                // cetak detail reviewer
                Cetak(reviewer);

                // ensure
                Warning("Anda yakin ingin menghapus?");
                cout << "Jawaban (y/n): ";
                getline(cin, ensureUpdate);

                // hapus jika jawaban Y atau y
                if (ensureUpdate == "Y" || ensureUpdate == "y") {
                    // delete reviewer
                    DeleteReviewer(listReviewer, reviewer);
                    Success("\nData berhasil dihapus.");
                } else {
                    Success("\nData tidak dihapus.");
                }
            }

            getch();

            // menuju view label
            goto ViewLabel;
        } else {
            // menuju view label
            goto ViewLabel;
        }
    }

    ExitLabel: ;
}
