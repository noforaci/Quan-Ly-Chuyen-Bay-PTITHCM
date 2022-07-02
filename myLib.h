#include "menu.h"
#include <sstream>
#include <fstream>

using namespace std;

#define MaxMB 300

typedef unsigned short us;

struct mayBay
{
	string soHieuMayBay;
	string loaiMayBay;

	int soCho;
	us daThucHien;

	bool trangThai;
};
struct dsMB
{
	mayBay* ptr[MaxMB];
	us count;
};

struct thoiGian
{
	us ngay;
	us thang;
	us nam;

	us gio;
	us phut;
};

struct veMayBay
{
	us soGhe;
	us soThuTu;
	string soCmnd;
};
struct dsveMB
{
	veMayBay* ptr;
	us daDat;
};

struct NodeHK 
{
	string soCMND;
	string ho;
	string ten;
	
	us phai; //0 - nam : 1 - nu
};
struct dshk 
{
	NodeHK data;
	int height;
	dshk* left;
	dshk* right;
};
typedef dshk* PTRHK;

struct chuyenBay
{
	string maChuyenBay;
	string sanBayDen;
	string soHieuMayBay;

	us trangThai;
	us soCho; // dung quan ly danh sach bay

	thoiGian ngayGioBay;

	chuyenBay* next;

	dsveMB qlveMB;

	bool *gheDaDat;
};

bool IsEmptyDSHK(PTRHK DSHK) 
{
	if (DSHK == NULL) return 1;
	return 0;
}

int GetHeight(PTRHK DSHK) 
{
	if (IsEmptyDSHK(DSHK)) return 0;
	return DSHK->height;
}

int Max(int a, int b) 
{
	if (a >= b) return a;
	return b;
}

//---Thao tac xoay phai
PTRHK RightRotate(PTRHK& DSHK) 
{
	PTRHK x = DSHK->left;
	// Bat dau xoay phai
	DSHK->left = x->right;
	x->right = DSHK;
	//Thiet lap chieu cao
	DSHK->height = 1 + Max(GetHeight(DSHK->left), GetHeight(DSHK->right));
	x->height = 1 + Max(GetHeight(x->left), GetHeight(x->right));

	return x;
}

//---Thao tac xoay trai
PTRHK LeftRotate(PTRHK& DSHK) 
{
	PTRHK y = DSHK->right;
	// Bat dau xoay trai
	DSHK->right = y->left;
	y->left = DSHK;
	//Thiet lap chieu cao
	DSHK->height = 1 + Max(GetHeight(DSHK->left), GetHeight(DSHK->right));
	y->height = 1 + Max(GetHeight(y->left), GetHeight(y->right));

	return y;
}

int valueBalance(PTRHK DSHK)
{
	if (IsEmptyDSHK(DSHK)) return 0;
	return GetHeight(DSHK->left) - GetHeight(DSHK->right);
}

//---Them mot Node vao AVL Tree
PTRHK InsertNode_HK(PTRHK& DSHK, NodeHK hk)
{
	//1. Bat dau Insert
	if (IsEmptyDSHK(DSHK)) 
	{
		PTRHK p = new dshk;
		p->height = 1;
		p->left = NULL;
		p->right = NULL;
		p->data = hk;
		DSHK = p;
		return DSHK; // Thiet lap Node co height = 1
	}
	else 
	{
		if (hk.soCMND < DSHK->data.soCMND) 
		{
			DSHK->left = InsertNode_HK(DSHK->left, hk);
		}
		else 
		{
			if (hk.soCMND > DSHK->data.soCMND) 
			{
				DSHK->right = InsertNode_HK(DSHK->right, hk);
			}
			else return DSHK; //Bang thi khong them
		}
	}
	//2. Thiet lap chieu cao
	DSHK->height = 1 + Max(GetHeight(DSHK->left), GetHeight(DSHK->right));
	//3. Cac thao tac xoay
	//3.0 Gia tri tu can bang
	int valBalance = valueBalance(DSHK);

	//Kiem tra 4 truong hop lam cay mat can bang
	//3.1 LEFT LEFT
	if (valBalance > 1 && hk.soCMND < DSHK->left->data.soCMND) return RightRotate(DSHK);

	//3.2 RIGHT RIGHT
	if (valBalance < -1 && hk.soCMND > DSHK->right->data.soCMND) return LeftRotate(DSHK);

	//3.3 LEFT RIGHT
	if (valBalance > 1 && hk.soCMND > DSHK->left->data.soCMND) 
	{
		DSHK->left = LeftRotate(DSHK->left);
		return RightRotate(DSHK);
	}
	//3.4 RIGHT LEFT
	if (valBalance < -1 && hk.soCMND < DSHK->right->data.soCMND) 
	{
		DSHK->right = RightRotate(DSHK->right);
		return LeftRotate(DSHK);
	}

	return DSHK;
}

PTRHK MaxValueNodeDSHK(PTRHK DSHK) 
{
	PTRHK current = DSHK;

	//Tim node co gia tri lon nhat
	while (current->right != NULL) current = current->right;

	return current;
}

//---Xoa mot Node khoi AVL Tree
PTRHK DeleteNode_HK(PTRHK& DSHK, string soCMND) 
{
	//1. Bat dau xoa Node
	if (IsEmptyDSHK(DSHK)) 
	{
		return DSHK; //Danh sach rong
	}

	if (soCMND > DSHK->data.soCMND) 
	{
		DeleteNode_HK(DSHK->right, soCMND);
	}
	else if (soCMND < DSHK->data.soCMND) 
	{
		DeleteNode_HK(DSHK->left, soCMND);
	}
	// da tim thay Node can xoa
	else 
	{
		//Truong hop node can xoa co 0 node con hoac 1 node con
		if (DSHK->left == NULL || DSHK->right == NULL) 
		{
			PTRHK tmp = DSHK->left;
			if (DSHK->right != NULL) tmp = DSHK->right;
			//TH: 0 con - no child case
			if (tmp == NULL) 
			{
				tmp = DSHK;
				DSHK = NULL;
				delete tmp;
			}
			//TH: 1 con - one child case
			else 
			{
				*DSHK = *tmp;
				delete tmp;
			}
		}
		//Truong hop node can xoa co 2 node con
		else 
		{
			PTRHK tmp = MaxValueNodeDSHK(DSHK);
			DSHK->data = tmp->data;
			DSHK->right = DeleteNode_HK(DSHK->right, tmp->data.soCMND);
		}
	}

	if (IsEmptyDSHK(DSHK)) return DSHK; //Neu khong con gi thi thoat ra	

	//2. Thiet lap chieu cao
	DSHK->height = 1 + Max(GetHeight(DSHK->left), GetHeight(DSHK->right));
	//3. Cac thao tac xoay
	//3.0 Gia tri tu can bang
	int valBalance = valueBalance(DSHK);

	//Kiem tra 4 truong hop lam cay mat can bang
	//3.1 LEFT LEFT
	if (valBalance > 1 && valueBalance(DSHK->left) >= 0) return RightRotate(DSHK);

	//3.2 RIGHT RIGHT
	if (valBalance < -1 && valueBalance(DSHK->right) <= 0) return LeftRotate(DSHK);

	//3.3 LEFT RIGHT
	if (valBalance > 1 && valueBalance(DSHK->left) <= 0) 
	{
		DSHK->left = LeftRotate(DSHK->left);
		return RightRotate(DSHK);
	}
	
	//3.4 RIGHT LEFT
	if (valBalance < -1 && valueBalance(DSHK->right) > 0) 
	{
		DSHK->right = RightRotate(DSHK->right);
		return LeftRotate(DSHK);
	}

	return DSHK;
}

//---Tim kiem mot Node tren AVL Tree
PTRHK SearchNode_HK(PTRHK DSHK, string soCMND) 
{
	if (IsEmptyDSHK(DSHK)) return NULL; //Danh sach rong
	
	if (soCMND > DSHK->data.soCMND) 
	{
		SearchNode_HK(DSHK->right, soCMND);
	}
	else if (soCMND < DSHK->data.soCMND) {
		SearchNode_HK(DSHK->left, soCMND);
	}
	//tim thay soCMND
	else 
	{
		return DSHK; //tra ve neu tim thay
	}
	
	return NULL; //Tra ve null neu khong tim thay
}

//---Ham check trung lap HK
int Match_HK(PTRHK DSHK, char checker[]) 
{
	if (DSHK == NULL) return 0;
	else 
	{
		if (DSHK->data.soCMND == checker) return 1;
		else if (DSHK->data.soCMND, checker) Match_HK(DSHK->left, checker);
		else Match_HK(DSHK->right, checker);
	}
}

//---Tim kiem soCMND trong AVL Tree
PTRHK Search_HK(PTRHK& DSHK, string soCMND) 
{
	if (IsEmptyDSHK(DSHK)) return NULL;
	else 
	{
		if (DSHK->data.soCMND == soCMND) return DSHK;
		else if (DSHK->data.soCMND > soCMND) Search_HK(DSHK->left, soCMND);
		else Search_HK(DSHK->right, soCMND);
	}
}


// File I/O
void loadDataMB(dsMB& qlMB)
{
	ifstream ifs("maybay.txt");
	
	ifs >> qlMB.count;
	ifs.ignore();

	for (us i = 0; i < qlMB.count; i++)
	{
		qlMB.ptr[i] = new mayBay;
		
		getline(ifs, qlMB.ptr[i]->loaiMayBay);
		ifs >> qlMB.ptr[i]->soHieuMayBay;
		
		ifs >> qlMB.ptr[i]->soCho;
		ifs >> qlMB.ptr[i]->daThucHien;
		ifs >> qlMB.ptr[i]->trangThai;
		ifs.ignore();
	}

	ifs.close();
}

void saveDataMB(dsMB& qlMB)
{
	ofstream ofs("maybay.txt");

	ofs << qlMB.count << "\n";

	for (us i = 0; i < qlMB.count; i++)
	{
		ofs << qlMB.ptr[i]->loaiMayBay << "\n" << qlMB.ptr[i]->soHieuMayBay << " " << qlMB.ptr[i]->soCho << " ";
		ofs << qlMB.ptr[i]->daThucHien << " " << qlMB.ptr[i]->trangThai << "\n";
	}

	ofs.close();
}

void loadDataCB(chuyenBay*& head, us& countCB)
{
	us i = 0;
	ifstream ifs("chuyenbay.txt");

	ifs >> countCB;
	
	chuyenBay* ptr = NULL;
	chuyenBay* temp;

	while (i != countCB)
	{
		temp = ptr;
		
		chuyenBay* add = new chuyenBay;
		add->next = NULL;
		
		ifs >> add->maChuyenBay;
		
		ifs >> add->ngayGioBay.ngay;
		ifs >> add->ngayGioBay.thang;
		ifs >> add->ngayGioBay.nam;

		ifs >> add->ngayGioBay.gio;
		ifs >> add->ngayGioBay.phut;
		ifs.ignore();

		getline(ifs,add->sanBayDen);
		
		ifs >> add->trangThai;
		ifs >> add->soCho;

		ifs >> add->soHieuMayBay;

		if (ptr == NULL)
		{
			ptr = add;
			i++;
			continue;
		}
		else
		{
			while (temp->next != NULL) temp = temp->next;
			temp->next = add;
			i++;
		}
	}

	ifs.close();

	head = ptr;
}

