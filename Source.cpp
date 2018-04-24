#define _CRT_SECURE_NO_WARNINGS
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <wchar.h>
#include "Header.h"


//Số ký tự tối đa của các chuỗi, nếu có thay đổi chỉ cần thay đổi tại đây
int size_mssv = 11;
int size_hovaten = 31;
int size_faculty = 31;
int size_khoa = 5;
int size_ngaysinh = 11;
int size_email = 31;
int size_hinhanh = 31;
int size_mota = 1001;
int size_sothich = 501;
#define maxSize 8000

//In thông tin SV ra màn hình
void PrintSV(SV a) {
	wprintf(L" - MSSV\t\t\t:\t%ls\n", a.MSSV);
	wprintf(L" - Họ và tên\t\t:\t%ls\n", a.HoVaTen);
	wprintf(L" - Khoa\t\t\t:\t%ls\n", a.Faculty);
	wprintf(L" - Khóa tuyển\t\t:\t%ld\n", a.Khoa);
	wprintf(L" - Ngày sinh\t\t:\t%ls\n", a.NgaySinh);
	wprintf(L" - Email\t\t:\t%ls\n", a.Email);
	wprintf(L" - Hình ảnh cá nhân\t:\t%ls\n", a.HinhAnh);
	wprintf(L" - Mô tả bản thân\t:\t%ls\n", a.Mota);
	if (a.HobbyCount == 0)
		wprintf(L" - Sở thích\t\t:\tKhông có sở thích\n");
	for (int i = 0; i < a.HobbyCount; i++) {
		wprintf(L" - Sở thích %ld\t\t:\t%ls\n", i + 1, a.SoThich[i]);
	}
	
}

//Xóa vùng nhớ các con trỏ trong kiểu SV
void MemoryDelete(SV &a) {
	if (a.MSSV != NULL) free(a.MSSV);
	if (a.HoVaTen != NULL) free(a.HoVaTen);
	if (a.Faculty != NULL) free(a.Faculty);
	if (a.NgaySinh != NULL) free(a.NgaySinh);
	if (a.Email != NULL) free(a.Email);
	if (a.HinhAnh != NULL) free(a.HinhAnh);
	if (a.Mota != NULL) free(a.Mota);
	/*for (int i = 0; i < a.HobbyCount; i++) {
		if (a.SoThich[i] != NULL)
			free(a.SoThich[i]);
	}*/
	for (int i = 0; i < a.HobbyCount; i++)
		if (a.SoThich[i] != NULL)
			free(a.SoThich[i]);
	
	if (a.SoThich != NULL) free(a.SoThich);

	wprintf(L"---------> Clear Memory: Done\n");
}

//Khai báo vùng nhớ
void MemoryInit(SV& a) {
	a.MSSV = (wchar_t*)malloc(sizeof(wchar_t)*size_mssv);
	a.HoVaTen = (wchar_t*)malloc(sizeof(wchar_t)*size_hovaten);
	a.Faculty = (wchar_t*)malloc(sizeof(wchar_t)*size_faculty);
	a.NgaySinh = (wchar_t*)malloc(sizeof(wchar_t)*size_ngaysinh);
	a.Email = (wchar_t*)malloc(sizeof(wchar_t)*size_email);
	a.HinhAnh = (wchar_t*)malloc(sizeof(wchar_t)*size_hinhanh);
	a.Mota = (wchar_t*)malloc(sizeof(wchar_t)*size_mota);
	//Cấp phát 5 phần tử cho mảng 2 chiều Sở thích
	a.SoThich = (wchar_t**)malloc(sizeof(wchar_t*)*5);

}

//Đọc chuỗi
int GetWS(FILE*fp, wchar_t*s) {
	wchar_t c;
	c = fgetwc(fp);
	if (c == '\n' || c == EOF) {
		s = NULL;
		return 1;
	}

	if (c == '\"') {	//Trường hợp: "Nội dung",...
		c = fgetwc(fp);
		int i = 0;
		while (c != '\"' && c != EOF && c != '\n') {

			s[i] = c;
			c = fgetwc(fp);
			i++;
		}
		s[i] = '\0';
	}
	else {	//Trường hợp: Nội dung, ...
		int i = 0;
		while (c != ',' && c != EOF && c != '\n') {

			s[i] = c;
			c = fgetwc(fp);
			i++;
		}
		s[i] = '\0';

	}
	if (c != '\n')
		c = fgetwc(fp);
	if (c == '\n' || c == EOF) {
		return 1;
	}
	else if (c == ',') {
		return 0;
	}

	fseek(fp, -1L, SEEK_CUR);	//Nếu ký tự đọc được không phải là dấu hiệu kết thúc hay dấu ngăn cách
								//Lùi con trỏ về vị trí cũ để trả lại chữ cái đã đọc được
	return 0;
	//Return 1: Kết thúc dòng hoặc kết thúc File;
	//Return 0: Chưa kết thúc dòng
}

