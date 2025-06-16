#include <iostream> 
#include <string> 

using namespace std;

class PegawaiToko;
class ProdukDisplay;
class Gudang;

template <typename T>
struct Node {
    T* data;
    Node* next;
    Node(T* data) : data(data), next(nullptr) {}
};

template <typename T>
class LinkedList {
    private:
    Node<T>* head;
    
    public: 
    LinkedList() : head(nullptr) {}
    
    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current->data; 
            delete current;
            current = next;
        }
    }
    
    // add new node to end of list
    void add(T* data) {
        Node<T>* newNode = new Node<T>(data);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    
    // display all nodes in the list
    void display() {
        Node<T>* current = head;
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        Node<T>* current = head;
        int count = 1;
        while (current != nullptr) {
            cout << "--- Item " << count++ << " ---" << endl;
            current->data->displayInfo();
            current = current->next;
        }
    }
    
    // find node by ID
    T* find(const string& id) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data->getIdProduk() == id) {
                return current->data;
            }
            current = current->next;
        }
        return nullptr; 
    }
    
    // remove node by ID
    bool remove(const string& id) {
        Node<T>* current = head;
        Node<T>* previous = nullptr;
        
        while (current != nullptr && current->data->getIdProduk() != id) {
            previous = current;
            current = current->next;
        }
        
        if (current == nullptr) {
            return false; // ID not found
        }
        
        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }
        
        delete current->data;
        delete current; 
        return true;
    }
};

class Toko {
    public: 
    virtual ~Toko() {} // destructor for proper cleanup in inheritance
};

class PegawaiToko : public Toko {
protected:
    string nama_pegawai,
           id_pegawai,
           jabatan_pegawai;
    int gaji_pegawai;

public: 
    PegawaiToko(string nama, string id, string jabatan, int gaji) : 
        nama_pegawai(nama), 
        id_pegawai(id), 
        jabatan_pegawai(jabatan), 
        gaji_pegawai(gaji) {}

    void setNamaPegawai(string nama) { nama_pegawai = nama; }
    void setJabatanPegawai(string jabatan) { jabatan_pegawai = jabatan; }
    string getNamaPegawai() { return nama_pegawai; }
    string getIdPegawai() { return id_pegawai; }
    string getJabatanPegawai() { return jabatan_pegawai; }
    int getGajiPegawai() { return gaji_pegawai; }
    void setGajiPegawai(int gaji) { gaji_pegawai = gaji; }

    virtual void displayInfo() {
        cout << "ID Pegawai\t: " << id_pegawai << endl
        << "Nama\t\t: " << nama_pegawai << endl
        << "Jabatan\t: " << jabatan_pegawai << endl
        << "Gaji\t\t: " << gaji_pegawai << endl;
    }
};

class ProdukDisplay : public Toko {
protected: 
    string id_produk,
           nama_produk,
           kategori_produk;        
    double harga_produk;
    int stok_produk;

public:
    ProdukDisplay(string nama, string id, string kategori, double harga, int stok) : 
        nama_produk(nama), 
        id_produk(id), 
        kategori_produk(kategori), 
        harga_produk(harga), 
        stok_produk(stok) {}

    string getIdProduk() { return id_produk; }
    string getNamaProduk() { return nama_produk; }
    int getStokProduk() { return stok_produk; }
    void setStokProduk(int stok) { stok_produk = stok; }

    virtual void displayInfo() {
        cout << "ID Produk\t: " << id_produk << endl
             << "Nama\t\t: " << nama_produk << endl
             << "Kategori\t: " << kategori_produk << endl
             << "Harga\t\t: " << harga_produk << endl
             << "Stok\t\t: " << stok_produk << endl;
    }
};

class Kasir : public PegawaiToko {
public: 
    Kasir(string nama, string id, int gaji) : 
        PegawaiToko(nama, id, "Kasir", gaji) {}
};

class PenjagaRak : public PegawaiToko {
public:
    PenjagaRak(string nama, string id, int gaji) :
        PegawaiToko(nama, id, "Penjaga Rak", gaji) {}
};

class ManajerGudang : public PegawaiToko {
public:
    ManajerGudang(string nama, string id, int gaji) :
        PegawaiToko(nama, id, "Manajer Gudang", gaji) {}
};

class Distributor : public PegawaiToko {
public:
    Distributor(string nama, string id, int gaji) :
        PegawaiToko(nama, id, "Distributor", gaji) {}
};

class Gudang{
private: 
    LinkedList<ProdukDisplay> daftar_produk;
    LinkedList<PegawaiToko> daftar_pegawai;

public:
    Gudang() {
        daftar_produk.add(new Buku("B001", "C++ Programming", 150000, 10, "Bjarne Stroustrup", "Programming"));
        daftar_produk.add(new Majalah("M001", "Tech Monthly", 50000, 20, "January 2023"));
        daftar_pegawai.add(new Kasir("Alice", "K001", 5000000, "11"));
        daftar_pegawai.add(new PenjagaRak("Bob", "P001", 4000000, "A1"));
    }

