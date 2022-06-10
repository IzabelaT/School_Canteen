#include <iostream>
#include"StudentQueue.h"

int main()
{
	std::ifstream File;
	StudentQueue students;
	students.OpenFile(File, "students.txt");
	students.AddInQueue(File);

	File.close();
	return 0;
}


