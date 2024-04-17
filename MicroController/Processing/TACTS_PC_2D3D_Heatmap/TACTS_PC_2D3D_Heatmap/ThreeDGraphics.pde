PGraphics canvas3D;
PGraphics canvasAxis;

int radi = 105;
int zlength = 160;

void draw3DGraphics() {
  canvas3D.beginDraw();
  canvas3D.background(0);
  canvas3D.camera(canvas3D.width / 2, canvas3D.height / 2, zoom*tan(PI*30/180),
  canvas3D.width / 2, canvas3D.height / 2, 0, 1, 0, 0); 

  canvas3D.translate(canvas3D.width / 2, canvas3D.height / 2);
  canvas3D.rotateX(angleX);
  canvas3D.rotateY(angleY);
  canvas3D.translate(-canvas3D.width / 2, -canvas3D.height / 2);
   
  drawDataPoints(canvas3D,2);
  canvas3D.pushMatrix();
  canvas3D.translate(canvas3D.width / 2 - zlength / 2, canvas3D.height / 2);
  drawCylinder(canvas3D, radi, zlength, 24);
  canvas3D.popMatrix();
  
  drawContactArrow(canvas3D);
  draw2DTextOverlay(canvas3D);
  drawButton(canvas3D);
  buttonOver = overButton();

  canvas3D.endDraw();
}

void drawDataPoints(PGraphics pg,int sphereSize){
  for (int i = 0; i < layers; i++) {
    for (int j = 0; j < spheresPerLayer; j++) {
      pg.pushMatrix();
      pg.translate(pg.width / 2 - zlength / 2, pg.height / 2);
      float angle = angleStep * j+ angleStep/2;
      float x = 40 * i + 20;
      float y = cos(angle) * (radi+sensorGroups[i][j]);
      float z = sin(angle) * (radi+sensorGroups[i][j]);
      pg.translate(x, y, z);
      pg.fill(0, 0, 255); //blue
      pg.sphere(sphereSize);
      pg.popMatrix();
    }
  }  
}


void drawCylinder(PGraphics pg, float r, float h, int detail) {
  pg.noStroke();
  pg.fill(255, 255, 255, 200); // Very transparent white
  pg.beginShape(QUAD_STRIP);
  for (int i = 0; i <= detail; i++) {
    float angle = TWO_PI / detail * i;
    float x = cos(angle) * r;
    float y = sin(angle) * r;
    pg.vertex(0, x, y);
    pg.vertex(h, x, y);
  }
  pg.endShape();
}

void drawContactArrow(PGraphics pg) {
  // 값이 유효한지 확인
  if (values == null || values.length >= 6+sensorNum) {
  

  // Force, Z, Cos, Sin 값을 파싱
  float force = float(values[sensorNum]);
  float z = float(values[sensorNum+1]);
  float cosValue = float(values[sensorNum+2]);
  float sinValue = -float(values[sensorNum+3]);

  // 화살표의 길이와 방향 계산
  float arrowLength = force*30; // Force를 화살표 길이에 반영
  float xDirection = (radi+4) * cosValue;
  float yDirection = (radi+4) * sinValue;
  float zDirection = z;


  // 화살표 그리기
  pg.pushMatrix();
  pg.fill(255, 0, 0);
  pg.translate(pg.width / 2 - zlength / 2, pg.height / 2);
  pg.translate(zDirection, -xDirection,-yDirection);
  float angle = atan2(yDirection, xDirection); // 방향에 따른 각도 계산
  pg.rotateX(angle); // 화살표 회전
  cone(pg, 4, 10);
  pg.fill(255, 0, 0); // 빨간색
  cylinder(pg, 2, -arrowLength);
  
  pg.popMatrix();
}
}

