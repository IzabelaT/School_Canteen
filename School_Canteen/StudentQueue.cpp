#include "StudentQueue.h"

void StudentQueue::Student::DisplayStudents()
{
	std::cout << "[" << name << "] " << waiting_time << "m" << std::endl;
}

void StudentQueue::Free()
{
	Student* iter = front;
	while (iter != nullptr)
	{
		Student* prev = iter;
		iter = iter->next;
		delete prev;
	}
	front = rear = nullptr;
}

void StudentQueue::CopyFrom(const StudentQueue& other)
{
	Student* iter = other.front;
	while (iter != nullptr)
	{
		Push(iter);
		iter = iter->next;
	}
}

bool StudentQueue::IsEmpty() const
{
	return front == nullptr;
}

StudentQueue::StudentQueue()
{
	front = nullptr;
	rear = nullptr;
}

StudentQueue::StudentQueue(const StudentQueue& other)
{
	CopyFrom(other);
}

StudentQueue StudentQueue::operator=(const StudentQueue& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

StudentQueue::~StudentQueue()
{
	Free();
}

void StudentQueue::Push(Student* New_Student)
{
	if (IsEmpty())
	{
		front = New_Student;
		rear = New_Student;
	}
	else
	{
		rear->next = New_Student;
		rear = New_Student;
	}
}

void StudentQueue::Pop()
{
	{
		if (IsEmpty())
			return;

		Student* temp = front;
		front = front->next;
		if (front == NULL)
			rear = NULL;

		delete (temp);
	}
}

void StudentQueue::Peek()
{
	if (IsEmpty())
	{
		throw std::runtime_error("The Queue is Empty!");
	}
	std::cout << "'" << front->name << "' -" << " [" << front->group_number << "] [" << front->waiting_time << "]\n";
}

void StudentQueue::AddInQueue(std::ifstream& file)
{
	std::string name;
	std::string number;
	int count_Pop = 0;
	bool FindFirend = false;

	while (!file.eof())
	{

		std::getline(file, name, ' ');
		std::getline(file, number);
		count_Pop++;
		unsigned int groupNumber = std::stoi(number);
		Student* new_Student = new Student(name, groupNumber);

		if (SearchForFriend(name, groupNumber) == true)
		{
			InsertStudent(front, name, groupNumber);
		}
		else
		{
			Push(new_Student);
		}
		CanteenTimer();
		if (count_Pop % 2 == 0)
		{
			front->DisplayStudents();
			Pop();
		}
	}
	while (front != nullptr)
	{
		count_Pop++;
		CanteenTimer();
		if (count_Pop % 2 == 0)
		{
			front->DisplayStudents();
			Pop();
		}
	}
}

void StudentQueue::CanteenTimer()
{
	Student* iter = front;
	int count = 0;
	while (iter != NULL)
	{
		iter->waiting_time = iter->waiting_time + 1;
		iter = iter->next;
	}
}

bool StudentQueue::SearchForFriend(std::string Student_Name, unsigned int Student_Group_Number)
{
	Student* iter = front;
	if (iter == NULL)
		return false;
	while (iter != NULL)
	{
		if (iter->group_number == Student_Group_Number)
		{
			return true;
		}
		iter = iter->next;
	}
}

void StudentQueue::InsertStudent(Student* front, std::string Student_Name, unsigned int Student_Group_Number)
{
	Student* newStudent = new Student(Student_Name, Student_Group_Number);
	if (Student_Group_Number == front->group_number) {
		newStudent->next = front->next;
		front->next = newStudent;
		return;
	}

	Student* temp = front;
	while (temp->group_number != Student_Group_Number) {
		temp = temp->next;
		if (temp == NULL) {
			return;
		}
	}
	newStudent->next = temp->next;
	temp->next = newStudent;
}

void StudentQueue::OpenFile(std::ifstream& File, std::string FileName)
{
	File.open(FileName);
	if (File.is_open())
	{
		std::cout << "Successfully opened file!" << std::endl;
	}
	else
	{
		std::cout << "Failed to opened file!" << std::endl;
		exit(-1);
	}
}

