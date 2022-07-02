#pragma once
# include<iostream>
# include<windows.h>
# include<string>
# include"console.h"

# define Enter 13
# define Esc 27
# define Len 72
# define Xuong 80
# define Trai 75
# define Phai 77
//# define PhimCach 32
# define F1 59
//# define F2 60
# define F4 62

using namespace std;


void box(int TD_x, int TD_y, int TD_w, int TD_h, int t_color, int b_color, string nd)
{
	textcolor(b_color);  // chỉnh mảu nền của chữ
	for (int iy = TD_y + 1; iy <= TD_y + TD_h - 1; iy++)
	{
		for (int ix = TD_x + 1; ix <= TD_x + TD_w - 1; ix++)
		{
			gotoxy(ix, iy);
			cout << " ";  // chảy đến đâu thì có khoảng trắng đè lên ( màu b_color)
		}
	}

	SetColor(b_color);  // màu chữ màu đen
	int i;
	if (TD_h % 2 != 0) // chan
		i = TD_h / 2;
	else
		i = (TD_h + 1) / 2;
	gotoxy(TD_x + i, TD_y + i);
	cout << nd;
	///// vẽ viền đè lên /////////////

	textcolor(b_color);  // chỉnh lai màu nền màu đen cho khác màu b_color
	SetColor(t_color);
	if (TD_h <= 1 || TD_w <= 1)
		return;
	for (int ix = TD_x; ix <= TD_x + TD_w; ix++)  // duyệt hàng ngang
	{
		gotoxy(ix, TD_y);
		cout << char(196);
		gotoxy(ix, TD_y + TD_h);
		cout << char(196);
	}
	for (int iy = TD_y; iy <= TD_y + TD_h; iy++)   // duyệt hàng dọc
	{
		gotoxy(TD_x, iy);
		cout << char(179);
		gotoxy(TD_x + TD_w, iy);
		cout << char(179);
	}
	gotoxy(TD_x, TD_y); cout << char(218);   // bắt 4 góc của 1 khung menu
	gotoxy(TD_x + TD_w, TD_y); cout << char(191);
	gotoxy(TD_x, TD_h + TD_y); cout << char(192);
	gotoxy(TD_x + TD_w, TD_h + TD_y); cout << char(217);
	textcolor(7);  // chuyênr về màu ban đầu
}
void thanh_xoa_name(int TD_x, int TD_y, int TD_w)   // thuc chat là đè lên  // w là chiều dài name
{
	for (int ix = TD_x; ix <= TD_x + TD_w; ix++)
	{
		gotoxy(ix, TD_y);
		cout << " ";  // chảy đến đâu thì có khoảng trắng đè lên ( màu b_color)
	}
}

