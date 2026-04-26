#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <limits>
using namespace std;

bool login_admin = false;
bool login_user = false;

struct nama_pengguna{
    string username;
    string password;
    int saldo;
};

struct Buah {
    string nama;
    int harga;
    int stok;
    string status;
};

struct topup{
    string username;
    int jumlah;
    string status;
};

#define MAX 100
Buah daftarBuah[MAX];
string username, password;
int pilihan, totalbuah = 0, percobaan = 0, jumlahpengguna = 1;
int jumlahTopUp = 0; topup daftarTopUp[MAX];

nama_pengguna pengguna[MAX] = {
    {"kicaw", "123", 100000}
};

void takvalid(){
    cout << "!!! pilihan tidak valid !!!" << endl;
    system("pause");
}

void judulpnjng(string judul){
    cout << "=========================================================" << endl;
    cout << setw(35) << judul << setw(30) << endl;
    cout << "=========================================================\n";
}

bool cek_username(string username, int index){
    if(index >= jumlahpengguna){
        return false;
    }
    if(username == pengguna[index].username){
        return true;
    }
    return cek_username(username, index + 1);
}

void registrasi(){
    cout << "=============================" << endl;
    cout << "           REGISTER" << endl;
    cout << "=============================" << endl;
    if (jumlahpengguna < MAX){
        cout << "masukkan username : ";
        cin >> username;
        cout << "masukkan password : ";
        cin >> password;
        if(cek_username(username, 0)){
            cout << "!!! username sudah ada !!!" << endl;
            system("pause");
            return;
        }
        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
        cout << "  REGISTRASI ANDA BERHASIL" << endl;
        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
        pengguna[jumlahpengguna].username = username;
        pengguna[jumlahpengguna].password = password;
        jumlahpengguna++;
        system("pause");
    }else{
        cout << "!!! daftar pengguna penuh !!!" << endl;
    }
}

bool admin_login(string &username, string &password){
    cout << "=============================" << endl;
    cout << "           ADMIN" << endl;
    cout << "=============================" << endl;
    cout << "MASUKKAN USERNAME : ";
    cin >> username;
    cout << "MASUKKAN PASSWORD : ";
    cin >> password;
    if(username == "admin" && password == "123"){
        return true;
    }
    return false;
}

bool login_pengguna(string &username, string &password){
    cout << "=============================" << endl;
    cout << "       PENGGUNA BIASA" << endl;
    cout << "=============================" << endl;
    cout << "MASUKKAN USERNAME : ";
    cin >> username;
    cout << "MASUKKAN PASSWORD : ";
    cin >> password;
    for(int i = 0; i < jumlahpengguna; i++){
        if(username == pengguna[i].username && password == pengguna[i].password){
            return true;
        }
    }
    return false;
}

void tambahBuah(){
    judulpnjng("TAMBAH DAFTAR BUAH");
}

void updateBuah(){
    judulpnjng("UPDATE DAFTAR BUAH");
}

void hapusBuah(){
    judulpnjng("HAPUS DAFTAR BUAH");
}

void laporanPenjualan(){
    judulpnjng("LAPORAN PENJUALAN");
}

