#include "Header.h"

//Các chuỗi để tìm kiếm và thay thế trong Sample.htm
	//Header
wchar_t Title[] = L"<title>HCMUS - ";
wchar_t NameMssv[] = L"\"Personal_FullName\">";
wchar_t FacUp[] = L"\"Personal_Department\">KHOA ";
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
wchar_t Desc[] = L"Description";
wchar_t Hobby[] = L"Sở thích";
wchar_t HobbyEnd[] = L"</ul>";
wchar_t HobbyElement[] = L"<li>";
wchar_t End[] = L"</";	//Đa số các lệnh đều kết thúc bằng chuỗi ký tự này

	//Footer
wchar_t Year[] = L"@";
wchar_t EndFooter[] = L"</br>";
wchar_t InfoFooter[] = L"MSSV - Tên sinh viên thực hiện";


//Một số chuỗi cố định
wchar_t Folder[] = L"Website/";
wchar_t FileTail[] = L".htm";	//Đuôi tên file
wchar_t PjYear[] = L"2018";		//Năm
wchar_t PjOwner_Index[] = L"1712827 - Trần Quốc Toản"; //MSSV và tên người làm đồ án
		
													   
													   
													   
													   
						   //CÁC HÀM DÙNG CHO FILE HTML


//Tạo tên File HTML: MSSV.htm
wchar_t* CreateFileName(wchar_t* mssv,wchar_t* folder, wchar_t* tail) {
	wchar_t* filename = (wchar_t*)malloc(sizeof(wchar_t) * 50);
	wcscpy(filename, folder);
	wcscat(filename, mssv);
	wcscat(filename, tail);
	return filename;
}


//Hàm ghi file HTML
void CreateHTML(wchar_t* FileSample, SV* data, int sl) {
	wchar_t* buf = (wchar_t*)malloc(1024); //Biến để đọc từng dòng
	for (int i = 0; i < sl; i++) {
		

		//Mở File HTML mẫu
		FILE* sample = _wfopen(FileSample, L"r, ccs=UTF-8");
		if (!sample) {
			wprintf(L"Không thể đọc file HTML mẫu %ls\n", FileSample);
		}

		//Tạo file HTML xuất ra
		wchar_t* FileOutput = CreateFileName(data[i].MSSV, Folder, FileTail);
		
		FILE* output = _wfopen(FileOutput, L"w, ccs=UTF-8");
		if (!output) {
			wprintf(L"Không thể mở file %ls\n", FileOutput);
		}

		//Tạo một số chuỗi tạm
			//Tên khoa viết hoa
		wchar_t* FacUp_temp = (wchar_t*)malloc(sizeof(wchar_t)*30);
		wcscpy(FacUp_temp, data[i].Faculty);
		Upper(FacUp_temp);
			//Họ và tên viết hoa - MSSV
		wchar_t* Ten_MSSV = (wchar_t*)malloc(sizeof(wchar_t)*50);
		wcscpy(Ten_MSSV, data[i].HoVaTen);
		Upper(Ten_MSSV);
		wcscat(Ten_MSSV, L" - ");
		wcscat(Ten_MSSV, data[i].MSSV);


		//Menu phát sinh Profile Page
		//Cho phép người dùng kiểm soát những thông tin nào được phát sinh ra Profile Page
		wprintf(L"\nChọn những thông tin của sinh viên thứ %ld muốn phát sinh ra Profile Page\n", i + 1);
		wprintf(L"\t  1. MSSV\n");
		wprintf(L"\t  2. Họ và tên\n");
		wprintf(L"\t  3. Khoa\n");
		wprintf(L"\t  4. Khóa tuyển\n");
		wprintf(L"\t  5. Ngày sinh\n");
		wprintf(L"\t  6. Email\n");
		wprintf(L"\t  7. Hình ảnh cá nhân\n");
		wprintf(L"\t  8. Mô tả\n");
		wprintf(L"\t  9. Sở thích\n");
		wprintf(L"\t 10. Tất cả\n");
		wprintf(L"\n\t --Nhấn 0 để thoát menu và bắt đầu tạo Profile Page cho sinh viên thứ %ld--\n", i + 1);
		int a[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int b;
		do {
			wscanf(L"%ld", &b);
			if (b == 0) break;
			if (1 <= b && b <= 9)
			{
				a[b] = 1;
			}
			else if (b == 10)
			{
				for (int i = 0; i < 10; i++)
					a[i] = 1;
				break;
			}
		} while (true);

		wchar_t blank[] = L"\0";	//Chuỗi rỗng


		//Bắt đầu đọc và thay thế
		while (!feof(sample)) {
			fgetws(buf, 1024, sample);

			//Nếu được người dùng cho phép thì mới phát sinh thông tin đó ra HTML, nếu không thì thay thế bằng chuỗi rỗng

			//Header
			if (a[2] == 1)
				ReplaceString(buf, Title, End, data[i].HoVaTen);	
			else
				ReplaceString(buf, Title, End, blank);

			if (a[3] == 1)
				ReplaceString(buf, FacUp, End, FacUp_temp);
			else
				ReplaceString(buf, FacUp, End, blank);

			if (a[6] == 1)
				ReplaceString(buf, EmailTop, EndEmailTop, data[i].Email);
			else
				ReplaceString(buf, EmailTop, EndEmailTop, blank);

			if (a[1] == 1 && a[2] == 1)
				ReplaceString(buf, NameMssv, End, Ten_MSSV);
			else
				ReplaceString(buf, NameMssv, End, blank);

			if (a[7] == 1)
				ReplaceString(buf, Photo, EndPhoto, data[i].HinhAnh);
			else
				ReplaceString(buf, Photo, EndPhoto, blank);

			//Body
			if (a[2] == 1)
				ReplaceString(buf, Name, End, data[i].HoVaTen);
			else
				ReplaceString(buf, Name, End, blank);
			
			if (a[1] == 1)
				ReplaceString(buf, Mssv, End, data[i].MSSV);
			else 
				ReplaceString(buf, Mssv, End, data[i].MSSV);

			if (a[3] == 1)
				ReplaceString(buf, Fac, End, data[i].Faculty);
			else
				ReplaceString(buf, Fac, End, blank);

			if (a[5] == 1)
				ReplaceString(buf, Birth, End, data[i].NgaySinh);
			else
				ReplaceString(buf, Birth, End, blank);

			if (a[6] == 1)
				ReplaceString(buf, EmailBot, End, data[i].Email);
			else
				ReplaceString(buf, Birth, End, blank);

			//Footer
			ReplaceString(buf, Year, EndFooter, PjYear);


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
				if (a[8] == 1)
					ReplaceString(buf, keybegin, keyend, data[i].Mota);
				else
					ReplaceString(buf, keybegin, keyend, blank);
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
					if (a[9]==1)
						for (int k = 0; k < data[i].HobbyCount; k++) {
							ReplaceString(buf, HobbyElement, End, data[i].SoThich[k]);
							fputws(buf, output);
						}
					else 
						for (int k = 0; k < data[i].HobbyCount; k++) {
							ReplaceString(buf, HobbyElement, End, blank);
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
		wprintf(L"\n\n---->Đã tạo xong Profile Page cho sinh viên thứ %ld\n\n", i + 1);
	}
	free(buf);
}
