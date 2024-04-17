boolean buttonOver = false;
int buttonX = 20;
int buttonY = 20;
int buttonWidth = 80;
int buttonHeight = 40; 

float zoom = 500;
float angleX = 0;
float angleY = 0;
float prevMouseX;
float prevMouseY;


void mouseWheel(MouseEvent event) {
  float e = event.getCount();
  zoom += e * 20;
  zoom = constrain(zoom, 500, 1000);
}


void ScreenRotate(){
  if (mousePressed) {
    angleX += (mouseX - prevMouseX) * 0.01;
    angleY += (mouseY - prevMouseY) * 0.01;
  }
  prevMouseX = mouseX;
  prevMouseY = mouseY;
}


void drawButton(PGraphics pg) {
  pg.pushMatrix();
  pg.camera();
  pg.noLights();
  if (buttonOver) {
    pg.fill(200);
  } else {
    pg.fill(180);
  }
  pg.rect(buttonX, buttonY, buttonWidth, buttonHeight);
  pg.fill(0); // 텍스트 색상
  pg.textAlign(CENTER, CENTER); // 텍스트를 버튼의 중앙에 정렬
  pg.textFont(font); // 저장된 폰트 사용
  pg.text("Home", buttonX + buttonWidth / 2, buttonY + buttonHeight / 2);
  
  pg.popMatrix();  
}

void mousePressed() {
  if (overButton()) {
      angleX = 0;
      angleY = 0;
      zoom = 500;
  }
}

boolean overButton() {
  return mouseX > buttonX && mouseX < buttonX + buttonWidth &&
         mouseY > buttonY && mouseY < buttonY + buttonHeight;
}
