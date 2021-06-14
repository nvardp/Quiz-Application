#include "google forms.h"

Person_in_univer::Person_in_univer(Status status)
{
	this->status = status;
}
Teacher::Teacher() : Person_in_univer(Status::teacher) {}
Student::Student() : Person_in_univer(Status::student) {}

std::ofstream Teacher::create_new_query(const std::string& filename)
{
	std::ofstream MyFile(get_path_of_exe()+"\\"+filename + ".txt",  std::ios_base::app);
	return MyFile;
}
std::ofstream Teacher::create_new_query_answers(const std::string& filename)
{
	std::ofstream MyFile(get_path_of_exe() + "\\" + filename + "_answers.txt", std::ios_base::app);
	return MyFile;
}
void Teacher::add_new_question_local(std::string& q)
{
	q += '\n';
	questions.push_back(q);
	std::cout << "Add 2-4 options (for having less then 4, just press empty enter)\n";
	std::string op;
	for (size_t i = 0; i < MAX_OPTIONS; i++)
	{
	std::getline(std::cin, op);
	questions.back() += op;
	questions.back() += '\n';
	}
	add_answer();
}
void Teacher::add_answer()
{
	std::cout << "Add right answer (ex. a)\n";
	std::string op_r;
	std::getline(std::cin, op_r);
	answers.push_back(op_r[0]);
}
void Teacher::add_to_file(std::ofstream file, const Question_Data& what)
{
	for (size_t i = 0; i < what.size(); i++)
	{
		file << std::endl << what[i] << std::endl << END_OF_QUESTION;
	}
}

void Teacher::add_to_file(std::ofstream file, const Answer_Data& what)
{
	for (size_t i = 0; i < what.size(); i++)
	{
		file << std::endl << what[i] << std::endl << END_OF_QUESTION;
	}
}

void Student::add_answer()
{
	std::cout << "You can choose only one answer (ex. a)\n";
	char op_r;
	std::cin >> op_r;
	answers.push_back(op_r);
}

void Student::show_exams()
{
	std::string path = get_path_of_exe() + "\\";
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (fs::path(entry.path()).extension() == ".txt")
		{
			std::string fileName = (entry.path()).string();
			std::string finalname= fileName.substr(fileName.find_last_of("\\/") + 1, fileName.size());
			finalname.erase(finalname.end() - 4, finalname.end());
			auto found = finalname.find("_answers");
			if(found == std::string::npos)
			std::cout << finalname <<std::endl;
		}
	}
}
void Teacher::show_questions(const std::string& filename)
{
	std::fstream file;
	file.open(get_path_of_exe() + "\\" + filename + ".txt");
}

void Teacher:: add_new_question(std::string& q)
{
	std::ofstream file = create_new_query(q);
	std::ofstream file_answers = create_new_query_answers(q);
	std::string q1;
	while (true)
	{
		std::cout << "Add new question\n";
		std::getline(std::cin, q1);
		if (q1 == STOP)
			break;
		add_new_question_local(q1);
	}
	add_to_file(std::move(file), questions);
	add_to_file(std::move(file_answers), answers);
}
void Student::show_questions_and_save_answers(const std::string& filename)
{
	std::fstream file;
	std::string finalname = get_path_of_exe() + "\\" + filename + ".txt";
	file.open(finalname);
	std::string line;
	std::string answer;
	while (!file.eof())
	{
		std::getline(file, line);
		while (line != END_OF_QUESTION)
		{
			if(line!=""&& line!=END_OF_QUESTION)
			std::cout << line << std::endl;
			std::getline(file, line);
			
		}
		std::cout << "you can enter only one answer (ex. a or 1)\n";
		std::getline(std::cin, answer);
		set_answer(answer);
	}
	std::ofstream tofile;
	tofile.open(get_path_of_exe()+"\\"+"student answer on" + filename + ".txt");
	save_data(std::move(tofile), answers);
}
void Student::set_answer(const std::string& answer)
{
	answers.push_back(answer[0]);
}
void Student::save_data(std::ofstream file, const Answer_Data& what)
{
	for (size_t i = 0; i < what.size(); i++)
	{
		file << std::endl << what[i] << std::endl << END_OF_QUESTION;
	}
}
std::string Person_in_univer::get_path_of_exe()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}