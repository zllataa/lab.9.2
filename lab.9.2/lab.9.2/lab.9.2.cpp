#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;

enum Specialyty { CS, INFORM, MATHandECONOM, PHISYCSandINFORM, WORKTRAINING };
// КОМПЮТЕРНІ НАУКИ, ІНФОРМАТИКА, МАТЕМАТИКА І ЕКОНОМІКА, ФІЗИКА І ІНФОРМАТИКА, ТРУДОВЕ НАВЧАННЯ

string specialytyStr[] = { "КОМПЮТЕРНІ НАУКИ", "ІНФОРМАТИКА", "МАТЕМАТИКА І ЕКОНОМІКА", "ФІЗИКА І ІНФОРМАТИКА", "ТРУДОВЕ НАВЧАННЯ" };

struct Student
{
    string lastName;
    int course;
    Specialyty specialyty;
    int markPHISICS;
    int markMATH;
    union
    {
        int markPROGRAMMING;
        int markNUMERICALMETHODS;
        int markPEDAGOGICS;
    };
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);
double LineSearch(Student* s, const int N);
double LineSearch1(Student* s, const int N);
void Sort(Student* s, const int N);
int BinSearch(Student* s, const int N, const string lastName, const Specialyty specialyty);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);

int main()
{
    SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
    int N;
    cout << "Введіть к-сть студентів: "; cin >> N;

    Student* s = new Student[N];
    double percent;
    string lastName;
    int ispecialyty;
    Specialyty specialyty;
    int found;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - вивід проценту студентів, " << endl;
        cout << "які вчаться без трійок (на “відмінно” і “добре): " << endl << endl;
        cout << " [4] - вивід прізвищ студентів, " << endl;
        cout << "які отримали з фізики оцінки “5” або “4”: " << endl << endl;
        cout << " [5] - фізичне впорядкування даних" << endl << endl; // Фізичне впорядкування масиву структур
        cout << " [6] - бінарний пошук студента"  << endl;
        cout << "за номером курсу та прізвищем"<< endl << endl; // Бінарний пошук в масиві структур
        cout << " [7] - індексне впорядкування та вивід даних" << endl << endl; // Індексне впорядкування масиву структур
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
        case 1:
            Create(s, N);
            break;
        case 2:
            Print(s, N);
            break;
        case 3:
            percent = LineSearch(s, N);
            cout << " Процент студентів, які вчаться без трійок (на “відмінно” і “добре):" << endl;
            cout << percent << "%" << endl;
            break;
        case 4:
            LineSearch1(s, N);
            break;
        case 5:
            Sort(s, N);
            break;
        case 6:
            cout << "Введіть ключі пошуку:" << endl;
            cout << " спеціальність(0 - КОМПЮТЕРНІ НАУКИ, 1 - ІНФОРМАТИКА, 2 - МАТЕМАТИКА І ЕКОНОМІКА, 3 - ФІЗИКА І ІНФОРМАТИКА, 4 - ТРУДОВЕ НАВЧАННЯ): ";
            cin >> ispecialyty; 
            specialyty = (Specialyty)ispecialyty;
            cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
            cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
            cout << " прізвище: "; getline(cin, lastName);
            cout << endl;
            if ((found = BinSearch(s, N, lastName, specialyty)) != -1)
                cout << "Знайдено працівника в позиції " << found + 1 << endl;
            else
                cout << "Шуканого працівника не знайдено" << endl;
            break;
        case 7:
            PrintIndexSorted(s, IndexSort(s, N), N);
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);
    return 0;
}

