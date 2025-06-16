#include <iostream>

// Gunakan namespace std sesuai permintaan
using namespace std;

// Struktur sederhana untuk menyimpan koordinat
struct Point {
    int r, c;
};

// Node untuk custom queue yang akan kita gunakan dalam BFS
class QueueNode {
public:
    Point data;
    QueueNode* next;

    QueueNode(Point p) {
        data = p;
        next = nullptr;
    }
};

// Implementasi Queue sederhana menggunakan linked list
class CustomQueue {
private:
    QueueNode* _front;
    QueueNode* _tail;

public:
    CustomQueue() : _front(nullptr), _tail(nullptr) {}

    ~CustomQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() {
        return _front == nullptr;
    }

    void enqueue(Point p) {
        QueueNode* newNode = new QueueNode(p);
        if (isEmpty()) {
            _front = _tail = newNode;
        } else {
            _tail->next = newNode;
            _tail = newNode;
        }
    }

    Point dequeue() {
        if (isEmpty()) {
            // Seharusnya tidak terjadi dalam logika BFS kita
            return {-1, -1};
        }
        QueueNode* temp = _front;
        Point p = temp->data;
        _front = _front->next;
        if (_front == nullptr) {
            _tail = nullptr;
        }
        delete temp;
        return p;
    }
};


// Kelas utama untuk menyelesaikan masalah
class MapSolver {
private:
    int _P, _Q;
    char** _map;          // Untuk menyimpan peta
    int** _region_id;     // Untuk menyimpan ID area dari setiap sel
    int* _region_pieces;  // Untuk menyimpan jumlah map piece per area
    int _region_count;    // Jumlah total area yang ditemukan

public:
    // Constructor: Mengalokasikan memori untuk semua array
    MapSolver(int p, int q) {
        _P = p;
        _Q = q;
        _region_count = 0;

        // Alokasi memori untuk peta (1-based index)
        _map = new char*[_P + 1];
        for (int i = 0; i <= _P; ++i) {
            _map[i] = new char[_Q + 1];
        }

        // Alokasi memori untuk ID area, inisialisasi dengan 0 (belum dikunjungi)
        _region_id = new int*[_P + 1];
        for (int i = 0; i <= _P; ++i) {
            _region_id[i] = new int[_Q + 1]();
        }

        // Alokasi memori untuk hasil per area (ukuran maksimum P*Q/2 + 1)
        _region_pieces = new int[(_P * _Q / 2) + 2]();
    }

    // Destructor: Membersihkan semua memori yang dialokasikan
    ~MapSolver() {
        for (int i = 0; i <= _P; ++i) {
            delete[] _map[i];
            delete[] _region_id[i];
        }
        delete[] _map;
        delete[] _region_id;
        delete[] _region_pieces;
    }

    // Membaca peta dari input
    void readMap() {
        for (int i = 1; i <= _P; ++i) {
            for (int j = 1; j <= _Q; ++j) {
                cin >> _map[i][j];
            }
        }
    }

    // Fungsi utama untuk pra-komputasi
    void precomputeRegions() {
        for (int i = 1; i <= _P; ++i) {
            for (int j = 1; j <= _Q; ++j) {
                // Jika menemukan sel jalan yang belum menjadi bagian dari area manapun
                if (_map[i][j] == '.' && _region_id[i][j] == 0) {
                    _region_count++; // Kita menemukan area baru
                    bfs(i, j, _region_count);
                }
            }
        }
    }

    // Mengambil hasil yang sudah dihitung untuk sebuah titik start
    int getPieces(int r, int c) {
        int id = _region_id[r][c];
        return _region_pieces[id];
    }

private:
    // Breadth-First Search untuk menjelajahi satu area dan menghitung map piece
    void bfs(int start_r, int start_c, int current_region_id) {
        CustomQueue q;
        int current_piece_count = 0;

        // Mulai BFS dari titik start
        q.enqueue({start_r, start_c});
        _region_id[start_r][start_c] = current_region_id;

        // Arah gerak: atas, kanan, bawah, kiri
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        while (!q.isEmpty()) {
            Point current = q.dequeue();

            // Cek 4 tetangga untuk menghitung map piece dan melanjutkan penjelajahan
            for (int i = 0; i < 4; ++i) {
                int nr = current.r + dr[i];
                int nc = current.c + dc[i];

                // Pengecekan batas tidak diperlukan karena soal menjamin border adalah '#'
                
                // Jika tetangga adalah dinding, itu adalah satu map piece
                if (_map[nr][nc] == '#') {
                    current_piece_count++;
                }
                // Jika tetangga adalah jalan yang belum dikunjungi
                else if (_map[nr][nc] == '.' && _region_id[nr][nc] == 0) {
                    _region_id[nr][nc] = current_region_id; // Tandai sebagai dikunjungi
                    q.enqueue({nr, nc}); // Masukkan ke antrian untuk dijelajahi
                }
            }
        }

        // Simpan total map piece untuk area ini
        _region_pieces[current_region_id] = current_piece_count;
    }
};

int main() {
    // Nonaktifkan sinkronisasi dengan stdio untuk I/O yang lebih cepat
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int P, Q, N;
    cin >> P >> Q >> N;

    MapSolver solver(P, Q);
    solver.readMap();
    solver.precomputeRegions();

    for (int i = 0; i < N; ++i) {
        int sr, sc;
        cin >> sr >> sc;
        cout << solver.getPieces(sr, sc) << endl;
    }

    return 0;
}
