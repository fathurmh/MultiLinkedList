// include library c++
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

// include library buatan
#include "common.h"
#include "list_reviewer.h"
#include "list_movie.h"
#include "review.h"
#include "admin_area.h"
#include "guest_area.h"

// using namespace
using namespace std;

// prosedur inisialisasi data reviewer
void inisialisasiDataReviewer(ListReviewer &listReviewer);
// prosedur inisialisasi data movie
void inisialisasiDataMovie(ListMovie &listMovie);
// prosedur inisialisasi data review
void inisialisasiDataReview(ListReview &ListReview, ListReviewer listReviewer, ListMovie listMovie);

// main program
int main() {
    // deklarasi variabel
    char mainMenu;
    ListReviewer listReviewer;
    ListMovie listMovie;
    ListReview ListReview;

    // create list
    CreateList(listReviewer);
    CreateList(listMovie);
    createList(ListReview);

    // inisialisasi data
    inisialisasiDataReviewer(listReviewer);
    inisialisasiDataMovie(listMovie);
    inisialisasiDataReview(ListReview, listReviewer, listMovie);

    // label main menu
    MainMenuLabel:

    // cetak header
    PrintHeader();

    // cetak menu utama
    PrintTitle("MAIN MENU");
    cout << "1. View Top 10 By Review" << endl << endl
         << "2. Sign In" << endl
         << "3. Sign Up" << endl << endl
         << "0. Exit" << endl << endl;
    cout << "Pilih Menu: ";

    // input pilihan menu
    cin >> mainMenu;
    cin.ignore();

    // check kondisi pilihan
    switch (mainMenu) {
        case '1' : { //  View Top 10 By Review
            viewTopTenMovie(ListReview, listMovie);
            getch();

            // menuju label main menu
            goto MainMenuLabel;
        }
        case '2' : { // Sign In
            // sign in user
            LoginUser userLogin = signIn(listReviewer);

            // cek user login
            if (userLogin == ADMINISTRATOR) {
                // sign in administrator berhasil
                Success("\nSign in berhasil.");
                Success("Anda masuk sebagai Administrator.");
                getch();
                // masuk ke menu admin
                menuAdmin(listReviewer, listMovie, ListReview);
            } else if (userLogin == REVIEWER) {
                // sign in reviewer berhasil
                Success("\nSign in berhasil.");
                Success("Anda masuk sebagai Reviewer.");
                getch();
            } else {
                // sign in gagal
                Warning("\nUser tidak ditemukan atau username dan password tidak cocok.");
                Failed("Sign in gagal.");
                Success("Anda tetap masuk sebagai Guest.");
                getch();
            }

            // menuju label main menu
            goto MainMenuLabel;
        }
        case '3' : { // Sign Up
            // sign up reviewer
            signUp(listReviewer);
            getch();

            // menuju label main menu
            goto MainMenuLabel;
        }
        case '0' : { // Exit
            // exit
            cout << endl;
            Success("Good bye, see you next time.");
            getch();
        }
        break;
        default : { // default
            // menuju label main menu
            goto MainMenuLabel;
        }
    }

    return 0;
}

// prosedur inisialisasi data reviewer
void inisialisasiDataReviewer(ListReviewer &listReviewer) {
    // deklarasi variabel
    Reviewer newReviewer;
    AddressReviewer newAddressReviewer;

    // data dibuat menjadi elemen reviewer
    newReviewer = CreateReviewer("Nugi", "nugi", "nugi123");
    // elemen reviewer dialokasikan pada memory
    newAddressReviewer = Allocate(newReviewer);
    // alamat memory reviewer dimasukan kedalam list dengan metode insert last
    InsertLast(listReviewer, newAddressReviewer);

    newReviewer = CreateReviewer("Fatri", "fatri", "fatri123");
    newAddressReviewer = Allocate(newReviewer);
    InsertLast(listReviewer, newAddressReviewer);

    newReviewer = CreateReviewer("Fathur", "fathur", "fathur123");
    newAddressReviewer = Allocate(newReviewer);
    InsertLast(listReviewer, newAddressReviewer);

    newReviewer = CreateReviewer("Eri", "eri", "eri123");
    newAddressReviewer = Allocate(newReviewer);
    InsertLast(listReviewer, newAddressReviewer);

    newReviewer = CreateReviewer("Nanda", "nanda", "nanda123");
    newAddressReviewer = Allocate(newReviewer);
    InsertLast(listReviewer, newAddressReviewer);

    newReviewer = CreateReviewer("Tubagus", "tubagus", "tubagus123");
    newAddressReviewer = Allocate(newReviewer);
    InsertLast(listReviewer, newAddressReviewer);

    newReviewer = CreateReviewer("Arib", "arib", "arib123");
    newAddressReviewer = Allocate(newReviewer);
    InsertLast(listReviewer, newAddressReviewer);

    newReviewer = CreateReviewer("Nugi Ganteng", "nugiganteng", "nugi123");
    newAddressReviewer = Allocate(newReviewer);
    InsertLast(listReviewer, newAddressReviewer);

    newReviewer = CreateReviewer("Fathur Fathur", "fathurfathur", "fathurfathur");
    newAddressReviewer = Allocate(newReviewer);
    InsertLast(listReviewer, newAddressReviewer);

    newReviewer = CreateReviewer("Nugi Nugi", "nuginugi", "nuginugi");
    newAddressReviewer = Allocate(newReviewer);
    InsertLast(listReviewer, newAddressReviewer);
}

