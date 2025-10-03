#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

/*
 * Fungsi ini menerima referensi ke pointer head.
 * Pointer head akan di-update setelah penukaran.
 */
void exchangeHeadAndTail(Node *&head_ref) {
    // Hanya berjalan jika ada 2 node atau lebih
    if (head_ref == nullptr || head_ref->next == head_ref) {
        return;
    }

    // Kasus khusus untuk 2 node, cukup update head_ref
    // Logika di bawah ini juga menangani kasus ini, tetapi ini lebih efisien.
    if (head_ref->next->next == head_ref) {
        head_ref = head_ref->next;
        return;
    }

    // Simpan node-node penting
    Node* head = head_ref;
    Node* tail = head_ref->prev;
    Node* head_next = head->next;
    Node* tail_prev = tail->prev;

    // 1. Sambungkan tail ke lingkungan head yang lama
    tail->next = head_next;
    head_next->prev = tail;

    // 2. Sambungkan head ke lingkungan tail yang lama
    head->prev = tail_prev;
    tail_prev->next = head;

    // 3. Sambungkan head dan tail satu sama lain di posisi baru mereka
    head->next = tail;
    tail->prev = head;

    // 4. Update head_ref menjadi tail yang lama
    head_ref = tail;
}

void printList(Node *head_ref) {
    if (head_ref == nullptr) {
        cout << "List kosong" << endl;
        return;
    }

    Node *current = head_ref;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

void insertEnd(Node *&head_ref, int data) {
    Node *newNode = new Node{data, nullptr, nullptr};

    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    Node *tail = head_ref->prev;
    newNode->next = head_ref;
    newNode->prev = tail;
    head_ref->prev = newNode;
    tail->next = newNode;
}

int main() {
    Node *head = nullptr;

    // Buat list: 1 <-> 2 <-> 3 <-> 4 <-> 5
    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);

    cout << "List sebelum exchange: ";
    printList(head);

    exchangeHeadAndTail(head);

    cout << "List setelah exchange head dan tail: ";
    printList(head); // Expected output: 5 2 3 4 1

    return 0;
}