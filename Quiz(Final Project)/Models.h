#pragma once

void Throw_add_writeErrorFile(str about_error, Exception* ex)
{
	try
	{
		throw new DatabaseException(about_error, __LINE__, __FILE__, __TIME__, __DATE__);
	}
	catch (Exception* ex)
	{
		SetConsoleTextAttribute(console, 4);
		system("cls");
		cout << "\t\t\t\t\t" << about_error << endl;
		SetConsoleTextAttribute(console, 7);
		ofstream error_file("errors.txt", ios::app);
		error_file << ex->what() << "\n";
		error_file.close();
	}
}

class User
{
	str _username;
	str _password;
	str _first_name;
	str _second_name;
	int _age;
	float _score = 0;
public:
	User()
	{
		_username = "";
		_password = "";
		_first_name = "";
		_second_name = "";
		_age = 0;
		_score = 0;
	}

	User(str username, str password, str first_name, str second_name, int age)
	{
		SetUsername(username);
		SetPassword(password);
		SetFirstname(first_name);
		SetSecondname(second_name);
		SetAge(age);
	}
	User(str username, str password, str first_name, str second_name, int age, float score) :User(username, password, first_name, second_name, age)
	{
		SetScore(score);
	}

	void SetUsername(str username)
	{
		if (username.size() >= 3)
		{
			this->_username = username;
			return;
		}
		try
		{
			throw new InvalidArgument("Username min. 3 symbol", __LINE__, __FILE__, __TIME__, __DATE__);
		}
		catch (Exception* ex)
		{
			system("cls");
			Throw_add_writeErrorFile("Username min. 3 symbol", ex);
			throw new InvalidArgument("Username min. 3 symbol", __LINE__, __FILE__, __TIME__, __DATE__);
		}
	}
	void SetPassword(str password)
	{
		if (password.size() >= 5)
		{
			this->_password = password;
			return;
		}
		try
		{
			throw new InvalidArgument("password min. 5 symbol", __LINE__, __FILE__, __TIME__, __DATE__);
		}
		catch (Exception* ex)
		{
			system("cls");
			Throw_add_writeErrorFile("password min. 5 symbol", ex);
			throw new InvalidArgument("password min. 5 symbol", __LINE__, __FILE__, __TIME__, __DATE__);
		}
	}
	void SetFirstname(str first_name)
	{
		if (first_name.size() >= 3)
		{
			this->_first_name = first_name;
			return;
		}
		try
		{
			throw new InvalidArgument("first_name min. 3 symbol", __LINE__, __FILE__, __TIME__, __DATE__);
		}
		catch (Exception* ex)
		{
			system("cls");
			Throw_add_writeErrorFile("first_name min. 3 symbol", ex);
			throw new InvalidArgument("first_name min. 3 symbol", __LINE__, __FILE__, __TIME__, __DATE__);
		}
	}
	void SetSecondname(str second_name)
	{
		if (second_name.size() >= 3)
		{
			this->_second_name = second_name;
			return;
		}
		try
		{
			throw new InvalidArgument("second_name min. 3 symbol", __LINE__, __FILE__, __TIME__, __DATE__);
		}
		catch (Exception* ex)
		{
			system("cls");
			Throw_add_writeErrorFile("second_name min. 3 symbol", ex);
			throw new InvalidArgument("second_name min. 3 symbol", __LINE__, __FILE__, __TIME__, __DATE__);
		}
	}
	void SetAge(int age)
	{
		if (age > 0 && age < 50)
		{
			this->_age = age;
			return;
		}
		try
		{
			throw new InvalidArgument("age min. 1 max. 50", __LINE__, __FILE__, __TIME__, __DATE__);
		}
		catch (Exception* ex)
		{
			system("cls");
			Throw_add_writeErrorFile("age min. 1 max. 50", ex);
			throw new InvalidArgument("age min. 1 max. 50", __LINE__, __FILE__, __TIME__, __DATE__);
		}

	}
	void SetScore(float score)
	{
		this->_score = score;
	}


	inline str GetUsername()const { return this->_username; }
	inline str GetPassword()const { return this->_password; }
	inline str GetFirstname()const { return this->_first_name; }
	inline str GetSecondname()const { return this->_second_name; }
	inline int GetAge()const { return this->_age; }
	inline float GetScore()const { return this->_score; }