// chảy 5 lần rồi thoát
void Hinh_3D(int x_3D, int y_3D)
{
	// td là tiêu đê
	/*int x_3D = 50;
	int y_3D = 4;*/
	int R_DumMau;
	int min_mau = 7;
	int max_mau = 14;
	srand(time(NULL));
	for (int i = 1; i <= 5; i++)  // vòng for randum màu
	{
		R_DumMau = rand() % (max_mau - min_mau + 1) + min_mau - 3;  // -3 là vì bên dưới cọng 3
		textcolor(R_DumMau);
		gotoxy(x_3D, y_3D + 1); cout << "                                (= = =                                          _";
		gotoxy(x_3D, y_3D + 2); cout << "                                \\\\   //                                        //";
		gotoxy(x_3D, y_3D + 3); cout << "                                    //                                        //";
		gotoxy(x_3D, y_3D + 4); cout << "      _ _ _                       __           __     __           _        _ _      _";
		gotoxy(x_3D, y_3D + 5); cout << "    /*_*_*_*\\   | |      | |      /\ _\\         /\ _\\   / /_\\        | \\_      \\\\*\\    /*/";
		gotoxy(x_3D, y_3D + 6); cout << "   |*/       \\  |*/       \\\\    / /**\\       / /**\\ / //*/        | |*|      \\\\*\\  /*/";
		gotoxy(x_3D, y_3D + 7);  cout << "   |*|        | |*|        |  /  /*/\\*\\     / /*/\\*\\ //*/         | |*|       |\\*\\/*/";
		gotoxy(x_3D, y_3D + 8); cout << "   \\|         |  \\\|         | / /*/==\\*\\   / /*/==\\*\\/*/          | |*|_ _    | |**|";
		gotoxy(x_3D, y_3D + 9); cout << "     \\ _ _ _ /    \\\\ _ _ _ / /_/*/    \\*\\ /_/*/    \\*\\/            \\|*_*_*|    \\|**|";
		gotoxy(x_3D, y_3D + 10); cout << "        \\*_*\\       ";
		textcolor(R_DumMau + 3);
		gotoxy(x_3D - 7, y_3D + 12); cout << "                                                          _            ";
		gotoxy(x_3D - 7, y_3D + 13); cout << "                                                         //               ";
		gotoxy(x_3D - 7, y_3D + 14); cout << "                                                   //\\\\ //              ";
		gotoxy(x_3D - 7, y_3D + 15); cout << "                                                  //  \\\\                 ";
		gotoxy(x_3D - 7, y_3D + 16); cout << "       _ _     _   _      _   _    _ _      _     _ _ _        __      __           _ _ _        __   _ _      _";
		gotoxy(x_3D - 7, y_3D + 17); cout << "     /* _*\\\\  | \\_\\ \\_\\  |\\_\\ \\_\\  \\\\*\\    /*/  |\\ _ _ _\\     /\ _\\   / /_\\        |  _ __\\      /\ _\\  \\\\*\\    /*/";
		gotoxy(x_3D - 7, y_3D + 18); cout << "    |*/  \\_\\  | |*|_|*|  ||*|  |*|  \\\\*\\  /*/   | |*_*_*|    / /**\\ / //*/        | |  @  \\    / /**\\  \\\\*\\  /*/";
		gotoxy(x_3D - 7, y_3D + 19); cout << "    |*|    _  | |* _ *|  ||*|  |*|   |\\*\\/*/    | |*|_ _    / /*/\\*\\ //*/         | |* * */   / /*/\\*\\  |\\*\\/*/";
		gotoxy(x_3D - 7, y_3D + 20); cout << "    \\*\\_ / /  | |*| |*|  \\|*\\_/*|    | |**|     | |*_-_--  / /*/==\\*\\/*/          | |  @  \\  / /*/==\\*\\ | |**|";
		gotoxy(x_3D - 7, y_3D + 21); cout << "     \\*_*_/    \\|*| |*|    \\*_*/      \\|**|      \\|*_*_*| /_/*/    \\*\\/            \\\\_*_*_/ /_/*/    \\*\\ \\|**|";

	}
	textcolor(7);
}
//// dừng khi ix > x_load+w_load
void loading(int& x_load, int& y_load, int& w_load, int& giaTri_load)
{
	int time;
	int ix = x_load;
	textcolor(19);  // cho thanh loading = 19(xanh duong)
	gotoxy(ix, y_load);
	cout << "    ";  // chảy đến đâu thì có khoảng trắng đè lên ( màu b_color)
	gotoxy(ix, y_load + 1);
	cout << "    ";  // chảy đến đâu thì có khoảng trắng đè lên ( màu b_color)

	ix = ix + 3; // ************** chưa bt làm j  // quên rồi
	gotoxy(138, y_load + 1);  // in giá trị phần trăm
	if (ix <= 130 - 20 && giaTri_load <= 90)  // cho giá trị dừng đến 90
		giaTri_load = giaTri_load + 5;
	if (ix >= 130)
		giaTri_load = 100;

	textcolor(7);  // cho 7(trắng)
	cout << giaTri_load << " % ";
	textcolor(7);

}
void in_mssv(int x, int y, string mssv)
{
	for (int i = 0; i <= 3; i++)
	{
		Sleep(40);
		gotoxy(x, y);
		thanh_xoa_name(x, y, 11);
		gotoxy(x, y);
		cout << mssv;
	}
}
// ok  // trong ten_nhom la có 3D rồi
void ten_nhom()
{

	// tỏa độ đầu khi dịch chuyển
	int x_Duy = 0; int y_Duy = 30;
	int x_Hoa = 180; int y_Hoa = 33;
	int x_Tien = 125; int y_Tien = 36;
	int xcu; int ycu;
	for (int ix = x_Duy; ix <= 120; ix = ix + 10)  // tên Duy  ( 125,30) tọa độ cuối
	{

		if (ix == 120)
		{

			gotoxy(ix, y_Duy);
			xcu = ix;
			ycu = y_Duy;
			thanh_xoa_name(xcu, ycu, 10);
			gotoxy(122, 30);  //tọa độ cuối
			textcolor(9); // cho màu chữ = 9(xanh dương)
			cout << "NGUYEN QUOC DUY";
			break;
		}
		Hinh_3D(82, 3);
		Sleep(100);
		gotoxy(ix, y_Duy);
		xcu = ix;
		ycu = y_Duy;
		thanh_xoa_name(xcu, ycu, 10);
		textcolor(9);  // cho màu chữ = 9(xanh dương)
		cout << "NGUYEN QUOC DUY";
	}

	in_mssv(144, 30, ": N20DCCN013");

	for (int ix = x_Hoa; ix >= 120; ix = ix - 5)  // tên hoa ( 125,33) tọa độ cuối
	{
		if (ix == 120)
		{
			gotoxy(ix, y_Duy);
			xcu = ix;
			ycu = y_Hoa;
			thanh_xoa_name(xcu, ycu, 100);
			gotoxy(122, 33);
			textcolor(6); // cho màu chữ 6(vàng)
			cout << "HOANG LE THUY HOA";
			break;
		}
		Hinh_3D(82, 3);
		Sleep(100);

		xcu = ix;
		ycu = y_Hoa;
		thanh_xoa_name(xcu, ycu, 100);
		gotoxy(ix, y_Hoa);
		textcolor(6); // cho màu chữ 6(vàng)
		cout << "HOANG LE THUY HOA";
	}
	in_mssv(144, 33, ": N20DCCN016");

	// tên Tien ( 125,36) tọa độ cuối
	for (int i = 1; i <= 4; i++)  // nháy 4 lần
	{
		Hinh_3D(82, 3);
		Sleep(120);
		gotoxy(x_Tien, y_Tien);
		textcolor(13); // cho màu chữ 13(tím)
		cout << "LE VAN TIEN";
		Sleep(120);
		thanh_xoa_name(x_Tien, y_Tien, 11);
		if (i == 4)
		{
			gotoxy(x_Tien, y_Tien);
			cout << "LE VAN TIEN";
		}
	}
	in_mssv(144, 36, ": N20DCCN064");


}
//ok
void Frontend_chay()
{
	int x_load = 40;
	int y_load = 35;
	int w_load = 90;
	int giatri_load = 10;
	for (int i = 5; ; i++)  // chạy thanh loading với  hình 3D
	{
		if (i == 5)
		{
			textcolor(7);  // cho chữ LOADING = trắng
			gotoxy(x_load - 11, y_load + 1);
			cout << "LOADING...";
		}
		if (i % 5 == 0 && i <= 40 + 90 - 10)  // tọa độ cuối
		{
			loading(x_load, y_load, w_load, giatri_load);
			x_load = x_load + 4;  // 4 khoảng trắng nên phải tô 4 khoảng trắng
			Sleep(100);
		}
		Hinh_3D(50, 4);
		if (x_load >= 130)   // 130 = x_load + w_load
			break;
	}
	Sleep(700); // cho dừng khi đạt 100%
	XoaManHinh();
	Sleep(500);   // cho dừng màn hình 
	ten_nhom();
	textcolor(7);
}
//chưa xong  // xem các thanh box hướng dẫn chạy thể nào nữa
void Frontend_co_dinh()
{
	// thanh hướng dẫn  x = 18  // y = 5
	int xF = 16;
	int yF = 1;
	int wF = 24;
	int hF = 2;
	int t_colorF = 15;
	int b_colorF = 15;
	box(xF, yF, wF, hF, t_colorF, b_colorF, "   F1 ''HUONG DAN''");
	box(xF + 1 * (wF + 3), yF, wF + 3, hF, t_colorF, b_colorF, " F4 ''THOAT CHUONG TRINH''");
	box(xF + 2 * (wF + 3) + 3, yF, wF, hF, t_colorF, b_colorF, "     ENTER ''CHON''");
	box(xF + 3 * (wF + 3) + 3, yF, wF, hF, t_colorF, b_colorF, " < > ''QUA LAI MENU''");
	box(xF + 4 * (wF + 3) + 3, yF, wF + 15, hF, t_colorF, b_colorF, " /\\ \\/ ''QUA LAI LUA CHON CUNG MENU''");


	//textcolor();
	Hinh_3D(82, 3);
	textcolor(9); // cho màu chữ = 9(xanh dương)
	gotoxy(123, 30); cout << "NGUYEN QUOC DUY  : N20DCCN013";
	textcolor(6); // cho màu chữ 6(vàng)
	gotoxy(122, 33); cout << "HOANG LE THUY HOA : N20DCCN016";
	textcolor(13); // cho màu chữ 13(tím)
	gotoxy(125, 36); cout << "LE VAN TIEN    : N20DCCN064 ";
	textcolor(7);
}

