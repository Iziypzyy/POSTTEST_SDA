#include <iostream>
#include <string>
using namespace std;

// Struct Mahasiswa
struct Mahasiswa {
    string nama;
    string nim;
    double ipk;
};

int main() {
    cout << "=== SOAL 3: DATA MAHASISWA BERDASARKAN IPK (ASCENDING) ===" << endl;
    cout << "==========================================================" << endl;
    
    // Array of struct Mahasiswa
    Mahasiswa mhs[4];
    
    // Input data mahasiswa
    mhs[0].nama = "rasyid";
    mhs[0].nim = "6042";
    mhs[0].ipk = 3.55;
    
    mhs[1].nama = "zifa";
    mhs[1].nim = "6025";
    mhs[1].ipk = 3.75;
    
    mhs[2].nama = "ahnaf";
    mhs[2].nim = "6035";
    mhs[2].ipk = 3.50;
    
    mhs[3].nama = "tomlembong";
    mhs[3].nim = "6001";
    mhs[3].ipk = 3.99;
    
    // Mengurutkan berdasarkan IPK (ascending) - Bubble Sort
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (mhs[j].ipk > mhs[j+1].ipk) {
                // Tukar posisi
                Mahasiswa temp = mhs[j];
                mhs[j] = mhs[j+1];
                mhs[j+1] = temp;
            }
        }
    }
    
    // Menampilkan data mahasiswa
    cout << "Data Mahasiswa (diurutkan berdasarkan IPK ascending):" << endl;
    cout << "Nama\t\tNIM\t\tIPK" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < 4; i++) {
        cout << mhs[i].nama << "\t\t" << mhs[i].nim << "\t\t" << mhs[i].ipk << endl;
    }
    
    return 0;
}