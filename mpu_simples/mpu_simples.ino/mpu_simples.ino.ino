#include<Wire.h>

//Endereco I2C do MPU6050
const int MPU=0x68;  
//Variaveis para armazenar valores dos sensores
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

#define      n     20        //número de pontos da média móvel 


// ===============================================================================
// --- Protótipo da Função ---
long moving_average();       //Função para filtro de média móvel


int       numbersAcX[n];        //vetor com os valores para média móvel
int       numbersAcY[n];
int       numbersAcZ[n];
int       numbersGyX[n];
int       numbersGyY[n];
int       numbersGyZ[n];
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
}
void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);  
  //Armazena o valor dos sensores nas variaveis correspondentes
  AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)




   //Serial.print(filtrado);


  //Envia valor X do acelerometro para a serial e o LCD
  Serial.print("AcX = "); Serial.print(mediaAcX(AcX));

  //Envia valor Y do acelerometro para a serial e o LCD
  Serial.print(" | AcY = "); Serial.print(mediaAcY(AcY));

  //Envia valor Z do acelerometro para a serial e o LCD
  Serial.print(" | AcZ = "); Serial.print(mediaAcZ(AcZ));
  //Envia valor X do giroscopio para a serial e o LCD
  Serial.print(" | GyX = "); Serial.print(mediaGyX(GyX));
 
  //Envia valor Y do giroscopio para a serial e o LCD  
  Serial.print(" | GyY = "); Serial.print(mediaGyY(GyY));

  //Envia valor Z do giroscopio para a serial e o LCD
  Serial.print(" | GyZ = "); Serial.println(mediaGyZ(GyZ));

  //Aguarda 300 ms e reinicia o processo
  delay(50);

}

long mediaAcX(int original)
{
   //desloca os elementos do vetor de média móvel
   for(int i= n-1; i>0; i--) numbersAcX[i] = numbersAcX[i-1];
   numbersAcX[0] = original; //posição inicial do vetor recebe a leitura original
   long acc = 0;          //acumulador para somar os pontos da média móvel
   for(int i=0; i<n; i++) acc += numbersAcX[i]; //faz a somatória do número de pontos
   return acc/n;  //retorna a média móvel 
}

long mediaAcY(int original)
{
   //desloca os elementos do vetor de média móvel
   for(int i= n-1; i>0; i--) numbersAcY[i] = numbersAcY[i-1];
   numbersAcY[0] = original; //posição inicial do vetor recebe a leitura original
   long acc = 0;          //acumulador para somar os pontos da média móvel
   for(int i=0; i<n; i++) acc += numbersAcY[i]; //faz a somatória do número de pontos
   return acc/n;  //retorna a média móvel 
}
long mediaAcZ(int original)
{
   //desloca os elementos do vetor de média móvel
   for(int i= n-1; i>0; i--) numbersAcZ[i] = numbersAcZ[i-1];
   numbersAcZ[0] = original; //posição inicial do vetor recebe a leitura original
   long acc = 0;          //acumulador para somar os pontos da média móvel
   for(int i=0; i<n; i++) acc += numbersAcZ[i]; //faz a somatória do número de pontos
   return acc/n;  //retorna a média móvel 
}

long mediaGyX(int original)
{
   //desloca os elementos do vetor de média móvel
   for(int i= n-1; i>0; i--) numbersGyX[i] = numbersGyX[i-1];
   numbersGyX[0] = original; //posição inicial do vetor recebe a leitura original
   long acc = 0;          //acumulador para somar os pontos da média móvel
   for(int i=0; i<n; i++) acc += numbersGyX[i]; //faz a somatória do número de pontos
   return acc/n;  //retorna a média móvel 
}
long mediaGyY(int original)
{
   //desloca os elementos do vetor de média móvel
   for(int i= n-1; i>0; i--) numbersGyY[i] = numbersGyY[i-1];
   numbersGyY[0] = original; //posição inicial do vetor recebe a leitura original
   long acc = 0;          //acumulador para somar os pontos da média móvel
   for(int i=0; i<n; i++) acc += numbersGyY[i]; //faz a somatória do número de pontos
   return acc/n;  //retorna a média móvel 
}
long mediaGyZ(int original)
{
   //desloca os elementos do vetor de média móvel
   for(int i= n-1; i>0; i--) numbersGyZ[i] = numbersGyZ[i-1];
   numbersGyZ[0] = original; //posição inicial do vetor recebe a leitura original
   long acc = 0;          //acumulador para somar os pontos da média móvel
   for(int i=0; i<n; i++) acc += numbersGyZ[i]; //faz a somatória do número de pontos
   return acc/n;  //retorna a média móvel 
}
