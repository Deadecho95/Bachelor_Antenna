#ifndef MENU_PRESENTER_HPP
#define MENU_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MenuView;

class MenuPresenter : public Presenter, public ModelListener
{
public:
    MenuPresenter(MenuView& v);

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

    virtual ~MenuPresenter() {};

    /**
      * @brief an interruption occured
      * @param interruptNumber : the number of the interrupt
      * @retval None
      */
	void hardInterrupt(uint16_t interruptNumber);

    /**
      * @brief calibrate the hard comparator
      * @param None
      * @retval None
      */
	void calibrate();

    /**
      * @brief set the adc Value
      * @param value from the ADC
      * @retval None
      */
    void ADCValue(uint16_t value);

private:
    MenuPresenter();

    MenuView& view;
};


#endif // MENU_PRESENTER_HPP
