#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <ctime>
#include <stdlib.h>
using namespace std;

struct Node 
{ 
    string data;
    Node* next;
};
typedef Node* NodePtr;

// Given a reference (pointer to pointer) to the head of a list and an int, inserts a new node on the front of the list. 
// Taken from geeksforgeeks.
void push(NodePtr& head_ref, string new_data) 
{
    NodePtr new_node;
    new_node = new Node;
    new_node->data = new_data;
    new_node->next = head_ref;
    head_ref = new_node;
}

string skyGen() 
{
    string str(40, ' ');
    int rnd;
    for (int i = 0; i < 2; i++) 
    {
        rnd = rand() % 40 + 1;
        if (0 + (rand() % (1 - 0 + 1)) == 1) 
            str[rnd] = '$';
        else 
            str[rnd] = '.';
    }
    return str;
}

// Function to remove the last node of the linked list code taken from geeks for geeks https://www.geeksforgeeks.org/remove-last-node-of-the-linked-list/
NodePtr removeLastNode(struct Node* head)
{
    if (head == NULL)
        return NULL;
    if (head->next == NULL) 
    {
        delete head;
        return NULL;
    }
    // Find the second last node
    NodePtr second_last = head;
    while (second_last->next->next != NULL)
        second_last = second_last->next;
    // Delete last node
    delete (second_last->next);
    // Change next of second last
    second_last->next = NULL;
    return head;
}

int main() {
    const char CPPKEYLEFT = 75;    //left arrow
    const char CPPKEYRIGHT = 77;   //right arrow
    srand (time(NULL)); // Keeps the sky generation differently random
    string str(40, ' '), tail;
    NodePtr head = new Node;

    //initiates the linked list
    for (int i = 0; i < 19; i++) // 19 here dictates the height of our sky
    { 
        push(head, str);
    }

    int score = 50, input, basketPos = 20;
    NodePtr tmp;

    while (true) 
    {
        push(head, skyGen()); // adds a new sky with generated cash or trash

        tmp = head;
        cout << "------------- Falling Money --------------" << endl; 
        while(tmp != NULL) 
        {
            //block of code for basket movement
            if (kbhit()) input = getch();
            if (input == CPPKEYLEFT && basketPos > 0) 
                basketPos--;
            else if (input == CPPKEYRIGHT && basketPos < 39) 
                basketPos++;
            input = 0;
            
            // block of code to print out the sky
            if (tmp->next == NULL) {    // specifically enables us to have the basket[U] to be constantly on the bottom
                tail = tmp->data;

                tail = tmp->data;       // code for checking if the user caught cash or trash
                if (tail[basketPos] == '$') 
                    score += 10;
                else if (tail[basketPos] == '.') 
                    score -= 15;

                tail[basketPos] = 'U';
                cout << '|' << tail << '|' << endl;
            }
            else 
            {
                cout << '|' << tmp->data << '|' << endl;
            }
            
            tmp = tmp->next;    // moves to the next node
        }
        
        removeLastNode(head);   // removes last node in the linked list thus simulating the falling effect with the help of system("cls");
        cout << "Your Score: " << score << endl;
        if (score <= 0) 
        { 
            cout << "Sorry, you lose...";
            Sleep(90);
            return 0;
        } 
        else if (score >= 100) 
        {
            cout << "Yeah, you win!!";
            Sleep(90);
            return 0;
        }

        Sleep(90);
        system("CLS");
    }
}