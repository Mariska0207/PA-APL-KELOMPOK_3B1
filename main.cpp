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
string username, password, namabuah;
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

void lihat_buah(){
    cout << left << setw(5) << "No"
    << setw(20) << "Nama Buah"
    << setw(10) << "Harga"
    << setw(10) << "Stok"
    << setw(10) << "Status" << endl;
    cout << "=========================================================\n";
    
    for(int i = 0; i < totalbuah; i++){
        cout << left << setw(5) << i+1
        << setw(20) << daftarBuah[i].nama
        << setw(10) << daftarBuah[i].harga
        << setw(10) << daftarBuah[i].stok
        << setw(10) << daftarBuah[i].status << endl;
    }
    cout << "=========================================================\n";
}

void headerbuah(){
    cout << left << setw(5) << "No"
        << setw(20) << "Nama Buah"
        << setw(10) << "Harga"
        << setw(10) << "Stok"
        << setw(10) << "Status" << endl;
    cout << "=========================================================\n";
}

void lihatbuah(int index){
    cout << left << setw(5) << index+1
        << setw(20) << daftarBuah[index].nama
        << setw(10) << daftarBuah[index].harga
        << setw(10) << daftarBuah[index].stok
        << setw(10) << daftarBuah[index].status << endl;
}

void lihat_user(){
    cout << left << setw(5) << "No"
    << setw(20) << "Username"
    << setw(10) << "Password" << endl;
    for(int i = 0; i < jumlahpengguna; i++){
        cout << left << setw(5) << i+1
        << setw(20) << pengguna[i].username
        << setw(10) << pengguna[i].password << endl;
    }
}

void tambahBuah(){
    judulpnjng("TAMBAH DAFTAR BUAH");
    if(totalbuah >= MAX){
        cout << "!!! daftar buah penuh !!!" << endl;
    }else{
        bool ada;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        do{
            ada = false;
            cout << "masukkan nama buah : ";
            getline(cin, daftarBuah[totalbuah].nama);
            for(int i = 0; i < totalbuah; i++){
                if(daftarBuah[totalbuah].nama == daftarBuah[i].nama){
                    cout << "nama buah sudah ada" << endl;
                    ada = true;
                    break;
                }
            }
        }while(ada);
        cout << "masukkan harga buah : ";
        cin >> daftarBuah[totalbuah].harga;
        cout << "masukkan stok buah (kg) : ";
        cin >> daftarBuah[totalbuah].stok;
        cout << "masukkan status buah : ";
        cin >> daftarBuah[totalbuah].status;
        totalbuah++;
        judulpnjng("BUAH BERHASIL DITAMBAHKAN");
    }
}

void updateBuah(){
    judulpnjng("UPDATE DAFTAR BUAH");
    if(totalbuah == 0){
        cout << "!!! daftar buah kosong !!!" << endl;
    }else{
        lihat_buah();
        int no_update;
        cout << "masukkan NOMOR buah yang ingin di update (1-" << totalbuah << "): ";
        cin >> no_update;
        cin.ignore();
        if(no_update >= 1 && no_update <= totalbuah){
            cout << "masukkan harga baru buah: ";
            cin >> daftarBuah[no_update - 1].harga;
            cout << "masukkan stok baru buah: ";
            cin >> daftarBuah[no_update - 1].stok;
            cout << "masukkan status baru buah: ";
            cin >> daftarBuah[no_update - 1].status;
            judulpnjng("BUAH BERHASIL DIUPDATE");
        }else{
            judulpnjng("!!! BUAH TIDAK DITEMUKAN !!!");
        }
    }
}