// prosedur inisialisasi data movie
void inisialisasiDataMovie(ListMovie &listMovie) {
    // deklarasi variabel
    Movie newMovie;
    AddressMovie newAddressMovie;

    // data dibuat menjadi elemen movie
    newMovie = CreateMovie("A STARS IS BORN", "Bradley Cooper", "Bradley Cooper, Lady Gaga, Sam Elliott, Dave Chappelle, Anthony Ramos", "Drama, Romance", "2 hour 14 minute", "19 October 2018");
    // elemen movie dialokasikan pada memory
    newAddressMovie = Allocate(newMovie);
    // alamat memory movie dimasukan kedalam list dengan metode insert last
    InsertLast(listMovie, newAddressMovie);

    newMovie = CreateMovie("AQUAMAN", "James Wan", "Jason Momoa, Amber Heard, Patrick Wilson, Nicole Kidman, Dolph Lundgren", "Action, Adventure, Fantasy", "2 hour 22 minute", "21 December 2018");
    newAddressMovie = Allocate(newMovie);
    InsertLast(listMovie, newAddressMovie);

    newMovie = CreateMovie("BIRD BOX", "Susanne Bier", "Sandra Bullock, Trevante Rhodes, Sarah Paulson, John Malkovich, Machine Gun Kelly", "Drama, Thriller", "2 hour 4 minute", "12 November 2018");
    newAddressMovie = Allocate(newMovie);
    InsertLast(listMovie, newAddressMovie);

    newMovie = CreateMovie("BOHEMIAN RHAPSODY", "Bryan Singer", "Rami Malek, Ben Hardy, Lucy Boynton, Mike Myres, Allen Leech, Joseph Mazzello", "Drama, Biography, Music", "2 hour 13 minute", "27 October 2018");
    newAddressMovie = Allocate(newMovie);
    InsertLast(listMovie, newAddressMovie);

    newMovie = CreateMovie("BUMBLEBEE", "Travis Knight", "Hailee Steinfeld, Dylan O'Brien, John Cena, Peter Cullen, Jorge Lendeborg Jr", "Sci-Fi, Action", "1 hour 54 minute", "19 December 2018");
    newAddressMovie = Allocate(newMovie);
    InsertLast(listMovie, newAddressMovie);

    newMovie = CreateMovie("CAPTAIN MARVEL", "Anna Boden, Ryan Fleck", "Brie Larson, Samuel L.Jackson, Jude Law, Gemma Chan, Ben Memdelsohn", "Fantasy, Sci-Fi", "2 hour 5 minute", "8 March 2019");
    newAddressMovie = Allocate(newMovie);
    InsertLast(listMovie, newAddressMovie);

    newMovie = CreateMovie("How To Train Your Dragon:The Hidden World", "Dean DeBlois", "Jay Baruchel, America Ferrera, Cate Blanchett, Kit Harington", "Action, Fantasy, Adventure", "1 hour 44 minute", "9 January 2019");
    newAddressMovie = Allocate(newMovie);
    InsertLast(listMovie, newAddressMovie);

    newMovie = CreateMovie("ISN'T IT ROMANTIC", "Todd Strauss-Schulson", "Rebel Wilson, Liam Hemsworth, Priyanka Chopra, Adam DeVine, Betty Gilpin, Tom Ellis", "Fantasy, Romance, Drama", "1 hour 29 minute", "13 February 2019");
    newAddressMovie = Allocate(newMovie);
    InsertLast(listMovie, newAddressMovie);

    newMovie = CreateMovie("SPIDER-MAN:INTO THE SPIDER-VERSE", "Peter Ramsey, Bob Persichetti, Rodney Rothman", "Jake Johnson, Shameik Moore, Hailee Steinfeld, Mahershala Ali, Nicolas Cage", "Fantasy, Sci-Fi", "1 hour 56 minute", "12 December 2018");
    newAddressMovie = Allocate(newMovie);
    InsertLast(listMovie, newAddressMovie);

    newMovie = CreateMovie("FANTASTIC BEASTS:THE CRIMES OF GRINDELWALD", "David Yates", "Eddie Redmayne, Jude Law, Johnny Depp, Ezra Miller, Dan Fogler", "Drama, Fantasy, Adventure", "2 hour 13 minute", "14 November 2018");
    newAddressMovie = Allocate(newMovie);
    InsertLast(listMovie, newAddressMovie);

    newMovie = CreateMovie("CRAZY RICH ASIANS", "Jon M.Chu", "Awkwafina, Henry Golding, Ken Jeong, Constance Wu, Gemma Chan", "Comedy, Romance", "2 hour 1 minute", "15 August 2018");
    newAddressMovie = Allocate(newMovie);
    InsertLast(listMovie, newAddressMovie);

    newMovie = CreateMovie("US", "Jordan Peele", "Nyong'o, Winston Duke, Anna Diop, Yahya Abdul-Matern II", "Mystery, Thriller", "2 hour 1 minute", "20 September 2019");
    newAddressMovie = Allocate(newMovie);
    InsertLast(listMovie, newAddressMovie);
}

