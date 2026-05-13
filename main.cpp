#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <windows.h>
#include <cctype>
#include <ctime>
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

void setcolor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void progressBar(){
    setcolor(10);
    cout << "\n[";
    for(int i = 0; i < 20; i++){
        cout << "▮";
        Sleep(50);
    }
    cout << " ]\n";
    setcolor(7);
}

bool validusername(const string& str){
    for(char c : str){
        if(!isalnum((unsigned char)c) && c != '_' && c != '.'){
            return false;
        }
    }
    return true;
}

bool validpassword(const string& str){
    for(char c : str){
        if(!isalnum((unsigned char)c) && c != '_' && c != '.'){
            return false;
        }
    }
    return true;
}

bool validNamaBuah(const string& str){
    for(char c : str){
        if(!isalpha((unsigned char)c) && c != ' '){
            return false;
        }
        if(!isalnum((unsigned char)c) && c != ' '){
            return false;
        }
    }
    return true;
}

void validpanjangpw(const string& str, int panjangmin = 3, int panjangmax = 8){
    if(str.length() < panjangmin || str.length() > panjangmax){
            throw invalid_argument("!!! panjang password minimal 3 karakter dan maksimal 8 karakter !!!");
    }
}

void validpanjangusn(const string& str, int panjangmin = 3, int panjangmax = 20){
    if(str.length() < panjangmin || str.length() > panjangmax){
            throw invalid_argument("!!! panjang username minimal 3 karakter dan maksimal 20 karakter !!!");
    }
}

void takvalid(){
    setcolor(12);
    cout << "!!! ⚠️  pilihan tidak valid !!!" << endl;
    setcolor(7);
    system("pause");
}

void judulpnjng(string judul){
    setcolor(11);
    int lebar = 57;
    int panjang = judul.length();
    int kiri = (lebar - panjang) / 2;

    cout << string(lebar, '=') << endl;
    cout << string(kiri, ' ') << judul << endl;
    cout << string(lebar, '=') << endl;
    setcolor(7);
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
    while(jumlahpengguna < MAX){
        system("cls");
        judulpnjng("REGISTRASI 📝");
        setcolor(14);
        cout << "TEKAN 0 UNTUK KEMBALI KE MENU UTAMA\n" << endl;
        setcolor(7);
        try{
            cout << "masukkan username : "; 
            getline(cin, username);
            if(username == "admin" || username == "Admin" || username == "ADMIN"){
                throw invalid_argument("!!! username tidak boleh digunakan !!!");
            }
            if(username == "0"){
                balik_menu = true;
                return;
            }
            if(username.empty()){
                throw invalid_argument("!!! username tidak boleh kosong !!!");
            }
            validpanjangusn(username);
            if(!validusername(username)){
                throw invalid_argument("!!! username tidak boleh mengandung karakter spesial seperti !@#$%^&*() dll. !!!");
            }
            cout << "masukkan password : "; 
            getline(cin, password);
            if(password.empty()){
                throw invalid_argument("!!! password tidak boleh kosong !!!");
            }
            validpanjangpw(password);
            if(!validpassword(password)){
                throw invalid_argument("!!! password tidak boleh mengandung karakter spesial(!@#$%^&*) dan spasi !!!");
            }
            if(cek_username(username, 0)){
                setcolor(12);
                cout << "!!! username sudah ada !!!" << endl;
                setcolor(7);
                system("pause");
                return;
            }
            progressBar();
            setcolor(10);
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
            cout << "        >>>>>> REGISTRASI ANDA BERHASIL ✅ <<<<<<" << endl;
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
            setcolor(7);
            pengguna[jumlahpengguna].username = username;
            pengguna[jumlahpengguna].password = password;
            pengguna[jumlahpengguna].saldo = 0;
            jumlahpengguna++;
            system("pause");
        }catch(exception &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
            system("pause");
        }
    }
    setcolor(12);
    cout << "!!! daftar pengguna penuh !!!" << endl;
    setcolor(7);
    system("pause");
}

bool admin_login(string &username, string &password, bool &balik_menu){
    while(percobaanadmin < 3){
        system("cls");
        judulpnjng("LOGIN ADMIN 💻");
        setcolor(14);
        cout << "TEKAN 0 UNTUK KEMBALI KE MENU UTAMA\n" << endl;
        setcolor(7);
        cout << "MASUKKAN USERNAME : ";
        getline(cin, username);
        if(username == "0"){
            balik_menu = true;
            return false;
        }
        if(username.empty()){
            throw invalid_argument("!!! username tidak boleh kosong !!!");
        }
        if(!validusername(username)){
            throw invalid_argument("!!! username tidak boleh mengandung karakter spesial seperti !@#$%^&*() dll. !!!");
        }
        cout << "MASUKKAN PASSWORD : ";
        getline(cin, password);
        if(password == "0"){
            balik_menu = true;
            return false;
        }
        if(password.empty()){
            throw invalid_argument("!!! password tidak boleh kosong !!!");
        }
        if(!validpassword(password)){
            throw invalid_argument("!!! password tidak boleh mengandung karakter spesial(!@#$%^&*) dan spasi !!!");
        }
        if(username == "admin" && password == "123"){
            progressBar();
            return true;
        }
        percobaanadmin++;
        if(percobaanadmin < 3){
            setcolor(14);
            cout << "\n⚠️  sisa percobaan " << 3 - percobaanadmin << " kali, coba lagi !!!\n" << endl;
            setcolor(7);
            system("pause");
            continue;
        }
    }
    return false;
}

