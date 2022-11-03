//Proiect Algoritmi Fundamentali , Tudor Vladut-Alexandru, Info1, Grupa 5

#include <iostream> //Librarie standard pentru input si output in C++
#include <queue> //Este o structura de date care urmareste principiul FIFO(First In First Out)
                 //in care primele elemente adaugate sunt si primele elemente sterse din lista
#include <string> //Librarie pentru a stoca sirurile de caractere
using namespace std;

class coduriHuffman //Implementam o structura de date numita clasa
{
    struct Nod //Cream un nod pentru Arbore
    {
        char data='\0'; //Initializam sirul
        size_t frecventa = 0; //Initializam frecventa
        Nod* stanga; //Folosim un pointer pentru stanga nodului
        Nod* dreapta; //Folosim un pointer pentru dreapta nodului
        Nod(char data, size_t frecventa) : data(data),frecventa(frecventa),stanga(nullptr),dreapta(nullptr){} //Alocam un nou nod in Arbore
        ~Nod()
        {
            delete stanga;
            delete dreapta;
        }
    };
    struct comparam //O structura pentru a compara si a ordona caracterele
    {
        bool operator()(Nod* st, Nod* dr)
        {
            return (st->frecventa > dr->frecventa);
        }
    };
    Nod* top; //Ne asiguram ca avem o variabila top care este un pointer la Nod
    void printareCod(Nod* root, string str) //O functie pentru a printa codurile
    {
        if(root==nullptr) //Null Pointer Value
            return;
        if(root->data == '$')
        {
            printareCod(root->stanga,str+"0");
            printareCod(root->dreapta,str+"1");
        }
        if(root->data != '$')
        {
            cout<<root->data<<" : "<<str<<"\n";
            printareCod(root->stanga,str+"0");
            printareCod(root->dreapta,str+"1");
        }
    }
public:
    coduriHuffman(){};
    ~coduriHuffman()
    {
        delete top;
    }
    void generareCod(vector<char>& data,vector<size_t>& frecventa,size_t size) //Generam codurile Huffman
    {
        Nod* stanga;
        Nod* dreapta;
        priority_queue<Nod*, std::vector<Nod*>,comparam>minHeap; //Sortam caracterele in functie de prioritate
        for(size_t i=0;i<size;++i)
        {
            minHeap.push(new Nod(data[i],frecventa[i]));
        }
        while(minHeap.size() != 1)
        {
            stanga=minHeap.top();
            minHeap.pop();
            dreapta=minHeap.top();
            minHeap.pop();
            top=new Nod('$', stanga->frecventa+dreapta->frecventa);
            top->stanga=stanga;
            top->dreapta=dreapta;
            minHeap.push(top);
        }
        printareCod(minHeap.top(), "");
    }
};

int main() //Implementam in functia main codul
{
    coduriHuffman generator;
    printf("Codurile Huffman sunt:\n");
    vector<char>data({'i', 'n', 'f', 'o', 'r', 'm', 'a', 't', 'c'});
    vector<size_t>frecventa({2,1,1,1,1,1,2,1,1});
    size_t size=data.size();
    generator.generareCod(data, frecventa, size);
    return 0;
}
