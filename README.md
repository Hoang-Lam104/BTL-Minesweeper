# BTL-Minesweeper

Link youtube: https://youtu.be/Z89yTEV6Uaw

1) Hướng dẫn cài đặt

	Cài đặt môi trường
 	* Cài đặt Visual Studio Code
 		https://code.visualstudio.com/download
 	* Cài đặt mingw
 		https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download
 	* Cài đặt sfml 
 		https://www.sfml-dev.org/download/sfml/2.5.1/
 	* Hướng dẫn cụ thê
 		https://www.youtube.com/watch?v=Ptw1KKI9_Sg
		
 	Hướng dẫn chạy game
	* Sau khi cài đặt hoàn tất, tải src code game về máy và giải nén
	* Khởi động Visual Studio Code đã cài đặt các thư viện
	* Chọn File/Open Folder/BTL-Minesweeper
	* Mở terminal
	* Chạy lệnh 'g++ -c main.cpp -I"C:\SFML-2.5.1\include"' để tạo main.o
	* Chạy lệnh 'g++ main.o -o main -L"C:\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system' để tạo main.exe
	* Chạy file main.exe để chạy game
	
2) Mô tả chung 

	 - Game Minesweeper hay Dò mìn là trò chơi giải đố 1 người chơi
	 - Game có map 30x16 ô và ẩn phía dưới map là các quả mìn được cài sẵn dưới các ô
	 - Các ô khi mở sẽ hiển thị 1 số ứng với số mìn xung quanh ô đó
	 - Nhiệm vụ của người chơi là mở hết tất cả các ô mà không bị bùm
 
3) Mô tả các chức năng

	* Check win và hiện thị "You Win" nếu người mở hết các ô mà không bị dính bom và hiện "Game Over" nếu người chơi mở trúng boom
	* Gài boom random trong map
	* Set number cho các ô tương ứng với số bom xung quang ô
	* Mở tất cả các ô có number = 0 xung quang
	
4) Kỹ thuật lập trình
	* Mảng 2 chiều 
 	* Đồ họa sfml
  	* Vector 2 chiều
  	* Đệ quy 

5) Đánh giá

  	* Game còn chưa được thực sự hoàn thành với 1 số chức năng còn thiếu 
  	* Hướng phát triển: 
   		- Thêm nút chơi lại
   		- Thêm tính thời gian và lưu trữ kết quả
   		- Thêm các map khác
