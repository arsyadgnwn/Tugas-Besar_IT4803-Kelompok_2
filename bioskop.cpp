#include "bioskop.h"

/* -------------------------
   INISIALISASI LIST
   ------------------------- */

void createListFilm(list_Film &L) {
    first(L) = NULL;
    last(L)  = NULL;
}

void createListPenonton(list_Penonton &L) {
    first(L) = NULL;
}

void createListRelasi(list_Relasi &L) {
    first(L) = NULL;
}

/* -------------------------
   BUAT NODE BARU
   ------------------------- */

adr_Film newFilm(Film data) {
    adr_Film P = new elm_Film;
    info(P) = data;
    next(P) = NULL;
    prev(P) = NULL;
    return P;
}

adr_Penonton newPenonton(Penonton data) {
    adr_Penonton P = new elm_Penonton;
    info(P) = data;
    next(P) = NULL;
    return P;
}

adr_Relasi newRelasi(adr_Film film, adr_Penonton penonton) {
    adr_Relasi P = new elm_Relasi;
    nextFilm(P) = film;
    nextPenonton(P) = penonton;
    next(P) = NULL;
    return P;
}

/* -------------------------
   OPERASI LIST FILM (DLL)
   ------------------------- */

void insert_first_Film(list_Film &L, adr_Film P) {
    if (first(L) == NULL) {
        first(L) = P;
        last(L)  = P;
    } else {
        next(P) = first(L);
        prev(first(L)) = P;
        first(L) = P;
    }
}

void insert_last_Film(list_Film &L, adr_Film P) {
    if (first(L) == NULL) {
        first(L) = P;
        last(L)  = P;
    } else {
        prev(P) = last(L);
        next(last(L)) = P;
        last(L) = P;
    }
}

void showAllFilms(list_Film L) {
    adr_Film i = first(L);
    if (i == NULL) {
        cout << "Tidak ada data film." << endl;
        return;
    }
    while (i != NULL) {
        cout << "ID Film: " << info(i).id_Film
             << ", Judul: " << info(i).judul
             << ", Jam Tayang: " << info(i).jam_Tayang
             << ", Harga: " << info(i).harga
             << ", Total Penonton: " << info(i).jumlah_Penonton << endl;
        i = next(i);
    }
}

adr_Film findFilm(list_Film L, int idFilm) {
    adr_Film i = first(L);
    while (i != NULL && info(i).id_Film != idFilm) {
        i = next(i);
    }
    return i;
}

void deleteFilm(list_Film &filmList, list_Relasi &relasiList, int idFilm) {
    adr_Film P = findFilm(filmList, idFilm);
    if (P == NULL) {
        cout << "DATA TIDAK DITEMUKAN" << endl;
        return;
    }

    if (P == first(filmList) && P == last(filmList)) {
        first(filmList) = NULL;
        last(filmList)  = NULL;
    } else if (P == first(filmList)) {
        first(filmList) = next(P);
        prev(first(filmList)) = NULL;
    } else if (P == last(filmList)) {
        last(filmList) = prev(P);
        next(last(filmList)) = NULL;
    } else {
        next(prev(P)) = next(P);
        prev(next(P)) = prev(P);
    }

    adr_Relasi R = first(relasiList);
    adr_Relasi prevRel = NULL;

    while (R != NULL) {
        if (nextFilm(R) == P) {
            info(nextPenonton(R)).banyak_Tiket--;

            adr_Relasi del = R;
            if (R == first(relasiList)) {
                first(relasiList) = next(R);
                R = first(relasiList);
                prevRel = NULL;
            } else {
                next(prevRel) = next(R);
                R = next(prevRel);
            }
            delete del;
        } else {
            prevRel = R;
            R = next(R);
        }
    }

    delete P;
    cout << "Film dan seluruh relasinya berhasil dihapus." << endl;
}

void editFilm(list_Film &L, int idFilm) {
    adr_Film i = findFilm(L, idFilm);
    if (i == NULL) {
        cout << "FILM TIDAK DITEMUKAN" << endl;
        return;
    }

    int pilihan = -1;
    while (pilihan != 0) {
        cout << "EDIT FILM DENGAN ID = " << info(i).id_Film << endl;
        cout << "DATA YANG INGIN DIUBAH : " << endl;
        cout << "1. JUDUL" << endl;
        cout << "2. JAM TAYANG" << endl;
        cout << "3. HARGA" << endl;
        cout << "4. EXIT" << endl;
        cout << "MASUKKAN PILIHAN = ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "JUDUL BARU = ";
            cin.ignore();
            getline(cin, info(i).judul);
        } else if (pilihan == 2) {
            cout << "JAM TAYANG BARU = ";
            cin >> info(i).jam_Tayang;
        } else if (pilihan == 3) {
            cout << "HARGA BARU = ";
            cin >> info(i).harga;
        } else {
            pilihan = 0;
        }
        cout << endl;
    }
}

