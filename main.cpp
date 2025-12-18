#include <iostream>
#include "bioskop.h"

using namespace std;

void menu() {
    cout << "\n========== MENU BIOSKOP ==========" << endl;
    cout << "1. Tambah Film" << endl;
    cout << "2. Tampilkan Semua Film" << endl;
    cout << "3. Tambah Aktor" << endl;
    cout << "4. Tampilkan Relasi Film - Aktor" << endl;
    cout << "5. Tambah Relasi Film - Aktor" << endl;
    cout << "6. Cari Aktor dari Film" << endl;
    cout << "7. Hapus Film" << endl;
    cout << "0. Keluar" << endl;
    cout << "=================================" << endl;
    cout << "Pilih menu: ";
}

int main() {
    list_Film filmList;
    list_aktor aktorList;
    list_Relasi relasiList;

    createListFilm(filmList);
    createListaktor(aktorList);
    createListRelasi(relasiList);

    int pilihan;

    do {
        menu();
        cin >> pilihan;

        switch (pilihan) {

        case 1: {
            Film f;
            cout << "\nID Film      : ";
            cin >> f.id_Film;
            cin.ignore();
            cout << "Judul Film   : ";
            getline(cin, f.judul);
            cout << "Aktor Utama  : ";
            getline(cin, f.namaaktor);
            cout << "Durasi (menit): ";
            cin >> f.durasi;
            f.jumlah_Penonton = 0;

            adr_Film P = newFilm(f);
            insert_last_Film(filmList, P);

            cout << "Film berhasil ditambahkan." << endl;
            break;
        }

        case 2:
            cout << "\n=== DAFTAR FILM ===" << endl;
            showAllFilms(filmList);
            break;

        case 3: {
            aktor a;
            cout << "\nID Aktor  : ";
            cin >> a.id_aktor;
            cin.ignore();
            cout << "Nama Aktor: ";
            getline(cin, a.namaaktor);
            cout << "Umur      : ";
            cin >> a.umur;

            adr_aktor P = newaktor(a);
            insert_last_aktor(aktorList, P);

            cout << "Aktor berhasil ditambahkan." << endl;
            break;
        }

        case 4:
            cout << "\n=== RELASI FILM & AKTOR ===" << endl;
            showFilmaktor(relasiList);
            break;

        case 5: {
            int idFilm, idAktor;
            cout << "\nMasukkan ID Film  : ";
            cin >> idFilm;
            cout << "Masukkan ID Aktor : ";
            cin >> idAktor;

            adr_Film film = findFilm(filmList, idFilm);
            adr_aktor aktor = findaktor(aktorList, idAktor);

            if (film != NULL && aktor != NULL) {
                insertRelasi(relasiList, film, aktor);
                cout << "Relasi berhasil ditambahkan." << endl;
            } else {
                cout << "Film atau Aktor tidak ditemukan." << endl;
            }
            break;
        }

        case 6: {
            int idFilm;
            cout << "\nMasukkan ID Film: ";
            cin >> idFilm;
            findaktorFromFilm(relasiList, idFilm);
            break;
        }

        case 7: {
            int idFilm;
            cout << "\nMasukkan ID Film yang akan dihapus: ";
            cin >> idFilm;
            deleteFilm(filmList, relasiList, idFilm);
            break;
        }

        case 0:
            cout << "Program selesai." << endl;
            break;

        default:
            cout << "Pilihan tidak valid." << endl;
        }

    } while (pilihan != 0);

    return 0;
}
