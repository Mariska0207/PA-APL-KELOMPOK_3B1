#include <iostream>
#include <iomanip>
#include <cmath>
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
nama_pengguna pengguna[MAX] = {
    {"kicaw", "123", 100000}
};
string username, password;
int pilihan, totalbuah = 0, percobaan = 0, jumlahpengguna = 1;

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
    judulpnjng("KONFIRMASI TOP-UP");
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

void topup(){
    judulpnjng("TOP-UP SALDO");
}

void lihatsaldo(){
    judulpnjng("LIHAT SALDO");
    for (int i = 0; i < jumlahpengguna; i++) {
        if (pengguna[i].username == username) {
            cout << "Saldo Anda saat ini: Rp" << pengguna[i].saldo << ".\n" << endl;
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
                topup();
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