/*
Nama Program    : LSB_Steg.cpp
Nama            : Fitri Sahwalia
NPM             : 140810240031
Tanggal Buat    : 06 Oktober 2026
Deskripsi       : membuat program untuk memecahkan kode menggunakan metode kriptografi Steganografi
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Fungsi untuk melakukan Encode (Menyembunyikan Pesan)
void encodeLSB(const string& inputFilename, const string& outputFilename, const string& secretMessage) {
    ifstream inFile(inputFilename);
    if (!inFile.is_open()) {
        cerr << "Gagal membuka file citra cover!" << endl;
        return;
    }

    string format;
    int width, height, maxVal;
    inFile >> format;
    if (format != "P3") {
        cerr << "Error: Format citra harus PPM (P3)!" << endl;
        return;
    }
    inFile >> width >> height >> maxVal;

    vector<int> pixels(width * height * 3);
    for (int i = 0; i < width * height * 3; ++i) {
        inFile >> pixels[i];
    }
    inFile.close();

    string fullMessage = secretMessage + '\0';
    vector<int> msgBits;

    // Konversi string pesan menjadi deretan bit
    for (char c : fullMessage) {
        for (int i = 7; i >= 0; --i) {
            msgBits.push_back((c >> i) & 1);
        }
    }

    if (msgBits.size() > pixels.size()) {
        cerr << "Error: Pesan terlalu panjang untuk kapasitas citra ini!" << endl;
        return;
    }

    // Menyisipkan bit pesan ke dalam LSB (Least Significant Bit) dari komponen pixel citra
    for (size_t i = 0; i < msgBits.size(); ++i) {
        pixels[i] = (pixels[i] & ~1) | msgBits[i];
    }

    // Simpan hasil ke file stego-image baru
    ofstream outFile(outputFilename);
    outFile << format << "\n" << width << " " << height << "\n" << maxVal << "\n";
    for (int i = 0; i < width * height * 3; ++i) {
        outFile << pixels[i] << " ";
    }
    outFile.close();
    
    cout << "Sukses! Pesan berhasil disembunyikan ke dalam " << outputFilename << endl;
}

// Fungsi untuk melakukan Decode (Mengekstrak Pesan)
void decodeLSB(const string& inputFilename) {
    ifstream inFile(inputFilename);
    if (!inFile.is_open()) {
        cerr << "Gagal membuka file stego-image!" << endl;
        return;
    }

    string format;
    int width, height, maxVal;
    inFile >> format;
    if (format != "P3") {
        cerr << "Error: Format citra harus PPM (P3)!" << endl;
        return;
    }
    inFile >> width >> height >> maxVal;

    vector<int> pixels(width * height * 3);
    for (int i = 0; i < width * height * 3; ++i) {
        inFile >> pixels[i];
    }
    inFile.close();

    string extractedMessage = "";
    char currentChar = 0;
    int bitCount = 0;

    // Ekstrak bit LSB dari setiap pixel
    for (size_t i = 0; i < pixels.size(); ++i) {
        int lsb = pixels[i] & 1;
        currentChar = (currentChar << 1) | lsb;
        bitCount++;

        if (bitCount == 8) {
            if (currentChar == '\0') break; // Berhenti jika menemui terminator
            extractedMessage += currentChar;
            currentChar = 0;
            bitCount = 0;
        }
    }

    cout << "Pesan rahasia yang ditemukan: " << extractedMessage << endl;
}

int main() {
    int pilihan;
    cout << "=== Program Steganografi LSB C++ ===\n";
    cout << "1. Encode Pesan (Sembunyikan)\n";
    cout << "2. Decode Pesan (Ekstrak)\n";
    cout << "Pilihan menu (1/2): ";
    cin >> pilihan;

    if (pilihan == 1) {
        string inFile, outFile, msg;
        cout << "Masukkan nama file cover (contoh: gambar.ppm): ";
        cin >> inFile;
        cout << "Masukkan nama file output stego (contoh: stego.ppm): ";
        cin >> outFile;
        cout << "Masukkan pesan rahasia yang ingin disembunyikan: ";
        cin.ignore();
        getline(cin, msg);
        encodeLSB(inFile, outFile, msg);
    } else if (pilihan == 2) {
        string inFile;
        cout << "Masukkan nama file stego yang akan diekstrak: ";
        cin >> inFile;
        decodeLSB(inFile);
    } else {
        cout << "Pilihan tidak valid!" << endl;
    }

    return 0;
}