#ifndef BIOSKOP_H_INCLUDED
#define BIOSKOP_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

#define info(P) P->info
#define next(P) P->next
#define prev(P) P->prev
#define nextFilm(R) R->nextFilm
#define nextPenonton(R) R->nextPenonton
#define first(L) L.first
#define last(L) L.last

/* -------------------------
   STRUCT FILM (PARENT, DLL)
   ------------------------- */
struct Film {
    int id_Film;
    string judul;
    string jam_Tayang;
    int harga;
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
   STRUCT PENONTON (CHILD, SLL)
   ----------------------------- */
struct Penonton {
    int id_Penonton;
    string nama;
    int banyak_Tiket;
};

typedef struct elm_Penonton *adr_Penonton;

struct elm_Penonton {
    Penonton info;
    adr_Penonton next;
};

struct list_Penonton {
    adr_Penonton first;
};

/* ------------------
   STRUCT RELASI SLL
   ------------------ */
typedef struct elm_Relasi *adr_Relasi;

struct elm_Relasi {
    adr_Film nextFilm;
    adr_Penonton nextPenonton;
    adr_Relasi next;
};

struct list_Relasi {
    adr_Relasi first;
};

/* ------------
   FUNGSI UTAMA
   ------------ */

void createListFilm(list_Film &L);
void createListPenonton(list_Penonton &L);
void createListRelasi(list_Relasi &L);

adr_Film newFilm(Film data);
adr_Penonton newPenonton(Penonton data);
adr_Relasi newRelasi(adr_Film film, adr_Penonton penonton);

void insert_first_Film(list_Film &L, adr_Film P);
void insert_last_Film(list_Film &L, adr_Film P);
void showAllFilms(list_Film L);
void deleteFilm(list_Film &filmList, list_Relasi &relasiList, int idFilm);
adr_Film findFilm(list_Film L, int idFilm);
void editFilm(list_Film &L, int idFilm);

void ShowAllPenonton(list_Penonton L);
adr_Penonton findPenonton(list_Penonton L, int idPenonton);
void insert_first_Penonton(list_Penonton &L, adr_Penonton P);
void insert_last_Penonton(list_Penonton &L, adr_Penonton P);
void editPenonton(list_Penonton &L, int idPenonton);

void insertRelasi(list_Relasi &L, adr_Film film, adr_Penonton penonton);
void showFilmPenonton(list_Relasi L);
void findPenontonFromFilm(list_Relasi &L, int idFilm);

#endif
