import processing.serial.*;
Serial myPort;
String serialData = "";
String[] values;
float[][] sensorGroups = new float[layers][spheresPerLayer]; 
int sensorNum = layers*spheresPerLayer;

float force, z, cosValue, sinValue;

void serialEvent(Serial p) {
  serialData = p.readStringUntil('\n');
  if (serialData != null) {
    serialData = trim(serialData);
    values = split(serialData, ' ');
    println(serialData);

    if (values.length >= sensorNum) {
      // 첫 48개의 값은 센서 데이터로 처리
      for (int i = 0; i < sensorNum; i++) {
        int groupIndex = i / 12; // 그룹 인덱스 (0, 1, 2, 3 중 하나)
        int dataIndex = i % 12; // 데이터 인덱스 (0에서 11 사이)
        sensorGroups[groupIndex][dataIndex] = float(values[i]);
      } 
    }
    if(values.length >= sensorNum+6){
      // 마지막 4개의 값은 force, z, cosValue, sinValue로 처리
      force = float(values[sensorNum]);
      z = float(values[sensorNum+1]);
      cosValue = float(values[sensorNum+2]);
      sinValue = float(values[sensorNum+3]);          
    }
  }
}
