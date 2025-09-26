#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Game {
    int id;
    string nama;
    string genre;
    int jumlah;
};

struct Node {
    Game data;
    Node *next;
    Node *prev;
};

Node *head = NULL;
Node *tail = NULL;
int panjangList = 0;
int autoID = 1;

// Utility: pause dan clear
void pause() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}
void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Insert First
void insertFirst() {
    Node *newNode = new Node();
    newNode->data.id = autoID++;
    cin.ignore();
    cout << "Nama Game : "; getline(cin, newNode->data.nama);
    cout << "Genre     : "; getline(cin, newNode->data.genre);
    cout << "Jumlah    : "; cin >> newNode->data.jumlah;

    newNode->prev = NULL;
    newNode->next = head;

    if (head == NULL && tail == NULL) {
        head = tail = newNode;
    } else {
        head->prev = newNode;
        head = newNode;
    }
    panjangList++;
    cout << "Game berhasil ditambahkan.\n";
    pause();
}

// Insert Last
void insertLast() {
    Node *newNode = new Node();
    newNode->data.id = autoID++;
    cin.ignore();
    cout << "Nama Game : "; getline(cin, newNode->data.nama);
    cout << "Genre     : "; getline(cin, newNode->data.genre);
    cout << "Jumlah    : "; cin >> newNode->data.jumlah;

    newNode->prev = tail;
    newNode->next = NULL;

    if (head == NULL && tail == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    panjangList++;
    cout << "Game berhasil ditambahkan.\n";
    pause();
}

// Insert At
void insertAt(int posisi) {
    if (posisi < 1 || posisi > panjangList + 1) {
        cout << "Posisi tidak valid!\n";
        pause();
        return;
    }
    if (posisi == 1) {
        insertFirst();
    } else if (posisi == panjangList + 1) {
        insertLast();
    } else {
        Node *newNode = new Node();
        newNode->data.id = autoID++;
        cin.ignore();
        cout << "Nama Game : "; getline(cin, newNode->data.nama);
        cout << "Genre     : "; getline(cin, newNode->data.genre);
        cout << "Jumlah    : "; cin >> newNode->data.jumlah;

        Node *temp = head;
        for (int i = 1; i < posisi - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;

        panjangList++;
        cout << "Game berhasil ditambahkan.\n";
        pause();
    }
}

// Delete First
void deleteFirst() {
    if (head == NULL && tail == NULL) {
        cout << "Inventory kosong.\n";
    } else if (head->next == NULL) {
        cout << "Game '" << head->data.nama << "' dihapus.\n";
        delete head;
        head = tail = NULL;
        panjangList--;
    } else {
        Node *del = head;
        cout << "Game '" << del->data.nama << "' dihapus.\n";
        head = head->next;
        head->prev = NULL;
        delete del;
        panjangList--;
    }
    pause();
}

// Delete Last
void deleteLast() {
    if (head == NULL && tail == NULL) {
        cout << "Inventory kosong.\n";
    } else if (head->next == NULL) {
        cout << "Game '" << head->data.nama << "' dihapus.\n";
        delete head;
        head = tail = NULL;
        panjangList--;
    } else {
        Node *del = tail;
        cout << "Game '" << del->data.nama << "' dihapus.\n";
        tail = tail->prev;
        tail->next = NULL;
        delete del;
        panjangList--;
    }
    pause();
}

// Delete At
void deleteAt(int posisi) {
    if (posisi < 1 || posisi > panjangList) {
        cout << "Posisi tidak valid!\n";
        pause();
        return;
    }
    if (posisi == 1) {
        deleteFirst();
    } else if (posisi == panjangList) {
        deleteLast();
    } else {
        Node *temp = head;
        for (int i = 1; i < posisi; i++) {
            temp = temp->next;
        }
        cout << "Game '" << temp->data.nama << "' dihapus.\n";
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        panjangList--;
        pause();
    }
}

// Print Forward
void printList() {
    if (head == NULL) {
        cout << ">> Inventory kosong <<\n";
        pause();
        return;
    }
    cout << "\nInventory (Depan -> Belakang):\n";
    Node *temp = head;
    while (temp != NULL) {
        cout << "ID: " << temp->data.id
             << " | Nama: " << temp->data.nama
             << " | Genre: " << temp->data.genre
             << " | Jumlah: " << temp->data.jumlah << endl;
        temp = temp->next;
    }
    pause();
}

// Print Reverse
void printReverse() {
    if (tail == NULL) {
        cout << ">> Inventory kosong <<\n";
        pause();
        return;
    }
    cout << "\nInventory (Belakang -> Depan):\n";
    Node *temp = tail;
    while (temp != NULL) {
        cout << "ID: " << temp->data.id
             << " | Nama: " << temp->data.nama
             << " | Genre: " << temp->data.genre
             << " | Jumlah: " << temp->data.jumlah << endl;
        temp = temp->prev;
    }
    pause();
}

// Cari Game
void cariGame(string keyword) {
    if (head == NULL) {
        cout << "Inventory kosong.\n";
        pause();
        return;
    }
    Node *temp = head;
    bool found = false;
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    while (temp != NULL) {
        string namaLower = temp->data.nama;
        transform(namaLower.begin(), namaLower.end(), namaLower.begin(), ::tolower);

        if (to_string(temp->data.id) == keyword || namaLower == keyword) {
            cout << "\n=== DETAIL GAME ===\n";
            cout << "ID    : " << temp->data.id << endl;
            cout << "Nama  : " << temp->data.nama << endl;
            cout << "Genre : " << temp->data.genre << endl;
            cout << "Jumlah: " << temp->data.jumlah << endl;
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (!found) cout << "Game tidak ditemukan.\n";
    pause();
}

// Main
int main() {
    int pilihan, posisi;
    string keyword;

    do {
        clear();
        cout << "=== MENU MANAJEMEN INVENTORY GAME ===\n";
        cout << "1. Tambah Game di Awal\n";
        cout << "2. Tambah Game di Akhir\n";
        cout << "3. Tambah Game di Posisi Tertentu\n";
        cout << "4. Hapus Game di Awal\n";
        cout << "5. Hapus Game di Akhir\n";
        cout << "6. Hapus Game di Posisi Tertentu\n";
        cout << "7. Tampilkan Inventory (Depan -> Belakang)\n";
        cout << "8. Tampilkan Inventory (Belakang -> Depan)\n";
        cout << "9. Cari Game (ID/Nama)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: insertFirst(); break;
            case 2: insertLast(); break;
            case 3: cout << "Posisi: "; cin >> posisi; insertAt(posisi); break;
            case 4: deleteFirst(); break;
            case 5: deleteLast(); break;
            case 6: cout << "Posisi: "; cin >> posisi; deleteAt(posisi); break;
            case 7: printList(); break;
            case 8: printReverse(); break;
            case 9: cout << "Masukkan ID atau Nama: "; cin.ignore(); getline(cin, keyword); cariGame(keyword); break;
            case 0: cout << "Program selesai, terima kasih telah mencoba bang :9.\n"; break;
            default: cout << "Pilihan tidak valid!\n"; pause();
        }
    } while (pilihan != 0);

    return 0;
}
