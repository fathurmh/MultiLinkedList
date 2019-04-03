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
#include "admin_area.h"

// using namespace
using namespace std;

// prosedur inisialisasi data reviewer
void InitDataReviewer(ListReviewer &list_reviewer);
// prosedur inisialisasi data movie
void InitDataMovie(ListMovie &list_movie);
// prosedur inisialisasi data review
void InitDataReview(ListReview &list_review, ListReviewer list_reviewer, ListMovie list_movie);

// main program
int main()
{
    // deklarasi variabel
    char main_menu;
    LoginUser user_login;

    ListReviewer list_reviewer;
    ListMovie list_movie;
    ListReview list_review;

    // create list
    CreateList(list_reviewer);
    CreateList(list_movie);
    CreateList(list_review);

    // inisialisasi data
    InitDataReviewer(list_reviewer);
    InitDataMovie(list_movie);
    InitDataReview(list_review, list_reviewer, list_movie);

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
    cin >> main_menu;
    cin.ignore();

    // check kondisi pilihan
    switch (main_menu)
    {
    case '1':
    { //  View Top 10 By Review
        ViewTopTenMovie(list_review, list_movie);
        getch();

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '2':
    { // Sign In
// sign in user
        user_login = SignIn(list_reviewer);

        // cek user login
        if (user_login == ADMINISTRATOR)
        {
            // sign in administrator berhasil
            Success("\nSign in berhasil.");
            Success("Anda masuk sebagai Administrator.");
            getch();
            // masuk ke menu admin
            MenuAdmin(list_reviewer, list_movie, list_review);
        }
        else if (user_login == REVIEWER)
        {
            // sign in reviewer berhasil
            Success("\nSign in berhasil.");
            Success("Anda masuk sebagai Reviewer.");
            getch();
        }
        else
        {
            // sign in gagal
            Warning("\nUser tidak ditemukan atau username dan password tidak cocok.");
            Failed("Sign in gagal.");
            Success("Anda tetap masuk sebagai Guest.");
            getch();
        }

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '3':
    { // Sign Up
// sign up reviewer
        SignUp(list_reviewer);
        getch();

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '0':
    { // Exit
// exit
        cout << endl;
        Success("Good bye, see you next time.");
        getch();
    }
    break;
    default:
    { // default
// menuju label main menu
        goto MainMenuLabel;
    }
    }

    return 0;
}

// prosedur inisialisasi data reviewer
void InitDataReviewer(ListReviewer &list_reviewer)
{
    // deklarasi variabel
    Reviewer reviewer;
    AddressReviewer address_reviewer;

    // data dibuat menjadi elemen reviewer
    reviewer = CreateReviewer("Nugi", "nugi", "nugi123");
    // elemen reviewer dialokasikan pada memory
    address_reviewer = Allocate(reviewer);
    // alamat memory reviewer dimasukan kedalam list dengan metode insert last
    InsertLast(list_reviewer, address_reviewer);

    reviewer = CreateReviewer("Fatri", "fatri", "fatri123");
    address_reviewer = Allocate(reviewer);
    InsertLast(list_reviewer, address_reviewer);

    reviewer = CreateReviewer("Fathur", "fathur", "fathur123");
    address_reviewer = Allocate(reviewer);
    InsertLast(list_reviewer, address_reviewer);

    reviewer = CreateReviewer("Eri", "eri", "eri123");
    address_reviewer = Allocate(reviewer);
    InsertLast(list_reviewer, address_reviewer);

    reviewer = CreateReviewer("Nanda", "nanda", "nanda123");
    address_reviewer = Allocate(reviewer);
    InsertLast(list_reviewer, address_reviewer);

    reviewer = CreateReviewer("Tubagus", "tubagus", "tubagus123");
    address_reviewer = Allocate(reviewer);
    InsertLast(list_reviewer, address_reviewer);

    reviewer = CreateReviewer("Arib", "arib", "arib123");
    address_reviewer = Allocate(reviewer);
    InsertLast(list_reviewer, address_reviewer);

    reviewer = CreateReviewer("Nugi Ganteng", "nugiganteng", "nugi123");
    address_reviewer = Allocate(reviewer);
    InsertLast(list_reviewer, address_reviewer);

    reviewer = CreateReviewer("Fathur Fathur", "fathurfathur", "fathurfathur");
    address_reviewer = Allocate(reviewer);
    InsertLast(list_reviewer, address_reviewer);

    reviewer = CreateReviewer("Nugi Nugi", "nuginugi", "nuginugi");
    address_reviewer = Allocate(reviewer);
    InsertLast(list_reviewer, address_reviewer);
}

// prosedur inisialisasi data movie
void InitDataMovie(ListMovie &list_movie)
{
    // deklarasi variabel
    Movie movie;
    AddressMovie address_movie;

    // data dibuat menjadi elemen movie
    movie = CreateMovie("A STARS IS BORN", "Bradley Cooper", "Bradley Cooper, Lady Gaga, Sam Elliott, Dave Chappelle, Anthony Ramos", "Drama, Romance", "2 hour 14 minute", "19 October 2018");
    // elemen movie dialokasikan pada memory
    address_movie = Allocate(movie);
    // alamat memory movie dimasukan kedalam list dengan metode insert last
    InsertLast(list_movie, address_movie);

    movie = CreateMovie("AQUAMAN", "James Wan", "Jason Momoa, Amber Heard, Patrick Wilson, Nicole Kidman, Dolph Lundgren", "Action, Adventure, Fantasy", "2 hour 22 minute", "21 December 2018");
    address_movie = Allocate(movie);
    InsertLast(list_movie, address_movie);

    movie = CreateMovie("BIRD BOX", "Susanne Bier", "Sandra Bullock, Trevante Rhodes, Sarah Paulson, John Malkovich, Machine Gun Kelly", "Drama, Thriller", "2 hour 4 minute", "12 November 2018");
    address_movie = Allocate(movie);
    InsertLast(list_movie, address_movie);

    movie = CreateMovie("BOHEMIAN RHAPSODY", "Bryan Singer", "Rami Malek, Ben Hardy, Lucy Boynton, Mike Myres, Allen Leech, Joseph Mazzello", "Drama, Biography, Music", "2 hour 13 minute", "27 October 2018");
    address_movie = Allocate(movie);
    InsertLast(list_movie, address_movie);

    movie = CreateMovie("BUMBLEBEE", "Travis Knight", "Hailee Steinfeld, Dylan O'Brien, John Cena, Peter Cullen, Jorge Lendeborg Jr", "Sci-Fi, Action", "1 hour 54 minute", "19 December 2018");
    address_movie = Allocate(movie);
    InsertLast(list_movie, address_movie);

    movie = CreateMovie("CAPTAIN MARVEL", "Anna Boden, Ryan Fleck", "Brie Larson, Samuel L.Jackson, Jude Law, Gemma Chan, Ben Memdelsohn", "Fantasy, Sci-Fi", "2 hour 5 minute", "8 March 2019");
    address_movie = Allocate(movie);
    InsertLast(list_movie, address_movie);

    movie = CreateMovie("How To Train Your Dragon:The Hidden World", "Dean DeBlois", "Jay Baruchel, America Ferrera, Cate Blanchett, Kit Harington", "Action, Fantasy, Adventure", "1 hour 44 minute", "9 January 2019");
    address_movie = Allocate(movie);
    InsertLast(list_movie, address_movie);

    movie = CreateMovie("ISN'T IT ROMANTIC", "Todd Strauss-Schulson", "Rebel Wilson, Liam Hemsworth, Priyanka Chopra, Adam DeVine, Betty Gilpin, Tom Ellis", "Fantasy, Romance, Drama", "1 hour 29 minute", "13 February 2019");
    address_movie = Allocate(movie);
    InsertLast(list_movie, address_movie);

    movie = CreateMovie("SPIDER-MAN:INTO THE SPIDER-VERSE", "Peter Ramsey, Bob Persichetti, Rodney Rothman", "Jake Johnson, Shameik Moore, Hailee Steinfeld, Mahershala Ali, Nicolas Cage", "Fantasy, Sci-Fi", "1 hour 56 minute", "12 December 2018");
    address_movie = Allocate(movie);
    InsertLast(list_movie, address_movie);

    movie = CreateMovie("FANTASTIC BEASTS:THE CRIMES OF GRINDELWALD", "David Yates", "Eddie Redmayne, Jude Law, Johnny Depp, Ezra Miller, Dan Fogler", "Drama, Fantasy, Adventure", "2 hour 13 minute", "14 November 2018");
    address_movie = Allocate(movie);
    InsertLast(list_movie, address_movie);

    movie = CreateMovie("CRAZY RICH ASIANS", "Jon M.Chu", "Awkwafina, Henry Golding, Ken Jeong, Constance Wu, Gemma Chan", "Comedy, Romance", "2 hour 1 minute", "15 August 2018");
    address_movie = Allocate(movie);
    InsertLast(list_movie, address_movie);

    movie = CreateMovie("US", "Jordan Peele", "Nyong'o, Winston Duke, Anna Diop, Yahya Abdul-Matern II", "Mystery, Thriller", "2 hour 1 minute", "20 September 2019");
    address_movie = Allocate(movie);
    InsertLast(list_movie, address_movie);
}

// prosedur inisialisasi data review
void InitDataReview(ListReview &list_review, ListReviewer list_reviewer, ListMovie list_movie)
{
    // deklarasi variabel
    Review review;
    AddressReview address_review;
    AddressReviewer address_reviewer;
    AddressMovie address_movie;

    // data dibuat menjadi elemen reviewer
    review = CreateReview(5, "GREAT MOVIE!!!");
    // cari pointer reviewer yang mereview
    address_reviewer = FindByUsername(list_reviewer, "nugi");
    // cari pointer movie yang direview
    address_movie = FindByTitle(list_movie, "A STARS IS BORN");
    // elemen reviewer dialokasikan pada memory
    address_review = Allocate(review, address_reviewer, address_movie);
    // alamat memory reviewer dimasukan kedalam list dengan metode insert last
    InsertFirst(list_review, address_review);

    review = CreateReview(5, "Pretty good super hero film.");
    address_reviewer = FindByUsername(list_reviewer, "fatri");
    address_movie = FindByTitle(list_movie, "AQUAMAN");
    address_review = Allocate(review, address_reviewer, address_movie);
    InsertFirst(list_review, address_review);

    review = CreateReview(5, "Insane scary loved it.");
    address_reviewer = FindByUsername(list_reviewer, "fathur");
    address_movie = FindByTitle(list_movie, "BIRD BOX");
    address_review = Allocate(review, address_reviewer, address_movie);
    InsertFirst(list_review, address_review);

    review = CreateReview(5, "Excellent movie! How queen became queen");
    address_reviewer = FindByUsername(list_reviewer, "eri");
    address_movie = FindByTitle(list_movie, "BOHEMIAN RHAPSODY");
    address_review = Allocate(review, address_reviewer, address_movie);
    InsertFirst(list_review, address_review);

    review = CreateReview(5, "Loved it!!! Awsome Movie!!!");
    address_reviewer = FindByUsername(list_reviewer, "nanda");
    address_movie = FindByTitle(list_movie, "BUMBLEBEE");
    address_review = Allocate(review, address_reviewer, address_movie);
    InsertFirst(list_review, address_review);

    review = CreateReview(5, "Best movie!!! Carol is awesome!");
    address_reviewer = FindByUsername(list_reviewer, "tubagus");
    address_movie = FindByTitle(list_movie, "CAPTAIN MARVEL");
    address_review = Allocate(review, address_reviewer, address_movie);
    InsertFirst(list_review, address_review);

    review = CreateReview(5, "AWESOME MOVIE!!!");
    address_reviewer = FindByUsername(list_reviewer, "fathur");
    address_movie = FindByTitle(list_movie, "CAPTAIN MARVEL");
    address_review = Allocate(review, address_reviewer, address_movie);
    InsertFirst(list_review, address_review);

    review = CreateReview(5, "Absolutely Amazing!!");
    address_reviewer = FindByUsername(list_reviewer, "arib");
    address_movie = FindByTitle(list_movie, "How To Train Your Dragon:The Hidden World");
    address_review = Allocate(review, address_reviewer, address_movie);
    InsertFirst(list_review, address_review);

    review = CreateReview(4, "Great movie and funny");
    address_reviewer = FindByUsername(list_reviewer, "nugiganteng");
    address_movie = FindByTitle(list_movie, "ISN'T IT ROMANTIC");
    address_review = Allocate(review, address_reviewer, address_movie);
    InsertFirst(list_review, address_review);

    review = CreateReview(5, "Amazing movie stan lee");
    address_reviewer = FindByUsername(list_reviewer, "fathurfathur");
    address_movie = FindByTitle(list_movie, "SPIDER-MAN:INTO THE SPIDER-VERSE");
    address_review = Allocate(review, address_reviewer, address_movie);
    InsertFirst(list_review, address_review);

    review = CreateReview(5, "FANTASTIC MOVIE!!!");
    address_reviewer = FindByUsername(list_reviewer, "nuginugi");
    address_movie = FindByTitle(list_movie, "FANTASTIC BEASTS:THE CRIMES OF GRINDELWALD");
    address_review = Allocate(review, address_reviewer, address_movie);
    InsertFirst(list_review, address_review);
}