#include <iostream>

class TaxableItem {
public:
    virtual double calculateTax() const = 0;
    virtual ~TaxableItem() {}
};

class Tax_Book : public TaxableItem {
private:
    double price;
    double taxPercent;
public:
    void setPrice(double p) { price = p; }
    void setTaxPercent(double t) { taxPercent = t; }
    double calculateTax() const { return price * taxPercent; }
};

class Tax_Electronics : public TaxableItem {
private:
    double price;
    double taxPercent;
public:
    void setPrice(double p) { price = p; }
    void setTaxPercent(double t) { taxPercent = t; }
    double calculateTax() const { return price * taxPercent; }
};

class Builder {
public:
    virtual void reset() = 0;
    virtual void setPrice(double price) = 0;
    virtual void setTaxPercent(double taxPercent) = 0;
    virtual ~Builder() {}
};

class Tax_Book_Builder : public Builder {
private:
    Tax_Book* book;
public:
    Tax_Book_Builder() { book = new Tax_Book(); }
    ~Tax_Book_Builder() { delete book; }
    void reset() {
        delete book;
        book = new Tax_Book();
    }
    void setPrice(double price) {
        book->setPrice(price);
    }
    void setTaxPercent(double percent) {
        book->setTaxPercent(percent);
    }
    Tax_Book* getResult() const {
        return book;
    }
};

class Tax_Electronics_Builder : public Builder {
private:
    Tax_Electronics* electronics;
public:
    Tax_Electronics_Builder() { electronics = new Tax_Electronics(); }
    ~Tax_Electronics_Builder() { delete electronics; }
    void reset() {
        delete electronics;
        electronics = new Tax_Electronics();
    }
    void setPrice(double price) {
        electronics->setPrice(price);
    }
    void setTaxPercent(double percent) {
        electronics->setTaxPercent(percent);
    }
    Tax_Electronics* getResult() const {
        return electronics;
    }
};

class Director {
public:
    void makeTaxComics(Builder* builder) {
        builder->reset();
        builder->setPrice(120.0);
        builder->setTaxPercent(0.05);
    }

    void makeTaxComputer(Builder* builder) {
        builder->reset();
        builder->setPrice(1000.0);
        builder->setTaxPercent(0.2);
    }
};

class TaxCalculator {
public:
    double calculateTotalTax(TaxableItem* items[], int size) {
        double total = 0.0;
        for (int i = 0; i < size; ++i) {
            total += items[i]->calculateTax();
        }
        return total;
    }
};

int main() {
    Director director;

    Tax_Book_Builder* bookBuilder = new Tax_Book_Builder();
    director.makeTaxComics(bookBuilder);
    Tax_Book* book = bookBuilder->getResult();

    Tax_Electronics_Builder* electronicsBuilder = new Tax_Electronics_Builder();
    director.makeTaxComputer(electronicsBuilder);
    Tax_Electronics* electronics = electronicsBuilder->getResult();

    TaxableItem* items[2] = { book, electronics };

    TaxCalculator calculator;
    std::cout << "Tong thue: " << calculator.calculateTotalTax(items, 2) << std::endl;

    delete bookBuilder;
    delete electronicsBuilder;

    return 0;
}

