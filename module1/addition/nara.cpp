#include <iostream> 
#include <string> 

using namespace std;


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
        while (current != nullptr) {
            current->data->displayInfo();
            cout << "------------------------" << endl;
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

class Gudang{

};
template <typename T>
struct Node {
    T* data;
    Node* next;
    Node(T* data) : data(data), next(nullptr) {}
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
