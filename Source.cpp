#include "run.h"

int main()
{
	dsMB qlMB;
	chuyenBay* head;
	PTRHK DSHK;

	int soLuong = 0;
	int TD_x = 18, TD_y =5;
	int TD_w = 30, TD_h = 4;
	int t_color = 15, b_color = 15;
	int b_color_sang = 100;
		
	string* DSSB;
	string name_menu;
	string vt_thanh ;
	string nd;
	
	char phimBam;

	runBeta(qlMB, head, DSHK, DSSB, TD_x, TD_y, TD_w, TD_h, t_color, b_color, b_color_sang, nd, soLuong, name_menu, vt_thanh, phimBam);
}
