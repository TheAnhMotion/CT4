#include <iostream>
#include <vector>
using namespace std;

class TaiKhoanNganHang {
private:
    string soTaiKhoan;
    double soDu;

public:
    TaiKhoanNganHang(string soTK, double soDuBanDau) {
        soTaiKhoan = soTK;
        soDu = soDuBanDau;
    }

    string getSoTaiKhoan() const {
        return soTaiKhoan;
    }

    double getSoDu() const {
        return soDu;
    }

    bool rutTien(double soTien) {
        if (soTien <= soDu) {
            soDu -= soTien;
            cout << "? Rut tien thanh cong. So du con lai: " << soDu << " VND" << endl;
            return true;
        } else {
            cout << "Rut tiun that bai" << endl;
            return false;
        }
    }
};

class GiaoDich {
private:
    double soTien;
    TaiKhoanNganHang* taiKhoan;  

public:
   
    GiaoDich(double soTien, TaiKhoanNganHang* taiKhoan) {
        this->soTien = soTien;
        this->taiKhoan = taiKhoan;
    }

    void thucHienGiaoDich() {
        if (taiKhoan == NULL) {
            cout << "Giao dich that bai. Tai khoan khong ton tai!" << endl;
            return;
        }

        cout << "So tai khoan: " << taiKhoan->getSoTaiKhoan() << endl;
        cout << "So du hien tai: " << taiKhoan->getSoDu() << " VND" << endl;

        if (taiKhoan->rutTien(soTien)) {
            cout << "?? Giao dich hoan tat!" << endl;
        } else {
            cout << "Giao dich khong thuc hien duoc!" << endl;
        }
    }
};

int main() {
    string soTaiKhoan;
    double soDu;

    
    cout << "Nhap so tai khoan: ";
    cin >> soTaiKhoan;
    cout << "Nhap so du hien tai: ";
    cin >> soDu;

    TaiKhoanNganHang taiKhoan(soTaiKhoan, soDu);

    double soTienRut;
    cout << "nhap so tien can rut: ";
    cin >> soTienRut;

    GiaoDich giaoDich(soTienRut, &taiKhoan);
    giaoDich.thucHienGiaoDich();

    return 0;
}

