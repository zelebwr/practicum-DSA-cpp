#include <iostream>
#include <string>

// Gunakan namespace std sesuai permintaan
using namespace std;

// Node untuk merepresentasikan satu 'note' dalam chart.
// Ini adalah node untuk doubly linked list.
class NoteNode {
public:
    int value;
    NoteNode *next;
    NoteNode *prev;

    NoteNode(int val) {
        value = val;
        next = nullptr;
        prev = nullptr;
    }
};

// Kelas untuk mengelola chart, diimplementasikan sebagai Deque (Doubly-Ended Queue)
// menggunakan doubly linked list.
class ChartDeque {
private:
    NoteNode *_head;
    NoteNode *_tail;
    int _size;

public:
    // Constructor: Inisialisasi deque kosong
    ChartDeque() {
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    }

    // Destructor: Membersihkan semua node untuk mencegah memory leak
    ~ChartDeque() {
        while (!isEmpty()) {
            popFront();
        }
    }

    // Cek apakah chart kosong
    bool isEmpty() const {
        return _size == 0;
    }
    
    // -- OPERASI PUSH --

    // slidestart: Tambah note di awal (front)
    void pushFront(int value) {
        NoteNode *newNode = new NoteNode(value);
        if (isEmpty()) {
            _head = _tail = newNode;
        } else {
            newNode->next = _head;
            _head->prev = newNode;
            _head = newNode;
        }
        _size++;
    }

    // slideend: Tambah note di akhir (back)
    void pushBack(int value) {
        NoteNode *newNode = new NoteNode(value);
        if (isEmpty()) {
            _head = _tail = newNode;
        } else {
            _tail->next = newNode;
            newNode->prev = _tail;
            _tail = newNode;
        }
        _size++;
    }

    // slidecenter: Tambah note di tengah
    void pushMid(int value) {
        if (_size < 2) {
            pushBack(value);
            return;
        }
        // Temukan posisi tengah (1-based index) sesuai formula
        int mid_pos = (_size % 2 == 0) ? (_size / 2) : ((_size + 1) / 2);
        NoteNode *current = _head;
        for (int i = 1; i < mid_pos; ++i) {
            current = current->next;
        }

        NoteNode *newNode = new NoteNode(value);
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != nullptr) {
            current->next->prev = newNode;
        }
        current->next = newNode;
        
        // Jika 'current' adalah tail, maka node baru menjadi tail
        if(current == _tail) {
            _tail = newNode;
        }
        _size++;
    }
    
    // -- OPERASI POP --

    // tap: Hapus note dari awal (front)
    void popFront() {
        if (isEmpty()) return;

        NoteNode *temp = _head;
        _head = _head->next;
        if (_head != nullptr) {
            _head->prev = nullptr;
        } else {
            _tail = nullptr; // List menjadi kosong
        }
        delete temp;
        _size--;
    }

    // hold: Hapus note dari akhir (back)
    void popBack() {
        if (isEmpty()) return;

        NoteNode *temp = _tail;
        _tail = _tail->prev;
        if (_tail != nullptr) {
            _tail->next = nullptr;
        } else {
            _head = nullptr; // List menjadi kosong
        }
        delete temp;
        _size--;
    }

    // touch: Hapus note dari tengah
    void popMid() {
        if (isEmpty()) return;
        if (_size <= 2) { // Hapus dari depan jika hanya ada 1 atau 2 note
            popFront();
            return;
        }
        // Temukan posisi tengah (1-based index) sesuai formula
        int mid_pos = (_size % 2 == 0) ? (_size / 2) : ((_size + 1) / 2);
        NoteNode *nodeToDelete = _head;
        for (int i = 1; i < mid_pos; ++i) {
            nodeToDelete = nodeToDelete->next;
        }

        // Unlink node dari list
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;
        
        delete nodeToDelete;
        _size--;
    }

    // chart: Tampilkan semua note
    void display() const {
        if (isEmpty()) {
            cout << "no notes exist, create some maybe" << endl;
            return;
        }
        cout << "Chart view - ";
        NoteNode *current = _head;
        while (current != nullptr) {
            cout << current->value;
            if (current->next != nullptr) {
                cout << ",";
            }
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    // Nonaktifkan sinkronisasi dengan stdio untuk I/O yang lebih cepat
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ChartDeque chart;
    string command;

    while (cin >> command && command != "break") {
        if (command == "chart") {
            chart.display();
        } 
        else if (command == "slidestart" || command == "slidecenter" || command == "slideend") {
            int n;
            cin >> n;
            for (int i = 0; i < n; ++i) {
                int val;
                cin >> val;
                if (command == "slidestart") chart.pushFront(val);
                else if (command == "slidecenter") chart.pushMid(val);
                else chart.pushBack(val);
            }
        } 
        else if (command == "tap" || command == "touch" || command == "hold") {
            int n;
            cin >> n;
            for (int i = 0; i < n; ++i) {
                if (chart.isEmpty()) {
                    cout << "no notes exist, create some maybe" << endl;
                    break; 
                }
                if (command == "tap") chart.popFront();
                else if (command == "touch") chart.popMid();
                else chart.popBack();
            }
        }
        else {
            cout << "what's that? try adding breaks" << endl;
            // Membersihkan sisa baris input yang tidak valid
            string dummy;
            getline(cin, dummy);
        }
    }

    return 0;
}