void saveDataCB(chuyenBay* head, us& countCB)
{
	ofstream ofs("chuyenbay.txt");
	ofs << countCB << "\n";
	
	while (head != NULL)
	{
		
		ofs << head->maChuyenBay << " ";
		ofs << head->ngayGioBay.ngay << " " << head->ngayGioBay.thang << " " << head->ngayGioBay.nam << " ";
		ofs << head->ngayGioBay.gio << " " << head->ngayGioBay.phut << "\n";

		ofs << head->sanBayDen << "\n";
		ofs << head->trangThai << " " << head->soCho << " ";
		ofs << head->soHieuMayBay << "\n";

		head = head->next;
	}

	ofs.close();
}

void loadDataVeMB(chuyenBay* head)
{
	ifstream ifs("vemaybay.txt");

	us temp;

	while (head != NULL)
	{
		ifs >> head->qlveMB.daDat;

		head->qlveMB.ptr = new veMayBay[head->soCho+1];
		head->gheDaDat = new bool[head->soCho+1];

		for (us i = 1; i <= head->soCho; i++) head->gheDaDat[i] = 0;
		
		for (us i = 1; i <= head->qlveMB.daDat; i++)
		{
			ifs >> temp;
			head->gheDaDat[temp] = 1;
			head->qlveMB.ptr[i].soGhe = temp;
			
			ifs >> head->qlveMB.ptr[i].soCmnd;
			ifs >> head->qlveMB.ptr[i].soThuTu;
		}
		
		here:
		head = head->next;
	}

	ifs.close();
}

void saveDataVeMB(chuyenBay*& ptr)
{
	ofstream ofs("vemaybay.txt");

	chuyenBay* head = ptr;

	while (head != NULL)
	{
		ofs << head->qlveMB.daDat << '\n';

		for (us i = 1; i <= head->qlveMB.daDat; i++)
		{
			ofs << head->qlveMB.ptr[i].soGhe << " ";
			ofs << head->qlveMB.ptr[i].soCmnd << " ";
			ofs << head->qlveMB.ptr[i].soThuTu << "\n";
		}

		here:
		head = head->next;
	}

	ofs.close();
}

void loadDataHK(PTRHK& qlHK, us& countHK)
{
	NodeHK hk;
	us i = 0;

	ifstream ifs("danhsachHK.txt");

	ifs >> countHK;

	while (i != countHK)
	{
		ifs >> hk.ho;
		ifs.ignore();
		getline(ifs, hk.ten);
		ifs >> hk.soCMND;
		ifs >> hk.phai;

		qlHK = InsertNode_HK(qlHK, hk);
		i++;
	}

	ifs.close();
}

void saveDataHK(PTRHK qlHK, us& countHK)
{
	ofstream ofs("danhsachHK.txt");

	PTRHK temp[1000];
	int c = -1;

	ofs << countHK << "\n";

	while (qlHK != NULL)
	{
		ofs << qlHK->data.ho << "\n" << qlHK->data.ten << "\n";
		ofs << qlHK->data.soCMND << " " << qlHK->data.phai << "\n";

		if (qlHK->right != NULL) temp[++c] = qlHK->right;
		
		if (qlHK->left != NULL) qlHK = qlHK->left;
		else if (c == -1) break;
		else qlHK = temp[c--];
	}

	ofs.close();
}
// ==================================================================================================


// khung do hoa cua chuong trinh
void sysBox()
{
	box(15,29,55,4,7,7,"");

	gotoxy(16,30);
	cout << "HE THONG";

	gotoxy(16,32);
	cout << "                                        ";
}

void boxVeTrong(chuyenBay* ptr)
{
	box(15,34,160,12,7,7,"");

	gotoxy(16,35);
	cout << "DANH SACH VE TRONG TREN CHUYEN BAY" << " [" << ptr->maChuyenBay << "]";

	gotoxy(16,37);
	cout << "                                                     ";
	cout << "                                                     ";
	cout << "                                                     ";

	gotoxy(16,39);
	cout << "                                                     ";
	cout << "                                                     ";
	cout << "                                                     ";

	gotoxy(16,41);
	cout << "                                                     ";
	cout << "                                                     ";
	cout << "                                                     ";

	gotoxy(16,43);
	cout << "                                                     ";
	cout << "                                                     ";
	cout << "                                                     ";

	gotoxy(16,45);
	cout << "                                                     ";
	cout << "                                                     ";
	cout << "                                                     ";
}

void boxDSHK(chuyenBay* head)
{
	gotoxy(75,2);
	cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY" << " [" << head->maChuyenBay << "]";
	
	gotoxy(75,3);
	cout << "Ngay gio khoi hanh: ";
	if (head->ngayGioBay.ngay < 10) cout << "0";
	cout << head->ngayGioBay.ngay << "/";
	if (head->ngayGioBay.thang < 10) cout << "0";
	cout << head->ngayGioBay.thang << "/";
	cout << head->ngayGioBay.nam << " ";
	
	if (head->ngayGioBay.gio < 10) cout << "0";
	cout << head->ngayGioBay.gio << ":";
	if (head->ngayGioBay.phut < 10) cout << "0";
	cout << head->ngayGioBay.phut << ".	";

	cout << "Noi den: " << head->sanBayDen;
	
	box(75,5,82,44,7,7,"");

	gotoxy(76,6);
	cout << "STT";

	gotoxy(82,6);
	cout << "So ve";

	gotoxy(90,6);
	cout << "So CMND";

	gotoxy(110,6);
	cout << "Ho ten";

	gotoxy(150,6);
	cout << "Phai";
}

void boxThoiGian()
{
	gotoxy(60,13);
	cout << "yyyy/mm/dd";
	box(49,14,7,2,2,7, "");
	box(58,14,5,2,2,7, "");
	box(65,14,5,2,2,7, "");

	gotoxy(61,20);
	cout << "hh : mm";
	gotoxy(64,18);
	cout << ":";
	box(58,17,5,2,2,7, "");
	box(65,17,5,2,2,7, "");
}

void boxNgayThang()
{
	gotoxy(60,13);
	cout << "yyyy/mm/dd";
	box(49,14,7,2,2,7, "");
	box(58,14,5,2,2,7, "");
	box(65,14,5,2,2,7, "");
}

void boxChuyenBayCoDK(us& ngay, us& thang, us& nam, string& diaDiem)
{
	gotoxy(75,2);
	cout << "DANH SACH CHUYEN BAY KHOI HANH TRONG NGAY ";
	if (ngay < 10) cout << "0";
	cout << ngay << "/";
	if (thang < 10) cout << "0";
	cout << thang << "/";
	cout << nam;

	gotoxy(75,3);
	cout << "Noi den: " << diaDiem;

	box(75,5,47,28,7,7,"");
	
	gotoxy(76,6);
	cout << "Ma CB";

	gotoxy(93,6);
	cout << "Gio khoi hanh";

	gotoxy(110,6);
	cout << "So ve trong";
}

void boxThongKe()
{
	gotoxy(75,35);
	cout << "THONG KE SO LUOT THUC HIEN CHUYEN BAY CUA CAC MAY BAY";
	
	box(75,3,20,30,7,7,"");
	
	box(95,3,10,30,7,7,"");

	gotoxy(76,4);
	cout << "So hieu may bay";

	gotoxy(96,4);
	cout << "So luot";
}

void boxMayBay()
{
	box(75,3,70,30,7,7,"");

	box(75,3,20,30,7,7,"");
	
	box(95,3,40,30,7,7,"");
	
	box(135,3,10,30,7,7,"");

	gotoxy(76,4);
	cout << "So hieu may bay";

	gotoxy(96,4);
	cout << "Loai may bay";

	gotoxy(136,4);
	cout << "So cho";
}

void boxThemChuyenBay()
{
	box(15,2,55,10,7,7,"");

	gotoxy(17,4);
	cout << "Ma CB: ";

	gotoxy(17,6);
	cout << "Ngay gio bay: ";

	gotoxy(45,6); 
	cout << "-";

	gotoxy(17,8);
	cout << "San bay den: ";

	gotoxy(17,10);
	cout << "Ma MB: ";

	box(58,10,12,2,7,7,"");

	gotoxy(60,11);
	cout << "AVAILABLE";
}

void boxChuyenBay()
{
	box(75,2,100,31,7,7,"");
	
	box(75,2,15,31,7,7,"");

	box(116,2,35,31,7,7,"");
	
	box(138,2,25,31,7,7,"");

	gotoxy(76,3);
	cout << "Ma CB";

	gotoxy(91,3);
	cout << "San bay den";

	gotoxy(117, 3);
	cout << "Ngay gio KH";

	gotoxy(139, 3);
	cout << "So hieu MB";

	gotoxy(164,3);
	cout << "Trang thai";
}

void boxHanhKhach()
{
	box(15,2,55,10,7,7,"");
	box(64,14,6,2,7,7,"");

	gotoxy(17,4);
	cout << "Ho: ";

	gotoxy(17,6);
	cout << "Ten: ";

	gotoxy(17,8);
	cout << "CMND / CCCD: ";

	gotoxy(17,10);
	cout << "Gioi tinh: ";

	gotoxy(37,10);
	cout << "Ma CB: ";

	gotoxy(55,15);
	cout << "So ghe";
}

void boxHanhKhachCu()
{
	boxHanhKhach();
	
	box(15,7,55,2,7,7,"");

	gotoxy(17,8);
	cout << "CMND / CCCD: ";
}

void boxTraCuuChuyenBay()
{
	box(15,2,55,4,7,7,"");
	
	gotoxy(16,3);
	cout << "Ngay khoi hanh: ";

	gotoxy(16,5);
	cout << "Dia diem: ";
}

void boxThongBao1()
{
	box(30,14,4,2,7,7,"");
	gotoxy(15,15);
	cout << "Tiep tuc?";

	gotoxy(15,20);
	cout << "[Bam phim (0-9) de TIEP TUC thao tac]";
	gotoxy(15,21);
	cout << "[Bam E de hieu chinh du lieu]";
	gotoxy(15,22);
	cout << "[Bam cac phim khac de THOAT]";
}

void boxThongBao2()
{
	box(30,14,4,2,7,7,"");
	gotoxy(15,15);
	cout << "Xac nhan?";

	gotoxy(15,20);
	cout << "                                       ";
	gotoxy(15,20);
	cout << "[1. YES]";
	gotoxy(15,21);
	cout << "                              ";
	gotoxy(15,21);
	cout << "[2. NO ]";
}

void boxThongBao3()
{
	box(30,14,4,2,7,7,"");
	gotoxy(15,15);
	cout << "Lua chon?";

	gotoxy(15,20);
	cout << "                                  ";
	gotoxy(15,20);
	cout << "[1. Mua ve lan dau]";
	gotoxy(15,21);
	cout << "                              ";
	gotoxy(15,21);
	cout << "[2. Da tung mua ve]";
	gotoxy(15,22);
	cout << "                         ";
	gotoxy(15,22);
	cout << "[0. Ket thuc      ]";
}

void boxThongBao4()
{
	box(30,14,4,2,7,7,"");

	gotoxy(15,22);
	cout << "                                ";

	gotoxy(15,15);
	cout << "Lua chon?";

	gotoxy(15,20);
	cout << "                                      ";
	gotoxy(15,20);
	cout << "[1. Tiep tuc nhap]";
	gotoxy(15,21);
	cout << "                              ";
	gotoxy(15,21);
	cout << "[2. Thoat        ]";	
}

void boxThongBao5()
{
	sysBox();

	gotoxy(16,32);
	cout << "Bam phim bat ky de thoat...";
}

us subBox()
{
	char c;
	
	boxThongBao1();
	
	while (true)
	{
		c = _getch();

		if (c == 101 || c == 69)
		{
			gotoxy(31,15);
			cout << "FIX";
			return 2;
		}
		else if (c >= 48 && c <= 57)
		{
			gotoxy(31,15);
			cout << "YES";
			return 1;
		}
		else
		{
			gotoxy(31,15);
			cout << "ESC";
			return 0;
		}
	}
}

