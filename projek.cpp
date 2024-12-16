#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Film {
    string judul;
    float rating;
    string tahun;
    string genre;
    string sutradara;
    float durasi;
    string deskripsi;
};

void tambahFilm(Film &film) {
    cout << "Masukkan judul film: ";
    cin.ignore();
    getline(cin, film.judul);
    film.judul[0]= toupper(film.judul[0]);


    for (int i = 0; i < 1;)
    {
        cout << "Masukkan rating(0-10): ";
        cin >> film.rating;
        if (film.rating < 0 || film.rating > 10){
        cout << "tolong masukan rating dengan benar" << endl;
        } else
        {
            i++;
        }
    }

    cout << "Masukkan tahun film: ";
    cin >> film.tahun;

    cout << "Masukan genre film:" << endl;
    cout << "0 = stop" << endl;
    cout << "1.Action " << "2.Adventure " << "3.Comedy " << "4.Drama " << "5.Horror " << "6.Romance " << "7.Sci-Fi " << "8.Thriller" <<endl;
    const string Genre[] = {" ", "Action","Adventure", "Comedy", "Drama", "Horror", "Romance", "Sci-Fi"} ;
    cout << "Masukan genre: ";
    int pilihan;
    film.genre = "";
    while (true) {
        cout << "Masukan genre: ";
        cin >> pilihan;
        if (pilihan > 0 && pilihan < 6) {
            if (!film.genre.empty()) {
                film.genre += ", ";
            }
            film.genre += Genre[pilihan];
            cout << Genre[pilihan] << " ditambahkan." << endl;
        } else if (pilihan == 0) {
            break;
        } else {
            cout << "Tolong masukan pilihan yang benar" << endl;
        }
    }
    
    cout << "Masukkan sutradara: ";
    cin.ignore();
    getline(cin, film.sutradara);
    
    cout << "Masukkan durasi(dalam menit): ";
    cin >> film.durasi;
    
    cout << "Masukan deskripsi film: ";
    cin.ignore();
    getline(cin, film.deskripsi);
}

void simpanFilm(Film film) {
    ofstream file("film.txt", ios::app);
    if (file.is_open()) {
        file << "Judul: " << film.judul << endl;
        file << "rating: " << film.rating << "/10" <<endl;
        file << "Tahun: " << film.tahun << endl;
        file << "Genre: " << film.genre << endl;
        file << "Sutradara: " << film.sutradara << endl;
        file << "Durasi: " << film.durasi << " menit" << endl;
        file << "Deskripsi: " << film.deskripsi << endl;
        file << endl;
        file.close();
        cout << "Film berhasil disimpan!" << endl;
    } else {
        cout << "Gagal menyimpan film!" << endl;
    }
}

void searchfilm(const string &judul) {
    ifstream file("film.txt");
    string line;
    bool found = false;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find("Judul: " + judul) != string::npos) {
                found = true;
                cout << line << endl; 
                for (int i = 0; i < 6; i++) { 
                    getline(file, line);
                    cout << line << endl;
                }
                break;
            }
        }
        file.close();
    } else {
        cout << "Gagal membuka file!" << endl;
    }

    if (!found) {
        cout << "Film dengan judul '" << judul << "' tidak ditemukan." << endl;
    }
}


int main() {
    const int MAX_FILMS = 100;
    Film films[MAX_FILMS];
    int count = 0;
    char choice;
    int x;
    string searchTitle;
    do {cout << "1.Cari film" << endl;
    cout << "2.Tambahkan film" << endl;
    cout << "Masukan Pilihan: ";
    cin >> x;
    switch (x)
    {
    case 1:
    cout << "Masukkan judul film yang ingin dicari(huruf pertama kapital): ";
    cin.ignore();
    getline(cin, searchTitle);
    searchfilm(searchTitle);;
        break;
    case 2:
    do {
        if (count < MAX_FILMS) {
            tambahFilm(films[count]);
            simpanFilm(films[count]);
            count++;
        } else {
            cout << "Jumlah film maksimum telah tercapai." << endl;
            break;
        }

        cout << "Apakah Anda ingin menambahkan film lain? (y/n): ";
        cin >> choice;
        cin.ignore(); 
    } while (choice == 'y' || choice == 'Y');
        break;
    default:
        break;
    }

cout << "Apakah Anda ingin kembali ke menu utama? (y/n): ";
        cin >> choice;
        cin.ignore(); 
    } while (choice == 'y' || choice == 'Y');


    return 0;

}