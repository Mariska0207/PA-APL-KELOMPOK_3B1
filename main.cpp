#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <windows.h>
using namespace std;

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
};


#define MAX 100
Buah daftarBuah[MAX];
string username, password, namabuah;
int pilihan, totalbuah = 0, percobaan = 0, jumlahpengguna = 1, totalTransaksi = 0;
string pembeli[MAX], barang[MAX];
int jumlahTopUp = 0; topup daftarTopUp[MAX];
int totalBayar[MAX], jumlahBeliLaporan[MAX];

nama_pengguna pengguna[MAX] = {
    {"kicaw", "123", 100000}
};

void progressBar(){
    cout << "\n[";
    for(int i = 0; i < 20; i++){
        cout << "▮";
        Sleep(50);
    }
    cout << " ]\n";
}


void takvalid(){
    cout << "!!! pilihan tidak valid !!!" << endl;
    system("pause");
}

void judulpnjng(string judul){
    int lebar = 57;
    int panjang = judul.length();
    int kiri = (lebar - panjang) / 2;

    cout << string(lebar, '=') << endl;
    cout << string(kiri, ' ') << judul << endl;
    cout << string(lebar, '=') << endl;
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
    cout << "=========================================================" << endl;
    cout << "                     REGISTER" << endl;
    cout << "=========================================================" << endl;
    if (jumlahpengguna < MAX){
        cout << "masukkan username : "; 
        getline(cin, username);
        if(username.empty()){
            throw invalid_argument("!!! username tidak boleh kosong !!!");
        }
        cout << "masukkan password : "; 
        getline(cin, password);
        if(password.empty()){
            throw invalid_argument("!!! password tidak boleh kosong !!!");
        }
        if(cek_username(username, 0)){
            cout << "!!! username sudah ada !!!" << endl;
            system("pause");
            return;
        }
        progressBar();
        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
        cout << "        >>>>>> REGISTRASI ANDA BERHASIL <<<<<<" << endl;
        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
        pengguna[jumlahpengguna].username = username;
        pengguna[jumlahpengguna].password = password;
        jumlahpengguna++;
        system("pause");
    }else{
        cout << "!!! daftar pengguna penuh !!!" << endl;
    }
}

bool admin_login(string &username, string &password){
    cout << "=========================================================" << endl;
    cout << "                      💻 ADMIN 💻" << endl;
    cout << "=========================================================" << endl;
    cout << "MASUKKAN USERNAME : ";
    getline(cin, username);
    if(username.empty()){
        throw invalid_argument("!!! username tidak boleh kosong !!!");
    }
    cout << "MASUKKAN PASSWORD : ";
    getline(cin, password);
    if(password.empty()){
        throw invalid_argument("!!! password tidak boleh kosong !!!");
    }
    if(username == "admin" && password == "123"){
        progressBar();
        return true;
    }
    return false;
}

