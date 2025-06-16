#include <iostream>
#include <string>

// Gunakan namespace std sesuai permintaan
using namespace std;

// class untuk node peristiwa
class Timenode {
public:
    int data;
    Timenode* next;

    // Constructor untuk inisialisasi node
    Timenode(int value) {
        data = value;
        next = nullptr;
    }
};

// class untuk mengatur linimasa circular
class TimeCircularList {
private:
    Timenode* _head;
    Timenode* _tail; // Pointer ke ekor untuk efisiensi
    int _size;

public:
    TimeCircularList() : _head(nullptr), _tail(nullptr), _size(0) {}

    // Destructor untuk membersihkan semua node secara manual dan hening.
    // Ini adalah revisi untuk memastikan tidak ada output yang tidak diinginkan
    // yang tercetak saat objek dihancurkan.
    ~TimeCircularList() {
        if (!isEmpty()) {
            Timenode* current = _head->next;
            while (current != _head) {
                Timenode* temp = current;
                current = current->next;
                delete temp;
            }
            // Hapus node kepala yang tersisa
            delete _head;
        }
    }

    bool isEmpty() {
        return _size == 0;
    }

    // Menambahkan node di belakang
    void tambahBelakang(int value) {
        Timenode* newNode = new Timenode(value);
        if (isEmpty()) {
            _head = newNode;
            _tail = newNode;
            newNode->next = newNode; // Menunjuk ke dirinya sendiri
        } else {
            _tail->next = newNode;   // Ekor lama menunjuk ke node baru
            newNode->next = _head;   // Node baru menunjuk ke kepala
            _tail = newNode;         // Update ekor menjadi node baru
        }
        _size++;
    }

    // Menghapus node di depan
    void hapusDepan() {
        if (isEmpty()) {
            cout << "Operasi gagal" << endl;
            return;
        }

        Timenode* temp = _head;
        if (_size == 1) {
            _head = nullptr;
            _tail = nullptr;
        } else {
            _head = _head->next;   // Kepala baru adalah node setelahnya
            _tail->next = _head;   // Ekor menunjuk ke kepala yang baru
        }

        delete temp; // Hapus kepala lama dari memori
        _size--;
    }

    // Memutar list satu langkah
    void putar() {
        if (isEmpty() || _size == 1) { // Menambahkan cek _size == 1 untuk efisiensi
            if(isEmpty()) cout << "Operasi gagal" << endl;
            return;
        }
        // Cukup geser pointer kepala dan ekor satu langkah
        _head = _head->next;
        _tail = _tail->next;
    }

    // Mencetak seluruh isi list
    void tampilkan() {
        if (isEmpty()) {
            // Sesuai contoh, tidak ada output jika kosong.
            return;
        }

        Timenode* current = _head;
        do {
            cout << current->data;
            current = current->next;
            if (current != _head) {
                cout << " ";
            }
        } while (current != _head);
        cout << endl;
    }
};

int main() {
    // Nonaktifkan sinkronisasi dengan stdio untuk I/O yang lebih cepat
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    TimeCircularList linimasa;
    string perintah;

    while (cin >> perintah) {
        if (perintah == "TAMBAH_BELAKANG") {
            int nilai;
            cin >> nilai;
            linimasa.tambahBelakang(nilai);
        } else if (perintah == "HAPUS_DEPAN") {
            linimasa.hapusDepan();
        } else if (perintah == "PUTAR") {
            linimasa.putar();
        } else if (perintah == "TAMPILKAN") {
            linimasa.tampilkan();
        }
    }

    return 0;
}