// prosedur inisialisasi data review
void inisialisasiDataReview(ListReview &ListReview, ListReviewer listReviewer, ListMovie listMovie) {
    // deklarasi variabel
    review newReview;
    addressReview newAddressReview;
    AddressReviewer addressReviewer;
    AddressMovie addressMovie;

    // data dibuat menjadi elemen reviewer
    newReview = createReview(5, "GREAT MOVIE!!!");
    // cari pointer reviewer yang mereview
    addressReviewer = FindByUsername(listReviewer, "nugi");
    // cari pointer movie yang direview
    addressMovie = FindByTitle(listMovie, "A STARS IS BORN");
    // elemen reviewer dialokasikan pada memory
    newAddressReview = allocate(newReview, addressReviewer, addressMovie);
    // alamat memory reviewer dimasukan kedalam list dengan metode insert last
    insertFirst(ListReview, newAddressReview);

    newReview = createReview(5, "Pretty good super hero film.");
    addressReviewer = FindByUsername(listReviewer, "fatri");
    addressMovie = FindByTitle(listMovie, "AQUAMAN");
    newAddressReview = allocate(newReview, addressReviewer, addressMovie);
    insertFirst(ListReview, newAddressReview);

    newReview = createReview(5, "Insane scary loved it.");
    addressReviewer = FindByUsername(listReviewer, "fathur");
    addressMovie = FindByTitle(listMovie, "BIRD BOX");
    newAddressReview = allocate(newReview, addressReviewer, addressMovie);
    insertFirst(ListReview, newAddressReview);

    newReview = createReview(5, "Excellent movie! How queen became queen");
    addressReviewer = FindByUsername(listReviewer, "eri");
    addressMovie = FindByTitle(listMovie, "BOHEMIAN RHAPSODY");
    newAddressReview = allocate(newReview, addressReviewer, addressMovie);
    insertFirst(ListReview, newAddressReview);

    newReview = createReview(5, "Loved it!!! Awsome Movie!!!");
    addressReviewer = FindByUsername(listReviewer, "nanda");
    addressMovie = FindByTitle(listMovie, "BUMBLEBEE");
    newAddressReview = allocate(newReview, addressReviewer, addressMovie);
    insertFirst(ListReview, newAddressReview);

    newReview = createReview(5, "Best movie!!! Carol is awesome!");
    addressReviewer = FindByUsername(listReviewer, "tubagus");
    addressMovie = FindByTitle(listMovie, "CAPTAIN MARVEL");
    newAddressReview = allocate(newReview, addressReviewer, addressMovie);
    insertFirst(ListReview, newAddressReview);

    newReview = createReview(5, "Absolutely Amazing!!");
    addressReviewer = FindByUsername(listReviewer, "arib");
    addressMovie = FindByTitle(listMovie, "How To Train Your Dragon:The Hidden World");
    newAddressReview = allocate(newReview, addressReviewer, addressMovie);
    insertFirst(ListReview, newAddressReview);

    newReview = createReview(4, "Great movie and funny");
    addressReviewer = FindByUsername(listReviewer, "nugiganteng");
    addressMovie = FindByTitle(listMovie, "ISN'T IT ROMANTIC");
    newAddressReview = allocate(newReview, addressReviewer, addressMovie);
    insertFirst(ListReview, newAddressReview);

    newReview = createReview(5, "Amazing movie stan lee");
    addressReviewer = FindByUsername(listReviewer, "fathurfathur");
    addressMovie = FindByTitle(listMovie, "SPIDER-MAN:INTO THE SPIDER-VERSE");
    newAddressReview = allocate(newReview, addressReviewer, addressMovie);
    insertFirst(ListReview, newAddressReview);

    newReview = createReview(5, "FANTASTIC MOVIE!!!");
    addressReviewer = FindByUsername(listReviewer, "nuginugi");
    addressMovie = FindByTitle(listMovie, "FANTASTIC BEASTS:THE CRIMES OF GRINDELWALD");
    newAddressReview = allocate(newReview, addressReviewer, addressMovie);
    insertFirst(ListReview, newAddressReview);
}