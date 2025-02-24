#include <GxEPD.h>
#include <GxGDEH029A1/GxGDEH029A1.h>  // Thư viện cho màn hình e-paper 2.9 inch
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <Fonts/FreeMonoBold24pt7b.h>  // Font chữ to cho hiển thị đẹp
#include <Fonts/FreeMonoBold18pt7b.h>  // Font chữ to cho hiển thị đẹp

// Cấu hình SPI và e-paper cho ESP32
#if defined(ESP32)
GxIO_Class io(SPI, /*CS=*/ 5, /*DC=*/ 17, /*RST=*/ 16);  // Chỉnh chân CS, DC, RST theo nhu cầu
GxEPD_Class display(io, /*RST=*/ 16, /*BUSY=*/ 4);       // Chỉnh chân BUSY nếu cần
#endif

void setup() {
  // Khởi động serial monitor để debug
  Serial.begin(115200);
  display.init();  // Khởi động màn hình E-Ink
  display.setRotation(1);  // Xoay màn hình nếu cần
  display.setTextColor(GxEPD_BLACK);
  
  // Hiệu ứng hiển thị từng màn hình
  showFirstScreen();
  delay(3000);  // Chờ 3 giây trước khi chuyển màn tiếp theo
  showSecondScreen();
  delay(3000);
  showSmileyFace();
  delay(3000);
}

void loop() {
  // Lặp lại hiệu ứng
  showFirstScreen();
  delay(3000);
  showSecondScreen();
  delay(3000);
  showSmileyFace();
  delay(3000);
}

// Hiển thị màn hình 1
void showFirstScreen() {
  display.fillScreen(GxEPD_WHITE);  // Xóa màn hình
  display.setFont(&FreeMonoBold18pt7b);
  display.setCursor(10, 30);  // Vị trí bắt đầu vẽ chữ
  display.println("Test E-INK");
  display.setCursor(10, 70);  // Vị trí bắt đầu vẽ chữ
  display.println("2.9 INCH");
  display.setCursor(10, 110);
  display.println("296x128");
  display.update();  // Cập nhật nội dung lên màn hình
}

// Hiển thị màn hình 2
void showSecondScreen() {
  display.fillScreen(GxEPD_WHITE);
  display.setFont(&FreeMonoBold24pt7b);
  display.setCursor(10, 70);
  display.println("QUY NGUYEN");
  display.update();  // Cập nhật nội dung lên màn hình
}

// Hiển thị mặt cười
void showSmileyFace() {
  display.fillScreen(GxEPD_WHITE);

  // Vẽ hình mặt cười (circle + eyes + mouth)
  int centerX = 148;  // Tâm ngang của màn hình (296 / 2)
  int centerY = 64;   // Tâm dọc của màn hình (128 / 2)
  int radius = 50;

  // Vẽ mặt tròn
  display.drawCircle(centerX, centerY, radius, GxEPD_BLACK);

  // Vẽ mắt trái
  display.fillCircle(centerX - 20, centerY - 20, 5, GxEPD_BLACK);
  // Vẽ mắt phải
  display.fillCircle(centerX + 20, centerY - 20, 5, GxEPD_BLACK);

  // Vẽ miệng cười (hình vòm đơn giản bằng đoạn thẳng)
  for (int angle = 45; angle <= 135; angle += 5) {
    int x1 = centerX + radius * 0.6 * cos(radians(angle));
    int y1 = centerY + radius * 0.6 * sin(radians(angle));
    int x2 = centerX + radius * 0.6 * cos(radians(angle + 5));
    int y2 = centerY + radius * 0.6 * sin(radians(angle + 5));
    display.drawLine(x1, y1, x2, y2, GxEPD_BLACK);
  }

  display.update();  // Cập nhật nội dung lên màn hình
}