void thanhSang_F4(int TD_x, int TD_y, int TD_w, int TD_h, int b_color, string nd)    //  h côngj thêm 3
{
	int TD_x2 = TD_x + 11;
	int TD_w2 = TD_w - 9;
	int TD_h2 = TD_h;
	textcolor(b_color);
	for (int iy = TD_y + 1; iy <= TD_y + TD_h2 - 1; iy++)
	{
		for (int ix = TD_x2 + 1; ix <= TD_x2 + TD_w2 - 1; ix++)
		{
			gotoxy(ix, iy);
			cout << " ";  // chảy đến đâu thì có khoảng trắng đè lên ( màu b_color)
		}
	}
	//SetColor(b_color);  // màu chữ màu đen

	gotoxy(TD_x2 + 1, TD_y + 2);  // cho chữ ở giữa khung
	int iy = TD_y;
	if (iy == 15)
		nd = "        YES";
	if (iy == 20)
		nd = "        NO";
	cout << nd;
	textcolor(7);
}
// cần đổi màu là ok
void XoaChon_F1_F4()
{
	int TD_x = 16, TD_y = 1;


	textcolor(7);  // cho vùng xóa chữ F4 va F1 ko phải trong menu 1 và 0 đều thành màu đen
	// cho F1 
	gotoxy(TD_x, TD_y); cout << "                                                        ";
	gotoxy(TD_x, TD_y + 1); cout << "                                                        ";
	gotoxy(TD_x, TD_y + 2); cout << "                                                        ";


}
void thanhSang_0(int TD_x, int TD_y, int TD_w, int TD_h, int b_color, string nd)
{
	TD_x = TD_x + 3;
	TD_y = TD_y + 10;
	textcolor(b_color);
	for (int iy = TD_y + 1; iy <= TD_y + TD_h - 1; iy++)
	{
		for (int ix = TD_x + 1; ix <= TD_x + TD_w - 1; ix++)
		{
			gotoxy(ix, iy);
			cout << " ";  // chảy đến đâu thì có khoảng trắng đè lên ( màu b_color)
		}
	}
	//	textcolor(b_color);

		//SetColor(b_color);  // màu chữ màu đen
	int i = 2;
	gotoxy(TD_x + i, TD_y + i);  // cho chữ ở giữa khung

	int iy = TD_y;
	if (iy == 15)
		nd = "        LET'S GO ";
	if (iy == 20)
		nd = "        TRO GIUP";
	if (iy == 25)
		nd = "      EXIT (CHON LUA)";
	cout << nd;
	//SetColor(0);  // quay lại màu ban đầu 
	textcolor(7);  // quay về màu trắng

}
void thanhSang_03(int TD_x, int TD_y, int TD_w, int TD_h, int b_color, string nd)    //  h côngj thêm 3
{
	int TD_x2 = TD_x + 11;
	int TD_w2 = TD_w - 9;
	int TD_h2 = TD_h - 2;
	textcolor(b_color);
	for (int iy = TD_y + 1; iy <= TD_y + TD_h2 - 1; iy++)
	{
		for (int ix = TD_x2 + 1; ix <= TD_x2 + TD_w2 - 1; ix++)
		{
			gotoxy(ix, iy);
			cout << " ";  // chảy đến đâu thì có khoảng trắng đè lên ( màu b_color)
		}
	}
	//SetColor(b_color);  // màu chữ màu đen

	gotoxy(TD_x2 + 1, TD_y + 1);  // cho chữ ở giữa khung
	int iy = TD_y;
	if (iy == 15)
		nd = "       YES";
	if (iy == 18)
		nd = "        NO";
	cout << nd;
	textcolor(7);
}
void thanhSang_chinh(int TD_x, int TD_y, int TD_w, int TD_h, int b_color, string nd)
{
	textcolor(b_color);
	for (int iy = TD_y + 1; iy <= TD_y + TD_h - 1; iy++)
	{
		for (int ix = TD_x + 1; ix <= TD_x + TD_w - 1; ix++)
		{
			gotoxy(ix, iy);
			cout << " ";  // chảy đến đâu thì có khoảng trắng đè lên ( màu b_color)
		}
	}
	//SetColor(b_color);  // màu chữ màu đen

	gotoxy(TD_x + 2, TD_y + 2);  // cho chữ ở giữa khung
	int iy = TD_y;
	if (iy == 5)
		nd = "     CAP NHAT MAY BAY";
	if (iy == 10)
		nd = "    CAP NHAT CHUYEN BAY";
	if (iy == 15)
		nd = "          DAT VE";
	if (iy == 20)
		nd = "          HUY VE";
	if (iy == 25)
		nd = "   IN DANH SACH (CHON LUA)";
	if (iy == 30)
		nd = "   THONG KE SO LUOT TH BAY";
	cout << nd;
	textcolor(7);
}
void thanhSang_11(int TD_x, int TD_y, int TD_w, int TD_h, int b_color, string nd)    //  h côngj thêm 3
{
	int TD_x2 = TD_x + 11;
	int TD_w2 = TD_w - 9;
	int TD_h2 = TD_h - 2;
	textcolor(b_color);
	for (int iy = TD_y + 1; iy <= TD_y + TD_h2 - 1; iy++)
	{
		for (int ix = TD_x2 + 1; ix <= TD_x2 + TD_w2 - 1; ix++)
		{
			gotoxy(ix, iy);
			cout << " ";  // chảy đến đâu thì có khoảng trắng đè lên ( màu b_color)
		}
	}
	//SetColor(b_color);  // màu chữ màu đen


	gotoxy(TD_x2 + 1, TD_y + 1);  // cho chữ ở giữa khung
	int iy = TD_y;
	if (iy == 5)
		nd = "       THEM";
	if (iy == 8)
		nd = "       XOA";
	if (iy == 11)
		nd = "    HIEU CHINH";
	cout << nd;
	textcolor(7);
}
void thanhSang_15(int TD_x, int TD_y, int TD_w, int TD_h, int b_color, string nd)  // y + 20
{

	int TD_x5 = TD_x + 16;  //34
	int TD_w5 = TD_w + 4;
	int TD_h5 = TD_h - 2;

	textcolor(b_color);
	for (int iy = TD_y + 1; iy <= TD_y + TD_h5 - 1; iy++)
	{
		for (int ix = TD_x5 + 1; ix <= TD_x5 + TD_w5 - 1; ix++)
		{
			gotoxy(ix, iy);
			cout << " ";  // chảy đến đâu thì có khoảng trắng đè lên ( màu b_color)
		}
	}
	//	SetColor(b_color);  // màu chữ màu đen


	gotoxy(TD_x5 + 1, TD_y + 1);  // cho chữ ở giữa khung
	int iy = TD_y;
	if (iy == 5)
		nd = "   IN HANH KHAC THEO CHUYEN BAY ";
	if (iy == 8)
		nd = "    IN CHUYEN BAY THEO NGAY";
	if (iy == 11)
		nd = " IN VE CON TRONG THEO CHUYEN BAY";
	cout << nd;
	textcolor(7);
}

