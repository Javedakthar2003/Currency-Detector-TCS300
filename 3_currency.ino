// Define color sensor pins

#define S0 8
#define S1 3
#define S2 5
#define S3 6
#define sensorOut 9

// Calibration Values
// Get these from Calibration Sketch

int redMin = 18;
int redMax = 209;
int greenMin = 20;
int greenMax = 223;
int blueMin = 14;
int blueMax = 165;

// Variables for Color Pulse Width Measurements

int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values

int redValue;
int greenValue;
int blueValue;

// Define color ranges for each currency
// Adjust the values based on your specific requirements

// Green color range for currency 1
int currency1GreenMin = 192;
int currency1GreenMax = 210;
int currency1RedMin = 213;
int currency1RedMax = 225;
int currency1BlueMin = 178;
int currency1BlueMax = 197;

// Blue color range for currency 2
int currency2GreenMin = 198;
int currency2GreenMax = 240;
int currency2RedMin = 195;
int currency2RedMax = 230;
int currency2BlueMin = 181;
int currency2BlueMax = 235;

// Red color range for currency 3
int currency3GreenMin = 180;
int currency3GreenMax = 219;
int currency3RedMin = 193;
int currency3RedMax = 225;
int currency3BlueMin = 185;
int currency3BlueMax = 225;

void setup() {

  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  
  // Set Frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop() {
  
  // Read red value
  redPW = getRedPW();
  // Map to value from 0-255
  redValue = map(redPW, redMin, redMax, 255, 0);
  // Delay to stabilize sensor
  delay(200);
  
  // Read green value
  greenPW = getGreenPW();
  // Map to value from 0-255
  greenValue = map(greenPW, greenMin, greenMax, 255, 0);
  // Delay to stabilize sensor
  delay(200);
  
  // Read blue value
  bluePW = getBluePW();
  // Map to value from 0-255
  blueValue = map(bluePW, blueMin, blueMax, 255, 0);
  // Delay to stabilize sensor
  delay(200);
  
  // Print output to Serial Monitor
  String detectedCurrency = detectCurrency(redValue, greenValue, blueValue);
  Serial.println("Detected currency: " + detectedCurrency);
}

// Function to read red Pulse Widths
int getRedPW() {

  // Set sensor to read red only
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read green Pulse Widths
int getGreenPW() {

  // Set sensor to read green only
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read blue Pulse Widths
int getBluePW() {

  // Set sensor to read blue only
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

String detectCurrency(int red, int green, int blue) {
  // Compare RGB values within the color ranges for each currency with +/- 10 tolerance
  if (green >= (currency1GreenMin - 10) && green <= (currency1GreenMax + 10) &&
      red >= (currency1RedMin - 10) && red <= (currency1RedMax + 10) &&
      blue >= (currency1BlueMin - 10) && blue <= (currency1BlueMax + 10)) {
    return "Currency 1";
  }
  else if (green >= (currency2GreenMin - 10) && green <= (currency2GreenMax + 10) &&
           red >= (currency2RedMin - 10) && red <= (currency2RedMax + 10) &&
           blue >= (currency2BlueMin - 10) && blue <= (currency2BlueMax + 10)) {
    return "Currency 2";
  }
  else if (green >= (currency3GreenMin - 10) && green <= (currency3GreenMax + 10) &&
           red >= (currency3RedMin - 10) && red <= (currency3RedMax + 10) &&
           blue >= (currency3BlueMin - 10) && blue <= (currency3BlueMax + 10)) {
    return "Currency 3";
  }

  // No matching currency
  return "Unknown Currency";
}

