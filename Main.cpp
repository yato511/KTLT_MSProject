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
	wprintf(L"\n-----Tiến hành đọc dữ liệu file CSV vào struct SV-----\n");
	SV* Data = NULL;
	int N = CountSV(input);
	GetInput(input, Data, N);
	wprintf(L"\n--->Đã đọc xong File CSV\n\n\n");

	//In thông tin sinh viên ra màn hình console
	PrintSV(Data, N);


	//Tên tập tin HTML mẫu
	wchar_t FileSample[] = L"Website/1212123.htm";

	//Bắt đầu tạo file HTML
	CreateHTML(FileSample, Data, N);
	wprintf(L"\n\n-------->Đã ghi xong %d file HTML\n", N);

	//Xóa vùng nhớ
	for (int i = 0; i < N; i++) {
		MemoryDelete(Data[i]);
	}
	if (Data != NULL)
		free(Data);
	wprintf(L"\n\n--------->Đã xóa vùng nhớ\n\n\n");

	wprintf(L"\n\n\n----------KẾT THÚC CHƯƠNG TRÌNH----------\n\n");
	_getch();
	return 0;
}