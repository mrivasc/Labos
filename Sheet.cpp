#include <iostream>
using namespace std;

/*De acuerdo al código visto en el último laboratorio, éste se debe modificar para que en lugar de sumar filas 
pueda sumar columnas, es decir el ejercicio 8 de la guía de Hoja Electrónica.*/

void menu();

struct Node{
    int nRow, nCol;
    Node *nextRow, *nextCol;
    int data;
};

class Sheet{
    private:
        int totRow, totCol;
        Node *head;
    public:
        Sheet(int, int);
        //~Sheet();
        void insertNode();
        void print();
        void deleteNode(int, int);
        void sumRow(int);
        void sumCol(int);
};

Sheet::Sheet(int totRow, int totCol){
    Node *nw, *p;
    head = new Node;
    
    this->totRow = totRow;  // total of rows provided by user
    this->totCol = totCol;  // same with columns
    head->nRow = 0;         
    head->nCol = 0;         
    head->nextRow = head;
    head->nextCol = head;
    head->data = 0;

    // Base row creation
    p = head;
    for(int i=1 ; i<=totCol ; i++){
        nw = new Node;
        p->nextCol = nw;
        nw->nRow = 0;       // we're in the same row. this won't change
        nw->nCol = i;       // what is going to change, is n of columns
        nw->data = 0;
        nw->nextRow = nw;
        p = p->nextCol;
    } nw->nextCol = head;

    // Base column creation
    p = head;
    for(int j=1 ; j<=totRow ; j++){
        nw = new Node;
        p->nextRow = nw;
        nw->nRow = j;
        nw->nCol = 0;
        nw->data = 0;
        nw->nextCol = nw;
        p = p->nextRow;
    } nw->nextRow = head;
}

void Sheet::insertNode(){
    int row=0, col=0;

    do{
        cout << "Insertando dato... (finalice ingresando 0, 0)\n";
        cout << " Fila: "; cin >> row;
        cout << " Columna: "; cin >> col;

        if(row>=1 && row<=totRow && col>=1 && col<=totCol){
            Node *nw = new Node;
            Node *pRow = head, *pCol = head;

            cout << " Entero: "; cin >> nw->data;
            nw->nRow = row;
            nw->nCol = col;

            for(int i=1 ; i<=row ; i++)
                pRow = pRow->nextRow;
            while(pRow->nextCol->nCol < col && pRow->nextCol->nCol != 0)
                pRow = pRow->nextCol;

            for(int j=1 ; j<=col ; j++)
                pCol = pCol->nextCol;
            while(pCol->nextRow->nRow < row && pCol->nextRow->nRow != 0)
                pCol = pCol->nextRow;
            
            nw->nextCol = pRow->nextCol;
            pRow->nextCol = nw;

            nw->nextRow = pCol->nextRow;
            pCol->nextRow = nw;
            cout << "El nodo se ha insertado.\n\n";
        } 
        else
            cout << "-- Ubicacion no valida --\n\n";
    } while (row!=0 && col!=0);
}

void Sheet::deleteNode(int row, int col){
    Node *pRow = head, *pCol = head, *pDelete = nullptr;
    
    for(int i=1; i<=row; i++)
        pRow = pRow->nextRow;
    while((pRow->nextCol->nCol < col) && (pRow->nextCol->nCol != 0)) // Avanzando sobre fila
        pRow = pRow->nextCol;

    // Localización de la posición sobre la columna. El puntero que salta sobre la col queda apuntando al nodo anterior.
    for(int j=1; j<=col; j++) // Avanzando sobre fila base
        pCol = pCol->nextCol;
    while((pCol->nextRow->nRow < row) && (pCol->nextRow->nRow != 0)) // Bajando sobre columna
        pCol = pCol->nextRow;
    
    // Desenlazar el nodo de la estructura y borrarlo
    pDelete = pRow->nextCol; // Verificar si el nodo existe
    pRow->nextCol = pRow->nextCol->nextCol;
    pCol->nextRow = pCol->nextRow->nextRow;

    delete pDelete;
    cout << "El nodo ha sido borrado\n\n";
}

void Sheet::sumRow(int row){
    Node *p=head;
    do{
        if(p->nRow == row){
            int sum=0;
            do{
               sum += p->data;
               p = p->nextCol;
            } while (p->nCol != 0);
            cout <<"Suma de la fila "<< row <<": "<< sum << endl << endl;
            break;
        }
        p = p->nextRow;
    }while(p->nRow != 0);
}

void Sheet::sumCol(int col){
    Node *p=head;
    do{
        if(p->nCol == col){
            int sum=0;
            do{
               sum += p->data;
               p = p->nextRow;
            } while (p->nRow != 0);
            cout <<"Suma de la columna "<< col <<": "<< sum << endl << endl;
            break;
        }
        p = p->nextCol;
    }while(p->nCol != 0);
}

void Sheet::print(){
    Node *p=head;

    cout << "\nFormato [fila columna dato]\n\n";

    do{
        do{ // printing first column
            cout << "[" << p->nRow << " " << p->nCol << " " << p->data << "]\t";
            p = p->nextCol;
        } while (p->nCol != 0); // continues until it finds 0 (to stop)
        cout << endl;
        p = p->nextRow; // jumping to the next row to print column again
    } while (p->nRow != 0);
    cout<<endl;
}

int main(){ menu(); }

void menu(){
    int r=0, totRow=0, totCol=0, row=0, col=0; bool cont=true;

    do{
        cout << "\nHOJA DE CALCULO\n\n";
        cout << "Total de filas: "; cin >> totRow; 
        cout << "Total de columnas: "; cin >> totCol; cin.ignore(); cout<<endl<<endl;

        if(totRow == 0 || totCol == 0)
            cout << "-- Ingrese una cantidad valida --\n";
    } while(totRow == 0 || totCol == 0);

    Sheet S(totRow, totCol);
    do{
        cout << "1. Ingresar dato \n2. Eliminar dato \n3. Mostrar hoja \n4. Suma de fila \n5. Suma de columna \n6. Salir \n";
        cout << "-> "; cin >> r; cout<<endl;

        switch(r){
            case 1: S.insertNode();
                break;

            case 2: 
                cout << "Ingrese la fila y columna que contiene el dato a eliminar...\n";
                cout << "Fila: "; cin >> row;
                cout << "Columna: "; cin >> col; cout<<endl;
                S.deleteNode(row, col);
                break;

            case 3: S.print();
                break;

            case 4: 
                cout << "Fila a sumar: "; cin >> row; cout<<endl;
                S.sumRow(row);
                break;

            case 5: 
                cout << "Columna a sumar: "; cin >> col; cout<<endl;    
                S.sumCol(col);
                break;

            case 6: cont = false;
                break;

            default:
                cout << "-- Ingrese una opcion valida --\n\n";
        }
    } while(cont);
}