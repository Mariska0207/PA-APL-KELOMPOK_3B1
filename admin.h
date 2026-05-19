#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <iomanip>
#include "global.h"
#include "lihat.h"
#include "utils.h"

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
            if(daftarBuah[totalbuah].nama.back() == ' '){
                throw invalid_argument("!!! nama buah tidak boleh diakhiri dengan spasi !!!");
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
            cout << "\n[ERROR] input terlalu panjang." << endl;
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
            cout << "\n[ERROR] input terlalu panjang." << endl;
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
            cout << "\n[ERROR] input terlalu panjang." << endl;
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
        cout << "\n[ERROR] input terlalu panjang." << endl;
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
            cout << "\n[ERROR] input terlalu panjang." << endl;
            setcolor(7);
        }catch(exception &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
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

#endif