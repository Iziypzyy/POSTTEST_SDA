#include <iostream>
using namespace std;

// Fungsi untuk membalik array menggunakan pointer
void balikArray(int *arr, int ukuran) {
    int *awal = arr;
    int *akhir = arr + ukuran - 1;
    
    while (awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;
        
        awal++;
        akhir--;
    }
}

int main() {
    cout << "=== SOAL 1: MEMBALIK ARRAY BILANGAN PRIMA ===" << endl;
    cout << "=============================================" << endl;
    
    // Array dengan 7 bilangan prima
    int bilangan_prima[7] = {2, 3, 5, 7, 11, 13, 17};
    
    cout << "Array sebelum dibalik: ";
    for (int i = 0; i < 7; i++) {
        cout << bilangan_prima[i] << " ";
    }
    cout << endl;
    
    // Memanggil fungsi dengan parameter pointer untuk membalik array
    balikArray(bilangan_prima, 7);
    
    cout << "Array setelah dibalik: ";
    for (int i = 0; i < 7; i++) {
        cout << bilangan_prima[i] << " ";
    }
    cout << endl;
    
    return 0;
}