void draw2DTextOverlay(PGraphics pg) {
  String[] labels = {"Force: ", "   Z    : ", "  Cos   : ", "  Sin   : ", "Theta : "}; 
  int textGap = 20; // 텍스트 간의 수직 간격
  int valueOffset = 60; // 값의 수평 위치 오프셋
  pg.pushMatrix();
  pg.camera(); // Reset to default camera for 2D overlay
  pg.noLights(); // Disable lights for 2D overlay
  pg.fill(255);
  pg.textSize(16);
  pg.textAlign(RIGHT, BOTTOM);

  for (int i = 0; i < labels.length; i++) {
    int yPosition = pg.height - textGap * (labels.length - i);
    pg.text(labels[i], pg.width - valueOffset, yPosition);
    String valueToShow = "";
    if (i < 4) {
      valueToShow = values != null && values.length > i+sensorNum ? values[i+sensorNum] : "";
    } else if (values != null && values.length >= sensorNum+6) {
      float theta = atan2(float(values[sensorNum+3]), float(values[sensorNum+2]));
      theta = degrees(theta);
      theta = round(theta * 100) / 100.0;
      valueToShow = String.valueOf(theta);
    }
    pg.text(valueToShow, pg.width - 10, yPosition);
  }
  pg.popMatrix();
}




void drawAxis() {
  canvasAxis.beginDraw();  
  canvasAxis.background(0); 
  canvasAxis.camera(canvasAxis.width / 2, canvasAxis.height / 2, 150*tan(PI*30/180),
  canvasAxis.width / 2, canvasAxis.height / 2, 0, 1, 0, 0);
  
  canvasAxis.translate(canvasAxis.width / 2,canvasAxis.height / 2);
  canvasAxis.rotateX(angleX);
  canvasAxis.rotateY(angleY);
  canvasAxis.translate(-canvasAxis.width / 2,-canvasAxis.height / 2);
  
  canvasAxis.pushMatrix();
  canvasAxis.translate(canvasAxis.width / 2,canvasAxis.height / 2);
  drawAxis(canvasAxis,1.2);
  canvasAxis.popMatrix();

  canvasAxis.endDraw();
}




void drawAxis(PGraphics pg, float scale){
  drawArrow(pg, scale, color(255, 0, 0), HALF_PI, 0);
  drawArrow(pg, scale, color(0, 255, 0), 0, 2 * HALF_PI);
  drawArrow(pg, scale, color(0, 0, 255), 0, HALF_PI);
}

void drawArrow(PGraphics pg, float scale, int col, float rotX, float rotZ) {
  
  float arrowRadius = 1 * scale; // Arrow body radius
  float arrowLength = 50 * scale; // Arrow body length
  float coneRadius = 4 * scale; // Cone base radius
  float coneLength = 10 * scale; // Cone length
  
  pg.pushMatrix();
  pg.rotateX(rotX); // Rotate arrow
  pg.rotateZ(rotZ); // Rotate arrow
  pg.fill(col); // Arrow color
  cylinder(pg,arrowRadius, arrowLength);
  pg.fill(col); // Arrow color
  pg.translate(0, arrowLength / 2, 0); // Move to position for cone
  cone(pg, coneRadius, coneLength); // Draw arrow tip
  pg.fill(col); // Arrow color
  pg.rotateX(-rotX); // Rotate arrow
  pg.rotateZ(-rotZ); // Rotate arrow
  pg.popMatrix();
}




void cylinder(PGraphics pg,float radius, float cylHeight) {
  pg.noStroke();
  float angleStep = TWO_PI / 24;
  pg.beginShape(QUAD_STRIP);
  for (float angle = 0; angle < TWO_PI; angle += angleStep) {
    float x = cos(angle) * radius;
    float z = sin(angle) * radius;
    pg.vertex(x, 0, z);
    pg.vertex(x, cylHeight / 2, z);
  }
  pg.endShape(CLOSE);
}

void cone(PGraphics pg,float radius, float conHeight) {
  pg.noStroke();
  float angleStep = TWO_PI / 24;
  pg.beginShape(TRIANGLE_FAN);
  pg.vertex(0, conHeight / 2, 0); // Tip of the cone
  for (float angle = 0; angle < TWO_PI; angle += angleStep) {
    float x = cos(angle) * radius;
    float z = sin(angle) * radius;
    pg.vertex(x, -conHeight / 2, z);
  }
  pg.endShape(CLOSE);
}