void Create(Student* s, const int N)
{
    int specialyty;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << " Прізвище: "; getline(cin, s[i].lastName);
        cout << " Курс: "; cin >> s[i].course;
        cout << " Спеціальність(0 - КОМПЮТЕРНІ НАУКИ, 1 - ІНФОРМАТИКА, 2 - МАТЕМАТИКА І ЕКОНОМІКА, 3 - ФІЗИКА І ІНФОРМАТИКА, 4 - ТРУДОВЕ НАВЧАННЯ): ";
        cin >> specialyty;
        s[i].specialyty = (Specialyty)specialyty;
        cout << " Оцінка з фізики: "; cin >> s[i].markPHISICS;
        cout << " Оцінка з математики: "; cin >> s[i].markMATH;
        switch (s[i].specialyty)
        {
        case CS:
            cout << " Оцінка з програмування: "; cin >> s[i].markPROGRAMMING;
            break;
        case INFORM:
            cout << " Оцінка з чисельних методів: "; cin >> s[i].markNUMERICALMETHODS;
            break;
        case MATHandECONOM:
            cout << " Оцінка з педагогіки: "; cin >> s[i].markPEDAGOGICS;
            break;
        case PHISYCSandINFORM:
            cout << " Оцінка з педагогіки: "; cin >> s[i].markPEDAGOGICS;
            break;
        case WORKTRAINING:
            cout << " Оцінка з педагогіки: "; cin >> s[i].markPEDAGOGICS;
            break;
        }
        cout << endl;
    }
}
void Print(Student* s, const int N)
{
    cout << "                                                                                                                                                    " << endl;
    cout << "                                                                                                                                                    " << endl;
    cout << "                                                        Рівень В) – дев’ять клітинок:                                                               " << endl;
    cout << "                              (1) – порядковий номер студента у групі, (2) – прізвище, (3) – курс,(4) – спеціальність,                              " << endl;
    cout << "                    оцінки з (5) – фізики, (6) – математики (клітинки цих оцінок заповнені для студентів всіх спеціальностей),                      " << endl;
    cout << "                                      оцінки з (7) – програмування, (8) – чисельних методів, (9) – педагогіки                                       " << endl;
    cout << "                              (заповнена лише одна з клітинок цих оцінок – залежно від спеціальності такого студента).                              " << endl;
    cout << "                                                                                                                                                    " << endl;
    cout << "  ================================================================================================================================================  " << endl;
    cout << " |   |                  |      |                                 |                                       Оцінка                                   | " << endl;
    cout << " | № |     Прізвище     | Курс |          Спеціальність          |--------------------------------------------------------------------------------| " << endl;
    cout << " |   |                  |      |                                 | з фізики | з математики | з програмування | з чисельних методів | з педагогіки | " << endl;
    cout << "  ================================================================================================================================================  " << endl;
    for (int i = 0; i < N; i++)
    {
        cout << " | " << right << i + 1 << " ";
        cout << "| " << setw(16) << left << s[i].lastName << " "
            << "| " << setw(4) << right << s[i].course << " "
            << "| " << setw(31) << left << specialytyStr[s[i].specialyty] << " ";
        cout << "| " << setw(8) << right << s[i].markPHISICS << " "
            << "| " << setw(12) << right << s[i].markMATH << " ";
        switch (s[i].specialyty)
        {
        case CS:
            cout << "| " << setw(15) << right << s[i].markPROGRAMMING << " |                     |              |" << endl;
            break;
        case INFORM:
            cout << "|                 | " << setw(19) << right << s[i].markNUMERICALMETHODS << " |              |" << endl;
            break;
        case MATHandECONOM:
            cout << "|                 |                     |" << setw(13) << right << s[i].markPEDAGOGICS << " |" << endl;
            break;
        case PHISYCSandINFORM:
            cout << "|                 |                     |" << setw(13) << right << s[i].markPEDAGOGICS << " |" << endl;
            break;
        case WORKTRAINING:
            cout << "|                 |                     |" << setw(13) << right << s[i].markPEDAGOGICS << " |" << endl;
            break;
        }
    }
    cout << "  ================================================================================================================================================  " << endl;
    cout << endl;
}

double LineSearch(Student* s, const int N)
{
    cout << " Прізвища студентів, які вчаться без трійок (на “відмінно” і “добре”):" << endl;
    int k = 0; // к-сть студентів які вчаться без трійок (на “відмінно” і “добре”)
    for (int i = 0; i < N; i++)
    {
        if (
            (s[i].markPHISICS > 3)
            &&
            (s[i].markMATH > 3)
            &&
            (s[i].markPROGRAMMING > 3)
            &&
            (s[i].markNUMERICALMETHODS > 3)
            &&
            (s[i].markPEDAGOGICS > 3)
            )
        {
            k++;
            cout << "   " << right << s[i].lastName << endl;
        }
    }
    return 100.0 * k / N;
}