bool login_pengguna(string &username, string &password, bool &balikmenu){
    while(percobaanuser < 3){
        system("cls");
        judulpnjng("LOGIN USER 👥");
        setcolor(14);
        cout << "TEKAN 0 UNTUK KEMBALI KE MENU UTAMA\n" << endl;
        setcolor(7);
        cout << "MASUKKAN USERNAME : ";
        getline(cin, username);
        if(username == "0"){
            balikmenu = true;
            return false;
        }
        if(username.empty()){
            throw invalid_argument("!!! username tidak boleh kosong !!!");
        }
        if(!validusername(username)){
            throw invalid_argument("!!! username tidak boleh mengandung karakter spesial seperti !@#$%^&*() dll. !!!");
        }
        cout << "MASUKKAN PASSWORD : ";
        getline(cin, password);
        if(password == "0"){
            balikmenu = true;
            return false;
        }
        if(password.empty()){
            throw invalid_argument("!!! password tidak boleh kosong !!!");
        }
        if(!validpassword(password)){
            throw invalid_argument("!!! password tidak boleh mengandung karakter spesial(!@#$%^&*) dan spasi !!!");
        }
        for(int i = 0; i < jumlahpengguna; i++){
            if(username == pengguna[i].username && password == pengguna[i].password){
                progressBar();
                return true;
            }
        }
        percobaanuser++;
        if(percobaanuser < 3){
            setcolor(14);
            cout << "\n⚠️  sisa percobaan " << 3 - percobaanuser << " kali, coba lagi !!!\n" << endl;
            setcolor(7);
            system("pause");
            continue;
        }
    }
    return false;
}

void lihatbuah(){
    setcolor(27);
    cout << left << setw(5) << "No"
    << setw(20) << "Nama Buah"
    << setw(10) << "Harga"
    << setw(10) << "Stok"
    << setw(12) << "Status" << endl;
    setcolor(11);
    cout << "=========================================================\n";
    setcolor(7);
    
    for(int i = 0; i < totalbuah; i++){
        cout << left << setw(5) << i+1
        << setw(20) << daftarBuah[i].nama; setcolor(14);
        cout << setw(10) << daftarBuah[i].harga; setcolor(7);
        cout << setw(10) << daftarBuah[i].stok
        << setw(10) << daftarBuah[i].status << endl;
    }
    setcolor(11);
    cout << "=========================================================\n";
    setcolor(7);
}

void headerbuah(){
    setcolor(11);
    cout << "=========================================================" << endl;
    setcolor(27);
    cout << left << setw(5) << "No"
        << setw(20) << "Nama Buah"
        << setw(10) << "Harga"
        << setw(10) << "Stok"
        << setw(12) << "Status" << endl;
    setcolor(11);
    cout << "=========================================================\n";
    setcolor(7);
}

void lihatbuah(int index){
    cout << left << setw(5) << index+1
        << setw(20) << daftarBuah[index].nama; setcolor(14);
        cout << setw(10) << daftarBuah[index].harga; setcolor(7);
        cout << setw(10) << daftarBuah[index].stok
        << setw(10) << daftarBuah[index].status << endl;
    setcolor(11);
    cout << "=========================================================\n";
    setcolor(7);
}

void lihat_user(){
    setcolor(27);
    cout << left << setw(5) << "No"
    << setw(20) << "Username"
    << setw(32) << "Password" << endl;
    setcolor(11);
    cout << "=========================================================\n";
    setcolor(7);
    for(int i = 0; i < jumlahpengguna; i++){
        cout << left << setw(5) << i+1
        << setw(20) << pengguna[i].username
        << setw(32) << pengguna[i].password << endl;
    }
    setcolor(11);
    cout << "=========================================================\n";
    setcolor(7);
}

void updateStatus(Buah *buah){
    if(buah->stok == 0){
        buah->status = "habis";
    }else{
        buah->status = "tersedia";
    }
}

void tambahBuah(){
    judulpnjng("TAMBAH DAFTAR BUAH 🍉");
    if(totalbuah >= MAX){
        setcolor(12);
        cout << "!!! daftar buah penuh !!!";
        setcolor(7);
    }else{
        try{
            cout << "masukkan nama buah : ";
            getline(cin, daftarBuah[totalbuah].nama);
            if(daftarBuah[totalbuah].nama.empty()){
                throw invalid_argument("!!! nama buah tidak boleh kosong !!!");
            }
            if(daftarBuah[totalbuah].nama[0] == ' '){
                throw invalid_argument("!!! nama buah tidak boleh dimulai dengan spasi !!!");
            }
            if(daftarBuah[totalbuah].nama.length() < panjangmin || daftarBuah[totalbuah].nama.length() > panjangmax){
                throw invalid_argument("!!! panjang nama buah minimal 3 karakter dan maksimal 30 karakter !!!");
            }
            if(!validNamaBuah(daftarBuah[totalbuah].nama)){
                throw invalid_argument("!!! nama buah tidak boleh mengandung karakter spesial seperti !@#$%^&*() dll. !!!");
            }
            for(char c : daftarBuah[totalbuah].nama){
                if(isdigit((unsigned char)c)){
                    throw invalid_argument("!!! nama buah tidak boleh mengandung angka !!!");
                }
            }               
            for(int i = 0; i < totalbuah; i++){
                if(daftarBuah[totalbuah].nama == daftarBuah[i].nama){
                    throw invalid_argument("!!! nama buah sudah ada !!!");
                }
            }
            string temp;
            cout << "masukkan harga buah :";
            setcolor(14);
            cout << " Rp";
            getline(cin, temp);
            setcolor(7);
            if(temp.empty()) throw invalid_argument("!!! harga tidak boleh kosong !!!");
            for(char c : temp) if(!isdigit(c)) throw invalid_argument("!!! harga tidak valid !!!");
            daftarBuah[totalbuah].harga = stol(temp);
            if(daftarBuah[totalbuah].harga < 1000 || daftarBuah[totalbuah].harga > 1000000) throw invalid_argument("!!! harga Rp1.000 - Rp1.000.000 !!!");

            cout << "masukkan stok buah : ";
            getline(cin, temp);
            if(temp.empty()) throw invalid_argument("!!! stok tidak boleh kosong !!!");
            for(char c : temp) if(!isdigit(c)) throw invalid_argument("!!! stok tidak valid !!!");
            daftarBuah[totalbuah].stok = stol(temp);
            if(daftarBuah[totalbuah].stok > 1000) throw invalid_argument("!!! stok maksimal 1000 pcs !!!");
            updateStatus(&daftarBuah[totalbuah]);

            totalbuah++;
            progressBar();
            setcolor(10);
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
            cout << "        >>>>>> BUAH BERHASIL DITAMBAHKAN ✅ <<<<<<" << endl;
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
            setcolor(7);
        }catch(out_of_range &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
        }catch(exception &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
        }
    }
}

