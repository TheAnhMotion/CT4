#include <iostream>
#include <vector>

class TaxableItem {
public:
    virtual double calculateTax() = 0;
    virtual ~TaxableItem() {}
};

class ITaxCal {
public:
    virtual double calculatorTax() = 0;
    virtual ~ITaxCal() {}
};

class Tax_Book : public TaxableItem {
private:
    double price;
    double TaxPercent;

public:
    Tax_Book(double price, double taxPercent) : price(price), TaxPercent(taxPercent) {}

    double calculateTax() {
        return price * TaxPercent;
    }

    ~Tax_Book() {}
};

class Tax_Electronics : public TaxableItem {
private:
    double price;
    double TaxPercent;

public:
    Tax_Electronics(double price, double taxPercent) : price(price), TaxPercent(taxPercent) {}

    double calculateTax() {
        return price * TaxPercent;
    }

    ~Tax_Electronics() {}
};

class CalTaxBook : public ITaxCal {
private:
    Tax_Book* taxBook;

public:
    CalTaxBook(Tax_Book* taxBook) : taxBook(taxBook) {}

    double calculatorTax() {
        return taxBook->calculateTax();
    }

    ~CalTaxBook() {
        delete taxBook;
    }
};

class CalTaxElectronics : public ITaxCal {
private:
    Tax_Electronics* taxElectronics;

public:
    CalTaxElectronics(Tax_Electronics* taxElectronics) : taxElectronics(taxElectronics) {}

    double calculatorTax() {
        return taxElectronics->calculateTax();
    }

    ~CalTaxElectronics() {
        delete taxElectronics;
    }
};

class TaxCalculator {
public:
    double calculateTotal(const std::vector<ITaxCal*>& items) {
        double total = 0.0;
        for (std::vector<ITaxCal*>::const_iterator it = items.begin(); it != items.end(); ++it) {
            total += (*it)->calculatorTax();
        }
        return total;
    }

    ~TaxCalculator() {}
};

int main() {
    Tax_Book* tb = new Tax_Book(10, 0.1);
    Tax_Electronics* tE = new Tax_Electronics(500, 0.5);
    Tax_Electronics* tE1 = new Tax_Electronics(510, 0.5);

    CalTaxBook* tbCal = new CalTaxBook(tb);
    CalTaxElectronics* tECal = new CalTaxElectronics(tE);
    CalTaxElectronics* tECal1 = new CalTaxElectronics(tE1);

    std::vector<ITaxCal*> items;
    items.push_back(tbCal);
    items.push_back(tECal);
    items.push_back(tECal1);

    TaxCalculator calculator;
    double totalTax = calculator.calculateTotal(items);

    std::cout << "T?ng Thu?: " << totalTax << std::endl;

    for (std::vector<ITaxCal*>::iterator it = items.begin(); it != items.end(); ++it) {
        delete *it;
    }

    return 0;
}
