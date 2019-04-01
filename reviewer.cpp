// include library c++
#include <iostream>
#include <conio.h>

// include library buatan
#include "common.h"
#include "reviewer.h"

// prosedur membuat list baru
void createList(listReviewer &newListReviewer) {
    // inisialisasi elemen pertama dengan null
    first(newListReviewer) = NULL;
    // inisialisasi elemen terakhir dengan null
    last(newListReviewer) = NULL;
}

// fungsi membuat data reviewer
reviewer createReviewer(string nama, string username, string password) {
    // inisialisasi id static agar otomatis bertambah saat membuat reviewer baru
    static int id = 0;

    // deklarasi variabel data reviewer
    reviewer newReviewer;

    // inisialisasi variabel data reviewer
    newReviewer.id = ++id;
    newReviewer.nama = nama;
    newReviewer.username = username;
    newReviewer.password = password;

    // kembalikan reviewer
    return newReviewer;
}

// fungsi alokasi reviewer
addressReviewer alokasiReviewer(reviewer reviewer) {
    // deklarasi pointer reviewer
    addressReviewer newAddressReviewer;
    // instansiasi pointer dengan elemen reviewer
    newAddressReviewer = new elementReviewer();

    // inisialisasi data pada pointer dengan parameter reviewer
    data(newAddressReviewer) = reviewer;
    // inisialisasi pointer menuju elemen selanjutnya dengan null
    next(newAddressReviewer) = NULL;
    // inisialisasi pointer menuju elemen sebelumnya dengan null
    prev(newAddressReviewer) = NULL;

    // kembalikan pointer
    return newAddressReviewer;
}

// prosedur insert first reviewer
void insertFirst(listReviewer &listReviewer, addressReviewer newAddressReviewer) {
    // pengecekan jika list masih kosong
    if(first(listReviewer) == NULL && last(listReviewer) == NULL) {
        // inisialisasi elemen pertama dengan pointer reviewer baru
        first(listReviewer) = newAddressReviewer;
        // inisialisasi elemen terakhir dengan pointer reviewer baru
        last(listReviewer) = newAddressReviewer;
    } else {
        // inisialisasi variabel firstReviewer dengan elemen pertama pada list
        addressReviewer firstReviewer = first(listReviewer);
        // inisialisasi pointer reviewer baru menuju elemen selanjutnya dengan elemen pertama pada list
        next(newAddressReviewer) = firstReviewer;
        // inisialisasi pointer reviewer baru menuju elemen sebelumnya dengan null
        prev(newAddressReviewer) = NULL;
        // inisialisasi pointer menuju elemen sebelumnya pada firstReviewer dengan pointer reviewer baru
        prev(firstReviewer) = newAddressReviewer;
        // inisialisasi elemen pertama pada list dengan pointer reviewer baru
        first(listReviewer) = newAddressReviewer;
    }
}

// prosedur insert last reviewer
void insertLast(listReviewer &listReviewer, addressReviewer newAddressReviewer) {
    // pengecekan jika list masih kosong
    if(first(listReviewer) == NULL && last(listReviewer) == NULL) {
        // jika list kosong maka insert first
        insertFirst(listReviewer, newAddressReviewer);
    } else {
        // inisialisasi variabel lastReviewer dengan elemen terakhir pada list
        addressReviewer lastReviewer = last(listReviewer);
        // inisialisasi pointer reviewer baru menuju elemen sebelumnya dengan elemen terakhir pada list
        prev(newAddressReviewer) = lastReviewer;
        // inisialisasi pointer reviewer baru menuju elemen selanjutnya dengan null
        next(newAddressReviewer) = NULL;
        // inisialisasi pointer menuju elemen selanjutnya pada lastReviewer dengan pointer reviewer baru
        next(lastReviewer) = newAddressReviewer;
        // inisialisasi elemen terakhir pada list dengan pointer reviewer baru
        last(listReviewer) = newAddressReviewer;
    }
}

