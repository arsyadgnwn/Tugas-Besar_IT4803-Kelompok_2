#ifndef BIOSKOP_H_INCLUDED
#define BIOSKOP_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

// Makro untuk kemudahan akses
#define info(P) (P)->info
#define next(P) (P)->next
#define prev(P) (P)->prev
#define nextFilm(R) (R)->nextFilm
#define nextaktor(R) (R)->nextaktor
#define first(L) ((L).first)
#define last(L) ((L).last)

/* -------------------------
    STRUCT FILM (PARENT - DLL)
   ------------------------- */
struct Film {
    int id_Film;
    string judul;
    string namaaktor; // Biasanya ini aktor utama
    int durasi;
    int jumlah_Penonton;
};

typedef struct elm_Film *adr_Film;

struct elm_Film {
    Film info;
    adr_Film next;
    adr_Film prev;
};

struct list_Film {
    adr_Film first;
    adr_Film last;
};

/* -----------------------------
    STRUCT AKTOR (CHILD - SLL)
   ----------------------------- */
struct aktor {
    int id_aktor; // Perbaikan: id_Film di child biasanya membingungkan, lebih baik id_aktor
    string namaaktor;
    int umur;     // Saya ganti durasi menjadi umur agar lebih logis untuk data aktor
};

typedef struct elm_aktor *adr_aktor;

struct elm_aktor {
    aktor info;
    adr_aktor next;
};

struct list_aktor {
    adr_aktor first;
};

/* -------------------------
    STRUCT RELASI (SLL)
   ------------------------- */
typedef struct elm_Relasi *adr_Relasi;

struct elm_Relasi {
    adr_Film nextFilm;
    adr_aktor nextaktor;
    adr_Relasi next;
};

struct list_Relasi {
    adr_Relasi first;
};

/* -------------------------
    PROTOTYPE FUNGSI
   ------------------------- */

// Manajemen List
void createListFilm(list_Film &L);
void createListaktor(list_aktor &L);
void createListRelasi(list_Relasi &L);

// Alokasi
adr_Film newFilm(Film data);
adr_aktor newaktor(aktor data); // Koreksi: sebelumnya adr_Penonton
adr_Relasi newRelasi(adr_Film film, adr_aktor aktor);

// Operasi Film
void insert_first_Film(list_Film &L, adr_Film P);
void insert_last_Film(list_Film &L, adr_Film P);
void showAllFilms(list_Film L);
void deleteFilm(list_Film &filmList, list_Relasi &relasiList, int idFilm);
adr_Film findFilm(list_Film L, int idFilm);
void editFilm(list_Film &L, int idFilm);

// Operasi Aktor
void insert_last_aktor(list_aktor &L, adr_aktor P);
void showAllaktor(list_aktor L);
adr_aktor findaktor(list_aktor L, int idaktor); // Koreksi: sebelumnya adr_Penonton

// Operasi Relasi
void insertRelasi(list_Relasi &L, adr_Film film, adr_aktor aktor);
void showFilmaktor(list_Relasi L);
void findaktorFromFilm(list_Relasi &L, int idFilm);

#endif