bool login_pengguna(string &username, string &password){
    cout << "=========================================================" << endl;
    cout << "                    PENGGUNA BIASA" << endl;
    cout << "=========================================================" << endl;
    cout << "MASUKKAN USERNAME : ";
    getline(cin, username);
    if(username.empty()){
        throw invalid_argument("!!! username tidak boleh kosong !!!");
    }
    cout << "MASUKKAN PASSWORD : ";
    getline(cin, password);
    if(password.empty()){
        throw invalid_argument("!!! password tidak boleh kosong !!!");
    }
    for(int i = 0; i < jumlahpengguna; i++){
        if(username == pengguna[i].username && password == pengguna[i].password){
            progressBar();
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
    cout << "=========================================================" << endl;
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
        cout << "!!! daftar buah penuh !!!";
    }else{
        try{
            bool ada;
            do{
                ada = false;
                cout << "masukkan nama buah : ";
                getline(cin, daftarBuah[totalbuah].nama);
                if(daftarBuah[totalbuah].nama.empty()){
                    throw invalid_argument("!!! nama buah tidak boleh kosong !!!");
                }
                for(char c : daftarBuah[totalbuah].nama){
                    if(isdigit(c)){
                        throw invalid_argument("!!! nama buah tidak boleh mengandung angka !!!");
                    }
                }               
                for(int i = 0; i < totalbuah; i++){
                    if(daftarBuah[totalbuah].nama == daftarBuah[i].nama){
                        cout << "nama buah sudah ada" << endl;
                        ada = true;
                        break;
                    }
                }
            }while(ada);
            string temp;
            cout << "masukkan harga buah : ";
            getline(cin, temp);
            if(temp.empty()) throw invalid_argument("!!! harga tidak boleh kosong !!!");
            for(char c : temp) if(!isdigit(c)) throw invalid_argument("!!! harga harus angka !!!");
            daftarBuah[totalbuah].harga = stol(temp);   
            if(daftarBuah[totalbuah].harga < 1000) throw invalid_argument("!!! harga minimal Rp1000 !!!");

            cout << "masukkan stok buah : ";
            getline(cin, temp);
            if(temp.empty()) throw invalid_argument("!!! stok tidak boleh kosong !!!");
            for(char c : temp) if(!isdigit(c)) throw invalid_argument("!!! stok harus angka !!!");
            daftarBuah[totalbuah].stok = stoi(temp);           
            if(daftarBuah[totalbuah].stok < 1) throw invalid_argument("!!! stok minimal 1 !!!");

            cout << "masukkan status buah(tersedia/habis) : ";
            getline(cin, daftarBuah[totalbuah].status);
            if(daftarBuah[totalbuah].status.empty()) throw invalid_argument("!!! status tidak boleh kosong !!!");
            if(daftarBuah[totalbuah].status != "tersedia" && daftarBuah[totalbuah].status != "habis"){
                throw invalid_argument("!!! status harus 'tersedia' atau 'habis' !!!");
            }

            totalbuah++;
            progressBar();
            judulpnjng(">>>>>>>>>> BUAH BERHASIL DITAMBAHKAN <<<<<<<<<<");
        }catch(out_of_range &e){
            cout << "\n[ERROR] input terlalu panjang." << endl;
        }catch(exception &e){
            cout << "\n[ERROR] " << e.what() << endl;
        }
    }
}

void updateBuah(){
    judulpnjng("UPDATE DAFTAR BUAH");
    if(totalbuah == 0){
        cout << "!!! daftar buah kosong !!!" << endl;
    }else{
        lihat_buah();
        try{
            string No;
            cout << "masukkan NOMOR buah yang ingin di update (1-" << totalbuah << "): ";
            getline(cin, No);
            if(No.empty()) throw invalid_argument("!!! nomor tidak boleh kosong !!!");
            int no_update = stoi(No);

            if(no_update >= 1 && no_update <= totalbuah){
                string temp;
                cout << "masukkan harga baru buah: ";
                getline(cin, temp);
                if(temp.empty()) throw invalid_argument("!!! harga tidak boleh kosong !!!");
                for(char c : temp) if(!isdigit(c)) throw invalid_argument("!!! harga harus angka !!!");
                daftarBuah[no_update - 1].harga = stol(temp);
                
                if(daftarBuah[no_update - 1].harga < 1000){
                    throw invalid_argument("!!! harga minimal Rp1000 !!!");
                }

                cout << "masukkan stok baru buah: ";
                getline(cin, temp);
                if(temp.empty()) throw invalid_argument("!!! stok tidak boleh kosong !!!");
                for(char c : temp) if(!isdigit(c)) throw invalid_argument("!!! stok harus angka !!!");
                daftarBuah[no_update - 1].stok = stoi(temp);

                if(daftarBuah[no_update - 1].stok < 1){
                    throw invalid_argument("!!! stok minimal 1 !!!");
                }

                cout << "masukkan status baru buah (tersedia/habis): ";
                getline(cin, daftarBuah[no_update - 1].status);
                if(daftarBuah[no_update - 1].status.empty()){
                    throw invalid_argument("!!! status tidak boleh kosong !!!");
                }
                if(daftarBuah[no_update - 1].status != "tersedia" && daftarBuah[no_update - 1].status != "habis"){
                    throw invalid_argument("!!! status tidak valid !!!");
                }
                progressBar();
                judulpnjng("BUAH  DIUPDATE");
            }else{
                judulpnjng("!!! BUAH TIDAK DITEMUKAN !!!");
            }
        }catch(out_of_range &e){
            cout << "\n[ERROR] input terlalu panjang." << endl;
        }catch(exception &e){
            cout << "\n[ERROR] " << e.what() << endl;
        }
    }
}

void hapusBuah(){
    judulpnjng("HAPUS DAFTAR BUAH");
    if(totalbuah == 0){
        cout << "!!! daftar buah kosong !!!" << endl;
    }else{
        lihat_buah();
        try{
            string No;
            cout << "masukkan NOMOR buah yang ingin di hapus (1-" << totalbuah << "): ";
            getline(cin, No); 
            if(No.empty()) throw invalid_argument("!!! nomor tidak boleh kosong !!!");
            int no_hapus = stoi(No);
            if(no_hapus >= 1 && no_hapus <= totalbuah){
                for(int j = no_hapus - 1; j < totalbuah - 1; j++){
                    daftarBuah[j] = daftarBuah[j + 1];
                }
                totalbuah--;
                progressBar();
                judulpnjng(">>>>>>>>>> BUAH BERHASIL DIHAPUS <<<<<<<<<<");
            }else{
                judulpnjng("!!! BUAH TIDAK DITEMUKAN !!!");
            }
        }catch(out_of_range &e){
            cout << "\n[ERROR] input terlalu panjang." << endl;
        }catch(exception &e){
            cout << "\n[ERROR] " << e.what() << endl;
        }
    }
}

void laporanPenjualan(){
    judulpnjng("LAPORAN PENJUALAN");

    if(totalTransaksi == 0){
        cout << "Belum ada transaksi pembelian." << endl;
        return;
    }

    cout << left << setw(5)  << "No"
        << setw(15) << "Username"
        << setw(20) << "Nama Buah"
        << setw(10) << "Jumlah"
        << setw(15) << "Total Harga" << endl;
    cout << "===============================================================" << endl;

    int totalPenjualan = 0;
    for(int i = 0; i < totalTransaksi; i++){
        cout << left << setw(5)  << i + 1
            << setw(15) << pembeli[i]
            << setw(20) << barang[i]
            << setw(10) << jumlahBeliLaporan[i]
            << setw(15) << totalBayar[i] << endl;
        totalPenjualan += totalBayar[i];
    }
    cout << "===============================================================" << endl;
    cout << setw(50) << "TOTAL : "
        << "Rp" << totalPenjualan << endl;
}

void konfirmasiTopUp(){
    try {
        judulpnjng("KONFIRMASI TOP-UP");
        cout << "+" << setfill('-') << setw(5) << "+" << setw(20) << "+" << setw(15) << "+" << setw(15) << "+" << endl;
        cout << setfill(' ') << "| " << left << setw(3) << "no" << " | " << setw(18) << "username" << "| " << setw(13) << "jumlah" << "| " << setw(12) << "status" << "|" << endl;
        cout << "+" << setfill('-') << setw(5) << "+" << setw(20) << "+" << setw(15) << "+" << setw(15) << "+" << setfill(' ') << endl;

        if (jumlahTopUp == 0) {
            cout << "| " << setw(52) << left << "tidak ada riwayat top-up." << " |" << endl;
        } else {
            for (int i = 0; i < jumlahTopUp; i++) {
                cout << "| " << left << setw(3) << i + 1 << " | " << setw(18) << daftarTopUp[i].username << "| Rp" << setw(10) << daftarTopUp[i].jumlah << " | " << setw(12) << daftarTopUp[i].status << "|" << endl;
            }
        }
        cout << "+" << setfill('-') << setw(5) << "+" << setw(20) << "+" << setw(15) << "+" << setw(15) << "+" << setfill(' ') << endl;
        
        if (jumlahTopUp == 0) return;
        string sNomor; cout << "\nmasukkan nomor top-up yang ingin diproses (0 untuk kembali): "; 
        getline(cin, sNomor); int nomor = stoi(sNomor);
        if (nomor == 0) return;
        if (nomor < 1 || nomor > jumlahTopUp) throw out_of_range("!!! nomor tidak valid !!!");

        int idx = nomor - 1;
        if (daftarTopUp[idx].status != "dalam proses") {
            throw runtime_error("!!! permintaan ini sudah diproses (selesai/ditolak) !!!");
        }
        cout << "> konfirmasi top-up [" << daftarTopUp[idx].username << "] sebesar Rp" << daftarTopUp[idx].jumlah << " (y/n): ";
        string konfirmasi; 
        getline(cin, konfirmasi);       
        if (konfirmasi == "y" || konfirmasi == "Y") {
            bool ditemukan = false;
            for (int j = 0; j < jumlahpengguna; j++) {
                if (pengguna[j].username == daftarTopUp[idx].username) {
                    pengguna[j].saldo += daftarTopUp[idx].jumlah;
                    daftarTopUp[idx].status = "selesai";
                    progressBar();
                    cout << ">>>>> BERHASIL: saldo pengguna telah ditambahkan <<<<<\n" << endl;
                    ditemukan = true;
                    break;
                }
            }
            if (!ditemukan) throw runtime_error("!!! pengguna tidak ditemukan di sistem !!!");
        } else if (konfirmasi == "n" || konfirmasi == "N") {
            daftarTopUp[idx].status = "ditolak";
            cout << ">>> GAGAL: permintaan top-up ditolak.\n" << endl;
        } else {
            throw invalid_argument("!!! input tidak valid, harap masukkan 'y' atau 'n' !!!");
        }
    } catch (const out_of_range& e) {
        cout << "\n[ERROR] input terlalu panjang." << endl;
    } catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << endl;
    }
}

