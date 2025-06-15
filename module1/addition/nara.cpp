#include <iostream> 
#include <string> 

using namespace std;

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
        while (current != nullptr) {
            current->data->displayInfo();
            current = current->next;
        }
    }
};

class Toko {

};

class PegawaiToko : public Toko {
private:
    string  nama_pegawai,
            id_pegawai,
            jabatan_pegawai;

    int     gaji_pegawai;

public: 
    PegawaiToko(string nama, string id, string jabatan, int gaji) : 
        nama_pegawai(nama), 
        id_pegawai(id), 
        jabatan_pegawai(jabatan), 
        gaji_pegawai(gaji) {}

    void setNamaPegawai(string nama) {
        nama_pegawai = nama;
    }

    void setIdPegawai(string id) {
        id_pegawai = id;
    }

    void setJabatanPegawai(string jabatan) {
        jabatan_pegawai = jabatan;
    }

    string getNamaPegawai() {
        return nama_pegawai;
    }

    string getIdPegawai() {
        return id_pegawai;
    }

    string getJabatanPegawai() {
        return jabatan_pegawai;
    }
    
    virtual void displayInfo() {
        cout << "Nama Pegawai: " << nama_pegawai << endl
             << "ID Pegawai: " << id_pegawai << endl
             << "Jabatan Pegawai: " << jabatan_pegawai << endl;
    }
};

class Kasir : public PegawaiToko {
private: 
    string nomor_meja_kasir;
    int     total_penjualan;

public: 
    Kasir(string nama, string id, string jabatan, int gaji, string nomor_meja) : 
        PegawaiToko(nama, id, jabatan, gaji), 
        nomor_meja_kasir(nomor_meja), 
        total_penjualan(0) {}

    void setNomorMejaKasir(string nomor) {
        nomor_meja_kasir = nomor;
    }

    void setTotalPenjualan(int total) {
        total_penjualan = total;
    }

    string getNomorMejaKasir() {
        return nomor_meja_kasir;
    }

    int getTotalPenjualan() {
        return total_penjualan;
    }

    void displayInfo() override {
        PegawaiToko::displayInfo();
        cout << "Nomor Meja Kasir: " << nomor_meja_kasir << endl
             << "Total Penjualan: " << total_penjualan << endl;
    }

};

class PenjagaRak : public PegawaiToko {

};

class ProdukDisplay : public Toko {
private: 
    string  id_produk,
            nama_produk, 
            kategori_produk;
            
    double  harga_produk;
    int     stok_produk;

public:
    ProdukDisplay(string nama, string id, string kategori, double harga, int stok) : 
        nama_produk(nama), 
        id_produk(id), 
        kategori_produk(kategori), 
        harga_produk(harga), 
        stok_produk(stok) {}

    void setNamaProduk(string nama) {
        nama_produk = nama;
    }
    
    virtual void displayInfo () {
        cout << "ID: " << id_produk << endl
             << "Nama: " << nama_produk << endl
             << "Kategori: " << kategori_produk << endl
             << "Harga: " << harga_produk << endl
             << "Stok: " << stok_produk << endl;
    }

    string getNamaProduk() {
        return nama_produk;
    }

    string getIdProduk() {
        return id_produk;
    }

    string getKategoriProduk() {
        return kategori_produk;
    }

    int getHargaProduk() {
        return harga_produk;
    }

    int getStokProduk() {
        return stok_produk;
    }

    void setNamaProduk(string nama) {
        nama_produk = nama;
    }

    void setIdProduk(string id) {
        id_produk = id;
    }
    
    void setKategoriProduk(string kategori) {
        kategori_produk = kategori;
    }
    
    void setHargaProduk(double harga) {
        harga_produk = harga;
    }
    
    void setStokProduk(double stok) {
        stok_produk = stok;
    }

};

class Buku : public ProdukDisplay {
private:
    string  penulis_buku,
            genre_buku;

public:
    Buku(string id, string nama, string kategori, double harga, int stok, string penulis, string genre) : 
        ProdukDisplay(nama, id, kategori, harga, stok), 
        penulis_buku(penulis), 
        genre_buku(genre) {}

    void displayInfo() override {
        cout << "Buku Info:" << endl; 
        ProdukDisplay::displayInfo();
        cout << "Penulis: " << penulis_buku << endl
             << "Genre: " << genre_buku << endl;
    }
};

class Majalah : public ProdukDisplay {
private:
    string  penerbit_majalah,
            edisi_majalah;

public:
    Majalah(string id, string nama, string kategori, double harga, int stok, string penerbit, string edisi) : 
        ProdukDisplay(nama, id, kategori, harga, stok), 
        penerbit_majalah(penerbit), 
        edisi_majalah(edisi) {}

    void displayInfo() override {
        cout << "Majalah Info:" << endl;
        ProdukDisplay::displayInfo();
        cout << "Penerbit: " << penerbit_majalah << endl
             << "Edisi: " << edisi_majalah << endl
             << "Penerbit: " << penerbit_majalah << endl
             << "Edisi: " << edisi_majalah << endl;
    }
};

class Gudang : public Toko {

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
