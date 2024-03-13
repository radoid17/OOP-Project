#include <iostream>
#include <cmath>
using namespace std;


class Punct {
    public:
        int x, y;

        //constructor de initializare fara parametri
        Punct() 
        { 
            this -> x = 0; 
            this -> y = 0;
        }

        //constructor de initializare cu parametri
        Punct (float x, float y): x(x), y(y) {}

        //functie de aflare a distantei
        static float distanta(const Punct& a, const Punct& b) 
        {
            return sqrt(pow(b.x - a.x, 2) + (pow(b.y - a.y, 2)));
        }

        //constructor copiere
        Punct(Punct &p) 
        {
            x = p.x; 
            y = p.y;
        }

        //destructor
        ~Punct(){}

        //operatorul=
        Punct &operator=(const Punct& p) 
        {
            x = p.x;
            y = p.y;
            return *this;
        }

        //operatorul>>
        friend istream& operator>>(istream& in, Punct &p) 
        {
            in >> p.x;
            in >> p.y;
            return in;      
        }

        //operatorul<<
        friend ostream& operator<<(ostream& out, Punct &p) 
        {
            out << p.x;
            out << p.y;
            return out;
        }
};

class Patrat {
    protected:
        Punct stanga_jos;
        float latura;

    public:
        int valid;
        
    public:
        //constructor de initializare fara parametri
        Patrat() 
        { 
            this -> latura = 0;
        }

        //constructor de initializare cu parametri
        Patrat (Punct stanga_jos, float latura): stanga_jos(stanga_jos), latura(latura), valid(1){}
        
        //functie de aflare a ariei
        template <typename T>
        T arie() 
        { 
            return latura * latura; 
        }

        //constructor copiere
        Patrat(Patrat &p) 
        {
            stanga_jos = p.stanga_jos; 
            latura = p.latura;
        }

        //destructor
        ~Patrat(){}

        //operatorul=
        Patrat &operator=(const Patrat& p) 
        {
            stanga_jos = p.stanga_jos;
            latura = p.latura;
            return *this;
        }

        //operatorul>>
        friend istream& operator>>(istream& in, Patrat &p) 
        {
            in >> p.stanga_jos;
            in >> p.latura;
            return in;      
        }

        //operatorul<<
        friend ostream& operator<<(ostream& out, Patrat &p) 
        {
            out << p.stanga_jos;
            out << p.latura;
            return out;
        }
};

class Dreptunghi : virtual public Patrat 
{
    private:
        float latura2;

    public:

        //constructor de initializare fara parametri
        Dreptunghi() 
        { 
            this -> latura2 = 0;
        }
        
        //constructor de initializare cu parametri
        Dreptunghi (Punct stanga_jos, float latura, float latura2): Patrat(stanga_jos, latura), latura2(latura2){}
        
        //functie de aflare a ariei
        template <typename T>
        T arie() 
        {
            if(latura == latura2)
            {
                return 0;
            }
            return latura * latura2; 
        }

        //constructor copiere
        Dreptunghi(Dreptunghi &p) 
        {
            latura2 = p.latura2;
        }

        //destructor
        ~Dreptunghi(){}

        //operatorul=
        Dreptunghi &operator=(const Dreptunghi& p) 
        {
            latura2 = p.latura2;
            return *this;
        }

        //operatorul>>
        friend istream& operator>>(istream& in, Dreptunghi &p) 
        {
            in >> p.latura2;
            return in;      
        }

        //operatorul<<
        friend ostream& operator<<(ostream& out, Dreptunghi &p) 
        {
            out << p.latura2;
            return out;
        }
};

class Romb : virtual public Patrat 
{
    private:
        Punct dreapta_sus, dreapta_jos, stanga_sus;

    public:

        //constructor de initializare fara parametri
        Romb(){}

