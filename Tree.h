#include <iostream>
#include <vector>
#include <ctime>
#include <windows.h>

using namespace std;

class Tree
{
private:
    int data;
    int childs_count;
    int index;

    Tree** childs;
    Tree* ancestor;

public:
    Tree();
    Tree(int i, Tree* anc);
    Tree(int child_c, int info, int number, Tree* temp);

    Tree* ChooseElement(int* way, int length);

    bool WayIsExist(int search, int& lvl, int number, Tree*& temp);
    bool WayIsExist(int search, int& lvl, int number, int& space_count, Tree*& temp);

    void AddChild(int search, Tree*& element);
    void AddLvl(int search, Tree*& temp);
    void Search(int search, int& wide, int& narrow, Tree*& temp);

    void PaintLvl(int search, int& sizeofmass, COORD& position, int*& Displacement, int*& TempDisplacement, Tree*& temp);
    void PaintTree(int lvl, Tree*& temp);

    void EraseElement(Tree* temp);

    ~Tree();
};