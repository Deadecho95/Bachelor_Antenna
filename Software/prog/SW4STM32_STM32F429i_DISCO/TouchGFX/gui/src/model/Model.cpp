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
}

void Model::tick()
{
	osEvent event;
	do{
		event = osMessageGet(InterruptQueueHandle,0);
		if(event.status == osStatus::osEventMessage){
			modelListener->hardInterrupt(event.value.v);
		}
	}while(event.status == osStatus::osEventMessage);

	event = osMessageGet(ADCQueue1Handle,0);
	if(event.status == osStatus::osEventMessage){
		modelListener->ADCValue(event.value.v);
	}

	event = osMessageGet(ADCQueue2Handle,0);
	if(event.status == osStatus::osEventMessage){
		setPosition(event.value.v);
	}

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
		osThreadResume(controllerTaskHandle);
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