        //constructor de initializare cu parametri
        Romb (Punct stanga_jos, Punct colt_opus, float latura): 
            Patrat(stanga_jos, latura), 
            dreapta_sus(colt_opus),
            dreapta_jos(stanga_jos.x + latura, stanga_jos.y),
            stanga_sus(colt_opus.x - latura, colt_opus.y)
        {
            // Punctul din stanga_jos si cel din dreapta_jos trebuie sa fie pe o linie paralela cu Ox
            // Ne asiguram ca laturile rombului au lungimi egale
            valid = (Punct::distanta(stanga_sus, colt_opus) == latura) && (Punct::distanta(stanga_jos, stanga_sus) == latura);
        }

        //functie de aflare a ariei
        template <typename T>
        T arie() 
        {
            if(valid != 1)
            {
                return 0;
            }
            return Punct::distanta(stanga_jos, dreapta_sus) * Punct::distanta(stanga_sus, dreapta_jos) / 2;
        }

        //constructor copiere
        Romb(Romb &p) 
        {
            dreapta_jos = p.dreapta_jos;
            dreapta_sus = p.dreapta_sus;
            stanga_sus = p.stanga_sus;
        }

        //destructor
        ~Romb(){}

        //operatorul=
        Romb &operator=(const Romb& p) 
        {
            dreapta_jos = p.dreapta_jos;
            dreapta_sus = p.dreapta_sus;
            stanga_sus = p.stanga_sus;
            return *this;
        }

        //operatorul>>
        friend istream& operator>>(istream& in, Romb &p) 
        {
            in >> p.dreapta_jos;
            in >> p.dreapta_sus;
            in >> p.stanga_sus;
            return in;      
        }

        //operatorul<<
        friend ostream& operator<<(ostream& out, Romb &p) 
        {
            out << p.dreapta_jos;
            out << p.dreapta_sus;
            out << p.stanga_sus;
            return out;
        }
};

class Paralelogram : public Dreptunghi, public Romb 
{
    private:
        Punct dreapta_sus, dreapta_jos, stanga_sus;

    public:
        //constructor de initializare fara parametri
        Paralelogram(){}

        Paralelogram(Punct stanga_jos, Punct colt_opus, float latura, float latura2):
            Patrat(stanga_jos, latura),
            Dreptunghi(stanga_jos, latura, latura2),
            Romb(stanga_jos, colt_opus, latura),

            dreapta_sus(colt_opus),
            dreapta_jos(stanga_jos.x + latura, stanga_jos.y),
            stanga_sus(colt_opus.x - latura, colt_opus.y)
        {
            valid = (Punct::distanta(stanga_sus, colt_opus) == latura2) && (Punct::distanta(stanga_jos, stanga_sus) == latura2);
        }

        //functie de aflare a ariei
        template <typename T>
        T arie() 
        {
            if(valid != 1)
            {
                return 0;
            }
            return (stanga_sus.y - stanga_jos.y) * Punct::distanta(stanga_jos, dreapta_jos);
        }

        //constructor copiere
        Paralelogram(Paralelogram &p) 
        {
            dreapta_jos = p.dreapta_jos;
            dreapta_sus = p.dreapta_sus;
            stanga_sus = p.stanga_sus;
        }

        //destructor
        ~Paralelogram(){}

        //operatorul=
        Paralelogram &operator=(const Paralelogram& p) 
        {
            dreapta_jos = p.dreapta_jos;
            dreapta_sus = p.dreapta_sus;
            stanga_sus = p.stanga_sus;
            return *this;
        }

        //operatorul>>
        friend istream& operator>>(istream& in, Paralelogram &p) 
        {
            in >> p.dreapta_jos;
            in >> p.dreapta_sus;
            in >> p.stanga_sus;
            return in;      
        }

        //operatorul<<
        friend ostream& operator<<(ostream& out, Paralelogram &p) 
        {
            out << p.dreapta_jos;
            out << p.dreapta_sus;
            out << p.stanga_sus;
            return out;
        }
};


