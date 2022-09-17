#include "Tree.h"

using namespace std;

void Search(Tree& root, Tree* temp, int lvl)
{
    int search;
    cout << "Enter lvl of search: ";
    cin >> search;

    if (search >= lvl || search <= 0)
        cout << "In out of range" << endl;
    else
    {
        int wide = 0;
        int narrow = -1;
        root.Search(search, wide, narrow, temp);
        cout << "Most wide: " << wide << endl << "Most narrow: " << narrow << endl;
    }
}

void AddLvl(Tree& root, Tree* temp, int& lvl)
{
    root.AddLvl(lvl, temp);
    lvl++;
}

void Remove(Tree& root, Tree* temp, int& lvl)
{
    int search;
    cout << "Enter lvl: ";
    cin >> search;

    if (search > lvl || search <= 0)
        cout << "In out of range" << endl;
    else
    {
        int* way = new int[search];

        cout << "Enter way: ";
        for (int i = 0; i < search; i++)
            scanf_s(" %d", &way[i]);

        Tree* removable = root.ChooseElement(way, search);

        root.EraseElement(removable);

        delete[] way;

        int tempint = 0;
        if (!root.WayIsExist(search, tempint, 0, temp))
            lvl = search - 1;
    }
}

void PaintTree(Tree& root, Tree* temp, int lvl)
{
    if (lvl == 0)
        cout << "Tree contains only root" << endl;
    else
        root.PaintTree(lvl, temp);
}

void Help()
{
    cout << "         Commands:" << endl
        << "h - Help" << endl
        << "a - Add new level to tree" << endl
        << "s - Search most wide and narrow tree at level" << endl
        << "g - Paint tree" << endl
        << "e - Remove element from tree" << endl
        << "q - Quit from programm" << endl;
}

int main()
{
    Help();

    int data;
    cout << "Enter data for root: ";
    cin >> data;

    Tree root(0, data, 0, NULL);
    Tree* temp = &root;

    int lvl = 0;

    while (true)
    {
        char command;
        cout << "Enter command: ";
        cin >> command;

        if (command == 'h')
            Help();
        else if (command == 's')
            Search(root, temp, lvl);
        else if (command == 'a')
            AddLvl(root, temp, lvl);
        else if (command == 'e')
            Remove(root, temp, lvl);
        else if (command == 'g')
            PaintTree(root, temp, lvl);
        else if (command == 'q')
            break;
        else
            cout << "Incorrect command" << endl;
    }
}