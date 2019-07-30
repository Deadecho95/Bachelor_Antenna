#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

extern osMessageQId ADCQueue1Handle;
extern osMessageQId ADCQueue2Handle;
extern osMessageQId InterruptQueueHandle;
extern osMessageQId ChosenBallQueueHandle;
Model::Model() : modelListener(0)
{
	ballNbr = 0;
	power = 0;
	newSignaliscomming = 0;
}

void Model::tick()
{
	osEvent event = osMessageGet(InterruptQueueHandle,NULL);
	if(event.status == osStatus::osEventMessage){
		modelListener->hardButtonPressed(event.value.v);
	}

	modelListener->update();

}

void Model::setBallNbr(uint16_t ballNbr) {

	if(newSignaliscomming){
		osMessagePut(ChosenBallQueueHandle,ballNbr,NULL);
		newSignaliscomming = 0;
	}
	this->ballNbr = ballNbr;
}

int Model::getBallNbr() {
	return ballNbr;
}

void Model::setPower(uint16_t value) {
	power = value;
}

int Model::getPower() {
	return power;
}

void Model::newSignal() {
	newSignaliscomming =1;
}
