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
#include "reviewer_area.h"

// using namespace
using namespace std;

// prosedur menu reviewer
void MenuReviewer(ListReviewer list_reviewer, ListMovie list_movie, ListReview &list_review, AddressReviewer current_address_reviewer)
{
    // deklarasi variabel
    char main_menu;

    // label main menu
MainMenuLabel:

    // cetak header
    PrintHeader();

    // cetak menu utama
    PrintTitle("MAIN MENU");
    cout << "1. Input Data Review" << endl
        << "2. Update Data Review" << endl
        << "3. Delete Data Review" << endl
        << "4. View Review History" << endl << endl
        << "5. Update Account" << endl << endl
        << "9. Sign Out" << endl
        << "0. Exit" << endl << endl;
    cout << "Pilih Menu: ";

    // input pilihan menu
    cin >> main_menu;
    cin.ignore();

    // check kondisi pilihan
    switch (main_menu)
    {
    case '1': // Input Data Review
    {
        InputDataReview(list_review, list_movie, current_address_reviewer);

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '2': // Update Data Review
    {
        UpdateDataReview(list_review, current_address_reviewer);

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '3': // Delete Data Review
    {
        DeleteDataReview(list_review, current_address_reviewer);

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '4': // View Review History
    {
        ViewReviewHistory(list_review, current_address_reviewer);

        // menuju label main menu
        goto MainMenuLabel;
    }
    case '5': // Update Account
    {
        UpdateAccount(list_reviewer, current_address_reviewer);

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

void InputDataReview(ListReview &list_review, ListMovie list_movie, AddressReviewer current_address_reviewer)
{
    // deklarasi variabel
    Review review;
    AddressReview address_review;
    AddressMovie address_movie;
    int id;
    int rating;
    string pilih_id;
    string pilih_rating;
    string description;
    int retry_rating_count;
    int retry_description_count;

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
        Warning("- Masukan ID movie yang akan direview.");
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

                PrintTitle("INPUT DATA REVIEW");

                // inisialisasi variabel pengulangan input rating
                retry_rating_count = 0;

            InputRatingLabel:

                // input rating
                cout << "Rating: ";
                getline(cin, pilih_rating);

                // convert input string ke integer
                istringstream int_stream(pilih_rating);
                int_stream >> rating;

                // convert integer ke string stream
                stringstream stream;
                stream << rating;

                // cek jika inputan kosong
                if (pilih_rating.empty() || rating <= 0 || rating > MAX_RATING)
                {
                    if (pilih_rating.empty())
                    {
                        // cetak bahwa rating tidak boleh kosong
                        Warning("\nRating tidak boleh kosong.");
                    }
                    else
                    {
                        // cetak bahwa rating harus diantara 1 - 5
                        Warning({ "\nMasukan rating hanya angka 1 sampai ", to_string(MAX_RATING), "." });
                    }

                    getch();

                    // cek maksimal mengulang kesalahan input
                    if (++retry_rating_count < MAX_RETRY_COUNT)
                    {
                        RemoveLastLine();
                        RemoveLastLine();
                        RemoveLastLine();

                        // mengulang menginput rating
                        goto InputRatingLabel;
                    }
                    else
                    {
                        // menuju final label
                        goto FinalLabel;
                    }
                }

                // inisialisasi variabel pengulangan input description
                retry_description_count = 0;

            InputDesctiptionLabel:

                // input description
                cout << "Description: ";
                getline(cin, description);

                // cek jika inputan kosong
                if (description.empty())
                {
                    // cetak bahwa description tidak boleh kosong
                    Warning("\nDescription tidak boleh kosong.");

                    getch();

                    // cek maksimal mengulang kesalahan input
                    if (++retry_description_count < MAX_RETRY_COUNT)
                    {
                        RemoveLastLine();
                        RemoveLastLine();
                        RemoveLastLine();

                        // mengulang menginput description
                        goto InputDesctiptionLabel;
                    }
                    else
                    {
                        // menuju final label
                        goto FinalLabel;
                    }
                }

            FinalLabel:
                // cek jika maksimal mengulang kesalahan input tercapai
                if (retry_rating_count == MAX_RETRY_COUNT || retry_description_count == MAX_RETRY_COUNT)
                {
                    // input data dinyatakan gagal
                    Failed("Input Data gagal.");
                }
                else
                {
                    // data hasil input dibuat menjadi elemen review
                    review = CreateReview(rating, description);

                    // elemen review dialokasikan pada memory
                    address_review = Allocate(review, current_address_reviewer, address_movie);

                    // alamat memory review dimasukan kedalam list dengan metode insert first
                    InsertFirst(list_review, address_review);

                    // cetak bahwa input data berhasil
                    // cetak header
                    PrintHeader();
                    PrintTitle("VIEW DETAIL DATA MOVIE");

                    // cetak movie with review
                    CetakMovieWithReview(list_review, address_movie);
                    Success("Input Data berhasil.");
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

void UpdateDataReview(ListReview &list_review, AddressReviewer current_address_reviewer)
{
    // deklarasi variabel
    int id;
    int rating;
    string pilih_id;
    string pilih_rating;
    string description;
    int retry_rating_count;
    string ensure_update;
    AddressReview address_review;

ViewLabel:
    // cetak header
    PrintHeader();
    PrintTitle("VIEW LIST REVIEW");

    // inisialisasi array review by reviewer id
    AddressReview *reviewer_reviews = FindByReviewerId(list_review, DATA(current_address_reviewer).id);

    // inisialisasi panjang array
    int length = Count(reviewer_reviews);

    // cetak review with movie
    CetakWithMovie(reviewer_reviews);

    // jika terdapat review dalam array
    if (length > 0)
    {
        // info
        Warning("- Masukan ID review yang akan diupdate.");
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

            // cari review by id
            address_review = FindById(reviewer_reviews, id);

            // cek pointer review
            if (address_review == NULL)
            {
                // cetak header
                PrintHeader();
                PrintTitle("UPDATE DATA REVIEW");
                Warning("Review tidak ditemukan.");
            }
            else
            {
                // cetak header
                PrintHeader();
                PrintTitle("VIEW DETAIL DATA MOVIE");

                // cetak movie
                Cetak(MOVIE(address_review));

                PrintTitle("UPDATE DATA REVIEW");

                // cetak detail review
                Warning("Jangan inputkan data untuk mengisi field seperti default.\n");
                Warning("Default data:");
                Cetak(address_review);

                // inisialisasi variabel pengulangan input rating
                retry_rating_count = 0;

                // input rating
            InputRatingLabel:
                cout << "Rating: ";
                getline(cin, pilih_rating);

                // cek jika inputan kosong, tampilkan default
                if (pilih_rating.empty())
                {
                    rating = DATA(address_review).rating;
                    RemoveLastLine();
                    cout << "Rating: " << rating << endl;
                }
                else
                {
                    // convert input string ke integer
                    istringstream int_stream(pilih_rating);
                    int_stream >> rating;

                    // cek jika inputan kosong
                    if (rating <= 0 || rating > MAX_RATING)
                    {
                        // cetak bahwa rating harus diantara 1 - Max
                        Warning({ "\nMasukan rating hanya angka 1 sampai ", to_string(MAX_RATING), "." });

                        getch();

                        // cek maksimal mengulang kesalahan input
                        if (++retry_rating_count < MAX_RETRY_COUNT)
                        {
                            RemoveLastLine();
                            RemoveLastLine();
                            RemoveLastLine();

                            // mengulang menginput rating
                            goto InputRatingLabel;
                        }
                        else
                        {
                            // menuju final label
                            goto FinalLabel;
                        }
                    }
                }

                // input description
                cout << "Description: ";
                getline(cin, description);

                // cek jika inputan kosong, tampilkan default
                if (description.empty())
                {
                    RemoveLastLine();
                    cout << "Description: " << DATA(address_review).description << endl;
                }

            FinalLabel:
                // cek jika maksimal mengulang kesalahan input tercapai
                if (retry_rating_count == MAX_RETRY_COUNT)
                {
                    // update data dinyatakan gagal
                    Failed("Update data gagal.");
                }
                else
                {
                    // ensure
                    Warning("\nAnda yakin ingin mengupdate?");
                    cout << "Jawaban (y/n): ";
                    getline(cin, ensure_update);

                    // update jika jawaban Y atau y
                    if (ensure_update == "Y" || ensure_update == "y")
                    {
                        // update review
                        UpdateReview(address_review, rating, description);
                        Success("\nData berhasil diupdate.");
                    }
                    else
                    {
                        Success("\nData tidak diupdate.");
                    }
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

    getch();

ExitLabel:;
    // dealokasi memory array karena sudah tidak digunakan
    Deallocate(reviewer_reviews);
}

void DeleteDataReview(ListReview &list_review, AddressReviewer current_address_reviewer)
{
    // deklarasi variabel
    int id;
    string pilih_id;
    string ensure_delete;
    AddressReview address_review;

ViewLabel:
    // cetak header
    PrintHeader();
    PrintTitle("VIEW LIST REVIEW");

    // inisialisasi array review by reviewer id
    AddressReview *reviewer_reviews = FindByReviewerId(list_review, DATA(current_address_reviewer).id);

    // inisialisasi panjang array
    int length = Count(reviewer_reviews);

    // cetak review with movie
    CetakWithMovie(reviewer_reviews);

    // jika terdapat review dalam array
    if (length > 0)
    {
        // info
        Warning("- Masukan ID review yang akan dihapus.");
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
            PrintTitle("DELETE DATA REVIEW");

            // cari review by id
            address_review = FindById(reviewer_reviews, id);

            // cek pointer review
            if (address_review == NULL)
            {
                Warning("Review tidak ditemukan.");
            }
            else
            {
                // cetak detail review
                CetakWithMovie(address_review);

                Warning("Anda yakin ingin menghapus?");
                cout << "Jawaban (y/n): ";
                getline(cin, ensure_delete);

                // hapus jika jawaban Y atau y
                if (ensure_delete == "Y" || ensure_delete == "y")
                {
                    // delete review
                    DeleteReview(list_review, address_review);
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

    getch();

ExitLabel:;
    // dealokasi memory array karena sudah tidak digunakan
    Deallocate(reviewer_reviews);
}

void ViewReviewHistory(ListReview list_review, AddressReviewer current_address_reviewer)
{
    // cetak header
    PrintHeader();
    PrintTitle("VIEW REVIEW HISTORY");

    // inisialisasi array review by reviewer id
    AddressReview *reviewer_reviews = FindByReviewerId(list_review, DATA(current_address_reviewer).id);

    // cetak review with movie
    CetakWithMovie(reviewer_reviews);

    // dealokasi memory array karena sudah tidak digunakan
    Deallocate(reviewer_reviews);

    getch();
}

void UpdateAccount(ListReviewer list_reviewer, AddressReviewer current_address_reviewer)
{
    // deklarasi variabel
    string name;
    string username;
    string password;
    string retype_password;
    string ensure_update;
    bool username_sudah_ada;

    // inisialisasi variabel pengulangan input username
    int retry_username_count = 0;
    // inisialisasi variabel pengulangan input password
    int retry_password_count = 0;

    // cetak header
    PrintHeader();
    PrintTitle("UPDATE ACCOUNT");

    // cetak detail reviewer
    Warning("Jangan inputkan data untuk mengisi field seperti default.\n");
    Warning("Default data:");
    Cetak(current_address_reviewer);

    // input name
    cout << "Name: ";
    getline(cin, name);

    // cek jika inputan kosong, tampilkan default
    if (name.empty())
    {
        name = DATA(current_address_reviewer).name;
        RemoveLastLine();
        cout << "Name: " << name << endl;
    }

    // label input username
InputUsernameLabel:

    // input username
    cout << "Username: ";
    getline(cin, username);

    // cek jika inputan kosong, tampilkan default
    if (username.empty())
    {
        username = DATA(current_address_reviewer).username;
        RemoveLastLine();
        cout << "Username: " << username << endl;
    }
    else
    {
        // cek username didalam list kecuali username yang login
        AddressReviewer hasil_cari = FindByUsername(list_reviewer, username);
        username_sudah_ada = hasil_cari != NULL && hasil_cari != current_address_reviewer;
        if (username_sudah_ada)
        {
            // cetak bahwa username sudah ada didalam list
            Failed("\nUsername sudah ada.");

            getch();

            // cek maksimal mengulang kesalahan input
            if (++retry_username_count < MAX_RETRY_COUNT)
            {
                RemoveLastLine();
                RemoveLastLine();
                RemoveLastLine();

                // mengulang menginput username
                goto InputUsernameLabel;
            }
            else
            {
                // menuju final label
                goto FinalLabel;
            }
        }
    }

    // label input password
InputPasswordLabel:

    // input password
    password = GetPassword("Password: ");

    // cek jika inputan kosong, tampilkan default
    if (password.empty())
    {
        RemoveLastLine();
        cout << "Password: " << string(DATA(current_address_reviewer).password.length(), '*') << endl;
    }
    else
    {
        // input retype password
        retype_password = GetPassword("Retype Password: ");

        // cek apakah variabel password dan retype_password tidak sama atau tidak menginputkan karakter
        if (password != retype_password)
        {
            // cetak bahwa password dan retype password tidak sama
            Failed("\nPassword tidak sama.");

            getch();

            // cek maksimal mengulang kesalahan input
            if (++retry_password_count < MAX_RETRY_COUNT)
            {
                RemoveLastLine();
                RemoveLastLine();
                RemoveLastLine();
                RemoveLastLine();

                // mengulang menginput password
                goto InputPasswordLabel;
            }
            else
            {
                // menuju final label
                goto FinalLabel;
            }
        }
    }

FinalLabel:
    // cek jika maksimal mengulang kesalahan input tercapai
    if (retry_password_count == MAX_RETRY_COUNT || retry_username_count == MAX_RETRY_COUNT)
    {
        // update account dinyatakan gagal
        Failed("Update Account gagal.");
    }
    else
    {
        // ensure
        Warning("\nAnda yakin ingin mengupdate?");
        cout << "Jawaban (y/n): ";
        getline(cin, ensure_update);

        // update jika jawaban Y atau y
        if (ensure_update == "Y" || ensure_update == "y")
        {
            // update movie
            UpdateReviewer(current_address_reviewer, name, username, password);
            Success("\nData berhasil diupdate.");
        }
        else
        {
            Success("\nData tidak diupdate.");
        }
    }

    getch();
}
