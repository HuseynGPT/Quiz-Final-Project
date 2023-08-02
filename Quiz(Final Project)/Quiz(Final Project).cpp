#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <cassert>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;
#pragma warning(disable : 4996)
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
typedef string str;
#include "Exception.h"
#include "Models.h"
#include "Functions.h"

int login_menu_row = 0, login_menu_column = 0;
int admin_menu_row = 0, admin_menu_column = 0;
int user_menu_row = 0, user_menu_column = 0;
int quiz_secimleri_row = 0, quiz_secimleri_column = 0;


char** login_menu = new char* [3]
{
	new char[] {" Sign Up"},
		new char[] {" Register"},
		new char[] {" Exit"}
};

char** admin_menu = new char* [5]
{
	new char[] {" Create new quiz"},
		new char[] {" Watch all quiz"},
		new char[] {" Check leaderboard"},
		new char[] {" Show Users"},
		new char[] {" Exit"}
};

char** user_menu = new char* [4]
{
	new char[] {" Start quiz"},
		new char[] {" Check leaderboard"},
		new char[] {" Show My Info"},
		new char[] {" Exit"},


};


char** quiz_menu_secimleri = new char* [3]
{
	new char[] {" Previus"},
		new char[] {" Next"},
		new char[] {" Sumbit"},
};

bool sortByScore(User* u1, User* u2)
{
	return u1->GetScore() > u2->GetScore();
}

