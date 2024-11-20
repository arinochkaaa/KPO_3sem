#include"stdafx.h"

#include"Error.h"
#include"Parm.h"
#include"Log.h"
#include"In.h"

int _tmain(int argc, _TCHAR* argv[]) {

	setlocale(LC_ALL, "rus");

	std::cout << "---- тест Parm::getparm ---" << std::endl << std::endl;
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);

		wcout << "-in: " << parm.in<<", -out: " << parm.out << ", -log: " << parm.log << endl<<endl;
	}
	catch (Error::ERROR e) {
		cout << "Ошибка " << e.id << "!!!:" << e.message << endl<<endl;
	};

	std::cout << "---- тест In::getin ---" << std::endl << std::endl;
	try { 
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		cout << in.text << endl;
		cout <<"Всего символов: " << in.size << endl;
		cout << "Всего строк: " << in.lines << endl;
		cout << "Пропущено: " << in.ignore << endl;
	}
	catch (Error::ERROR e) {
		cout << "Ошибка " << e.id << ":" << e.message << endl;
	}

	Log::LOG log;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, (char*)"Тест:", (char*)" успешно\n", "");
		Log::WriteLine(log, (char*)"Тест:", (char*)" успешно\n", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	};




	/*setlocale(LC_ALL, "rus");
	std::cout << "---- test Error::geterror ---" << std::endl << std::endl;
	try { throw ERROR_THROW(100); }
	catch (Error::ERROR e) {
		std::cout << "Error" << e.id << ":" << e.message << std::endl << std::endl;
	};

	std::cout<<"---- test Error::geterrorin ---" << std::endl << std::endl;
	try { throw ERROR_THROW_IN(111, 7, 7); }
	catch (Error::ERROR e) {

	std::cout << "error" << e.id << ":" << e.message
		<< ",stroke" << e.inext.line
		<< ",position" << e.inext.col << std::endl << std::endl;
	};*/
	

	system("pause");
	return 0;


}