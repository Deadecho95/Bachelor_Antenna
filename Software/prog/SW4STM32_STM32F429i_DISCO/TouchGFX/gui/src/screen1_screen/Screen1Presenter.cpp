#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{
}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::update() {

	//set the view
	view.setBallNbr(model->getBallNbr());
	view.setPower(model->getPower());
	view.setPosition(model->getPosition());
}

void Screen1Presenter::btnPlusPressed() {
	int val = (model->getBallNbr()+1)%16;
	model->setBallNbr(val);
}

void Screen1Presenter::btnMinusPressed() {
	int16_t val = model->getBallNbr()-1;
	if(val < 0){
		val = 15;
	}
	model->setBallNbr(val);

}

void Screen1Presenter::hardInterrupt(uint16_t interruptNumber){
	uint16_t val;

	switch (interruptNumber) {
		case interrupt::RECEIVED_SIGNAL:
			model->newSignal();
			break;

		case interrupt::BUTTON1press:
			model->setBallNbr((model->getBallNbr()+1)%MAX_BALL+1);
			break;

		case interrupt::BUTTON2press:
			val = (model->getBallNbr()-1);
			if(val < 0){
				val = MAX_BALL;
			}
			model->setBallNbr(val);
			break;

		case interrupt::BLUE_BUTTONpress:
			///test///
			model->newSignal();
			break;
		default:
			break;
	}
}