us askBox(us temp)
{
	char c;
	
	if (temp == 1) boxThongBao2();
	else if (temp == 2) boxThongBao4();
	
	while (true)
	{
		c = _getch();

		if (c != 49 && c != 50) continue;

		if (c == 49)
		{
			gotoxy(31,15);
			cout << "YES";
			return 1;
		}
		else if (c == 50)
		{
			gotoxy(31,15);
			cout << "ESC";
			Sleep(471);
			return 2;
		}
	}
}

us buyBox()
{
	char c;

	boxThongBao3();

	while (true)
	{
		c = _getch();

		if (c!= 48 && c != 49 && c != 50) continue;

		if (c == 49)
		{
			gotoxy(31,15);
			cout << "NEW";
			return 1;
		}
		else if (c == 50)
		{
			gotoxy(31,15);
			cout << "BUY";
			return 2;
		}
		else
		{
			gotoxy(31,15);
			cout << "ESC";
			Sleep(471);
			return 0;
		}
	}
}

us exitBox()
{
	char c;

	boxThongBao5();

	c = _getch();

	return 0;
}
// ====================================================================================================


// khac
int isCheckSHMB(dsMB& qlMB, string soHieuMB) 
{
	for (us i = 0; i < qlMB.count; i++) 
	{
		if (qlMB.ptr[i]->soHieuMayBay == soHieuMB) return i;
	}
	return -1;
}

bool isCheckMCB(chuyenBay* head, string maCB)
{
	while (head != NULL)
	{
		if (head->maChuyenBay == maCB) return true;
		head = head->next;
	}
	
	return false;
}

bool isCheckCMND(PTRHK qlHK, string soCMND, NodeHK& fake)
{	
	while (qlHK != NULL)
	{
		if (qlHK->data.soCMND == soCMND)
		{
			fake = qlHK->data;
			return true;
		}
		else if (qlHK->data.soCMND < soCMND) qlHK = qlHK->right;
		else if (qlHK->data.soCMND > soCMND) qlHK = qlHK->left;
	}

	return false;	
}

bool isMaCbAvailable(chuyenBay*& temp, string maCB)
{
	while (temp != NULL)
	{
		if (temp->trangThai == 1 && temp->maChuyenBay == maCB) return true;

		temp = temp->next;
	}

	return false;
}

bool maCbLeft(chuyenBay* temp)
{
	while (temp != NULL)
	{
		if (temp->trangThai == 1) return true;

		temp = temp->next;
	}

	return false;
}

bool maMbLeft(dsMB qlMB)
{
	if (qlMB.count == 0) return false;

	return true;
}

void infoMayBay(mayBay*& print, us& i)
{
	gotoxy(76,6+i*2);
	cout << print->soHieuMayBay;

	gotoxy(96,6+i*2);
	cout <<  print->loaiMayBay;

	gotoxy(136,6+i*2);
	cout << print->soCho;
}

void infoChuyenBay(chuyenBay*& head, us i)
{
	gotoxy(76,5+i*2);
	cout << head->maChuyenBay;

	gotoxy(91,5+i*2);
	cout << head->sanBayDen;

	gotoxy(117,5+i*2);
	if (head->ngayGioBay.ngay < 10) cout << "0";
	cout << head->ngayGioBay.ngay << "/";
	if (head->ngayGioBay.thang < 10) cout << "0";
	cout << head->ngayGioBay.thang << "/";
	cout << head->ngayGioBay.nam << " - ";
	
	if (head->ngayGioBay.gio < 10) cout << "0";
	cout << head->ngayGioBay.gio << ":";
	if (head->ngayGioBay.phut < 10) cout << "0";
	cout << head->ngayGioBay.phut;

	gotoxy(139,5+i*2);
	cout << head->soHieuMayBay;

	gotoxy(164,5+i*2);
	if (head->trangThai == 0) cout << "HUY CHUYEN";
	else if (head->trangThai == 1) cout << "CON VE";
	else if (head->trangThai == 2) cout << "HET VE";
	else cout << "HOAN THANH";
}

void infoChuyenBayCoDK(chuyenBay*& head, us i)
{
	gotoxy(76,8+i*2);
	cout << head->maChuyenBay;

	gotoxy(93,8+i*2);
	if (head->ngayGioBay.gio < 10) cout << "0";
	cout << head->ngayGioBay.gio << ":";
	if (head->ngayGioBay.phut < 10) cout << "0";
	cout << head->ngayGioBay.phut;

	gotoxy(110,8+i*2);
	cout << head->soCho - head->qlveMB.daDat;
}

void infoLuotThucHien(mayBay*& print, us& i)
{
	
	gotoxy(76,6+i*2);
	cout << print->soHieuMayBay;

	gotoxy(96,6+i*2);
	cout << print->daThucHien;
}

void infoVeMB(chuyenBay*& ptr, NodeHK& hk, us i)
{	
	us temp;
	
	gotoxy(76,6+i*2);
	cout << i;

	for (us j = 1; j <= ptr->qlveMB.daDat; j++)
	{
		if (hk.soCMND == ptr->qlveMB.ptr[j].soCmnd)
		{
			temp = ptr->qlveMB.ptr[j].soGhe;
			break;
		}
	}
	gotoxy(82,6+i*2);
	if (temp < 10) cout << "00";
	else if (temp < 100) cout << "0";
	cout << temp;

	gotoxy(90,6+i*2);
	cout << hk.soCMND;

	gotoxy(110,6+i*2);
	cout << hk.ho << " " << hk.ten;

	gotoxy(150,6+i*2);
	if (hk.phai == 1) cout << "Nam";
	else cout << "Nu";
}
// ==================================================================================================


// ho tro nguoi dung
void duLieuSanBay(string*& DSSB)
{
	DSSB[0] = "Noi Bai - Tp.Ha Noi";
	DSSB[1] = "Dien Bien Phu - Dien Bien";
	DSSB[2] = "Cat Bi - Hai Phong";
	DSSB[3] = "Van Don - Quang Ninh";
	DSSB[4] = "Tho Xuan - Thanh Hoa";
	DSSB[5] = "Vinh - Nghe An";
	DSSB[6] = "Dong Hoi - Quang Binh";
	DSSB[7] = "Phu Bai - Thua Thien Hue";
	DSSB[8] = "Chu Lai - Quang Nam";
	DSSB[9] = "Da Nang - Tp.Da Nang";
	DSSB[10] = "Phu Cat - Binh Dinh";
	DSSB[11] = "Tuy Hoa - Phu Yen";
	DSSB[12] = "Pleiku - Gia Lai";
	DSSB[13] = "Buon Ma Thuot - Dak Lak";
	DSSB[14] = "Lien Khuong - Lam Dong";
	DSSB[15] = "Cam Ranh - Khanh Hoa";
	DSSB[16] = "Con Dao - Ba Ria Vung Tau";
	DSSB[17] = "Tan Son Nhat - Tp.HCM";
	DSSB[18] = "Can Tho - Tp.Can Tho";
	DSSB[19] = "Rach Gia - Kien Giang";
	DSSB[20] = "Phu Quoc - Kien Giang";
	DSSB[21] = "Ca Mau - Ca Mau";
}

void traCuuSanBay(string*& DSSB)
{
	box(75,2,62,31,7,7,"");

	gotoxy(76,3);
	cout << "DANH SACH SAN BAY";

	for (us i = 0; i < 11; i++)
	{
		gotoxy(76,5+i*2);
		cout << i*2+1 << ". " << DSSB[i*2];

		gotoxy(107,5+i*2);
		cout << i*2+2 << ". " << DSSB[i*2+1];
	}
}

void traCuuMayBay(dsMB& qlMB, chuyenBay* head, us& ngay, us& thang, us& nam)
{	
	us line = 0;
	
	box(75,2,70,31,7,7,"");
	
	box(75,2,40,31,7,7,"");

	box(115,2,20,31,7,7,"");
	
	box(135,2,10,31,7,7,"");

	gotoxy(76,3);
	cout << "Loai may bay";

	gotoxy(116,3);
	cout << "So hieu may bay";

	gotoxy(136,3);
	cout << "So cho";
	
	for (us i = 0; i < qlMB.count; i++)
	{
		while (head != NULL)
		{
			if (qlMB.ptr[i]->soHieuMayBay == head->soHieuMayBay)
			{
				if ((head->ngayGioBay.ngay == ngay) && (head->ngayGioBay.thang == thang) && (head->ngayGioBay.nam == nam))
				{
					if (head->trangThai == 1 || head->trangThai == 2) goto here;
				}
			}
				
			head = head->next;
		}
		
		infoMayBay(qlMB.ptr[i], line);
		line++;

		here:
		line += 0;
	}
}

void traCuuChuyenBay(chuyenBay* head)
{
	us i = 0;

	boxChuyenBay();

	while (head != NULL)
	{
		if (head->trangThai == 1)
		{
			infoChuyenBay(head, i);
			i++;
		}

		head = head->next;
	}
}
// ===================================================================================================


// ba ham nhap du lieu (co the toi gian thanh 1 ham giong nhu nameInput() bang cach them tham so 'type')
string limitedInput(us x, us y, us lim)
{
	string text;
	char c;

	while (true)
	{
		c = _getch();

        if (c == 13) break;

		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= 48 && c <= 57) || c == 8 || c == 32) goto here;
		else continue;

		here:
        if (text.length() == lim) if (c != 8) continue;

        if (text.length() == 0) if ((c == 8) || (c == 32)) continue;
		
		if (c == 8)
		{
			x-=1;
            gotoxy(x,y);
            cout << " ";
            gotoxy(x,y);
			text.erase(text.length()-1,1);
			continue;
		}
		else
		{
			
			if (c == 32 && text[text.length()-1] == 32) goto pos;
			
			cout << c;
			text.push_back(c);
			x++;
		}

		pos:
		if (text[0] == 32) text.erase(0,1);
	}

	if (text[text.length()-1] == 32) text.erase(text.length()-1,1);
	
	return text;
}

string nameInput(us x, us y, us lim, us type)
{
	string text;
	char c;

	while (true)
	{
		c = _getch();

        if (c == 13) break;

		if (type == 2)
		{
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= 48 && c <= 57) || c == 8 || c == '_') goto here;
			else continue;
		}
		else if (type == 1)
		{
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == 8 || c == 32) goto here;
			else continue;
		}
		else if (type == 0)
		{
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == 8) goto here;
			else continue;
		}

		here:
        if (text.length() == lim) if (c != 8) continue;

        if (text.length() == 0) if ((c == 8) || (c == 32)) continue;
		
		if (c == 8)
		{
			x-=1;
            gotoxy(x,y);
            cout << " ";
            gotoxy(x,y);
			text.erase(text.length()-1,1);
			continue;
		}
		else
		{
			if(text.length() != 0)
				if ((c == 32 && text[text.length()-1] == 32) || (c == '_') && text[text.length()-1] == '_') goto pos;
			
			cout << c;
			text.push_back(c);
			x++;
		}

		pos:
		if (text[0] == 32) text.erase(0,1);
	}

	if (text[text.length()-1] == 32) text.erase(text.length()-1,1);
	
	return text;
}

