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

	//view.setPower();
	view.setBallNbr(model->getBallNbr());
	view.setPower(model->getPower());
}

void Screen1Presenter::btnPlusPressed() {
	int val = (model->getBallNbr()+1)%16;
	model->setBallNbr(val);
}

void Screen1Presenter::btnMinusPressed() {
	int val = (model->getBallNbr()-1)%16;
	if(val < 0){
		val = 15;
	}
	model->setBallNbr(val);

}

void Screen1Presenter::hardButtonPressed(uint16_t numberOfButtonpressed) {
	model->setPower(model->getPower()+10);
	switch (numberOfButtonpressed) {
		case interrupt::RECEIVED_SIGNAL:
			model->newSignal();
			break;
		default:
			break;
	}
}