/* -------------------------------
   OPERASI LIST PENONTON (SLL)
   ------------------------------- */

void ShowAllPenonton(list_Penonton L) {
    adr_Penonton i = first(L);
    if (i == NULL) {
        cout << "Tidak ada data penonton." << endl;
        return;
    }
    while (i != NULL) {
        cout << "ID Penonton: " << info(i).id_Penonton
             << ", Nama: " << info(i).nama
             << ", Banyak Tiket: " << info(i).banyak_Tiket << endl;
        i = next(i);
    }
}

adr_Penonton findPenonton(list_Penonton L, int idPenonton) {
    adr_Penonton i = first(L);
    while (i != NULL && info(i).id_Penonton != idPenonton) {
        i = next(i);
    }
    return i;
}

void insert_first_Penonton(list_Penonton &L, adr_Penonton P) {
    if (first(L) == NULL) {
        first(L) = P;
    } else {
        next(P) = first(L);
        first(L) = P;
    }
}

void insert_last_Penonton(list_Penonton &L, adr_Penonton P) {
    if (first(L) == NULL) {
        first(L) = P;
    } else {
        adr_Penonton Q = first(L);
        while (next(Q) != NULL) {
            Q = next(Q);
        }
        next(Q) = P;
    }
}

void editPenonton(list_Penonton &L, int idPenonton) {
    adr_Penonton i = findPenonton(L, idPenonton);
    if (i == NULL) {
        cout << "PENONTON TIDAK DITEMUKAN" << endl;
        return;
    }

    int pilihan = -1;
    while (pilihan != 0) {
        cout << "EDIT DATA PENONTON DENGAN ID = " << info(i).id_Penonton << endl;
        cout << "DATA YANG INGIN DIUBAH : " << endl;
        cout << "1. NAMA" << endl;
        cout << "2. BANYAK TIKET" << endl;
        cout << "3. EXIT" << endl;
        cout << "MASUKKAN PILIHAN = ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "NAMA BARU = ";
            cin.ignore();
            getline(cin, info(i).nama);
        } else if (pilihan == 2) {
            cout << "BANYAK TIKET BARU = ";
            cin >> info(i).banyak_Tiket;
        } else {
            pilihan = 0;
        }
        cout << endl;
    }
}

/* -------------------------
   OPERASI RELASI (SLL)
   ------------------------- */

void insertRelasi(list_Relasi &L, adr_Film film, adr_Penonton penonton) {
    adr_Relasi newRel = newRelasi(film, penonton);

    if (first(L) == NULL) {
        first(L) = newRel;
    } else {
        adr_Relasi temp = first(L);
        while (next(temp) != NULL) {
            temp = next(temp);
        }
        next(temp) = newRel;
    }
}

void showFilmPenonton(list_Relasi L) {
    adr_Relasi P = first(L);
    if (P == NULL) {
        cout << "Belum ada relasi Film - Penonton." << endl;
        return;
    }
    while (P != NULL) {
        cout << "Film: " << nextFilm(P)->info.judul
             << " - Penonton: " << nextPenonton(P)->info.nama
             << " (" << nextPenonton(P)->info.banyak_Tiket << " tiket)" << endl;
        P = next(P);
    }
}

void findPenontonFromFilm(list_Relasi &L, int idFilm) {
    adr_Relasi P = first(L);
    bool found = false;

    while (P != NULL) {
        if (nextFilm(P)->info.id_Film == idFilm) {
            if (!found) {
                cout << "FILM: " << nextFilm(P)->info.judul << endl;
                found = true;
            }
            cout << "Penonton ID: " << nextPenonton(P)->info.id_Penonton
                 << ", Nama: " << nextPenonton(P)->info.nama << endl;
        }
        P = next(P);
    }

    if (!found) {
        cout << "Tidak ada penonton yang ditemukan untuk ID Film " << idFilm << "." << endl;
    }
}
