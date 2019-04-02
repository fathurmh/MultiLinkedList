// include library c++
#include <iostream>
#include <conio.h>

// include library buatan
#include "common.h"
#include "reviewer.h"

// prosedur membuat list baru
void createList(listReviewer &newListReviewer) {
    // inisialisasi elemen pertama dengan null
    FIRST(newListReviewer) = NULL;
    // inisialisasi elemen terakhir dengan null
    LAST(newListReviewer) = NULL;
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
    DATA(newAddressReviewer) = reviewer;
    // inisialisasi pointer menuju elemen selanjutnya dengan null
    NEXT(newAddressReviewer) = NULL;
    // inisialisasi pointer menuju elemen sebelumnya dengan null
    PREV(newAddressReviewer) = NULL;

    // kembalikan pointer
    return newAddressReviewer;
}

// prosedur insert first reviewer
void insertFirst(listReviewer &listReviewer, addressReviewer newAddressReviewer) {
    // pengecekan jika list masih kosong
    if(FIRST(listReviewer) == NULL && LAST(listReviewer) == NULL) {
        // inisialisasi elemen pertama dengan pointer reviewer baru
        FIRST(listReviewer) = newAddressReviewer;
        // inisialisasi elemen terakhir dengan pointer reviewer baru
        LAST(listReviewer) = newAddressReviewer;
    } else {
        // inisialisasi variabel firstReviewer dengan elemen pertama pada list
        addressReviewer firstReviewer = FIRST(listReviewer);
        // inisialisasi pointer reviewer baru menuju elemen selanjutnya dengan elemen pertama pada list
        NEXT(newAddressReviewer) = firstReviewer;
        // inisialisasi pointer reviewer baru menuju elemen sebelumnya dengan null
        PREV(newAddressReviewer) = NULL;
        // inisialisasi pointer menuju elemen sebelumnya pada firstReviewer dengan pointer reviewer baru
        PREV(firstReviewer) = newAddressReviewer;
        // inisialisasi elemen pertama pada list dengan pointer reviewer baru
        FIRST(listReviewer) = newAddressReviewer;
    }
}

// prosedur insert last reviewer
void insertLast(listReviewer &listReviewer, addressReviewer newAddressReviewer) {
    // pengecekan jika list masih kosong
    if(FIRST(listReviewer) == NULL && LAST(listReviewer) == NULL) {
        // jika list kosong maka insert first
        insertFirst(listReviewer, newAddressReviewer);
    } else {
        // inisialisasi variabel lastReviewer dengan elemen terakhir pada list
        addressReviewer lastReviewer = LAST(listReviewer);
        // inisialisasi pointer reviewer baru menuju elemen sebelumnya dengan elemen terakhir pada list
        PREV(newAddressReviewer) = lastReviewer;
        // inisialisasi pointer reviewer baru menuju elemen selanjutnya dengan null
        NEXT(newAddressReviewer) = NULL;
        // inisialisasi pointer menuju elemen selanjutnya pada lastReviewer dengan pointer reviewer baru
        NEXT(lastReviewer) = newAddressReviewer;
        // inisialisasi elemen terakhir pada list dengan pointer reviewer baru
        LAST(listReviewer) = newAddressReviewer;
    }
}

// prosedur delete reviewer
void deleteReviewer(listReviewer &listReviewer, addressReviewer reviewer) {
    // cek jika list kosong
    if(FIRST(listReviewer) == NULL && LAST(listReviewer) == NULL) {
        Warning("Tidak ada data.");
        getch();
    } else if (reviewer != NULL){
        // jika elemen yang dihapus adalah elemen pertama
        if (FIRST(listReviewer) == reviewer) {
            // inisialisasi elemen pertama dengan elemen selanjutnya dari reviewer yang akan dihapus
            FIRST(listReviewer) = NEXT(reviewer);
        }

        // jika elemen yang dihapus adalah elemen terakhir
        if (LAST(listReviewer) == reviewer) {
            // inisialisasi elemen terakhir dengan elemen sebelumnya dari reviewer yang akan dihapus
            LAST(listReviewer) = PREV(reviewer);
        }

        // jika elemen yang dihapus bukan elemen pertama
        if (PREV(reviewer) != NULL) {
            // inisialisasi elemen selanjutnya dari elemen sebelumnya dari reviewer yang akan dihapus dengan elemen selanjutnya dari reviewer yang akan dihapus
            NEXT(PREV(reviewer)) = NEXT(reviewer);
        }

        // jika elemen yang dihapus bukan elemen terakhir
        if (NEXT(reviewer) != NULL) {
            // inisialisasi elemen sebelumnya dari elemen selanjutnya dari reviewer yang akan dihapus dengan elemen sebelumnya dari reviewer yang akan dihapus
            PREV(NEXT(reviewer)) = PREV(reviewer);
        }

        // hapus memory
        delete reviewer;
    }
}