// prosedur delete reviewer
void deleteReviewer(listReviewer &listReviewer, addressReviewer reviewer) {
    // cek jika list kosong
    if(first(listReviewer) == NULL && last(listReviewer) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else if (reviewer != NULL){
        // jika elemen yang dihapus adalah elemen pertama
        if (first(listReviewer) == reviewer) {
            // inisialisasi elemen pertama dengan elemen selanjutnya dari reviewer yang akan dihapus
            first(listReviewer) = next(reviewer);
        }

        // jika elemen yang dihapus adalah elemen terakhir
        if (last(listReviewer) == reviewer) {
            // inisialisasi elemen terakhir dengan elemen sebelumnya dari reviewer yang akan dihapus
            last(listReviewer) = prev(reviewer);
        }

        // jika elemen yang dihapus bukan elemen pertama
        if (prev(reviewer) != NULL) {
            // inisialisasi elemen selanjutnya dari elemen sebelumnya dari reviewer yang akan dihapus dengan elemen selanjutnya dari reviewer yang akan dihapus
            next(prev(reviewer)) = next(reviewer);
        }

        // jika elemen yang dihapus bukan elemen terakhir
        if (next(reviewer) != NULL) {
            // inisialisasi elemen sebelumnya dari elemen selanjutnya dari reviewer yang akan dihapus dengan elemen sebelumnya dari reviewer yang akan dihapus
            prev(next(reviewer)) = prev(reviewer);
        }

        // hapus memory
        delete reviewer;
    }
}

// prosedur delete all reviewer
void deleteAll(listReviewer &listReviewer) {
    // cek jika list kosong
    if(first(listReviewer) == NULL && last(listReviewer) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // deklarasi variabel next
        addressReviewer next;
        // inisialisasi variabel iterator dengan elemen pertama pada list
        addressReviewer current = first(listReviewer);
        // loop delete reviewer dalam list
        while(current != NULL) {
            next = next(current);
            deleteReviewer(listReviewer, current);
            current = next;
        }
    }
}

// prosedur delete first reviewer
void deleteFirst(listReviewer &listReviewer) {
    // cek jika elemen pertama null (list kosong)
    if(first(listReviewer) == NULL && last(listReviewer) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // delete reviewer
        deleteReviewer(listReviewer, first(listReviewer));
    }
}

// prosedur delete last reviewer
void deleteLast(listReviewer &listReviewer) {
    // cek jika elemen pertama null (list kosong)
    if(first(listReviewer) == NULL && last(listReviewer) == NULL) {
        warning("Tidak ada data.");
        getch();
    } else {
        // delete reviewer
        deleteReviewer(listReviewer, last(listReviewer));
    }
}

// fungsi cari reviewer by username pada list
addressReviewer searchByUsername(listReviewer &listReviewer, string username) {
    // inisialisasi variabel ketemu
    bool ketemu = false;

    // inisialisasi variabel dataKetemu dengan null
    addressReviewer dataKetemu = NULL;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressReviewer current = first(listReviewer);

    // loop selama tidak ketemu dan iterator tidak sama dengan null
    while (!ketemu && current != NULL) {
        // jika username iterator sama dengan parameter username maka ketemu
        if (data(current).username == username) {
            ketemu = true;
            dataKetemu = current;
        }
        // variabel iterator diisi dengan elemen selanjutnya
        current = next(current);
    }

    // kembalikan data
    return dataKetemu;
}

// fungsi cari reviewer by id pada list
addressReviewer searchById(listReviewer &listReviewer, int id) {
    // inisialisasi variabel ketemu
    bool ketemu = false;

    // inisialisasi variabel dataKetemu dengan null
    addressReviewer dataKetemu = NULL;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressReviewer current = first(listReviewer);

    // loop selama tidak ketemu dan iterator tidak sama dengan null
    while (!ketemu && current != NULL) {
        // jika username iterator sama dengan parameter username maka ketemu
        if (data(current).id == id) {
            ketemu = true;
            dataKetemu = current;
        }
        // variabel iterator diisi dengan elemen selanjutnya
        current = next(current);
    }

    // kembalikan data
    return dataKetemu;
}

// fungsi hitung total elemen pada list
int countList(listReviewer listReviewer) {
    // inisialisasi count
    int count = 0;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressReviewer current = first(listReviewer);

    // hitung selama iterator tidak sama dengan null
    while (current != NULL) {
        count++;
        current = next(current);
    }

    // kembalikan hasil hitung
    return count;
}

// prosedur cetak data reviewer
void cetakReviewer(addressReviewer addressReviewer) {
    // cetak data reviewer
    cout << "ID      : " << data(addressReviewer).id << endl
         << "Nama    : " << data(addressReviewer).nama << endl
         << "Username: " << data(addressReviewer).username << endl << endl;
}

// prosedur cetak list data reviewer
void cetakList(listReviewer listReviewer) {
    // inisialisasi count
    int count = 0;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressReviewer current = first(listReviewer);

    printTitle("VIEW LIST REVIEWER");

    if (current == NULL) {
        // cetak info tidak ada data
        warning("Tidak ada data.");
        getch();
    } else {
        // loop cetak reviewer dalam list
        while(current != NULL) {
            // cetak reviewer
            cetakReviewer(current);

            // next iterator
            current = next(current);
            count++;
        }

        // cetak total reviewer
        cout << "Total Reviewer: " << count << endl;
    }
}