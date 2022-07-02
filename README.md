# Quan-Ly-Chuyen-Bay-PTITHCM
Đồ án quản lý chuyến bay khóa 2020

## ĐỀ BÀI <a name="1"></a>

#### Máy bay: 
+ Mảng con trỏ có tối đa 300 máy bay. 
+ Mỗi máy bay có các thông tin (Số hiệu MB (C15), loại máy bay (C40), số chỗ)
+ Mỗi máy bay có 1 số hiệu duy nhất; số chỗ >=20

#### Chuyến bay: 
+ Danh sách liên kết đơn (Mã CB: C15, Ngày giờ khởi hành, Sân bay đến, Trạng thái, Số hiệu MB, danh sách vé). 
+ Mỗi chuyến bay có 1 mã duy nhất
+ Trạng thái chuyến bay bao gồm: 0: hủy chuyến, 1: còn vé, 2: hết vé, 3: hoàn tất
+ Danh sách vé cho biết thông tin vé trên chuyến bay, và số CMND của hành khách đã đặt vé đó. (mảng con trỏ)
+ Mỗi vé có số vé là số thứ tự trên chuyến từ số 1 đến số chỗ. Danh sách vé được cấp phát bộ nhớ tự động dựa vào số chỗ của máy bay thực hiện chuyến bay.

#### Hành khách: 
+ Cây nhị phân tìm kiếm cân bằng (Số CMND, Ho, Ten, Phai)

#### Chương trình có các chức năng sau: 

a/ Cập nhập danh sách các máy bay (thêm / xóa / hiệu chỉnh)      -         

b/ Cập nhật chuyến bay: cho phép lập chuyến bay mới, hiệu chỉnh ngày giờ khởi hành của chuyến bay, hủy chuyến.

c/ Đặt vé: cho phép đặt vé trên 1 chuyến bay; nếu thông tin hành khách chưa có thì tự động cập nhật vào danh sách hành khách, nếu có rồi thì in ra màn hình để kiểm tra. Mỗi vé đều phải ghi nhận số CMND của hành khách; nếu hành khách chưa có số CMND thì yêu cầu nhập thông tin hành khách trước. Trên 1 chuyến bay, mỗi hành khách chỉ được mua 1 vé. 

d/ Hủy vé: cho phép hủy vé đã đặt của hành khách.

e/ In danh sách các hành khách thuộc 1 chuyến bay dựa vào mã chuyến bay. Kết xuất:

DANH SÁCH HÀNH KHÁCH THUỘC CHUYẾN BAY ######
Ngày giờ khởi hành:   dd/mm/yyyy    hh:mm    Nơi đến: xxxxxxxxxxx

	STT	SỐ VÉ		SỐ CMND	HỌ TÊN	PHÁI


f/ In danh sách các chuyến bay khởi hành trong ngày dd/mm/yyyy đến nơi XXXX (cho biết cụ thể số lượng các vé còn trống và giờ khởi hành) 

g/ In danh sách các vé còn trống của 1 chuyến bay có mã chuyến bay là X. 
h/ Thống kê số lượt thực hiện chuyến bay của từng máy bay theo thứ tự số lượt thực hiện giảm dần. Kết xuất:
	Số hiệu máy bay		Số lượt thực hiện chuyến bay

Lưu ý: Chương trình cho phép lưu các danh sách vào file; Kiểm tra các điều kiện khi nhập liệu làm dữ liệu bị sai.

## CHỨC NĂNG <a name="2"></a>

a) MÁY BAY (thêm, xóa, hiệu chỉnh)

- Thêm (maMB là khóa chính không được trùng, không có khoảng trắng, soCho được giới hạn từ 20-300)
- Xóa (Khi chuyến bay đã dùng maMB nào đó, kể cả khi chuyến bay đã ở trạng thái hoàn thành hoặc hủy chuyến thì không được xóa)
- Chỉnh sửa:
    - Không khuyến khích chức năng sửa maMB (ý kiến của mình)
    - Chưa thành lập chuyến bay: loaiMB và soCho được sửa tùy ý
    - Đã thành lập nhưng status là còn vé hoặc hết vé → chỉ cho sửa số ghế tăng dần
        (cập nhật chuyến bay số ghế tăng dần)
        
