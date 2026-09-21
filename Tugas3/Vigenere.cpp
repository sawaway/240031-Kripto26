/*
Nama Program    : Vigenere.cpp
Nama            : Fitri Sahwalia
NPM             : 140810240031
Tanggal Buat    : 21 Sepetember 2026
Deskripsi       : membuat program untuk memecahkan kode menggunakan metode kriptografi viginere cipher
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Fungsi untuk enkripsi
string enkripsi(string teks, string key){
    string hasil="";
    int j = 0;
    for(int i = 0; i < teks.length(); i++){
        char c = teks[i];
        if (isalpha(c)){
            char k = toupper(key[j % key.length()]);
            int geser = k - 'A';

            if (isupper(c)){
                hasil += char((c - 'A' + geser) % 26 + 'A');
            }else{
                hasil += char((c - 'a' + geser) % 26 + 'a');
            }
            j++;
        }else{
            hasil += c;
        }
    }
    return hasil;
}

// Fungsi untuk deskripsi
string dekripsi(string teks, string key){
    string hasil="";
    int j = 0;
    for(int i = 0; i < teks.length(); i++){
        char c = teks[i];
        if (isalpha(c)){
            char k = toupper(key[j % key.length()]);
            int geser = k - 'A';

            if (isupper(c)){
                hasil += char((c - 'A' - geser + 26) % 26 + 'A');
            }else{
                hasil += char((c - 'a' - geser + 26) % 26 + 'a');
            }
            j++;
        }else{
            hasil += c;
        }
    }
    return hasil;
}

int main() {
    string teks;
    string key;
    int pilihan;

    do {
        cout << "\n=== VIGENERE CIPHER ===" << endl;
        cout << "1. Enkripsi" << endl;
        cout << "2. Dekripsi" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (pilihan == 1) {

            cin.ignore();

            cout << "Masukkan teks: ";
            getline(cin, teks);

            cout << "Masukkan key: ";
            cin >> key;

            // Memastikan key hanya berisi huruf
            for (char c : key) {
                if (!isalpha(c)) {
                    cout << "Key harus berupa huruf!" << endl;
                    continue;
                }
            }

            if (key.empty()) {
                cout << "Key tidak boleh kosong!" << endl;
                continue;
            }

            cout << "Hasil Enkripsi: " << enkripsi(teks, key) << endl;

        } 
        else if (pilihan == 2) {

            cin.ignore();

            cout << "Masukkan teks: ";
            getline(cin, teks);

            cout << "Masukkan key: ";
            cin >> key;

            // Memastikan key hanya berisi huruf
            for (char c : key) {
                if (!isalpha(c)) {
                    cout << "Key harus berupa huruf!" << endl;
                    continue;
                }
            }

            if (key.empty()) {
                cout << "Key tidak boleh kosong!" << endl;
                continue;
            }

            cout << "Hasil Dekripsi: " << dekripsi(teks, key) << endl;

        } 
        else if (pilihan == 3) {

            cout << "Program selesai." << endl;

        } 
        else {

            cout << "Pilihan tidak valid!" << endl;

        }

    } while (pilihan != 3);

    return 0;
}