void hapusBuah(){
    judulpnjng("HAPUS DAFTAR BUAH");
    if(totalbuah == 0){
        cout << "!!! daftar buah kosong !!!" << endl;
    }else{
        lihat_buah();
        int no_hapus;
        cout << "masukkan NOMOR buah yang ingin di hapus (1-" << totalbuah << "): ";
        cin >> no_hapus;
        cin.ignore();
        if(no_hapus >= 1 && no_hapus <= totalbuah){
            for(int j = no_hapus - 1; j < totalbuah - 1; j++){
                daftarBuah[j] = daftarBuah[j + 1];
            }
            totalbuah--;
            judulpnjng("BUAH BERHASIL DIHAPUS");
        }else{
            judulpnjng("!!! BUAH TIDAK DITEMUKAN !!!");
        }
    }
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
    if(jumlahpengguna == 0){
        cout << "!!! daftar pengguna kosong !!!" << endl;
    }else{
        lihat_user();
        int no_hapus;
        cout << "masukkan NOMOR pengguna yang ingin di hapus (1-" << jumlahpengguna << "): ";
        cin >> no_hapus;
        cin.ignore();
        if(no_hapus >= 1 && no_hapus <= jumlahpengguna){
            for(int j = no_hapus - 1; j < jumlahpengguna - 1; j++){
                pengguna[j] = pengguna[j + 1];
            }
            jumlahpengguna--;
            judulpnjng("USER BERHASIL DIHAPUS");
        }else{
            judulpnjng("!!! USER TIDAK DITEMUKAN !!!");
        }
    }
}

void belibuah(){
    judulpnjng("PEMBELIAN BUAH");
    try{
        if(totalbuah == 0){
            cout << "!!! daftar buah kosong !!!" << endl;
            return;
        }
        lihat_buah();
        int pilihBuah, jumlahBeli;
        cout << "masukkan nomor buah yang ingin dibeli : ";
        cin >> pilihBuah;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("input harus berupa angka.");
        }

        if(pilihBuah < 1 || pilihBuah > totalbuah){
            throw out_of_range("nomor buah tidak tersedia");
        }

        cout << "masukkan jumlah beli (kg) : ";
        cin >> jumlahBeli;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("jumlah beli harus angka");
        }
        if(jumlahBeli <= 0){
            throw invalid_argument("jumlah beli harus lebih dari 0");
        }
        int index = pilihBuah - 1;
        if(daftarBuah[index].stok < jumlahBeli){
            throw runtime_error("stok buah tidak mencukupi");
        }
        int totalHarga = daftarBuah[index].harga * jumlahBeli;
        int userIndex = -1;
        for(int i = 0; i < jumlahpengguna; i++){
            if(pengguna[i].username == username){
                userIndex = i;
                break;
            }
        }
        if(userIndex == -1){
            throw runtime_error("data pengguna tidak ditemukan");
        }
        if(pengguna[userIndex].saldo < totalHarga){
            throw runtime_error("saldo anda tidak cukup");
        }

        pengguna[userIndex].saldo -= totalHarga;
        daftarBuah[index].stok -= jumlahBeli;

        if(daftarBuah[index].stok == 0){
            daftarBuah[index].status = "habis";
        }

        cout << "\n==========================================" << endl;
        cout << "         PEMBELIAN BERHASIL" << endl;
        cout << "==========================================" << endl;
        cout << "Nama buah   : " << daftarBuah[index].nama << endl;
        cout << "Jumlah beli : " << jumlahBeli << " kg" << endl;
        cout << "Total bayar : Rp" << totalHarga << endl;
        cout << "Sisa saldo  : Rp" << pengguna[userIndex].saldo << endl;
        cout << "Sisa stok   : " << daftarBuah[index].stok << " kg" << endl;
        cout << "==========================================" << endl;

    }catch(exception &e){
        cout << "\n[ERROR] " << e.what() << endl;
    }
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

void urutharga(Buah* arr, int n){
    for (int i = 0; i < n - 1; i++){
        int min_idx = i;
        for (int j = i + 1; j < n; j++){
            if ((arr + j)->harga < (arr + min_idx)->harga){
                min_idx = j;
            }
        }
        if(min_idx != i){
            swap(*(arr + i), *(arr + min_idx));
        }
    }
}

void nama(Buah* arr, int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;

    Buah L[n1], R[n2];

    for (int i = 0; i < n1; i++){
        *(L + i) = *(arr + l + i);
    }
    for (int j = 0; j < n2; j++){
        *(R + j) = *(arr + m + 1 + j);
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2){
        if((L + i)->nama >= (R + j)->nama){
            *(arr + k) = *(L + i);
            i++;
        }else{
            *(arr + k) = *(R + j);
            j++;
        }
        k++;
    }
    while (i < n1){
        *(arr + k) = *(L + i);
        i++;k++;
    }
    while (j < n2){
        *(arr + k) = *(R + j);
        j++;k++;
    }
}

