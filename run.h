# include<iostream>
# include"console.h"
# include"myLib.h"

using namespace std;

void runBeta(dsMB& qlMB, chuyenBay*& head, PTRHK& DSHK, string*& DSSB, int TD_x, int TD_y, int TD_w, int TD_h, int t_color, int b_color, int  b_color_sang, string nd, int& soLuong, string& name_menu, string& vt_thanh, char& phimBam)
{
	
	
	head = NULL;
	DSHK = NULL;

	qlMB.count = 0;
	
	us countCB = 0;
	us countHK = 0;
	
	chuyenBay* ptr = head;
	
	DSSB = new string[22];
	duLieuSanBay(DSSB);

	loadDataMB(qlMB);

	loadDataCB(head, countCB);
	loadDataVeMB(head);
	loadDataHK(DSHK, countHK);

	resizeConsole(1920, 1080);
	Frontend_chay();
	AnConTroChuot();
	XoaManHinh();
	MENU_0(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);

	while (true)
	{
		if (name_menu == "0")
		{
			if (phimBam == F4)
			{
				MENU_F4(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
				if (vt_thanh == "F41")
				{
					XoaManHinh();
					return;
				}
				else
					MENU_0(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
			}

			else if (phimBam == F1)
			{
				MENU_02(name_menu, vt_thanh, phimBam);
			}
			else
			{
				if (vt_thanh == "01")
				{
					if (phimBam == Enter)
					{

						MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
				if (vt_thanh == "02")
				{
					if (phimBam == Enter)
					{

						MENU_02(name_menu, vt_thanh, phimBam);
					}

				}
				if (vt_thanh == "03")
				{
					if (phimBam == Enter || phimBam == Phai)
					{

						MENU_03(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);

					}
				}

			}
		}
		if (name_menu == "02")
		{
			if (phimBam == Enter || phimBam == Esc)
			{
				MENU_0(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
			}
		}
		if (name_menu == "03")
		{
			if (vt_thanh == "031")
			{

				if (phimBam == Enter)
				{
					XoaManHinh();
					return;
				}
				if (phimBam == Trai)
				{

					MENU_0(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
				}
			}
			if (vt_thanh == "032")
			{
				if (phimBam == Enter || phimBam == Trai)
				{

					XoaManHinh();
					MENU_0(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
				}
			}
		}
		if (name_menu == "1")
		{
			if (phimBam == F4)
			{
				MENU_F4(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
				if (vt_thanh == "F41")
				{
					XoaManHinh();

					saveDataMB(qlMB);

					saveDataCB(head, countCB);

					saveDataVeMB(head);

					saveDataHK(DSHK, countHK);

					for (us i = 0; i < qlMB.count; i++) delete qlMB.ptr[i];

					if (ptr != NULL)
					{
						while (ptr->next != NULL)
						{
							delete ptr->qlveMB.ptr;
							ptr = ptr->next;
						}
					}

					xoaBoNhoChuyenBay(head);

					delete[]DSSB;

					return;
				}
				else
					MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
			}
			else if (phimBam == F1)
			{
				XoaManHinh();
				MENU_chuThich();
				MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
			}
			else
			{
				if (vt_thanh == "11")
				{
					if (phimBam == Enter || phimBam == Phai)
					{
						MENU_11(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
				if (vt_thanh == "12")
				{
					if (phimBam == Enter)
					{
						HienConTroChuot();
						chucNang2_1(head, qlMB, DSSB, countCB);
						MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
				if (vt_thanh == "13")
				{
					if (phimBam == Enter)
					{
						HienConTroChuot();
						chucNang3_1(head, qlMB, DSHK, countHK);
						MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
				if (vt_thanh == "14")
				{
					if (phimBam == Enter)
					{
						HienConTroChuot();
						chucNang4_1(head, qlMB, DSHK);
						MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
				if (vt_thanh == "15")
				{
					if (phimBam == Enter || phimBam == Phai)
					{
						MENU_15(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
				if (vt_thanh == "16")
				{
					if (phimBam == Enter)
					{
						HienConTroChuot();
						chucNang6_1(qlMB);
						MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
			}
		}
		if (name_menu == "11")
		{
			if (phimBam == Trai)
			{
				MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
			}
			else
			{
				if (vt_thanh == "111")
				{
					if (phimBam == Enter)
					{
						HienConTroChuot();
						chucNang1_1(qlMB, head);
						hinhMenuChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang);
						thanhSang_chinh(TD_x, TD_y, TD_w, TD_h, b_color_sang, "   CAP NHAT DS (CHON LUA)");  // tô màu thanh đang trỏ đến 
						MENU_11(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
						//MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
				if (vt_thanh == "112")
				{
					if (phimBam == Enter)
					{
						HienConTroChuot();
						chucNang1_2(qlMB, head);
						hinhMenuChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang);
						thanhSang_chinh(TD_x, TD_y, TD_w, TD_h, b_color_sang, "   CAP NHAT DS (CHON LUA)");  // tô màu thanh đang trỏ đến 
						MENU_11(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
						//MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
				if (vt_thanh == "113")
				{
					if (phimBam == Enter)
					{
						HienConTroChuot();
						chucNang1_0(qlMB, head);
						hinhMenuChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang);
						thanhSang_chinh(TD_x, TD_y, TD_w, TD_h, b_color_sang, "   CAP NHAT DS (CHON LUA)");  // tô màu thanh đang trỏ đến 
						MENU_11(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
						//MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
			}
		}
		if (name_menu == "15")
		{
			if (phimBam == Trai)
			{
				MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
			}
			else
			{
				if (vt_thanh == "151")
				{
					if (phimBam == Enter)
					{
						HienConTroChuot();
						chucNang5_1(DSHK, head);
						hinhMenuChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang);
						thanhSang_chinh(TD_x, TD_y, TD_w, TD_h, b_color_sang, "   IN DANH SACH (CHON LUA)");  // tô màu thanh đang trỏ đến 
						MENU_15(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					//	MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
				if (vt_thanh == "152")
				{
					if (phimBam == Enter)
					{
						HienConTroChuot();
						chucNang5_2(DSSB, head);	
						hinhMenuChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang);
						thanhSang_chinh(TD_x, TD_y, TD_w, TD_h, b_color_sang, "   IN DANH SACH (CHON LUA)");  // tô màu thanh đang trỏ đến 
						MENU_15(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					//	MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
				if (vt_thanh == "153")
				{
					if (phimBam == Enter)
					{
						HienConTroChuot();
						chucNang5_3(head);
						hinhMenuChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang);
						thanhSang_chinh(TD_x, TD_y, TD_w, TD_h, b_color_sang, "   IN DANH SACH (CHON LUA)");  // tô màu thanh đang trỏ đến 
						MENU_15(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
						//MENUChinh(TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
					}
				}
			}
		}
	}
}