int main()
{
	srand(time(NULL));
	int log_menu_input;
	int admin_menu_input;
	int user_menu_input;

	vector<User*>users = loadUsersFromFile("users.txt");
	vector<Quiz*> quizes;


	while (true)
	{
	main_menu:
		system("cls");
		showClock();

		ReadLogosFromFile("MAIN MENU LOGO.txt");
		login_menu[login_menu_row][login_menu_column] = '>';
		print_menu(login_menu, login_menu_row, 3);
		log_menu_input = _getch();
		MyMenu(login_menu, 3, login_menu_row, login_menu_column, log_menu_input);
		if (login_menu_row == 0 && log_menu_input == 13)
		{
			system("cls");
			showClock();

			str username_input;
			str password_input;
			ReadLogosFromFile("sign_logo.txt");
			if (SignUp(username_input, password_input))
			{
				if (username_input.compare("admin") == 0 && password_input.compare("admin123") == 0)
				{
					while (1)
					{
						system("cls");
						showClock();

						admin_menu[admin_menu_row][admin_menu_column] = '>';
						print_menu(admin_menu, admin_menu_row, 5);
						admin_menu_input = _getch();
						MyMenu(admin_menu, 5, admin_menu_row, admin_menu_column, admin_menu_input);
						//Create quiz
						if (admin_menu_row == 0 && admin_menu_input == 13)
						{
							system("cls");
							int num = 1;
							Quiz* myQuiz = new Quiz();
							str filename;
							cout << "Enter file name: "; cin >> filename;
							cout << endl;
							int sualSayi;
							cout << "Nece sualdan ibaret olacaq ?"; cin >> sualSayi;
							cout << endl;
							myQuiz->SetFilename(filename);
							while (num != sualSayi+1)
							{
								str question, correct_answer;
								str* answers = new str[4];
								Question* q1 = new Question();
								cin.ignore();
								cout << "Enter " << num << " question: ";  getline(cin, question);
								cout << endl;
								cout << "Enter answers:\n";
								cout << "[A] ---> "; getline(cin, answers[0]);
								cout << "[B] ---> "; getline(cin, answers[1]);
								cout << "[C] ---> "; getline(cin, answers[2]);
								cout << "[D] ---> "; getline(cin, answers[3]);
								cout << endl;
								cout << "Enter correct answer: "; getline(cin, correct_answer);
								q1->SetQuestion(question);
								q1->SetAnswers(answers);
								q1->SetCorrectAnswer(correct_answer);
								myQuiz->addQuestion(q1);
								num++;
							}
							writeFileNameToFile(filename);
							cout << endl;
							system("cls");
							writeQuizToFile(myQuiz);
							SetConsoleTextAttribute(console, 2);
							cout << "Quiz created succesfulyy" << endl;
							SetConsoleTextAttribute(console, 7);
							quizes.push_back(myQuiz);
							system("pause");
						}
						//Show quizes
						else if (admin_menu_row == 1 && admin_menu_input == 13)
						{
							system("cls");
							vector<str>filenames = readQuizNames("Quizler/All quizes.txt");
							if (filenames.empty())
								cout << "Quiz yoxdur" << endl;
							else
							{
								int counter = 1;
								for (auto items : filenames)
								{
									cout << counter << "." << items << endl;
									counter++;
								}
							}
							cout << endl;
							system("pause");
						}
						//Leaderboard
						if (admin_menu_row == 2 && admin_menu_input == 13)
						{
							system("cls");
							sort(begin(users), end(users), sortByScore);
							cout << "--------------Leaderboard-----------------" << endl;
							int counter = 1;
							int i = 3;
							cout << "        Name       |        Score         " << endl;
							cout << "------------------------------------------" << endl;
							for (auto items : users)
							{
								cout << counter << '.';
								SetConsoleTextAttribute(console, i);
								cout << " " << items->GetUsername() << " ";
								SetConsoleTextAttribute(console, 2);
								cout << "            ";
								cout << items->GetScore() << endl;
								SetConsoleTextAttribute(console, 7);
								cout << "------------------------------------------" << endl;
								counter++;
								i++;
							}
							system("pause");
						}
						// Show all users
						else if (admin_menu_row == 3 && admin_menu_input == 13)
						{
							system("cls");
							cout << "---------------------------------\n";
							int i = 1;
							for (auto items : users)
							{

								SetConsoleTextAttribute(console, i);

								items->Show();
								cout << endl;
								i++;
							}
							SetConsoleTextAttribute(console, 7);
							cout << "---------------------------------\n";
							system("pause");
						}
						// Exit
						else if (admin_menu_row == 4 && admin_menu_input == 13)
							goto main_menu;
					}
				}
				else
				{
					while (1)
					{
						system("cls");
						showClock();
						cout << endl;
						cout << endl;
						user_menu[user_menu_row][user_menu_column] = '>';
						print_menu(user_menu, user_menu_row, 4);
						user_menu_input = _getch();
						MyMenu(user_menu, 4, user_menu_row, user_menu_column, user_menu_input);
						User* user = findUserfromUsersList(users, username_input, password_input);

						//Start Quiz
						if (user_menu_row == 0 && user_menu_input == 13)
						{
							system("cls");
							int selectedItem = 0;
							int key;
							vector<str>filenames = readQuizNames("Quizler/All quizes.txt");
							str saved_quiz_name;
							while (1)
							{
								displayMenu(filenames, selectedItem);
								key = _getch();

								saved_quiz_name = filenames[selectedItem];
								if (key == 72)
								{
									selectedItem = (selectedItem - 1 + filenames.size()) % filenames.size();
									saved_quiz_name = filenames[selectedItem];
								}
								if (key == 80)
								{

									selectedItem = (selectedItem + 1) % filenames.size();
									saved_quiz_name = filenames[selectedItem];

								}
								if (key == 13)
									break;
							}
							int r = 0;

							if (filenames.empty())
								cout << "Quiz yoxdur" << endl;
							else
							{
								vector<Question*>quiz = findQuizFromFilename(saved_quiz_name);
								int sual_sayi = 0;
								int dogru_cavablar = 0;
								int sehv_cavablar = 0;
								int bos_cavablar = 0;

								int r1 = 0, c1 = 0;
								int answers_input;

								while (1)
								{
									system("cls");
									cout << quiz[sual_sayi]->GetQuestion() << endl;
									str* answers = new str[7]
									{
										 quiz[sual_sayi]->GetAnswers()[0],
										 quiz[sual_sayi]->GetAnswers()[1],
										  quiz[sual_sayi]->GetAnswers()[2],
										 quiz[sual_sayi]->GetAnswers()[3] + "\n",
										(" Next"),
										(" Previus"),
										(" Sumbit"),

									};
									//shuffleAnswers(answers, 3);
									print_menu(answers, r1, 7, answers_input);
									answers_input = _getch();
									MyMenu(answers, 7, r1, c1, answers_input);


									if (r1 == 0 && answers_input == 13)
									{
										SetConsoleTextAttribute(console, 1);

										if (answers[0].compare(quiz[sual_sayi]->GetCorrectAnswer()) == 0)
										{
											dogru_cavablar++;
										}
										else
											sehv_cavablar++;
										if (sual_sayi < quiz.size())
										{
											sual_sayi++;

										}
										if (sual_sayi == quiz.size())
										{
											system("cls");
											SetConsoleTextAttribute(console, 2);
											cout << "\t\t\t Quiz i bitirdiniz!!!!" << endl;
											SetConsoleTextAttribute(console, 7);
											char choice;
											cout << "Son sualdasiniz bitirmek isteyirsiniz? "; cin >> choice;
											if (choice == 'y')
											{
												system("pause");
												break;
											}
											else
											{
												sual_sayi = quiz.size() - 1;
											}
										}
										SetConsoleTextAttribute(console, 7);
									}
									if (r1 == 1 && answers_input == 13)
									{
										SetConsoleTextAttribute(console, 8);
										if (answers[1].compare(quiz[sual_sayi]->GetCorrectAnswer()) == 0)
										{
											dogru_cavablar++;
										}
										else
											sehv_cavablar++;
										if (sual_sayi < quiz.size())
										{
											sual_sayi++;

										}
										if (sual_sayi == quiz.size())
										{
											system("cls");
											SetConsoleTextAttribute(console, 2);
											cout << "\t\t\t Quiz i bitirdiniz!!!!" << endl;
											SetConsoleTextAttribute(console, 7);
											char choice;
											cout << "Son sualdasiniz bitirmek isteyirsiniz? "; cin >> choice;
											if (choice == 'y')
											{
												system("pause");
												break;
											}
											else
											{
												sual_sayi = quiz.size() - 1;
											}
											SetConsoleTextAttribute(console, 7);

										}
									}
									if (r1 == 2 && answers_input == 13)
									{
										SetConsoleTextAttribute(console, 8);

										if (answers[2].compare(quiz[sual_sayi]->GetCorrectAnswer()) == 0)
										{
											dogru_cavablar++;
										}
										else
											sehv_cavablar++;
										if (sual_sayi < quiz.size())
										{
											sual_sayi++;

										}
										if (sual_sayi == quiz.size())
										{
											system("cls");
											SetConsoleTextAttribute(console, 2);
											cout << "\t\t\t Quiz i bitirdiniz!!!!" << endl;
											SetConsoleTextAttribute(console, 7);
											char choice;
											cout << "Son sualdasiniz bitirmek isteyirsiniz? "; cin >> choice;
											if (choice == 'y')
											{
												system("pause");
												break;
											}
											else
											{
												sual_sayi = quiz.size() - 1;
											}
										}
										SetConsoleTextAttribute(console, 7);

									}
									if (r1 == 3 && answers_input == 13)
									{
										SetConsoleTextAttribute(console, 2);

										if (answers[3].compare(quiz[sual_sayi]->GetCorrectAnswer()) == 0)
										{
											dogru_cavablar++;
										}
										else
											sehv_cavablar++;
										if (sual_sayi < quiz.size())
										{
											sual_sayi++;

										}
										if (sual_sayi == quiz.size())
										{
											system("cls");
											SetConsoleTextAttribute(console, 2);
											cout << "\t\t\t Quiz i bitirdiniz!!!!" << endl;
											SetConsoleTextAttribute(console, 7);
											char choice;
											cout << "Son sualdasiniz bitirmek isteyirsiniz? "; cin >> choice;
											if (choice == 'y')
											{
												system("pause");
												break;
											}
											else
											{
												sual_sayi = quiz.size() - 1;
											}
										}
										SetConsoleTextAttribute(console, 7);

									}
									//next
									if (r1 == 4 && answers_input == 13)
									{
										if (sual_sayi < quiz.size())
										{
											sual_sayi++;

										}
										if (sual_sayi == quiz.size())
										{
											system("cls");
											SetConsoleTextAttribute(console, 4);
											cout << "\t\t\tSiz sonuncu Sualdasiz" << endl;
											SetConsoleTextAttribute(console, 7);
											sual_sayi = quiz.size() - 1;
											system("pause");
										}

									}
									//previus
									if (r1 == 5 && answers_input == 13)
									{

										if (sual_sayi >= 0)
											sual_sayi--;
										if (sual_sayi < 0)
										{
											sual_sayi = 0;
											system("cls");
											SetConsoleTextAttribute(console, 4);
											cout << "\t\t\tSiz Birinci Sualdasiniz!!" << endl;
											SetConsoleTextAttribute(console, 7);
											system("pause");
										}

									}
									if (r1 == 6 && answers_input == 13)
									{
										bos_cavablar = quiz.size() - dogru_cavablar - sehv_cavablar;
										break;
									}
								}
								system("cls");
								SetConsoleTextAttribute(console, 2);
								cout << "Dogru Cavablarin Sayi: " << dogru_cavablar << endl;
								SetConsoleTextAttribute(console, 4);
								cout << "Sehv Cavablarin Sayi: " << sehv_cavablar << endl;
								SetConsoleTextAttribute(console, 7);
								cout << "Bos Cavablarin Sayi: " << bos_cavablar << endl;
								user->uptadeScore(dogru_cavablar, sehv_cavablar, bos_cavablar);
								system("pause");
							}

						}
						//Leaderboard
						if (user_menu_row == 1 && user_menu_input == 13)
						{
							system("cls");
							sort(begin(users), end(users), sortByScore);
							cout << "--------------Leaderboard-----------------" << endl;
							int counter = 1;
							int i = 3;
							cout << "        Name       |        Score         " << endl;
							cout << "------------------------------------------" << endl;
							for (auto items : users)
							{
								cout << counter << '.';
								SetConsoleTextAttribute(console, i);
								cout << " " << items->GetUsername() << " ";
								SetConsoleTextAttribute(console, 2);
								cout << "            ";
								cout << items->GetScore() << endl;
								SetConsoleTextAttribute(console, 7);
								cout << "------------------------------------------" << endl;
								counter++;
								i++;
							}
							system("pause");
						}
						//Show My Info
						if (user_menu_row == 2 && user_menu_input == 13)
						{
							system("cls");
							cout << "--------------------------\n";
							SetConsoleTextAttribute(console, 2);
							user->Show();
							SetConsoleTextAttribute(console, 7);
							cout << "--------------------------\n";
							system("pause");
						}

						//Exit
						if (user_menu_row == 3 && user_menu_input == 13)
						{
							writeAllUserToFile(users);
							goto main_menu;
						}

					}
				}
			}
			else
			{
				try
				{
					throw new DatabaseException("Username or password is wrong", __LINE__, __FILE__, __TIME__, __DATE__);
				}
				catch (Exception* ex)
				{
					system("cls");
					Throw_add_writeErrorFile("Username or password is wrong", ex);
				}
			}
			system("pause");
		}
		if (login_menu_row == 1 && log_menu_input == 13)
		{
			system("cls");
			ReadLogosFromFile("register_logo.txt");
			User* new_user = Register();
			users.push_back(new_user);

			system("pause");
		}
		if (login_menu_row == 2 && log_menu_input == 13)
		{
			system("cls");
			break;
		}
	}
}

