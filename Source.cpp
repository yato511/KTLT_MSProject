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
	wchar_t *SoThich;
	//wchar_t **SoThich_extra;
};
typedef struct SinhVien SV;


//Số ký tự tối đa của các chuỗi, nếu có thay đổi chỉ cần thay đổi tại đây
int mssv = 11;
int hovaten = 31;
int faculty = 31;
int khoa = 4;
int ngaysinh = 11;
int email = 31;
int hinhanh = 31;
int mota = 1001;
int sothich = 1001;
#define maxSize 8000


//Các chuỗi để tìm kiếm và thay thế trong Sample.htm
wchar_t Title[] = L"<title>HCMUS - ";
wchar_t EndTitle[] = L"</title>";
wchar_t FalUp[] = L"<div class=\"Personal_Department\">KHOA ";
wchar_t EndFalUp[] = L"</div>";
wchar_t Email[] = L"Email: ";
wchar_t EndEmailTop[] = L"\n";
wchar_t Photo[] = L"<img src=\"";
wchar_t EndPhoto[] = L"\" class = \"Personal_Hinhcanhan\" / >";
wchar_t Name[] = L"<li>Họ và tên: ";
wchar_t End[] = L"</li>";
wchar_t Mssv[] = L"<li>MSSV: ";
wchar_t	Fal[] = L"<li>Sinh viên khoa ";
wchar_t Birth[] = L"<li>Ngày sinh :";
wchar_t Desc[] = L"<div class=\"Description\">";

wchar_t tail[] = L".htm";//Đuôi tên file


//Xóa vùng nhớ các con trỏ trong kiểu SV
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


//Xóa ký tự bị thừa
void Fix(wchar_t* s) {
	if (s == NULL) return;
	//Xóa ký tự
	wchar_t* s2 = s;
	for (; (*s2) != '\0'; ++s2)
	{
		if ((*s2 != '\n') && (*s2 != '\"') && (*s2 != '�'))
			*(s++) = *s2;
	}
	*s = '\0';
}

//Lấy dữ liệu kiểu chuỗi Unicode
wchar_t* GetWString(FILE *fp, int size)
{
	wchar_t *data = (wchar_t*)malloc(size * sizeof(wchar_t) * 2); //Vì wchar_t có lúc bằng 2 có lúc bằng 4
	wchar_t ch = fgetwc(fp);
	if (ch != L',')
	{
		if (ch == L'\"')  //TH1:"1","2",
		{
			fwscanf(fp, L"%[^\"]", data);
			fseek(fp, 1L, SEEK_CUR);
		}
		else  //TH2: 1,2,
		{
			fseek(fp, -1L, SEEK_CUR);
			fwscanf(fp, L"%[^,]", data);
		}
	}
	else
	{
		wchar_t ch2 = fgetwc(fp);
		if (ch2 == L'\"')  //TH3: ,"2","3",
		{
		fwscanf(fp, L"%[^\"]", data);
		fseek(fp, 1L, SEEK_CUR);
		}
		else //TH4: , 2, 3,
		{
			fseek(fp, -1L, SEEK_CUR);
			fwscanf(fp, L"%[^,]", data);
		}
	}
	Fix(data);
	return data;
}



//Lấy dữ liệu kiểu số nguyên
int GetNumb(FILE* fp, int size) {
	int data = 0;
	wchar_t* temp = NULL;
	temp = GetWString(fp, size);
	data = wcstol(temp, 0, 10);
	if (temp != NULL) {
		free(temp);
	}
	return data;
}


//Lấy dữ liệu cho 1 biến kiểu SV
SV GetSVData(FILE*fp) {
	SV data;
	data.MSSV = GetWString(fp, mssv);
	data.HoVaTen = GetWString(fp, hovaten);
	data.Faculty = GetWString(fp, faculty);
	data.Khoa = GetNumb(fp, khoa);
	data.NgaySinh = GetWString(fp, ngaysinh);
	data.Email = GetWString(fp, email);
	data.HinhAnh = GetWString(fp, hinhanh);
	data.Mota = GetWString(fp, mota);
	data.SoThich = GetWString(fp, sothich);
	return data;
}


//Lấy dữ liệu cho 1 mảng kiểu SV, biết trước số lượng
SV* GetInput(FILE*fp, int sl) {
	//rewind(fp);
	fseek(fp, 3L, SEEK_SET);
	SV *data_arr = (SV*)malloc(sizeof(SV)*sl);
	for (int i = 0; i < sl; i++) {
		data_arr[i] = GetSVData(fp);
	}
	return data_arr;
}


//Xác định số lượng cho mảng SV
int CountSV(FILE *&FileIn) {
	rewind(FileIn);
	int dem = 0;
	wchar_t ch;
	while (!feof(FileIn))
	{
		ch = fgetwc(FileIn);
		if (ch == L'\n')
		{
			dem++;
		}
	}
	return dem;
}


