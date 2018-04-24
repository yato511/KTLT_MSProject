#include "Header.h"

			//CÁC HÀM DÙNG TRONG FILE CSV


//Đọc chuỗi Unicode
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

//Đếm số lượng sinh viên trong file
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
	wchar_t* temp = (wchar_t*)malloc(sizeof(wchar_t)*5);
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
		a.SoThich[a.HobbyCount] = (wchar_t*)malloc(sizeof(wchar_t)*500);
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
