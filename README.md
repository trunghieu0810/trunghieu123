# trunghieu123

game có giao diện đồ họa
có tính điểm
************CÁCH CHƠI******************
cách chơi:
- sử dụng các phím mũi tên để di chuyển máy bay chính
- chuột trái để bắn đạn laser, chuột phải để bắn đạn bom
- mỗi lượt chơi có 3 mạng


**********THAM KHẢO*********
phát triển dựa trên bản gốc game plane battle được hướng dẫn trên trang https://phattrienphanmem123az.com, cải tiến thêm các tính năng:
- tính điểm
- nhạc nền
- thêm mạng(lượt chơi) cho nhân vật
- cải thiện về mặt hình ảnh
- tối ưu lại code

**********MÔ TẢ GAME*********
luồng hoạt động của game:
- các thành phần chính bao gồm:
  + nhân vật chính là 1 máy bay
  + địch là các máy bay đi ngc chiều
  + lớp đạn bắn(gồm có đạn bắn của nv chính và đạn bắn của địch)
- game hoạt động như sau:
  + điều khiển nhân vật chính, bắn ra các viên đạn để tiêu diệt địch
  + khi ảnh địch và viên đạn trùng nhau thì sẽ delete hình ảnh địch và random 1 vị trí mới
  + khi ảnh của nv chính trùng với ảnh máy bay địch hoặc ảnh viên đạn địch thì sẽ bị mất 1 mạng
  + khi số lần chết > 3 thì game over
  + game over thì sẽ load lên screen lựa chọn "Exit" và "Play again"
  + nếu chọn exit thì out game còn nếu chọn play again thì khởi tạo lại tất cả mọi giá trị và trở lại vị trí trước vòng while(sử dụng goto)