string numInput(us x, us y, us lim)
{
	string text;
	char c;

	while (true)
	{
		c = _getch();

        if (c == 13) break;

		if ((c >= 48 && c <= 57) || c == 8) goto here;
		else continue;

		here:
        if (text.length() == lim) if (c != 8) continue;

        if (text.length() == 0) if (c == 8) continue;
		
		if (c == 8)
		{
			x-=1;
            gotoxy(x,y);
            cout << " ";
            gotoxy(x,y);
			text.erase(text.length()-1,1);
		}
		else
		{
			cout << c;
			text.push_back(c);
			x++;
		}
	}

	return text;
}
// =====================================================================================================


// xy ly chuoi
void correctName(string& text)
{
	for (us i = 0; i < text.length(); i++) if (text[i] >= 65 && text[i] <= 90) text[i] += 32;

	if (text[0] >= 97 && text[0] <= 122) text[0] -= 32;

	for (us i = 1; i < text.length()-1; i++)
	{
		if (text[i] == 32 && text[i+1] != 32)
		{
			if (text[i+1] >= 97 && text[i+1] <= 122) text[i+1] -= 32;
		}	
	}
}

void inHoa(string& text)
{
	for (us i = 0; i < text.length(); i++)
	{
		if (text[i] >= 97 && text[i] <= 122) text[i] -= 32;
	}
}

bool kyTuRong(string& str)
{
	if (str.length() == 0) goto here;

	for (us i = 0; i < str.length(); i++)
	{
		if (str[i] != 32) return false;
	}

	here:
	gotoxy(16,32);
	cout << "Khong duoc bo trong!";

	return true;
}
// =====================================================================================================


// xy ly cau a
int timMayBay(dsMB& qlMB)
{
	string text;
	int temp;

	sysBox();

	box(15,3,55,2,7,7,"");

	gotoxy(16,4);
	cout << "Nhap so hieu may bay: ";

	text = nameInput(38,4,15,2);

	inHoa(text);

	temp = isCheckSHMB(qlMB, text);

	if (temp == -1)
	{
		sysBox();
		gotoxy(16,32);
		cout << "SO HIEU MAY BAY VUA NHAP KHONG TON TAI!";
	}
	else
	{
		sysBox();
		gotoxy(16,32);
		cout << "Dang HIEU CHINH chuyen bay so hieu [" << qlMB.ptr[temp]->soHieuMayBay << "]";
	}

	return temp;
}

bool xoaMayBay(dsMB& qlMB, chuyenBay* head)
{
	int temp;

	temp = timMayBay(qlMB);

	if (temp == -1) return false;

	while (head != NULL) //neu co CHUYEN BAY dang su dung -> khong cho XOA
	{
		if (head->soHieuMayBay == qlMB.ptr[temp]->soHieuMayBay)
		{
			if (head->trangThai == 1 || head->trangThai == 2)
			{
				gotoxy(16,32);
				cout << "Chuyen bay " << head->maChuyenBay << " dang SU DUNG may bay nay!";
				return false;
			}
		}

		head = head->next;
	}

	if (askBox(1) == 1)
	{
		for (us i = temp; i < qlMB.count-1; i++) qlMB.ptr[i] = qlMB.ptr[i+1];

		qlMB.count -= 1;
	}
	else
	{
		sysBox();
		gotoxy(16,32);
		cout << "HUY BO thao tac!";

		return false;
	}

	return true;
}

bool editMayBay(dsMB& qlMB, chuyenBay*& head)
{	
	chuyenBay* ptr = head;
	veMayBay* ptrVE;
	
	us temp;
	bool *duLieuGhe;
	
	string text;
	int t1;
	int t2;

	sysBox();

	box(15,3,55,8,7,7,"");

	t1 = timMayBay(qlMB);

	if (t1 == -1) return false;

	//loai may bay--------------------------------------//
	box(15,3,55,2,7,7,"");
	
	gotoxy(17,4);
	cout << "Loai MB: ";
	
	gotoxy(26,4);
	text = limitedInput(26,4,40);
	
	if (text.length() != 0)
	{
		qlMB.ptr[t1]->loaiMayBay = text;
		
		gotoxy(96,6+t1*2);
		cout << "                            ";
		
		gotoxy(96,6+t1*2);
		cout << qlMB.ptr[t1]->loaiMayBay;
	}

	//so hieu may bay------------------------------------//
	box(15,3,55,2,7,7,"");
	
	gotoxy(17,4);
	cout << "So hieu MB: ";
	
	there:
	gotoxy(29,4);
	text = nameInput(29,4,15,2);

	inHoa(text);

	if (text.length() != 0)
	{
		if (isCheckSHMB(qlMB, text) != -1)
		{
			gotoxy(16,32);
			cout << "So hieu MB vua nhap da TON TAI";

			gotoxy(29,4);
			cout << "               ";

			goto there;
		}

		while (ptr != NULL) //cap nhat lai soHieuMayBay ben ChuyenBay
		{
			if (ptr->soHieuMayBay == qlMB.ptr[t1]->soHieuMayBay) ptr->soHieuMayBay = text;
			ptr = ptr->next;
		}

		qlMB.ptr[t1]->soHieuMayBay = text;

		gotoxy(76,6+t1*2);
		cout << "               ";

		gotoxy(76,6+t1*2);
		cout << qlMB.ptr[t1]->soHieuMayBay;
	}

	sysBox();

	//so cho---------------------------------------------//
	box(15,3,55,2,7,7,"");
	
	gotoxy(17,4);
	cout << "So cho: ";

	here:
	gotoxy(25,4);
	text = numInput(25,4,5);
	if (text.length() != 0)
	{
		stringstream ss(text);
		ss >> t2;

		if (t2 < 20)
		{
			sysBox();
			
			gotoxy(16,32);
			cout << "So cho phai >= 20";

			gotoxy(25,4);
			cout << "     ";

			goto here;
		}

		while (ptr != NULL)
		{
			if (ptr->soHieuMayBay == qlMB.ptr[t1]->soHieuMayBay)
			{
				if (ptr->soCho >= t2)
				{
					sysBox();
					
					if (ptr->qlveMB.daDat != 0)
					{
						gotoxy(16,32);
						cout << "Da co " << ptr->qlveMB.daDat << " nguoi da dat cho!";

						Sleep(1250);
						sysBox();

						gotoxy(16,32);
						cout << "So cho PHAI > So cho ban dau!";

						gotoxy(25,4);
						cout << "    ";

						goto here;
					}
					else ptr->soCho = t2;
				}
				else if (ptr->soCho < t2)
				{
					temp = ptr->soCho;

					ptr->soCho = t2;
					
					ptrVE = new veMayBay[temp+1];
					duLieuGhe = new bool[temp+1];

					for (us i = 1; i <= temp; i++) duLieuGhe[i] = 0;
					for (us i = 1; i <= temp; i++) if (ptr->gheDaDat[i] == 1) duLieuGhe[i] = 1;

					for (us i = 1; i <= ptr->qlveMB.daDat; i++)
					{
						ptrVE[i].soGhe = ptr->qlveMB.ptr[i].soGhe;
						ptrVE[i].soCmnd = ptr->qlveMB.ptr[i].soCmnd;
					}

					delete[]ptr->qlveMB.ptr;
					delete[]ptr->gheDaDat;

					ptr->qlveMB.ptr = new veMayBay[t2+1];
					ptr->gheDaDat = new bool[t2+1];

					for (us i = 1; i <= t2; i++)
					{
						if (i <= ptr->qlveMB.daDat)
						{
							ptr->qlveMB.ptr[i].soGhe = ptrVE[i].soGhe;
							ptr->qlveMB.ptr[i].soCmnd = ptrVE[i].soCmnd;
						}

						ptr->qlveMB.ptr[i].soThuTu = i;
					}

					for (us i = 1; i <= t2; i++)
					{
						if (i <= temp) ptr->gheDaDat[i] = duLieuGhe[i];
						else ptr->gheDaDat[i] = 0;
					}

					delete[]ptrVE;
					delete[]duLieuGhe;
				}
			}

			ptr = ptr->next;
		}

		qlMB.ptr[t1]->soCho = t2;

		gotoxy(136,6+t1*2);
		cout << "       ";

		gotoxy(136,6+t1*2);
		cout << qlMB.ptr[t1]->soCho;
	}

	sysBox();
	gotoxy(16,32);
	cout << "Hoan thanh viec HIEU CHINH";

	return true;
}

void nhapMayBay(mayBay*& add, dsMB& qlMB)
{
	int temp;
	string text;

	add->trangThai = 0;
	add->daThucHien = 0;
	
	//loai may bay----------------------------------//
	there1:
	gotoxy(26,5);
	text = limitedInput(26,5,40);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(26,5);
		cout << "                                           ";

		goto there1;
	}

	add->loaiMayBay = text;

	//so hieu may bay-------------------------------//	
	there:
	gotoxy(29,7);
	text = nameInput(29,7,15,2);

	inHoa(text);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(29,7);
		cout << "              ";

		goto there;
	}
	
	if (isCheckSHMB(qlMB, text) != -1)
	{
		gotoxy(16,32);
		cout << "So hieu MB vua nhap da TON TAI";

		gotoxy(29,7);
		cout << "               ";

		goto there;
	}

	add->soHieuMayBay = text;

	//so cho----------------------------------------//
	here:
	gotoxy(25,9);
	text = numInput(25,9,4);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(25,9);
		cout << "    ";

		goto here;
	}

	stringstream ss(text);
	ss >> temp;

	if (temp < 20 || temp > 300)
	{
		gotoxy(16,32);
		cout << "20 <= So cho <= 300";

		gotoxy(25,9);
		cout << "     ";

		goto here;
	}

	add->soCho = temp;

	sysBox();
}

void themMayBay(dsMB& qlMB)
{
	sysBox();
	
	box(15,3,55,8,7,7,"");

	gotoxy(17,5);
	cout << "Loai MB: ";

	gotoxy(17,7);
	cout << "So hieu MB: ";

	gotoxy(17,9);
	cout << "So cho: ";
	
	qlMB.ptr[qlMB.count] = new mayBay;

	nhapMayBay(qlMB.ptr[qlMB.count], qlMB);

	qlMB.count++;
}

void inMayBay(dsMB& qlMB)
{
	boxMayBay();

	for (us i = 0; i < qlMB.count; i++)
		infoMayBay(qlMB.ptr[i], i); 
}
// =====================================================================================================


// cau a
void chucNang1_0(dsMB& qlMB, chuyenBay*& head)
{
	system("cls");
	system("color 7");

	if (maMbLeft(qlMB) == false)
	{
		sysBox();

		gotoxy(16,32);
		cout << "KHONG CO may bay nao duoc khoi tao!";

		Sleep(1500);

		return;
	}
	
	int temp;

	inMayBay(qlMB);

	while (true)
	{
		temp = askBox(2);

		if (temp == 2) break;
		
		editMayBay(qlMB, head);
	}
}

void chucNang1_1(dsMB& qlMB, chuyenBay*& head)
{
	us temp;
	
	system("cls");
	system("color 7");

	inMayBay(qlMB);

	here:
	while (true)	
	{										
		temp = subBox();

		if (temp == 2)
		{
			editMayBay(qlMB, head);
			continue;
		}
		else if (temp == 0) break;
		
		themMayBay(qlMB);

		temp = qlMB.count-1;

		infoMayBay(qlMB.ptr[temp], temp);
	}
	
	Sleep(1000);
}

void chucNang1_2(dsMB& qlMB, chuyenBay*& head)
{
	system("cls");
	system("color 7");
	
	if (maMbLeft(qlMB) == false)
	{
		sysBox();

		gotoxy(16,32);
		cout << "KHONG CO may bay nao duoc khoi tao!";

		Sleep(1500);

		return;
	}
	
	us temp;

	inMayBay(qlMB);

	while (true)
	{
		if (qlMB.count == 0)
		{
			sysBox();
			gotoxy(16,32);
			cout << "DANH SACH MAY BAY DANG RONG!";

			Sleep(1400);

			return;
		}

		if (askBox(2) == 2) return;
		
		if (xoaMayBay(qlMB, head) == true) inMayBay(qlMB);
	}
}
// ======================================================================================================


