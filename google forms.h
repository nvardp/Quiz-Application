#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <Windows.h>


std::string const STOP = "end";
const std::string END_OF_QUESTION = "#";
const int MAX_OPTIONS = 4;
namespace fs = std::filesystem;

enum class Status
{
	teacher = 1,
	student,
};
class Person_in_univer
{
public:
	using  Question_Data = std::vector<std::string>;
	using Answer_Data = std::vector<char>;

	Person_in_univer(Status status);
protected:
	virtual void add_answer() = 0;
	virtual std::string get_path_of_exe();
protected:
	Question_Data questions;
	Answer_Data answers;
	Status status;
};
class Teacher : public Person_in_univer
{
public:
	Teacher();
public:
	void  add_new_question(std::string& q);
	void show_questions(const std::string&);
private:
	std::ofstream create_new_query(const std::string&);
	std::ofstream create_new_query_answers(const std::string&);
	void add_new_question_local(std::string&);
	void add_to_file(std::ofstream, const Question_Data&);
	void add_answer() override;
	void add_to_file(std::ofstream, const Answer_Data&);
};


class Student : public Person_in_univer
{
public:
	Student();

public:
	void show_exams();
	void show_questions_and_save_answers(const std::string&);
private:
	void add_answer() override;
	void set_answer(const std::string&);
    void save_data(std::ofstream, const Answer_Data&);

};