double LineSearch1(Student* s, const int N)
{
    cout << " Прізвища студентів, які отримали з фізики оцінки “5” або “4”:" << endl;
    for (int i = 0; i < N; i++)
    {
        if ((s[i].markPHISICS == 4) || (s[i].markPHISICS == 5))
        {
            cout << "   " << right << s[i].lastName << endl;
        }
    }
    return 0;
}

void Sort(Student* s, const int N) //Фізичне впорядкування масиву структур
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((s[i1].course > s[i1 + 1].course)
                ||
                (s[i1].course == s[i1 + 1].course &&
                    s[i1].markMATH > s[i1 + 1].markMATH)
                ||
                (s[i1].course == s[i1 + 1].course &&
                    s[i1].markMATH == s[i1 + 1].markMATH &&
                    s[i1].lastName < s[i1 + 1].lastName))
            {
                tmp = s[i1];
                s[i1] = s[i1 + 1];
                s[i1 + 1] = tmp;
            }
}

int BinSearch(Student* s, const int N, const string lastName, const Specialyty specialyty)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (s[m].lastName == lastName && s[m].specialyty == specialyty)
            return m;
        if ((s[m].specialyty < specialyty)
            ||
            (s[m].specialyty == specialyty &&
                s[m].lastName < lastName))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}

int* IndexSort(Student* s, const int N)
{
    int* I = new int[N];// створили індексний масив
    for (int i = 0; i < N; i++)
        I[i] = i; // заповнили його початковими даними
    int i, j, value; // починаємо сортувати масив індексів
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
            j >= 0 && ((s[I[j]].specialyty > s[value].specialyty) ||
                (s[I[j]].specialyty == s[value].specialyty &&
                    s[I[j]].lastName > s[value].lastName));
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(Student* s, int* I, const int N)
{
    cout << "                                                                                                                                                    " << endl;
    cout << "  ================================================================================================================================================  " << endl;
    cout << " |   |                  |      |                                 |                                       Оцінка                                   | " << endl;
    cout << " | № |     Прізвище     | Курс |          Спеціальність          |--------------------------------------------------------------------------------| " << endl;
    cout << " |   |                  |      |                                 | з фізики | з математики | з програмування | з чисельних методів | з педагогіки | " << endl;
    cout << "  ================================================================================================================================================  " << endl;
    for (int i = 0; i < N; i++)
    {
        cout << " | " << right << i + 1 << " "; 
        cout << "| " << setw(16) << left << s[I[i]].lastName << " "
            << "| " << setw(4) << right << s[I[i]].course << " "
            << "| " << setw(31) << left << specialytyStr[s[I[i]].specialyty] << " ";
        cout << "| " << setw(8) << right << s[I[i]].markPHISICS << " "
            << "| " << setw(12) << right << s[I[i]].markMATH << " ";
        switch (s[I[i]].specialyty)
        {
        case CS:
            cout << "| " << setw(15) << right << s[I[i]].markPROGRAMMING << " |                     |              |" << endl;
            break;
        case INFORM:
            cout << "|                 | " << setw(19) << right << s[I[i]].markNUMERICALMETHODS << " |              |" << endl;
            break;
        case MATHandECONOM:
            cout << "|                 |                     |" << setw(13) << right << s[I[i]].markPEDAGOGICS << " |" << endl;
            break;
        case PHISYCSandINFORM:
            cout << "|                 |                     |" << setw(13) << right << s[I[i]].markPEDAGOGICS << " |" << endl;
            break;
        case WORKTRAINING:
            cout << "|                 |                     |" << setw(13) << right << s[I[i]].markPEDAGOGICS << " |" << endl;
            break;
        }
    }
    cout << "  ================================================================================================================================================  " << endl;
    cout << endl;
}
