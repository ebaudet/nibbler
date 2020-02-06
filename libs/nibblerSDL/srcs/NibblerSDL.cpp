#include "NibblerSDL.hpp"
#include "Logging.hpp"

// -- Constructors -------------------------------------------------------------

NibblerSDL::NibblerSDL() :
_win(nullptr),
_event(new SDL_Event()) {
	// init logging
	#if DEBUG
		logging.setLoglevel(LOGDEBUG);
		logging.setPrintFileLine(LOGWARN, true);
		logging.setPrintFileLine(LOGERROR, true);
		logging.setPrintFileLine(LOGFATAL, true);
	#else
		logging.setLoglevel(LOGINFO);
	#endif
	logInfo("new SDL");
}

NibblerSDL::~NibblerSDL() {
	delete _event;
	logInfo("exit SDL");
	SDL_DestroyWindow(_win);
	SDL_Quit();
}

NibblerSDL::NibblerSDL(NibblerSDL const &src) {
	*this = src;
}

// -- Operators ----------------------------------------------------------------

NibblerSDL &NibblerSDL::operator=(NibblerSDL const &rhs) {
	if ( this != &rhs ) {
		_win = rhs._win;
		_surface = rhs._surface;
		_event = rhs._event;
	}
	return *this;
}

// -- Methods ------------------------------------------------------------------

bool	NibblerSDL::init() {
	logInfo("loading SDL");
	return true;
}

void	NibblerSDL::updateInput() {
	logInfo("updateInput SDL");
}

bool	NibblerSDL::draw() {
	logInfo("draw SDL");
	return true;
}

// -- Exceptions errors --------------------------------------------------------

NibblerSDL::NibblerSDLException::NibblerSDLException()
: std::runtime_error("NibblerSDL Exception") {}

NibblerSDL::NibblerSDLException::NibblerSDLException(const char* what_arg)
: std::runtime_error(std::string(std::string("NibblerSDLError: ") + what_arg).c_str()) {}

// -- Extern C -----------------------------------------------------------------

extern "C" {
	ANibblerGui *makeNibblerSDL() {
		return new NibblerSDL();
	}
}