void updateBuah(){
    judulpnjng("UPDATE DAFTAR BUAH 🫐");
    if(totalbuah == 0){
        setcolor(12);
        cout << "!!! daftar buah kosong !!!" << endl;
        setcolor(7);
    }else{
        lihatbuah();
        try{
            string No;
            cout << "masukkan NOMOR buah yang ingin di update (1-" << totalbuah << "): ";
            getline(cin, No);
            if(No.empty()) throw invalid_argument("!!! nomor tidak boleh kosong !!!");
            for(char c : No) if(!isdigit(c)) throw invalid_argument("!!! nomor tidak valid !!!");
            int no_update = stoi(No);

            if(no_update >= 1 && no_update <= totalbuah){
                string temp;
                cout << "\nmasukkan harga baru buah :";
                setcolor(14);
                cout << " Rp";
                getline(cin, temp);
                setcolor(7);
                if(temp.empty()) throw invalid_argument("!!! harga tidak boleh kosong !!!");
                for(char c : temp) if(!isdigit(c)) throw invalid_argument("!!! harga tidak valid !!!");
                daftarBuah[no_update - 1].harga = stol(temp);
                if(daftarBuah[no_update - 1].harga < 1000 || daftarBuah[no_update - 1].harga > 1000000) throw invalid_argument("!!! harga Rp1.000 - Rp1.000.000 !!!");

                cout << "masukkan stok baru buah: ";
                getline(cin, temp);
                if(temp.empty()) throw invalid_argument("!!! stok tidak boleh kosong !!!");
                for(char c : temp) if(!isdigit(c)) throw invalid_argument("!!! stok tidak valid !!!");
                daftarBuah[no_update - 1].stok = stol(temp);
                if(daftarBuah[no_update - 1].stok > 1000) throw invalid_argument("!!! stok maksimal 1000 pcs !!!");
                updateStatus(&daftarBuah[no_update - 1]);
                
                progressBar();
                setcolor(10);
                cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                cout << "          >>>>>> BUAH BERHASIL DIUPDATE ✅ <<<<<<" << endl;
                cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                setcolor(7);
            }else{
                setcolor(12);
                cout << "!!! BUAH TIDAK DITEMUKAN !!!" << endl;
                setcolor(7);
            }
        }catch(out_of_range &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
        }catch(exception &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
        }
    }
}

void hapusBuah(){
    judulpnjng("HAPUS DAFTAR BUAH 🗑️");
    if(totalbuah == 0){
        setcolor(12);
        cout << "!!! daftar buah kosong !!!" << endl;
        setcolor(7);
    }else{
        lihatbuah();
        try{
            string No;
            cout << "masukkan NOMOR buah yang ingin di hapus (1-" << totalbuah << "): ";
            getline(cin, No); 
            if(No.empty()) throw invalid_argument("!!! nomor tidak boleh kosong !!!");
            for(char c : No) if(!isdigit(c)) throw invalid_argument("!!! nomor tidak valid !!!");
            int no_hapus = stoi(No);
            if(no_hapus >= 1 && no_hapus <= totalbuah){
                for(int j = no_hapus - 1; j < totalbuah - 1; j++){
                    daftarBuah[j] = daftarBuah[j + 1];
                }
                totalbuah--;
                progressBar();
                setcolor(10);
                cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                cout << "           >>>>>> BUAH BERHASIL DIHAPUS ✅ <<<<<<" << endl;
                cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                setcolor(7);
            }else{
                setcolor(12);
                cout << "!!! BUAH TIDAK DITEMUKAN !!!" << endl;
                setcolor(7);
            }
        }catch(out_of_range &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
        }catch(exception &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
        }
    }
}

