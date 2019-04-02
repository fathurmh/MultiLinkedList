// include library c++
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <sstream>

// include library buatan
#include "admin_area.h"

// using namespace
using namespace std;

// prosedur menu admin
void menuAdmin(listReviewer &listReviewer, listMovie &listMovie, ListReview listReview) {
    // deklarasi variabel
    char mainMenu;

    // label main menu
    MainMenuLabel:

    // cetak header
    printHeader();

    // cetak menu utama
    printTitle("MAIN MENU");
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
            success("Signed out, see you next time.");
            getch();
        }
        break;
        case '0' : { // Exit
            cout << endl;
            success("Good bye, see you next time.");
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
void inputDataMovie(listMovie listMovie) {
    // deklarasi variabel
    movie movie;
    addressMovie addressMovie;
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
    printHeader();
    printTitle("INPUT DATA MOVIE");

    // input title
    cout << "Title: ";
    getline(cin, title);

    // cek title didalam list
    titleSudahAda = searchByTitle(listMovie, title) != NULL;

    // cek title jika sudah ada didalam list atau tidak menginputkan karakter
    if (titleSudahAda || title.empty()) {
        // cek title jika tidak menginputkan karakter
        if (title.empty()) {
            // cetak bahwa title tidak boleh kosong
            warning("\nTitle tidak boleh kosong.");
        } else {
            // cetak bahwa title sudah ada didalam list
            failed("\nTitle sudah ada.");
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

    // data hasil input dibuat menjadi elemen movie
    movie = createMovie(title, director, actors, genre, runningTime, releaseDate);

    // elemen movie dialokasikan pada memory
    addressMovie = alokasiMovie(movie);

    // alamat memory movie dimasukan kedalam list dengan metode insert last
    insertLast(listMovie, addressMovie);

    FinalLabel:
    // cek jika maksimal mengulang kesalahan input tercapai
    if (retryTitleCount == MAX_RETRY_COUNT) {
        // sign up dinyatakan gagal
        failed("Input Data gagal.");
    } else {
        // cetak bahwa input data berhasil
        printHeader();
        printTitle("DATA MOVIE");
        cetakMovie(addressMovie);
        success("Input Data berhasil.");
    }
    getch();
}

// prosedur update data movie
void updateDataMovie(listMovie listMovie) {
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
    addressMovie movie;

    // label view
    ViewLabel:

    // cetak header
    printHeader();

    // cetak list movie
    cetakList(listMovie);

    // jika terdapat movie dalam list
    if (first(listMovie) != NULL) {
        // info
        warning("\n- Masukan ID movie yang akan diupdate.");
        warning("- Masukan 0 untuk kembali ke menu sebelumnya.\n");

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
            printHeader();
            printTitle("UPDATE DATA MOVIE");

            // cari movie by id
            movie = searchById(listMovie, id);

            // cek pointer movie
            if (movie == NULL) {
                warning("Movie tidak ditemukan.");
            } else {
                // cetak detail movie
                warning("Jangan inputkan data untuk mengisi field seperti default.\n");
                warning("Default data:");
                cetakMovie(movie);

                // input title
                cout << "Title: ";
                getline(cin, title);

                // cek jika inputan kosong, tampilkan default
                if (title.empty()) {
                    removeLastLine();
                    cout << "Title: " << data(movie).title << endl;
                }

                // input director
                cout << "Director: ";
                getline(cin, director);

                // cek jika inputan kosong, tampilkan default
                if (director.empty()) {
                    removeLastLine();
                    cout << "Director: " << data(movie).director << endl;
                }

                // input actors
                cout << "Actors: ";
                getline(cin, actors);

                // cek jika inputan kosong, tampilkan default
                if (actors.empty()) {
                    removeLastLine();
                    cout << "Actors: " << data(movie).actors << endl;
                }

                // input genre
                cout << "Genre: ";
                getline(cin, genre);

                // cek jika inputan kosong, tampilkan default
                if (genre.empty()) {
                    removeLastLine();
                    cout << "Genre: " << data(movie).genre << endl;
                }

                // input runningTime
                cout << "Running Time: ";
                getline(cin, runningTime);

                // cek jika inputan kosong, tampilkan default
                if (runningTime.empty()) {
                    removeLastLine();
                    cout << "Running Time: " << data(movie).runningTime << endl;
                }

                // input releaseDate
                cout << "Release Date: ";
                getline(cin, releaseDate);

                // cek jika inputan kosong, tampilkan default
                if (releaseDate.empty()) {
                    removeLastLine();
                    cout << "Release Date: " << data(movie).releaseDate << endl;
                }

                // ensure
                warning("Anda yakin ingin mengupdate?");
                cout << "Jawaban (y/n): ";
                getline(cin, ensureUpdate);

                // update jika jawaban Y atau y
                if (ensureUpdate == "Y" || ensureUpdate == "y") {
                    // update movie
                    updateMovie(movie, title, director, actors, genre, runningTime, releaseDate);
                    success("\nData berhasil diupdate.");
                } else {
                    success("\nData tidak diupdate.");
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
void viewDataMovie(listMovie listMovie, ListReview listReview) {
    // deklarasi variabel
    int id;
    string pilihId;
    addressMovie movie;

    // label view
    ViewLabel:

    // cetak header
    printHeader();

    // cetak list movie
    cetakList(listMovie);

    // jika terdapat movie dalam list
    if (first(listMovie) != NULL) {
        // info
        warning("\n- Masukan ID movie untuk melihat detail.");
        warning("- Masukan 0 untuk kembali ke menu sebelumnya.\n");

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
            printHeader();
            printTitle("VIEW DETAIL DATA MOVIE");

            // cari movie by id
            movie = searchById(listMovie, id);

            // cek pointer movie
            if (movie == NULL) {
                warning("Movie tidak ditemukan.");
            } else {
                // deklarasi review
                ListReview listReviewByMovie;
                createList(listReviewByMovie);

                // cari review berdasarkan movie id
                findByMovieId(listReviewByMovie, listReview, id);

                // cetak detail movie
                cetakMovie(movie);
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
void deleteDataMovie(listMovie &listMovie) {
    // deklarasi variabel
    int id;
    string pilihId;
    string ensureUpdate;
    addressMovie movie;

    // label view
    ViewLabel:

    // cetak header
    printHeader();

    // cetak list movie
    cetakList(listMovie);

    // jika terdapat movie dalam list
    if (first(listMovie) != NULL) {
        // info
        warning("\n- Masukan ID movie yang akan dihapus.");
        warning("- Masukan 0 untuk kembali ke menu sebelumnya.\n");

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
            printHeader();
            printTitle("DELETE DATA MOVIE");

            // cari movie by id
            movie = searchById(listMovie, id);

            // cek pointer movie
            if (movie == NULL) {
                warning("Movie tidak ditemukan.");
            } else {
                // cetak detail movie
                cetakMovie(movie);

                // ensure
                warning("Anda yakin ingin menghapus?");
                cout << "Jawaban (y/n): ";
                getline(cin, ensureUpdate);

                // hapus jika jawaban Y atau y
                if (ensureUpdate == "Y" || ensureUpdate == "y") {
                    // delete movie
                    deleteMovie(listMovie, movie);
                    success("\nData berhasil dihapus.");
                } else {
                    success("\nData tidak dihapus.");
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
void viewDataReviewer(listReviewer listReviewer) {
    // deklarasi variabel
    int id;
    string pilihId;
    addressReviewer reviewer;

    // label view
    ViewLabel:

    // cetak header
    printHeader();

    // cetak list reviewer
    cetakList(listReviewer);

    // jika terdapat reviewer dalam list
    if (first(listReviewer) != NULL) {
        // info
        warning("\n- Masukan ID reviewer untuk melihat detail.");
        warning("- Masukan 0 untuk kembali ke menu sebelumnya.\n");

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
            printHeader();
            printTitle("VIEW DETAIL DATA REVIEWER");

            // cari reviewer by id
            reviewer = searchById(listReviewer, id);

            // cek pointer reviewer
            if (reviewer == NULL) {
                warning("Reviewer tidak ditemukan.");
            } else {
                // cetak detail reviewer
                cetakReviewer(reviewer);
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
void deleteDataReviewer(listReviewer &listReviewer) {
    // deklarasi variabel
    int id;
    string pilihId;
    string ensureUpdate;
    addressReviewer reviewer;

    // label view
    ViewLabel:

    // cetak header
    printHeader();

    // cetak list reviewer
    cetakList(listReviewer);

    // jika terdapat reviewer dalam list
    if (first(listReviewer) != NULL) {
        // info
        warning("\n- Masukan ID reviewer yang akan dihapus.");
        warning("- Masukan 0 untuk kembali ke menu sebelumnya.\n");

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
            printHeader();
            printTitle("DELETE DATA REVIEWER");

            // cari reviewer by id
            reviewer = searchById(listReviewer, id);

            // cek pointer reviewer
            if (reviewer == NULL) {
                warning("Reviewer tidak ditemukan.");
            } else {
                // cetak detail reviewer
                cetakReviewer(reviewer);

                // ensure
                warning("Anda yakin ingin menghapus?");
                cout << "Jawaban (y/n): ";
                getline(cin, ensureUpdate);

                // hapus jika jawaban Y atau y
                if (ensureUpdate == "Y" || ensureUpdate == "y") {
                    // delete reviewer
                    deleteReviewer(listReviewer, reviewer);
                    success("\nData berhasil dihapus.");
                } else {
                    success("\nData tidak dihapus.");
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
