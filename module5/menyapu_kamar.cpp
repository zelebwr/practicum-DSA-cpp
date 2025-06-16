#include <iostream>

// Gunakan namespace std sesuai permintaan
using namespace std;

// Node untuk merepresentasikan satu sampah.
// Terhubung dengan tetangga di baris dan kolom yang sama.
// Setiap node juga menyimpan koordinatnya sendiri untuk mempermudah
// proses pelepasan dari list di dimensi lain.
class SampahNode {
public:
    int r, c; // Menyimpan koordinat baris (r) dan kolom (c)
    // Pointer untuk list pada baris yang sama
    SampahNode* next_row;
    SampahNode* prev_row;
    // Pointer untuk list pada kolom yang sama
    SampahNode* next_col;
    SampahNode* prev_col;

    SampahNode(int row, int col) {
        r = row;
        c = col;
        next_row = nullptr;
        prev_row = nullptr;
        next_col = nullptr;
        prev_col = nullptr;
    }
};

// Class untuk mengelola seluruh grid dan operasinya
class Grid {
private:
    int max_h, max_w;
    // Array of pointers yang menjadi 'kepala' dari setiap
    // linked list baris dan kolom.
    SampahNode** heads_row;
    SampahNode** heads_col;
    // Array of pointers tambahan untuk 'ekor' agar penambahan O(1)
    SampahNode** tails_row;
    SampahNode** tails_col;


public:
    // Constructor: alokasi memori untuk array kepala dan ekor list
    Grid(int h, int w) {
        max_h = h;
        max_w = w;
        // Alokasi H+1 dan W+1 untuk mengakomodasi indeks 1-based.
        // Inisialisasi dengan `()` memastikan semua pointer awalnya nullptr.
        heads_row = new SampahNode*[h + 1]();
        heads_col = new SampahNode*[w + 1]();
        tails_row = new SampahNode*[h + 1]();
        tails_col = new SampahNode*[w + 1]();
    }

    // Destructor: membersihkan sisa sampah yang ada
    ~Grid() {
        // Cukup membersihkan dari satu arah (misal, baris).
        // Iterasi dari 1 sampai max_h karena menggunakan 1-based indexing.
        for (int i = 1; i <= max_h; ++i) {
            SampahNode* current = heads_row[i];
            while (current != nullptr) {
                SampahNode* nodeToDelete = current;
                current = current->next_row;
                // Tidak perlu melepaskan dari list kolom karena seluruh grid
                // sedang dihapus.
                delete nodeToDelete;
            }
        }
        delete[] heads_row;
        delete[] heads_col;
        delete[] tails_row;
        delete[] tails_col;
    }

    // Fungsi untuk menambahkan sampah baru ke grid (O(1) time)
    void tambahSampah(int r, int c) {
        SampahNode* newNode = new SampahNode(r, c);

        // 1. Sambungkan ke linked list baris
        if (heads_row[r] == nullptr) {
            heads_row[r] = newNode;
            tails_row[r] = newNode;
        } else {
            tails_row[r]->next_row = newNode;
            newNode->prev_row = tails_row[r];
            tails_row[r] = newNode;
        }

        // 2. Sambungkan ke linked list kolom
        if (heads_col[c] == nullptr) {
            heads_col[c] = newNode;
            tails_col[c] = newNode;
        } else {
            tails_col[c]->next_col = newNode;
            newNode->prev_col = tails_col[c];
            tails_col[c] = newNode;
        }
    }

    // Fungsi untuk memproses query
    void prosesQuery(int tipe, int index) {
        if (tipe == 1) { // Query Tipe 1: Baris
            int count = 0;
            SampahNode* current = heads_row[index];
            
            // Telusuri semua sampah di baris ini
            while (current != nullptr) {
                count++;
                
                // Lepaskan node ini dari linked list kolomnya
                if (current->prev_col != nullptr) {
                    current->prev_col->next_col = current->next_col;
                } else {
                    // Jika node ini adalah head di list kolomnya, update head kolom
                    heads_col[current->c] = current->next_col;
                }
                
                if (current->next_col != nullptr) {
                    current->next_col->prev_col = current->prev_col;
                } else {
                    // Jika node ini adalah tail di list kolomnya, update tail kolom
                    tails_col[current->c] = current->prev_col;
                }

                SampahNode* nodeToDelete = current;
                current = current->next_row;
                delete nodeToDelete; // Hapus sampah
            }
            
            cout << count << endl;
            heads_row[index] = nullptr; // Baris ini sekarang kosong
            tails_row[index] = nullptr;

        } else { // Query Tipe 2: Kolom
            int count = 0;
            SampahNode* current = heads_col[index];

            // Telusuri semua sampah di kolom ini
            while (current != nullptr) {
                count++;
                
                // Lepaskan node ini dari linked list barisnya
                if (current->prev_row != nullptr) {
                    current->prev_row->next_row = current->next_row;
                } else {
                    // Jika node ini adalah head di list barisnya, update head baris
                    heads_row[current->r] = current->next_row;
                }
                
                if (current->next_row != nullptr) {
                    current->next_row->prev_row = current->prev_row;
                } else {
                    // Jika node ini adalah tail di list barisnya, update tail baris
                    tails_row[current->r] = current->prev_row;
                }

                SampahNode* nodeToDelete = current;
                current = current->next_col;
                delete nodeToDelete; // Hapus sampah
            }
            cout << count << endl;
            heads_col[index] = nullptr; // Kolom ini sekarang kosong
            tails_col[index] = nullptr;
        }
    }
};


int main() {
    // Nonaktifkan sinkronisasi dengan stdio untuk I/O yang lebih cepat
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int H, W, N;
    cin >> H >> W >> N;

    Grid kamar(H, W);

    for (int i = 0; i < N; ++i) {
        int r, c;
        cin >> r >> c;
        kamar.tambahSampah(r, c);
    }

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; ++i) {
        int tipe, index;
        cin >> tipe >> index;
        kamar.prosesQuery(tipe, index);
    }

    return 0;
}