void hapusUser(){
    judulpnjng("HAPUS USER");
    if(jumlahpengguna == 0){
        cout << "!!! daftar pengguna kosong !!!" << endl;
    }else{
        lihat_user();
        try{
            string sNo;
            cout << "masukkan NOMOR pengguna yang ingin di hapus (1-" << jumlahpengguna << "): ";
            getline(cin, sNo);
            if(sNo.empty()) throw invalid_argument("!!! nomor tidak boleh kosong !!!");
            
            int no_hapus = stoi(sNo);
            if(no_hapus >= 1 && no_hapus <= jumlahpengguna){
                for(int j = no_hapus - 1; j < jumlahpengguna - 1; j++){
                    pengguna[j] = pengguna[j + 1];
                }
                jumlahpengguna--;
                progressBar();
                judulpnjng(">>>>>>>>>> USER BERHASIL DIHAPUS <<<<<<<<<<");
            }else{
                judulpnjng("!!! USER TIDAK DITEMUKAN !!!");
            }
        }catch(out_of_range &e){
            cout << "\n[ERROR] input terlalu panjang." << endl;
        }catch(exception &e){
            cout << "\n[ERROR] " << e.what() << endl;
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
        string sPilih, sJumlah;
        cout << "masukkan nomor buah yang ingin dibeli : ";
        getline(cin, sPilih);
        int pilihBuah = stoi(sPilih);
        if(pilihBuah < 1 || pilihBuah > totalbuah){
            throw out_of_range("pilihan tidak tersedia");
        }
        cout << "masukkan jumlah beli : ";
        getline(cin, sJumlah);
        int jumlahBeli = stoi(sJumlah);
        if(jumlahBeli <= 0) throw invalid_argument("jumlah beli harus lebih dari 0");
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

        pembeli[totalTransaksi] = username;
        barang[totalTransaksi] = daftarBuah[index].nama;
        jumlahBeliLaporan[totalTransaksi] = jumlahBeli;
        totalBayar[totalTransaksi] = totalHarga;
        totalTransaksi++;
        progressBar();
        cout << "\n==========================================" << endl;
        cout << "      >>>>>> PEMBELIAN BERHASIL <<<<<<" << endl;
        cout << "==========================================" << endl;
        cout << "Nama buah   : " << daftarBuah[index].nama << endl;
        cout << "Jumlah beli : " << jumlahBeli << " pcs" << endl;
        cout << "Total bayar : Rp" << totalHarga << endl;
        cout << "Sisa saldo  : Rp" << pengguna[userIndex].saldo << endl;
        cout << "Sisa stok   : " << daftarBuah[index].stok << endl;
        cout << "==========================================" << endl;

    }catch(out_of_range &e){
        cout << "\n[ERROR] input terlalu panjang." << endl;
    }catch(exception &e){
        cout << "\n[ERROR] " << e.what() << endl;
    }
}
void lihatriwayat(){
    judulpnjng("RIWAYAT PEMBELIAN");
    bool ada = false;
    cout << left << setw(5) << "No"
        << setw(20) << "Nama Buah"
        << setw(15) << "Jumlah"
        << setw(15) << "Total Harga" << endl;
    cout << "====================================================" << endl;

    int no = 1;
    for(int i = 0; i < totalTransaksi; i++){
        if(pembeli[i] == username){
            cout << left << setw(5) << no++
                << setw(20) << barang[i]
                << setw(15) << jumlahBeliLaporan[i]
                << setw(15) << totalBayar[i] << endl;
            ada = true;
        }
    }
    if(!ada){
        cout << "belum ada riwayat pembelian." << endl;
    }
    cout << "====================================================" << endl;
}

void prosesTopUp(){
    judulpnjng("TOP-UP SALDO");
    try {
        if (jumlahTopUp >= MAX) {
            cout << "!!! antrean top-up penuh, silakan hubungi admin !!!" << endl;
            return;
        }
        cout << "masukkan jumlah top-up: Rp"; 
        string input;
        getline(cin, input);
        if (input.empty()) {
            throw invalid_argument("!!! input tidak boleh kosong !!!");
        }
        for (char c : input) {
            if (!isdigit(c)) {
                throw invalid_argument("!!! input harus angka !!!");
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
        progressBar();
        cout << "\npermintaan telah dikirim! menunggu konfirmasi admin.\n" << endl;
    } catch (const out_of_range& e) {
        cout << "\n[ERROR] input terlalu panjang." << endl;
    } catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << endl;
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
    bool found = false;
    for (int i = 0; i < n; i++){
        if (arr[i].nama == nama){
            if(!found) headerbuah();
            lihatbuah(i);
            found = true;
        }
    }
    if(found) return 0;
    
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
        try{
            string sPilih;
            cout << "masukkan pilihan anda : ";
            getline(cin, sPilih);
            if(sPilih.empty()) throw invalid_argument("!!! pilihan tidak boleh kosong !!!");
            pilihan = stoi(sPilih);
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
                getline(cin, namabuah);
                if(namabuah.empty()){
                    throw invalid_argument("!!! input tidak boleh kosong !!!");
                }
                carinama(daftarBuah, totalbuah, namabuah);
                system("pause");
                break;
            case 5:{
                judulpnjng("CARI BERDASARKAN HARGA");
                cout << "masukkan harga yang ingin dicari : ";
                string input;
                getline(cin, input);
                if(input.empty()){
                    throw invalid_argument("!!! input tidak boleh kosong !!!");
                }
                for(char c : input){
                    if(!isdigit(c)){
                        throw invalid_argument("!!! input harus berupa angka !!!");
                    }
                }
                int targetharga = stoi(input);
                cariharga(targetharga);
                system("pause");
                break;
            }
            case 6:
                keluar = true;
                break;
            default:
                takvalid();
                continue;
        }
        } catch(out_of_range &e) {
            cout << "\n[ERROR] input terlalu panjang." << endl;
            system("pause");
        } catch(exception &e) {
            cout << "\n[ERROR] " << e.what() << endl;
            system("pause");
        }
    }
}

void menuadmin(){
    while(login_admin){
        system("cls");
        judulpnjng("SILAHKAN PILIH MENU");
        try {
            cout << "1. tambah daftar buah" << endl;
            cout << "2. lihat daftar buah" << endl;
            cout << "3. update harga dan stok buah" << endl;
            cout << "4. hapus buah" << endl;
            cout << "5. laporan penjualan" << endl;
            cout << "6. konfirmasi top-up" << endl;
            cout << "7. hapus user" << endl;
            cout << "8. keluar" << endl;
            cout << "=============================" << endl;
            cout << "MASUKKAN PILIHAN ANDA : "; string pilihan;
            getline(cin, pilihan);
            if (pilihan.empty()) {
                throw invalid_argument("!!! input tidak boleh kosong !!!");
            }
            system("cls");
            for (char c : pilihan) {
                if (c < '0' || c > '9') {
                    throw invalid_argument("!!! input tidak valid !!!");
                }
            }
            int pilih = stoi(pilihan);
            switch(pilih){
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
        } catch (const out_of_range& e) {
            cout << "\n[ERROR] input terlalu panjang." << endl;
            system("pause");
        } catch (const exception& e) {
            cout << "\n[ERROR] " << e.what() << endl;
            system("pause");
        }
    }
}

void menuuser(){
    while(login_user){
        try{
            system("cls");
            judulpnjng("SILAHKAN PILIH MENU");
            cout << "1. lihat daftar buah" << endl;
            cout << "2. pembelian buah" << endl;
            cout << "3. riwayat pembelian" << endl;
            cout << "4. top-up saldo" << endl;
            cout << "5. lihat saldo" << endl;
            cout << "6. keluar" << endl;
            cout << "=============================" << endl;
            cout << "MASUKKAN PILIHAN ANDA : ";
            string input;
            getline(cin, input);
            if(input.empty()){
                throw invalid_argument("!!! input tidak boleh kosong !!!");
            }
            for(char c : input){
                if(!isdigit(c)){
                    throw invalid_argument("!!! input harus berupa angka !!!");
                }
            }
            pilihan = stoi(input);
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
        }catch(out_of_range &e){
            cout << "\n[ERROR] input terlalu panjang." << endl;
            system("pause");
        }catch(exception &e){
            cout << "\n[ERROR] " << e.what() << endl;
            system("pause");
        }
    }
}

int main(){
    SetConsoleOutputCP(65001);
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
            try {
                string input;
                getline(cin, input);

            if(input.empty()) throw invalid_argument("!!! input tidak boleh kosong !!!");
            for(char c : input) {
                if(!isdigit(c)) throw invalid_argument("!!! input harus berupa angka !!!");
            }

            pilihan = stoi(input);
            system("cls");
            switch(pilihan){
                case 1:
                    if(admin_login(username, password)){
                        judulpnjng(">>>>>>>>>> LOGIN BERHASIL <<<<<<<<<<");
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
                            cout << "!!! sisa percobaan " << 3 - percobaan << " kali, coba lagi !!!" << endl;
                            system("pause");
                        }
                        continue;
                    }
                case 2:
                    if(login_pengguna(username, password)){
                        judulpnjng(">>>>>>>>>> LOGIN BERHASIL <<<<<<<<<<");
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
                            cout << "!!! sisa percobaan " << 3 - percobaan << " kali, coba lagi !!!" << endl;
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
            } catch(out_of_range &e) {
                cout << "\n[ERROR] input terlalu panjang " << endl;
                system("pause");
            }catch(exception &e){
                cout << "\n[ERROR] " << e.what() << endl;
                system("pause");
            }
        }
    }
}