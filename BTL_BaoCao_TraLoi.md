# Báo cáo Trả lời Câu hỏi Bài tập lớn (BTL) Cấu trúc dữ liệu & Giải thuật

Báo cáo này được lập để trả lời các câu hỏi 1, 2, và 3 theo yêu cầu của bạn dựa trên việc phân tích các file nguồn trong dự án Quản lý Đặt Tour Du lịch.

---

## Câu 1: Cấu trúc dữ liệu sử dụng để lưu trữ và Đối tượng quản lý chính

### 1. Cấu trúc dữ liệu lưu trữ
Dự án sử dụng các cấu trúc dữ liệu tự định nghĩa dạng danh sách liên kết kép (Double Linked List) để lưu trữ và xử lý dữ liệu trong bộ nhớ (`Storage` trong [storage.h](file:///d:/BTL_CTDLGT/controllers/storage.h)), thay thế hoàn toàn cho các container chuẩn (STL):
*   **`DoubleLinkedList` (Danh sách liên kết kép tự định nghĩa):** Đây là cấu trúc dữ liệu lưu trữ chính trong bộ nhớ. Nó quản lý các nút (`DLLNode`) liên kết hai chiều, cho phép duyệt thuận nghịch, chèn và xóa phần tử một cách linh hoạt. Các danh sách bao gồm:
    *   `DoubleLinkedList<Tour> tours;` (Danh sách các chuyến du lịch)
    *   `DoubleLinkedList<Customer> customers;` (Danh sách khách hàng)
    *   `DoubleLinkedList<Staff> staffs;` (Danh sách nhân viên)
    *   `DoubleLinkedList<Booking> bookings;` (Danh sách đơn đặt tour)
*   **`DLLMap` (Bảng ánh xạ tự định nghĩa dựa trên danh sách liên kết kép):** Được sử dụng thay thế cho `std::map` trong các hàm thống kê và gom nhóm dữ liệu (trong [storage.h](file:///d:/BTL_CTDLGT/controllers/storage.h) và [storage.cpp](file:///d:/BTL_CTDLGT/controllers/storage.cpp)). Mỗi nút trong danh sách liên kết kép của `DLLMap` đóng vai trò là một cặp Key-Value với hai trường dữ liệu tương ứng là `first` (khoá) và `second` (giá trị), giúp duyệt phần tử nhanh chóng qua cú pháp tương thích hoàn toàn với STL:
    *   `DLLMap<int, double> revenuePerTour` (Thống kê doanh thu theo mã Tour)
    *   `DLLMap<int, int> bookingsPerCustomer` (Số đơn đặt của mỗi Khách hàng)
    *   `DLLMap<int, int> bookingsPerStaff` (Số đơn đặt do mỗi Nhân viên xử lý)
    *   `DLLMap<std::string, int> bookingsByStatus` (Số đơn đặt theo trạng thái đơn)

### 2. Đối tượng được quản lý chính
Hệ thống được thiết kế theo mô hình thực thể liên kết giống như cơ sở dữ liệu quan hệ, quản lý **4 đối tượng chính**:
1.  **Tour (Chuyến đi - [Tour.h](file:///d:/BTL_CTDLGT/models/Tour.h)):** Đại diện cho một gói du lịch. Các thông tin chính gồm: Mã chuyến đi (`aintTourID`), Tên chuyến đi (`astrTourName`), Điểm khởi hành (`astrOrigin`), Điểm đến (`astrDestination`), Ngày bắt đầu (`astrStartDate`), Ngày kết thúc (`astrEndDate`), Giá tiền (`adblPrice`), Sức chứa tối đa (`aintCapacity`), Trạng thái (`astrStatus`), và Mô tả (`astrDescription`).
2.  **Customer (Khách hàng - [Customer.h](file:///d:/BTL_CTDLGT/models/Customer.h)):** Khách hàng đặt mua tour. Các thông tin chính gồm: Mã khách hàng (`aintCustomerID`), Tên khách hàng (`astrCustomerName`), Số điện thoại (`astrPhone`), Email (`astrEmail`), Địa chỉ (`astrAddress`), Ngày sinh (`astrBirthDate`), và Hạng thành viên (`astrMemberType`).
3.  **Staff (Nhân viên - [Staff.h](file:///d:/BTL_CTDLGT/models/Staff.h)):** Nhân viên chịu trách nhiệm bán tour hoặc hướng dẫn. Các thông tin chính gồm: Mã nhân viên (`aintStaffID`), Tên nhân viên (`astrStaffName`), Chức vụ (`astrPosition`), Số điện thoại (`astrPhone`), Email (`astrEmail`), và Tên tài khoản (`astrUsername`).
4.  **Booking (Đơn đặt tour - [Booking.h](file:///d:/BTL_CTDLGT/models/Booking.h)):** Đơn giao dịch liên kết 3 thực thể trên thông qua khoá ngoại. Các thông tin chính gồm: Mã đơn (`aintBookingID`), Mã chuyến đi liên kết (`aintTourID`), Mã khách hàng đặt (`aintCustomerID`), Mã nhân viên tạo đơn (`aintStaffID`), Số lượng khách tham gia (`aintQuantity`), Tổng số tiền (`adblTotal`), Ngày đặt đơn (`astrBookingDate`), và Trạng thái đơn đặt (`astrStatus`).

---

## Câu 2: Các yêu cầu xử lý đã thực hiện được trong BTL

Hệ thống đã hoàn thiện một bộ chức năng phong phú phục vụ quản lý tour bao gồm:
1.  **Quản lý nghiệp vụ CRUD cơ bản (Thêm, Đọc, Tìm kiếm, Xóa):**
    *   **Thêm mới:** Hỗ trợ tự sinh mã ID tăng dần (`myIntNextTourID`, `myIntNextCustomerID`, v.v.) khi thêm mới các đối tượng Tour, Customer, Staff, Booking.
    *   **Hiển thị:** Hiển thị danh sách tóm tắt hoặc chi tiết liên kết (JOIN-like view) của các đơn đặt tour kết hợp thông tin Tên Tour, Tên Khách hàng, Tên Nhân viên.
    *   **Tìm kiếm:** Tìm kiếm nhanh đối tượng bằng ID hoặc theo Tên (ví dụ tìm Tour theo cụm từ trong tên).
    *   **Xóa và Đảm bảo toàn vẹn dữ liệu (Ràng buộc khóa ngoại):** Kiểm tra điều kiện ràng buộc trước khi xóa. Không cho phép xóa Tour, Khách hàng hoặc Nhân viên nếu họ đang có đơn đặt tour (Booking) hoạt động để tránh dữ liệu mồ côi.
2.  **Kiểm tra tính hợp lệ của nghiệp vụ (Business Rules Validation):**
    *   Chuyển đổi chuỗi ngày dạng `DDMMYYYY` thành số nguyên `YYYYMMDD` để thực hiện so sánh toán học.
    *   Kiểm tra ngày khởi hành của Tour mới phải từ ngày hiện tại trở đi.
    *   Kiểm tra ngày kết thúc của Tour phải sau ngày khởi hành.
    *   Kiểm tra ngày đặt Booking phải nằm trong khoảng thời gian khởi hành và kết thúc của Tour đó, đồng thời không được đặt trong quá khứ.
    *   Tự động tính tổng tiền của Booking dựa trên đơn giá Tour và số lượng khách đăng ký.
3.  **Sắp xếp dữ liệu (Sorting):**
    *   Sắp xếp danh sách Tour tăng/giảm theo Giá vé hoặc Ngày bắt đầu.
    *   Sắp xếp danh sách Khách hàng theo Tên (alphabet).
    *   Sắp xếp danh sách Booking theo Ngày thực hiện giao dịch.
4.  **Tìm kiếm giá trị cực trị (Min / Max):**
    *   Tìm Tour có giá cao nhất / thấp nhất.
    *   Tìm Tour có sức chứa lớn nhất.
    *   Tìm Booking có tổng trị giá đơn hàng lớn nhất.
5.  **Báo cáo và Thống kê (Aggregation & Statistics):**
    *   Tính tổng doanh thu toàn hệ thống, doanh thu trung bình trên mỗi booking, tổng số lượt khách đã đặt.
    *   Thống kê chi tiết tổng doanh thu phát sinh theo từng Tour.
    *   Thống kê số lượng booking của từng khách hàng, số lượng booking do từng nhân viên phụ trách.
    *   Lọc danh sách các Tour diễn ra trong một tháng/năm cụ thể.
    *   Thống kê phân loại số lượng booking theo Trạng thái (Confirmed, Pending, Canceled).
6.  **Sao lưu và Phục hồi dữ liệu (File Persistence):**
    *   Xuất toàn bộ trạng thái hệ thống ra file định dạng văn bản có cấu trúc phân tách bằng ký tự `|` (mặc định là `storage_dump.txt`).
    *   Đọc và tải dữ liệu từ file văn bản vào bộ nhớ khi khởi chạy ứng dụng.
7.  **Tạo dữ liệu thử nghiệm:**
    *   Hỗ trợ tạo nhanh dữ liệu mẫu gồm 10 bản ghi cho mỗi thực thể để thuận tiện chạy thử nghiệm ứng dụng. Chức năng có gắn cờ kiểm tra chỉ cho phép sinh dữ liệu một lần duy nhất.

---

## Câu 3: Thiết kế và Hướng dẫn lập trình chi tiết cho yêu cầu xử lý mới

**Yêu cầu xử lý mới:**
> *"Thực hiện đếm xem có bao nhiêu chuyến đi (Tour) trong danh sách có cùng điểm khởi hành (Origin) với chuyến đi đầu tiên trong danh sách."*

Để tích hợp yêu cầu này vào cấu trúc BTL hiện tại một cách chuẩn mực và nhất quán với quy tắc đặt tên của dự án (Variables prefix scope/type: `aint`, `astr`, `the`, `my`), ta sẽ thực hiện sửa đổi qua **3 file chính**:
1.  [storage.h](file:///d:/BTL_CTDLGT/controllers/storage.h) - Khai báo hàm xử lý.
2.  [storage.cpp](file:///d:/BTL_CTDLGT/controllers/storage.cpp) - Định nghĩa/Cài đặt logic thuật toán.
3.  [menu.cpp](file:///d:/BTL_CTDLGT/controllers/menu.cpp) - Tích hợp vào menu Báo cáo/Thống kê của giao diện dòng lệnh (CLI).

---

### Bước 1: Khai báo hàm trong [storage.h](file:///d:/BTL_CTDLGT/controllers/storage.h)

Ta mở file [storage.h](file:///d:/BTL_CTDLGT/controllers/storage.h), tìm đến phần khai báo các hàm aggregate helper (khoảng dòng 72-78) và khai báo thêm nguyên mẫu hàm sau:

```cpp
// Thêm khai báo dưới đây vào sau hàm countCustomers(const Storage &theStorage);
int countToursWithSameOriginAsFirst(const Storage &theStorage);
```

---

### Bước 2: Định nghĩa logic hàm trong [storage.cpp](file:///d:/BTL_CTDLGT/controllers/storage.cpp)

Ta mở file [storage.cpp](file:///d:/BTL_CTDLGT/controllers/storage.cpp), tìm đến khu vực các hàm thống kê (khoảng dòng 340-344, gần hàm `countCustomers`) và thêm phần cài đặt chi tiết dưới đây:

```cpp
int countToursWithSameOriginAsFirst(const Storage &theStorage) {
    // 1. Kiểm tra danh sách chuyến đi có trống hay không
    if (theStorage.tours.empty()) {
        return 0;
    }
    
    // 2. Lấy giá trị điểm khởi hành của phần tử đầu tiên làm mốc chuẩn (sử dụng nạp chồng toán tử [])
    std::string astrFirstOrigin = theStorage.tours[0].astrOrigin;
    int aintCount = 0;
    
    // 3. Duyệt danh sách chuyến đi (sử dụng vòng lặp range-based for trên danh sách liên kết kép)
    for (const auto &theT : theStorage.tours) {
        if (theT.astrOrigin == astrFirstOrigin) {
            aintCount++;
        }
    }
    
    return aintCount;
}
```

---

### Bước 3: Tích hợp vào Menu hiển thị trong [menu.cpp](file:///d:/BTL_CTDLGT/controllers/menu.cpp)

Ta cần cập nhật menu **Reports / Statistics** trong file [menu.cpp](file:///d:/BTL_CTDLGT/controllers/menu.cpp) để người dùng có thể lựa chọn và xem kết quả.

1.  **Cập nhật chuỗi thông báo Menu:**
    Tìm hàm `menuReports` (khoảng dòng 226) và thêm tùy chọn `13. Count tours with same origin as first` vào danh sách text hiển thị:
    ```cpp
    std::cout << "\n--- Reports / Statistics ---\n1. List Tours... \n12. Bookings by status\n13. Count tours with same origin as first\n0. Back\nChoose: ";
    ```

2.  **Thêm case xử lý trong câu lệnh switch-case:**
    Tìm câu lệnh `switch (aintChoice)` trong hàm `menuReports` và thêm `case 13` trước `default`:
    ```cpp
            case 13: {
                if (theStorage.tours.empty()) {
                    std::cout << "No tours available to compare.\n";
                } else {
                    std::string astrOrigin = theStorage.tours[0].astrOrigin;
                    int aintResult = countToursWithSameOriginAsFirst(theStorage);
                    
                    std::cout << "-------------------------------------------\n";
                    std::cout << "First tour: " << theStorage.tours[0].astrTourName << "\n";
                    std::cout << "Origin of first tour: " << astrOrigin << "\n";
                    std::cout << "Total tours starting from " << astrOrigin << ": " << aintResult << "\n";
                    std::cout << "-------------------------------------------\n";
                }
                readLine("Press Enter to continue...");
                break;
            }
    ```