// xu ly cau b
bool leafYear(us num)
{
	if (num % 400 == 0) return true;

	if (num % 4 == 0 && num % 100 != 0) return true;

	return false; 
}

bool isAvailable(chuyenBay* head, string maMB, us ngay, us thang, us nam)
{
	while (head != NULL)
	{
		if (head->soHieuMayBay == maMB)
		{
			if (head->trangThai == 1 || head->trangThai == 2 || head->trangThai == 3)
			{
				if (head->ngayGioBay.nam != nam) goto here;
				else if (head->ngayGioBay.thang != thang) goto here;
				else if (head->ngayGioBay.ngay != ngay) goto here;
				else return false;
			}
		}

		here:
		head = head->next;
	}

	return true;
}

void inChuyenBay(chuyenBay* head)
{
	us i = 0;

	boxChuyenBay();
	
	while (head != NULL)
	{
		infoChuyenBay(head,i);
		head = head->next;
		i++;
	}
}

bool nhapChuyenBay(chuyenBay*& head, dsMB& qlMB, string*& DSSB)
{
	if (qlMB.count == 0)
	{
		gotoxy(16,32);
		cout << "KHONG co bat cu may bay nao trong danh sach!";
		return false;
	}
	
	us temp;
	string text;
	bool lYear;
	chuyenBay* ptr = head;
	
	chuyenBay* add = new chuyenBay;
	add->next = NULL;

	add->trangThai = 1;

	//xy ly ma chuyen bay--------------------------------------------//
	p0:
	gotoxy(24,4);
	text = nameInput(24,4,15,2);

	inHoa(text);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(24,4);
		cout << "                 ";

		goto p0;
	}

	if (isCheckMCB(head, text) == true)
	{
		gotoxy(16,32);
		cout << "Ma CB vua nhap da TON TAI!";

		gotoxy(24,4);
		cout << "                      ";

		goto p0;
	}

	add->maChuyenBay = text;

	//ngay thang nam----------------------------------------xu ly nam//
	p1:
	gotoxy(50,15);
	text = numInput(50,15,4);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(50,15);
		cout << "    ";

		goto p1;
	}

	stringstream ss(text);
	ss >> temp;

	if (temp <= 2021)
	{
		gotoxy(16,32);
		cout << "Khong quan ly cac chuyen bay truoc nam 2022";

		gotoxy(50,15);
		cout << "     ";

		goto p1;
	}
	
	add->ngayGioBay.nam = temp;

	lYear = leafYear(temp);
	gotoxy(50,15);
	cout << "     ";
	gotoxy(51,15);
	cout << temp;

	//ngay thang nam-----------------------------------------xu ly thang//
	p2:
	gotoxy(59,15);
	text = numInput(59,15,2);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(59,15);
		cout << "  ";

		goto p2;
	}
	
	stringstream ss1(text);
	ss1 >> temp;

	if (temp == 0 || temp >= 13)
	{
		gotoxy(16,32);
		cout << "Khong co thang " << temp;

		gotoxy(59,15);
		cout << "  ";

		goto p2;
	}

	if (add->ngayGioBay.nam == 2022 && temp < 5)
	{
		gotoxy(16,32);
		cout << "Khong quan ly cac chuyen bay truoc thang 5";

		gotoxy(59,15);
		cout << "  ";

		goto p2;
	}

	add->ngayGioBay.thang = temp;

	gotoxy(59,15);
	cout << "  ";
	gotoxy(60,15);
	if (temp < 10) cout << "0";
	cout << temp;

	//ngay thang nam--------------------------------------------xu ly ngay//
	p3:
	gotoxy(66,15);
	text = numInput(66,15,2);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(66,15);
		cout << "  ";

		goto p3;
	}

	stringstream ss2(text);
	ss2 >> temp;

	sysBox();

	if (temp == 0)
	{
		gotoxy(16,32);
		cout << "Khong co ngay thu 0";
		gotoxy(66,15);
		cout << "   ";

		goto p3;
	}
	else if (temp >= 32)
	{
		gotoxy(16,32);
		cout << "Mot thang khong the co hon 31 ngay!";
		gotoxy(66,15);
		cout << "   ";

		goto p3;
	}
	else if (add->ngayGioBay.thang == 4 || add->ngayGioBay.thang == 6 || add->ngayGioBay.thang == 9 || add->ngayGioBay.thang == 11)
	{
		if (temp == 31)
		{
			gotoxy(16,32);
			cout << "Thang " << add->ngayGioBay.thang << " chi co 30 ngay! (Goi y: 1 -> 30)";
			gotoxy(66,15);
			cout << "   ";

			goto p3;
		}
	}
	else if (add->ngayGioBay.thang == 2)
	{
		if (lYear == false)
		{
			if (temp >= 29)
			{
				gotoxy(16,32);
				cout << "Thang 2 chi co 28 ngay!";
				gotoxy(66,15);
				cout << "   ";

				goto p3;
			} 
		}
		else
		{
			if (temp >= 30)
			{
				gotoxy(16,32);
				cout << "Thang 2 chi co 29 ngay!";
				gotoxy(66,15);
				cout << "   ";

				goto p3;
			} 
		}
	}

	if (add->ngayGioBay.nam == 2022 && add->ngayGioBay.thang == 5 && temp < 31)
	{
		gotoxy(16,32);
		cout << "Khong quan ly chuyen bay truoc ngay 31/05/2022";
		
		gotoxy(66,15);
		cout << "   ";

		goto p3;		 
	}

	add->ngayGioBay.ngay = temp;

	gotoxy(66,15);
	cout << "   ";
	gotoxy(67,15);
	if (temp < 10) cout << "0";
	cout << temp;

	//ghi lai ngay thang nam vao khung--------------------------------------//
	gotoxy(31,6);
	if (add->ngayGioBay.ngay < 10) cout << "0";
	cout << add->ngayGioBay.ngay << "/";
	if (add->ngayGioBay.thang < 10) cout << "0";
	cout << add->ngayGioBay.thang << "/";
	cout << add->ngayGioBay.nam;

	//xu ly thoi gian---------------------------------------------------gio//
	p4:
	gotoxy(59,18);
	text = numInput(59,18,2);

	sysBox();
	
	if (kyTuRong(text) == true)
	{
		gotoxy(59,18);
		cout << "  ";

		goto p4;
	}

	stringstream ss3(text);
	ss3 >> temp;

	if (temp >= 24)
	{
		gotoxy(16,32);
		cout << "Sai dinh dang gio! (Goi y: 0 -> 23)";

		gotoxy(59,18);
		cout << "  ";

		goto p4;
	}

	add->ngayGioBay.gio = temp;

	gotoxy(59,18);
	cout << "  ";
	gotoxy(60,18);
	if (temp < 10) cout << "0";
	cout << temp;

	//xu ly thoi gian--------------------------------------------------phut//
	p5:
	gotoxy(66,18);
	text = numInput(66,18,2);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(66,18);
		cout << "  ";

		goto p5;
	}

	stringstream ss4(text);
	ss4 >> temp;

	if (temp >= 60)
	{
		gotoxy(16,32);
		cout << "Sai dinh dang phut! (Goi y: 0 -> 59)";

		gotoxy(66,18);
		cout << "  ";

		goto p5;
	}

	add->ngayGioBay.phut = temp;
	sysBox();

	gotoxy(66,18);
	cout << "   ";
	gotoxy(67,18);
	if (temp < 10) cout << "0";
	cout << temp;

	sysBox();
	
	//ghi lai thoi gian vao khung------------------------------------------//
	gotoxy(51,6);
	if (add->ngayGioBay.gio < 10) cout << "0";
	cout << add->ngayGioBay.gio << " : ";
	if (add->ngayGioBay.phut < 10) cout << "0";
	cout << add->ngayGioBay.phut;

	//san bay den----------------------------------------------------------//
	//---------------------------------------------------------------------//
	traCuuSanBay(DSSB);
	p6:
	gotoxy(30,8);
	text = numInput(30,8,2);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(30,8);
		cout << "  ";

		goto p6;
	}

	stringstream ss5(text);
	ss5 >> temp;

	if (temp == 0 || temp >= 23)
	{
		gotoxy(16,32);
		cout << "Khong co trong danh sach!";

		gotoxy(30,8);
		cout << "   ";

		goto p6;
	}

	gotoxy(30,8);
	cout << DSSB[temp-1];

	inChuyenBay(head);

	add->sanBayDen = DSSB[temp-1];
	
	//so hieu may bay------------------------------------------------------//
	box(75,2,100,31,7,7,"");
	traCuuMayBay(qlMB, head, add->ngayGioBay.ngay, add->ngayGioBay.thang, add->ngayGioBay.nam);
	p7:
	gotoxy(24,10);
	text = nameInput(24,10,15,2);

	inHoa(text);

	sysBox();

	if (kyTuRong(text) == true)	
	{
		gotoxy(24,10);
		cout << "                 ";

		goto p7;
	}

	if (isCheckSHMB(qlMB, text) == -1)
	{
		gotoxy(16,32);
		cout << "Ma MB vua nhap khong TON TAI";


		if (askBox(2) == 2)
		{
			sysBox();

			gotoxy(16,32);
			cout << "Chuyen bay vua nhap se KHONG duoc luu lai!";

			inChuyenBay(head);

			return false;
		}

		gotoxy(24,10);
		cout << "                  ";

		goto p7;
	}

	if (isAvailable(head, text, add->ngayGioBay.ngay, add->ngayGioBay.thang, add->ngayGioBay.nam) == false)
	{		
		gotoxy(16,32);
		cout << "Khong the su dung may bay so hieu " << text;

		temp = subBox();
		if (temp == 0)
		{
			gotoxy(16,32);
			cout << "                                    ";
			gotoxy(16,32);
			cout << "Chuyen bay vua nhap se KHONG duoc luu lai!";
			inChuyenBay(head);
			return false;
		}

		gotoxy(24,10);
		cout << "                 ";

		goto p7;
	}

	inChuyenBay(head);
	temp = isCheckSHMB(qlMB,text);

	add->soHieuMayBay = text;
	
	qlMB.ptr[temp]->trangThai = 1;

	//khoi tao danh sach ve may bay-------------------------------------------------//
	add->soCho = qlMB.ptr[isCheckSHMB(qlMB,text)]->soCho;
	temp = add->soCho;
	
	add->qlveMB.ptr = new veMayBay[temp+1];

	add->gheDaDat = new bool[temp+1];
	
	add->qlveMB.daDat = 0;

	for (us i = 1; i <= temp; i++)
	{
		add->qlveMB.ptr[i].soThuTu = i;
		add->gheDaDat[i] = 0;
	}

	gotoxy(16,32);
	cout << "DANH SACH VE da duoc khoi tao tu dong!";

	//noi cac node voi nhau--------------------------------------------------------//

	if (head == NULL)
	{
		head = add;
		return true;
	}

	while (ptr->next != NULL) ptr = ptr->next;
	ptr->next = add;

	return true;
}

bool themChuyenBay(chuyenBay*& head, dsMB& qlMB, string*& DSSB)
{
	sysBox();
	
	boxThemChuyenBay();

	boxThoiGian();

	if (nhapChuyenBay(head,qlMB,DSSB) == true) return true;
	
	return false;
}

