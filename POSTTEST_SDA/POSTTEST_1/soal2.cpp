#include <iostream>
using namespace std;

// Fungsi untuk menghitung jumlah elemen baris genap
void hitungJumlahBarisGenap(int matriks[3][3]) {
    int total = 0;
    
    // Baris genap (indeks 1, karena mulai dari 0)
    for (int j = 0; j < 3; j++) {
        total += matriks[1][j];
    }
    
    cout << "Jumlah elemen baris genap (indeks 1): " << total << endl;
}

int main() {
    cout << "=== SOAL 2: MENGHITUNG JUMLAH ELEMEN BARIS GENAP MATRIKS ===" << endl;
    cout << "============================================================" << endl;
    
    // Matriks 3x3
    int matriks[3][3] = {
        {1, 2, 3},
        {4, 5, 6},  // Baris genap (indeks 1)
        {7, 8, 9}
    };
    
    cout << "Matriks 3x3:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Baris " << i << ": ";
        for (int j = 0; j < 3; j++) {
            cout << matriks[i][j] << " ";
        }
        cout << endl;
    }
    
    // Memanggil fungsi untuk menghitung jumlah elemen baris genap
    hitungJumlahBarisGenap(matriks);
    
    return 0;
}