#include "bioskop.h"

/* -------------------------
   IMPLEMENTASI LIST FILM
   ------------------------- */
void createListFilm(list_Film &L) {
    first(L) = NULL;
    last(L) = NULL;
}

adr_Film newFilm(Film data) {
    adr_Film P = new elm_Film;
    info(P) = data;
    next(P) = NULL;
    prev(P) = NULL;
    return P;
}

void insert_first_Film(list_Film &L, adr_Film P) {
    if (first(L) == NULL) {
        first(L) = P;
        last(L) = P;
    } else {
        next(P) = first(L);
        prev(first(L)) = P;
        first(L) = P;
    }
}

void insert_last_Film(list_Film &L, adr_Film P) {
    if (first(L) == NULL) {
        first(L) = P;
        last(L) = P;
    } else {
        prev(P) = last(L);
        next(last(L)) = P;
        last(L) = P;
    }
}

adr_Film findFilm(list_Film L, int idFilm) {
    adr_Film P = first(L);
    while (P != NULL) {
        if (info(P).id_Film == idFilm) return P;
        P = next(P);
    }
    return NULL;
}

void showAllFilms(list_Film L) {
    adr_Film P = first(L);
    if (P == NULL) {
        cout << "List Film Kosong." << endl;
    } else {
        while (P != NULL) {
            cout << "ID: " << info(P).id_Film << " | Judul: " << info(P).judul 
                 << " | Aktor: " << info(P).namaaktor << " | Durasi: " << info(P).durasi << endl;
            P = next(P);
        }
    }
}

/* -----------------------------
   IMPLEMENTASI LIST AKTOR
   ----------------------------- */
void createListaktor(list_aktor &L) {
    first(L) = NULL;
}

adr_aktor newaktor(aktor data) {
    adr_aktor P = new elm_aktor;
    info(P) = data;
    next(P) = NULL;
    return P;
}

void insert_last_aktor(list_aktor &L, adr_aktor P) {
    if (first(L) == NULL) {
        first(L) = P;
    } else {
        adr_aktor Q = first(L);
        while (next(Q) != NULL) {
            Q = next(Q);
        }
        next(Q) = P;
    }
}

/* -----------------------------
   IMPLEMENTASI RELASI
   ----------------------------- */
void createListRelasi(list_Relasi &L) {
    first(L) = NULL;
}

adr_Relasi newRelasi(adr_Film film, adr_aktor aktor) {
    adr_Relasi R = new elm_Relasi;
    nextFilm(R) = film;
    nextaktor(R) = aktor;
    next(R) = NULL;
    return R;
}

void insertRelasi(list_Relasi &L, adr_Film film, adr_aktor aktor) {
    adr_Relasi R = newRelasi(film, aktor);
    if (first(L) == NULL) {
        first(L) = R;
    } else {
        next(R) = first(L);
        first(L) = R;
    }
}

void showFilmaktor(list_Relasi L) {
    adr_Relasi R = first(L);
    if (R == NULL) {
        cout << "Tidak ada relasi film dan aktor." << endl;
    } else {
        while (R != NULL) {
            cout << "Film: " << info(nextFilm(R)).judul 
                 << " <---> Aktor: " << info(nextaktor(R)).namaaktor << endl;
            R = next(R);
        }
    }
}

void findaktorFromFilm(list_Relasi &L, int idFilm) {
    adr_Relasi R = first(L);
    bool found = false;
    cout << "Mencari aktor di Film ID [" << idFilm << "]:" << endl;
    while (R != NULL) {
        if (info(nextFilm(R)).id_Film == idFilm) {
            cout << "- " << info(nextaktor(R)).namaaktor << endl;
            found = true;
        }
        R = next(R);
    }
    if (!found) cout << "Tidak ada aktor yang ditemukan untuk film ini." << endl;
}

/* -----------------------------
   FUNGSI DELETE & EDIT (BASIC)
   ----------------------------- */
void deleteFilm(list_Film &filmList, list_Relasi &relasiList, int idFilm) {
    adr_Film P = findFilm(filmList, idFilm);
    if (P != NULL) {
        // Hapus relasi yang terhubung terlebih dahulu (Opsional tergantung logika bisnis)
        // Di sini kita hanya menghapus elemen Film dari Double Linked List
        if (P == first(filmList)) {
            first(filmList) = next(P);
            if (first(filmList) != NULL) prev(first(filmList)) = NULL;
        } else if (P == last(filmList)) {
            last(filmList) = prev(P);
            next(last(filmList)) = NULL;
        } else {
            next(prev(P)) = next(P);
            prev(next(P)) = prev(P);
        }
        delete P;
        cout << "Film berhasil dihapus." << endl;
    } else {
        cout << "Film tidak ditemukan." << endl;
    }
}