void addON(chuyenBay* head, us i)
{
	while (head->next != NULL) head = head->next;
	
	gotoxy(76,5+i*2);
	cout << head->maChuyenBay;

	gotoxy(91,5+i*2);
	cout << head->sanBayDen;

	gotoxy(117,5+i*2);
	if (head->ngayGioBay.ngay < 10) cout << "0";
	cout << head->ngayGioBay.ngay << "/";
	if (head->ngayGioBay.thang < 10) cout << "0";
	cout << head->ngayGioBay.thang << "/";
	cout << head->ngayGioBay.nam << " - ";
	
	if (head->ngayGioBay.gio < 10) cout << "0";
	cout << head->ngayGioBay.gio << ":";
	if (head->ngayGioBay.phut < 10) cout << "0";
	cout << head->ngayGioBay.phut;

	gotoxy(139,5+i*2);
	cout << head->soHieuMayBay;

	gotoxy(164,5+i*2);
	if (head->trangThai == 0) cout << "HUY CHUYEN";
	else if (head->trangThai == 1) cout << "CON VE";
	else if (head->trangThai == 2) cout << "HET VE";
	else cout << "HOAN THANH";
}

void xoaBoNhoChuyenBay(chuyenBay*& head)
{
	chuyenBay* ptr = head;

	while (head != NULL)
	{
		ptr = head;

		head = head->next;
		
		delete ptr;
	}
}

bool timChuyenBay(chuyenBay*& add, us& i)
{
	string text;

	sysBox();

	box(15,2,55,2,7,7,"");

	gotoxy(16,3);
	cout << "Nhap ma chuyen bay: ";

	gotoxy(36,3);
	text = nameInput(36,3,15,2);

	inHoa(text);

	while (add != NULL)
	{
		if (add->maChuyenBay == text)
		{
			if (add->trangThai == 0 || add->trangThai == 3)
			{
				sysBox();
				gotoxy(16,32);
				cout << "KHONG the hieu chinh chuyen bay CO trang thai HT/HC!";
				Sleep(471);

				return false;
			}
			else return true;
		}
		
		
		add = add->next;
		i++;
	}

	gotoxy(16,32);
	cout << "MA CHUYEN BAY VUA NHAP KHONG TON TAI!";

	return false;
}

void editChuyenBay(chuyenBay*& head, dsMB& qlMB)
{	
	us temp;
	us i = 0;
	us d,m,y;
	bool find;
	bool lYear;
	string text;

	chuyenBay* add = head;

	sysBox();
	box(15,2,55,10,7,7,"");

	boxThoiGian();

	if (timChuyenBay(add,i) == false) return;

	box(15,2,55,2,7,7,"");
	gotoxy(16,3);
	cout << "Ngay gio bay: ";

	top:
	boxThoiGian();
	
	//ngay thang nam----------------------------------------xu ly nam//
	p1:
	gotoxy(50,15);
	text = numInput(50,15,4);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(16,32);
		cout << "                      ";
		
		gotoxy(51,15);
		
		cout << "xxxx";

		y = add->ngayGioBay.nam;

		goto p2;
	}
	else
	{
		stringstream ss(text);
		ss >> temp;

		if (temp <= 2021)
		{
			gotoxy(16,32);
			cout << "Khong quan ly cac chuyen bay truoc nam 2022";

			gotoxy(50,15);
			cout << "     ";

			goto p1;
		}
		
		y = temp;

		lYear = leafYear(temp);
		gotoxy(50,15);
		cout << "     ";
		gotoxy(51,15);
		cout << temp;
	}

	//ngay thang nam-----------------------------------------xu ly thang//
	p2:
	gotoxy(59,15);
	text = numInput(59,15,2);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(16,32);
		cout << "                      ";
		
		gotoxy(60,15);
		
		cout << "xx";

		m = add->ngayGioBay.thang;

		goto p3;
	}
	else
	{
		stringstream ss1(text);
		ss1 >> temp;

		if (temp == 0 || temp >= 13)
		{
			gotoxy(16,32);
			cout << "Khong co thang " << temp;

			gotoxy(59,15);
			cout << "  ";

			goto p2;
		}

		if (add->ngayGioBay.nam == 2022 && temp < 5)
		{
			gotoxy(16,32);
			cout << "Khong quan ly cac chuyen bay truoc thang 5";

			gotoxy(59,15);
			cout << "  ";

			goto p2;
		}

		m = temp;

		gotoxy(59,15);
		cout << "  ";
		gotoxy(60,15);
		if (temp < 10) cout << "0";
		cout << temp;	
	}
	
	//ngay thang nam--------------------------------------------xu ly ngay//
	p3:
	gotoxy(66,15);
	text = numInput(66,15,2);

	sysBox();

	if (kyTuRong(text) == true)
	{
		here1:
		gotoxy(16,32);
		cout << "                      ";
		
		gotoxy(67,15);
		cout << "xx";

		d = add->ngayGioBay.ngay;

		goto check;
	}
	else
	{		
		stringstream ss2(text);
		ss2 >> temp;

		if (temp == add->ngayGioBay.ngay)
		{
			gotoxy(66,15);
			cout << "  ";

			goto here1;
		}

		sysBox();

		if (temp == 0)
		{
			gotoxy(16,32);
			cout << "Khong co ngay thu 0";
			gotoxy(66,15);
			cout << "   ";

			goto p3;
		}
		else if (temp >= 32)
		{
			gotoxy(16,32);
			cout << "Mot thang khong the co hon 31 ngay!";
			gotoxy(66,15);
			cout << "   ";

			goto p3;
		}
		else if (add->ngayGioBay.thang == 4 || add->ngayGioBay.thang == 6 || add->ngayGioBay.thang == 9 || add->ngayGioBay.thang == 11)
		{
			if (temp == 31)
			{
				gotoxy(16,32);
				cout << "Thang " << add->ngayGioBay.thang << " chi co 30 ngay! (Goi y: 1 -> 30)";
				gotoxy(66,15);
				cout << "   ";

				goto p3;
			}
		}
		else if (add->ngayGioBay.thang == 2)
		{
			if (lYear == false)
			{
				if (temp >= 29)
				{
					gotoxy(16,32);
					cout << "Thang 2 chi co 28 ngay!";
					gotoxy(66,15);
					cout << "   ";

					goto p3;
				} 
			}
			else
			{
				if (temp >= 30)
				{
					gotoxy(16,32);
					cout << "Thang 2 chi co 29 ngay!";
					gotoxy(66,15);
					cout << "   ";

					goto p3;
				} 
			}
		}

		if (add->ngayGioBay.nam == 2022 && add->ngayGioBay.thang == 5 && temp < 31)
		{
			gotoxy(16,32);
			cout << "Khong quan ly chuyen bay vao ngay ";
			if (temp < 10) cout << "0";
			cout << temp << "/05/2022";
			
			gotoxy(66,15);
			cout << "   ";

			goto p3;		 
		}

		d = temp;

		gotoxy(66,15);
		cout << "   ";
		gotoxy(67,15);
		if (temp < 10) cout << "0";
		cout << temp;
	}


	check:
	//kiem tra lai ngay thang nam

	if (d == add->ngayGioBay.ngay && m == add->ngayGioBay.thang && y == add->ngayGioBay.nam) goto p4; //khong cap nhat lai dd/mm/yyyy;

	if (isAvailable(head, add->soHieuMayBay, d, m, y) == false)
	{
		gotoxy(16,32);
		cout << "May bay [" << add->soHieuMayBay << "] khong the dung vao ngay ";
		if (d < 10) cout << "0";
		cout << d << "/";
		if (m < 10) cout << "0";
		cout << m << "/" << y;

		gotoxy(66,15);
		cout << "  ";

		goto top;
	}	

	add->ngayGioBay.ngay = d;
	add->ngayGioBay.thang = m;
	add->ngayGioBay.nam = y;

	gotoxy(123,5+i*2);
	cout << y;

	gotoxy(120,5+i*2);
	if (temp < 10) cout << "0";
	cout << m;

	gotoxy(117,5+i*2);
	if (temp < 10) cout << "0";
	cout << d;

	//xu ly thoi gian---------------------------------------------------gio//
	p4:
	gotoxy(59,18);
	text = numInput(59,18,2);

	sysBox();
	
	if (kyTuRong(text) == true)
	{
		gotoxy(16,32);
		cout << "                      ";
		
		gotoxy(60,18);
		cout << "xx";

		goto p5;
	}
	else
	{
		stringstream ss3(text);
		ss3 >> temp;

		if (temp >= 24)
		{
			gotoxy(16,32);
			cout << "Sai dinh dang gio! (Goi y: 0 -> 23)";

			gotoxy(59,18);
			cout << "  ";

			goto p4;
		}

		add->ngayGioBay.gio = temp;

		gotoxy(59,18);
		cout << "  ";
		gotoxy(60,18);
		if (temp < 10) cout << "0";
		cout << temp;

		gotoxy(130,5+i*2);
		if (temp < 10) cout << "0";
		cout << temp;
	}

	

	//xu ly thoi gian--------------------------------------------------phut//
	p5:
	gotoxy(66,18);
	text = numInput(66,18,2);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(16,32);
		cout << "                      ";
		
		gotoxy(67,18);
		cout << "xx";

		goto here;
	}
	else
	{
		stringstream ss4(text);
		ss4 >> temp;

		if (temp >= 60)
		{
			gotoxy(16,32);
			cout << "Sai dinh dang phut! (Goi y: 0 -> 59)";

			gotoxy(66,18);
			cout << "  ";

			goto p5;
		}

		add->ngayGioBay.phut = temp;
		sysBox();

		gotoxy(66,18);
		cout << "   ";
		gotoxy(67,18);
		if (temp < 10) cout << "0";
		cout << temp;

		gotoxy(133,5+i*2);
		if (temp < 10) cout << "0";
		cout << temp;
	}

	here:
	box(15,2,55,2,7,7,"");
	gotoxy(16,3);
	cout << "Trang thai: ";

	text = numInput(28,3,1);

	sysBox();
	
	if (kyTuRong(text) == true)
	{
		gotoxy(16,32);
		cout << "                               ";
		gotoxy(16,32);
		cout << "Trang thai duoc giu nguyen";

		return;
	}
	else
	{
		stringstream ss5(text);
		ss5 >> temp;

		if (temp >= 4)
		{
			gotoxy(16,32);
			cout << "Goi y: 0. Huy chuyen - 2. Het ve - 3. Hoan thanh";

			gotoxy(28,3);
			cout << "  ";

			goto here;
		}

		if (temp == add->trangThai)
		{
			gotoxy(16,32);
			cout << "Trang thai duoc GIU NGUYEN!";
			return;
		}

		if (temp == 0 || temp == 3)
		{
			sysBox();
			gotoxy(16,32);
			if (temp == 0) cout << "Chuyen bay se KHONG THE hieu chinh neu thay doi!";
			else if (temp == 3)
			{
				cout << "Chuyen bay [" << add->maChuyenBay << "] chua den NGAY khoi hanh!";
				return;
			}

			if (askBox(1) == 2) return;
		}

		add->trangThai = temp;

		gotoxy(164,5+i*2);
		if (temp == 0) cout << "HUY CHUYEN";
		else if (temp == 1) return;
		else if (temp == 2)
		{
			if (add->qlveMB.daDat < add->soCho)
			{
				gotoxy(16,32);
				cout << "Con " << add->soCho - add->qlveMB.daDat << " ve chua ban...";
				add->trangThai = 1;
				return;
			}
			else if (add->qlveMB.daDat == add->soCho) cout << "HET VE";
		}
		else if (temp == 3)
		{
			for (us i = 0; i < qlMB.count; i++)
			{
				if (qlMB.ptr[i]->soHieuMayBay == add->soHieuMayBay)
				{
					qlMB.ptr[i]->daThucHien += 1;
					break;
				}
			}
			
			cout << "HOAN THANH";
		}
	}


}
// =======================================================================================================


