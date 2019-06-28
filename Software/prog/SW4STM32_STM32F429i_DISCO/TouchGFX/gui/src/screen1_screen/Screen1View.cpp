#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{

}

void Screen1View::tearDownScreen()
{

}

std::array<bool, NBR_OF_BUTTONS> Screen1View::getButtonsState() {

	std::array<bool, NBR_OF_BUTTONS> buttonsState;
	buttonsState[0] = buttonPlus.getPressedState();
	buttonsState[1] = buttonPlus.getPressedState();

	return buttonsState;
}

void Screen1View::setBallNbr(int nbr) {
	Unicode::snprintf(ballNbrBuffer,BALLNBR_SIZE, "%d",nbr);
	ballNbr.invalidate();
}

void Screen1View::btnMinusPressed() {
	presenter->btnMinusPressed();
}

void Screen1View::btnPlusPressed() {
	presenter->btnPlusPressed();
}

void Screen1View::setPower(int power) {
	Unicode::snprintf(powerValueBuffer,POWERVALUE_SIZE, "%d",power);
	powerValue.invalidate();

	boxProgress1.setValue(power);
}