// ok
// di chuyển thanh lên xuống trong 1 menu

// MENU_F4 chỉ chạy  ở menu  0 và menu chính
void MENU_F4(int TD_x, int TD_y, int TD_w, int TD_h, int t_color, int b_color, int  b_color_sang, string nd, int& soLuong, string& name_menu, string& vt_thanh, char& phimBam)
{
	//name_menu = "F4";
	XoaManHinh();
	AnConTroChuot();
	Frontend_co_dinh();
	XoaChon_F1_F4();
	SetColor(12);  // cho chữ CHU THICH thanh mau đỏ
	gotoxy(TD_x + 30, TD_y + 8); cout << "       THOAT CHUONG TRINH";

	TD_x = TD_x + 3;
	TD_y = TD_y + 10;
	int TD_x2 = TD_x + 21;
	int TD_w2 = TD_w - 9;
	int TD_h2 = TD_h;
	int xp, yp, xcu, ycu;
	bool kt;
	xp = TD_x2; yp = TD_y;  // tọa độ thanh sáng
	xcu = xp;  ycu = yp; // tọa dộ cũ đệ xóa màu
	kt = true;
	soLuong = 2;
	box(TD_x2 + 11, TD_y, TD_w2, TD_h2, t_color, b_color, "        YES");
	box(TD_x2 + 11, TD_y + TD_h + 1, TD_w2, TD_h2, t_color, b_color, "       NO");

	while (true)
	{
		/////*** in *********
		if (kt == true) // cho 1 lệnh thực hiện trước mỗi phím bấm
		{
			////****** back space *******  // bấm rồi mới xóa các thanh đã tô màu  // bấm rồi mới xóa thanh cũ
			gotoxy(xcu, ycu);
			thanhSang_F4(xcu, ycu, TD_w, TD_h, b_color, nd);
			xcu = xp; ycu = yp;  // cập nhật lại
			/// **********
			thanhSang_F4(xp, yp, TD_w, TD_h, b_color_sang, nd);  // tô màu thanh đang trỏ đến 
			kt = false;
		}
		//**** dieu kien *********
		int yMin = TD_y;
		int yMax = yMin + (5 * (soLuong - 1));  /////////////////////////////////////////////////////
		if (_kbhit())
		{
			phimBam = _getch();
			kt = true;   // đã bấm
			if (yp == 15) vt_thanh = "F41";
			if (yp == 20)  vt_thanh = "F42";

			/*cout << yp;
			Sleep(4000);*/
			if (phimBam == Len || phimBam == Xuong)
			{
				if (phimBam == Len)  // len
				{
					yp -= 5;
					if (yp < yMin)
					{
						yp = yMax;

					}
				}
				if (phimBam == Xuong)  // xuong
				{
					yp += 5;
					if (yp > yMax)
					{
						yp = yMin;
					}
				}
			}
			if (vt_thanh == "F41")
			{
				if (phimBam == Enter)
				{
					break;
				}
			}
			if (vt_thanh == "F42")
			{
				if (phimBam == Enter)
				{
					break;
				}
			}

		}
	}




}
void MENU_0(int TD_x, int TD_y, int TD_w, int TD_h, int t_color, int b_color, int  b_color_sang, string nd, int& soLuong, string& name_menu, string& vt_thanh, char& phimBam)
{
	XoaManHinh();
	AnConTroChuot();
	Frontend_co_dinh();
	name_menu = "0";
	int xp, yp, xcu, ycu;
	bool kt;
	xp = TD_x; yp = TD_y;  // tọa độ thanh sáng
	xcu = xp;  ycu = yp; // tọa dộ cũ đệ xóa màu
	kt = true;
	soLuong = 3;
	box(TD_x + 3, TD_y + 10, TD_w, TD_h, t_color, b_color, "        LET'S GO ");
	box(TD_x + 3, TD_y + 15, TD_w, TD_h, t_color, b_color, "        TRO GIUP");
	box(TD_x + 3, TD_y + 20, TD_w, TD_h, t_color, b_color, "      EXIT (CHON LUA)");

	while (true)
	{
		/////*** in *********
		if (kt == true) // cho 1 lệnh thực hiện trước mỗi phím bấm
		{
			////****** back space *******  // bấm rồi mới xóa các thanh đã tô màu  // bấm rồi mới xóa thanh cũ
			gotoxy(xcu, ycu);
			thanhSang_0(xcu, ycu, TD_w, TD_h, b_color, nd);
			xcu = xp; ycu = yp;  // cập nhật lại
			/// **********
			thanhSang_0(xp, yp, TD_w, TD_h, b_color_sang, nd);  // tô màu thanh đang trỏ đến 
			kt = false;
		}
		//**** dieu kien *********
		int yMin = TD_y;
		int yMax = yMin + (5 * (soLuong - 1));  /////////////////////////////////////////////////////
		if (yp == TD_y)	       vt_thanh = "01";
		if (yp == TD_y + 5)	       vt_thanh = "02";
		if (yp == TD_y + 10)			vt_thanh = "03";
		if (_kbhit())
		{
			phimBam = _getch();
			kt = true;   // đã bấm

			if (phimBam == F1 || phimBam == F4)
			{
				break;
			}
			else if (phimBam == Len || phimBam == Xuong)  // len
			{
				if (phimBam == Len)
				{
					yp -= 5;
					if (yp < yMin)   // x = 50, y = 5
					{
						yp = yMax;
					}
				}
				if (phimBam == Xuong)  // xuong
				{
					yp += 5;
					if (yp > yMax)
					{
						yp = yMin;
					}
				}
			}
			else
			{
				if (vt_thanh == "01" || vt_thanh == "02")
				{
					if (phimBam == Enter)
					{
						break;
					}
				}

				if (vt_thanh == "03")
				{
					if (phimBam == Enter || phimBam == Phai)
						break;
				}
			}
		}
	}

}
void MENU_02(string& name_menu, string& vt_thanh, char& phimBam)
{
	name_menu = "02";
	XoaManHinh();
	AnConTroChuot();
	int x = 65; int y = 17; int w = 20; int h = 2; int t_col = 11; int b_col = 7;

	SetColor(12);  // cho chữ CHU THICH thanh mau đỏ
	gotoxy(x + 5, y - 3); cout << "CHU THICH";

	box(x, y, w, h, t_col, b_col, "       ESC ");
	box(x, y + 2, w, h, t_col, b_col, "       F1");
	box(x, y + 4, w, h, t_col, b_col, "       F4");
	box(x, y + 6, w, h, t_col, b_col, "     NUT LEN");
	box(x, y + 8, w, h, t_col, b_col, "    NUT XUONG");
	box(x, y + 10, w, h, t_col, b_col, "     NUT TRAI");
	box(x, y + 12, w, h, t_col, b_col, "     NUT PHAI ");
	box(x, y + 14, w, h, t_col, b_col, "      ENTER");

	box(x + w, y, w + 40, h, t_col, b_col, " TRO GIUP quay ve MENU ban dau ");  // abs
	box(x + w, y + 2, w + 40, h, t_col, b_col, " MENU chinh xem chu thich ");  // f1
	box(x + w, y + 4, w + 40, h, t_col, b_col, " THOAT chuong trinh");   //f4
	box(x + w, y + 6, w + 40, h, t_col, b_col, " DI CHUYEN qua lai cac lua chon menu");  // nut len
	box(x + w, y + 8, w + 40, h, t_col, b_col, " DI CHUYEN qua lai cac lua chon menu");   // nut xuong
	box(x + w, y + 10, w + 40, h, t_col, b_col, " QUAY LAI MENU truoc ");      // trai 
	box(x + w, y + 12, w + 40, h, t_col, b_col, " LUA CHON MENU co 'chon lua'");   //  phai
	box(x + w, y + 14, w + 40, h, t_col, b_col, " CHON LUA ");    // Enter


	/*  bắt lỗi các thanh */
	// màu xanh dương
	int iy = 2;
	textcolor(7);
	for (int i = 1; i <= 7; i++)
	{
		/*gotoxy(x, y + iy); cout << char(179);*/
		gotoxy(x, y + iy); cout << char(195);
		gotoxy(x + w, y + iy); cout << char(197);
		gotoxy(x + (2 * w) + 40, y + iy); cout << char(180);
		iy = iy + 2;
	}
	gotoxy(x + w, y); cout << char(194);
	gotoxy(x + w, y + 16); cout << char(193);


	box(x + w, y + 17, w + 20, 4, t_col, b_col, " ");    // khong in noi dung j
	   // thay đổi thanh màu 
	textcolor(100);
	for (int iy = y + 18; iy <= y + 18 + 2; iy++)
	{
		for (int ix = x + w + 1; ix <= x + (2 * w) + 20 - 1; ix++)
		{
			gotoxy(ix, iy);
			cout << " ";  // chảy đến đâu thì có khoảng trắng đè lên ( màu b_color)
		}
	}
	SetColor(9);   // thay đổi màu chữ thành màu xanh
	gotoxy(x + w + 11, y + 18); cout << "ENTER hoac ESC ";
	gotoxy(x + w + 13, y + 19); cout << "< THOAT > ";

	while (true)
	{
		if (_kbhit())
		{
			phimBam = _getch();
			if (phimBam == Enter || phimBam == Esc)  // len
			{
				break;
			}
		}
	}
	textcolor(7);  // quay lại màu = 7 (đen)  // phông đen
}
void MENU_03(int TD_x, int TD_y, int TD_w, int TD_h, int t_color, int b_color, int  b_color_sang, string nd, int& soLuong, string& name_menu, string& vt_thanh, char& phimBam)
{
	name_menu = "03";
	AnConTroChuot();
	XoaChon_F1_F4();
	TD_x = TD_x + 3;
	TD_y = TD_y + 10;
	int TD_x2 = TD_x + 21;
	int TD_w2 = TD_w - 9;
	int TD_h2 = TD_h - 2;
	int xp, yp, xcu, ycu;
	bool kt;
	xp = TD_x2; yp = TD_y;  // tọa độ thanh sáng
	xcu = xp;  ycu = yp; // tọa dộ cũ đệ xóa màu
	kt = true;
	soLuong = 2;
	box(TD_x2 + 11, TD_y, TD_w2, TD_h2, t_color, b_color, "       YES");
	box(TD_x2 + 11, TD_y + 3, TD_w2, TD_h2, t_color, b_color, "        NO");

	while (true)
	{
		/////*** in *********
		if (kt == true) // cho 1 lệnh thực hiện trước mỗi phím bấm
		{
			////****** back space *******  // bấm rồi mới xóa các thanh đã tô màu  // bấm rồi mới xóa thanh cũ
			gotoxy(xcu, ycu);
			thanhSang_03(xcu, ycu, TD_w, TD_h, b_color, nd);
			xcu = xp; ycu = yp;  // cập nhật lại
			/// **********
			thanhSang_03(xp, yp, TD_w, TD_h, b_color_sang, nd);  // tô màu thanh đang trỏ đến 
			kt = false;
		}
		//**** dieu kien *********
		int yMin = TD_y;
		int yMax = yMin + (3 * (soLuong - 1));  /////////////////////////////////////////////////////
		if (_kbhit())
		{
			phimBam = _getch();
			kt = true;   // đã bấm
			if (yp == 15) vt_thanh = "031";
			if (yp == 18)  vt_thanh = "032";

			if (phimBam == Len || phimBam == Xuong)
			{
				if (phimBam == Len)  // len
				{
					yp -= 3;
					if (yp < yMin)
					{
						yp = yMax;

					}
				}
				if (phimBam == Xuong)  // xuong
				{
					yp += 3;
					if (yp > yMax)
					{
						yp = yMin;
					}
				}
			}
			if (vt_thanh == "031")
			{
				if (phimBam == Enter || phimBam == Trai)
					break;
			}
			if (vt_thanh == "032")
			{
				if (phimBam == Enter || phimBam == Trai)
					break;
			}

		}
	}

}
void MENUChinh(int TD_x, int TD_y, int TD_w, int TD_h, int t_color, int b_color, int  b_color_sang, string nd, int& soLuong, string& name_menu, string& vt_thanh, char& phimBam)
{
	XoaManHinh();
	AnConTroChuot();
	Frontend_co_dinh();
	name_menu = "1";
	int xp, yp, xcu, ycu;
	bool kt;
	xp = TD_x; yp = TD_y;  // tọa độ thanh sáng
	xcu = xp;  ycu = yp; // tọa dộ cũ đệ xóa màu
	kt = true;
	soLuong = 6;
	box(TD_x, TD_y, TD_w, TD_h, t_color, b_color, "     CAP NHAT MAY BAY");
	box(TD_x, TD_y + 5, TD_w, TD_h, t_color, b_color, "    CAP NHAT CHUYEN BAY");
	box(TD_x, TD_y + 10, TD_w, TD_h, t_color, b_color, "          DAT VE");
	box(TD_x, TD_y + 15, TD_w, TD_h, t_color, b_color, "          HUY VE");
	box(TD_x, TD_y + 20, TD_w, TD_h, t_color, b_color, "   IN DANH SACH (CHON LUA)");
	box(TD_x, TD_y + 25, TD_w, TD_h, t_color, b_color, "   THONG KE SO LUOT TH BAY");
	while (true)
	{
		/////*** in *********
		if (kt == true) // cho 1 lệnh thực hiện trước mỗi phím bấm
		{
			////****** back space *******  // bấm rồi mới xóa các thanh đã tô màu  // bấm rồi mới xóa thanh cũ
			gotoxy(xcu, ycu);
			thanhSang_chinh(xcu, ycu, TD_w, TD_h, b_color, nd);
			xcu = xp; ycu = yp;  // cập nhật lại
			/// **********
			thanhSang_chinh(xp, yp, TD_w, TD_h, b_color_sang, nd);  // tô màu thanh đang trỏ đến 
			kt = false;
		}
		//**** dieu kien *********
		int yMin = TD_y;
		int yMax = yMin + (5 * (soLuong - 1));  /////////////////////////////////////////////////////
		if (_kbhit())
		{
			phimBam = _getch();
			kt = true;   // đã bấm
			if (yp == 5)	       vt_thanh = "11";
			if (yp == 10)	       vt_thanh = "12";
			if (yp == 15)			vt_thanh = "13";
			if (yp == 20)			vt_thanh = "14";
			if (yp == 25)			vt_thanh = "15";
			if (yp == 30)			vt_thanh = "16";
			if (phimBam == Enter || phimBam == Phai || phimBam == Len || phimBam == Xuong || phimBam == F1 || phimBam == F4) // Bắt th phát hiện chuyển menu /****************************
			{
				if (phimBam == F1 || phimBam == F4 || phimBam == Enter)// Bắt th phát hiện chuyển menu /****************************
				{
					break;
				}
				else if (phimBam == Len || phimBam == Xuong)  // len
				{
					if (phimBam == Len)
					{
						yp -= 5;
						if (yp < yMin)   // x = 50, y = 5
						{
							yp = yMax;
						}
					}
					if (phimBam == Xuong)  // xuong
					{
						yp += 5;
						if (yp > yMax)
						{
							yp = yMin;
						}
					}
				}
				if (vt_thanh == "11" || vt_thanh == "15")
				{
					if (phimBam == Phai)
						break;
				}

			}
		}
	}
}
void hinhMenuChinh(int TD_x, int TD_y, int TD_w, int TD_h, int t_color, int b_color, int  b_color_sang)
{
	XoaManHinh();
	AnConTroChuot();
	Frontend_co_dinh();
	int xp, yp, xcu, ycu;
	bool kt;
	xp = TD_x; yp = TD_y;  // tọa độ thanh sáng
	xcu = xp;  ycu = yp; // tọa dộ cũ đệ xóa màu
	kt = true;
	box(TD_x, TD_y, TD_w, TD_h, t_color, b_color, "     CAP NHAT MAY BAY");
	box(TD_x, TD_y + 5, TD_w, TD_h, t_color, b_color, "    CAP NHAT CHUYEN BAY");
	box(TD_x, TD_y + 10, TD_w, TD_h, t_color, b_color, "          DAT VE");
	box(TD_x, TD_y + 15, TD_w, TD_h, t_color, b_color, "          HUY VE");
	box(TD_x, TD_y + 20, TD_w, TD_h, t_color, b_color, "   IN DANH SACH (CHON LUA)");
	box(TD_x, TD_y + 25, TD_w, TD_h, t_color, b_color, "   THONG KE SO LUOT TH BAY");

}

