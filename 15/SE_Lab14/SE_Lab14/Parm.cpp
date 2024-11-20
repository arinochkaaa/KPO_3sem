#include "stdafx.h"
#include "Error.h"
#include "Parm.h"
#include <cwchar>

namespace Parm {

	void remove_txt_extension(wchar_t* str) {
		const wchar_t* extension = L".txt";
		wchar_t* pos = wcsstr(str, extension);
		if (pos != nullptr) {
			*pos = L'\0';  // ”станавливаем конец строки на место начала ".txt"
		}
	}

	PARM getparm(int argc, _TCHAR* argv[]) {
		PARM parm = { L"", L"", L"" }; // »нициализируем структуру пустыми строками

		// ѕеребираем аргументы командной строки
		for (int i = 1; i < argc; i++) {
			if (wcsstr(argv[i], PARM_IN) == argv[i]) {
				// ќбработка параметра -in:
				wcscpy_s(parm.in, argv[i] + wcslen(PARM_IN));
				if (wcslen(parm.in) > PARM_MAX_SIZE) {
					throw ERROR_THROW(104);
				}
			}
			else if (wcsstr(argv[i], PARM_OUT) == argv[i]) {
				// ќбработка параметра -out:
				wcscpy_s(parm.out, argv[i] + wcslen(PARM_OUT));
				if (wcslen(parm.out) > PARM_MAX_SIZE) {
					throw ERROR_THROW(104);
				}
			}
			else if (wcsstr(argv[i], PARM_LOG) == argv[i]) {
				// ќбработка параметра -log:
				wcscpy_s(parm.log, argv[i] + wcslen(PARM_LOG));
				if (wcslen(parm.log) > PARM_MAX_SIZE) {
					throw ERROR_THROW(104);
				}
			}
		}

		// ѕровер€ем, задан ли об€зательный параметр -in:
		if (wcslen(parm.in) == 0) {
			throw ERROR_THROW(100);
		}

		// ≈сли параметр -out: не задан, формируем его значение по умолчанию
		if (wcslen(parm.out) == 0) {
			wcscpy_s(parm.out, parm.in);
			//remove_txt_extension(parm.log);
			wcsncat_s(parm.out, PARM_OUT_DEFAULT_EXT, _TRUNCATE);
		}

		// ≈сли параметр -log: не задан, формируем его значение по умолчанию
		if (wcslen(parm.log) == 0) {
			wcscpy_s(parm.log, parm.in);
			//remove_txt_extension(parm.log);
			wcsncat_s(parm.log, PARM_LOG_DEFAULT_EXT, _TRUNCATE);
		}

		// ¬озвращаем заполненную структуру
		return parm;
	}
}
