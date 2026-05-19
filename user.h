#ifndef USER_H
#define USER_H
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <iomanip>
#include <ctime>
#include "global.h"
#include "lihat.h"
#include "utils.h"

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
        if(sPilih[0] == '0') throw invalid_argument("!!! nomor tidak boleh di awali angka 0 !!!");
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
        if(sJumlah[0] == '0') throw invalid_argument("!!! jumlah beli tidak boleh di awali angka 0 !!!");
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
    }catch(const out_of_range &e){
        setcolor(12);
        cout << "\n[ERROR] input terlalu panjang." << endl;
        setcolor(7);
    }catch(const exception &e){
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
        if (input.empty()) throw invalid_argument("!!! input tidak boleh kosong !!!");
        if(input[0] == '0') throw invalid_argument("!!! input tidak boleh di awali angka 0 !!!");
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
    } catch(const out_of_range& e) {
        setcolor(12);
        cout << "\n[ERROR] input terlalu panjang." << endl;
        setcolor(7);
    } catch(const exception& e) {
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
            if(input.empty()) throw invalid_argument("!!! input tidak boleh kosong !!!");
            if(input[0] == '0') throw invalid_argument("!!! input tidak boleh di awali angka 0 !!!");
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
        } catch(const out_of_range &e) {
            setcolor(12);
            cout << "\n[ERROR] input terlalu panjang." << endl;
            setcolor(7);
            system("pause");
        }catch(const exception &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
            system("pause");
        }
    }
}

#endif