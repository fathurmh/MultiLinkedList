// include library c++
#include <iostream>
#include <conio.h>
#include <cstdlib>

// include library buatan
#include "guest_area.h"

// fungsi sign in
loginUser signIn(listReviewer listReviewer) {
    // deklarasi variabel
    string username;
    string password;
    addressReviewer reviewer;

    // inisialisasi login user guest
    loginUser loginUser = Guest;

    // cetak header
    printHeader();
    printTitle("SIGN IN");

    // input username
    cout << "Username: ";
    getline(cin, username);

    // input password
    password = getPass("Password: ");

    // cek jika user adalah administrator
    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        // login user diisi administrator
        loginUser = Administrator;
    } else {
        // cari reviewer dengan username yang diinputkan
        reviewer = searchByUsername(listReviewer, username);

        // cek jika reviewer tidak sama dengan null dan passwordnya sama dengan yang diinputkan
        if (reviewer != NULL && data(reviewer).password == password) {
            // login user diisi reviewer
            loginUser = Reviewer;
        }
    }

    return loginUser;
}

// prosedur sign up
void signUp(listReviewer &listReviewer) {
    // deklarasi variabel
    reviewer reviewer;
    addressReviewer addressReviewer;
    string name;
    string username;
    string password;
    string retypePassword;
    int retryPasswordCount;
    int retryUsernameCount;
    bool usernameSudahAda;

    // cetak header
    printHeader();
    printTitle("SIGN UP");

    // input nama
    cout << "Nama: ";
    getline(cin, name);

    // inisialisasi variabel pengulangan input username
    retryUsernameCount = 0;

    // label input username
    InputUsernameLabel:

    // cetak header akan menghapus console sebelumnya
    printHeader();
    printTitle("SIGN UP");

    // cetak data yang diinputkan sebelumnya
    cout << "Nama: " << name << endl;

    // input username
    cout << "Username: ";
    getline(cin, username);

    // cek username didalam list
    usernameSudahAda = searchByUsername(listReviewer, username) != NULL;

    // cek username jika sama dengan admin atau sudah ada didalam list atau tidak menginputkan karakter
    if (username == ADMIN_USERNAME || usernameSudahAda || username.empty()) {
        // cek username jika tidak menginputkan karakter
        if (username.empty()) {
            // cetak bahwa username tidak boleh kosong
            warning("\nUsername tidak boleh kosong.");
        } else {
            // cetak bahwa username sudah ada didalam list
            failed("\nUsername sudah ada.");
        }

        getch();

        // cek maksimal mengulang kesalahan input
        if (++retryUsernameCount < MAX_RETRY_COUNT) {
            // mengulang menginput username
            goto InputUsernameLabel;
        } else {
            // menuju final label
            goto FinalLabel;
        }
    }

    // inisialisasi variabel pengulangan input password
    retryPasswordCount = 0;

    // label input username
    InputPasswordLabel:

    // cetak header akan menghapus console sebelumnya
    printHeader();
    printTitle("SIGN UP");

    // cetak data yang diinputkan sebelumnya
    cout << "Nama: " << name << endl;
    cout << "Username: " << username << endl;

    // input password
    password = getPass("Password: ");

    // input retype password
    retypePassword = getPass("Retype Password: ");

    // cek apakah variabel password dan retypePassword tidak sama atau tidak menginputkan karakter
    if (password != retypePassword || password.empty()) {
        // cek password jika tidak menginputkan karakter
        if (password.empty()) {
            // cetak bahwa username tidak boleh kosong
            warning("\nPassword tidak boleh kosong.");
        } else {
            // cetak bahwa password dan retype password tidak sama
            failed("\nPassword tidak sama.");
        }

        getch();

        // cek maksimal mengulang kesalahan input
        if (++retryPasswordCount < MAX_RETRY_COUNT) {
            // mengulang menginput username
            goto InputPasswordLabel;
        } else {
            // menuju final label
            goto FinalLabel;
        }
    }

    FinalLabel:
    // cek jika maksimal mengulang kesalahan input tercapai
    if (retryPasswordCount == MAX_RETRY_COUNT || retryUsernameCount == MAX_RETRY_COUNT) {
        // sign up dinyatakan gagal
        failed("Sign Up gagal.");
    } else {
        // data sign up dibuat menjadi elemen reviewer
        reviewer = createReviewer(name, username, password);
        // elemen reviewer dialokasikan pada memory
        addressReviewer = alokasiReviewer(reviewer);
        // alamat memory reviewer dimasukan kedalam list dengan metode insert last
        insertLast(listReviewer, addressReviewer);
        // cetak bahwa sign up berhasil
        printHeader();
        printTitle("DATA REVIEWER");
        cetakReviewer(addressReviewer);
        success("Sign Up berhasil.");
        success("Silahkan melakukan Sign In.");
    }
}

int findIndex(addressMovie *arrayMovie, int arraySize, addressMovie searchMovie) {
    for(int i = 0; i < arraySize; i++)
    {
        if(data(arrayMovie[i]).id == data(searchMovie).id)
            return i;
    }
    return -1;
}

int compare(const void *pa, const void *pb) {
    int *a = (int *)pa;
    int *b = (int *)pb;
    if(a[0] == b[0])
        return a[1] - b[1];
    else
        return a[0] - b[0];
}

// view top 10 movie dengan ulasan terbanyak
void viewTopTenMovie(ListReview listReview, listMovie listMovie) {
    if (first(listMovie) != NULL && last(listMovie) != NULL){
        // preprocessing
        int totalMovie = countList(listMovie), i = 0;
        addressMovie arrayMovie[totalMovie] = { NULL };
        addressMovie temp = first(listMovie);

        while(temp != NULL){
            arrayMovie[i] = temp;
            temp = next(temp);
            i++;
        }


        ListReview result;
        createList(result);
        findByMovieId(result, listReview, 1);

        // process
        int idxMovie = 0;
        int arrayMovieReviewCount[totalMovie][2] = { 0 };

        for(int i = 0; i < totalMovie; i++)
        {

        }


        // addressReview current = first(ListReview);
        // addressMovie currentMovie = movie(current);
        // do {
        //     current = next(current);
        //     currentMovie = movie(current);
        //     idxMovie = findIndex(arrayMovie, totalMovie, currentMovie);
        //     arrayMovieReviewCount[idxMovie][0]++;
        //     arrayMovieReviewCount[idxMovie][1] = idxMovie;
        // } while (current != first(ListReview));

        for(i = 0; i < totalMovie; i++){
            printf("Count: %d\tIndex: %d\n", arrayMovieReviewCount[i][0], arrayMovieReviewCount[i][1]);
        }

        qsort(arrayMovieReviewCount, totalMovie, sizeof(*arrayMovieReviewCount), compare);

        printf("\n\ndata\tindex\n");
        for(i = 0; i < totalMovie; i++){
            printf("Count: %d\tIndex: %d\n", arrayMovieReviewCount[i][0], arrayMovieReviewCount[i][1]);
        }

        getch();
    }
}