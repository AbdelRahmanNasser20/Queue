#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated Node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue<T>& operator= (Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  void Push(const T&);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front 
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  bool IsEmpty();
  // Name: size
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  int size();
  // Name: Find()
  // Preconditions: Requires a lqueue
  // Postconditions: Iterates through lqueue and if it finds the thing, returns index, else -1
  int Find(T&);
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  void Clear();
  //Name: Overloaded [] operator
  //Precondition: Existing Lqueue
  //Postcondition: Returns object from Lqueue using []
  //Desc: Iterates to node x and returns data from Lqueue
  T& operator[] (int x);//Overloaded [] operator to pull data from Lqueue
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};
//***********IMPLEMENT LQUEUE HERE***********************
template <class T>
Lqueue<T>::Lqueue(){
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

// desturcter 
template <class T>
Lqueue<T>::~Lqueue(){
    Node <T> *temp = m_head;

    while (m_head != nullptr){
        temp = m_head->GetNext();
        delete m_head;
        m_head = temp;
    }
    // sets the points to null ptr
    m_head = nullptr;
    m_tail = nullptr;
    // check to see if its an issue
    temp = nullptr;
    m_size = 0;
}

template <class T>
Lqueue<T>::Lqueue(const Lqueue& source){
  // intalize variables
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
    // create a node to iterate through the LL
    Node <T> *curr = source.m_head;
    
    while (curr != nullptr){

        //push the curr data into the new LL
        Push(curr->GetData());

        curr = curr->GetNext();//iterate the curr LL
    }
    
}


template <class T>
Lqueue<T>& Lqueue<T>::operator= (Lqueue& source){
    m_size = 0;

    // create a node to iterate through the LL
    Node <T> *curr = source.m_head;
    
    while (curr != nullptr){

        //push the curr data into the new LL
        Push(curr->GetData());

        curr = curr->GetNext();//iterate the curr LL
    }
    return *this;

}

template <class T>  
void Lqueue<T>::Push(const T& data){
    Node <T> *nodeToAdd = new Node<T>(data);
    
    if (IsEmpty() == true){
        m_head = nodeToAdd;
        m_tail = nodeToAdd;
        m_size++;
        return;
    }
    
    Node <T> *curr = m_head;
    // dynmancally alocate a new node while passing in a data
    while (curr->GetNext() != nullptr){
        // curr->SetNext(curr->GetNext());
        curr = curr->GetNext();
    }
    curr->SetNext(nodeToAdd);
    nodeToAdd->SetNext(nullptr);
    m_tail = nodeToAdd;
    m_size++;
    
}

template <class T>  
T Lqueue<T>::Pop(){
    T data;
    Node <T> *temp = m_head;
    data = temp->GetData();
    // remove the first node 
    if (m_size == 1){
      // dellocate m_head and set head and tail to nullptr
        delete m_head;
        m_tail = nullptr;
        m_head = nullptr;
    }
    // remove the first node and get the data
    else if (m_size > 1){
      m_head = temp->GetNext();  
      delete temp;
    }
    m_size--;
    return data;
}
template <class T>
void Lqueue<T>::Display(){
    Node <T> *temp = m_head;
    while (temp != nullptr){
        cout << temp->GetData() << " -> ";
        temp = temp->GetNext();
    }
    cout << "END" << endl;
}

template <class T>  
T Lqueue<T>::Front(){return m_head->GetData();}

template <class T>
bool Lqueue<T>::IsEmpty(){
    if (m_head == nullptr){
        return true;
    }
    return false;
}

template <class T>
int Lqueue<T>::size(){return m_size;}

template <class T>
int Lqueue<T>::Find(T& node){
    
    // if Lqueue is empty return -1
    if (m_head == nullptr){
        return -1;
    }
    int index = 0;
    Node <T> *temp = m_head;
    
    // transverse the LL
    while (temp != nullptr){
        
        // if the data match return the index
        if (temp->GetData() == node){
            return index;
        }
        temp = temp->GetNext();
        index++;
    }
    return -1;
}

template <class T>
void Lqueue<T>::Swap(int index){
    // if the size of the leque is less then two or it wants so swap the last index it will return nothing
    if (m_size <= 1 or index == 0 or index >= m_size){
        cout << "cant swap " << endl;
        return;
    }
    
    Node <T>* next;
    
    // swaps the first node with the second node
    if (index == 1){

        // sets the nodes place holders to the first and second node
        Node <T>* prev = m_head;
        Node <T>* curr = prev->GetNext(); 
        
        m_head = curr; // set the head to the second node
        next = m_head->GetNext(); // tempory holds the next node which is the third node
        
        // change the first two nodes next to their corrosponding next
        curr->SetNext(prev); 
        prev->SetNext(next);
        
        cout << "rotated the first node" << endl;
        return;
    }
    
    // initalize the nodes used
    Node <T>* curr = m_head;    
    Node <T>* prev;
    Node <T>* ancorPrior;
    
    // iterates through the lqueue 
    for (int i = 1; i < m_size; i++){
        
        // gets the two previous nodes from the current node we are swapping
        ancorPrior = prev;
        prev = curr;
        curr = curr->GetNext();
        
        // if we find the node we want to swap
        if (i == index){
            
            next = curr->GetNext();   
            
            // changes the location of the nodes
            ancorPrior->SetNext(curr);
            curr->SetNext(prev);
            prev->SetNext(next);
        
            // if we are swapping the last node
            if (index == m_size -1){
                m_tail = prev; // set the tail to the new last node 
            }
        }
    
    }
    
}

template <class T>
T& Lqueue<T>::operator[] (int x){
    Node <T> *temp = m_head;
    int i = 0;
    while (temp != nullptr and (i != x)){
        temp = temp->GetNext();
        i++;
    }
    return temp->GetData();
    
}

template <class T>
void Lqueue<T>::Clear(){
    
    Node <T> *temp = m_head;
    // iterates the Lqueue and deletes each node
    while (m_head != nullptr){
        temp = m_head->GetNext();
        delete m_head;
        m_head = temp;
    }
    // sets the points to null ptr
    m_head = nullptr;
    m_tail = nullptr;
    // check to see if its an issue
    temp = nullptr;
    m_size = 0;
}

#endif
