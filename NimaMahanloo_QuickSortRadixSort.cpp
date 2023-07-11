// Nima Mahanloo
// Quick Sort and Radix Sort
// CISP 430
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
/*Quick Sort Section*/
// Quick Sort linked list node structure
struct node
{
    bool pivotFlag = false;
    int number;
    node* next = nullptr;
    node* prev = nullptr;
};
// A module to push data to the linked list
void pushList (node* (&last), int num)
{
    if (last->pivotFlag == false)
    {
        last->next = new node;
        last->next->prev = last;
        last = last->next;
    }
    last->number = num;
    if (last->pivotFlag == true)
    {
        last->pivotFlag = false;
    }
}
// A module to swap nodes data
void swapData(node* (&low), node* (&high))
{
    int tempValue;
    tempValue = low->number;
    low->number = high->number;
    high->number = tempValue;
}
// A module to display linked list data
void displayList (node* first)
{
    node* curr = first;
    while (curr != nullptr)
    {
        cout << curr->number << " ";
        curr = curr->next;
    }
    cout << endl;
}
// A module to list by quick sort
void quickSort (node* (&first), node* (&last), int listSize, int pivotIndex, int &pivotCounter)
{
    node* low = first;
    node* high = first;
    node* pivot = last;
    int counter;
    pivot->pivotFlag = true;
    cout << "Pivot :" << pivot->number << endl;
    for (counter = 0; counter < pivotIndex; counter++)
    {
        if (low->number < pivot->number)
        {
            high = low->next;
            while ((high->next != nullptr) && (high->number < pivot->number))
            {
                high = high->next;
            }
            swapData (low, high);
            if (high->pivotFlag == true)
            {
                high->pivotFlag = false;
                low->pivotFlag = true;
                pivot = low;
                pivotIndex = counter+1;
            }
        }
        if((low->pivotFlag == false) && (low->next != nullptr))
        {
            low = low->next;
        }
        displayList(first);
    }
    pivotCounter++;
    if (pivotCounter < listSize)
    {
        cout << "Next Round >" << endl;
        if((pivot->prev != nullptr) && (pivot->prev->pivotFlag == false))
        {
            cout << "low : " << first->number << endl;
            cout << "high : " << pivot->prev->number << endl;
            quickSort(first, pivot->prev, listSize, pivotIndex, pivotCounter);
        }
        else if (pivot->next != nullptr)
        {
            low = pivot->next;
            while ((low->pivotFlag == true) && (low->next != nullptr))
            {
                low = low->next;
            }
            cout << "low : " << low->number << endl;
            high = low;
            counter = 1;
            while ((high->next != nullptr) && (high->next->pivotFlag == false))
            {
                high = high->next;
                counter++;
            }
            cout << "High : " << high->number << endl;
            quickSort(low, high, listSize, counter, pivotCounter);
        }
    }
}
// A module to add 5s
void equalDigits(node* (&first))
{
    node* curr = first;
    while (curr != nullptr)
    {
        if ((curr->number < 10) && (curr->number > 0))
        {
            curr->number *= 100;
            curr->number += 55;
        }
        else if ((curr->number < 100) && (curr->number > 9))
        {
            curr->number *= 10;
            curr->number += 5;
        }
        else if (curr->number == 0)
        {
            curr->number = 555;
        }
        else if ((curr->number < 0) && (curr->number > -10))
        {
            curr->number *= 100;
            curr->number += -55;
        }
        else if ((curr->number < -9) && (curr->number > -100))
        {
            curr->number *= 10;
            curr->number += -5;
        }
        curr = curr->next;
    }
}
// A module to read numbers from the input file
void readData (node* (&last))
{
    int number;
    ifstream readFile ("input.txt");
    if (readFile.is_open())
    {
        while (!(readFile.eof()))
        {
            readFile >> number;
            pushList(last, number);
        }
        readFile.close();
    }
    else
    {
        cout << "Error: Can not open file!" << endl;
        assert(readFile.is_open() == true);
    }

}
// A module to destroy the linked list
void clearList (node* (&first))
{
    node* temp;
    while (first != nullptr)
    {
        temp = first;
        first = first->next;
        if (first != nullptr)
        {
            delete temp;
            temp = nullptr;
        }
    }
}
/*Radix Sort Section*/
// A 2D node object as structure
struct radixNode
{
    bool firstData = false;
    int number = 0;
    radixNode* data = nullptr;
    radixNode* next = nullptr;
    radixNode* prev = nullptr;
};
// A module to initialize the program queue first dimension
void queueInitial(radixNode* (&head))
{
    int counter;
    for (counter = 0; counter < 19; counter++)
    {
        head->next = new radixNode;
        head->next->prev = head;
        head = head->next;
    }
}
// A module to push data inside current dimension
void pushData(radixNode* (&curr), int n)
{
    if (curr->data == nullptr)
    {
        curr->data = new radixNode;
        curr->data->firstData = true;
    }
    radixNode* headData = curr->data;
    while (headData->next != nullptr)
    {
        headData = headData->next;
    }
    if (headData->firstData == false)
    {
        headData->next = new radixNode;
        headData->next->prev = headData;
        headData = headData->next;
    }
    headData->number = n;
    if (headData->firstData == true)
    {
        headData->firstData = false;
    }
}
// A module to display 2D queue contains for process check
void displayQueue (radixNode* tail)
{
    int counter = -9;
    radixNode* curr = tail;
    while (curr->next != nullptr)
    {
        cout << counter << ": ";
        radixNode* headData = curr->data;
        while (headData != nullptr)
        {
            cout << headData->number << " ";
            headData = headData->next;
        }
        cout << endl;
        curr = curr->next;
        counter++;
    }
    cout << endl;
}
// A module to copy by priority queue data to linked list
void queueToList(node* (&first), node* (&last), radixNode* tail, bool arrange)
{
    radixNode* curr;
    radixNode* headData;
    node* currList;
    // For ascending
    if (arrange == false)
    {
        curr = tail;
        currList = first;
        while (curr->next != nullptr)
        {
            headData = curr->data;
            while ((headData != nullptr) && (currList != nullptr))
            {
                currList->number = headData->number;
                headData = headData->next;
                currList = currList->next;
            }
            curr = curr->next;
        }
    }
    // For descending
    else
    {
        curr = tail;
        currList = last;
        while (curr->next != nullptr)
        {
            headData = curr->data;
            while ((headData != nullptr) && (currList != nullptr))
            {
                currList->number = headData->number;
                headData = headData->next;
                currList = currList->prev;
            }
            curr = curr->next;
        }
    }
}
// A module to reset the queue second dimension
void clearQueue (radixNode* (&tail))
{
    radixNode* curr = tail;
    radixNode* headData = nullptr;
    radixNode* temp = nullptr;
    while(curr->next != nullptr)
    {
        headData = curr->data;
        if (headData != nullptr)
        {
            while (headData->next != nullptr)
            {
                temp = headData->next;
                if(headData->next->next != nullptr)
                {
                    headData->next->prev = headData;
                }
                headData->next = headData->next->next;
                delete temp;
                temp = nullptr;
            }
            delete headData;
            headData = nullptr;
            delete curr->data;
            curr->data = nullptr;
        }
        curr = curr->next;
    }
}
// A module to sort input array by radix sort algorithm
void radixSort(node* (&first), node* (&last), radixNode* (&tail))
{
    radixNode* curr = tail;
    node* currList = first;
    int round, counter = -1, outerCounter, endIndex;
    // Find maximum and minimum values in the array
    int maxValue = currList->number, minValue = currList->number;
    currList = currList->next;
    while (currList != nullptr)
    {
        if (currList->number > maxValue)
        {
            maxValue = currList->number;
        }
        else if (currList->number < minValue)
        {
            minValue = currList->number;
        }
        currList = currList->next;
    }
    // Determine number of necessary rounds for radix sorting process
    if (((minValue > -10) && (minValue <= 0)) || ((maxValue >= 0) && (maxValue < 10)))
    {
        round = 1;
    }
    else if (((minValue > -100) && (minValue <= -10)) || ((maxValue >= 10) && (maxValue < 100)))
    {
        round = 2;
    }
    else if (((minValue > -1000) && (minValue <= -100)) || ((maxValue >= 100) && (maxValue < 1000)))
    {
        round = 3;
    }
    else if (((minValue > -10000) && (minValue <= -1000)) || ((maxValue >= 1000) && (maxValue < 10000)))
    {
        round = 4;
    }
    // A loop for radix sorting rounds
    for (outerCounter = 0; outerCounter < round; outerCounter++)
    {
        cout << endl << "Round " << outerCounter+1 << ">" << endl;
        currList = first;
        // A loop to explain each array member in ascending direction
        while (currList != nullptr)
        {
            // Assign the queue first dimension first node to curr node
            curr = tail;
            // If the array current member number is between -1 and -9
            if ((currList->number > -10) && (currList->number < 0))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = 9-((-1)*currList->number);
                    for(counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is not at first round
                else
                {
                    for(counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
            }
            // If the array current member number is between -10 and -99
            else if ((currList->number > -100) && (currList->number < -9))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = 9-(((-1)*currList->number)%10);
                    for (counter = 0; counter <  endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is at second round
                else if (outerCounter == 1)
                {
                    endIndex = 9-(((-1)*currList->number)/10);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is not at first or second round
                else
                {
                    for(counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
            }
            // If the array current member number is between -100 and -999
            else if ((currList->number > -1000) && (currList->number < -99))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = ((-1)*currList->number)%100;
                    endIndex = 9-(endIndex%10);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is at second round
                else if (outerCounter == 1)
                {
                    endIndex = ((-1)*currList->number)%100;
                    endIndex = 9-(endIndex/10);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is at third round
                else if (outerCounter == 2)
                {
                    endIndex = 9-(((-1)*currList->number)/100);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is not at first, second or third round
                else
                {
                    for(counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
            }
            // If the array current member number is between -1000 and -9999
            else if ((currList->number > -10000) && (currList->number < -999))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = ((-1)*currList->number)%1000;
                    endIndex = endIndex%100;
                    endIndex = 9-(endIndex%10);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is at second round
                else if (outerCounter == 1)
                {
                    endIndex = ((-1)*currList->number)%1000;
                    endIndex = endIndex%100;
                    endIndex = 9-(endIndex/10);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is at third round
                else if (outerCounter == 2)
                {
                    endIndex = ((-1)*currList->number)%1000;
                    endIndex = 9-(endIndex/100);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is at fourth round
                else if (outerCounter == 3)
                {
                    endIndex = 9-(((-1)*currList->number)/1000);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is not at first, second, third or fourth round
                else
                {
                    for(counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
            }
            // If the array current member number is between 0 and 9
            else if ((currList->number < 10) && (currList->number > -1))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = currList->number;
                    for(counter = 0; counter <  endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is not at first round
                else
                {
                    for (counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
            }
            // If the array current member number is between 10 and 99
            else if ((currList->number < 100) && (currList->number > 9))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = currList->number%10;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is at second round
                else if (outerCounter == 1)
                {
                    endIndex = currList->number/10;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is not at first or second round
                else
                {
                    for (counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
            }
            // If the array current member number is between 100 and 999
            else if ((currList->number < 1000) && (currList->number > 99))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = currList->number%100;
                    endIndex = endIndex%10;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is at second round
                else if (outerCounter == 1)
                {
                    endIndex = currList->number%100;
                    endIndex = endIndex/10;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is at third round
                else if (outerCounter == 2)
                {
                    endIndex = currList->number/100;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is not at first, second or third round
                else
                {
                    for (counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
            }
            // If the array current member number is between 1000 and 9999
            else if ((currList->number < 10000) && (currList->number > 999))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = currList->number%1000;
                    endIndex = endIndex%100;
                    endIndex = endIndex%10;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is at second round
                else if (outerCounter == 1)
                {
                    endIndex = currList->number%1000;
                    endIndex = endIndex%100;
                    endIndex = endIndex/10;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is at third round
                else if (outerCounter == 2)
                {
                    endIndex = currList->number%1000;
                    endIndex = endIndex/100;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is at fourth round
                else if (outerCounter == 3)
                {
                    endIndex = currList->number/1000;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
                // If radix sort is not at first, second, third or fourth round
                else
                {
                    for (counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, currList->number);
                }
            }
            currList = currList->next;
        }
        // Copy the queue contains to array
        queueToList(first, last, tail, false);
        displayQueue(tail);
        displayList(first);
        if (outerCounter < round-1)
        {
            // Reset the queue 2nd dimension for next round
            clearQueue(tail);
        }
    }
    // Show final result to user
    cout << endl << "Sorted List by Radix Sort (Desc):" << endl << endl;
    queueToList(first, last, tail, true);
    displayList(first);
    // Reset the queue 2nd dimension
    clearQueue(tail);
}
int main()
{
    /*Quick Sort Section*/
    int listSize = 9, pivotIndex = listSize, pivotCounter = 0;
    node* linkedList = new node;
    node* first = linkedList;
    node* last = linkedList;
    last->pivotFlag = true;
    readData(last);
    cout << endl << "Unsorted List:" << endl << endl;
    displayList(first);
    cout << endl << "Quick Sort Process (Desc):" << endl << endl;
    quickSort(first, last, listSize, pivotIndex, pivotCounter);
    cout << endl << "Sorted list by Quick Sort (Desc):" << endl << endl;
    displayList(first);
    equalDigits(first);
    cout << endl << "Added aditional 5 digits:" << endl << endl;
    displayList(first);
    /*Radix Sort Section*/
    radixNode* Queue = new radixNode;
    radixNode* tail = Queue;
    radixNode* head = Queue;
    queueInitial(head);
    cout << endl << "Radix Sort Process (Asc):" << endl;
    radixSort(first, last, tail);
    clearList(first);
    return 0;
}
