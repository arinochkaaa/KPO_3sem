#include "stdafx.h"
#include "Error.h"    // обработка ошибок
#include "Parm.h"     // обработка параметров
#include "Log.h"      // работа с протоколом
#include "In.h"       // ввод исходного файла
#include "Out.h"       // вывод исходного файла в файл -out

using namespace std;

void TestGetParm(int argc, _TCHAR* argv[]) {
    cout << "---- тест getparm ----" << endl;
    try {
        Parm::PARM parm = Parm::getparm(argc, argv);
        wcout << "-in: " << parm.in << ", -out: " << parm.out << ", -log: " << parm.log << endl << endl;
    }
    catch (const Error::ERROR& e) {
        cout << "ID: " << e.id << " Сообщение: " << e.message
            << " Строка: " << e.inext.line
            << " Позиция: " << e.inext.col << endl;
    }
}

void TestGetIn(int argc, _TCHAR* argv[]) {
    cout << "---- тест getin ----" << endl;
    try {
        Parm::PARM parm = Parm::getparm(argc, argv);
        In::IN in = In::getin(parm.in);
        cout << in.text << endl;
        cout << "Всего символов: " << in.size << endl;
        cout << "Всего строк: " << in.lines << endl;
        cout << "Пропущено: " << in.ignor << endl;
    }
    catch (const Error::ERROR& e) {
        cout << "ID: " << e.id << " Сообщение: " << e.message
            << " Строка: " << e.inext.line
            << " Позиция: " << e.inext.col
            << " Символ: " << e.inext.ch << endl;
    }
}

void TestLog(int argc, _TCHAR* argv[]) {
    Log::LOG log;

    try {
        Parm::PARM parm = Parm::getparm(argc, argv);
        log = Log::getlog(parm.log);

        Log::WriteLine(log, (char*)"Тест", (char*)" без ошибок \n", (char*)"");
        Log::WriteLine(log, (wchar_t*)L"Тест", (wchar_t*)L" без ошибок \n", (wchar_t*)L"");
        Log::WriteLog(log);
        Log::WriteParm(log, parm);

        In::IN in = In::getin(parm.in);
        Log::WriteIn(log, in);

        Log::Close(log);
    }
    catch (const Error::ERROR& e) {
        Log::WriteError(log, e);
    }
}

void TestOut(int argc, _TCHAR* argv[]){
    Out::OUT out = Out::INITOUT;

    try {
        Parm::PARM parm = Parm::getparm(argc, argv);
        out = Out::getout(parm.out);
        In::IN in = In::getin(parm.in);
        Out::WriteInOut(out, in);
    }
    catch (Error::ERROR e)
    {
        Out::WriteErrorOut(out, e);
    };
}

int _tmain(int argc, _TCHAR* argv[]) {
    setlocale(LC_ALL, "russian");

    TestGetParm(argc, argv);
    TestGetIn(argc, argv);
    TestLog(argc, argv);
    TestOut(argc, argv);

    cout << "-------------------------------------------------------------------------" << endl;
    system("pause");

    return 0;
}