b) CHUYẾN BAY (thêm,cancle,hiệu chỉnh ngày giờ)
- Thêm (maCB là khóa chính, không cho phép lập chuyến bay trong quá khứ, ngày giờ phải hợp lệ ví dụ như tháng 2 của năm nhuận, không cho phép dùng cùng một maMB trong ngày vì tính logic)
- Hiệu chỉnh (cho phép hiệu chỉnh ngày giờ trong điều kiện maMB đang dùng hợp lệ với ngày tháng vừa mới nhập liệu; chỉ cho phép sửa trạng thái từ CÒN VÉ sang HẾT VÉ khi thật sự hết vé, còn không chỉ có thể sửa thành HOÀN THÀNH hoặc HỦY CHUYẾN)
- Hủy (không thể hủy những maCB ở trạng thái HOÀN THÀNH hoặc HỦY CHUYẾN)

c) ĐẶT VÉ
- Gồm 2 lựa chọn: đã từng mua vé hoặc lần đầu đặt vé
- soCMND dùng được ở 02 định dạng: 8 số hoặc 12 số (mình không nhớ rõ lắm ^^), không được trùng!
- Khách được đặt vé thoải mái, trừ trường hợp đặt hai vé trên CÙNG một maCB

d) HỦY VÉ
- Hủy thoải mái không ràng buộc điều kiện

e/ In danh sách các hành khách thuộc 1 chuyến bay dựa vào mã chuyến bay
- In theo đúng như thứ tự đăng ký vé trên maCB ấy

(các câu thống kê g,h chức năng tương tự đề yêu cầu)

h/ Thống kê số lượt thực hiện chuyến bay của từng máy bay
- In ra tất cả các maMB và lượt thực hiện của nó.

## LƯU Ý <a name="3"></a>
- TRÁNH các biến dư thừa trong quá trình làm việc (không dùng thì PHẢI xóa đi khỏi CTDL)
- Cẩn thận khi cấp phát vùng nhớ cho con trỏ, phải giải phóng ĐÚNG CÁCH
- Các file lưu dữ liệu hợp lý nhất có thể (ví dụ không nên lưu mỗi hành khách một file)
- Các loại khóa chính như maMB, maCB thì luôn phải chuẩn hóa thành dạng IN HOA
- Trong vùng nhập số thì không nên cho nhập chữ và ngược lại (mình sử dụng các hàm riêng biệt để nhập, tên là [.?]Input(), các bạn có thể xem trong file)-
- Và còn rất nhiều điều khác, hãy tận dụng những buổi học hoặc hỏi trên ZALO để hỏi thầy về những phần không chắc chắn
- QUAN TRỌNG: nhớ hiểu kỹ CODE của mình làm, điểm số rất chênh lệch giữa người hiểu và không hiểu. Ngoài ra bạn hiểu CODE hơn sẽ được thầy ưu tiên trả lời lại câu hỏi của những bạn không trả lời đúng câu hỏi (cơ hội để cướp điểm ấy ^^).
- QUAN TRỌNG KHÔNG KÉM: hãy GHI NHỚ mã điểm 3 chữ số mà thầy chấm xong khi vấn đáp ^^

## THẦY NHẬN XÉT <a name="4"></a>
- Khen
  ........!*@#&!^#*!$*@

- Chê
  - Chương trình không có khả năng quay lại (ví dụ khi không may nhập sai một phần nào đó của MÁY BAY thì không sửa lại được ngay lập tức, khi đang nhập liệu dở dang mà muốn không nhập nữa thì không được)
  - Có một vài biến thừa trong CTDL
  - Giải phóng vùng nhớ không tốt ở phần MÁY BAY liên quan đến mảng con trỏ. Mặc dù thầy cho cơ hội viết sửa lại code nhưng mình không sửa được :( tại gà quá
