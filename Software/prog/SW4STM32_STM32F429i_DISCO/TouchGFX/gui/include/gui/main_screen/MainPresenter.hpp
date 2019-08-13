#ifndef MAIN_PRESENTER_HPP
#define MAIN_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MainView;

class MainPresenter : public Presenter, public ModelListener
{
public:
    MainPresenter(MainView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~MainPresenter() {};

    /**
      * @brief Update the screen
      * @param None
      * @retval None
      */
    void update();

    /**
      * @brief plus button pressed
      * @param None
      * @retval None
      */
	void btnPlusPressed();

    /**
      * @brief Minus button pressed
      * @param None
      * @retval None
      */
	void btnMinusPressed();

    /**
      * @brief an interruption occured
      * @param interruptNumber : the number of the interrupt
      * @retval None
      */
	void hardInterrupt(uint16_t interruptNumber);

    /**
      * @brief set the adc Value
      * @param value from the ADC
      * @retval None
      */
	void ADCValue(uint16_t value);

private:
    MainPresenter();

    MainView& view;
    double powerLPDA;
    double powerLOOP;
};


#endif // MAIN_PRESENTER_HPP
