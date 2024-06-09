/**
 * @file board_configuration.cpp
 *
 *
 * @brief Configuration defaults for the 4chan board
 *
 * @author andreika <prometheus.pcb@gmail.com>
 * @author Andrey Belomutskiy, (c) 2012-2020
 */

#include "pch.h"
#include "defaults.h"


static void setledsPins() {

	Gpio getCommsLedPin() {
	return H144_LED3_BLUE;
}

Gpio getRunningLedPin() {
	return H144_LED2_GREEN;
}

Gpio getWarningLedPin() {
	return H144_LED4_YELLOW;
}

}


static void setInjectorPins() {

	engineConfiguration->injectionPins[0] = Gpio::H144_LS_1;
	engineConfiguration->injectionPins[1] = Gpio::H144_LS_2;
	engineConfiguration->injectionPins[2] = Gpio::H144_LS_3;
	engineConfiguration->injectionPins[3] = Gpio::H144_LS_4;
}



static void setIgnitionPins() {

	engineConfiguration->ignitionPins[0] = Gpio::H144_IGN_5;
	engineConfiguration->ignitionPins[1] = Gpio::H144_IGN_2;
	engineConfiguration->ignitionPins[2] = Gpio::H144_IGN_3;
	engineConfiguration->ignitionPins[3] = Gpio::H144_IGN_4;
}


static void setupDefaultSensorInputs() {
	// trigger inputs, hall
	engineConfiguration->triggerInputPins[0] = Gpio::H144_IN_D_3;
	engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;
	engineConfiguration->camInputs[0] = Gpio::H144_IN_D_4;

	engineConfiguration->tps1_1AdcChannel = H144_IN_TPS;

    	engineConfiguration->map.sensor.hwChannel = H144_IN_MAP3;

	engineConfiguration->afr.hwChannel = H144_IN_O2S;

	engineConfiguration->clt.adcChannel = H144_IN_CLT;
	engineConfiguration->iat.adcChannel = H144_IN_IAT;
	engineConfiguration->clt.config.bias_resistor = 2700;
	engineConfiguration->iat.config.bias_resistor = 2700;
}

void boardInitHardware() {
	
	boardOnConfigurationChange(nullptr);
}



void setBoardConfigOverrides() {

	
	engineConfiguration->etbIo[0].controlPin = Gpio::H144_OUT_PWM4; // etb pwm
	engineConfiguration->etbIo[0].directionPin1 = Gpio::H144_OUT_IO2; // ebt dir
	engineConfiguration->etbIo[0].disablePin = Gpio::H144_OUT_IO12; // etb dis
	engineConfiguration->vrThreshold[0].pin = Gpio::Unassigned;
	engineConfiguration->vrThreshold[1].pin = Gpio::Unassigned;

        //setHellenEnPin(Gpio::H144_GP_IO7);


	// hellenMegaSdWithAccelerometer();
	engineConfiguration->spi1mosiPin = Gpio::H_SPI1_MOSI;
	engineConfiguration->spi1misoPin = Gpio::H_SPI1_MISO;
	engineConfiguration->spi1sckPin = Gpio::H_SPI1_SCK;
	engineConfiguration->is_enabled_spi_1 = true;
	
	engineConfiguration->sdCardSpiDevice = SPI_DEVICE_1;

	engineConfiguration->accelerometerSpiDevice = SPI_DEVICE_1;
	engineConfiguration->accelerometerCsPin = Gpio::H_SPI1_CS2;

	engineConfiguration->binarySerialRxPin = H144_UART2_RX;
	engineConfiguration->binarySerialTxPin = H144_UART2_TX;
	// engineConfiguration->tunerStudioSerialSpeed = 115200;


}

/**
 * @brief   Board-specific configuration defaults.
 *
 * See also setDefaultEngineConfiguration
 *
 * @todo    Add your board-specific code, if any.
 */
void setBoardDefaultConfiguration() {

	//setHellenVbatt();
	engineConfiguration->analogInputDividerCoefficient = 2.0f;
	
	engineConfiguration->vbattDividerCoeff = (33 + 6.8) / 6.8; // 5.835

	engineConfiguration->vbattAdcChannel = H144_IN_VBATT;

	engineConfiguration->adcVcc = 3.29f;

	setInjectorPins();
	setIgnitionPins();
	setledsPins();

	
	engineConfiguration->lps25BaroSensorScl = Gpio::B10; // sethellenmmbaro
	engineConfiguration->lps25BaroSensorSda = Gpio::B11;
    	
	
	engineConfiguration->enableSoftwareKnock = true;

//    	engineConfiguration->boardUseTempPullUp = true;

	//setHellenCan();
	engineConfiguration->canTxPin = H176_CAN_TX;
	engineConfiguration->canRxPin = H176_CAN_RX;

	engineConfiguration->vehicleSpeedSensorInputPin = Gpio::H144_IN_SENS3;
	engineConfiguration->clutchDownPin = Gpio::H144_IN_SENS1;

	engineConfiguration->acRelayPin = Gpio::H144_OUT_IO4;
	engineConfiguration->acSwitch = Gpio::H144_IN_D_2;

	engineConfiguration->fuelPumpPin = Gpio::H144_OUT_IO11;
	engineConfiguration->fanPin = Gpio::H144_OUT_IO8;
	engineConfiguration->enableFan1WithAc = true;
        engineConfiguration->boostControlPin = Gpio::H144_OUT_PWM3;	
	engineConfiguration->idle.solenoidPin = Gpio::H144_OUT_PWM2;
	// engineConfiguration->tachOutputPin = Gpio::H144_IGN_6;
	// engineConfiguration->alternatorControlPin = Gpio::H144_OUT_IO13;
	engineConfiguration->malfunctionIndicatorPin = Gpio::H144_OUT_IO7;

	// "required" hardware is done - set some reasonable defaults
	setupDefaultSensorInputs();

	engineConfiguration->cylindersCount = 4;
	engineConfiguration->firingOrder = FO_1_3_4_2;

	engineConfiguration->injector.flow = 238.0;
	engineConfiguration->map.sensor.type = MT_DENSO183;
	engineConfiguration->ignitionMode = IM_ONE_COIL;

	setAlgorithm(LM_SPEED_DENSITY);	

	
}


static Gpio OUTPUTS[] = {
		Gpio::H144_LS_1, 
		Gpio::H144_LS_2,
		Gpio::H144_LS_3,
		Gpio::H144_LS_4,
		Gpio::H144_IGN_1,
		Gpio::H144_IGN_2,
		Gpio::H144_IGN_3,
		Gpio::H144_IGN_4,
		Gpio::H144_IGN_5,
		Gpio::H144_IGN_6,
		Gpio::H144_OUT_PWM2,
		Gpio::H144_OUT_PWM3,
		Gpio::H144_OUT_PWM5,
		Gpio::H144_OUT_PWM6,
		Gpio::H144_OUT_PWM7,
		Gpio::H144_OUT_IO4,
		Gpio::H144_OUT_IO7,
		Gpio::H144_OUT_IO8,
		Gpio::H144_OUT_IO11,
		Gpio::H144_OUT_IO13,
};

int getBoardMetaOutputsCount() {
    return efi::size(OUTPUTS);
}

Gpio* getBoardMetaOutputs() {
    return OUTPUTS;
}