//
//int GetSV(FILE*fp, SV &a) {
//	MemoryInit(a);
//	int i = 0;
//	i = GetWS(fp, a.MSSV);
//	i = GetWS(fp, a.HoVaTen);
//	i = GetWS(fp, a.Faculty);
//	wchar_t* temp = (wchar_t*)malloc(sizeof(wchar_t)*size_khoa);
//	i = GetWS(fp, temp);
//	a.Khoa = wcstol(temp, 0, 10);	//Chuyển từ chuỗi sang số nguyên
//	free(temp);
//	i = GetWS(fp, a.NgaySinh);
//	i = GetWS(fp, a.Email);
//	i = GetWS(fp, a.HinhAnh);
//	i = GetWS(fp, a.Mota);
//	i = GetWS(fp, a.SoThich);
//	//i = GetWS(fp, data.MSSV);
//	return i;
//}
//void GetInput(FILE*fp, SV* &data,int n) {
//	data = (SV*)malloc(sizeof(SV) * n);
//	fseek(fp, 3L, SEEK_SET);
//	for (int i = 0; i < n; i++) {
//		GetSV(fp, data[i]);
//	}
//}
int CountSV(FILE* fp) {
	int count = 0;
	wchar_t* buf = (wchar_t*)malloc(sizeof(wchar_t) * 2000);
	while (fgetws(buf, 2000, fp)) {
		//Điều kiện để tránh dữ liệu rác
		if (buf[0] != '\n' && buf[0] != '\t' && buf[0] != ' ' && wcslen(buf) >= 20) {
			count++;
		}
	}
	free(buf);
	return count;
}

//Lấy thông tin cho 1 SV
void GetSV(FILE*fp, SV &a) {
	MemoryInit(a);
	int i = 0;
	i = GetWS(fp, a.MSSV);
	i = GetWS(fp, a.HoVaTen);
	i = GetWS(fp, a.Faculty);
	wchar_t* temp = (wchar_t*)malloc(sizeof(wchar_t)*size_khoa);
	i = GetWS(fp, temp);
	a.Khoa = wcstol(temp, 0, 10);	//Chuyển từ chuỗi sang số nguyên
	free(temp);
	i = GetWS(fp, a.NgaySinh);
	i = GetWS(fp, a.Email);
	i = GetWS(fp, a.HinhAnh);
	i = GetWS(fp, a.Mota);
	
	/*if (i == 1) {
		a.HobbyCount = 1;
		a.SoThich = (wchar_t**)realloc(a.SoThich, 1);
		a.SoThich[0] = (wchar_t*)malloc(sizeof(wchar_t) * 50);
		wchar_t temp[] = L"Không có sở thích";
		wcscpy(a.SoThich[0], temp);
	}*/
	a.HobbyCount = 0;
	while (i != 1) {
		a.SoThich[a.HobbyCount] = (wchar_t*)malloc(sizeof(wchar_t)*size_sothich);
		i = GetWS(fp, a.SoThich[a.HobbyCount]);
		a.HobbyCount++;
	}
}
//Lấy thông tin cho mảng SV
void GetInput(FILE*fp, SV* &data, int n) {
	data = (SV*)malloc(sizeof(SV) * n);
	fseek(fp, 3L, SEEK_SET);
	for (int i = 0; i < n; i++) {
		GetSV(fp, data[i]);
	}
}

//Tạo tên File HTML: MSSV.htm
wchar_t* CreateFileName(wchar_t* mssv, wchar_t* tail) {
	wchar_t* filename = (wchar_t*)malloc(sizeof(wchar_t) * 15);
	wcscpy(filename, mssv);
	wcscat(filename, tail);
	return filename;
}
//Đổi chuỗi thường thành chuỗi in hoa
void Upper(wchar_t *str)
{
	wchar_t chuthuong[] = L"áàảãạăắằẳẵặâấầẩẫậđéèẻẽẹêếềểễệíìỉĩịóòỏõọôốồổỗộơớờởỡợúùủũụưứừửữựýỳỷỹỵ";
	wchar_t chuhoa[] = L"ÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬĐÉÈẺẼẸÊẾỀỂỄỆÍÌỈĨỊÓÒỎÕỌÔỐỒỔỖỘƠỚỜỞỠỢÚÙỦŨỤƯỨỪỬỮỰÝỲỶỸỴ";
	bool IsWchar = false;
	for (int i = 0; str[i] != '\0'; i++) {
		for (int j = 0; chuthuong[j] != '\0'; j++) {
			if (str[i] == chuthuong[j])
			{
				str[i] = chuhoa[j];
				IsWchar = true;
				break;
			}
		}
		if (!IsWchar)
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] -= 32;
		IsWchar = false;
	}
}
//Các chuỗi để tìm kiếm và thay thế trong Sample.htm
	//Header
