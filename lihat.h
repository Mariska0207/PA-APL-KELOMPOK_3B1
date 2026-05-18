#ifndef LIHAT_H
#define LIHAT_H
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <cmath>
#include "global.h"
#include "utils.h"

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

#endif