    void clearInput() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    }

    void tambahProdukBaru(){
        int type; 
        cout << "\nPilih tipe produk (1: Buku; 2: Majalah): "; 
        cin >> type;
        clearInput(); // clear the input buffer after reading type

        string id, nama; 
        double harga; 
        int stok; 

        cout << "ID Produk: "; getline(cin, id);
        cout << "Nama Produk: "; getline(cin, nama);
        cout << "Harga Produk: "; cin >> harga;
        cout << "Stok Produk: "; cin >> stok;
        clearInput(); // clear the input buffer after reading stok

        if (type == 1) {
            string penulis, genre;
            cout << "Penulis Buku: "; getline(cin, penulis);
            cout << "Genre Buku: "; getline(cin, genre);
            daftar_produk.add(new Buku(id, nama, harga, stok, penulis, genre));
        } else if (type == 2) {
            string edisi;
            cout << "Edisi Majalah: "; getline(cin, edisi);
            daftar_produk.add(new Majalah(id, nama, harga, stok, edisi));
        } else {
            cout << "Tipe produk tidak valid." << endl;
            return;
        }
        cout << "Produk berhasil ditambahkan." << endl;
    }

    void lihatDaftarProduk() {
        cout << "\n--- Menampilkan Semua Produk di Gudang ---" << endl;
        daftar_produk.display();
    }

    void tambahPegawaiBaru() {
        string nama, id, jabatan;
        int gaji;

        cout << "\nNama Pegawai: "; getline(cin, nama);
        cout << "ID Pegawai: "; getline(cin, id);
        cout << "Jabatan Pegawai: "; getline(cin, jabatan);
        cout << "Gaji Pegawai: "; cin >> gaji;
        clearInput(); // clear the input buffer after reading gaji

        if (jabatan == "Kasir") {
            string nomor_meja;
            cout << "Nomor Meja Kasir: "; getline(cin, nomor_meja);
            daftar_pegawai.add(new Kasir(nama, id, gaji, nomor_meja));
        } else if (jabatan == "Penjaga Rak") {
            string area_tugas;
            cout << "Area Tugas Penjaga Rak: "; getline(cin, area_tugas);
            daftar_pegawai.add(new PenjagaRak(nama, id, gaji, area_tugas));
        } else if (jabatan == "Manajer Gudang") {
            daftar_pegawai.add(new ManajerGudang(nama, id, gaji));
    }

    void lihatDaftarPegawai() {
        cout << "\n--- Menampilkan Semua Pegawai Toko ---" << endl;
        daftar_pegawai.display();
    }
};

class Kasir : public PegawaiToko {
    private: 
    string nomor_meja_kasir;
    
    public: 
    Kasir(string nama, string id, int gaji, string nomor_meja) : 
        PegawaiToko(nama, id, "Kasir", gaji), 
        nomor_meja_kasir(nomor_meja) {}

    void displayInfo() override {
        PegawaiToko::displayInfo();
        cout << "Nomor Meja Kasir: " << nomor_meja_kasir << endl;
    }
};

class PenjagaRak : public PegawaiToko {
private: 
    string area_tugas; 

public: 
    PenjagaRak(string nama, string id, int gaji, string area) : 
        PegawaiToko(nama, id, "Penjaga Rak", gaji), 
        area_tugas(area) {}

    void displayInfo() override {
        PegawaiToko::displayInfo();
        cout << "Area Tugas\t: " << area_tugas << endl;
    }
};


class Buku : public ProdukDisplay {
private:
    string penulis_buku,
           genre_buku;

public:
    Buku(string id, string nama, double harga, int stok, string penulis, string genre) : 
        ProdukDisplay(nama, id, "Buku", harga, stok), 
        penulis_buku(penulis), 
        genre_buku(genre) {}

    void displayInfo() override {
        ProdukDisplay::displayInfo();
        cout << "Penulis\t: " << penulis_buku << endl
             << "Genre\t\t: " << genre_buku << endl;
    }
};

class Majalah : public ProdukDisplay {
private:
    string edisi_majalah;

public:
    Majalah(string id, string nama, double harga, int stok, string edisi) : 
        ProdukDisplay(nama, id, "Majalah", harga, stok), 
        edisi_majalah(edisi) {}

    void displayInfo() override {
        ProdukDisplay::displayInfo();
        cout << "Edisi\t\t: " << edisi_majalah << endl;
    }
};


class ManajerGudang : public PegawaiToko {

};

class Distributor : public PegawaiToko {

};


int main () {
    LinkedList<Buku> daftarBuku; 
    LinkedList<Kasir> daftarKasir;
    LinkedList<Majalah> daftarMajalah;

    int option = 0; 
    while (true) {
        cout << "\nBook Store Management System" << endl
             << "1. Check Book List" << endl
             << "2. Add Book" << endl
             << "3. Check Magazine List" << endl
             << "4. Add Magazine" << endl
             << "5. Exit" << endl
             << "Select an option: ";
        cin >> option;

        switch (option) {
            case 1:
                // Check Book List
                break;
            case 2:
                // Add Book
                break;
            case 3:
                // Check Magazine List
                break;
            case 4:
                // Add Magazine
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
}