// cau b
void chucNang2_1(chuyenBay*& head, dsMB& qlMB, string*& DSSB, us& countCB)
{
	us temp;
	
	system("cls");
	system("color 7");

	inChuyenBay(head);

	while (true)
	{
		temp = subBox();

		if (temp == 2)
		{
			editChuyenBay(head, qlMB);
			continue;
		}
		else if (temp == 0) break;

		if (themChuyenBay(head, qlMB, DSSB) == true)
		{
			addON(head, countCB);
			countCB += 1;
		}
	}
}
// =======================================================================================================


// xu ly cau c
void gheTrong(chuyenBay*& ptr)
{
	us line = 0;
	
	boxVeTrong(ptr);

	gotoxy(16,37);

	for (us i = 1; i <= ptr->soCho; i++)
	{
		if (ptr->gheDaDat[i] == 0)
		{
			if (i == 50)
			{
				line++;
				gotoxy(16,37+line*2);
			}

			if (i == 100)
			{
				line++;
				gotoxy(16,37+line*2);
			}

			if (i > 100)
			{
				if (i == 139+(line-2)*40)
				{
					line++;
					gotoxy(16,37+line*2);
				}
			}

			cout << i << " ";
		}
	}
}

void xuLyVeMB(chuyenBay*& head, NodeHK& hk)
{
	string text;
	chuyenBay* cb;
	us temp;
	
	traCuuChuyenBay(head);
	p4:
	cb = head;
	gotoxy(44,10);

	text = limitedInput(44,10,15);

	inHoa(text);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(16,32);
		cout << "Khong duoc bo trong!";

		gotoxy(44,10);
		cout << "                ";

		goto p4;
	}

	if (isMaCbAvailable(cb, text) == false)
	{
		gotoxy(16,32);
		cout << "Ma CB vua nhap KHONG ton tai";

		gotoxy(44,10);
		cout << "                ";

		goto p4;
	}

	for (us i = 1; i <= cb->soCho; i++)
	{
		if (cb->qlveMB.ptr[i].soCmnd == hk.soCMND)
		{
			gotoxy(16,32);
			cout << "KHONG THE mua 2 ve tren cung mot chuyen bay!";

			gotoxy(44,10);
			cout << "                ";

			if (askBox(2) == 2)
			{
				sysBox();
				
				gotoxy(16,32);
				cout << "HUY BO thao tac dat ve!";

				return;
			}
			else goto p4;
		}
	}

	gheTrong(cb);
	p5:
	gotoxy(65,15);
	text = numInput(65,15,3);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(16,32);
		cout << "Khong duoc bo trong!";

		gotoxy(65,15);
		cout << "   ";

		goto p5;
	}

	stringstream ss(text);
	ss >> temp;

	if (temp < 1 || temp > cb->soCho)
	{
		gotoxy(16,32);
		cout << "Cho ngoi khong hop le!";

		gotoxy(65,15);
		cout << "   ";

		goto p5;
	}
	else if (cb->gheDaDat[temp] == 1)
	{
		gotoxy(16,32);
		cout << "Ghe so [";
		if (temp < 10) cout << "00";
		else if (temp < 100) cout << "0";
		cout << temp << "] da co HK dat truoc!";

		gotoxy(65,15);
		cout << "   ";

		goto p5;
	}

	gotoxy(65,15);
	cout << "     ";
	
	gotoxy(66,15);
	if (temp < 10) cout << "00";
	else if (temp < 100) cout << "0";
	cout << temp;

	cb->qlveMB.daDat += 1;

	cb->qlveMB.ptr[cb->qlveMB.daDat].soCmnd = hk.soCMND;
	cb->qlveMB.ptr[cb->qlveMB.daDat].soGhe = temp;

	cb->gheDaDat[temp] = 1;

	gotoxy(16,32);
	cout << "Dat ve THANH CONG!";
}

NodeHK xuLysoCMND(PTRHK& qlHK, bool& find)
{
	string text;
	NodeHK fake;
	
	p2:
	gotoxy(30,8);
	
	text = numInput(30,8,12);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(16,32);
		cout << "Khong duoc bo trong!";

		gotoxy(30,8);
		cout << "                   ";

		goto p2;
	}

	if (text.length() != 12 && text.length() != 9)
	{
		gotoxy(16,32);
		cout << "Can co 9 hoac 12 chu so!";

		gotoxy(30,8);
		cout << "                   ";

		goto p2;
	}

	if (isCheckCMND(qlHK, text, fake) == true)
	{
		gotoxy(22,4);
		cout << fake.ho;

		gotoxy(22,6);
		cout << fake.ten;

		gotoxy(28,10);
		if (fake.phai == 1) cout << "Nam";
		else cout << "Nu";
		
		find = true;
		return fake;
	}
	else
	{
		gotoxy(16,32);
		cout << "So CMND / CCCD vua nhap KHONG ton tai!";

		gotoxy(30,8);
		cout << "                   ";

		if (askBox(2) == 2)
		{
			find = false;
			return fake;
		}
		else goto p2;
	}
}

bool themHanhKhach(PTRHK& qlHK, chuyenBay*& head, NodeHK& hk)
{
	string text;
	us temp;
	NodeHK fake;

	p0:
	gotoxy(21,4);
	text = nameInput(21,4,10,0);

	if (kyTuRong(text) == true)
	{
		gotoxy(16,32);
		cout << "Khong duoc bo trong!";

		gotoxy(21,4);
		cout << "           ";

		goto p0;
	}

	correctName(text);
	hk.ho = text;

	p1:
	gotoxy(22,6);
	
	text = nameInput(22,6,30,1);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(16,32);
		cout << "Khong duoc bo trong!";

		gotoxy(22,6);
		cout << "                              ";

		goto p1;
	}

	correctName(text);
	hk.ten = text;

	p2:
	gotoxy(30,8);
	
	text = numInput(30,8,12);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(16,32);
		cout << "Khong duoc bo trong!";

		gotoxy(30,8);
		cout << "                   ";

		goto p2;
	}

	if (text.length() != 12 && text.length() != 9)
	{
		gotoxy(16,32);
		cout << "Can co 9 hoac 12 chu so!";

		gotoxy(30,8);
		cout << "                   ";

		goto p2;
	}

	if (isCheckCMND(qlHK, text, fake) == true)
	{
		gotoxy(16,32);
		cout << "So CMND / CCCD vua nhap da TON TAI!";

		gotoxy(30,8);
		cout << "                   ";

		goto p2;
	}
	
	hk.soCMND = text;	

	p3:
	gotoxy(16,32);
	cout << "Huong dan: 1. Nam - 2. Nu";
	gotoxy(28,10);
	
	text = numInput(28,10,1);

	sysBox();

	if (kyTuRong(text) == true)
	{
		sysBox();
		gotoxy(16,32);
		cout << "Khong duoc bo trong!";

		gotoxy(28,10);
		cout << " ";

		goto p3;
	}

	stringstream ss(text);

	ss >> temp;
	if (temp == 1 || temp == 2)
	{
		hk.phai = temp;
		gotoxy(28,10);

		if (temp == 1) cout << "Nam";
		else cout << "Nu";
	}
	else
	{
		sysBox();

		gotoxy(28,10);
		cout << " ";

		goto p3;
	}

	xuLyVeMB(head, hk);
}

void muaThemVe(PTRHK& qlHK, chuyenBay* head)
{
	NodeHK hk;
	bool find = false;
	
	sysBox();

	boxHanhKhachCu();

	hk = xuLysoCMND(qlHK, find);

	if (find == false) return;

	xuLyVeMB(head, hk);
}

void datVeMayBay(PTRHK& qlHK, chuyenBay* head, NodeHK& hk, us& countHK)
{
	sysBox();

	boxHanhKhach();
	
	themHanhKhach(qlHK, head, hk);

	qlHK = InsertNode_HK(qlHK, hk);

	countHK += 1;
}
// ========================================================================================================


// cau c
void chucNang3_1(chuyenBay*& head, dsMB& qlMB, PTRHK& qlHK, us& countHK)
{
	us temp;
	NodeHK hk;
	
	system("cls");
	system("color 7");

	if (maCbLeft(head) == false)
	{
		sysBox();
		gotoxy(16,32);
		cout << "Hien tai KHONG CO chuyen bay nao kha dung!";

		Sleep(1500);

		return;
	}

	while (true)
	{
		temp = buyBox();
		box(15,34,160,12,7,7,"");

		if (temp == 1) datVeMayBay(qlHK, head, hk, countHK);
		else if (temp == 2) muaThemVe(qlHK, head);
		else break;
	}
}
// ========================================================================================================


// xu ly cau d
bool maCbDaMua(chuyenBay* head, NodeHK& hk)
{
	us count = 0;
	bool isFind = false;

	boxChuyenBay();
	
	while (head != NULL)
	{
		for (us i = 1; i <= head->qlveMB.daDat; i++)
		{
			if (head->trangThai == 1)
			{
				if (head->qlveMB.ptr[i].soCmnd == hk.soCMND)
				{
					infoChuyenBay(head, count);
					count++;
					isFind = true;
					goto here;
				}
			}
		}

		here:
		head = head->next;
	}

	return isFind;
}

bool huyVeMB(PTRHK& qlHK, chuyenBay* head)
{
	NodeHK hk;
	chuyenBay* cb;

	bool find = false;
	string text;
	us temp;
	
	sysBox();

	p1:
	boxHanhKhach();

	hk = xuLysoCMND(qlHK, find);

	if (find == false) return false;

	if (maCbDaMua(head, hk) == false)
	{
		gotoxy(16,32);
		cout << "CHUA dat ve...KHONG THE thuc hien thao tac!";

		if (askBox(2) == 1) goto p1;
		else return false;
	}

	p2:
	cb = head;
	gotoxy(44,10);

	text = limitedInput(44,10,15);

	inHoa(text);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(16,32);
		cout << "Khong duoc bo trong!";

		gotoxy(44,10);
		cout << "                ";

		goto p2;
	}

	if (isMaCbAvailable(cb, text) == false)
	{
		gotoxy(16,32);
		cout << "Ma CB vua nhap KHONG ton tai";

		gotoxy(44,10);
		cout << "                ";

		goto p2;
	}

	if (askBox(1) == 1)
	{
		cb = head;

		while (cb != NULL)
		{
			if (cb->maChuyenBay == text)
			{
				gotoxy(16,32);
				cout << "Huy ve THANH CONG";

				for (us i = 1; i <= cb->qlveMB.daDat; i++)
				{
					if (hk.soCMND == cb->qlveMB.ptr[i].soCmnd)
					{
						temp = i;
						cb->gheDaDat[cb->qlveMB.ptr[i].soGhe] = 0;
						break;
					}
				}
				
				for (us i = temp; i < cb->qlveMB.daDat; i++)
				{
					cb->qlveMB.ptr[i].soGhe = cb->qlveMB.ptr[i+1].soGhe;
					cb->qlveMB.ptr[i].soCmnd = cb->qlveMB.ptr[i+1].soCmnd;
				}

				cb->qlveMB.daDat -= 1;

				return true;
			}

			cb = cb->next;
		}
	}
	else
	{
		gotoxy(16,32);
		cout << "HUY BO thao tac!";
	}
	
	if (askBox(2) == 2) return false;
	else return true;

	boxChuyenBay();
}
// =========================================================================================================