//In thông tin SV ra màn hình
void PrintSV(SV a) {
	wprintf(L" - MSSV:\t%ls\n", a.MSSV);
	wprintf(L" - Họ và tên:\t%ls\n", a.HoVaTen);
	wprintf(L" - Khoa:\t%ls\n", a.Faculty);
	wprintf(L" - Khóa tuyển:\t%ld\n", a.Khoa);
	wprintf(L" - Ngày sinh:\t%ls\n", a.NgaySinh);
	wprintf(L" - Email:\t%ls\n", a.Email);
	wprintf(L" - Hình ảnh cá nhân:\t%ls\n", a.HinhAnh);
	wprintf(L" - Mô tả bản thân:\t%ls\n", a.Mota);
	wprintf(L" - Sở thích:\t%ls\n\n\n", a.SoThich);
}


//Hàm tạo tên file HTML: MSSV.htm
wchar_t* CreateFileName(wchar_t* mssv, wchar_t* tail) {
	wchar_t* filename = (wchar_t*)malloc(sizeof(wchar_t) * 15);
	wcscpy(filename, mssv);
	wcscat(filename, tail);
	return filename;
}

//Từ chuỗi buf = BeginSign + "..." + EndSign thay thế thành BeginSign + Str + Engsign
void ReplaceString(wchar_t* buf, wchar_t*BeginSign, wchar_t*EndSign, wchar_t*str) {
	wchar_t* temp1 = wcsstr(buf, BeginSign);
	wchar_t* temp2 = wcsstr(buf, EndSign);
	if (temp1 != NULL && temp2!NULL = )) {

}
		
	
}

//Hàm copy 2 file
void CreateHTML(wchar_t* FileSample, SV* data, int sl) {
	for (int i = 0; i < sl; i++) {
		FILE* sample = _wfopen(FileSample, L"r, ccs=UTF-8");
		if (!sample) {
			wprintf(L"Không thể đọc file Template\n");
		}
		wchar_t* FileOutput = CreateFileName(data[i].MSSV, tail);
		FILE* output = _wfopen(FileOutput, L"w, ccs=UTF-8");
		if (!output) {
			wprintf(L"Không thể mở file Template\n");
		}
		wchar_t* buf = (wchar_t*)malloc(1024);
		while (!feof(sample)) {
			fgetws(buf, 1024, sample);
			ReplaceString(buf, Title, EndTitle, data[i].HoVaTen);
			ReplaceString(buf, FalUp, EndFalUp, data[i].Faculty);
			ReplaceString(buf, Email, EndEmailTop, data[i].Email);
			ReplaceString(buf, Photo, EndPhoto, data[i].HinhAnh);
			ReplaceString(buf, Name, End, data[i].HoVaTen);
			ReplaceString(buf, Mssv, End, data[i].MSSV);
			ReplaceString(buf, Fal, End, data[i].Faculty);
			ReplaceString(buf, Birth, End, data[i].NgaySinh);
			ReplaceString(buf, Email, End, data[i].Email);
			fputws(buf, output);
		}
		fclose(sample);
		fclose(output);
	}
}
	








int wmain(int argc, wchar_t *argv[]) {

	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input

	FILE* input = _wfopen(L"Data.csv", L"r, ccs=UTF-8");
	if (!input) {
		wprintf(L"Không thể mở file CSV\n");
	}

	
	//Đếm số lượng SV
	int sl = CountSV(input);
	wprintf(L"Số lượng sinh viên: %ld\n\n\n", sl);
	SV* data = NULL;

	//Lấy dữ liệu từ file CSV
	data = GetInput(input, sl);


	//Xuất ra màn hình
	for (int i = 0; i < sl; i++) {
		PrintSV(data[i]);
	}
	fclose(input);

	wchar_t temp1[] = L"Sample.htm";
	CreateHTML(temp1, data, sl);

	//Mở file HTML mẫu, để đọc và copy qua file mới

	//for (int i = 0; i < sl; i++) {
	
	//	wchar_t* filename = CreateFileName(data[i].MSSV, tail);
	//	FILE* output = _wfopen(filename, L"r, ccs=UTF-8");
	//	if (!output) {
	//		wprintf(L"Không thể mở tạo file HTML\n");
	//	}
	//	CopyFile(sample, output);
	//	//Xử lí File HTML
	//	fclose(output);
	//}
	
	
	
	//Xoá vùng nhớ
	for (int i = 0; i < sl; i++) {
		MemoryDelete(data[i]);
	}
	if (data != NULL) {
		free(data);
		wprintf(L"OK\n");
	}
	_getch();
	return 0;
}