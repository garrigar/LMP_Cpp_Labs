#include <iostream>
using namespace std;

class LinkedList{
	
// private member
private:
    // Struct inside the class LinkedList
    // This is one node which is not needed by the caller. It is just
    // for internal work.
    struct Node {
        int x;
        Node *next;
    };
	
	Node *head; // this is the private member variable. It is just a pointer to the first Node

// public member
public:
    // constructor
    LinkedList(){
        head = NULL; // set head to NULL
    }																

    // destructor
    ~LinkedList(){
        Node *next = head;

        while(next) {              // iterate over all elements
            Node *deleteMe = next;
            next = next->next;     // save pointer to the next element
            delete deleteMe;       // delete the current entry
        }
    }

    // This prepends a new value at the beginning of the list
    void addValue(int val){
        Node *n = new Node();   // create new Node
        n->x = val;             // set value
        n->next = head;         // make the node point to the next node.
                                //  If the list is empty, this is NULL, so the end of the list --> OK
        head = n;               // last but not least, make the head point at the new node.
    }
    
};

int main() {
    LinkedList list;

    list.addValue(5);

    return 0;
}

#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>

struct Node
{
    Node* next;
    int key;
    int key2;

    Node( int key, int key2 )
        : key(key), key2(key2), next()
    {}
};

Node * createList(size_t N)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(1,10);

    Node *root = nullptr;
    Node **pp = &root;
    for (int i=0; i<N; ++i)
    {
        *pp = new Node(dist(rng), i+1);
        pp = &(*pp)->next;
    }
    return root;
}

void freeList(Node *& root)
{
    while (root)
    {
        Node *tmp = root;
        root = tmp->next;
        delete tmp;
    }
}

void printList(const Node* root)
{
    for (;root;root = root->next)
        std::cout << root->key << '(' << root->key2 << ") ";
    std::cout << '\n';
}

// quicksort a linked list.
void quickSort(Node *&root)
{
    // trivial lists are just returned immediately
    if  (!root || !(root->next))
        return;

    Node *lhs = nullptr, **pplhs = &lhs;
    Node *rhs = nullptr, **pprhs = &rhs;
    Node *pvt = root;
    root = root->next;
    pvt->next = nullptr;

    while (root)
    {
        if (root->key < pvt->key)
        {
            *pplhs = root; // tack on lhs list end
            pplhs = &(*pplhs)->next;
        }
        else
        {
            *pprhs = root; // tack on rhs list end
            pprhs = &(*pprhs)->next;
        }
        root = root->next;
    }

    // terminate both list. note that the pivot is still
    //  unlinked, and will remain so until we merge
    *pplhs = *pprhs = nullptr;

    // invoke on sublists.
    quickSort(lhs);
    quickSort(rhs);

    // find end of lhs list, slip the pivot into  position, then 
    //  tack on the rhs list.
    while (*pplhs)
        pplhs = &(*pplhs)->next;
    *pplhs = pvt;
    pvt->next = rhs;

    // set final output
    root = lhs;
}

int main()
{
    Node *root = createList(20);
    printList(root);
    quickSort(root);
    printList(root);
    freeList(root);
    return 0;
}