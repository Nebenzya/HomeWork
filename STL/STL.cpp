#include <iostream>
#include <list>

int main()
{
    std::list<int> list = { 3,5,8,13,21,34 };
    std::list<int>::iterator it = list.begin();
    int n,i;

    std::cout << "Enter number: "; std::cin >> n;
    do
    {
        std::cout << "Enter index: "; std::cin >> i;
    } while (i > list.size());

    for (int y = 0; y < i; y++, it++){}
    list.insert(it,n);
    //list.insert(list.begin() + i, n); WHY NOT?
    
    for (int i : list) 
    {
        std::cout << i << "\t";
    }
    std::cout << std::endl;
}
