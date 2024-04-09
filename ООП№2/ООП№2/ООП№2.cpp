
#include <iostream>
#include <cmath>

using namespace std;

class Polynomial {
private:
    int size;
    double* mas;
public:
    Polynomial();
    Polynomial(int);
    Polynomial(Polynomial&);
    Polynomial(Polynomial&&) noexcept;
    Polynomial(double*, int);

    double& operator[](int) const;
    friend ostream& operator<<(ostream&, const Polynomial&);
    friend istream& operator>>(istream&, Polynomial&);
    operator double* () const;

    bool operator==(const Polynomial&);
    bool operator!=(const Polynomial&);
    bool operator>(const Polynomial&);
    bool operator<(const Polynomial&);
    bool operator>=(const Polynomial&);
    bool operator<=(const Polynomial&);

    Polynomial& operator=(const Polynomial&);
    Polynomial& operator=(Polynomial&&) noexcept;

    Polynomial operator+(Polynomial);
    Polynomial operator-(Polynomial);
    Polynomial operator+(double);
    Polynomial operator*(double);
    double operator()(double);

    ~Polynomial();
};

Polynomial::Polynomial() :size(0) {

    mas = new double[2];
    mas[0] = 0;
    mas[1] = 0;
}

Polynomial::Polynomial(int s) : size(s) {
    if (s <= 0)abort();
    mas = new double[size];
    for (int i = 0; i < size; i++)
        mas[i] = 0;
}

Polynomial::Polynomial(Polynomial& p) : size(p.size) {
    mas = new double[size];
    for (int i = 0; i < size; i++)
        mas[i] = p.mas[i];
}

Polynomial::Polynomial(Polynomial&& p) noexcept : size(p.size), mas(p.mas) {
    p.mas = NULL;
}

Polynomial::Polynomial(double* m, int s) : size(s) {
    if (s <= 0)abort();
    mas = new double[size];
    for (int i = 0; i < size; i++)
        mas[i] = m[i];
}

double& Polynomial :: operator[](int i) const {
    if ((i < 0) || (i > size - 1)) abort();
    return mas[i];
}

ostream& operator<<(ostream& out, const Polynomial& p) {
    out << "( ";
    for (int i = 0; i < p.size; i++) {

        if (p.mas[i] != 0) {
            if (i == 0) {
                out << p.mas[i];
            }
            else if (p.mas[i - 1] == 0 && p.mas[i - 1] == p.mas[0]) {
                out << p.mas[i] << "x";
            }
            else if (i == 1) {
                if (p.mas[i] > 0)
                    out << " + " << p.mas[i] << "x";
                else
                    out << " - " << -p.mas[i] << "x";
            }
            else if (i > 1) {
                if (p.mas[i] > 0)
                    out << " + " << p.mas[i] << "x^" << i;
                else
                    out << " - " << -p.mas[i] << "x^" << i;
            }
        }
    }
    out << " )" << endl;   
    return out;
}

istream& operator>>(istream& in, Polynomial& p) {
    in >> p.size;
    p.mas = new double[p.size];
    for (int i = 0; i < p.size; i++)
        in >> p.mas[i];
    return in;
}

Polynomial:: operator double* () const {
    return mas;
}

bool Polynomial:: operator==(const Polynomial& p) {
    if (size != p.size)
        return false;
    
    for (int i = 0; i < size; i++) {
        if (mas[i] != p.mas[i])
            return false;
    }
    return true;

}

bool Polynomial:: operator!=(const Polynomial& p) {
    return !(*this == p);
}
   
bool Polynomial:: operator>(const Polynomial& p) {
    if (*this != p) {
        if (size > p.size)
            return true;

        else if (size == p.size && mas[size-1] > p.mas[size-1])
            return true;
    }
    return false;
    
}

bool Polynomial:: operator<(const Polynomial& p) {
    if (*this != p)
        return !(*this > p);
}

bool Polynomial:: operator>=(const Polynomial& p) {
    return (*this > p || *this == p);
}

bool Polynomial:: operator<=(const Polynomial& p){
    return (*this < p || *this == p);
}

Polynomial& Polynomial :: operator=(const Polynomial& p) {
    if (this == &p) return *this;
    if (size != p.size) abort();
    for (int i = 0; i < size; i++)
        mas[i] = p.mas[i];
    return *this;
}

Polynomial& Polynomial :: operator=(Polynomial&& p) noexcept {
    if (this == &p) return *this;
    if (size != p.size) abort();
    mas = p.mas;
    p.mas = NULL;
    return *this;
}

Polynomial Polynomial :: operator+(Polynomial p) {
    int maxSize = max(size, p.size);
    Polynomial result(maxSize);

    for (int i = 0; i < maxSize; i++) {       
        result.mas[i] = mas[i] + p.mas[i];
    }
    return result;
}

Polynomial Polynomial :: operator-(Polynomial p) {
    int maxSize = max(size, p.size);
    Polynomial result(maxSize);
    
    for (int i = 0; i < maxSize; i++) {
        double coeff1 = (i <= size) ? mas[i] : 0;
        double coeff2 = (i <= p.size) ? p.mas[i] : 0;
        result.mas[i] = coeff1 - coeff2;
    }
    
    return result;
}

Polynomial Polynomial :: operator+(double num) {
    Polynomial result(size);
   
    for (int i = 0; i < size; i++) {
        result.mas[0] = mas[0] + num;
        result.mas[i + 1] = mas[i + 1];
    }

    return result;
}

Polynomial Polynomial :: operator*(double num) {
    Polynomial result(size);

    for (int i = 0; i < size; i++) {
        result.mas[i] = mas[i] * num;
    }
    return result;

}

double Polynomial :: operator()(double x) {
    double result = 0;
    for (int i = 0; i < size; i++) {
        result += mas[i] * pow(x, i);
    }
    return result;
}
    
Polynomial :: ~Polynomial() {
    delete[]mas;
} 

int main()
{
    
    double array1[3] = { 11, 3.2, -4 };

    Polynomial  p1, p2(array1, 3), p3(3);
    cin >> p1;

    cout <<"P1: "<< p1 << endl;     
    cout << "P2: " << p2 << endl;
    cout << "First element P1: " << p1[0] << endl;     
    
    double* d1 = (double*)p1;
    cout << "Mas P1: ";
    for (int i = 0; i < 3; i++) {
        cout << d1[i] << " ";
    }
    cout << endl;

    cout << "Comparison of P1 and P2: " << endl;
    cout << "==: " << (p1 == p2) << endl;
    cout << "!=: " << (p1 != p2) << endl;   
    cout << ">: " << (p1 > p2) << endl;    
    cout << "<: " << (p1 < p2) << endl;   
    cout << ">=: " << (p1 >= p2) << endl;   
    cout << "<=: " << (p1 <= p2) << endl; 

    p3[0] = p2[1];
    cout << "First element P3 (is equal 2nd element P2): " << p3[0] << endl;

    Polynomial p4 = p1;
    cout << "P4 (is equal P1): " << p4;    

    Polynomial P1(p1 + p2);
    Polynomial P2(p1 - p2);
    Polynomial P3(p1 * 2);
    Polynomial P4(p1 + 2);
    double d = p1(2);

    cout << "Sum P1 and P2: "<< P1;       
    cout << "Difference P1 and P2: " << P2;
    cout << "Scalar multiplication P1 by 2: " << P3;
    cout << "Add 2 to P1: " << P4;    
    cout << "Value of P1 at (x = 2): "<< d;
   
    return 0;

}

