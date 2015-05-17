// This example shows how to use the Scratch data areas
// to communicate with an external application.
//
// In this example the sketch fetches the LED values from
// the scratch data area 1 and writes the current temperature
// to the scratch data area 2.

String beanName = "Bean";
const uint8_t ledScratch = 1;
const uint8_t temperatureScratch = 2;

void setup() {
	// Setup bean
	Bean.setBeanName(beanName);
	Bean.enableWakeOnConnect(true);

	// Reset the scratch data area 1.
	uint8_t resetLedBuffer[] = {0, 0, 0};
	Bean.setScratchData(ledScratch, resetLedBuffer, 3);
}

// the loop routine runs over and over again forever:
void loop() {
	bool connected = Bean.getConnectionState();

	if(connected) {
                AccelerationReading acceleration = Bean.getAcceleration();
  
  		// Write current temperature to a scratch data area.
//		uint8_t temperatureBuffer[1];
//		temperatureBuffer[0] = Bean.getTemperature();
		uint8_t accelerationBuffer[3];
                accelerationBuffer[0] = Bean.getAccelerationX();
                accelerationBuffer[1] = Bean.getAccelerationY();
                accelerationBuffer[2] = Bean.getAccelerationZ();

		Bean.setScratchData(temperatureScratch, accelerationBuffer, 3);

		// Update LEDs
		ScratchData receivedData = Bean.readScratchData(ledScratch);

		uint8_t redLed = receivedData.data[0];
		uint8_t greenLed = receivedData.data[1];
		uint8_t blueLed = receivedData.data[2];

		Bean.setLed(redLed, greenLed, blueLed);
	}
	else {
		// Turn LED off and put to sleep.
		Bean.setLed(0, 0, 0);
		Bean.sleep(0xFFFFFFFF);
	}
}