void laporanPenjualan(){
    setcolor(11);
    string title = "LAPORAN PENJUALAN 📚";
    int lebar = 68;
    int panjang = title.length();
    int kiri = (lebar - panjang) / 2;

    cout << string(lebar, '=') << endl;
    cout << string(kiri, ' ') << title << endl;
    cout << string(lebar, '=') << endl;
    setcolor(7);
    if(totalTransaksi == 0){
        setcolor(12);
        cout << "Belum ada transaksi pembelian." << endl;
        setcolor(7);
        return;
    }
    setcolor(27);
    cout << left << setw(4)  << "No"
        << setw(13) << "Username"
        << setw(13) << "Nama Buah"
        << setw(8)  << "Jumlah"
        << setw(13) << "Total Harga"
        << setw(17) << "Waktu" << endl;
    setcolor(11);
    cout << "====================================================================\n";
    setcolor(7);

    int totalPenjualan = 0;
    for(int i = 0; i < totalTransaksi; i++){
        cout << left << setw(4)  << i + 1
            << setw(13) << daftartran[i].pembeli
            << setw(13) << daftartran[i].barang
            << setw(8)  << daftartran[i].jumlahbeli; 
        setcolor(14);
        cout << setw(13) << daftartran[i].totalbayar; 
        setcolor(7);
        cout << setw(17) << daftartran[i].waktuTransaksi << endl;
        totalPenjualan += daftartran[i].totalbayar;
    }
    setcolor(11);
    cout << "====================================================================\n";
    setcolor(7);
    cout << setw(51) << "TOTAL : "; setcolor(14); cout << "Rp" << totalPenjualan << endl; setcolor(7);
}

void konfirmasiTopUp(){
    try {
        setcolor(11);
        string title = "KONFIRMASI TOP-UP 🏦";
        int lebar = 76;
        int panjang = title.length();
        int kiri = (lebar - panjang) / 2;

        cout << string(lebar, '=') << endl;
        cout << string(kiri, ' ') << title << endl;
        cout << string(lebar, '=') << endl;
        setcolor(7);
        cout << "+-----+-------------------+--------------+--------------+------------------+" << endl;
        cout << setfill(' ') << "| " << left << setw(3) << "no" << " | " << setw(18) << "username" << "| " << setw(13) << "jumlah" << "| " << setw(12) << "status" << " | " << setw(17) << "waktu" << "|" << endl;
        cout << "+-----+-------------------+--------------+--------------+------------------+" << endl;

        if (jumlahTopUp == 0) {
            cout << "| "; setcolor(12); cout  << setw(72) << left << "tidak ada antrean top-up."; setcolor(7); cout  << " |" << endl;
            cout << "+-----+-------------------+--------------+--------------+------------------+" << endl;
            return;
        } else {
            for (int i = 0; i < jumlahTopUp; i++) {
                cout << "| " << left << setw(3) << i + 1 << " | " << setw(18) << daftarTopUp[i].username << "| "; setcolor(14); cout << "Rp" << setw(10) << daftarTopUp[i].jumlah; setcolor(7); cout << " | " << setw(12) << daftarTopUp[i].status << " | " << setw(17) << daftarTopUp[i].waktuDibuat << "|" << endl;
            }
            cout << "+-----+-------------------+--------------+--------------+------------------+" << endl;
        }
        
        string sNomor; cout << "\nmasukkan nomor top-up yang ingin diproses (0 untuk kembali): "; 
        getline(cin, sNomor); 
        if (sNomor.empty()) throw invalid_argument("!!! input tidak boleh kosong !!!");
        for (char c : sNomor) if (!isdigit(c)) throw invalid_argument("!!! input tidak valid !!!");
        
        int nomor = stoi(sNomor);
        if (nomor == 0) return;
        if (nomor < 1 || nomor > jumlahTopUp) throw invalid_argument("!!! nomor tidak valid !!!");

        int idx = nomor - 1;
        if (daftarTopUp[idx].status != "dalam proses") {
            throw runtime_error("!!! permintaan ini sudah diproses (selesai/ditolak) !!!");
        }
        cout << "> konfirmasi top-up [" << daftarTopUp[idx].username << "] sebesar Rp" << daftarTopUp[idx].jumlah << " (y/n): ";
        string konfirmasi; 
        getline(cin, konfirmasi);       
        if (konfirmasi.empty()) throw invalid_argument("!!! input tidak boleh kosong !!!");
        if (konfirmasi == "y" || konfirmasi == "Y") {
            bool ditemukan = false;
            for (int j = 0; j < jumlahpengguna; j++) {
                if (pengguna[j].username == daftarTopUp[idx].username) {
                    pengguna[j].saldo += daftarTopUp[idx].jumlah;
                    daftarTopUp[idx].status = "selesai";
                    progressBar();
                    setcolor(10);
                    cout << ">>>>> BERHASIL: saldo pengguna telah ditambahkan ✅ <<<<<\n" << endl;
                    setcolor(7);
                    ditemukan = true;
                    break;
                }
            }
            if (!ditemukan) throw runtime_error("!!! pengguna tidak ditemukan di sistem !!!");
        } else if (konfirmasi == "n" || konfirmasi == "N") {
            daftarTopUp[idx].status = "ditolak";
            progressBar();
            setcolor(12);
            cout << ">>> GAGAL: permintaan top-up ditolak  ❌\n" << endl;
            setcolor(7);
        } else {
            throw invalid_argument("!!! input tidak valid, harap masukkan 'y' atau 'n' !!!");
        }
    } catch (const out_of_range& e) {
        setcolor(12);
        cout << "\n[ERROR] " << e.what() << endl;
        setcolor(7);
    } catch (const exception& e) {
        setcolor(12);
        cout << "\n[ERROR] " << e.what() << endl;
        setcolor(7);
    }
}