void konfirmasiTopUp(){
    try {
        judulpnjng("KONFIRMASI TOP-UP");
        bool adaPermintaan = false;

        cout << "+" << setfill('-') << setw(5) << "+" << setw(20) << "+" << setw(15) << "+" << setw(15) << "+" << endl;
        cout << setfill(' ') << "| " << left << setw(3) << "no" << " | " << setw(18) << "username" << "| " << setw(13) << "jumlah" << "| " << setw(12) << "status" << "|" << endl;
        cout << "+" << setfill('-') << setw(5) << "+" << setw(20) << "+" << setw(15) << "+" << setw(15) << "+" << setfill(' ') << endl;

        for (int i = 0; i < jumlahTopUp; i++) {
            if (daftarTopUp[i].status == "dalam proses") {
                adaPermintaan = true;
                cout << "| " << left << setw(3) << i + 1 << " | " << setw(18) << daftarTopUp[i].username << "| Rp" << setw(10) << daftarTopUp[i].jumlah << " | " << setw(12) << daftarTopUp[i].status << "|" << endl;
            }
        }

        if (!adaPermintaan) {
            cout << "| " << setw(52) << left << "tidak ada antrean top-up saat ini." << " |" << endl;
        }
        cout << "+" << setfill('-') << setw(5) << "+" << setw(20) << "+" << setw(15) << "+" << setw(15) << "+" << setfill(' ') << endl << endl;

        if (adaPermintaan) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan sisa Enter dari menu sebelumnya
            for (int i = 0; i < jumlahTopUp; i++) {
                if (daftarTopUp[i].status == "dalam proses") {
                    cout << "> konfirmasi top-up [" << daftarTopUp[i].username << "] sebesar Rp" << daftarTopUp[i].jumlah << " (y/n): ";
                    string konfirmasi; getline(cin, konfirmasi);
                    
                    if (konfirmasi == "y" || konfirmasi == "Y") {
                        for (int j = 0; j < jumlahpengguna; j++) {
                            if (pengguna[j].username == daftarTopUp[i].username) {
                                pengguna[j].saldo += daftarTopUp[i].jumlah;
                                daftarTopUp[i].status = "selesai";
                                cout << ">>> berhasil dikonfirmasi!\n" << endl;
                                break;
                            }
                        }
                    } else if (konfirmasi.empty()) {
                        throw invalid_argument("!!! input tidak boleh kosong !!!");
                    } else if (konfirmasi == "n" || konfirmasi == "N") {
                        cout << ">>> dilewati.\n" << endl;
                    } else {
                        throw invalid_argument("!!! input tidak valid, harap masukkan 'y' atau 'n' !!!");
                    }
                }
            }
        }
    } catch (const exception& e) {
        cout << "\n[ERROR] Terjadi Kesalahan: " << e.what() << endl;
    }
}

void hapusUser(){
    judulpnjng("HAPUS USER");
}

void belibuah(){
    judulpnjng("PEMBELIAN BUAH");
}

void lihatriwayat(){
    judulpnjng("RIWAYAT PEMBELIAN");
}

void prosesTopUp(){
    judulpnjng("TOP-UP SALDO");
    try {
        if (jumlahTopUp >= MAX) {
            cout << "!!! antrean top-up penuh, silakan hubungi admin !!!" << endl;
            return;
        }

        cout << "masukkan jumlah top-up: Rp"; string input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); getline(cin, input);

        if (input.empty()) {
            throw invalid_argument("!!! input tidak boleh kosong !!!");
        }

        for (char c : input) {
            if (c < '0' || c > '9') {
                throw invalid_argument("!!! input tidak valid !!!");
            }
        }

        int jumlah = stoi(input);
        if (jumlah < 10000) throw invalid_argument("!!! jumlah top-up tidak boleh kurang dari Rp10000 !!!");

        for (int i = 0; i < jumlahpengguna; i++) {
            if (pengguna[i].username == username) {
                if (jumlah > 1000000) {
                    throw invalid_argument("!!! jumlah top-up tidak boleh lebih dari Rp1.000.000 !!!");
                }
                break;
            }
        }

        daftarTopUp[jumlahTopUp].username = username;
        daftarTopUp[jumlahTopUp].jumlah = jumlah;
        daftarTopUp[jumlahTopUp].status = "dalam proses";

        cout << "\n+" << setfill('-') << setw(46) << "+" << endl;
        cout << setfill(' ') << "|" << setw(36) << right << "RINGKASAN PERMINTAAN TOP-UP" << setw(10) << "|" << endl;
        cout << "+" << setfill('-') << setw(46) << "+" << endl;
        cout << setfill(' ') << "| " << left << setw(13) << "username" << " : " << setw(26) << daftarTopUp[jumlahTopUp].username << "  |" << endl;
        cout << "| " << left << setw(13) << "jumlah"   << " : Rp" << setw(23) << daftarTopUp[jumlahTopUp].jumlah << "   |" << endl;
        cout << "| " << left << setw(13) << "status"   << " : " << setw(26) << daftarTopUp[jumlahTopUp].status << "  |" << endl;
        cout << "+" << setfill('-') << setw(46) << "+" << setfill(' ') << endl;

        jumlahTopUp++;
        cout << "\npermintaan telah dikirim! menunggu konfirmasi admin.\n" << endl;
    } catch (const exception& e) {
        cout << "\n[ERROR] terjadi kesalahan: " << e.what() << endl;
    }
}

void lihatsaldo(){
    judulpnjng("LIHAT SALDO");
    for (int i = 0; i < jumlahpengguna; i++) {
        if (pengguna[i].username == username) {
            cout << "saldo anda saat ini: Rp" << pengguna[i].saldo << "\n" << endl;
            return;
        }
    }
}

