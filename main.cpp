#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#define MIN_TABLE_SIZE 10

using namespace std;

//node status declaration

enum Hashentry {
        
    freeslot, empty, deletedslot
        
};

//node declaration

struct Node

{

    int element;

    enum Hashentry status;

};

//table declaration

struct HashTable

{

    int size;

    Node *table;

};

//check if next size is prime or not

bool isPrime (int n)

{

    if (n == 2 || n == 3)

        return true;

    if (n == 1 || n % 2 == 0)

        return false;

    for (int i = 3; i * i <= n; i += 2)

        if (n % i == 0)

            return false;

    return true;

}

//find next prime size of the table

int nextPrime(int n)

{

    if (n <= 0)

        n == 3;

    if (n % 2 == 0)

        n++;

    for (; !isPrime( n ); n += 2);

    return n;

}

//hash

int Hashing(int key, int size)

{

    return key % size;

}

//add element

HashTable *createTable(int size)

{

    HashTable *ctable;

    if (size < MIN_TABLE_SIZE)

    {

        cout<<"Table Size Too Small"<<endl;

        return NULL;

    }

    ctable = new HashTable;

    if (ctable == NULL)

    {

        cout<<"Out of Space"<<endl;

        return NULL;

    }

    ctable->size = nextPrime(size);

    ctable->table = new Node [ctable->size];

    if (ctable->table == NULL)

    {

        cout<<"Table Size Too Small"<<endl;

        return NULL;

    }

    for (int i = 0; i < ctable->size; i++)

    {

        ctable->table[i].status = empty;

        ctable->table[i].element = NULL;

    }

    return ctable;

}

//find element

int Findelement(int key, HashTable *ctable)

{

    int position = Hashing(key, ctable->size);

    int collisions = 0;

    while (ctable->table[position].status != empty && ctable->table[position].element != key)

    {

        position = position + 2 * ++collisions -1;
            
        if (position >= ctable->size)

            position = position - ctable->size;

    }

    return position;

}

//enter element

void Insertelement(int key, HashTable *ctable)

{

    int position = Findelement(key, ctable);

    if (ctable->table[position].status != freeslot)

    {

        ctable->table[position].status = freeslot;

        ctable->table[position].element = key;

    }

}

//rehash table

HashTable *Rehashtable(HashTable *ctable)

{

    int size = ctable->size;

    Node *table = ctable->table;

    ctable = createTable(2 * size);

    for (int i = 0; i < size; i++)
    {

        if (table[i].status == freeslot)

            Insertelement(table[i].element, ctable);

    }

    free(table);

    return ctable;

}

//display table

void Displaytable(HashTable *ctable)

{

    for (int i = 0; i < ctable->size; i++)

    {

        int value = ctable->table[i].element;

        if (!value)

            cout<<"Position: "<<i + 1<<" Element: Null"<<endl;

        else

            cout<<"Position: "<<i + 1<<" Element: "<<value<<endl;

    }

}

//Menu

int main()

{

    int value, size, position, i = 1;

    int choice;

    HashTable *ctable;

    while(1)

    {

        cout << endl << "====================" <<endl;

        cout<<"1.CREATE TABLE"<<endl;

        cout<<"2.ADD ELEMENT"<<endl;

        cout<<"3.DISPLAY HASH TABLE"<<endl;

        cout<<"4.REHASH THE TABLE"<<endl;

        cout<<"5.EXIT"<<endl<<endl;

        cout<<"TYPE TASK: ";

        cin>>choice;
            
        switch(choice)

        {

        case 1:

            cout<<"Enter the size of the Hash Table: ";

            cin>>size;

            ctable = createTable(size);

            cout<<"Size of Hash Table: "<<nextPrime(size);
                
            break;

        case 2:

            if (i > ctable->size)

            {

                cout<<"Table is Full, please rehash the table!"<<endl;

                continue;

            }

            cout<<"Enter element: ";

            cin>>value;

            Insertelement(value, ctable);

            i++;
                
            break;

        case 3:

            Displaytable(ctable);
                
            break;

        case 4:

            ctable = Rehashtable(ctable);
                
            break;

        case 5:

            exit(1);

        default:

            cout<<"\nInvalid answer. Try again!\n";

        }
        if(choice == 3){
               
        }
        else{
            system("clear");
        }
            
    }
        
    return 0;

}
