#include "Tree.h"

using namespace std;

Tree::Tree()
{
    data = 0;
    childs_count = 0;
    index = 0;
    childs = new Tree * [0];
    ancestor = new Tree;
}

Tree::Tree(int i, Tree* anc)
{
    data = 0;
    childs_count = 0;
    index = i;
    childs = new Tree * [0];
    ancestor = anc;
}

Tree::Tree(int child_c, int info, int number, Tree* temp)
{
    data = info;
    childs_count = child_c;
    index = number;
    childs = new Tree * [child_c];
    for (int i = 0; i < child_c; i++)
    {
        childs[i] = new Tree(i, temp);
    }
}

Tree* Tree::ChooseElement(int* way, int length)
{
    Tree* temp = this;

    for (int i = 0; i < length; i++)
    {
        if (way[i] >= temp->childs_count)
            return NULL;
        temp = temp->childs[way[i]];
    }

    return temp;
}

bool Tree::WayIsExist(int search, int& lvl, int number, Tree*& temp)
{
    if (temp->childs_count > number)
    {
        temp = temp->childs[number];

        lvl++;

        if (search == lvl)
            return true;
        else
            return WayIsExist(search, lvl, 0, temp);
    }
    else
    {
        if (temp != this)
        {
            int tempint = temp->index;
            temp = temp->ancestor;
            lvl--;
            return WayIsExist(search, lvl, tempint + 1, temp);
        }
        else
            return false;
    }
}

bool Tree::WayIsExist(int search, int& lvl, int number, int& space_count, Tree*& temp)
{
    if (temp->childs_count > number)
    {
        temp = temp->childs[number];

        lvl++;

        if (search == lvl)
            return true;
        else
            return WayIsExist(search, lvl, 0, space_count, temp);
    }
    else if (temp->childs_count == 0)
    {
        space_count++;

        int tempint = temp->index;
        temp = temp->ancestor;
        lvl--;
        return WayIsExist(search, lvl, tempint + 1, space_count, temp);
    }
    else
    {
        if (temp != this)
        {
            int tempint = temp->index;
            temp = temp->ancestor;
            lvl--;
            return WayIsExist(search, lvl, tempint + 1, space_count, temp);
        }
        else
            return false;
    }
}

int* push_back(int* Displacement, int& size, int data)
{
    size++;

    int* bufer = new int[size];
    for (int i = 0; i < size - 1; i++)
        bufer[i] = Displacement[i];
    bufer[size - 1] = data;

    delete[] Displacement;

    return bufer;
}

int back(int* Displacement, int size)
{
    return Displacement[size - 1];
}

void Tree::AddChild(int search, Tree*& element)
{
    cout << "Enter count of childs for ";

    Tree* temp = element;
    int* way = new int[search];
    int i = 0;
    while (element != this)
    {
        way[i++] = element->index;
        element = element->ancestor;
    }
    for (int j = search - 1; j >= 0; j--)
        cout << way[j];
    delete[] way;
    element = temp;

    if (temp == this)
        cout << "root";
    cout << ": ";

    int tempcount;
    cin >> tempcount;

    Tree** c = new Tree * [tempcount];
    for (int i = 0; i < tempcount; i++)
    {
        c[i] = new Tree(i, temp);
        cout << "   Enter data for " << i + 1 << " child: ";
        cin >> c[i]->data;
    }

    temp->childs = c;
    temp->childs_count = tempcount;
}

void Tree::AddLvl(int search, Tree*& temp)
{
    if (childs_count == 0)
        AddChild(0, temp);
    else
    {
        int tempint = 0;
        int lvl = 0;

        while (WayIsExist(search, lvl, tempint, temp))
        {
            AddChild(search, temp);

            tempint = temp->index + 1;
            temp = temp->ancestor;
            lvl--;
        }
    }
}

void Tree::Search(int search, int& wide, int& narrow, Tree*& temp)
{
    int tempint = 0;
    int lvl = 0;

    while (WayIsExist(search, lvl, tempint, temp))
    {
        if (temp->childs_count > wide)
            wide = temp->childs_count;

        if (temp->childs_count < narrow || narrow == -1)
            narrow = temp->childs_count;

        tempint = temp->index + 1;
        temp = temp->ancestor;
        lvl--;
    }
}

void PaintElement(int data, COORD& position, int lvl)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    cout << "+---+";
    position.Y -= 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    cout << "|";
    cout.setf(ios::left);
    cout.width(3);
    cout << data << "|";
    position.Y -= 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    cout << "+---+";

    if (lvl != 0)
    {
        position.X += 2;
        position.Y -= 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
        cout << "|";
        position.Y -= 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
        cout << "+";

        position.X -= 2;
        position.Y += 2;
    }
    if (lvl != 2)
    {
        position.X += 2;
        position.Y += 3;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
        cout << "|";
        position.Y += 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
        cout << "+";

        position.X -= 2;
        position.Y -= 4;
    }
    position.X += 5;
    position.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void PaintLine(int indent, COORD position)
{
    position.X -= 3 + indent;
    position.Y -= 4;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

    for (int i = 0; i < indent; i++)
        cout << "-";
    cout << "+";

    position.X += 3 + indent;
    position.Y += 4;
}