void hapusUser(){
    judulpnjng("HAPUS USER 🗑️");
    if(jumlahpengguna == 0){
        setcolor(12);
        cout << "!!! daftar pengguna kosong !!!" << endl;
        setcolor(7);
    }else{
        lihat_user();
        try{
            string sNo;
            cout << "masukkan NOMOR pengguna yang ingin di hapus (1-" << jumlahpengguna << "): ";
            getline(cin, sNo);
            if(sNo.empty()) throw invalid_argument("!!! nomor tidak boleh kosong !!!");
            for (char c : sNo) if (!isdigit(c)) throw invalid_argument("!!! input tidak valid !!!");
            
            int no_hapus = stoi(sNo);
            if(no_hapus >= 1 && no_hapus <= jumlahpengguna){
                for(int j = no_hapus - 1; j < jumlahpengguna - 1; j++){
                    pengguna[j] = pengguna[j + 1];
                }
                jumlahpengguna--;
                progressBar();
                setcolor(10);
                cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                cout << "          >>>>>> USER BERHASIL DIHAPUS ✅ <<<<<<" << endl;
                cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                setcolor(7);
            }else{
                setcolor(12);
                cout << "!!! USER TIDAK DITEMUKAN !!!" << endl;
                setcolor(7);
            }
        }catch(out_of_range &e){
            setcolor(12);
            cout << "\n[ERROR] angka di luar batas." << endl;
            setcolor(7);
        }catch(exception &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
        }
    }
}

void belibuah(){
    judulpnjng("PEMBELIAN BUAH 🛒");

    try{
        if(totalbuah == 0){
            setcolor(12);
            cout << "!!! daftar buah kosong !!!" << endl;
            setcolor(7);
            return;
        }
        lihatbuah();
        string sPilih, sJumlah;
        cout << "masukkan nomor buah yang ingin dibeli (0 untuk kembali): ";
        getline(cin, sPilih);
        if(sPilih.empty()) throw invalid_argument("!!! nomor tidak boleh kosong !!!");
        for(char c : sPilih) if(!isdigit(c)) throw invalid_argument("!!! nomor tidak valid !!!");
        int pilihBuah = stoi(sPilih);
        if(pilihBuah == 0){
            cout << endl; return;
        }
        if(pilihBuah < 1 || pilihBuah > totalbuah){
            throw invalid_argument("pilihan tidak tersedia");
        }
        cout << "masukkan jumlah beli : ";
        getline(cin, sJumlah); 
        if(sJumlah.empty()) throw invalid_argument("!!! jumlah tidak boleh kosong !!!");
        for(char c : sJumlah) if(!isdigit(c)) throw invalid_argument("!!! jumlah tidak valid !!!");
        
        long int jumlahBeli = stoi(sJumlah);
        if(jumlahBeli <= 0) throw invalid_argument("!!! jumlah beli harus lebih dari 0 !!!");
        int index = pilihBuah - 1;
        if(daftarBuah[index].stok < jumlahBeli){
            throw runtime_error("!!! stok buah tidak mencukupi !!!");
        }
        long int totalHarga = daftarBuah[index].harga * jumlahBeli;
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
        updateStatus(&daftarBuah[index]);

        transaksi waktu;
        time_t t = time(0);
        tm* sekarang = localtime(&t);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M", sekarang);
        waktu.waktuTransaksi = buffer;

        daftartran[totalTransaksi].pembeli = username;
        daftartran[totalTransaksi].barang = daftarBuah[index].nama;
        daftartran[totalTransaksi].jumlahbeli = jumlahBeli;
        daftartran[totalTransaksi].totalbayar = totalHarga;
        daftartran[totalTransaksi].waktuTransaksi = waktu.waktuTransaksi;
        totalTransaksi++;
        progressBar();
        setcolor(10);
        cout << "\n==========================================" << endl;
        cout << "      >>>>>> PEMBELIAN BERHASIL ✅ <<<<<<" << endl;
        cout << "==========================================" << endl;
        setcolor(7);
        cout << "Nama buah   : " << daftarBuah[index].nama << endl;
        cout << "Jumlah beli : " << jumlahBeli << " pcs" << endl;
        cout << "Total bayar : "; setcolor(14); cout << "Rp" << totalHarga << endl; setcolor(7);
        cout << "Sisa saldo  : "; setcolor(14); cout << "Rp" << pengguna[userIndex].saldo << endl; setcolor(7);
        cout << "Waktu       : " << waktu.waktuTransaksi << endl;
        cout << "Sisa stok   : " << daftarBuah[index].stok << endl;
        setcolor(10);
        cout << "==========================================" << endl;
        setcolor(7);
    }catch(out_of_range &e){
        setcolor(12);
        cout << "\n[ERROR] input terlalu panjang." << endl;
        setcolor(7);
    }catch(exception &e){
        setcolor(12);
        cout << "\n[ERROR] " << e.what() << endl;
        setcolor(7);
    }
}

void lihatriwayat(){
    setcolor(11);
    string title = "RIWAYAT PEMBELIAN 📜";
    int lebar = 62;
    int panjang = title.length();
    int kiri = (lebar - panjang) / 2;

    cout << string(lebar, '=') << endl;
    cout << string(kiri, ' ') << title << endl;
    cout << string(lebar, '=') << endl;

    bool ada = false;
    setcolor(27);
    cout << left << setw(4) << "No"
        << setw(18) << "Nama Buah"
        << setw(10) << "Jumlah"
        << setw(13) << "Total Harga"
        << setw(17) << "Waktu" << endl;
    setcolor(11);
    cout << "==============================================================\n";
    setcolor(7);

    int no = 1;
    for(int i = 0; i < totalTransaksi; i++){
        if(daftartran[i].pembeli == username){
            cout << left << setw(4) << no++
                << setw(18) << daftartran[i].barang
                << setw(10) << daftartran[i].jumlahbeli;
            setcolor(14); 
            cout << setw(13) << daftartran[i].totalbayar; 
            setcolor(7);
            cout << setw(17) << daftartran[i].waktuTransaksi << endl;
            ada = true;
        }
    }
    if(!ada){
        setcolor(12);
        cout << "belum ada riwayat pembelian." << endl;
        setcolor(7);
    }
    setcolor(11);
    cout << "==============================================================\n";
    setcolor(7);
}