void urutnama(Buah* arr, int l, int r){
    if (l < r){
        int m = (l + r) / 2;
        urutnama(arr, l, m);
        urutnama(arr, m + 1, r);
        nama(arr, l, m, r);
    }
}

void urutstok(Buah* arr, int n){
    for (int i = 1; i < n ; i++){
        Buah key = *(arr + i);
        int j = i - 1;
        while (j >= 0 && (arr + j)->stok > key.stok){
            *(arr + j + 1) = *(arr + j);
            j = j - 1;
        }
        *(arr + j + 1) = key;
    }
}

int carinama(Buah* arr, int n, string nama){
    if (n == 0){
        cout << "!!! daftar buah kosong !!!" << endl;
        return -1;
    }
    for (int i = 0; i < n; i++){
        if (arr[i].nama == nama){
            headerbuah();
            for (int j = i; j < n; j++){
                if (arr[j].nama == nama){
                    lihatbuah(j);
                }
            }
            return i;
        }
    }
    cout << "!!! buah tidak ditemukan !!!" << endl;
    return -1;
}

void cariharga(int target){
    int n = totalbuah;
    if (n == 0){
        cout << "!!! data kosong !!!" << endl;
        return;
    }
    urutharga(daftarBuah, totalbuah);
    int step = (int)sqrt(n);
    int prev = 0;
    while (prev < n && daftarBuah[min(step, n)-1].harga < target){
        prev = step;
        step += (int)sqrt(n);
        if (prev >= n){
            cout << "!!! buah tidak ditemukan !!!\n";
            return;
        }
    }
    int batas = min(step, n);
    while (prev < batas){
        if (daftarBuah[prev].harga == target){
            int i = prev;
            while (i >= 0 && daftarBuah[i].harga == target){
                i--;
            }
            i++;
            cout << "hasil ditemukan:" << endl;
            headerbuah();
            while (i < n && daftarBuah[i].harga == target){
                lihatbuah(i);
                i++;
            }
            return;
        }
        prev++;
    }
    cout << "!!! buah tidak ditemukan !!!\n";
}

void menulihat(){
    bool keluar = false;
    while(!keluar){
        system("cls");
        judulpnjng("SILAHKAN PILIH MENU");
        cout << "1. harga termurah-termahal\n2. nama urut(z-a)\n3. stok terdikit-terbanyak\n4. cari berdasarkan nama\n5. cari berdasarkan harga\n6.keluar" << endl;
        cout << "=============================" << endl;
        cout << "masukkan pilihan anda : ";
        cin >> pilihan;
        system("cls");
        switch(pilihan){
            case 1:
                judulpnjng("HARGA TERMURAH-TERMAHAL");
                if(totalbuah == 0){
                    cout << "!!! daftar buah kosong !!!" << endl;
                    system("pause");
                    continue;
                }else{
                    urutharga(daftarBuah, totalbuah);
                    lihat_buah();
                    system("pause");
                    continue;
                }
            case 2:
                judulpnjng("NAMA URUT (Z-A)");
                if(totalbuah == 0){
                    cout << "!!! daftar buah kosong !!!" << endl;
                    system("pause");
                    continue;
                }else{
                    urutnama(daftarBuah, 0, totalbuah-1);
                    lihat_buah();
                    system("pause");
                    continue;
                }
            case 3:
                judulpnjng("STOK TERDIKIT-TERBANYAK");
                if(totalbuah == 0){
                    cout << "!!! daftar buah kosong !!!" << endl;
                    system("pause");
                    continue;
                }else{
                    urutstok(daftarBuah, totalbuah);
                    lihat_buah();
                    system("pause");
                    continue;
                }
            case 4:
                judulpnjng("CARI BERDASARKAN NAMA");
                cout << "masukkan nama buah yang ingin dicari : ";
                cin >> namabuah;
                carinama(daftarBuah, totalbuah, namabuah);
                system("pause");
                break;
            case 5:
                judulpnjng("CARI BERDASARKAN HARGA");
                cout << "masukkan harga yang ingin dicari : ";
                int targetharga;
                cin >> targetharga;
                cariharga(targetharga);
                system("pause");
                break;
            case 6:
                keluar = true;
                break;
            default:
                takvalid();
                continue;
        }
    }
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