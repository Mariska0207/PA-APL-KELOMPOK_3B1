#ifndef GLOBAL_H
#define GLOBAL_H

bool login_admin = false;
bool login_user = false;

struct nama_pengguna{
    string username;
    string password;
    long int saldo;
};

struct Buah {
    string nama;
    long int harga;
    long int stok;
    string status;
};

struct topup{
    string username;
    long int jumlah;
    string status;
    string waktuDibuat;
};

struct transaksi{
    string pembeli;
    string barang;
    long int jumlahbeli;
    long int totalbayar;
    string waktuTransaksi;
};


#define MAX 100
Buah daftarBuah[MAX];
transaksi daftartran[MAX];
string username, password, namabuah;
int pilihan, totalbuah = 0, percobaanuser = 0, percobaanadmin = 0, jumlahpengguna = 1, totalTransaksi = 0, panjangmin = 3, panjangmax = 30;
int jumlahTopUp = 0; topup daftarTopUp[MAX];
bool balik_menu = false;

nama_pengguna pengguna[MAX] = {
    {"kicaw", "123", 100000}
};

#endif