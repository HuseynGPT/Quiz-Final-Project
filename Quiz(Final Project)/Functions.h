#pragma once



void MyMenu(char**& arr, int count, int& _row, int& _column, int input)
{
	if (input == 224)
	{
		input = _getch();
		//UP
		if (int(input) == 72)
		{
			if (_row == 0)
			{
				arr[_row][_column] = ' ';
				_row = count - 1;
			}
			else
			{
				_row--;
				arr[_row + 1][_column] = ' ';
			}
		}
		//Down
		else if (int(input) == 80)
		{


			_row++;
			arr[_row - 1][_column] = ' ';


		}


		if (_row == -1 && input == 72)
		{
			_row = 0;
			arr[_row][_column] = ' ';
			_row = count - 1;
		}
		if (_row == count && input == 80)
		{


			arr[_row - 1][_column] = ' ';
			_row = 0;
		}


	}

}

void MyMenu(str*& arr, int count, int& _row, int& _column, int input)
{
	if (input == 224)
	{
		input = _getch();
		//UP
		if (int(input) == 72)
		{
			if (_row == 0)
			{
				arr[_row][_column] = ' ';
				_row = count - 1;
			}
			else
			{
				_row--;
				arr[_row + 1][_column] = ' ';
			}
		}
		//Down
		else if (int(input) == 80)
		{


			_row++;
			arr[_row - 1][_column] = ' ';


		}


		if (_row == -1 && input == 72)
		{
			_row = 0;
			arr[_row][_column] = ' ';
			_row = count - 1;
		}
		if (_row == count && input == 80)
		{


			arr[_row - 1][_column] = ' ';
			_row = 0;
		}


	}

}

void print_menu(char** arr, int a, int size)
{
	system("color 7");
	cout << "\n\n\n\n\n\n";
	for (size_t i = 0; i < size; i++)
	{
		if (i == a)
			SetConsoleTextAttribute(console, 27);
		else
			SetConsoleTextAttribute(console, 7);
		cout << "\t\t\t\t\t\t";
		cout << arr[i] << " ";
		SetConsoleTextAttribute(console, 7);
		cout << endl;


	}

}

void print_menu(str* arr, int a, int size, int& input)
{
	system("color 7");
	for (size_t i = 0; i < size; i++)
	{
		if (i == a && input == 13)
			SetConsoleTextAttribute(console, 3);
		if (i == a)
			SetConsoleTextAttribute(console, 27);
		else
			SetConsoleTextAttribute(console, 7);
		
		if (i == 0)
		{
			cout << "A)";
		}
		if (i == 1)
		{
			cout << "B)";
		}
		if (i == 2)
		{
			cout << "C)";
		}
		if (i == 3)
		{
			cout << "D)";
		}
		cout << arr[i] << " ";
		SetConsoleTextAttribute(console, 7);
		cout << endl;


	}

}

User* Register()
{
	char ch;

	str username;
	str password;
	str first_name;
	str second_name;
	int age;
	cout << "-------------------------------------" << endl;
	cout << "Enter your username --> "; cin >> username;
	cout << "-------------------------------------" << endl;
	cout << "Enter your password --> ";
	while (true)
	{
		ch = _getch();
		if (ch == 13)
			break;
		password.push_back(ch);
		cout << "*";
	}
	cout << endl;
	cout << "-------------------------------------" << endl;
	cout << "Enter your first name --> "; cin >> first_name;
	cout << "-------------------------------------" << endl;
	cout << "Enter your second name --> "; cin >> second_name;
	cout << "-------------------------------------" << endl;
	cout << "Enter your age --> "; cin >> age;
	cout << "-------------------------------------" << endl;
	ofstream file("users.txt", ios::app);
	ofstream file2("users_for_login.txt", ios::app);

	if (username.size() < 3)
		assert(!"username wrong");
	if (password.size() < 5)
		assert(!"password wrong");
	if (first_name.size() < 3)
		assert(!"first name wrong");
	if (second_name.size() < 3)
		assert(!"second name wrong");
	if (age < 0)
		assert(!"Age wrong");
	if (file.is_open())
	{
		User* newUser = new User(username, password, first_name, second_name, age);
		file << username << " " << password << " " << first_name << " " << second_name << " " << age << " " << newUser->GetScore() << endl;
		file2 << username << " " << password << endl;
		SetConsoleTextAttribute(console, 2);
		cout << "Registration complated!!\n";
		SetConsoleTextAttribute(console, 7);
		return newUser;
	}
	else
	{
		SetConsoleTextAttribute(console, 3);
		cout << "File not openning!!\n";
		SetConsoleTextAttribute(console, 7);

	}
	file.close();


}

