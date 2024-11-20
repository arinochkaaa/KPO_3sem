#include "Log.h"
#include "stdafx.h"
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdarg>
#include <locale>
#include <codecvt>
#include <ctime>

namespace Log {
	LOG getlog(wchar_t logfile[]) {

		LOG log;
		log.stream = new std::ofstream;
		log.stream->open(logfile);
		if (!log.stream->is_open())
		{
			throw ERROR_THROW(112);
		}
		wcscpy_s(log.logfile, logfile);

		return log;
	}

	void WriteLine(LOG log, char* c, ...) {
		char** pc = &c;
		int i = 0;
		while (*pc != "") {
			*log.stream << *pc;
			*pc++;
		}
		*log.stream << std::endl;
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{
		wchar_t** pc = &c;
		char l[1024] = "";
		char f[1024] = "";
		while (*pc != L"")
		{
			wcstombs_s(0, l, *pc, IN_MAX_LEN_TEXT);
			strcat_s(f, l);
			pc++;
		}
		*log.stream << f;
	}

	void WriteLog(LOG log) {
		char date[100];
		tm local;
		time_t currentTime;
		currentTime = time(NULL);
		localtime_s(&local, &currentTime);
		strftime(date, 100, "%d.%m.%Y %H:%M:%S", &local);
		*log.stream << "--- �������� --- ����: " << date << std::endl;
	}

	void WriteParm(LOG log, Parm::PARM parm) {

		char buff[PARM_MAX_SIZE];
		size_t tsize = 0;

		*log.stream << "---- ��������� ------" << std::endl;
		wcstombs_s(&tsize, buff, parm.log, PARM_MAX_SIZE);
		*log.stream << "-log: " << buff << std::endl;
		wcstombs_s(&tsize, buff, parm.out, PARM_MAX_SIZE);
		*log.stream << "-out: " << buff << std::endl;
		wcstombs_s(&tsize, buff, parm.in, PARM_MAX_SIZE);
		*log.stream << "-in: " << buff << std::endl;
	}

	void WriteIn(LOG log, In::IN in) {

		*log.stream << "---- �������� ������ ------" << std::endl;
		*log.stream << "���������� ��������: " << in.size << std::endl;
		*log.stream << "���������������: " << in.ignor << std::endl;
		*log.stream << "���������� �����: " << in.lines << std::endl;
		*log.stream << "���� ���� ��������: " << in.lines << std::endl;
		for (int i = 0; i < 256; i++) {
			*log.stream << in.code[i] << ' ';
			if (i % 16 == 0 && i != 0) *log.stream << std::endl;
		}
	}

	void WriteError(LOG log, Error::ERROR error) {

		*log.stream << "--- ������ --- " << std::endl;
		*log.stream << "������ " << error.id << ": " << error.message << std::endl;

		if (error.inext.line != -1)
		{
			*log.stream << "������ " << error.inext.line << " ������: " << error.inext.col << error.inext.col << " ������: " << error.inext.ch << std::endl << std::endl;			
		}
	}

	// ��������� �����
	void Close(LOG log) {
		log.stream->close();
		delete log.stream;
	}
}
