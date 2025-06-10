#include <iostream>
using namespace std;

// Interface TaxableItem
class TaxableItem {
public:
    virtual double CalculateTax() const = 0;
    virtual ~TaxableItem() {}
};

// Class TaxBook
class TaxBook : public TaxableItem {
private:
    double price;

public:
    TaxBook(double price) : price(price) {}

    double CalculateTax() const {
        return price * 0.2;
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

    double CalculateTax() const {
        return price * 0.5;
    }

    double CalculateTaxElectronics() const {
        return CalculateTax();
    }
};

// Class Calculate
class Calculate {
private:
    const TaxBook* tb;
    const TaxElectronics* te;

public:
    Calculate() : tb(0), te(0) {}

    double Calculator(const TaxableItem* t) {

        const TaxBook* book = dynamic_cast<const TaxBook*>(t);
        if (book) {
            tb = book;
            return calculateBook();
        }

        const TaxElectronics* electronics = dynamic_cast<const TaxElectronics*>(t);
        if (electronics) {
            te = electronics;
            return calculateTaxElectronics();
        }

        cerr << "Unsupported item type" << endl;
        return 0.0;
    }

    double calculateBook() const {
        return tb->CalculateTaxBook();
    }

    double calculateTaxElectronics() const {
        return te->CalculateTaxElectronics();
    }
};

// Main function
int main() {
    TaxBook book(120.0);
    TaxElectronics electronics(500.0);

    Calculate calc;

    double tax1 = calc.Calculator(&book);
    double tax2 = calc.Calculator(&electronics);

    cout << "Book Tax: $" << tax1 << endl;
    cout << "Electronics Tax: $" << tax2 << endl;
    cout << "Total Tax: $" << (tax1 + tax2) << endl;

    return 0;
}

