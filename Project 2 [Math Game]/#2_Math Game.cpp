#include <iostream>  
#include <cstdlib>    
#include <ctime>      

using namespace std;

enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
    int Number1;
    int Number2;
    enOperationType OpType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool IsRigthAnswer = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestion = 0;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    enOperationType OpType;
    enQuestionLevel QuestionLevel;
    bool IsPass = false;
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short ReadHowManyQuestions()
{
    short lengthQuestions = 1;
    do
    {
        cout << "How many Questions do you want to answer ? ";
        cin >> lengthQuestions;

    } while (lengthQuestions < 1);

    return lengthQuestions;
}

enQuestionLevel ReadQuestionLevel()
{
    short QuestionLevel;
    do
    {
        cout << ("Enter Question Level: [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ? ");
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);

    return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
    short OpType;
    do
    {
        cout << ("Enter Operation Type: [1]:Add, [2]:Sub, [3]:Mult, [4]:Div, [5]:Mix ? ");
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);

    return (enOperationType)OpType;
}

int ReadPlayerAnswer()
{
    int Number;
    cin >> Number;
    return Number;
}

enOperationType GetOperationType()
{
    return (enOperationType) RandomNumber(1, 4);
}

int SimpleCalcolaat(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType) {

    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

stQuestion GenertQuestionQuizz(enOperationType OpType, enQuestionLevel QuestionLevel)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::Mix)
    {
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    }

    if (OpType == enOperationType::MixOp)
    {
        OpType = GetOperationType();
    }
    Question.OpType = OpType;

    switch (QuestionLevel)
    {
    case (enQuestionLevel::EasyLevel):
    {
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalcolaat(Question.Number1, Question.Number2, Question.OpType);
        Question.QuestionLevel = QuestionLevel;

        return Question;
    }

    case (enQuestionLevel::MedLevel):
    {
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalcolaat(Question.Number1, Question.Number2, Question.OpType);
        Question.QuestionLevel = QuestionLevel;

        return Question;
    }

    case (enQuestionLevel::HardLevel):
    {
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalcolaat(Question.Number1, Question.Number2, Question.OpType);
        Question.QuestionLevel = QuestionLevel;

        return Question;
    }
    }
}

void GenertQuestionQuizz(stQuizz& Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestion; Question++)
    {
        Quizz.QuestionList[Question] = GenertQuestionQuizz(Quizz.OpType, Quizz.QuestionLevel);
    }
}

void GenretColor(bool IsRigth)
{
    if (IsRigth)
        system("color 2f");
    else
    {
        system("color 4f");
        cout << "\a";
    }
}

char GetOpSymbol(enOperationType OperationType)
{
    char Op[4] = { '+', '-', '*', '/' };
    return Op[OperationType - 1]; 
}

void CarrutQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].IsRigthAnswer = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "Wrong Answer!" << endl;
        cout << "The right Answer is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }

    else
    {
        Quizz.QuestionList[QuestionNumber].IsRigthAnswer = true;
        Quizz.NumberOfRightAnswers++;

        cout << "Right Answer" << endl;
    }

    GenretColor(Quizz.QuestionList[QuestionNumber].IsRigthAnswer);
}

void PirntResultQuestion(stQuizz Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestion << "]\n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpSymbol(Quizz.QuestionList[QuestionNumber].OpType);
    cout << "\n__________" << endl;
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestion; QuestionNumber++)
    {
        PirntResultQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
        CarrutQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string OperationTypeSimple(enOperationType PlayChoice)
{
    string OperationType[5] = { "+","-","x","/"," Mix" };
    return OperationType[PlayChoice - 1];
}

string QuestionLevelTet(enQuestionLevel Winner)
{
    string QuestionLevel[4] = { "Easy", "Med", "Hard" , "Mix" };
    return QuestionLevel[Winner - 1];
}

string GetFinalResutlsText(bool Pass)
{
    if (Pass)
        return "Pass :-)";
    else
        return "Fial :-(";
}

void PirntQuizzResults(stQuizz Quizz)
{
    cout << "\n\n\n______________________________\n\n";
    cout << " Final Resutls is " << GetFinalResutlsText(Quizz.IsPass);
    cout << "\n______________________________\n";


    cout << "Number of Questions : " << Quizz.NumberOfQuestion << endl;
    cout << "Question Level      : " << QuestionLevelTet(Quizz.QuestionLevel) << endl;
    cout << "Operation Type      : " << OperationTypeSimple(Quizz.OpType) << endl;
    cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "______________________________\n\n";
}

void ResretScreen()
{
    system("cls");
    system("color 0f");
}

void PalyMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestion = ReadHowManyQuestions();
    Quizz.QuestionLevel = ReadQuestionLevel();
    Quizz.OpType = ReadOpType();

    GenertQuestionQuizz(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PirntQuizzResults(Quizz);

}

void StartGame()
{
    char PlayAgen = 'Y';
    do
    {
        ResretScreen();
        PalyMathGame();


        cout << "Do you want to paly again? Y/N ? ";
        cin >> PlayAgen;

    } while (PlayAgen == 'Y' || PlayAgen == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}