// cau d
void chucNang4_1(chuyenBay*& head, dsMB& qlMB, PTRHK& qlHK)
{
	us temp;
	
	system("cls");
	system("color 7");

	if (maCbLeft(head) == false)
	{
		sysBox();
		gotoxy(16,32);
		cout << "Hien tai KHONG CO chuyen bay nao kha dung!";

		Sleep(1500);

		return;
	}

	while (true)
	{
		if (askBox(2) == 2) break;
		
		if (huyVeMB(qlHK, head) == false) Sleep(1500);
	}
}
// =========================================================================================================


// xu ly cau e
bool kiemTraChuyenBay(chuyenBay*& add)
{
	string text;

	sysBox();

	box(15,2,55,2,7,7,"");

	gotoxy(16,3);
	cout << "Nhap ma chuyen bay: ";

	gotoxy(36,3);
	text = limitedInput(36,3,15);

	inHoa(text);

	while (add != NULL)
	{
		if (add->maChuyenBay == text)
		{
			if (add->trangThai == 1 || add->trangThai == 2 || add->trangThai == 3)
			{
				sysBox();
				gotoxy(16,32);
				cout << "Dang tim kiem danh sach hanh khach...";
				Sleep(1000);

				return true;
			}
			else if (add->trangThai == 0)
			{
				sysBox();
				gotoxy(16,32);
				cout << "Chuyen bay da HUY BO, khong the xem!";
				return false;
			}
		}
		
		add = add->next;
	}

	gotoxy(16,32);
	cout << "MA CHUYEN BAY VUA NHAP KHONG TON TAI!";

	return false;
}

bool inDanhSachCB(chuyenBay* head)
{
	us i = 0;

	boxChuyenBay();

	while (head != NULL)
	{
		if (head->trangThai == 1 || head->trangThai == 2 || head->trangThai == 3)
		{
			infoChuyenBay(head, i);
			i++;
		}

		head = head->next;
	}
}

void inDanhSachHK(PTRHK& qlHK, chuyenBay*& ptr)
{
	NodeHK temp;
	
	for (us i = 1; i <= ptr->qlveMB.daDat; i++)
	{
		isCheckCMND(qlHK, ptr->qlveMB.ptr[i].soCmnd, temp);
		infoVeMB(ptr, temp, i);
	}
}
// =========================================================================================================


// cau e
void chucNang5_1(PTRHK& qlHK, chuyenBay*& head)
{
	system("cls");
	system("color 7");

	if (head == NULL)
	{
		sysBox();
		
		gotoxy(16,32);
		cout << "KHONG CO chuyen bay nao kha dung!";
		
		Sleep(1500);
		
		return;
	}

	chuyenBay* ptr;

	inDanhSachCB(head);

	while (true)
	{
		ptr = head;
		
		if (kiemTraChuyenBay(ptr) == false)
		{
			if (askBox(2) == 2) return;
			else continue;
		}

		system("cls");
		system("color 7");
		
		boxDSHK(ptr);

		inDanhSachHK(qlHK, ptr);
		
		if (exitBox() == 0) return;
	}	
}
// =========================================================================================================


// xu ly cau f
void nhapNgayThang(us& ngay, us& thang, us& nam)
{
	bool lYear;
	string text;
	us temp;

	boxNgayThang();
	sysBox();

	p1:
	gotoxy(50,15);
	text = numInput(50,15,4);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(50,15);
		cout << "    ";

		goto p1;
	}

	stringstream ss(text);
	ss >> temp;

	if (temp <= 2021)
	{
		gotoxy(16,32);
		cout << "Khong quan ly cac chuyen bay truoc nam 2022";

		gotoxy(50,15);
		cout << "     ";

		goto p1;
	}
	
	nam = temp;

	lYear = leafYear(temp); // kiem tra nam nhuan
	gotoxy(50,15);
	cout << "     ";
	gotoxy(51,15);
	cout << temp;

	//ngay thang nam-----------------------------------------xu ly thang//
	p2:
	gotoxy(59,15);
	text = numInput(59,15,2);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(59,15);
		cout << "  ";

		goto p2;
	}
	
	stringstream ss1(text);
	ss1 >> temp;

	if (temp == 0 || temp >= 13)
	{
		gotoxy(16,32);
		cout << "Khong co thang " << temp;

		gotoxy(59,15);
		cout << "  ";

		goto p2;
	}

	thang = temp;

	gotoxy(59,15);
	cout << "  ";
	gotoxy(60,15);
	if (temp < 10) cout << "0";
	cout << temp;

	//ngay thang nam--------------------------------------------xu ly ngay//
	p3:
	gotoxy(66,15);
	text = numInput(66,15,2);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(66,15);
		cout << "  ";

		goto p3;
	}

	stringstream ss2(text);
	ss2 >> temp;

	sysBox();

	if (temp == 0)
	{
		gotoxy(16,32);
		cout << "Khong co ngay thu 0";
		gotoxy(66,15);
		cout << "   ";

		goto p3;
	}
	else if (temp >= 32)
	{
		gotoxy(16,32);
		cout << "Mot thang khong the co hon 31 ngay!";
		gotoxy(66,15);
		cout << "   ";

		goto p3;
	}
	else if (thang == 4 || thang == 6 || thang == 9 || thang == 11)
	{
		if (temp == 31)
		{
			gotoxy(16,32);
			cout << "Thang " << thang << " chi co 30 ngay! (Goi y: 1 -> 30)";
			gotoxy(66,15);
			cout << "   ";

			goto p3;
		}
	}
	else if (thang == 2) 
	{
		if (lYear == false) // neu khong phai nam nhuan
		{
			if (temp >= 29)
			{
				gotoxy(16,32);
				cout << "Thang 2 chi co 28 ngay!";
				gotoxy(66,15);
				cout << "   ";

				goto p3;
			} 
		}
		else
		{
			if (temp >= 30)
			{
				gotoxy(16,32);
				cout << "Thang 2 chi co 29 ngay!";
				gotoxy(66,15);
				cout << "   ";

				goto p3;
			} 
		}
	}

	ngay = temp;

	gotoxy(66,15);
	cout << "   ";
	gotoxy(67,15);
	if (temp < 10) cout << "0";
	cout << temp;

	//ghi lai ngay thang nam vao khung--------------------------------------//
	gotoxy(32,3);
	if (ngay < 10) cout << "0";
	cout << ngay << "/";
	if (thang < 10) cout << "0";
	cout << thang << "/";
	cout << nam;
}

void nhapDiaDiem(string*& DSSB, string& diaDiem)
{
	string text;
	us temp;
	
	traCuuSanBay(DSSB);

	p6:
	gotoxy(26,5);
	text = numInput(26,5,2);

	sysBox();

	if (kyTuRong(text) == true)
	{
		gotoxy(26,5);
		cout << "  ";

		goto p6;
	}

	stringstream ss5(text);
	ss5 >> temp;

	if (temp == 0 || temp >= 23)
	{
		gotoxy(16,32);
		cout << "Khong co trong danh sach!";

		gotoxy(26,5);
		cout << "   ";

		goto p6;
	}

	gotoxy(26,5);
	cout << DSSB[temp-1];

	diaDiem = DSSB[temp-1]; // cho thay dia chi
}

void traCuuChuyenBayCoDK(string*& DSSB, chuyenBay* head)
{
	us i = 0;
	us ngay, thang, nam;
	string diaDiem;
	
	boxTraCuuChuyenBay();

	nhapNgayThang(ngay, thang, nam);

	nhapDiaDiem(DSSB, diaDiem);

	system("cls");
	system("color 7");

	boxChuyenBayCoDK(ngay, thang, nam, diaDiem);

	while (head != NULL)
	{
		if (head->ngayGioBay.ngay == ngay && head->ngayGioBay.thang == thang && head->ngayGioBay.ngay == ngay && head->sanBayDen == diaDiem)
		{
			infoChuyenBayCoDK(head, i);
			i++;
		}

		head = head->next;
	}
}
// =========================================================================================================


// cau f
void chucNang5_2(string*& DSSB, chuyenBay*& head)
{	
	system("cls");
	system("color 7");
	
	while (true)
	{
		traCuuChuyenBayCoDK(DSSB, head);

		if (askBox(2) == 2) break;
	}	
}
// =========================================================================================================


// xu ly cau g
bool kiemTraVeTrong(chuyenBay*& add)
{
	string text;

	sysBox();

	box(15,2,55,2,7,7,"");

	gotoxy(16,3);
	cout << "Nhap ma chuyen bay: ";

	gotoxy(36,3);
	text = limitedInput(36,3,15);

	inHoa(text);

	while (add != NULL)
	{
		if (add->maChuyenBay == text)
		{
			if (add->trangThai == 1 || add->trangThai == 3)
			{
				sysBox();
				gotoxy(16,32);
				cout << "Dang tim kiem ve con trong...";
				Sleep(1000);

				return true;
			}
			else if (add->trangThai == 2)
			{
				sysBox();
				gotoxy(16,32);
				cout << "Chuyen bay da HET VE!";
				Sleep(1000);

				return false;
			}
			else if (add->trangThai == 0)
			{
				sysBox();
				gotoxy(16,32);
				cout << "Chuyen bay da HUY BO, khong the xem!";
				return false;
			}
		}
		
		add = add->next;
	}

	gotoxy(16,32);
	cout << "MA CHUYEN BAY VUA NHAP KHONG TON TAI!";

	return false;
}

void chuyenBayKhaDung(chuyenBay* head)
{
	us i = 0;

	boxChuyenBay();

	while (head != NULL)
	{
		if (head->trangThai == 1 || head->trangThai == 3)
		{
			infoChuyenBay(head, i);
			i++;
		}

		head = head->next;
	}
}
// =========================================================================================================


// cau g
void chucNang5_3(chuyenBay*& head)
{
	system("cls");
	system("color 7");
	
	if (head == NULL)
	{
		sysBox();
		gotoxy(16,32);

		cout << "KHONG CO chuyen bay nao kha dung!";
		Sleep(1500);
		return;
	}

	chuyenBay* ptr;

	chuyenBayKhaDung(head);

	while (true)
	{	
		if (askBox(2) == 2) return;

		ptr = head;

		if (kiemTraVeTrong(ptr) == false) continue;
		else gheTrong(ptr);
	}
}
// =========================================================================================================


// xu ly cau h
void sapXep(dsMB& qlMB)
{
	mayBay* temp;
	
	for (us i = 0; i < qlMB.count-1; i++)
	{
		for (us j = i; j < qlMB.count; j++)
		{
			if (qlMB.ptr[i]->daThucHien < qlMB.ptr[j]->daThucHien)
			{
				temp = qlMB.ptr[i];

				qlMB.ptr[i] = qlMB.ptr[j];

				qlMB.ptr[j] = temp;
			}
		}
	}
}
// ==========================================================================================================


// cau h
void chucNang6_1(dsMB& qlMB)
{
	system("cls");
	system("color 7");

	if (qlMB.count == 0)
	{
		sysBox();
		
		gotoxy(16,32);
		cout << "KHONG CO may bay nao de THONG KE";

		Sleep(1500);
	}
	else
	{
		dsMB fake = qlMB; // tao ra 1 bien de truyen du lieu quan ly may bay tam thoi
		
		boxThongKe();
	
		sapXep(fake); // thao tac tren con tro fake

		for (us i = 0; i < fake.count; i++) 
		{
			if(fake.ptr[i]->daThucHien > 0) infoLuotThucHien(fake.ptr[i], i); // in ra
	
	}
	
	}
	exitBox();
}
// ==========================================================================================================
