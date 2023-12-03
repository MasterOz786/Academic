
/*
    Mohammad Hassaan Ejaz
    i222434
    SE - B
    Ms. Shahela Saif
*/

#include <iostream>
#include "LL.hpp"

template <typename T>
LL<T>::LL()
{
    head = nullptr;
    tail = nullptr;
}

// use O(1) to insert at the front of the list using list's head
template <typename T>
void LL<T>::insertAtFront(T data)
{
    if (head != nullptr && head->next == nullptr && tail == nullptr)
    {
        tail = head;
    }

    Node<T> *newNode = new Node<T>(data);
    newNode->next = head;
    newNode->prev = nullptr;
    head = newNode;
}

// O(1) insertion using tail
template <typename T>
void LL<T>::insertAtEnd(T data)
{
    Node<T> *newNode = new Node<T>(data);

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    else if (tail == nullptr)
    {
        newNode->next = nullptr;
        newNode->prev = head;
        head->next = newNode;
        tail = newNode;
        return;
    }

    newNode->prev = tail;
    newNode->next = nullptr;
    tail->next = newNode;
    tail = newNode;
}

// O(n) insertion using head
template <typename T>
void LL<T>::insertAfter(Node<T> *reqNode, T data)
{
    Node<T> *newNode = new Node<T>(data);
    newNode->next = nullptr;

    // if the list is empty, update the head
    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    // if the tail is the node to insert after then the operation is O(1)
    else if (tail != nullptr && tail->data == data)
    {
        insertAtEnd(data);
        return;
    }

    // O(n) traversal of list to find the node and then update the pointers respectively
    Node<T> *cur = head;
    while (cur)
    {
        if (cur->data == data)
        {
            newNode->next = cur->next;
            cur->next->prev = newNode;
            cur->next = newNode;
            newNode->prev = cur;
            return;
        }
        cur = cur->next;
    }

    std::cout << "\nData was non-existent in the list, can't insert after it!\n"
              << std::endl;
}

// takes care of unique insertion
// special case for objects, == operator needs to be overloaded for classes
template <typename T>
void LL<T>::insertUnique(T data)
{
    // first check if the node exists
    Node<T> *cur = head;
    while (cur)
    {
        if (cur->data == data)
        {
            return;
        }
        cur = cur->next;
    }

    // if the data is unique, insert at tail
    insertAtEnd(data);
}

// pop the head
template <typename T>
void LL<T>::deleteFront()
{
    if (head == nullptr)
    {
        std::cout << "\nList is empty, can't delete from it!\n"
                  << std::endl;
        return;
    }

    // if we delete from the tail then there was a problem that the tail becomes equal to head so
    // updating the tail and head respectively
    else if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }

    // normal case, delete from head
    Node<T> *temp = head;
    head = head->next;
    head->prev = nullptr;
    delete temp;
}

template <typename T>
void LL<T>::deleteTail()
{
    if (head == nullptr)
    {
        std::cout << "\nList is empty, can't delete from it!\n"
                  << std::endl;
        return;
    }

    else if (tail == nullptr)
    {
        std::cout << "\nCan't delete from the list, the tail is empty!\n"
                  << std::endl;
        return;
    }

    // if we kept on deleting tail, it became similar to head
    // so had to update the head and tail respectively
    else if (tail == head)
    {
        delete tail;
        head = nullptr;
        tail = nullptr;
        return;
    }

    Node<T> *temp = tail;
    tail = tail->prev;
    tail->next = nullptr;

    delete temp;
}

// traverse and find the node whcih matches the data
template <typename T>
void LL<T>::deleteNode(T data)
{
    if (head == nullptr)
    {
        std::cout << "\nList is empty, can't delete from it!\n"
                  << std::endl;
        return;
    }
    else if (head->data == data)
    {
        deleteFront();
        return;
    }
    else if (tail->data == data)
    {
        deleteTail();
        return;
    }

    // traversal here
    Node<T> *cur = head;
    while (cur)
    {
        if (cur->data == data)
        {
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            delete cur;

            return;
        }
        cur = cur->next;
    }

    std::cout << "\nThe required node in the list doesn't exist!\n";
}

template <typename T>
Node<T> *LL<T>::searchNode(T data)
{
    if (head->data == data)
    {
        return head;
    }

    else if (tail->data == data)
    {
        return tail;
    }

    Node<T> *temp = head;
    while (temp)
    {
        if (temp->data == data)
        {
            break;
        }

        temp = temp->next;
    }

    return temp;
}

template <typename T>
void LL<T>::swap(Node<T> *n1, Node<T> *n2)
{
    // if the nodes are same
    if (n1 == n2)
    {
        return;
    }

    // Update the 'prev' pointers
    Node<T> *tempPrev = n1->prev;
    n1->prev = n2->prev;
    n2->prev = tempPrev;

    if (n1->prev)
    {
        n1->prev->next = n1;
    }

    if (n2->prev)
    {
        n2->prev->next = n2;
    }

    // Update the 'next' pointers
    Node<T> *tempNext = n1->next;
    n1->next = n2->next;
    n2->next = tempNext;

    if (n1->next)
    {
        n1->next->prev = n1;
    }
    if (n2->next)
    {
        n2->next->prev = n2;
    }

    // Update the head and tail pointers
    if (n1 == head)
    {
        head = n2;
    }
    else if (n2 == head)
    {
        head = n1;
    }

    if (n1 == tail)
    {
        tail = n2;
    }
    else if (n2 == tail)
    {
        tail = n1;
    }
}

template <typename T>
void LL<T>::UpdatePosition(int pos, int data)
{
    Node<T> *cur = head;
    while (cur)
    {
        if (cur->data == data)
        {
            cur->data = pos;
            return;
        }
        cur = cur->next;
    }
}

template <typename T>
void LL<T>::printList() const
{
    Node<T> *cur = head;
    while (cur)
    {
        std::cout << cur->data;
        cur = cur->next;
    }
    std::cout << '\n';
}

template <typename T>
void LL<T>::bubbleSort()
{
    if (head == nullptr)
    {
        std::cout << "\nList is empty, can't be sorted!\n";
        return;
    }

    Node<T> *cur1 = head;
    while (cur1)
    {
        bool swapped = false;
        Node<T> *cur2 = head;

        while (cur2)
        {
            if (cur2->next && cur2->data > cur2->next->data)
            {
                swap(cur2, cur2->next);
                swapped = true;
            }
            cur2 = cur2->next;
        }
        // if the list is already sorted, the variable would remain unchecked
        // best case, the loop runs only once
        if (!swapped)
        {
            return;
        }

        cur1 = cur1->next;
    }
}

template <typename T>
void LL<T>::insertionSort()
{
    Node<T> *cur1 = head;

    while (cur1->next)
    {
        if (cur1->data > cur1->next->data)
        {
            Node<T> *cur2 = cur1;
            while (cur2->prev)
            {
                if (cur2->data > cur2->prev->data)
                {
                    swap(cur2, cur2->prev);
                }

                if (cur2->prev)
                    cur2 = cur2->prev;
                else
                    break;
            }
        }
        cur1 = cur1->next;
    }
}

// template <typename T>
// LL<T>::~LL()
// {
//     delete head;
//     delete tail;

//     head = nullptr;
//     tail = nullptr;
// }

// operator overloading
std::ostream &operator<<(std::ostream &out, Vertex &vertex)
{
    // method calls the print for the edges in the vertex
    out << vertex.id;
    return out;
}

// // needed to print the Edges on cout
std::ostream &operator<<(std::ostream &out, Edge &edge)
{
    out << edge.dest << ' ';
    return out;
}
