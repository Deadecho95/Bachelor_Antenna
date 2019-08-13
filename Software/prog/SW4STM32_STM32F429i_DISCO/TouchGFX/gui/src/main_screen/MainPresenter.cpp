#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>

MainPresenter::MainPresenter(MainView& v)
    : view(v)
{
     powerLPDA = 0;
     powerLOOP = 0;
}

void MainPresenter::activate()
{
	model->changeState(state::startReception);
}

void MainPresenter::deactivate()
{

}

void MainPresenter::update() {

	//set the view
	view.setBallNbr(model->getBallNbr());

	//calculate the LPDA power with the adc value
	powerLPDA = model->getPower()/SLOPE_mVDBm-MIN_LT5537;
	view.setPower(powerLPDA);

	//calculate the LPDA power with the adc value
	powerLOOP = model->getPosition()/SLOPE_mVDBm-MIN_LT5537;
	view.setPosition(powerLOOP);

	//set the progress bar
	if(powerLPDA > -RECEPTION_LIMIT){
		view.setPowerBar(-((-powerLPDA-MAX_POWER)*(100/(-(model->getMinPower()/SLOPE_mVDBm-MIN_LT5537)-MAX_POWER))-100));
	}
	else {
		view.setPowerBar(0);
	}
}

void MainPresenter::btnPlusPressed() {


	int val = (model->getBallNbr()+1)%(MAX_BALL+1);
	model->setBallNbr(val);
}

void MainPresenter::btnMinusPressed() {

	int16_t val = model->getBallNbr()-1;
	if(val < 0){
		val = MAX_BALL;
	}
	model->setBallNbr(val);

}

void MainPresenter::hardInterrupt(uint16_t interruptNumber){
	uint16_t val;

	switch (interruptNumber) {
		case interrupt::RECEIVED_SIGNAL:
			model->newSignal();
			break;

		case interrupt::BUTTON1press:
			//set new ball nbr
			model->setBallNbr((model->getBallNbr()+1)%(MAX_BALL+1));
			break;

		case interrupt::BUTTON2press:
			//set new ball nbr
			val = (model->getBallNbr()-1);
			if(val < 0){
				val = MAX_BALL;
			}
			model->setBallNbr(val);
			break;

		case interrupt::BLUE_BUTTONpress:
			//make screen change
			view.handleKeyEvent(interrupt::BLUE_BUTTONpress);
			break;
		default:
			break;
	}
}

void MainPresenter::ADCValue(uint16_t value) {
	model->setPower(value);
}
