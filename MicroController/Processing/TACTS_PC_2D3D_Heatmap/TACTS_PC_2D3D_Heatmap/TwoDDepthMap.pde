PGraphics canvasHeatmap;

//float[][] sensorGroups = new float[layers][spheresPerLayer]; 

void drawHeatmap() {
  float maxVal = findMax(sensorGroups);
  float minVal = findMin(sensorGroups);

  canvasHeatmap.beginDraw();
  canvasHeatmap.background(255);
  canvasHeatmap.textAlign(CENTER, CENTER); // 텍스트를 셀의 중앙에 정렬
  canvasHeatmap.textSize(12); // 텍스트 크기 설정

  for (int j = 0; j < layers; j++) {
    for (int i = 0; i < spheresPerLayer; i++) {
      float scaledValue = scaleValue(sensorGroups[j][i], minVal, maxVal);
      color c = color((1 - scaledValue) * 255, 0,  scaledValue* 255);
      canvasHeatmap.fill(c);
      float cellX = i * (canvasHeatmap.width / spheresPerLayer);
      float cellY = j * (canvasHeatmap.height / layers);
      float cellWidth = canvasHeatmap.width / spheresPerLayer;
      float cellHeight = canvasHeatmap.height / layers;
      canvasHeatmap.rect(cellX, cellY, cellWidth, cellHeight);

      
      canvasHeatmap.fill(0); // 텍스트 색상 설정
      canvasHeatmap.text(nf(sensorGroups[j][i], 0, 2), cellX + cellWidth / 2, cellY + cellHeight / 2);
    }
  }
  canvasHeatmap.endDraw();
}
// 최대값과 최소값을 찾는 함수
float findMax(float[][] data) {
  float max = data[0][0];
  for (int i = 0; i < data.length; i++) {
    for (int j = 0; j < data[i].length; j++) {
      if (data[i][j] > max) {
        max = data[i][j];
      }
    }
  }
  return max;
}

float findMin(float[][] data) {
  float min = data[0][0];
  for (int i = 0; i < data.length; i++) {
    for (int j = 0; j < data[i].length; j++) {
      if (data[i][j] < min) {
        min = data[i][j];
      }
    }
  }
  return min;
}

// 데이터를 0과 1 사이로 스케일링하는 함수
float scaleValue(float value, float min, float max) {
  return (value - min) / (max - min);
}
