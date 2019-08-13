#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

extern osMessageQId ADCQueue1Handle;
extern osMessageQId ADCQueue2Handle;
extern osMessageQId InterruptQueueHandle;
extern osMessageQId ChosenBallQueueHandle;
extern osThreadId controllerTaskHandle;
extern osMessageQId stateQueueHandle;
Model::Model() : modelListener(0)
{
	ballNbr = 0;
	power = 0;
	position = 0;
	minPower = 0;
	noSignal = 0;
}

void Model::tick()
{

	osEvent event;

	//read all events
	do{
		event = osMessageGet(InterruptQueueHandle,0);
		//if message
		if(event.status == osStatus::osEventMessage){
			//send the interrupt number
			modelListener->hardInterrupt(event.value.v);
		}
	}while(event.status == osStatus::osEventMessage);


	event = osMessageGet(ADCQueue1Handle,0);
	//read adc value
	if(event.status == osStatus::osEventMessage){
		modelListener->ADCValue(event.value.v);
		//there is a signal
		noSignal = 0;
	}
	else if(noSignal < MIN_TIME_WITHOUT_SIGNAL){
		//there is not a signal
		noSignal = noSignal + 1;
	}

	event = osMessageGet(ADCQueue2Handle,0);
	//read adc value
	if(event.status == osStatus::osEventMessage){
		setPosition(event.value.v);
	}

	//if no signal while MIN_TIME_WITHOUT_SIGNAL time
	if(noSignal == MIN_TIME_WITHOUT_SIGNAL){
		//all displayed value are 0
		modelListener->ADCValue(0);
		setPosition(0);
	}

	//update the screen
	modelListener->update();


}

void Model::setBallNbr(uint16_t ballNbr) {

	this->ballNbr = ballNbr;
}

uint16_t Model::getBallNbr() {
	return ballNbr;
}

void Model::setPower(uint16_t value) {
	power = value;
}

uint16_t Model::getPower() {
	return power;
}

void Model::setPosition(uint16_t value) {
	position = value;
}

uint16_t Model::getPosition() {
	return position;
}

void Model::newSignal() {
	osMessagePut(ChosenBallQueueHandle,ballNbr,0);
}

void Model::activateCalibration() {
	osThreadResume(controllerTaskHandle);
}

void Model::changeState(state enumState) {
	osMessagePut(stateQueueHandle,enumState,0);
	osThreadResume(controllerTaskHandle);
}

void Model::setMinPower(uint16_t value) {
	minPower = value;
}

int16_t Model::getMinPower() {
	return minPower;
}
