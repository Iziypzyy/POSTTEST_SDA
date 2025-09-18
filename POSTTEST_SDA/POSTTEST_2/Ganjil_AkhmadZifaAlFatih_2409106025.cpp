#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include <limits>
using namespace std;

// Struct untuk merepresentasikan game dalam inventory
struct Game {
    string namaGame;
    int jumlah;
    string genre;
    Game* next;
};

// Class untuk mengelola linked list inventory
class ManajerInventory {
private:
    Game* head;
    Game* tail;
    int jumlahAwal;
    int posisiSisip;
    
public:
    ManajerInventory(int jmlAwal, int posSisip) : head(nullptr), tail(nullptr), jumlahAwal(jmlAwal), posisiSisip(posSisip) {}
    
    // Cek apakah inventory kosong
    bool apakahKosong() {
        return head == nullptr;
    }
    
    // Tambah game baru di akhir
    void tambahGameBaru(string nama, string genre) {
        Game* gameBaru = new Game;
        gameBaru->namaGame = nama;
        gameBaru->jumlah = jumlahAwal;
        gameBaru->genre = genre;
        gameBaru->next = nullptr;
        
        if (apakahKosong()) {
            head = gameBaru;
            tail = gameBaru;
        } else {
            tail->next = gameBaru;
            tail = gameBaru;
        }
        
        cout << "Game '" << nama << "' berhasil ditambahkan dengan jumlah " << jumlahAwal << "!\n";
    }
    
    // Sisipkan game di posisi tertentu
    void sisipkanGame(string nama, string genre) {
        if (posisiSisip < 1) {
            cout << "Posisi harus lebih besar dari 0!\n";
            return;
        }
        
        Game* gameBaru = new Game;
        gameBaru->namaGame = nama;
        gameBaru->jumlah = jumlahAwal;
        gameBaru->genre = genre;
        
        if (posisiSisip == 1) {
            gameBaru->next = head;
            head = gameBaru;
            if (tail == nullptr) {
                tail = gameBaru;
            }
            cout << "Game '" << nama << "' berhasil disisipkan di posisi " << posisiSisip << "!\n";
            return;
        }
        
        Game* saatIni = head;
        Game* sebelumnya = nullptr;
        int hitung = 1;
        
        while (saatIni != nullptr && hitung < posisiSisip) {
            sebelumnya = saatIni;
            saatIni = saatIni->next;
            hitung++;
        }
        
        if (hitung < posisiSisip) {
            cout << "Posisi " << posisiSisip << " terlalu besar. Game akan ditambahkan di akhir.\n";
            tambahGameBaru(nama, genre);
        } else {
            sebelumnya->next = gameBaru;
            gameBaru->next = saatIni;
            if (saatIni == nullptr) {
                tail = gameBaru;
            }
            cout << "Game '" << nama << "' berhasil disisipkan di posisi " << posisiSisip << "!\n";
        }
    }
    
    // Hapus game terakhir
    void hapusGameTerakhir() {
        if (apakahKosong()) {
            cout << "Inventory kosong! Tidak ada game untuk dihapus.\n";
            return;
        }
        
        if (head == tail) {
            string gameTerhapus = head->namaGame;
            delete head;
            head = nullptr;
            tail = nullptr;
            cout << "Game '" << gameTerhapus << "' berhasil dihapus!\n";
            return;
        }
        
        Game* saatIni = head;
        while (saatIni->next != tail) {
            saatIni = saatIni->next;
        }
        
        string gameTerhapus = tail->namaGame;
        delete tail;
        tail = saatIni;
        tail->next = nullptr;
        cout << "Game '" << gameTerhapus << "' berhasil dihapus!\n";
    }
    
    // Tampilkan semua game dalam inventory dengan nomor pilihan
    void tampilkanGameUntukDipilih() {
        if (apakahKosong()) {
            cout << "Inventory kosong!\n";
            return;
        }
        
        cout << "\n+----- DAFTAR GAME YANG TERSEDIA -----+\n";
        cout << "| No. | Nama Game         | Jumlah |\n";
        cout << "+-----+-------------------+--------+\n";
        
        Game* saatIni = head;
        int hitung = 1;
        while (saatIni != nullptr) {
            cout << "| " << setw(3) << hitung << " | " 
                 << setw(17) << left << saatIni->namaGame << " | " 
                 << setw(6) << saatIni->jumlah << " |\n";
            saatIni = saatIni->next;
            hitung++;
        }
        
        cout << "+-----------------------------------+\n";
    }
    
