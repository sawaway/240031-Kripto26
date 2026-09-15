#include <iostream>
#include <string>
using namespace std;

// Mengubah huruf ke angka
int hurufKeAngka(char huruf){
    return huruf - 'A';
}

// Mengubah angka ke huruf
char angkaKeHuruf(int angka){
    angka = angka % 26;

    if (angka < 0){
        angka += 26;
    }

    return char(angka + 'A');
}

// Mencari invers modulo
int inversModulo(int a){
    a = a % 26;

    for (int x = 1; x < 26; x++){
        if ((a * x) % 26 == 1)
            return x;
    }

    return -1;
}

// Mencari determin matriks 2 x 2
int determinan(int matriks[2][2]) {

    return (
        matriks[0][0] * matriks[1][1]
        -
        matriks[0][1] * matriks[1][0]
    );
}

// Mencari inver matriks 2 x 2
bool inversMatriks(int matriks[2][2],
                   int hasil[2][2]) {

    int det = determinan(matriks);

    det = det % 26;

    if (det < 0) {
        det += 26;
    }

    // Mencari invers determinan
    int inversDet = inversModulo(det);

    // Tidak memiliki invers
    if (inversDet == -1) {
        return false;
    }

    int a = matriks[0][0];
    int b = matriks[0][1];
    int c = matriks[1][0];
    int d = matriks[1][1];

    hasil[0][0] = (d * inversDet) % 26;
    hasil[0][1] = (-b * inversDet) % 26;
    hasil[1][0] = (-c * inversDet) % 26;
    hasil[1][1] = (a * inversDet) % 26;

    // Memastikan hasil tidak negatif
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {

            if (hasil[i][j] < 0) {
                hasil[i][j] += 26;
            }
        }
    }

    return true;
}


// Enkripsi
string enkripsi(string plaintext,
                int kunci[2][2]) {

    // Mengubah menjadi huruf besar
    for (int i = 0; i < plaintext.length(); i++) {
        if (plaintext[i] >= 'a' &&
            plaintext[i] <= 'z') {

            plaintext[i] =
                plaintext[i] - 'a' + 'A';
        }
    }

    // Jika jumlah huruf ganjil,
    // tambahkan X
    if (plaintext.length() % 2 != 0) {
        plaintext += 'X';
    }

    string ciphertext = "";

    for (int i = 0; i < plaintext.length(); i += 2) {

        int p1 = hurufKeAngka(plaintext[i]);
        int p2 = hurufKeAngka(plaintext[i + 1]);

        int c1 =
            (kunci[0][0] * p1 +
             kunci[0][1] * p2) % 26;

        int c2 =
            (kunci[1][0] * p1 +
             kunci[1][1] * p2) % 26;

        ciphertext += angkaKeHuruf(c1);
        ciphertext += angkaKeHuruf(c2);
    }

    return ciphertext;
}


// Dekripsi
string dekripsi(string ciphertext,
                int kunci[2][2]) {

    int invers[2][2];

    // Mencari invers kunci
    if (!inversMatriks(kunci, invers)) {

        return "ERROR";
    }

    string plaintext = "";

    for (int i = 0; i < ciphertext.length(); i += 2) {

        int c1 = hurufKeAngka(ciphertext[i]);
        int c2 = hurufKeAngka(ciphertext[i + 1]);

        int p1 =
            (invers[0][0] * c1 +
             invers[0][1] * c2) % 26;

        int p2 =
            (invers[1][0] * c1 +
             invers[1][1] * c2) % 26;

        plaintext += angkaKeHuruf(p1);
        plaintext += angkaKeHuruf(p2);
    }

    return plaintext;
}


// Mencari kunci
bool cariKunci(string plaintext,
               string ciphertext,
               int kunci[2][2]) {

    if (plaintext.length() != 4 ||
        ciphertext.length() != 4) {

        return false;
    }

    // Membuat matriks P
    int P[2][2];

    P[0][0] = hurufKeAngka(plaintext[0]);
    P[1][0] = hurufKeAngka(plaintext[1]);

    P[0][1] = hurufKeAngka(plaintext[2]);
    P[1][1] = hurufKeAngka(plaintext[3]);


    // Membuat matriks C
    int C[2][2];

    C[0][0] = hurufKeAngka(ciphertext[0]);
    C[1][0] = hurufKeAngka(ciphertext[1]);

    C[0][1] = hurufKeAngka(ciphertext[2]);
    C[1][1] = hurufKeAngka(ciphertext[3]);


    // Mencari invers P
    int PInv[2][2];

    if (!inversMatriks(P, PInv)) {
        return false;
    }


    // K = C × P^-1

    kunci[0][0] =
        (C[0][0] * PInv[0][0] +
         C[0][1] * PInv[1][0]) % 26;

    kunci[0][1] =
        (C[0][0] * PInv[0][1] +
         C[0][1] * PInv[1][1]) % 26;

    kunci[1][0] =
        (C[1][0] * PInv[0][0] +
         C[1][1] * PInv[1][0]) % 26;

    kunci[1][1] =
        (C[1][0] * PInv[0][1] +
         C[1][1] * PInv[1][1]) % 26;


    return true;
}


