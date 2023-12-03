
template <typename T>
class QueueNode
{
public:
    T data;
    QueueNode<T> *next;

    QueueNode()
    {
        next = nullptr;
    }

    QueueNode(T data)
    {
        this->data = data;
        next = nullptr;
    }
};

template <typename T>
class PriorityQueue
{
    int size;
    QueueNode<T> *front, *tail;

public:
    PriorityQueue()
    {
        front = nullptr;
        tail = nullptr;
        size = 0;
    }

    void enqueue(T data)
    {
        size++;
        if (front == nullptr)
        {
            front = new QueueNode<T>(data);
            return;
        }

        else if (front != nullptr && tail == nullptr)
        {
            tail = new QueueNode<T>(data);
            front->next = tail;
            return;
        }

        QueueNode<T> *newNode = new QueueNode<T>(data);
        tail->next = newNode;
        tail = newNode;
        sortPriorityQueue();
    }

    void dequeue()
    {
        if (front == nullptr)
            return;

        size--;
        QueueNode<T> *temp = front;
        if (front->next)
            front = front->next;
        else
            front = nullptr;

        delete temp;
    }

    T showFront()
    {
        return this->front->data;
    }

    T &showBack()
    {
        return this->tail->data;
    }

    bool isEmpty()
    {
        // returns true if the queue is empty, else false
        return size == 0;
    }

    void printQueue()
    {
        QueueNode<T> *temp = this->front;
        while (temp)
        {
            std::cout << temp->data << " -- ";
            temp = temp->next;
        }

        std::cout << '\n';
    }

    int getSize()
    {
        return this->size;
    }

    void sortPriorityQueue()
    {
        QueueNode<T> *temp = this->front;
        while (temp)
        {
            QueueNode<T> *temp2 = temp->next;
            while (temp2)
            {
                if (temp->data > temp2->data)
                {
                    T tempData = temp->data;
                    temp->data = temp2->data;
                    temp2->data = tempData;
                }
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
    }

    void UpdatePriorityQueue(T data)
    {
        // assuming that its a pair of distance and vertex id
        QueueNode<T> *temp = front;
        while (temp != nullptr)
        {
            if (temp->data.second == data.second)
            {
                temp->data.first = data.first;
            }
            temp = temp->next;
        }
    }
};