void menulihat(){
}

void menuadmin(){
    while(login_admin){
        system("cls");
        judulpnjng("SILAHKAN PILIH MENU");
        cout << "1. tambah daftar buah" << endl;
        cout << "2. lihat daftar buah" << endl;
        cout << "3. update harga dan stok buah" << endl;
        cout << "4. hapus buah" << endl;
        cout << "5. laporan penjualan" << endl;
        cout << "6. konfirmasi top-up" << endl;
        cout << "7. hapus user" << endl;
        cout << "8. keluar" << endl;
        cout << "=============================" << endl;
        cout << "masukkan pilihan anda : ";
        cin >> pilihan;
        system("cls");
        switch(pilihan){
            case 1: 
                tambahBuah();
                system("pause");
                continue;
            case 2:
                menulihat();
                system("pause");
                continue;
            case 3:
                updateBuah();
                system("pause");
                continue;
            case 4:
                hapusBuah();
                system("pause");
                continue;
            case 5:
                laporanPenjualan();
                system("pause");
                continue;
            case 6:
                konfirmasiTopUp();
                system("pause");
                continue;
            case 7:
                hapusUser();
                system("pause");
                continue;
            case 8:
                login_admin = false;
                break;
            default:
                takvalid();
                continue;
        }
    }
}

void menuuser(){
    while(login_user){
        system("cls");
        judulpnjng("SILAHKAN PILIH MENU");
        cout << "1. lihat daftar buah" << endl;
        cout << "2. pembelian buah" << endl;
        cout << "3. riwayat pembelian" << endl;
        cout << "4. top-up saldo" << endl;
        cout << "5. lihat saldo" << endl;
        cout << "6. keluar" << endl;
        cout << "=============================" << endl;
        cout << "masukkan pilihan anda : ";
        cin >> pilihan;
        system("cls");
        switch(pilihan){
            case 1:
                menulihat();
                system("pause");
                continue;
            case 2:
                belibuah();
                system("pause");
                continue;
            case 3:
                lihatriwayat();
                system("pause");
                continue;
            case 4:
                prosesTopUp();
                system("pause");
                continue;
            case 5:
                lihatsaldo();
                system("pause");
                continue;
            case 6:
                login_user = false;
                break;
            default:
                takvalid();
                continue;
        }
    }
}

int main(){
    while(true){
        while(!login_admin && !login_user){
            system("cls");
            judulpnjng("SELAMAT DATANG DI TOKO BUAH KICAW");
            cout << "1. LOGIN SEBAGAI ADMIN " << endl;
            cout << "2. LOGIN SEBAGAI PENGGUNA BIASA" << endl;
            cout << "3. REGISTER" << endl;
            cout << "4. KELUAR" << endl;
            cout << "=========================================================\n";
            cout << "MASUKKAN PILIHAN ANDA : ";
            cin >> pilihan;
            system("cls");
            switch(pilihan){
                case 1:
                    if(admin_login(username, password)){
                        judulpnjng("LOGIN BERHASIL");
                        system("pause");
                        login_admin = true;
                        login_user = false;
                        percobaan = 0;
                        menuadmin();
                        break;
                    }else{
                        percobaan++;
                        if(percobaan == 3){
                            cout << "percobaan login anda habis, program keluar" << endl;
                            return 0;
                        }else{
                            cout << "!!! percobaan anda tersisa " << 3 - percobaan << " kali, coba lagi !!!" << endl;
                            system("pause");
                        }
                        continue;
                    }
                case 2:
                    if(login_pengguna(username, password)){
                        judulpnjng("LOGIN BERHASIL");
                        system("pause");
                        login_admin = false;
                        login_user = true;
                        percobaan = 0;
                        menuuser();
                        break;
                    }else{
                        percobaan++;
                        if(percobaan == 3){
                            cout << "percobaan login anda habis, program keluar" << endl;
                            return 0;
                        }else{
                            cout << "!!! percobaan anda tersisa " << 3 - percobaan << " kali, coba lagi !!!" << endl;
                            system("pause");
                        }
                        continue;
                    }
                case 3:
                    registrasi();
                    continue;
                case 4:
                    cout << "TERIMA KASIH TELAH  MENGGUNAKAN PROGRAM INI" << endl;
                    return 0;
                default:
                    takvalid();
                    continue;
            }
        }
    }
}