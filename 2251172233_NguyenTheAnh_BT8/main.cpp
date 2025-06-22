#include <iostream>
using namespace std;

// Interface TaxableItem
class TaxableItem {
public:
    virtual double CalculateTax() const = 0;
    virtual void notify(TaxableItem* sender, double tax) = 0;
    virtual ~TaxableItem() {}
};

// Class TaxBook
class TaxBook : public TaxableItem {
private:
    double price;

public:
    TaxBook(double price) : price(price) {}

    double CalculateTax() const override {
        return price * 0.2;
    }

    void notify(TaxableItem* sender, double tax) override {
        if (sender != this) {
            cout << "Thuế sách được tính là $" << tax << endl;
        }
    }

    double CalculateTaxBook() const {
        return CalculateTax();
    }
};

// Class TaxElectronics
class TaxElectronics : public TaxableItem {
private:
    double price;

public:
    TaxElectronics(double price) : price(price) {}

    double CalculateTax() const override {
        return price * 0.5;
    }

    void notify(TaxableItem* sender, double tax) override {
        if (sender != this) {
            cout << "Thuế điện tử được tính là $" << tax << endl;
        }
    }

    double CalculateTaxElectronics() const {
        return CalculateTax();
    }
};

// Mediator Class Calculate
class Calculate {
private:
    TaxBook* tb;
    TaxElectronics* te;

public:
    Calculate() : tb(nullptr), te(nullptr) {}

    void setTaxBook(TaxBook* book) {
        tb = book;
    }

    void setTaxElectronics(TaxElectronics* electronics) {
        te = electronics;
    }

    double Calculator(TaxableItem* item) {
        if (item == nullptr) {
            cout << "Đối tượng không hợp lệ" << endl;
            return 0.0;
        }

        double tax = item->CalculateTax();
        if (tb && item == dynamic_cast<TaxableItem*>(tb)) {
            if (te) te->notify(item, tax);
            return tb->CalculateTaxBook();
        }
        if (te && item == dynamic_cast<TaxableItem*>(te)) {
            if (tb) tb->notify(item, tax);
            return te->CalculateTaxElectronics();
        }
        cout << "Loại đối tượng không được hỗ trợ" << endl;
        return 0.0;
    }
};

// Main function
int main() {
    TaxBook book(120.0);
    TaxElectronics electronics(500.0);

    Calculate calc;
    calc.setTaxBook(&book);
    calc.setTaxElectronics(&electronics);

    double tax1 = calc.Calculator(&book);
    double tax2 = calc.Calculator(&electronics);

    cout << "Thuế Sách: $" << tax1 << endl;
    cout << "Thuế Điện Tử: $" << tax2 << endl;
    cout << "Tổng Thuế: $" << (tax1 + tax2) << endl;

    return 0;
}
