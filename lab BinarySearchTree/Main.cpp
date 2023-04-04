#include <iostream>
#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"

using namespace std;

template <class T>
void menu(BinarySearchTree<T>* a);

int main()
{
    int c = 0;
    while (true)
    {
        cout << "Choose what type of keys will be in the binary search tree" << "\n" << "1. Int" << "\n" << "2. String" << "\n" << "Enter the command number: ";
        cin >> c;
        if (!cin.fail() && (c==1 || c==2))
        {
            cout << "\n";
            break;
        }
        else
        {
            cout << "Invalid input. Enter the number from 1 to 2." << "\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }
    if (c == 1)
    {
        BinarySearchTree<int> a;
        menu(&a);
    }
    else if (c == 2)
    {
        BinarySearchTree<string> a;
        menu(&a);
    }
    
    return 0;
}

template <class T>
void menu(BinarySearchTree<T>* a)
{
    int choice = 0;
    T key;
    int k = 0;
    
    while (choice != 12)
    {
        k = 0;
        cout << "========= MENU =========" << "\n";
        cout << "1. Find an element by key" << "\n";
        cout << "2. Add an element" << "\n";
        cout << "3. Delete an element" << "\n";
        cout << "4. Printing a string tree image" << "\n";
        cout << "5. Get the number of tree elements" << "\n";
        cout << "6. Get the height of the tree" << "\n";
        cout << "7. Infix tree traversal (iterative)" << "\n";
        cout << "8. Infix tree traversal (recursive)" << "\n";
        cout << "9. Traversing the binary tree by levels (in width)" << "\n";
        cout << "10. Are the two trees similar" << "\n";
        cout << "11. There are identical keys in two search trees" << "\n";
        cout << "12. Exit" << "\n";
        cout << "Enter the command number: ";
        cin >> choice;
        if (cin.fail())
        {
            cout << "Invalid input." << "\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice)
        {
        case 1:
            cout << "Enter the key you want to find: ";
            cin >> key;
            if (cin.fail())
            {
                cout << "Invalid input." << "\n\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << (a->iterativeSearch(key) ? "Element with this key was found" : "Element with this key wasn't found") << "\n\n";
            break;
        case 2:
            cout << "Enter the key you want to add: ";
            cin >> key;
            if (cin.fail())
            {
                cout << "Invalid input." << "\n\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << (a->insert(key) ? "Element with this key has been added" : "Element with this key already exists in the tree") << "\n\n";
            break;
        case 3:
            cout << "Enter the key you want to delete: ";
            cin >> key;
            if (cin.fail())
            {
                cout << "Invalid input." << "\n\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << (a->deleteKey(key) ? "Element with this key was deleted" : "There is no element with this key in the tree") << "\n\n";
            break;
        case 4:
            a->print(cout);
            cout << "\n\n";
            break;
        case 5:
            cout << "Number of tree elements: " << a->getCount() << "\n\n";
            break;
        case 6:
            cout << "Height of the tree: " << a->getHeight() << "\n\n";
            break;
        case 7:
            cout << "Infix traversal: ";
            a->iterativeInorderWalk();
            cout << "\n\n";
            break;
        case 8:
            cout << "Infix traversal: ";
            a->inorderWalk();
            cout << "\n\n";
            break;
        case 9:
            cout << "Traversing  by levels: ";
            a->walkByLevels();
            cout << "\n\n";
            break;
        case 10:
        {
            BinarySearchTree<T> a2;
            while (k!=2)
            {
                cout << "Add elements to the second tree: " << "\n" << "1. Add element" << "\n" << "2. Stop" << "\n" << "Enter the command number: ";
                cin >> k;
                if (!cin.fail() && k == 1)
                {
                    cout << "Enter the key you want to add: ";
                    cin >> key;
                    if (cin.fail())
                    {
                        cout << "Invalid input." << "\n\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    cout << (a2.insert(key) ? "Element with this key has been added" : "Element with this key already exists in the tree") << "\n";
                }
                else if (!cin.fail() && k == 2)
                {
                    cout << (a->isSimilar(a2) ? "Trees are similar" : "Trees aren't similar") << "\n\n";
                    break;
                }
                else
                {
                    cout << "Invalid input. Enter the number from 1 to 2." << "\n\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
            }
        }
        case 11:
        {
            BinarySearchTree<T> a2;
            while (k!=2)
            {
                cout << "Add elements to the second tree: " << "\n" << "1. Add element" << "\n" << "2. Stop" << "\n" << "Enter the command number: ";
                cin >> k;
                if (!cin.fail() && k == 1)
                {
                    cout << "Enter the key you want to add: ";
                    cin >> key;
                    if (cin.fail())
                    {
                        cout << "Invalid input." << "\n\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    cout << (a2.insert(key) ? "Element with this key has been added" : "Element with this key already exists in the tree") << "\n";
                }
                else if (!cin.fail() && k == 2)
                {
                    cout << (a->isIdenticalKey(a2) ? "Identical keys exist" : "Identical keys do not exist") << "\n\n";
                    break;
                }
                else
                {
                    cout << "Invalid input. Enter the number from 1 to 2." << "\n\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
            }
        }
            break;
        case 12:
            break;
        default:
            cout << "Invalid choise. Enter a number from 1 to 12." << "\n\n";
            break;
        }
    }

}