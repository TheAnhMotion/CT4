#include <iostream>
#include <vector>

using namespace std;

class TaxableItem {
public:
    virtual double CalculateTax() = 0;
    virtual ~TaxableItem() {}
};


class BookTax : public TaxableItem {
private:
    double price;
public:
    BookTax(double p) {
        price = p;
    }

    double CalculateTax() {
        return price * 0.05;
    }
};


class ElectronicsTax : public TaxableItem {
private:
    double price;
public:
    ElectronicsTax(double p) {
        price = p;
    }

    double CalculateTax() {
        return price * 0.1; 
    }
};


class TaxableItemFactory {
public:
    virtual TaxableItem* CreateItem(double price) = 0;
    virtual ~TaxableItemFactory() {}
};


class BookFactory : public TaxableItemFactory {
public:
    TaxableItem* CreateItem(double price) {
        return new BookTax(price);
    }
};


class ElectronicsFactory : public TaxableItemFactory {
public:
    TaxableItem* CreateItem(double price) {
        return new ElectronicsTax(price);
    }
};


class TaxCalculator {
public:
    double CalculateTotalTax(const vector<TaxableItem*>& items) {
        double total = 0.0;
        for (size_t i = 0; i < items.size(); ++i) {
            total += items[i]->CalculateTax();
        }
        return total;
    }
};


int main() {
    vector<TaxableItem*> items;

    BookFactory bookFactory;
    ElectronicsFactory electronicsFactory;

    double bookPrice, electronicsPrice;

    cout << "Nhap gia sach: ";
    cin >> bookPrice;
    cout << "Nhap gia dien tu: ";
    cin >> electronicsPrice;

    items.push_back(bookFactory.CreateItem(bookPrice));        
    items.push_back(electronicsFactory.CreateItem(electronicsPrice));  

    TaxCalculator calculator;
    double totalTax = calculator.CalculateTotalTax(items);

    cout << "Tong tien thue: " << totalTax << endl;

    for (size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }

    return 0;
}

