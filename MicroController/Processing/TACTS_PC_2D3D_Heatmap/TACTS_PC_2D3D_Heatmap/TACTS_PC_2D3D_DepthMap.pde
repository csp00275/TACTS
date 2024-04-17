float[][] spherePositions;  // 구의 위치를 저장하는 2차원 배열
int spheresPerLayer = 12;
int layers = 4;
float angleStep = TWO_PI / spheresPerLayer;

PFont font; // 폰트를 저장할 전역 변수


void setup() {
  size(640, 960, P2D); // 메인 창 설정
  
  canvas3D = createGraphics(640, 480, P3D);
  canvasAxis = createGraphics(120, 120, P3D);
  canvas2D = createGraphics(640, 240, P2D);
  canvasHeatmap = createGraphics(640, 240, P2D);
 
  printArray(Serial.list());
 
  myPort = new Serial(this, Serial.list()[0], 115200); 
  myPort.bufferUntil('\n');
  
  font = createFont("Arial", 20, true); // 폰트 생성

}

void draw() {
  draw3DGraphics(); // 3D 그래픽 그리기
  drawAxis();
  draw2DGraphics();
  drawHeatmap();
  
  image(canvas3D, 0, 0); // 상단에 3D 캔버스 표시
  image(canvasAxis, 0, 360); // 상단에 3D 캔버스 표시
  image(canvas2D, 0, 480); // 하단에 2D 캔버스 표시
  image(canvasHeatmap, 0, 720); // 하단에 2D 캔버스 표시  
  ScreenRotate();  
  
}
