#include "Header.h"

int wmain(int argc, wchar_t *argv[]) {

	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input


	//Mở file CSV
	FILE* input = _wfopen(L"Data.csv", L"r, ccs=UTF-8");
	if (!input) {
		wprintf(L"Không thể mở file CSV\n");
		return 0;
	}

	//Đọc tập tin CSV vào struct
	SV* Data = NULL;
	int N = CountSV(input);
	GetInput(input, Data, N);


	//In thông tin sinh viên ra màn hình console
	for (int i = 0; i < N; i++)
	{
		wprintf(L"\n\nThông tin sinh viên thứ %ld:\n", i + 1);
		PrintSV(Data[i]);
	}


	//Tên tập tin HTML mẫu
	wchar_t FileSample[] = L"1212123.htm";

	//Bắt đầu tạo file HTML
	CreateHTML(FileSample, Data, N);


	//Xóa vùng nhớ
	for (int i = 0; i < N; i++) {
		MemoryDelete(Data[i]);
	}

	if (Data != NULL)
		free(Data);


	_getch();
	return 0;
}