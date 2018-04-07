#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

struct SinhVien {
	char *MSSV;
	char *HoVaTen;
	char *Faculty;
	int	Khoa;
	char *NgaySinh;
	char *Email;
	char *HinhAnh;
	char *Mota;
	char *SoThich;
};
typedef struct SinhVien SV;

SV* GetInput(char* Path, int soluong) {
	SV *a = (SV*)malloc(soluong*sizeof(SV));
	//Mo tap tin
	FILE* fp = fopen(Path, "r");
	if (fp != NULL) {
		for (int i = 0; i < soluong; i++) {
			//Memory Init
			a[i].MSSV = (char*)malloc(10 * sizeof(char));
			a[i].HoVaTen = (char*)malloc(30 * sizeof(char));
			a[i].Faculty = (char*)malloc(30 * sizeof(char));
			a[i].NgaySinh = (char*)malloc(10 * sizeof(char));
			a[i].Email = (char*)malloc(30 * sizeof(char));
			a[i].HinhAnh = (char*)malloc(30 * sizeof(char));
			a[i].Mota = (char*)malloc(1000 * sizeof(char));
			a[i].SoThich = (char*)malloc(1000 * sizeof(char));

			//Get data
			fscanf(fp, "%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n", a[i].MSSV, a[i].HoVaTen, a[i].Faculty, &a[i].Khoa, a[i].NgaySinh, a[i].Email, a[i].HinhAnh, a[i].Mota, a[i].SoThich);
		}
		fclose(fp);
	}
	return a;
}
void Output(SV *a, int soluong) {
	for (int i = 0; i < soluong; i++) {
		printf("\nSinh vien thu %d\n", i + 1);
		printf("MSSV:\t%s\n", a[i].MSSV);
		printf("Ho va ten:\t%s\n", a[i].HoVaTen);
		printf("Khoa:\t%s\n", a[i].Faculty);
		printf("Khoa:\t%d\n", a[i].Khoa);		
		printf("Ngay sinh:\t%s\n", a[i].NgaySinh);
		printf("Email:\t%s\n", a[i].Email);
		printf("Mo ta:\t%s\n", a[i].Mota);
		printf("Hinh anh:\t%s\n", a[i].HinhAnh);
		printf("So thich:\t%s\n", a[i].SoThich);
	}
}

void main() {
	int n;
	printf("Nhap so luong: ");
	scanf("%d", &n);
	SV* a = GetInput("Data.csv", n);
	Output(a, n);
	free(a);
}