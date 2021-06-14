#include <iostream>
#include "google forms.h"

int choose_status()
{
	std::cout << "Hello everyone!\n Please enter tour permission level.\n for teacher press 1\n for student press 2\n";
	std::string result;
	std::getline(std::cin, result);
	return stoi(result);
}

int main()
{
	int result = choose_status();
	system("cls");
	std::string q;
	if (static_cast<Status>(result) == Status::teacher)
	{
		Teacher teacher;
		std::cout << "Add name_of exam\n";
		std::getline(std::cin, q);
		teacher.add_new_question(q);
	}
	else if (static_cast<Status>(result) == Status::student)
	{
		Student student;
		std::cout << "choose which exam you want to pass\n";
		student.show_exams();
		std::getline(std::cin, q);
		student.show_questions_and_save_answers(q);
		std::cout << "This was the last question, thank you!\n";
	}
}