wchar_t Title[] = L"<title>HCMUS - ";
wchar_t NameMssv[] = L"<span class=\"Personal_FullName\">";
wchar_t FacUp[] = L"class=\"Personal_Department\">KHOA ";
wchar_t EmailTop[] = L"Email: ";
wchar_t EndEmailTop[] = L"\n";
wchar_t Photo[] = L"<img src=\"";
wchar_t EndPhoto[] = L"\" class=\"Personal_Hinhcanhan";
	//Body
wchar_t Name[] = L"Họ và tên: ";
wchar_t Mssv[] = L"MSSV: ";
wchar_t	Fac[] = L"Sinh viên khoa ";
wchar_t EmailBot[] = L"Email: ";
wchar_t Birth[] = L"Ngày sinh: ";
wchar_t Desc[] = L"class=\"Description\">";
wchar_t Hobby[] = L" <div class=\"InfoGroup\">Sở thích</div>";
wchar_t HobbyEnd[] = L"</ul>";
wchar_t HobbyElement[] = L"<li>";
wchar_t End[] = L"</";	//Đa số các lệnh đều kết thúc bằng chuỗi ký tự này

	//Footer
wchar_t Year[] = L"@";
wchar_t EndFooter[] = L"</br>";
wchar_t InfoFooter[] = L"MSSV - Tên sinh viên thực hiện";

//Một số chuỗi cố định
wchar_t FileTail[] = L".htm";//Đuôi tên file
wchar_t Pjyear[] = L"2018";//Năm
wchar_t PjOwner_Index[] = L"1712827 - Trần Quốc Toản"; //MSSV và tên người làm đồ án

//Tìm vị trí của chuỗi con trong chuỗi cha
int FindSubString(wchar_t* str, wchar_t* substr)		//lấy vị trí của chuỗi con trong chuỗi cha để chèn chuỗi con ra sau
{
	int len = wcslen(str);
	int slen = wcslen(substr);
	for (int i = 0; i < len - slen + 1; i++)
	{
		wchar_t* temp = (wchar_t*)malloc(sizeof(wchar_t)*(slen));
		wcsncpy(temp, str + i, slen);
		temp[slen] = '\0';
		if (wcscmp(temp, substr) == 0)
			return i;
	}
	return -1;
}



//Từ chuỗi buf = "..." + BeginSign + "something" + EndSign + "..." thay thế thành "..." + BeginSign + String + EngSign + "..."
void ReplaceString(wchar_t* buf, wchar_t*BeginSign, wchar_t*EndSign, wchar_t*str) {
	int pos1 = FindSubString(buf, BeginSign);
	int pos2 = FindSubString(buf, EndSign);
	if (pos1 != -1 && pos2 != -1) {	//Trong chuỗi buf phải xuất hiện cả BeginSign và EndSign
		int lenbuf = wcslen(buf);
		int pos_ins = pos1 + wcslen(BeginSign);	//Vị trí bắt đầu chèn
		
		//Khai báo các biến tạm
		wchar_t* temp1 = (wchar_t*)malloc(512 * sizeof(wchar_t));
		wchar_t* temp2 = (wchar_t*)malloc(512 * sizeof(wchar_t));
		wchar_t* temp3 = (wchar_t*)malloc(512 * sizeof(wchar_t));

		wcsncpy(temp1, buf, pos_ins);
		temp1[pos_ins] = '\0';			//temp1 = "something" + EndSign + "..."
		wcscpy(temp2, buf + pos_ins);	//temp2 = "
		wcscpy(temp3, buf + pos2);
		wcscpy(temp2, str);
		temp2[wcslen(str)] = '\0';
		wcscat(temp2, temp3);
		wcscat(temp1, temp2);
		wcscpy(buf, temp1);
		free(temp1);
		free(temp2);
		free(temp3);
	}
}




