// include library c++
#include <iostream>
#include <conio.h>

// include library buatan
#include "common.h"
#include "adminarea.h"
#include "reviewer.h"
#include "movie.h"

// using namespace
using namespace std;

// prosedur inisialisasi data reviewer
void inisialisasiDataReviewer(listReviewer &listReviewer);
// prosedur inisialisasi data movie
void inisialisasiDataMovie(listMovie &listMovie);

// main program
int main() {
    // deklarasi variabel
    char mainMenu;
    listReviewer listReviewer;
    listMovie listMovie;

    // create list
    createList(listReviewer);
    createList(listMovie);

    // inisialisasi data
    inisialisasiDataReviewer(listReviewer);
    inisialisasiDataMovie(listMovie);

    // label main menu
    MainMenuLabel:

    // cetak header
    printHeader();

    // cetak menu utama
    printTitle("MAIN MENU");
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
            printHeader();
            getch();

            // menuju label main menu
            goto MainMenuLabel;
        }
        case '2' : { // Sign In
            // sign in user
            loginUser userLogin = signIn(listReviewer);

            // cek user login
            if (userLogin == Administrator) {
                // sign in administrator berhasil
                success("\nSign in berhasil.");
                success("Anda masuk sebagai Administrator.");
                getch();
                // masuk ke menu admin
                menuAdmin(listReviewer, listMovie);
            } else if (userLogin == Reviewer) {
                // sign in reviewer berhasil
                success("\nSign in berhasil.");
                success("Anda masuk sebagai Reviewer.");
                getch();
            } else {
                // sign in gagal
                warning("\nUser tidak ditemukan atau username dan password tidak cocok.");
                failed("Sign in gagal.");
                success("Anda tetap masuk sebagai Guest.");
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
            success("Good bye, see you next time.");
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
void inisialisasiDataReviewer(listReviewer &listReviewer) {
    // deklarasi variabel
    reviewer newReviewer;
    addressReviewer newAddressReviewer;

    // data dibuat menjadi elemen reviewer
    newReviewer = createReviewer("Nugi", "nugi", "nugi123");
    // elemen reviewer dialokasikan pada memory
    newAddressReviewer = alokasiReviewer(newReviewer);
    // alamat memory reviewer dimasukan kedalam list dengan metode insert last
    insertLast(listReviewer, newAddressReviewer);

    newReviewer = createReviewer("Fatri", "fatri", "fatri123");
    newAddressReviewer = alokasiReviewer(newReviewer);
    insertLast(listReviewer, newAddressReviewer);

    // newReviewer = createReviewer("Fathur", "fathur", "fathur123");
    // newAddressReviewer = alokasiReviewer(newReviewer);
    // insertLast(listReviewer, newAddressReviewer);

    // newReviewer = createReviewer("Eri", "eri", "eri123");
    // newAddressReviewer = alokasiReviewer(newReviewer);
    // insertLast(listReviewer, newAddressReviewer);

    // newReviewer = createReviewer("Nanda", "nanda", "nanda123");
    // newAddressReviewer = alokasiReviewer(newReviewer);
    // insertLast(listReviewer, newAddressReviewer);

    // newReviewer = createReviewer("Tubagus", "tubagus", "tubagus123");
    // newAddressReviewer = alokasiReviewer(newReviewer);
    // insertLast(listReviewer, newAddressReviewer);

    // newReviewer = createReviewer("Arib", "arib", "arib123");
    // newAddressReviewer = alokasiReviewer(newReviewer);
    // insertLast(listReviewer, newAddressReviewer);

    // newReviewer = createReviewer("Nugi Ganteng", "nugiganteng", "nugi123");
    // newAddressReviewer = alokasiReviewer(newReviewer);
    // insertLast(listReviewer, newAddressReviewer);

    // newReviewer = createReviewer("Fathur Fathur", "fathurfathur", "fathurfathur");
    // newAddressReviewer = alokasiReviewer(newReviewer);
    // insertLast(listReviewer, newAddressReviewer);

    // newReviewer = createReviewer("Nugi Nugi", "nuginugi", "nuginugi");
    // newAddressReviewer = alokasiReviewer(newReviewer);
    // insertLast(listReviewer, newAddressReviewer);
}

// prosedur inisialisasi data movie
void inisialisasiDataMovie(listMovie &listMovie) {
    // deklarasi variabel
    movie newMovie;
    addressMovie newAddressMovie;

    // data dibuat menjadi elemen movie
    newMovie = createMovie("A STARS IS BORN", "Bradley Cooper", "Bradley Cooper, Lady Gaga, Sam Elliott, Dave Chappelle, Anthony Ramos", "Drama, Romance", "2 hour 14 minute", "19 October 2018");
    // elemen movie dialokasikan pada memory
    newAddressMovie = alokasiMovie(newMovie);
    // alamat memory movie dimasukan kedalam list dengan metode insert last
    insertLast(listMovie, newAddressMovie);

    newMovie = createMovie("AQUAMAN", "James Wan", "Jason Momoa, Amber Heard, Patrick Wilson, Nicole Kidman, Dolph Lundgren", "Action, Adventure, Fantasy", "2 hour 22 minute", "21 December 2018");
    newAddressMovie = alokasiMovie(newMovie);
    insertLast(listMovie, newAddressMovie);

    newMovie = createMovie("BIRD BOX", "Susanne Bier", "Sandra Bullock, Trevante Rhodes, Sarah Paulson, John Malkovich, Machine Gun Kelly", "Drama, Thriller", "2 hour 4 minute", "12 November 2018");
    newAddressMovie = alokasiMovie(newMovie);
    insertLast(listMovie, newAddressMovie);

    newMovie = createMovie("BOHEMIAN RHAPSODY", "Bryan Singer", "Rami Malek, Ben Hardy, Lucy Boynton, Mike Myres, Allen Leech, Joseph Mazzello", "Drama, Biography, Music", "2 hour 13 minute", "27 October 2018");
    newAddressMovie = alokasiMovie(newMovie);
    insertLast(listMovie, newAddressMovie);

    newMovie = createMovie("BUMBLEBEE", "Travis Knight", "Hailee Steinfeld, Dylan O'Brien, John Cena, Peter Cullen, Jorge Lendeborg Jr", "Sci-Fi, Action", "1 hour 54 minute", "19 December 2018");
    newAddressMovie = alokasiMovie(newMovie);
    insertLast(listMovie, newAddressMovie);

    newMovie = createMovie("CAPTAIN MARVEL", "Anna Boden, Ryan Fleck", "Brie Larson, Samuel L.Jackson, Jude Law, Gemma Chan, Ben Memdelsohn", "Fantasy, Sci-Fi", "2 hour 5 minute", "8 March 2019");
    newAddressMovie = alokasiMovie(newMovie);
    insertLast(listMovie, newAddressMovie);

    newMovie = createMovie("How To Train Your Dragon:The Hidden World", "Dean DeBlois", "Jay Baruchel, America Ferrera, Cate Blanchett, Kit Harington", "Action, Fantasy, Adventure", "1 hour 44 minute", "9 January 2019");
    newAddressMovie = alokasiMovie(newMovie);
    insertLast(listMovie, newAddressMovie);

    newMovie = createMovie("ISN'T IT ROMANTIC", "Todd Strauss-Schulson", "Rebel Wilson, Liam Hemsworth, Priyanka Chopra, Adam DeVine, Betty Gilpin, Tom Ellis", "Fantasy, Romance, Drama", "1 hour 29 minute", "13 February 2019");
    newAddressMovie = alokasiMovie(newMovie);
    insertLast(listMovie, newAddressMovie);

    newMovie = createMovie("SPIDER-MAN:INTO THE SPIDER-VERSE", "Peter Ramsey, Bob Persichetti, Rodney Rothman", "Jake Johnson, Shameik Moore, Hailee Steinfeld, Mahershala Ali, Nicolas Cage", "Fantasy, Sci-Fi", "1 hour 56 minute", "12 December 2018");
    newAddressMovie = alokasiMovie(newMovie);
    insertLast(listMovie, newAddressMovie);

    newMovie = createMovie("FANTASTIC BEASTS:THE CRIMES OF GRINDELWALD", "David Yates", "Eddie Redmayne, Jude Law, Johnny Depp, Ezra Miller, Dan Fogler", "Drama, Fantasy, Adventure", "2 hour 13 minute", "14 November 2018");
    newAddressMovie = alokasiMovie(newMovie);
    insertLast(listMovie, newAddressMovie);

    newMovie = createMovie("CRAZY RICH ASIANS", "Jon M.Chu", "Awkwafina, Henry Golding, Ken Jeong, Constance Wu, Gemma Chan", "Comedy, Romance", "2 hour 1 minute", "15 August 2018");
    newAddressMovie = alokasiMovie(newMovie);
    insertLast(listMovie, newAddressMovie);

    newMovie = createMovie("US", "Jordan Peele", "Nyong'o, Winston Duke, Anna Diop, Yahya Abdul-Matern II", "Mystery, Thriller", "2 hour 1 minute", "20 September 2019");
    newAddressMovie = alokasiMovie(newMovie);
    insertLast(listMovie, newAddressMovie);
}