void Tree::PaintLvl(int search, int& sizeofmass, COORD& position, int*& Displacement, int*& TempDisplacement, Tree*& temp)
{
    int space_count = 0;
    int tempint = 0;
    int lvl = 0;

    if (sizeofmass == 0)
    {
        while (WayIsExist(search, lvl, tempint, space_count, temp))
        {
            if (sizeofmass == 0)
                Displacement = push_back(Displacement, sizeofmass, 0);
            else
                Displacement = push_back(Displacement, sizeofmass, back(Displacement, sizeofmass) + 6);

            for (int i = 0; i < space_count; i++)
                Displacement = push_back(Displacement, sizeofmass, back(Displacement, sizeofmass) + 6);

            position.X = back(Displacement, sizeofmass);

            PaintElement(temp->data, position, 2);

            if (temp != temp->ancestor->childs[0])
                PaintLine(5, position);

            space_count = 0;
            tempint = temp->index + 1;
            temp = temp->ancestor;
            lvl--;
        }

        for (int i = 0; i < space_count; i++)
            Displacement = push_back(Displacement, sizeofmass, back(Displacement, sizeofmass) + 6);
    }
    else if (search == 0)
    {
        position.X = (Displacement[0] + back(Displacement, sizeofmass)) / 2;

        PaintElement(temp->data, position, 0);
    }
    else
    {
        int size = 0;
        int sizeoftemp = 0;

        while (WayIsExist(search, lvl, tempint, space_count, temp))
        {
            for (int i = 0; i < space_count; i++)
            {
                TempDisplacement = push_back(TempDisplacement, sizeoftemp, Displacement[size]);
                size++;
            }

            if (temp->childs_count < 2)
            {
                TempDisplacement = push_back(TempDisplacement, sizeoftemp, Displacement[size]);
                size++;
            }
            else
            {
                TempDisplacement = push_back(TempDisplacement, sizeoftemp, (Displacement[size] + Displacement[size + temp->childs_count - 1]) / 2);
                size += temp->childs_count;
            }

            position.X = back(TempDisplacement, sizeoftemp);

            if (temp->childs_count > 0)
                PaintElement(temp->data, position, 1);
            else
                PaintElement(temp->data, position, 2);

            if (temp != temp->ancestor->childs[0])
                PaintLine(back(TempDisplacement, sizeoftemp) - TempDisplacement[sizeoftemp - 2] - 1, position);

            space_count = 0;
            tempint = temp->index + 1;
            temp = temp->ancestor;
            lvl--;
        }

        for (int i = 0; i < space_count; i++)
            TempDisplacement = push_back(TempDisplacement, sizeoftemp, Displacement[size]);

        Displacement = TempDisplacement;
        sizeofmass = sizeoftemp;
    }
}

void Tree::PaintTree(int lvl, Tree*& temp)
{
    COORD bufferSize = { 800, 500 };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    PCONSOLE_SCREEN_BUFFER_INFO bi = new CONSOLE_SCREEN_BUFFER_INFO;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), bi);
    COORD* position = &bi->dwCursorPosition;

    position->Y += lvl * 6 + 4;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *position);

    int sizeofmass = 0;
    int* Displacement = new int[sizeofmass];

    for (int i = lvl; i >= 0; i--)
    {
        int* TempDisplacement = new int[0];

        position->X += 1;

        PaintLvl(i, sizeofmass, *position, Displacement, TempDisplacement, temp);

        position->X = 0;
        position->Y -= 6;
    }
    position->Y += lvl * 6 + 8;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *position);
    cout << endl;
}

void Tree::EraseElement(Tree* temp)
{
    int tempint = temp->index;
    int j = 0;
    temp = temp->ancestor;

    if (temp->childs_count == 1)
        temp->childs = NULL;
    else
    {
        Tree** bufer = new Tree * [temp->childs_count - 1];
        for (int i = 0; i < temp->childs_count; i++)
        {
            if (i != tempint)
            {
                bufer[j] = temp->childs[i];
                bufer[j]->index = j;
                Tree* g1 = bufer[j];
                Tree* g2 = temp->childs[i];
                j++;
            }
        }

        temp->childs = bufer;
    }

    temp->childs_count -= 1;
}

Tree::~Tree()
{
    delete[] childs;
    delete[] ancestor;
}