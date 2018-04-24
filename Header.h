#define _CRT_SECURE_NO_WARNINGS
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <wchar.h>

struct SinhVien {
	wchar_t *MSSV;
	wchar_t *HoVaTen;
	wchar_t *Faculty;
	int	Khoa;
	wchar_t *NgaySinh;
	wchar_t *Email;
	wchar_t *HinhAnh;
	wchar_t *Mota;
	wchar_t **SoThich;
	int HobbyCount;
};
typedef struct SinhVien SV;



					//KHAI BÁO CÁC HÀM DÙNG TRONG CHƯƠNG TRÌNH
	
	//CSV
int GetWS(FILE*fp, wchar_t*s);
int CountSV(FILE* fp);
void GetSV(FILE*fp, SV &a);
void GetInput(FILE*fp, SV* &data, int n);

	//HTML
wchar_t* CreateFileName(wchar_t* mssv, wchar_t* tail);
void CreateHTML(wchar_t* FileSample, SV* data, int sl);

	//Sub Function
void PrintSV(SV a);
void MemoryDelete(SV &a);
void MemoryInit(SV& a);
void Upper(wchar_t *str);
int FindSubString(wchar_t* str, wchar_t* substr);
void ReplaceString(wchar_t* buf, wchar_t*BeginSign, wchar_t*EndSign, wchar_t*str);