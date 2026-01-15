#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix1 = 5 };

struct stRoundInfo
{
	int UserAnswer = 0;
	int RightAnswer = 0;

	char Operator = '-';

	int FirstNumber = 0;
	int SecondNumber = 0;

	enQuestionsLevel Level;
	enOperationType OperationType;
};

struct stGameResults
{
	short NumberOfQuestions = 0;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;

	string LevelName = "";
	string OpTypeName = "";
};

int RandomNumber(int From, int To)
{
	int RandomValue = rand() % (To - From + 1) + From;

	return RandomValue;
}

short ReadQuestionsNumbers()
{
	short QuestionsNumber = 0;

		cout << "How Many Questions Do You Want to Answer? ";
		cin >> QuestionsNumber;

		return QuestionsNumber;
}

enQuestionsLevel ReadQuestionLevle()
{
	short QuestionLevel = 0;

	do
	{
		cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
	short OperationType = 0;

	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix? ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType > 5);

	return (enOperationType)OperationType;
}

int GetRandomNumber(enQuestionsLevel Level)
{
	switch (Level)
	{
	case enQuestionsLevel::Easy:
		return RandomNumber(1, 10);

	case enQuestionsLevel::Med:
		return RandomNumber(11, 50);

	case enQuestionsLevel::Hard:
		return RandomNumber(51, 100);

	case enQuestionsLevel::Mix:
		return RandomNumber(1, 100);
	}
}

int GetRightAnswer(stRoundInfo RoundInfo)
{
	switch (RoundInfo.Operator)
	{
	case '+':
		return RoundInfo.FirstNumber + RoundInfo.SecondNumber;

	case '-':
		return RoundInfo.FirstNumber - RoundInfo.SecondNumber;

	case '*':
		return RoundInfo.FirstNumber * RoundInfo.SecondNumber;

	case '/':
		return RoundInfo.FirstNumber / RoundInfo.SecondNumber;
	}
}

int ReadUserAnswer(stRoundInfo RoundInfo)
{
	int UserAnswer;

	cout << "\n" << RoundInfo.FirstNumber;
	cout << "\n" << RoundInfo.SecondNumber << " " << RoundInfo.Operator << endl;
	cout << "_________________\n";
	cin >> UserAnswer;

	return UserAnswer;
}

char GetOperator(enOperationType OpType)
{
	if (OpType == enOperationType::Mix1)
		OpType = enOperationType(RandomNumber(1, 4));

	switch (OpType)
	{
	case enOperationType::Add:
		return '+';

	case enOperationType::Sub:
		return '-';

	case enOperationType::Mul:
		return '*';

	case enOperationType::Div:
		return '/';
	}
}

void CheckAnswer(int UserAnswer, int RightAnswer, short& NumberOfRightAnswers, short& NumberOfWrongAnswers)
{
	if (UserAnswer == RightAnswer)
	{
		cout << "Right Answer :-)\n";
		system("color 2F");
		NumberOfRightAnswers++;
	}
	else
	{
		cout << "\aWrong Answer :-(\n";
		cout << "The Right Answer is: " << RightAnswer << endl;
		system("color 4F");
		NumberOfWrongAnswers++;
	}
}

string OpTypeName(enOperationType OpType)
{
	string arrOpTypeName[5] = { "Add", "Sub", "Mul", "Div", "Mix" };
	
	return arrOpTypeName[OpType - 1];
}

string LevelName(enQuestionsLevel Level)
{
	string arrLevelName[4] = { "Easy", "Med", "Hard", "Mix" };
	
	return arrLevelName[Level - 1];
}

stGameResults FillGameResults(short NumberOfQuestions, short NumberOfRightAnswers, short NumberOfWrongAnswers, stRoundInfo RoundInfo)
{
	stGameResults GameResults;

	GameResults.NumberOfQuestions = NumberOfQuestions;
	GameResults.NumberOfRightAnswers = NumberOfRightAnswers;
	GameResults.NumberOfWrongAnswers = NumberOfWrongAnswers;
	GameResults.OpTypeName = OpTypeName(RoundInfo.OperationType);
	GameResults.LevelName = LevelName(RoundInfo.Level);

	return GameResults;
}

void PrintFinalResultBar(short NumberOfRightAnswers, short NumberOfWrongAnswers)
{
	Sleep(2000);

	cout << "\n\n\n_________________________________________\n";
	
	if (NumberOfRightAnswers > NumberOfWrongAnswers)
	{
		cout << "\n  Final Result is PASS :-)\n";
		system("color 2F");
	}
	else
	{
		cout << "\n  Final Result is Fail :-(\n";
		system("color 4F");
	}

	cout << "_________________________________________\n";
}

void PrintGameResults(stGameResults GameResults)
{
	cout << "\nNumber of Questions   : " << GameResults.NumberOfQuestions << endl;
	cout << "Question Level          : " << GameResults.LevelName << endl;
	cout << "OpType                  : " << GameResults.OpTypeName << endl;
	cout << "Number of Right Answers : " << GameResults.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers : " << GameResults.NumberOfWrongAnswers << endl;
	cout << "_________________________________________\n";
}

stGameResults PlayGame(short NumberOfQuestions)
{
	stRoundInfo RoundInfo;

	short NumberOfRightAnswers = 0, NumberOfWrongAnswers = 0;

	RoundInfo.Level = ReadQuestionLevle();
	RoundInfo.OperationType = ReadOperationType();
	
	for (int Question = 1; Question <= NumberOfQuestions; Question++)
	{
		cout << "\n\nQuestion [" << Question << "/" << NumberOfQuestions << "]\n";

		RoundInfo.FirstNumber = GetRandomNumber(RoundInfo.Level);
		RoundInfo.SecondNumber = GetRandomNumber(RoundInfo.Level);
		RoundInfo.Operator = GetOperator(RoundInfo.OperationType);
		RoundInfo.UserAnswer = ReadUserAnswer(RoundInfo);
		RoundInfo.RightAnswer = GetRightAnswer(RoundInfo);

		CheckAnswer(RoundInfo.UserAnswer, RoundInfo.RightAnswer, NumberOfRightAnswers ,NumberOfWrongAnswers);
	}

	return FillGameResults(NumberOfQuestions, NumberOfRightAnswers, NumberOfWrongAnswers, RoundInfo);
}

void ResetScreen()
{
	system("color 0F");
	system("cls");
}

void StartGame()
{
	char PlayAgain = 'y';

	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadQuestionsNumbers());
		PrintFinalResultBar(GameResults.NumberOfRightAnswers, GameResults.NumberOfWrongAnswers);
		PrintGameResults(GameResults);

		cout << "\nDo You Want To Play Again? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}