    // Gunakan game berdasarkan pilihan nomor
    void gunakanGameBerdasarkanPilihan(int nomor) {
        if (apakahKosong()) {
            cout << "Inventory kosong! Tidak ada game untuk digunakan.\n";
            return;
        }
        
        if (nomor < 1) {
            cout << "Nomor tidak valid!\n";
            return;
        }
        
        Game* saatIni = head;
        Game* sebelumnya = nullptr;
        int hitung = 1;
        
        while (saatIni != nullptr && hitung < nomor) {
            sebelumnya = saatIni;
            saatIni = saatIni->next;
            hitung++;
        }
        
        if (saatIni == nullptr) {
            cout << "Nomor game tidak valid!\n";
            return;
        }
        
        // Kurangi jumlah game
        saatIni->jumlah -= 1;
        cout << "Game '" << saatIni->namaGame << "' digunakan. Jumlah sekarang: " << saatIni->jumlah << endl;
        
        // Hapus game jika jumlah habis
        if (saatIni->jumlah <= 0) {
            if (sebelumnya == nullptr) {
                // Hapus node pertama
                head = saatIni->next;
                if (head == nullptr) {
                    tail = nullptr;
                }
            } else {
                sebelumnya->next = saatIni->next;
                if (saatIni->next == nullptr) {
                    tail = sebelumnya;
                }
            }
            cout << "Game '" << saatIni->namaGame << "' dihapus dari inventory karena habis.\n";
            delete saatIni;
        }
    }
    
    // Gunakan game (versi lama dengan input nama)
    void gunakanGame(string nama) {
        if (apakahKosong()) {
            cout << "Inventory kosong! Tidak ada game untuk digunakan.\n";
            return;
        }
        
        Game* saatIni = head;
        Game* sebelumnya = nullptr;
        
        // Konversi nama ke lowercase untuk pencarian case-insensitive
        transform(nama.begin(), nama.end(), nama.begin(), ::tolower);
        
        while (saatIni != nullptr) {
            string namaSaatIni = saatIni->namaGame;
            transform(namaSaatIni.begin(), namaSaatIni.end(), namaSaatIni.begin(), ::tolower);
            
            if (namaSaatIni == nama) {
                saatIni->jumlah -= 1;
                cout << "Game '" << saatIni->namaGame << "' digunakan. Jumlah sekarang: " << saatIni->jumlah << endl;
                
                if (saatIni->jumlah <= 0) {
                    if (sebelumnya == nullptr) {
                        // Hapus node pertama
                        head = saatIni->next;
                        if (head == nullptr) {
                            tail = nullptr;
                        }
                        delete saatIni;
                    } else {
                        sebelumnya->next = saatIni->next;
                        if (saatIni->next == nullptr) {
                            tail = sebelumnya;
                        }
                        delete saatIni;
                    }
                    cout << "Game '" << nama << "' dihapus dari inventory karena habis.\n";
                }
                return;
            }
            
            sebelumnya = saatIni;
            saatIni = saatIni->next;
        }
        
        cout << "Game '" << nama << "' tidak ditemukan dalam inventory.\n";
    }
    
    // Tampilkan semua game dalam inventory
    void tampilkanInventory() {
        if (apakahKosong()) {
            cout << "Inventory kosong!\n";
            return;
        }
        
        cout << "\n+---------------------- INVENTORY GAME ----------------------+\n";
        cout << "| No. | Nama Game         | Jumlah | Genre              |\n";
        cout << "+-----+-------------------+--------+--------------------+\n";
        
        Game* saatIni = head;
        int hitung = 1;
        while (saatIni != nullptr) {
            cout << "| " << setw(3) << hitung << " | " 
                 << setw(17) << left << saatIni->namaGame << " | " 
                 << setw(6) << saatIni->jumlah << " | " 
                 << setw(18) << left << saatIni->genre << " |\n";
            saatIni = saatIni->next;
            hitung++;
        }
        
        cout << "+-------------------------------------------------------+\n";
    }
    
    // Destruktor untuk membersihkan memory
    ~ManajerInventory() {
        Game* saatIni = head;
        while (saatIni != nullptr) {
            Game* berikutnya = saatIni->next;
            delete saatIni;
            saatIni = berikutnya;
        }
    }
};