//Hàm ghi file HTML
void CreateHTML(wchar_t* FileSample, SV* data, int sl) {
	wchar_t* buf = (wchar_t*)malloc(1024); //Biến để đọc từng dòng
	for (int i = 0; i < sl; i++) {

		//Mở File
		FILE* sample = _wfopen(FileSample, L"r, ccs=UTF-8");
		if (!sample) {
			wprintf(L"Không thể đọc file HTML mẫu %ls\n", FileSample);
		}
		wchar_t* FileOutput = CreateFileName(data[i].MSSV, FileTail);
		FILE* output = _wfopen(FileOutput, L"w, ccs=UTF-8");
		if (!output) {
			wprintf(L"Không thể mở file %ls\n", FileOutput);
		}

		//Tạo một số chuỗi tạm
			//Tên khoa viết hoa
		wchar_t* FacUp_temp = (wchar_t*)malloc(sizeof(wchar_t)*size_faculty);
		wcscpy(FacUp_temp, data[i].Faculty);
		Upper(FacUp_temp);
			//Họ và tên viết hoa - MSSV
		wchar_t* Ten_MSSV = (wchar_t*)malloc(sizeof(wchar_t)*(size_hovaten + size_mssv));
		wcscpy(Ten_MSSV, data[i].HoVaTen);
		Upper(Ten_MSSV);
		wcscat(Ten_MSSV, L" - ");
		wcscat(Ten_MSSV, data[i].MSSV);

		//Bắt đầu đọc và thay thế
		while (!feof(sample)) {
			fgetws(buf, 1024, sample);
			//Header
			ReplaceString(buf, Title, End, data[i].HoVaTen);
			ReplaceString(buf, FacUp, End, FacUp_temp);
			ReplaceString(buf, EmailTop, EndEmailTop, data[i].Email);
			ReplaceString(buf, NameMssv, End, Ten_MSSV);
			ReplaceString(buf, Photo, EndPhoto, data[i].HinhAnh);
			//Body
			ReplaceString(buf, Name, End, data[i].HoVaTen);
			ReplaceString(buf, Mssv, End, data[i].MSSV);
			ReplaceString(buf, Fac, End, data[i].Faculty);
			ReplaceString(buf, Birth, End, data[i].NgaySinh);
			ReplaceString(buf, EmailBot, End, data[i].Email);
			//Footer
			ReplaceString(buf, Year, EndFooter, Pjyear);

			//Description xử lí riêng
			//Vì BeginSign và EndSign của Description không nằm trên cùng dòng
			if (wcsstr(buf, Desc) != NULL) {
				fputws(buf, output);		//In dòng cũ
				fgetws(buf, 1024, sample);	//Đọc dòng dưới
				wchar_t keyend[] = L"\n";	//Ký tự xuống dòng là EndSign
				int j = 0;
				wchar_t* keybegin = (wchar_t*)malloc(512);
				//Vì dòng Description có dạng \t\t\t\t\t\t\t + Mô tả + \n
				for (j = 0; buf[j] == '\t' || buf[j] == ' '; j++)
				{
					keybegin[j] = buf[j];
				}
				keybegin[j] = '\0';
				ReplaceString(buf, keybegin, keyend, data[i].Mota);
				free(keybegin);
			}


			//Sở thích xử lí riêng
			if (wcsstr(buf, Hobby) != NULL) {
				for (int x = 1; x <= 3; x++) {
					fputws(buf, output);	//In dòng cũ
					fgetws(buf, 1024, sample);	//Đọc dòng bên dưới
				}

				//buf lúc này = <li>Ẩm thực....</li>
				if (data[i].HobbyCount == 0) {		//Nếu biến data[i] không có sở thích -> để trống
					fgetws(buf, 1024, sample);
					fgetws(buf, 1024, sample);		//Đọc 2 lần nữa để bỏ qua 2 dòng sở thích trong file mẫu
				}
				else {				//Nếu có sở thích, thay thế chuỗi nằm giữa <li> và </li>
					//Tạo biến buf có dạng <li> Sở thích [k] </li>
					for (int k = 0; k < data[i].HobbyCount; k++) {
						ReplaceString(buf, HobbyElement, End, data[i].SoThich[k]);
						fputws(buf, output);
					}

					fgetws(buf, 1024, sample);
					fgetws(buf, 1024, sample);	//Đọc 2 lần nữa để bỏ qua 2 dòng sở thích trong file mẫu
				}
			}

			//Phần thông tin trong Footer xử lí riêng
			if (wcsstr(buf, InfoFooter) != NULL) {
				//Tạo BeginSign đặc biệt
				int i = 0;
				wchar_t* keybegin = (wchar_t*)malloc(512);
				for (i = 0; buf[i] != '\t' && buf[i] != ' '; i++)
				{
					keybegin[i] = buf[i];
				}
				keybegin[i] = '\0';

				ReplaceString(buf, keybegin, EndFooter, PjOwner_Index);
				free(keybegin);
			}

			//Sau các hàm thay thế, ghi chuỗi buf vào File
			fputws(buf, output);
		}
		//Xóa vùng nhớ biến tạm, đóng file
		fclose(sample);
		fclose(output);
		free(FileOutput);
		free(FacUp_temp);
		free(Ten_MSSV);
	}
	free(buf);
}

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
	if (Data != NULL) free(Data);
	_getch();
	return 0;
}