#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

struct SinhVien {
	char MSSV[10];
	char HoVaTen[30];
	char Faculty[30];
	int	Khoa;
	char NgaySinh[11];
	char Email[30];
	char HinhAnh[20];
	char Mota[100];
	char SoThich[100];
};
typedef struct SinhVien SV;

SV GetInput(char* Path) {
	SV a;
	FILE* fp = fopen(Path, "r");
	if (fp != NULL) {
		fscanf(fp, "%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^\n]", a.MSSV, a.HoVaTen, a.Faculty, &a.Khoa, a.NgaySinh, a.Email, a.HinhAnh, a.Mota, a.SoThich);
		fclose(fp);
	}
	return a;
}
void Output(SV a) {
		printf("%s\n", a.MSSV);
		printf("%s\n", a.HoVaTen);
		printf("%s\n", a.Faculty);
		printf("%d\n", a.Khoa);
		printf("%s\n", a.Email);
		printf("%s\n", a.NgaySinh);
		printf("%s\n", a.Mota);
		printf("%s\n", a.HinhAnh);
		printf("%s\n", a.SoThich);
}
void main() {
	SV a = GetInput("Data.csv");
	Output(a);

}