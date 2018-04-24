#include "Header.h"

int wmain(int argc, wchar_t *argv[]) {

	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input

	FILE* input = _wfopen(L"thongtin.csv", L"r, ccs=UTF-8");
	if (!input) {
		wprintf(L"Không thể mở file CSV\n");
		return 0;
	}


	wchar_t FileSample[] = L"1212123.htm";
	SV* Data = NULL;
	int N = CountSV(input);
	GetInput(input, Data, N);
	for (int i = 0; i < N; i++)
	{
		wprintf(L"Thông tin sinh viên thứ %ld:\n", i + 1);
		PrintSV(Data[i]);
	}
	CreateHTML(FileSample, Data, N);
	for (int i = 0; i < N; i++) {
		MemoryDelete(Data[i]);
	}
	if (Data != NULL)
		free(Data);
	if (Data == NULL) {
		wprintf(L"Cleared\n");
	}
	else wprintf(L"Uncleared\n");


	_getch();
	return 0;
}