void prosesTopUp(){
    judulpnjng("TOP-UP SALDO 💸");
    try {
        if (jumlahTopUp >= MAX) {
            setcolor(12);
            cout << "!!! antrean top-up penuh, silakan hubungi admin !!!" << endl;
            setcolor(7);
            return;
        }
        cout << "masukkan jumlah top-up:"; 
        string input;
        setcolor(14);
        cout << " Rp";
        getline(cin, input);
        setcolor(7);
        if (input.empty()) {
            throw invalid_argument("!!! input tidak boleh kosong !!!");
        }
        for (char c : input) {
            if (!isdigit(c)) {
                throw invalid_argument("!!! input tidak valid !!!");
            }
        }
        long int jumlah = stol(input);
        if (jumlah < 10000) throw invalid_argument("!!! jumlah top-up tidak boleh kurang dari Rp10000 !!!");
        for (int i = 0; i < jumlahpengguna; i++) {
            if (pengguna[i].username == username) {
                if (jumlah > 1000000) {
                    throw invalid_argument("!!! jumlah top-up tidak boleh lebih dari Rp1.000.000 !!!");
                }
                break;
            }
        }
        
        topup waktu;
        time_t t = time(0);
        tm* sekarang = localtime(&t);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M", sekarang);
        waktu.waktuDibuat = buffer;

        daftarTopUp[jumlahTopUp].username = username;
        daftarTopUp[jumlahTopUp].jumlah = jumlah;
        daftarTopUp[jumlahTopUp].status = "dalam proses";
        daftarTopUp[jumlahTopUp].waktuDibuat = waktu.waktuDibuat;

        cout << "\n+---------------------------------------------+" << endl;
        cout << setfill(' ') << "|" << setw(36) << right << "RINGKASAN PERMINTAAN TOP-UP" << setw(10) << "|" << endl;
        cout << "+" << setfill('-') << setw(46) << "+" << endl;
        cout << setfill(' ') << "| " << left << setw(13) << "username" << " : " << setw(26) << daftarTopUp[jumlahTopUp].username << "  |" << endl;
        cout << "| " << left << setw(13) << "jumlah"   << " : "; setcolor(14); cout << "Rp" << setw(26) << daftarTopUp[jumlahTopUp].jumlah; setcolor(7); cout << "|" << endl;
        cout << "| " << left << setw(13) << "status"   << " : " << setw(26) << daftarTopUp[jumlahTopUp].status << "  |" << endl;
        cout << "| " << left << setw(13) << "waktu"   << " : " << setw(26) << daftarTopUp[jumlahTopUp].waktuDibuat << "  |" << endl;

        cout << "+---------------------------------------------+" << endl;

        jumlahTopUp++;
        progressBar();
        setcolor(10);
        cout << "\npermintaan telah dikirim! menunggu konfirmasi admin.\n" << endl;
        setcolor(7);
    } catch (const out_of_range& e) {
        setcolor(12);
        cout << "\n[ERROR] input terlalu panjang." << endl;
        setcolor(7);
    } catch (const exception& e) {
        setcolor(12);
        cout << "\n[ERROR] " << e.what() << endl;
        setcolor(7);
    }
}

