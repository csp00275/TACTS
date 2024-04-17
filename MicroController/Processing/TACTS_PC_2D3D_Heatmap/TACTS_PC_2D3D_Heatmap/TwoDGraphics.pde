
PGraphics canvas2D;

void draw2DGraphics() {
  canvas2D.beginDraw();
  canvas2D.background(255); // 2D 캔버스 배경색
  ToFPoint(canvas2D);
  drawContactPoint(canvas2D);

  canvas2D.endDraw();
}

void ToFPoint(PGraphics pg){
  for (int i = 0; i < layers; i++) {
    for (int j = 0; j < spheresPerLayer; j++) {
      float radius  = 5;
      float x = j * (canvas2D.width / spheresPerLayer)+ canvas3D.width / 24;
      float y = canvas2D.height * (40*i+20)/160;
      pg.fill(0, 0, 255); //blue
      pg.circle(x, y, radius * 2); 
    }
  }
}

void drawContactPoint(PGraphics pg) {
  // 데이터 유효성 검사를 더 엄격하게 처리
  if (values == null || values.length < sensorNum + 6) {
    // 유효한 데이터가 없으면 함수에서 빠르게 반환하여 그리기를 건너뜀
    return;
  }

  // 이하 코드는 데이터가 유효할 때만 실행됨
  float force = float(values[sensorNum]);
  float z = float(values[sensorNum+1]);
  float cosValue = float(values[sensorNum+2]);
  float sinValue = -float(values[sensorNum+3]);

  // 데이터를 사용한 그리기 로직
  float radius  = force*2+2;
  float angle = atan2(sinValue, cosValue);
  angle *= (180.0 / PI); // 라디안을 도 단위로 변환
  angle += 180;
  float x = pg.width * angle/360;
  float y = pg.height * z/160;

  pg.fill(255, 0, 0); // 빨간색으로 유지
  pg.circle(x, y, radius * 2);   
}