bool SignUp(str& username, str& password)
{
	char ch;
	cout << "-------------------------------------" << endl;
	cout << "Enter your username --> "; cin >> username;
	cout << "-------------------------------------" << endl;
	cout << "Enter your password --> ";
	while (true)
	{
		ch = _getch();
		if (ch == 13)
			break;
		password.push_back(ch);
		cout << "*";
	}
	cout << "t-------------------------------------" << endl;

	if (username.size() < 3)
		assert(!"username wrong");
	if (password.size() < 5)
		assert(!"password wrong");
	ifstream file("users_for_login.txt");
	if (file.is_open())
	{
		str username1, password1;
		while (file >> username1 >> password1)
		{

			if (username1 == username && password1 == password)
			{

				file.close();
				return true;
			}
		}
		file.close();
	}
	return false;
}

void ReadLogosFromFile(str filename)
{
	FILE* logo;
	fopen_s(&logo, filename.c_str(), "r");
	char symbol = getc(logo);
	while (symbol != EOF)
	{
		cout << symbol;
		symbol = getc(logo);
	}
	fclose(logo);

}

void writeQuizToFile(Quiz*& quiz)
{
	str file_name = "Quizler/" + quiz->GetFilename();
	ofstream file(file_name);
	vector<Question*> questions = quiz->GetQuestions();


	for (auto items : questions)
	{
		file << items->GetQuestion() << endl;
		file << items->GetAnswers()[0] << endl;
		file << items->GetAnswers()[1] << endl;
		file << items->GetAnswers()[2] << endl;
		file << items->GetAnswers()[3] << endl;
		file << items->GetCorrectAnswer() << endl;
	}
	file.close();
}

void writeFileNameToFile(str filename)
{
	str file_name = "Quizler/All quizes.txt";
	ofstream file(file_name, ios::app);

	file << filename << ".txt" << endl;
	file.close();

}

vector<User*> loadUsersFromFile(str filename)
{
	vector<User*> users;
	ifstream file(filename);


	if (file.is_open())
	{
		string username, password, first_name, second_name;
		int age;
		float score;
		while (file >> username >> password >> first_name >> second_name >> age >> score)
		{
			users.push_back(new User(username, password, first_name, second_name, age, score));
		}
		file.close();
	}

	return users;
}

User*& findUserfromUsersList(vector<User*> users, str username, str password)
{
	for (auto items : users)
	{
		if (items->GetUsername().compare(username) == 0 && items->GetPassword().compare(password) == 0)
		{
			return items;
		}
	}
}

vector<str> readQuizNames(str filename)
{
	vector<str>filenames;
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "file acilmadi" << endl;
	}
	str name;
	while (getline(file, name))
	{
		filenames.push_back(name);
	}
	file.close();
	return filenames;
}

vector<Question*> findQuizFromFilename(str filename)
{
	str namee = "Quizler/" + filename;
	vector<Question*> quiz;
	ifstream file(namee);
	if (file.is_open())
	{
		str question;
		str* answers = new str[4];
		str correct_answer;

		while (file.eof() == false)
		{
			getline(file, question);
			getline(file, answers[0]);
			getline(file, answers[1]);
			getline(file, answers[2]);
			getline(file, answers[3]);
			getline(file, correct_answer);
			
			quiz.push_back(new Question(question, correct_answer, answers, true));
		}

		file.close();
	}
	else
		cout << "fILE ACILA BILMEDI\n";
	return quiz;
}

void writeAllUserToFile(vector<User*> persons)
{
	ofstream file("users.txt");
	if (file.is_open())
	{
		for (auto items : persons)
		{
			file << items->GetUsername() << " " << items->GetPassword() << " " << items->GetFirstname() << " " << items->GetSecondname() << " " << items->GetAge() << " " << items->GetScore() << endl;

		}
		file.close();
		return;
	}
	else
	{
		cout << "File acila Bilmedi" << endl;
		return;
	}
}

void shuffleAnswers(str* answers, int size) 
{
	for (int i = size - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		swap(answers[i], answers[j]);
	}
}

void showClock()
{
	
	time_t t = time(0);
	struct tm* now = localtime(&t);


	int hour = now->tm_hour;
	int minute = now->tm_min;
	int second = now->tm_sec;

	cout << "----------" << endl;
	cout << "|" << setfill('0') << setw(2) << hour << "|"
		<< setfill('0') << setw(2) << minute << "|"
		<< setfill('0') << setw(2) << second  <<"|" << endl;
	cout << "----------" << endl;
	cout << endl;
}

void displayMenu(const vector<string>& menuItems, int selectedItem) {
	system("cls"); 

	for (int i = 0; i < menuItems.size(); ++i) {
		if (i == selectedItem) 
		{
			SetConsoleTextAttribute(console, 4);
			cout << ">>> ";
			SetConsoleTextAttribute(console, 7);
			cout << menuItems[i];
			SetConsoleTextAttribute(console, 4);
			cout << " <<<" << endl;
			SetConsoleTextAttribute(console, 7);
		}
		else {
			cout << "    " << menuItems[i] << endl;
		}
	}
}