void lihatsaldo(){
    judulpnjng("LIHAT SALDO 🤑");
    for (int i = 0; i < jumlahpengguna; i++) {
        if (pengguna[i].username == username) {
            cout << "saldo anda saat ini: "; setcolor(14); cout <<  "Rp" << pengguna[i].saldo << "\n" << endl; setcolor(7);
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
        setcolor(12);
        cout << "!!! daftar buah kosong !!!" << endl;
        setcolor(7);
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
        setcolor(12);
        cout << "!!! buah tidak ditemukan !!!" << endl;
        setcolor(7);
    return -1;
}

void cariharga(int target){
    int n = totalbuah;
    if (n == 0){
        setcolor(12);
        cout << "!!! daftar buah kosong !!!" << endl;
        setcolor(7);
        return;
    }
    urutharga(daftarBuah, totalbuah);
    int step = (int)sqrt(n);
    int prev = 0;
    while (prev < n && daftarBuah[min(step, n)-1].harga < target){
        prev = step;
        step += (int)sqrt(n);
        if (prev >= n){
            break;
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
            headerbuah();
            while (i < n && daftarBuah[i].harga == target){
                lihatbuah(i);
                i++;
            }
            return;
        }
        prev++;
    }
    setcolor(12);
    cout << "!!! buah dengan harga " << target << " tidak ditemukan !!!\n";
    setcolor(7);
}

void menulihat(){
    bool keluar = false;
    while(!keluar){
        system("cls");
        judulpnjng("SILAHKAN PILIH MENU 🔍");
        cout << "1. 📈 harga termurah-termahal\n2. 🔤 nama urut(z-a)\n3. 📦 stok terdikit-terbanyak\n4. 🔎 cari berdasarkan nama\n5. 💲 cari berdasarkan harga\n6. keluar" << endl;
        setcolor(11);
        cout << "=========================================================\n";
        setcolor(7);
        try{
            string sPilih;
            setcolor(9);
            cout << "MASUKKAN PILIHAN ANDA : ";
            getline(cin, sPilih);
            setcolor(7);
            if(sPilih.empty()) throw invalid_argument("!!! pilihan tidak boleh kosong !!!");
            for (char c : sPilih) {
                if (!isdigit(c)) {
                    throw invalid_argument("!!! input tidak valid !!!");
                }
            }
            pilihan = stoi(sPilih);
            system("cls");
            switch(pilihan){
                case 1:
                    judulpnjng("HARGA TERMURAH-TERMAHAL 📈");
                    if(totalbuah == 0){
                        setcolor(12);
                        cout << "!!! daftar buah kosong !!!" << endl;
                        setcolor(7);
                        system("pause");
                        break;
                    }else{
                        urutharga(daftarBuah, totalbuah);
                        lihatbuah();
                        system("pause");
                        break;
                    }
                case 2:
                    judulpnjng("NAMA URUT (Z-A) 🔤");
                    if(totalbuah == 0){
                        setcolor(12);
                        cout << "!!! daftar buah kosong !!!" << endl;
                        setcolor(7);
                        system("pause");
                        break;
                    }else{
                        urutnama(daftarBuah, 0, totalbuah-1);
                        lihatbuah();
                        system("pause");
                        break;
                    }
                case 3:
                    judulpnjng("STOK TERDIKIT-TERBANYAK 📈");
                    if(totalbuah == 0){
                        setcolor(12);
                        cout << "!!! daftar buah kosong !!!" << endl;
                        setcolor(7);
                        system("pause");
                        break;
                    }else{
                        urutstok(daftarBuah, totalbuah);
                        lihatbuah();
                        system("pause");
                        break;
                    }
                case 4:
                    judulpnjng("CARI BERDASARKAN NAMA 🔍");
                    cout << "masukkan nama buah yang ingin dicari : ";
                    getline(cin, namabuah);
                    if(namabuah.empty()){
                        throw invalid_argument("!!! input tidak boleh kosong !!!");
                    }
                    if(!validNamaBuah(namabuah)){
                        throw invalid_argument("!!! nama buah tidak boleh mengandung karakter spesial seperti !@#$%^&*() dll. !!!");
                    }
                    carinama(daftarBuah, totalbuah, namabuah);
                    system("pause");
                    break;
                case 5:{
                    judulpnjng("CARI BERDASARKAN HARGA 🔍");
                    cout << "masukkan harga yang ingin dicari : ";
                    string input;
                    getline(cin, input);
                    if(input.empty()){
                        throw invalid_argument("!!! input tidak boleh kosong !!!");
                    }
                    for(char c : input){
                        if(!isdigit(c)){
                            throw invalid_argument("!!! input tidak valid !!!");
                        }
                    }
                    long int targetharga = stol(input);
                    cariharga(targetharga);
                    system("pause");
                    break;
                }
                case 6:
                    keluar = true;
                    break;
                default:
                    takvalid();
                    break;
            }
        } catch(out_of_range &e) {
            setcolor(12);
            cout << "\n[ERROR] input terlalu panjang." << endl;
            setcolor(7);
            system("pause");
        } catch(exception &e) {
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
            system("pause");
        }
    }
}

void menuadmin(){
    while(login_admin){
        system("cls");
        judulpnjng("MENU ADMIN 🛠️");
        try {
            cout << "1. 🍉 tambah daftar buah" << endl;
            cout << "2. 👀 lihat daftar buah" << endl;
            cout << "3. ✏️  update harga dan stok buah" << endl;
            cout << "4. 🗑️  hapus buah" << endl;
            cout << "5. 📊 laporan penjualan" << endl;
            cout << "6. 💳 konfirmasi top-up" << endl;
            cout << "7. ❌ hapus user" << endl;
            cout << "8. 🚪 keluar" << endl;
            setcolor(11);
            cout << "=========================================================\n";
            setcolor(9);
            cout << "MASUKKAN PILIHAN ANDA : "; string pilihan;
            getline(cin, pilihan);
            setcolor(7);
            if (pilihan.empty()) {
                throw invalid_argument("!!! input tidak boleh kosong !!!");
            }
            for (char c : pilihan) {
                if (c < '0' || c > '9') {
                    throw invalid_argument("!!! input tidak valid !!!");
                }
            }
            int pilih = stoi(pilihan);
            system("cls");
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
        } catch(out_of_range &e) {
            setcolor(12);
            cout << "\n[ERROR] input terlalu panjang." << endl;
            setcolor(7);
            system("pause");
        } catch (const exception& e) {
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
            system("pause");
        }
    }
}

void menuuser(){
    while(login_user){
        try{
            system("cls");
            judulpnjng("MENU USER 👤");
            cout << "1. 👀 lihat daftar buah" << endl;
            cout << "2. 🛍️  pembelian buah" << endl;
            cout << "3. 📜 riwayat pembelian" << endl;
            cout << "4. 💸 top-up saldo" << endl;
            cout << "5. 💰 lihat saldo" << endl;
            cout << "6. 🚪 keluar" << endl;
            setcolor(11);
            cout << "=========================================================\n";
            setcolor(9);
            cout << "MASUKKAN PILIHAN ANDA : ";
            string input;
            getline(cin, input);
            setcolor(7);
            if(input.empty()){
                throw invalid_argument("!!! input tidak boleh kosong !!!");
            }
            for(char c : input){
                if(!isdigit(c)){
                    throw invalid_argument("!!! input tidak valid !!!");
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
        } catch(out_of_range &e) {
            setcolor(12);
            cout << "\n[ERROR] input terlalu panjang." << endl;
            setcolor(7);
            system("pause");
        }catch(exception &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
            system("pause");
        }
    }
}

int main(){
    SetConsoleOutputCP(65001);
    while(true){
        while(!login_admin && !login_user){
            system("cls");
            judulpnjng("SELAMAT DATANG DI TOKO BUAH KICAW 🍎");
            cout << "1. 🖥️  LOGIN SEBAGAI ADMIN " << endl;
            cout << "2. ​👥​ LOGIN SEBAGAI PENGGUNA BIASA" << endl;
            cout << "3. 📝 REGISTER" << endl;
            cout << "4. 🚪 KELUAR" << endl;
            setcolor(11);
            cout << "=========================================================\n";
            setcolor(9);
            cout << "MASUKKAN PILIHAN ANDA : ";
            try {
                string input;
                getline(cin, input);
                setcolor(7);
            if(input.empty()) throw invalid_argument("!!! input tidak boleh kosong !!!");
            for(char c : input) {
                if(!isdigit(c)) throw invalid_argument("!!! input tidak valid !!!");
            }
            pilihan = stoi(input);
            system("cls");
            switch(pilihan){
                case 1:
                    if(admin_login(username, password, balik_menu)){
                        setcolor(10);
                        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                        cout << "             >>>>>> LOGIN BERHASIL ✅ <<<<<<" << endl;
                        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                        setcolor(7);
                        system("pause");
                        login_admin = true;
                        login_user = false;
                        percobaanadmin = 0;
                        menuadmin();
                        break;
                    }else if(percobaanadmin == 3){
                        setcolor(13);
                        cout << "\npercobaan login anda habis, program keluar 💀" << endl;
                        setcolor(7);
                        return 0;
                    }else{
                        balik_menu = true;
                        continue;
                    }
                case 2:
                    if(login_pengguna(username, password, balik_menu)){
                        setcolor(10);
                        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                        cout << "             >>>>>> LOGIN BERHASIL ✅ <<<<<<" << endl;
                        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                        setcolor(7);
                        system("pause");
                        login_admin = false;
                        login_user = true;
                        percobaanuser = 0;
                        menuuser();
                        break;
                    }else if(percobaanuser == 3){
                        setcolor(13);
                        cout << "\npercobaan login anda habis, program keluar 💀" << endl;
                        setcolor(7);
                        return 0;
                    }else{
                        balik_menu = true;
                        continue;
                    }
                case 3:
                    registrasi();
                    balik_menu = true;
                    continue;
                case 4:             
                    setcolor(14);         
                    cout << "TERIMA KASIH TELAH  MENGGUNAKAN PROGRAM INI 👋 \n" << endl;
                    cout << R"(⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⠞⢛⣟⢛⠻⣿⣛⣛⣟⣛⠳⣦⣤⣤⣴⠶⠿⠛⢛⣻⣟⣻⣿⣿⣷⣶⣶⣤⣀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⠾⠛⢉⣠⡾⣿⡿⢿⣷⣶⣤⡈⠉⠉⠛⠻⢯⣥⡀⠀⣀⣤⠶⣻⣿⢻⣿⣿⣯⡍⠙⠻⢿⣿⣦⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⠿⠟⢀⣴⠞⠋⠁⢰⣿⡿⢿⣯⣉⣿⣷⠀⠀⠀⠀⠀⠈⣿⠟⠉⠀⢰⣿⣿⢿⣿⣉⣿⣿⡄⠀⠀⠀⠉⣿
⠀⠀⠀⠀⠀⠀⢀⣤⡾⠋⠃⠀⠀⠻⣧⡀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⣸⡇⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⢀⣴⡟
⠀⠀⠀⠀⢀⣴⠟⠉⠀⠀⠀⠀⠀⠀⠀⠙⠳⢦⣤⣙⣻⠿⠿⠟⠋⣁⣀⣠⣤⣶⠾⠋⠳⠶⣤⣤⣤⣙⣻⣿⣿⣿⣯⣥⣶⡶⣿⡿⠟⠀
⠀⠀⠀⣴⣿⠁⠀⠀⠀⠀⢀⣤⠶⠶⠶⠶⣦⣤⣤⣉⡉⠉⠉⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀
⠀⢠⣾⠋⠀⠀⠀⠀⠀⠀⢿⣧⡀⠀⠰⣤⣀⣀⠀⠉⠙⠛⠛⠷⠶⢶⣦⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⣶⠾⠛⣷⡄⠀
⣰⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠷⣦⣄⡀⠉⠛⠒⠶⢤⣄⠀⠀⠀⠀⠀⠈⠉⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠉⠉⠀⠀⣀⣴⣿⠁⠀
⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠳⢶⣤⣄⣀⠀⠀⠈⠉⠉⠛⠓⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡇⢻⡆⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠛⠻⠷⢶⣤⣤⣤⣤⣤⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣴⠿⠁⠈⢿⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⠀⠀⠀⠀⠈⠉⠉⠉⠉⠉⠙⠛⠉⠉⠁⠀⠀⠀⠘⣧
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⠉⠛⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⡇⠀⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡇⠀⣼⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡿⠁⢀⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠛⠁⠀⠘⠿⠶⠶⣦⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠈⢉⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢋⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠟⠁⠀⠀⠀⣀⣤⣤⣀⣀⠀⠀⣀⣴⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⠟⠁⠀⠀⠀⣠⣾⠟⠁⠀⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⡾⠛⠁⠀⠀⠀⣠⡾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡶⠋⠁⠀⠀⠀⠀⣠⣾⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)";
                    setcolor(7);
                    return 0;
                default:
                    takvalid();
                    continue;
                }
            } catch(out_of_range &e) {
                setcolor(12);
                cout << "\n[ERROR] input terlalu panjang." << endl;
                setcolor(7);
                system("pause");
            }catch(exception &e){
                setcolor(12);
                cout << "\n[ERROR] " << e.what() << endl;
                setcolor(7);
                system("pause");
            }
        }
    }
}