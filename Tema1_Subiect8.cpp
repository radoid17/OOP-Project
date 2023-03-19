#include <iostream>
#include <cstring>
using namespace std;

class IntSet{
    private:
        int *vector, size;

    public:
        
        //constructor de initializare fara parametri
        IntSet() 
        { 
            cout << "constructorul de initializare fara parametri\n";
            this -> size = 0; 
            this -> vector = nullptr;
        }

        //constructor de initializare cu parametri
        IntSet(int size, int *vector) 
        {
            cout << "S-a apelat constructorul de initializare cu parametri\n";
            this->vector = new int[size];

            int position_in_set = 0;

            // verificam daca avem elemente care se repeta pentru a transforma vectorul intr-o multime matematica 
            for (int i = 0; i < size; i++) 
            {
                bool found_in_vector = false;
                for (int j = 0; j < position_in_set; j++) 
                {
                    if (this -> vector[j] == vector[i]) 
                    {
                        found_in_vector = true;
                    }
                }

                if (!found_in_vector) 
                {
                    this -> vector[position_in_set] = vector[i];
                    position_in_set ++;
                }
            }

            this -> size = position_in_set;
        }

        //functie de adaugat elemente
        void add(int element) 
        {
            cout << "S-a apelat fuctia de adaugat elemente\n";
            bool found_in_vector = false;
            for (int i = 0 ; i < size; i ++) 
            {
                if (vector[i] == element) // verificam daca elementul pe care il adaugam este in multime
                {
                    found_in_vector = true;
                }
            }

            if (found_in_vector)
            {
                return;
            }

            int* arr = new int[size + 1]; // creem un vector nou care o sa ia valoarile vechiului vector
            memcpy(arr, vector, sizeof(int) * size); // folosim functia memcpy pentru a copia elementele lui vector in arr
            arr[size] = element; // adaugam elementul nou pe ultima pozitie

            delete[] vector; // stergem vectorul
            vector = arr; // vector ia valorile noi multimi din arr
            size += 1; // marimea vectorului creste
        }

        //functie de afisare
        void print() 
        {
            for (int i = 0; i < this->size; i++) 
            {
                cout << this -> vector[i] << " ";
            }
            cout << "\n";
        }


        //constructor de copiere
        IntSet(const IntSet &v) 
        {
            cout << "S-a apelat constructotul de copiere\n";
            size = v.size;
            vector = new int[size];
            memcpy(vector, v.vector, sizeof(int) * size);
        }

        //operatorul=
        IntSet &operator=(const IntSet& v) 
        {
            size = v.size;
        
            delete vector;
            vector = new int[size];

            for (int i = 0 ; i < size ; i ++)
            {
                vector[i] = v.vector[i];
            }

            return *this;
        }

        ~IntSet() 
        {
            cout << "S-a apelat destructorul\n";
            delete[] vector;
        }

        // Nu folosim setterul din cauza ca daca userul schimba size-ul fara sa modifice vectorul o sa avem o eroare
        // Exemplu: vector - {1, 2, 3} -> {1, 1, 3}

        //getter
        int getSize()
        {
            return size;
        }

        const int* getVector()
        {
            return vector;
        }

        //operatorul>>
        friend istream& operator>>(istream& in, IntSet &v) 
        {
            in >> v.size;
            v.vector = new int[v.size];
            for(int i = 0 ; i < v.size ; i ++)
            {
                in >> v.vector[i];
            }
            return in;      
        }

        //operatorul<<
        friend ostream& operator<<(ostream& out, IntSet &v) 
        {
            for(int i = 0 ; i < v.size ; i ++)
            {
                out << v.vector[i] << " ";
            }
            return out;
        }

        //functie de eliminat elemente
        void remove(int element)
        {
            cout << "S-a apelat functia de eliminat elemente\n";
            bool found_in_vector = false;
            for (int i = 0 ; i < size; i ++) 
            {
                if (vector[i] == element) //verificam daca elementul se afla sau nu in multime
                {
                    found_in_vector = true;
                }
                if(found_in_vector == true)
                {
                    if(i < size - 1)//inlocuim elementul cu cel care urmeaza daca este unul in fata
                    {
                        vector[i] = vector[i + 1];
                    }
                    else
                    {
                        size -= 1;// daca elementul este pe ultima pozitie, acesta este eliminat
                    }    
                }     
            }

            if (found_in_vector == false)
            {
                cout << "Elementul " << element << " nu este in multime\n";
            }
            else
            {
                cout << "Elementul " << element << " este in multime\n";
            }
        }

        //operatorul +
        IntSet operator+(IntSet& other) 
        {   
            // luam un set gol pentru a adauga elemente in el
            IntSet reuniune(*this);

            // folosim getter-ul pentru a obtine lungimea si elementele vectorilor pe care o sa ii folosim
            int other_size = other.getSize();
            const int *other_elems = other.getVector();

            for (int i = 0; i < other_size; i++) // parcurgem vectorul
            {
                reuniune.add(other_elems[i]);
            }

            return reuniune;
        }

        //operatorul -
        IntSet operator-(IntSet& other)
        {
            // luam un set gol pentru a adauga elemente in el
            IntSet diferenta(*this);
            
            // folosim getter-ul pentru a obtine lungimea si elementele vectorilor pe care o sa ii folosim
            int other_size = other.getSize(); 
            const int *other_elems = other.getVector();

            for(int i = 0 ; i < other_size; i ++) // parcurgem vectorul
            {
                diferenta.remove(other_elems[i]);
            }

            return diferenta;
        }

        int in(int element) // creem o functie care verifica daca elementul unui vector se afla in alt vector (vom folosi functia in operatorul*)
        {
            bool found_in_vector = false;
            for (int i = 0 ; i < size; i ++) 
            {
                if (vector[i] == element) // verificam daca elementul pe care il adaugam este in multime
                {
                    found_in_vector = true;
                }
            }

            return found_in_vector; // returnam adevarat sau fals
        }

        IntSet operator*(IntSet& other)
        {
            // luam un set gol pentru a adauga elemente in el
	        IntSet intersectie;

            // folosim getter-ul pentru a obtine lungimea si elementele vectorilor pe care o sa ii folosim
	        int other_size = other.getSize();
            const int *other_elems = other.getVector();

	        for (int i = 0; i < other_size; ++i) // parcurgem vectorul
            {
		        if (in(other_elems[i])) // verificam daca elementele dintr-un sir se afla in celalalt
                {
			        intersectie.add(other_elems[i]); // adaugam elementele in intersectie
		        }
	        }

	        return intersectie;
        }
};

int main()
{
    int arr[] = {1, 2, 3, 1, 4};

    IntSet set1(5, arr);

    set1.print();

    set1.add(3);
    set1.add(5);

    set1.print();

    cout << set1.getSize() << "\n";
    cout << set1.getVector()[0] << "\n";

    IntSet set2(set1);

    set1.add(9);
    set2.add(7);

    set1.print();
    set2.print();

    IntSet set3;
    set3 = set2;

    set3.add(11);
    set2.add(23);

    cout << set3 << "\n";
    cout << set2 << "\n";

    IntSet reuniune;
    reuniune = set2 + set3;
    cout << set2 << "+ " << set3 << "= " << reuniune << "\n";

    set2.remove(13);
    set2.print();

    set2.remove(5);
    set2.print();

    IntSet diferenta;
    diferenta = set3 - set2;
    cout << set3 << "- " << set2 << "= " << diferenta << "\n";

    IntSet intersectie = set3 * set2;
    cout << set2 << "* " << set3 << "= " << intersectie << "\n";

    return 0;
}