// Fungsi untuk memvalidasi input angka
int dapatkanIntegerTervalidasi() {
    int nilai;
    while (!(cin >> nilai)) {
        cout << "Input tidak valid. Masukkan angka: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return nilai;
}

// Fungsi utama
int main() {
    // Input identitas
    string nama, nim;
    cout << "Masukkan Nama Anda: ";
    getline(cin, nama);
    cout << "Masukkan NIM Anda: ";
    getline(cin, nim);
    
    // Validasi NIM
    if (nim.length() < 3) {
        cout << "NIM harus terdiri dari minimal 3 digit!\n";
        return 1;
    }
    
    // Untuk NIM dengan angka terakhir 25
    // Jumlah awal = 25 (dua digit terakhir)
    int jumlahAwal = 25;
    
    // Posisi sisip = digit terakhir (5) + 1 = 6
    int posisiSisip = 6;
    
    cout << "Jumlah awal game: " << jumlahAwal << endl;
    cout << "Posisi sisip game: " << posisiSisip << endl;
    
    // Inisialisasi manajer inventory
    ManajerInventory inventory(jumlahAwal, posisiSisip);
    
    int pilihan;
    do {
        // Tampilkan menu
        cout << "\n" << string(60, '=') << endl;
        cout << "         MANAJEMEN INVENTORY GAME" << endl;
        cout << "      [ " << nama << " - " << nim << " ]" << endl;
        cout << string(60, '=') << endl;
        cout << "| 1. Tambah Game Baru                                 |" << endl;
        cout << "| 2. Sisipkan Game                                    |" << endl;
        cout << "| 3. Hapus Game Terakhir                              |" << endl;
        cout << "| 4. Gunakan Game                                     |" << endl;
        cout << "| 5. Tampilkan Inventory                              |" << endl;
        cout << "| 0. Keluar                                           |" << endl;
        cout << string(60, '=') << endl;
        
        cout << "Pilih menu (0-5): ";
        pilihan = dapatkanIntegerTervalidasi();
        
        switch (pilihan) {
            case 1: {
                cout << "\n--- Tambah Game Baru ---\n";
                string namaGame, genre;
                cout << "Masukkan nama game: ";
                getline(cin, namaGame);
                cout << "Masukkan genre game (RPG, FPS, Adventure, dll): ";
                getline(cin, genre);
                inventory.tambahGameBaru(namaGame, genre);
                break;
            }
            case 2: {
                cout << "\n--- Sisipkan Game (Posisi: " << posisiSisip << ") ---\n";
                string namaGame, genre;
                cout << "Masukkan nama game: ";
                getline(cin, namaGame);
                cout << "Masukkan genre game (RPG, FPS, Adventure, dll): ";
                getline(cin, genre);
                inventory.sisipkanGame(namaGame, genre);
                break;
            }
            case 3: {
                cout << "\n--- Hapus Game Terakhir ---\n";
                inventory.hapusGameTerakhir();
                break;
            }
            case 4: {
                cout << "\n--- Gunakan Game ---\n";
                
                // Tampilkan daftar game yang tersedia
                inventory.tampilkanGameUntukDipilih();
                
                // Beri opsi untuk memilih
                cout << "\nPilih cara penggunaan:\n";
                cout << "1. Pilih dari daftar (masukkan nomor)\n";
                cout << "2. Masukkan nama game secara manual\n";
                cout << "Pilihan: ";
                
                int cara;
                cara = dapatkanIntegerTervalidasi();
                
                if (cara == 1) {
                    // Gunakan berdasarkan pilihan nomor
                    cout << "Masukkan nomor game yang ingin digunakan: ";
                    int nomorGame;
                    nomorGame = dapatkanIntegerTervalidasi();
                    inventory.gunakanGameBerdasarkanPilihan(nomorGame);
                } else if (cara == 2) {
                    // Gunakan berdasarkan input nama
                    string namaGame;
                    cout << "Masukkan nama game yang ingin digunakan: ";
                    getline(cin, namaGame);
                    inventory.gunakanGame(namaGame);
                } else {
                    cout << "Pilihan tidak valid!\n";
                }
                break;
            }
            case 5: {
                cout << "\n--- Tampilkan Inventory ---\n";
                inventory.tampilkanInventory();
                break;
            }
            case 0: {
                cout << "Terima kasih telah mencoba bang, semoga seratus :D!\n";
                break;
            }
            default: {
                cout << "Pilihan tidak valid! Silakan pilih menu 0-5.\n";
                break;
            }
        }
        
        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
    } while (pilihan != 0);
    
    return 0;
}