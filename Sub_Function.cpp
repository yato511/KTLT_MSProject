#include "Header.h"

//Số ký tự tối đa của các chuỗi, nếu có thay đổi chỉ cần thay đổi tại đây
int size_mssv = 11;
int size_hovaten = 31;
int size_faculty = 31;
int size_khoa = 5;
int size_ngaysinh = 11;
int size_email = 51;
int size_hinhanh = 31;
int size_mota = 1001;
int size_sothich = 1001;
#define maxSize 8000


		//CÁC HÀM PHỤ TRỢ KHÁC

//In thông tin SV ra màn hình
void PrintSV(SV *a, int sl) {
	wprintf(L"\nChọn thông tin của sinh viên muốn in ra màn hình\n");
	wprintf(L"\t 1. MSSV\n");
	wprintf(L"\t 2. Họ và tên\n");
	wprintf(L"\t 3. Khoa\n");
	wprintf(L"\t 4. Khóa tuyển\n");
	wprintf(L"\t 5. Ngày sinh\n");
	wprintf(L"\t 6. Email\n");
	wprintf(L"\t 7. Hình ảnh cá nhân\n");
	wprintf(L"\t 8. Mô tả\n");
	wprintf(L"\t 9. Sở thích\n");
	wprintf(L"\t 0. Tất cả\n");
	wprintf(L"\t-1. Bỏ qua\n");
	int c;
	wscanf(L"%ld", &c);
	while (c != -1) {
		for (int i = 0; i < sl; i++) {
			wprintf(L"\n\nThông tin của sinh viên thứ %ld:\n\n", i + 1);
			switch (c) {
			case 1:
			
				wprintf(L" - MSSV: %ls\n", a[i].MSSV);
				break;
			
			case 2:
			
				wprintf(L" - Họ và tên: %ls\n", a[i].HoVaTen);
				break;
			
			case 3:
			
				wprintf(L" - Khoa: %ls\n", a[i].Faculty);
				break;
			
			case 4:
			
				wprintf(L" - Khóa tuyển: %ld\n", a[i].Khoa);
				break;
			
			case 5:
			
				wprintf(L" - Ngày sinh: %ls\n", a[i].NgaySinh);
				break;
			
			case 6:
			
				wprintf(L" - Email: %ls\n", a[i].Email);
				break;
			
			case 7:
			
				wprintf(L" - Hình ảnh cá nhân: %ls\n", a[i].HinhAnh);
				break;
			
			case 8:
			
				wprintf(L" - Mô tả bản thân: %ls\n", a[i].Mota);
				break;
			
			case 9:
			
				if (a[i].HobbyCount == 0)
					wprintf(L" - Sở thích: Không có sở thích\n");
				for (int j = 0; j < a[i].HobbyCount; j++) {
					wprintf(L" - Sở thích %ld: %ls\n", j + 1, a[i].SoThich[j]);
				}
				break;
			
			default:
			
				wprintf(L" - MSSV\t\t\t:\t%ls\n", a[i].MSSV);
				wprintf(L" - Họ và tên\t\t:\t%ls\n", a[i].HoVaTen);
				wprintf(L" - Khoa\t\t\t:\t%ls\n", a[i].Faculty);
				wprintf(L" - Khóa tuyển\t\t:\t%ld\n", a[i].Khoa);
				wprintf(L" - Ngày sinh\t\t:\t%ls\n", a[i].NgaySinh);
				wprintf(L" - Email\t\t:\t%ls\n", a[i].Email);
				wprintf(L" - Hình ảnh cá nhân\t:\t%ls\n", a[i].HinhAnh);
				wprintf(L" - Mô tả bản thân\t:\t%ls\n", a[i].Mota);
				if (a[i].HobbyCount == 0)
					wprintf(L" - Sở thích\t\t:\tKhông có sở thích\n");
				for (int j = 0; j < a[i].HobbyCount; j++) {
					wprintf(L" - Sở thích %ld\t\t:\t%ls\n", j + 1, a[i].SoThich[j]);
				}
			}
			
		}

		wprintf(L"\n\nBạn có muốn in ra màn hình thêm thông tin nào nữa không?\n");
		wprintf(L"\t 1. MSSV\n");
		wprintf(L"\t 2. Họ và tên\n");
		wprintf(L"\t 3. Khoa\n");
		wprintf(L"\t 4. Khóa tuyển\n");
		wprintf(L"\t 5. Ngày sinh\n");
		wprintf(L"\t 6. Email\n");
		wprintf(L"\t 7. Hình ảnh cá nhân\n");
		wprintf(L"\t 8. Mô tả\n");
		wprintf(L"\t 9. Sở thích\n");
		wprintf(L"\t 0. Tất cả\n");
		wprintf(L"\t-1. Bỏ qua\n");
		wscanf(L"%ld", &c);
		if (c == -1) break;
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

	for (int i = 0; i < a.HobbyCount; i++)
		if (a.SoThich[i] != NULL)
			free(a.SoThich[i]);

	if (a.SoThich != NULL) free(a.SoThich);

}

//Khai báo vùng nhớ các con trỏ trong kiểu SV
void MemoryInit(SV& a) {
	a.MSSV = (wchar_t*)malloc(sizeof(wchar_t)*size_mssv);
	a.HoVaTen = (wchar_t*)malloc(sizeof(wchar_t)*size_hovaten);
	a.Faculty = (wchar_t*)malloc(sizeof(wchar_t)*size_faculty);
	a.NgaySinh = (wchar_t*)malloc(sizeof(wchar_t)*size_ngaysinh);
	a.Email = (wchar_t*)malloc(sizeof(wchar_t)*size_email);
	a.HinhAnh = (wchar_t*)malloc(sizeof(wchar_t)*size_hinhanh);
	a.Mota = (wchar_t*)malloc(sizeof(wchar_t)*size_mota);
	//Cấp phát 5 phần tử cho mảng 2 chiều Sở thích
	a.SoThich = (wchar_t**)malloc(sizeof(wchar_t*) * 5);

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


//Tìm vị trí của chuỗi con
int FindSubString(wchar_t* str, wchar_t* substr)
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
		temp1[pos_ins] = '\0';			
		wcscpy(temp2, buf + pos_ins);	
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

