/*
  Redox Potential Meter — portfolio implementation
  Author: Shoaib Akhtar

  IMPORTANT:
  The electrode pair must connect through a suitable high-input-impedance,
  isolated signal-conditioning front end. Do not connect electrochemical
  electrodes directly to an Arduino analogue input.
*/

const uint8_t SIGNAL_PIN = A0;
const unsigned long REPORT_INTERVAL_MS = 1000;
const uint16_t SAMPLES_PER_READING = 50;

// Adjust these values for the selected board and measured reference voltage.
const float ADC_REFERENCE_V = 5.000;
const float ADC_MAX_COUNT = 1023.0;

// Replace these placeholder values with results from the calibration procedure.
const float ZERO_ORP_OUTPUT_V = 2.500;
const float ORP_MV_PER_OUTPUT_V = 1000.0;
const float CALIBRATION_OFFSET_MV = 0.0;

unsigned long previousReportMs = 0;

float readMeanAdc() {
  unsigned long total = 0;

  for (uint16_t sample = 0; sample < SAMPLES_PER_READING; sample++) {
    total += analogRead(SIGNAL_PIN);
    delay(2);
  }

  return static_cast<float>(total) / SAMPLES_PER_READING;
}

float adcToVoltage(float adcMean) {
  return adcMean * ADC_REFERENCE_V / ADC_MAX_COUNT;
}

float voltageToOrpMv(float signalVoltage) {
  return ((signalVoltage - ZERO_ORP_OUTPUT_V) * ORP_MV_PER_OUTPUT_V)
         + CALIBRATION_OFFSET_MV;
}

void setup() {
  Serial.begin(115200);
  pinMode(SIGNAL_PIN, INPUT);
  Serial.println("time_ms,adc_mean,signal_voltage_v,orp_mv");
}

void loop() {
  const unsigned long now = millis();

  if (now - previousReportMs >= REPORT_INTERVAL_MS) {
    previousReportMs = now;

    const float adcMean = readMeanAdc();
    const float signalVoltage = adcToVoltage(adcMean);
    const float orpMv = voltageToOrpMv(signalVoltage);

    Serial.print(now);
    Serial.print(',');
    Serial.print(adcMean, 2);
    Serial.print(',');
    Serial.print(signalVoltage, 4);
    Serial.print(',');
    Serial.println(orpMv, 2);
  }
}
