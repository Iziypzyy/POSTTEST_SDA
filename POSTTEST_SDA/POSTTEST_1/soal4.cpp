#include <iostream>
using namespace std;

// Fungsi untuk menukar nilai dua variabel menggunakan reference
void tukarNilai(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    cout << "=== SOAL 4: MENUKAR NILAI DUA VARIABEL INTEGER DENGAN REFERENCE ===" << endl;
    cout << "===========================================================" << endl;
    
    int a, b;
    
    // Input nilai
    cout << "Masukkan nilai pertama: ";
    cin >> a;
    
    cout << "Masukkan nilai kedua: ";
    cin >> b;
    
    // Menampilkan nilai sebelum ditukar
    cout << "Sebelum ditukar: a = " << a << ", b = " << b << endl;
    
    // Memanggil fungsi dengan reference parameter untuk menukar nilai
    tukarNilai(a, b);
    
    // Menampilkan nilai setelah ditukar
    cout << "Setelah ditukar: a = " << a << ", b = " << b << endl;
    
    return 0;
}