// Menampilkan matriks
void tampilkanMatriks(int matriks[2][2]) {

    cout << "[" << matriks[0][0]
         << " " << matriks[0][1]
         << "]" << endl;

    cout << "[" << matriks[1][0]
         << " " << matriks[1][1]
         << "]" << endl;
}


int main() {

    int pilihan;

    do {

        cout << "\n==============================" << endl;
        cout << "       PROGRAM HILL CIPHER" << endl;
        cout << "==============================" << endl;

        cout << "1. Enkripsi" << endl;
        cout << "2. Dekripsi" << endl;
        cout << "3. Mencari Kunci" << endl;
        cout << "4. Keluar" << endl;

        cout << "\nPilih menu: ";
        cin >> pilihan;


        // Enkripsi
        if (pilihan == 1) {

            string plaintext;

            int kunci[2][2];

            cout << "\n--- ENKRIPSI ---" << endl;

            cout << "Masukkan plaintext: ";
            cin >> plaintext;

            cout << "\nMasukkan matriks kunci 2x2:" << endl;

            cout << "Baris 1 kolom 1: ";
            cin >> kunci[0][0];

            cout << "Baris 1 kolom 2: ";
            cin >> kunci[0][1];

            cout << "Baris 2 kolom 1: ";
            cin >> kunci[1][0];

            cout << "Baris 2 kolom 2: ";
            cin >> kunci[1][1];


            string hasil =
                enkripsi(plaintext, kunci);

            cout << "\nCiphertext: "
                 << hasil << endl;
        }


        // Dekripsi
        else if (pilihan == 2) {

            string ciphertext;

            int kunci[2][2];

            cout << "\n--- DEKRIPSI ---" << endl;

            cout << "Masukkan ciphertext: ";
            cin >> ciphertext;

            cout << "\nMasukkan matriks kunci 2x2:" << endl;

            cout << "Baris 1 kolom 1: ";
            cin >> kunci[0][0];

            cout << "Baris 1 kolom 2: ";
            cin >> kunci[0][1];

            cout << "Baris 2 kolom 1: ";
            cin >> kunci[1][0];

            cout << "Baris 2 kolom 2: ";
            cin >> kunci[1][1];


            // Mengecek jumlah ciphertext
            if (ciphertext.length() % 2 != 0) {

                cout << "\nCiphertext harus memiliki "
                     << "jumlah huruf genap."
                     << endl;

            } else {

                string hasil =
                    dekripsi(ciphertext, kunci);


                if (hasil == "ERROR") {

                    cout << "\nKunci tidak memiliki "
                         << "invers modulo 26."
                         << endl;

                } else {

                    cout << "\nPlaintext: "
                         << hasil << endl;
                }
            }
        }


        // Mencari kunci
        else if (pilihan == 3) {

            string plaintext;
            string ciphertext;

            int kunci[2][2];

            cout << "\n--- MENCARI KUNCI ---"
                 << endl;

            cout << "Masukkan plaintext (4 huruf): ";
            cin >> plaintext;

            cout << "Masukkan ciphertext (4 huruf): ";
            cin >> ciphertext;


            // Ubah menjadi huruf besar
            for (int i = 0; i < plaintext.length(); i++) {
                if (plaintext[i] >= 'a' &&
                    plaintext[i] <= 'z') {

                    plaintext[i] =
                        plaintext[i] - 'a' + 'A';
                }
            }

            for (int i = 0; i < ciphertext.length(); i++) {
                if (ciphertext[i] >= 'a' &&
                    ciphertext[i] <= 'z') {

                    ciphertext[i] =
                        ciphertext[i] - 'a' + 'A';
                }
            }


            bool berhasil =
                cariKunci(
                    plaintext,
                    ciphertext,
                    kunci
                );


            if (berhasil) {

                cout << "\nKunci ditemukan:"
                     << endl;

                tampilkanMatriks(kunci);

            } else {

                cout << "\nKunci tidak dapat ditemukan."
                     << endl;
            }
        }


    
        // Keluar
        else if (pilihan == 4) {

            cout << "\nProgram selesai."
                 << endl;
        }


        else {

            cout << "\nPilihan tidak valid."
                 << endl;
        }

    } while (pilihan != 4);


    return 0;
}