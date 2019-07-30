#include <gui/menu_screen/MenuView.hpp>
#include <gui/menu_screen/MenuPresenter.hpp>

MenuPresenter::MenuPresenter(MenuView& v)
    : view(v)
{
}

void MenuPresenter::activate()
{
	model->changeState(state::menu);
}

void MenuPresenter::deactivate()
{

}

void MenuPresenter::calibrate()
{
	model->changeState(state::calibrate);
}

void MenuPresenter::hardInterrupt(uint16_t interruptNumber){

	switch (interruptNumber) {
		case interrupt::RECEIVED_SIGNAL:
			break;

		case interrupt::BUTTON1press:
			calibrate();
			break;

		case interrupt::BUTTON2press:
			//make screen change
			view.handleKeyEvent(interrupt::BUTTON2press);
			break;

		case interrupt::BLUE_BUTTONpress:

			break;
		default:
			break;
	}
}

void MenuPresenter::ADCValue(uint16_t value) {
	model->setMinPower(value);
}
