#ifndef TEAMLIST_H
#define TEAMLIST_H

template<typename T>
class TeamNode
{
public:
    // Node data
    T data;
    TeamNode<T>* next;

    // Node constructor
    TeamNode(T data) : data{data}, next{nullptr} { }
};

template<typename T>
class TeamList
{
public:
    // Default constructor
    TeamList(): head{nullptr} { }

    // Insert function
    // O(N) where N is the length of the list
    void insert(T data)
    {
        // Create the new node
        TeamNode<T>* newNode = new TeamNode<T>(data);

        if (head == nullptr)
        {
            // If the list is empty, then make newNode the head
            head = newNode;
        } else {
            // Else add newNode to the end of the list

            // Iterate through the list until we reach the end
            TeamNode<T>* currentNode = head;
            while (currentNode->next != nullptr)
            {
                currentNode = currentNode->next;
            }

            // Reached the end, so add the newNode here
            currentNode->next = newNode;
        }
    }

    // remove function
    // O(N) where N is the length of the list
    void remove(T data)
    {
        // End if the list is empty
        if (head == nullptr)
        {
            return;
        }

        // Check if the head is about to be removed
        if (head->data == data)
        {
            TeamNode<T>* temp = head;

            // Redefine head to be the next node in line
            head = head->next;

            // Delete the temp node
            delete temp;
            return;
        }

        // Default case
        TeamNode<T>* currentNode = head;

        // While the next node is NOT null And as while the next node is not the one we're looking for
        while (currentNode->next != nullptr && currentNode->next->data != data)
        {
            // Move to the next node
            currentNode = currentNode->next;
        }

        // currentNode->next is what we are looking to remove
        if (currentNode->next != nullptr)
        {
            // Assign the next node to temp
            TeamNode<T>* temp = currentNode->next;

            // make the next node the one after next
            currentNode->next = currentNode->next->next;

            // delete currentNode->next
            delete temp;
        }
    }

    // getHead function
    // O(1)
    TeamNode<T>* getHead()
    {
        return head;
    }

private:
    TeamNode<T>* head;

};

#endif // TEAMLIST_H
