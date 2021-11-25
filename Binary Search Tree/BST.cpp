#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *left, *right;
};

class BinTree{
    private:
        Node *root;
    public:
        BinTree();
        ~BinTree();        
        void add();
        void addNode(Node **, int);
        void inOrder();
        void preOrder();
        void postOrder();
        void printInOrder(Node *);
        void printPreOrder(Node *);
        void printPostOrder(Node *);
        Node** minValue(Node **);
        Node** maxValue(Node **);
        void buscar();
        void search(Node *, int);
        void eliminar();
        void deleteNode(Node **, int);
};

BinTree::BinTree(){ root = nullptr; }

BinTree::~BinTree(){ cout << "\nDestructor..."; }

void BinTree::add(){
    int n; bool end=false;

    cout << "AGREGANDO DATOS...\n(ingrese 'n' para terminar/cancelar)\n";
    do{
        cout << "Dato: ";
        if(!(cin >> n))
            end = true;    
        else{
            addNode(&root, n); cin.ignore(); }
    } while (end!=true);
    cin.clear();    // IMPORTANT: don't forget cin.clear() to avoid loop
    return;
}

void BinTree::addNode(Node **p, int n){
    if(!(*p)){
        *p = new Node;
        (*p)->data = n;
        (*p)->left = (*p)->right = nullptr;
    } else {
        if(n < (*p)->data)
            addNode(&(*p)->left, n);
        else
            if(n > (*p)->data)
                addNode(&(*p)->right, n);
            else
            cout << "~ La llave ya esta en el arbol ~\n";
    }
}

void BinTree::inOrder(){ printInOrder(root); }

void BinTree::printInOrder(Node *p){ // L N R
    if(p){
        printInOrder(p->left);
        cout << p->data << " ";
        printInOrder(p->right);
    }
}

void BinTree::preOrder(){ printPreOrder(root); }

void BinTree::printPreOrder(Node *p){ // N L R
    if(p){
        cout << p->data << " ";
        printPreOrder(p->left);
        printPreOrder(p->right);
    }
}

void BinTree::postOrder(){ printPostOrder(root); }

void BinTree::printPostOrder(Node *p){ // L R N
    if(p){
        printPostOrder(p->left);
        printPostOrder(p->right);
        cout << p->data << " ";
    }
}

Node** BinTree::minValue(Node **p){
    Node **current = p;

    while((*current) && (*current)->left != nullptr)
        (*current) = (*current)->left;

    return current;
}

Node** BinTree::maxValue(Node **p){
    Node **current = p;

    while((*current) && (*current)->right != nullptr)
        (*current) = (*current)->right;

    return current;
}

void BinTree::eliminar(){ 
    int n=0;

    cout << "Dato a eliminar: "; cin >> n;
    deleteNode(&root, n);
}

void BinTree::deleteNode(Node **p, int n){
    if(*p){
        if(n == (*p)->data){
            if((*p)->left == nullptr && (*p)->right == nullptr){
                Node *c = *p;
                *p = nullptr;
                return;
            }

            if((*p)->left == nullptr || (*p)->right == nullptr){
                Node *c = *p;
                Node *child = ((*p)->left==nullptr) ? (*p)->right:(*p)->left; // existing son takes over father position
                (*p) = child; 
                delete(c); 
                return;
            }

            Node **m = minValue(&(*p)->right);
            (*p)->data = (*m)->data;
            deleteNode(&(*m), (*m)->data);
            return;

        } else
            if(n < (*p)->data)
                deleteNode(&(*p)->left, n);
            else
                deleteNode(&(*p)->right, n);
    } else
        cout << "~ La llave no esta en el arbol ~\n";
}

void BinTree::buscar(){
    int n=0;

    cout << "Dato a buscar: "; cin >> n;
    search(root, n);
}

void BinTree::search(Node *p, int n){
    if(!p)
        cout << "~ La llave no esta el arbol ~\n";
    else
        if(n < p->data)
            search(p->left, n);
        else if(n > p->data)
            search(p->right, n);
        else cout << "La llave esta en el arbol.";
}

int main(){
    BinTree bt; int r=0;

    do{
        cout << "\nARBOLITO BINARIO uwu\n\n";

        cout << "1- Agregar datos \n2- Mostrar InOrden \n3- Mostrar PreOrden \n4- Mostrar PostOrden \n";
        cout << "5- Eliminar dato \n6- Buscar un dato \n7- Salir\n";
        cout << "-> "; cin >> r;

        switch(r){ 
            case 1:cout<<endl; 
                bt.add(); cin.ignore(); // IMPORTANT: don't forget cin.ignore() to avoid loop
                break;     
            case 2: cout<<endl<<"InOrden\n"; 
                bt.inOrder(); cout<<endl;
                break;

            case 3: cout<<endl<<"PreOrden\n";
                bt.preOrder(); cout<<endl;
                break;

            case 4: cout<<endl<<"PostOrden\n";
                bt.postOrder(); cout<<endl;
                break;

            case 5: 
                bt.eliminar(); cout<<endl;
                break;

            case 6:
                bt.buscar(); cout<<endl;

            case 7: break;

            default: cout << "~ Ingrese una opcion valida ~\n";
        } 
    } while(r!=7);   
}