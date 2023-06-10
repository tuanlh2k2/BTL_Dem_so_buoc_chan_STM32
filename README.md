 Bài tập lớn môn học "Nhập môn hệ thống nhúng".
 Giảng viên: 
 - TS.Nguyễn Kiêm Hùng.
 Sinh viên thực hiện:
 - Lường Hữu Tuấn - 20020735
 - Bùi Quang Hiếu - 20020662

 Mô tả bài tập.
-	Chức năng: Đếm số bước chân khi người sử dụng thiết bị di chuyển và hiển thị kết quả trên màn LCD.
-	Các đầu vào:
    * Hệ thống sử dụng cảm biến gia tốc mpu6050 để đo số bước chân.
    * SW1 để chuyển đổi bộ đếm bước chân hoạt động giữa trạng thái hoạt động và trạng thái dừng. Khi bộ đếm dừng hoạt động, nếu bấm SW1 bộ đếm chuyển sang trạng thái hoạt động, và ngược lại. Khi chuyển từ trạng thái dừng sang trạng thái hoạt động, bộ đếm tiếp tục đếm từ số bước chân đang hiển thị trên LCD.
    * SW2 để xóa (reset) kết quả đếm của bộ đếm về không.
-	Các đầu ra: 
    * Hệ thống có 2 lối ra trạng thái: LED xanh nhấp nháy với tần số 1Hz khi bộ đếm hoạt động; tắt khi hệ thống dừng hoạt động. LED đỏ sáng khi hệ thống dừng hoạt động; tắt khi hệ thống hoạt động.
    * LCD: Hiện thị số bước chân 
-	Bộ đếm sử dụng một timer để xác định khoảng thời gian nhấp nháy LED xanh.
