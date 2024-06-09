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


	Gpio getCommsLedPin() {
	return Gpio::E7;
}

Gpio getRunningLedPin() {
	return Gpio::G1;
}

Gpio getWarningLedPin() {
	return Gpio::E8;
}

static void setInjectorPins() {

	engineConfiguration->injectionPins[0] = Gpio::G7;
	engineConfiguration->injectionPins[1] = Gpio::G8;
	engineConfiguration->injectionPins[2] = Gpio::D11;
	engineConfiguration->injectionPins[3] = Gpio::D10;
}



static void setIgnitionPins() {

	engineConfiguration->ignitionPins[0] = Gpio::E2;
	engineConfiguration->ignitionPins[1] = Gpio::E5;
	engineConfiguration->ignitionPins[2] = Gpio::E4;
	engineConfiguration->ignitionPins[3] = Gpio::E3;
}


static void setupDefaultSensorInputs() {
	// trigger inputs, hall
	engineConfiguration->triggerInputPins[0] = Gpio::E14;
	engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;
	engineConfiguration->camInputs[0] = Gpio::E15;

	engineConfiguration->tps1_1AdcChannel = EFI_ADC_4;

    	engineConfiguration->map.sensor.hwChannel = EFI_ADC_2;

	engineConfiguration->afr.hwChannel = EFI_ADC_0;

	engineConfiguration->clt.adcChannel = EFI_ADC_12;
	engineConfiguration->iat.adcChannel = EFI_ADC_13;
	engineConfiguration->clt.config.bias_resistor = 2700;
	engineConfiguration->iat.config.bias_resistor = 2700;
}

void boardInitHardware() {
	
	boardOnConfigurationChange(nullptr);
}



void setBoardConfigOverrides() {

	
	engineConfiguration->etbIo[0].controlPin = Gpio::C8; // etb pwm
	engineConfiguration->etbIo[0].directionPin1 = Gpio::A9; // ebt dir
	engineConfiguration->etbIo[0].disablePin = Gpio::A8; // etb dis
	engineConfiguration->vrThreshold[0].pin = Gpio::Unassigned;
	engineConfiguration->vrThreshold[1].pin = Gpio::Unassigned;

        //setHellenEnPin(Gpio::H144_GP_IO7);


	// hellenMegaSdWithAccelerometer();
	engineConfiguration->spi1mosiPin = Gpio::B5;
	engineConfiguration->spi1misoPin = Gpio::B4;
	engineConfiguration->spi1sckPin = Gpio::B3;
	engineConfiguration->is_enabled_spi_1 = true;
	
	engineConfiguration->sdCardSpiDevice = SPI_DEVICE_1;

	engineConfiguration->accelerometerSpiDevice = SPI_DEVICE_1;
	engineConfiguration->accelerometerCsPin = Gpio::B7;

	engineConfiguration->binarySerialRxPin = Gpio::D6;
	engineConfiguration->binarySerialTxPin = Gpio::D5;
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

	engineConfiguration->vbattAdcChannel = EFI_ADC_5;

	engineConfiguration->adcVcc = 3.29f;

	setInjectorPins();
	setIgnitionPins();
	setledsPins();

	
	engineConfiguration->lps25BaroSensorScl = Gpio::B10; // sethellenmmbaro
	engineConfiguration->lps25BaroSensorSda = Gpio::B11;
    	
	
	engineConfiguration->enableSoftwareKnock = true;

//    	engineConfiguration->boardUseTempPullUp = true;

	//setHellenCan();
	engineConfiguration->canTxPin = Gpio::D1;
	engineConfiguration->canRxPin = Gpio::D0;

	engineConfiguration->vehicleSpeedSensorInputPin = Gpio::F5;
	engineConfiguration->clutchDownPin = Gpio::F3;

	engineConfiguration->acRelayPin = Gpio::G5;
	engineConfiguration->acSwitch = Gpio::E13;

	engineConfiguration->fuelPumpPin = Gpio::G2;
	engineConfiguration->fanPin = Gpio::G4;
	engineConfiguration->enableFan1WithAc = true;
        engineConfiguration->boostControlPin = Gpio::C7;	
	engineConfiguration->idle.solenoidPin = Gpio::C6;
	// engineConfiguration->tachOutputPin = Gpio::B8;
	// engineConfiguration->alternatorControlPin = Gpio::G6;
	engineConfiguration->malfunctionIndicatorPin = Gpio::G3;

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
		Gpio::G7, 
		Gpio::G8,
		Gpio::D11,
		Gpio::D10,
		Gpio::C13,
		Gpio::E5,
		Gpio::E4,
		Gpio::E3,
		Gpio::E2,
		Gpio::B8,
		Gpio::C6,
		Gpio::C7,
		Gpio::C8,
		Gpio::D14,
		Gpio::D15,
		Gpio::G5,
		Gpio::G3,
		Gpio::G4,
		Gpio::G2,
		Gpio::G6,
};

int getBoardMetaOutputsCount() {
    return efi::size(OUTPUTS);
}

Gpio* getBoardMetaOutputs() {
    return OUTPUTS;
}
