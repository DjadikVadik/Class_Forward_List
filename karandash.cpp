#include "Forward_list.h"




int main()
{
	system("chcp 1251 > 0");

	Forward_List<int> list;
	
	list.push_front(56);
	list.push_front(14);
	list.push_front(96);
	list.push_front(45);
	list.push_front(9);

	list.print();

	list.sort_asc();
	
	list.print();

	list.sort_desc();

	list.print();
}