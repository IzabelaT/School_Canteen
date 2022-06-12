#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include<fstream>

class StudentQueue
{
	struct Student
	{

		std::string name;
		unsigned int group_number;
		int waiting_time;
		Student* next;

		Student(std::string Name, unsigned int Group_Number)
		{
			this->name = Name;
			this->group_number = Group_Number;
			this->waiting_time = 0;
			next = nullptr;
		}
		int GetWaitingTime()
		{
			return this->waiting_time;
		}
		void SetWaitingTime(int WaitingTime)
		{
			this->waiting_time = WaitingTime;
		}
	void DisplayStudents();

	};
	Student* front;
	Student* rear;

	void Free();
	void CopyFrom(const StudentQueue& other);
	bool IsEmpty() const;

public:
	StudentQueue();
	StudentQueue(const StudentQueue& other);
	StudentQueue operator=(const StudentQueue& other);
	~StudentQueue();

	void Push(Student* New_Student);
	void Pop();
	void Peek();
	void AddInQueue(std::ifstream& file);
	void CanteenTimer();
	bool SearchForFriend(std::string Student_Name, unsigned int Student_Group_Number);
	void InsertStudent(Student* front, std::string Student_Name, unsigned int Student_Group_Number);
	void OpenFile(std::ifstream& File, std::string FileName);

};
