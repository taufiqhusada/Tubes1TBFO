#include<bits/stdc++.h>
using namespace std;

#define pengaliHygiene 10000
#define pengaliEnergy 100

// list aksi
string listAksi[] = {"Tidur Siang","Tidur Malam","Makan Hamburger","Makan Pizza","Makan Steak And Beans","Minum Air","Minum Kopi","Minum Jus","Buang Air Kecil", "Buang Air Besar","Bersosialisasi Ke Kafe","Bermain Media Sosial","Bermain Komputer","Mandi","Cuci Tangan","Mendengarkan Musik Di Radio","Membaca Koran","Membaca Novel"};

bool isVisited[151515+5];   // untuk mengecek apakah state sudah tervisit
int tabelTransisi[151515+5][17+5];      // menyimpan tabel transisi
// atribut: hygiene, energy, fun

// getter atribut hygiene dari state
int getHygiene(int state){
    return (state/10000);
}

// getter atribut energy dari state
int getEnergy(int state){
    return ((state/100)%100);
}

// getter atribut fun dari state
int getFun(int state){
    return state%100;
}

int transisi(int stateAwal, string aksi){
    // fungsi transisi dari state awal ke state lanjutannya setelah melakukan suatu aksi
    if (aksi=="Tidur Siang"){
        return stateAwal+pengaliEnergy*10;
    }
    else if (aksi=="Tidur Malam"){
        return stateAwal+pengaliEnergy*15;
    }
    else if (aksi=="Makan Hamburger"){
        return stateAwal+pengaliEnergy*5;
    }
    else if (aksi=="Makan Pizza"){
        return stateAwal+pengaliEnergy*10;
    }
    else if (aksi=="Makan Steak And Beans"){
        return stateAwal+pengaliEnergy*15;
    }
    else if (aksi=="Minum Air"){
        return stateAwal-pengaliHygiene*5;
    }
    else if (aksi=="Minum Kopi"){
        return stateAwal-pengaliHygiene*10+pengaliEnergy*5;
    }
    else if (aksi=="Minum Jus"){
        return stateAwal-pengaliHygiene*5+pengaliEnergy*10;
    }
    else if (aksi=="Buang Air Kecil"){
        return stateAwal+pengaliHygiene*5;
    }
    else if (aksi=="Buang Air Besar"){
        return stateAwal+pengaliHygiene*10-pengaliEnergy*5;
    }
    else if (aksi=="Bersosialisasi Ke Kafe"){
        return stateAwal+15-pengaliEnergy*10-pengaliHygiene*5;
    }
    else if (aksi=="Bermain Media Sosisal"){
        return stateAwal+10-pengaliEnergy*10;
    }
    else if (aksi=="Bermain Komputer"){
        return stateAwal+15-pengaliEnergy*10;
    }
    else if (aksi=="Mandi"){
        return stateAwal+pengaliHygiene*15-pengaliEnergy*5;
    }
    else if (aksi=="Cuci Tangan"){
        return stateAwal + pengaliHygiene*5;
    }
    else if (aksi=="Mendengarkan Musik Di Radio"){
        return stateAwal+10-pengaliEnergy*5;
    }
    else if (aksi=="Membaca Koran"){
        return stateAwal+5-pengaliEnergy*5;
    }
    else { // membaca novel
        return stateAwal+10-pengaliEnergy*5;
    }
}

int enumerateAksi(string aksi){
    // fungsi untuk mengonvert aksi dari string ke integer, agar bisa mengakses array
    if (aksi=="Tidur Siang"){
        return 0;
    }
    else if (aksi=="Tidur Malam"){
        return 1;
    }
    else if (aksi=="Makan Hamburger"){
        return 2;
    }
    else if (aksi=="Makan Pizza"){
        return 3;
    }
    else if (aksi=="Makan Steak And Beans"){
        return 4;
    }
    else if (aksi=="Minum Air"){
        return 5;
    }
    else if (aksi=="Minum Kopi"){
        return 6;
    }
    else if (aksi=="Minum Jus"){
        return 7;
    }
    else if (aksi=="Buang Air Kecil"){
        return 8;
    }
    else if (aksi=="Buang Air Besar"){
        return 9;
    }
    else if (aksi=="Bersosialisasi Ke Kafe"){
        return 10;
    }
    else if (aksi=="Bermain Media Sosisal"){
        return 11;
    }
    else if (aksi=="Bermain Komputer"){
        return 12;
    }
    else if (aksi=="Mandi"){
        return 13;
    }
    else if (aksi=="Cuci Tangan"){
        return 14;
    }
    else if (aksi=="Mendengarkan Musik Di Radio"){
        return 15;
    }
    else if (aksi=="Membaca Koran"){
        return 16;
    }
    else { // membaca novel
        return 17;
    }
}

bool isTransisiValid(int stateAwal, string aksi){
    // fungsi untuk mengecek apakah suatu transisi valid atau tidak
    int nextState = transisi(stateAwal,aksi);
    int hygieneNow = getHygiene(nextState);
    int energyNow = getEnergy(nextState);
    int funNow = getFun(nextState);
    if (hygieneNow<0 || hygieneNow>15 || energyNow<0 || energyNow>15 || funNow<0 || funNow>15) return false;
    return true;
}

bool isEndState(int state){
    // fumgsi untuk mengecek apakah suatu state merupakan end state atau bukan
    return (state==0 ||state==151515);
}

void stateGenerator(int stateNow){
    // prosedur untuk menggenerate semua state yang possible
    for (int i = 0; i<=17; ++i){
        if (isTransisiValid(stateNow,listAksi[i])){
            int nextState = transisi(stateNow,listAksi[i]);
            tabelTransisi[stateNow][i] = nextState;
            if (!isEndState(nextState) && !isVisited[nextState]){
                isVisited[nextState] = true;
                stateGenerator(nextState);
            }
        }
    }
}

void writeToCsv(){
    // prosedur untuk menuliskan semua state yang telah di generate ke dalam csv
    std::ofstream myfile;
    myfile.open("output.csv");
    myfile<<"state awal"<<", ,";
    for (int i = 0; i<=17; ++i){
        myfile<<listAksi[i]<<",";
    }
    myfile<<"\n";
    for (int i = 0; i<=15; i+=5){
        for (int j = 0; j<=15; j+=5){
            for (int k = 0; k<=15; k+=5){
                int stateNow = i*pengaliHygiene+j*pengaliEnergy+k;
                myfile<<"( "<<getHygiene(stateNow)<<" "<<getEnergy(stateNow)<<" "<<getFun(stateNow)<<" )"<<", ,";
                for (int l = 0; l<=17; ++l){
                    if (tabelTransisi[stateNow][l]!=-1){
                        myfile<<"( "<<getHygiene(tabelTransisi[stateNow][l])<<" "<<getEnergy(tabelTransisi[stateNow][l])<<" "<<getFun(tabelTransisi[stateNow][l])<<" )"<<",";
                    }
                    else{
                        myfile<<",";
                    }
                }
                myfile<<"\n";
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    memset(tabelTransisi,-1,sizeof(tabelTransisi)); //inisialisasi
    stateGenerator(0);
    //writeToCsv();     // cukup dilakukan 1 kali saja


}
