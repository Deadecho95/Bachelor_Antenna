#include <gui/main_screen/MainView.hpp>

MainView::MainView()
{

}

void MainView::setupScreen()
{
    MainViewBase::setupScreen();
}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}

std::array<bool, NBR_OF_BUTTONS> MainView::getButtonsState() {

	std::array<bool, NBR_OF_BUTTONS> buttonsState;
	buttonsState[0] = buttonPlus.getPressedState();
	buttonsState[1] = buttonPlus.getPressedState();

	return buttonsState;
}

void MainView::setBallNbr(uint16_t nbr) {
	Unicode::snprintf(ballNbrBuffer,BALLNBR_SIZE, "%d",nbr);
	ballNbr.invalidate();
}

void MainView::btnMinusPressed() {
	presenter->btnMinusPressed();
}

void MainView::btnPlusPressed() {
	presenter->btnPlusPressed();
}

void MainView::setPower(int16_t power) {
	Unicode::snprintf(powerValueBuffer,POWERVALUE_SIZE, "%d",power);
	powerValue.invalidate();
}

void MainView::setPosition(int16_t position) {
	Unicode::snprintf(positionValueBuffer,POSITIONVALUE_SIZE, "%d",position);
	positionValue.invalidate();

}

void MainView::setPowerBar(uint16_t value) {
	boxProgress1.setValue(value);
}
