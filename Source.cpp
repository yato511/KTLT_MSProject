#define _CRT_SECURE_NO_WARNINGS
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <wchar.h>


struct SinhVien {
	char *MSSV;
	wchar_t *HoVaTen;
	wchar_t *Faculty;
	int	Khoa;
	char *NgaySinh;
	char *Email;
	wchar_t *HinhAnh;
	wchar_t *Mota;
	wchar_t *SoThich;
};
typedef struct SinhVien SV;

#define maxSize 8000

void MemoryInit(SV &a) {
	a.MSSV = (char*)malloc(10 * sizeof(char));
	a.HoVaTen = (wchar_t*)malloc(30 * sizeof(char));
	a.Faculty = (wchar_t*)malloc(30 * sizeof(char));
	a.NgaySinh = (char*)malloc(10 * sizeof(char));
	a.Email = (char*)malloc(30 * sizeof(char));
	a.HinhAnh = (wchar_t*)malloc(30 * sizeof(char));
	a.Mota = (wchar_t*)malloc(1000 * sizeof(char));
	a.SoThich = (wchar_t*)malloc(1000 * sizeof(char));
}

void MemoryDelete(SV &a) {
	if (a.MSSV != NULL) free(a.MSSV);
	if (a.HoVaTen != NULL) free(a.HoVaTen);
	if (a.Faculty != NULL) free(a.Faculty);
	if (a.NgaySinh != NULL) free(a.NgaySinh);
	if (a.Email != NULL) free(a.Email);
	if (a.HinhAnh != NULL) free(a.HinhAnh);
	if (a.Mota != NULL) free(a.Mota);
	if (a.SoThich != NULL) free(a.SoThich);
}
int GetString(wchar_t* buf,char* &data, int beginpos) {
	data = (char*)malloc(sizeof(char)*10);
	int length = 0;
	int i;
	for (i = beginpos; buf[i] != '"'; i++) {
		data[length] = buf[i];
		length++;
	}
	data[length] = '\0';
	return i;
}
void GetWString(wchar_t* buf, wchar_t* wdata) {

}

//void GetData(wchar_t* buf,SV data) {
//	char*p;
//	while (p = )
//}

int main() //int argc, wchar_t *argv[]
{
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input

	wchar_t *buf = (wchar_t*)malloc(maxSize);
	//wchar_t *buf = NULL;
	FILE* fileCSV = _wfopen(L"Data.csv", L"r, ccs=UTF-8");
	if (!fileCSV) {
		wprintf(L"Không thể đọc file\n");
	}


	SV *data = NULL;
	int dem = 0;

	while (fgetws(buf, maxSize, fileCSV) != NULL)
	{
		buf[wcslen(buf) - 1] = L'\0'; // eat the newline fgets() stores
		wprintf(L"%s\n", buf);
		data = (SV*)realloc(data, sizeof(SV)*(dem + 1));
		MemoryInit(data[dem]);
		GetString(buf, data[dem].MSSV, 1);
		printf("%s\n", data[dem].MSSV);
		dem++;
	}
	if (data != NULL)
		free(data);
	fclose(fileCSV);
	_getch();
	return 0;
}