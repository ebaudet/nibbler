#include "ANibblerGui.hpp"

// -- Constructors -------------------------------------------------------------

ANibblerGui::ANibblerGui() {
}

ANibblerGui::~ANibblerGui() {
}

ANibblerGui::ANibblerGui(ANibblerGui const &src) {
	*this = src;
}

// -- Operators ----------------------------------------------------------------

ANibblerGui &ANibblerGui::operator=(ANibblerGui const &rhs) {
	if ( this != &rhs ) {
		input = rhs.input;
	}
	return *this;
}

// -- Intput Part --------------------------------------------------------------

ANibblerGui::Input::Input()
: quit(false), direction(MOVE_LEFT), loadGuiID(NO_GUI_LOADED) {
}

ANibblerGui::Input::Input(ANibblerGui::Input const &src) {
	*this = src;
}

ANibblerGui::Input &ANibblerGui::Input::operator=(Input const &rhs) {
	if (this != &rhs) {
		quit = rhs.quit;
		direction = rhs.direction;
		loadGuiID = rhs.loadGuiID;
	}
	return *this;
}