void MENU_chuThich()
{
	XoaManHinh();
	AnConTroChuot();
	int x = 65; int y = 17; int w = 20; int h = 2; int t_col = 11; int b_col = 7;
	SetColor(12);  // cho chữ CHU THICH thanh mau đỏ
	gotoxy(x + 5, y - 3); cout << "CHU THICH";

	box(x, y, w, h, t_col, b_col, "       ESC ");
	box(x, y + 2, w, h, t_col, b_col, "       F1");
	box(x, y + 4, w, h, t_col, b_col, "       F4");
	box(x, y + 6, w, h, t_col, b_col, "     NUT LEN");
	box(x, y + 8, w, h, t_col, b_col, "    NUT XUONG");
	box(x, y + 10, w, h, t_col, b_col, "     NUT TRAI");
	box(x, y + 12, w, h, t_col, b_col, "     NUT PHAI ");
	box(x, y + 14, w, h, t_col, b_col, "      ENTER");

	box(x + w, y, w + 40, h, t_col, b_col, " TRO GIUP quay ve MENU ban dau ");  // abs
	box(x + w, y + 2, w + 40, h, t_col, b_col, " MENU chinh xem chu thich ");  // f1
	box(x + w, y + 4, w + 40, h, t_col, b_col, " THOAT chuong trinh");   //f4
	box(x + w, y + 6, w + 40, h, t_col, b_col, " DI CHUYEN qua lai cac lua chon menu");  // nut len
	box(x + w, y + 8, w + 40, h, t_col, b_col, " DI CHUYEN qua lai cac lua chon menu");   // nut xuong
	box(x + w, y + 10, w + 40, h, t_col, b_col, " QUAY LAI MENU truoc ");      // trai 
	box(x + w, y + 12, w + 40, h, t_col, b_col, " LUA CHON MENU co 'chon lua'");   //  phai
	box(x + w, y + 14, w + 40, h, t_col, b_col, " CHON LUA ");    // Enter

	/*  bắt lỗi các thanh */
	int iy = 2;
	textcolor(7);
	for (int i = 1; i <= 7; i++)
	{
		/*gotoxy(x, y + iy); cout << char(179);*/
		gotoxy(x, y + iy); cout << char(195);
		gotoxy(x + w, y + iy); cout << char(197);
		gotoxy(x + (2 * w) + 40, y + iy); cout << char(180);
		iy = iy + 2;
	}
	gotoxy(x + w, y); cout << char(194);
	gotoxy(x + w, y + 16); cout << char(193);

	box(x + w, y + 17, w + 20, 4, t_col, b_col, " ");    // khong in noi dung j
	   // thay đổi thanh màu
	textcolor(100);
	for (int iy = y + 18; iy <= y + 18 + 2; iy++)
	{
		for (int ix = x + w + 1; ix <= x + (2 * w) + 20 - 1; ix++)
		{
			gotoxy(ix, iy);
			cout << " ";  // chảy đến đâu thì có khoảng trắng đè lên ( màu b_color)
		}
	}
	SetColor(9);   // thay đổi màu chữ thành màu xanh
	gotoxy(x + w + 11, y + 18); cout << "ENTER hoac ESC ";
	gotoxy(x + w + 13, y + 19); cout << "< THOAT > ";

	while (true)
	{
		if (_kbhit())
		{
			int c = _getch();
			if (c == Enter || c == Esc)  // len
			{
				break;
			}
		}
	}

	textcolor(7);  // quay lại màu = 7 (đen)  // phông đen
}
void MENU_11(int TD_x, int TD_y, int TD_w, int TD_h, int t_color, int b_color, int  b_color_sang, string nd, int& soLuong, string& name_menu, string& vt_thanh, char& phimBam)
{
	name_menu = "11";
	XoaChon_F1_F4();
	AnConTroChuot();
	int TD_x2 = TD_x + 21;
	int TD_w2 = TD_w - 9;
	int TD_h2 = TD_h - 2;
	soLuong = 3;
	int xp, yp, xcu, ycu;
	bool kt;
	xp = TD_x2; yp = TD_y;  // tọa độ thanh sáng
	xcu = xp;  ycu = yp; // tọa dộ cũ đệ xóa màu
	kt = true;
	soLuong = 3;
	box(TD_x2 + 11, TD_y, TD_w2, TD_h2, t_color, b_color, "       THEM");
	box(TD_x2 + 11, TD_y + 3, TD_w2, TD_h2, t_color, b_color, "       XOA");
	box(TD_x2 + 11, TD_y + 6, TD_w2, TD_h2, t_color, b_color, "    HIEU CHINH");
	while (true)
	{
		/////*** in *********
		if (kt == true) // cho 1 lệnh thực hiện trước mỗi phím bấm
		{
			////****** back space *******  // bấm rồi mới xóa các thanh đã tô màu  // bấm rồi mới xóa thanh cũ
			gotoxy(xcu, ycu);
			thanhSang_11(xcu, ycu, TD_w, TD_h, b_color, nd);
			xcu = xp; ycu = yp;  // cập nhật lại
			/// **********
			thanhSang_11(xp, yp, TD_w, TD_h, b_color_sang, nd);  // tô màu thanh đang trỏ đến 
			kt = false;
		}
		//**** dieu kien *********
		int yMin = TD_y;
		int yMax = yMin + (3 * (soLuong - 1));  /////////////////////////////////////////////////////
		if (_kbhit())
		{
			phimBam = _getch();
			kt = true;   // đã bấm
			if (yp == 5)  vt_thanh = "111";
			if (yp == 8)  vt_thanh = "112";
			if (yp == 11)  vt_thanh = "113";
			if (phimBam == Enter || phimBam == Trai || phimBam == Len || phimBam == Xuong)
			{
				if (phimBam == Enter) // chon menu
				{
					break;
				}
				else if (phimBam == Trai) // quay ve menu 1
				{
					break;
				}
				else if (phimBam == Len || phimBam == Xuong)
				{
					if (phimBam == Len)  // len
					{
						yp -= 3;
						if (yp < yMin)
						{
							yp = yMax;

						}
					}
					if (phimBam == Xuong)  // xuong
					{
						yp += 3;
						if (yp > yMax)
						{
							yp = yMin;
						}
					}
				}
			}
		}
	}
}
void MENU_15(int TD_x, int TD_y, int TD_w, int TD_h, int t_color, int b_color, int  b_color_sang, string nd, int& soLuong, string& name_menu, string& vt_thanh, char& phimBam)  // y đã thay đổi rồi 
{
	name_menu = "15";
	XoaChon_F1_F4();
	AnConTroChuot();
	int TD_x5 = TD_x + 16;  //34
	int TD_w5 = TD_w + 4;
	int TD_h5 = TD_h - 2;
	soLuong = 3;
	int xp, yp, xcu, ycu;
	bool kt;
	xp = TD_x5; yp = TD_y;  // tọa độ thanh sáng  // yp đầu = 29
	xcu = xp;  ycu = yp; // tọa dộ cũ đệ xóa màu
	kt = true;
	soLuong = 3;
	box(TD_x5 + 16, TD_y, TD_w5, TD_h5, t_color, b_color, "   IN HANH KHAC THEO CHUYEN BAY ");  // toa do  x = 
	box(TD_x5 + 16, TD_y + 3, TD_w5, TD_h5, t_color, b_color, "    IN CHUYEN BAY THEO NGAY");
	box(TD_x5 + 16, TD_y + 6, TD_w5, TD_h5, t_color, b_color, " IN VE CON TRONG THEO CHUYEN BAY");
	while (true)
	{
		/////*** in *********
		if (kt == true) // cho 1 lệnh thực hiện trước mỗi phím bấm
		{
			////****** back space *******  // bấm rồi mới xóa các thanh đã tô màu  // bấm rồi mới xóa thanh cũ
			gotoxy(xcu, ycu);
			thanhSang_15(xcu, ycu, TD_w, TD_h, b_color, nd);
			xcu = xp; ycu = yp;  // cập nhật lại
			/// **********
			thanhSang_15(xp, yp, TD_w, TD_h, b_color_sang, nd);  // tô màu thanh đang trỏ đến 
			kt = false;
		}
		//**** dieu kien *********
		int yMin = TD_y;
		int yMax = yMin + (3 * (soLuong - 1));
		if (_kbhit())
		{
			phimBam = _getch();
			kt = true;   // đã bấm
			if (yp == 5)	vt_thanh = "151";
			if (yp == 8)	vt_thanh = "152";
			if (yp == 11)	vt_thanh = "153";
			if (phimBam == Enter || phimBam == Trai || phimBam == Len || phimBam == Xuong) // phat hien phim enter
			{
				if (phimBam == Enter)  // chon
				{
					break;
				}
				if (phimBam == Trai)  // quay ve menu 1
				{
					break;
				}

				if (phimBam == Len || phimBam == Xuong)
				{
					if (phimBam == Len)  // len
					{
						yp -= 3;
						if (yp < yMin)
						{
							yp = yMax;
						}
					}
					if (phimBam == Xuong)  // xuong
					{
						yp += 3;
						if (yp > yMax)
						{
							yp = yMin;
						}
					}
				}
			}
		}
	}

}