// prosedur delete all reviewer
void deleteAll(listReviewer &listReviewer) {
    // cek jika list kosong
    if(FIRST(listReviewer) == NULL && LAST(listReviewer) == NULL) {
        Warning("Tidak ada data.");
        getch();
    } else {
        // deklarasi variabel next
        addressReviewer next;
        // inisialisasi variabel iterator dengan elemen pertama pada list
        addressReviewer current = FIRST(listReviewer);
        // loop delete reviewer dalam list
        while(current != NULL) {
            next = NEXT(current);
            deleteReviewer(listReviewer, current);
            current = next;
        }
    }
}

// prosedur delete first reviewer
void deleteFirst(listReviewer &listReviewer) {
    // cek jika elemen pertama null (list kosong)
    if(FIRST(listReviewer) == NULL && LAST(listReviewer) == NULL) {
        Warning("Tidak ada data.");
        getch();
    } else {
        // delete reviewer
        deleteReviewer(listReviewer, FIRST(listReviewer));
    }
}

// prosedur delete last reviewer
void deleteLast(listReviewer &listReviewer) {
    // cek jika elemen pertama null (list kosong)
    if(FIRST(listReviewer) == NULL && LAST(listReviewer) == NULL) {
        Warning("Tidak ada data.");
        getch();
    } else {
        // delete reviewer
        deleteReviewer(listReviewer, LAST(listReviewer));
    }
}

// fungsi cari reviewer by username pada list
addressReviewer searchByUsername(listReviewer &listReviewer, string username) {
    // inisialisasi variabel ketemu
    bool ketemu = false;

    // inisialisasi variabel dataKetemu dengan null
    addressReviewer dataKetemu = NULL;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressReviewer current = FIRST(listReviewer);

    // loop selama tidak ketemu dan iterator tidak sama dengan null
    while (!ketemu && current != NULL) {
        // jika username iterator sama dengan parameter username maka ketemu
        if (DATA(current).username == username) {
            ketemu = true;
            dataKetemu = current;
        }
        // variabel iterator diisi dengan elemen selanjutnya
        current = NEXT(current);
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
    addressReviewer current = FIRST(listReviewer);

    // loop selama tidak ketemu dan iterator tidak sama dengan null
    while (!ketemu && current != NULL) {
        // jika username iterator sama dengan parameter username maka ketemu
        if (DATA(current).id == id) {
            ketemu = true;
            dataKetemu = current;
        }
        // variabel iterator diisi dengan elemen selanjutnya
        current = NEXT(current);
    }

    // kembalikan data
    return dataKetemu;
}

// fungsi hitung total elemen pada list
int countList(listReviewer listReviewer) {
    // inisialisasi count
    int count = 0;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressReviewer current = FIRST(listReviewer);

    // hitung selama iterator tidak sama dengan null
    while (current != NULL) {
        count++;
        current = NEXT(current);
    }

    // kembalikan hasil hitung
    return count;
}

// prosedur cetak data reviewer
void cetakReviewer(addressReviewer addressReviewer) {
    // cetak data reviewer
    cout << "ID      : " << DATA(addressReviewer).id << endl
         << "Nama    : " << DATA(addressReviewer).nama << endl
         << "Username: " << DATA(addressReviewer).username << endl << endl;
}

// prosedur cetak list data reviewer
void cetakList(listReviewer listReviewer) {
    // inisialisasi count
    int count = 0;

    // inisialisasi variabel iterator dengan elemen pertama pada list
    addressReviewer current = FIRST(listReviewer);

    PrintTitle("VIEW LIST REVIEWER");

    if (current == NULL) {
        // cetak info tidak ada data
        Warning("Tidak ada data.");
        getch();
    } else {
        // loop cetak reviewer dalam list
        while(current != NULL) {
            // cetak reviewer
            cetakReviewer(current);

            // next iterator
            current = NEXT(current);
            count++;
        }

        // cetak total reviewer
        cout << "Total Reviewer: " << count << endl;
    }
}