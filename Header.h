#pragma once
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

void MemoryDelete(SV &a);	//Xóa vùng nhớ các con trỏ trong kiểu SV
void PrintSV(SV a);	//In thông tin SV ra màn hình