	void Show()
	{
		cout << "Username: " << this->_username << endl;
		cout << "Password: ";
		for (size_t i = 0; i < _password.size(); i++)
			cout << "*";
		cout << endl;
		cout << "First Name: " << this->_first_name << endl;
		cout << "Second Name: " << this->_second_name << endl;
		cout << "Age: " << this->_age << endl;
		cout << "Score: " << this->_score << endl;
	}

	void LeaderboardShow()
	{
		cout << this->_username << "    " << this->_score << endl;
	}
	void uptadeScore(int dogru_cavablar, int sehv_cavablar, int bos_buraxilanlar)
	{
		this->_score = this->_score + (dogru_cavablar * 10) - (sehv_cavablar * 10) - (bos_buraxilanlar * 15);
	}

};

class Question
{
	static int question_number;
	int	num = question_number;
	str _question;
	str _correct_answer;
	str* _answers;
public:
	Question()
	{
		question_number++;
		_question = "";
		_correct_answer = "";
		_answers = new str[4];
	}
	Question(str question, str correct_answer, str* answers)
	{
		question_number++;
		SetQuestion(question);
		SetAnswers(answers);
		SetCorrectAnswer(correct_answer);
	}
	Question(str question, str correct_answer, str* answers, bool c)
	{
		this->_question = question;
		this->_correct_answer = correct_answer;
		this->_answers = answers;

	}

	void SetQuestion(str question)
	{
		if (question.size() >= 0)
		{
			//this->_question = question;
			this->_question = to_string(num) + ". " + question;
			return;
		}
		else
		{
			try
			{
				throw new InvalidArgument("Question is wrong", __LINE__, __FILE__, __TIME__, __DATE__);
			}
			catch (Exception* ex)
			{
				system("cls");
				Throw_add_writeErrorFile("Question is wrong", ex);
				throw new InvalidArgument("Question is wrong", __LINE__, __FILE__, __TIME__, __DATE__);
			}


		}
	}
	void SetAnswers(str* answers)
	{
		this->_answers = new str[4];
		for (size_t i = 0; i < 4; i++)
			this->_answers[i] = answers[i];
	}
	void SetCorrectAnswer(str correct_answer)
	{
		bool isCheck = false;
		for (size_t i = 0; i < 4; i++)
		{
			if (this->_answers[i] == correct_answer)
			{
				isCheck = true;
				break;
			}
		}
		if (isCheck == false)
		{

			try
			{
				throw new InvalidArgument("Correct answer is wrong", __LINE__, __FILE__, __TIME__, __DATE__);
			}
			catch (Exception* ex)
			{
				system("cls");
				Throw_add_writeErrorFile("Correct answer is wrong", ex);
				throw new InvalidArgument("Correct answer is wrong", __LINE__, __FILE__, __TIME__, __DATE__);
			}

		}
		else
		{
			this->_correct_answer = correct_answer;
		}
	}

	inline str GetQuestion()const { return this->_question; }
	inline str GetCorrectAnswer()const { return this->_correct_answer; }
	inline str* GetAnswers()const { return this->_answers; }


	void Show()
	{
		cout << this->_question << endl;
		cout << endl;
		cout << "A) " << this->_answers[0] << endl;
		cout << "B) " << this->_answers[1] << endl;
		cout << "C) " << this->_answers[2] << endl;
		cout << "D) " << this->_answers[3] << endl;
		cout << endl;
	}


};

int Question::question_number = 1;
class Quiz
{
	vector<Question*> _questions;
	str _filename;

public:
	Quiz()
	{

	}
	Quiz(Question* question, str filename)
	{
		SetFilename(filename);
		_questions.push_back(question);
	}

	void SetFilename(str filename)
	{
		if (filename.size() >= 3)
		{
			this->_filename = filename + ".txt";
			return;
		}
		else
		{
			try
			{
				throw new InvalidArgument("Filename is wrong", __LINE__, __FILE__, __TIME__, __DATE__);
			}
			catch (Exception* ex)
			{
				system("cls");
				Throw_add_writeErrorFile("Filename is wrong", ex);
				throw new InvalidArgument("Filename is wrong", __LINE__, __FILE__, __TIME__, __DATE__);
			}


		}
	}

	inline vector<Question*> GetQuestions()const { return this->_questions; }
	inline str GetFilename()const { return this->_filename; }
	inline void addQuestion(Question* q1)
	{
		_questions.push_back(q1);
	}

	void ShowAllQuestions()
	{
		for (auto items : _questions)
		{
			items->Show();
		}
		cout << endl;
	}

};