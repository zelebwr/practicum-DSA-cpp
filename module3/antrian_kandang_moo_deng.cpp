#include <iostream>
#include <string>

// Gunakan namespace std sesuai permintaan
using namespace std;

// Node untuk merepresentasikan satu pengunjung dalam antrian
class PengunjungNode {
public:
    string nama;
    PengunjungNode* next;

    // Constructor untuk membuat node baru dengan nama tertentu
    PengunjungNode(string namaPengunjung) {
        nama = namaPengunjung;
        next = nullptr;
    }
};

// Kelas untuk mengelola seluruh logika antrian (Queue)
class Antrian {
private:
    PengunjungNode* kepala; // Pointer ke depan antrian (head)
    PengunjungNode* ekor;   // Pointer ke belakang antrian (tail)

public:
    // Constructor: Inisialisasi antrian kosong
    Antrian() {
        kepala = nullptr;
        ekor = nullptr;
    }

    // Destructor: Membersihkan semua node yang tersisa untuk mencegah memory leak
    ~Antrian() {
        while (kepala != nullptr) {
            PengunjungNode* temp = kepala;
            kepala = kepala->next;
            delete temp;
        }
    }

    // Fungsi untuk menambahkan pengunjung baru ke akhir antrian (enqueue)
    void datang(string nama) {
        PengunjungNode* pengunjungBaru = new PengunjungNode(nama);
        if (ekor == nullptr) { // Jika antrian kosong
            kepala = ekor = pengunjungBaru;
        } else { // Jika antrian sudah ada isinya
            ekor->next = pengunjungBaru;
            ekor = pengunjungBaru;
        }
        cout << "PENGUNJUNG " << nama << " MASUK ANTRIAN" << endl;
    }

    // Fungsi untuk memanggil/menghapus pengunjung dari depan antrian (dequeue)
    void panggil() {
        if (kepala == nullptr) { // Jika antrian kosong
            cout << "ANTRIAN KOSONG, TIDAK ADA YANG DIPANGGIL" << endl;
            return;
        }

        // Simpan node yang akan dihapus dan namanya
        PengunjungNode* temp = kepala;
        string namaDihapus = kepala->nama;

        // Majukan kepala ke node berikutnya
        kepala = kepala->next;

        // Jika setelah penghapusan antrian menjadi kosong, update juga ekor
        if (kepala == nullptr) {
            ekor = nullptr;
        }

        cout << "PENGUNJUNG " << namaDihapus << " DIPANGGIL MASUK" << endl;
        delete temp; // Hapus node dari memori
    }

    // Fungsi untuk menampilkan seluruh isi antrian
    void lihat() {
        cout << "Antrian Saat Ini: ";
        if (kepala == nullptr) {
            cout << "KOSONG" << endl;
        } else {
            cout << "[";
            PengunjungNode* current = kepala;
            while (current != nullptr) {
                cout << current->nama;
                if (current->next != nullptr) {
                    cout << ", ";
                }
                current = current->next;
            }
            cout << "]" << endl;
        }
    }
};

int main() {
    // Nonaktifkan sinkronisasi dengan stdio untuk I/O yang lebih cepat
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    cin >> Q;

    Antrian antrianPengunjung;
    string perintah, nama;

    for (int i = 0; i < Q; ++i) {
        cin >> perintah;
        if (perintah == "DATANG") {
            cin >> nama;
            antrianPengunjung.datang(nama);
        } else if (perintah == "PANGGIL") {
            antrianPengunjung.panggil();
        } else if (perintah == "LIHAT") {
            antrianPengunjung.lihat();
        }
    }

    return 0;
}