int main()
{
    /*
    Patrat p(Punct {0, 0}, 5.0);
    cout << "Aria patratului este " << p.arie() << "\n";
    
    Dreptunghi d(Punct {0, 0}, 5.0, 3.0);
    cout << "Aria dreptunghiului este " << d.arie() << "\n";
    
    Romb r(Punct(0, 0), Punct(5, 5), 5);
    cout << "Aria rombului este " << r.arie() << "\n";

    Paralelogram pa(Punct(0, 0), Punct(5, 5), 5, 5);
    cout << "Aria paralelogramului este " << pa.arie() << "\n";
    */

    int tasta;

    cout << "Pentru a accesa programul de aflare a ariei unei forme geometrice apasati tasta 1.\n";
    cin >> tasta;
    if(tasta == 1)
    {
        cout << "Pentru aflarea ariei unui patrat, apasati tasta 1.\n";
        cout << "Pentru aflarea ariei unui dreptunghi, apasati tasta 2.\n";
        cout << "Pentru aflarea ariei unui romb, apasati tasta 3.\n";
        cout << "Pentru aflarea ariei unui paralelogram, apasati tasta 4.\n";
        cout << "Pentru aflarea ariei unui trapez, apasati tasta 5.\n";
        cin >> tasta;

        if(tasta == 1)
        {
            float x, y, l;
            cout << "Introduciti coordonatele urmatoare:\n";
            cout << "x = "; cin >> x;
            cout << "y = "; cin >> y;
            cout << "lungime = "; cin >> l;
            Patrat p(Punct {x, y}, l);
            cout << "Aria patratului este " << p.arie<float>() << "\n";
        }
        if(tasta == 2)
        {
            float x, y, l, h;
            cout << "Introduciti coordonatele urmatoare:\n";
            cout << "x = "; cin >> x;
            cout << "y = "; cin >> y;
            cout << "Introduceti lungimile urmatoare:\n";
            cout << "lungime = "; cin >> l;
            cout << "latime = "; cin >> h;
            Dreptunghi d(Punct {x, y}, l, h);
            if(d.arie<float>() != 0)
            {
                cout << "Aria dreptunghiului este " << d.arie<float>() << "\n";
            }
            else
            {
                cout << "Coordonatele nu sunt valide\n";
            }
        }
        if(tasta == 3)
        {   
            float x1, y1, x2, y2, l; 
            cout << "Introduciti coordonatele urmatoare:\n";
            cout << "x = "; cin >> x1;
            cout << "y = "; cin >> y1;
            cout << "Introduciti coordonatele urmatoare:\n";
            cout << "x = "; cin >> x2;
            cout << "y = "; cin >> y2;
            cout << "lungime = "; cin >> l;
            Romb r(Punct(x1, y1), Punct(x2, y2), l);
            if(r.arie<float>() != 0)
            {
                cout << "Aria rombului este " << r.arie<float>() << "\n";
            }
            else
            {
                cout << "Coordonatele nu sunt valide\n";
            }
        }
        if(tasta == 4)
        {
            float x1, y1, x2, y2, l, h; 
            cout << "Introduciti coordonatele urmatoare:\n";
            cout << "x = "; cin >> x1;
            cout << "y = "; cin >> y1;
            cout << "Introduciti coordonatele urmatoare:\n";
            cout << "x = "; cin >> x2;
            cout << "y = "; cin >> y2;
            cout << "lungime = "; cin >> l;
            cout << "Inaltime = "; cin >> h;
            Paralelogram pa(Punct(x1, y1), Punct(x2, y2), l, h);
            cout << "Aria paralelogramului este " << pa.arie<float>() << "\n";
        }
        if(tasta == 5)
        {
            cout << "Programul inca nu este gata. Sa aveti o zi frumoasa!\n";
        }
        
    }
    else
    {
        cout << "Programul nu a fost accesat. Sa aveti o zi frumoasa!\n";
    }

    return 0;
}