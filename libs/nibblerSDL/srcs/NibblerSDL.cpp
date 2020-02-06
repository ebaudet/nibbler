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

	 /* Poll for events */
	while( SDL_PollEvent( _event ) ){

		switch( _event->type ){
			/* Keyboard event */
			/* Pass the event data onto PrintKeyInfo() */
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
				std::cout << "KeyInfo: " << _event->key << std::endl;
				break;
			/* SDL_QUIT event (window close) */
			case SDL_QUIT:
				input.quit = true;
				break;

			default:
				break;
		}

	}
}

// Privates _____________

/* Print modifier info */
void NibblerSDL::_printModifiers( SDL_Keymod mod ){
	printf( "Modifers: " );

	/* If there are none then say so and return */
	if( mod == KMOD_NONE ){
		printf( "None\n" );
		return;
	}

	/* Check for the presence of each SDLMod value */
	/* This looks messy, but there really isn't    */
	/* a clearer way.                              */
	if( mod & KMOD_NUM ) printf( "NUMLOCK " );
	if( mod & KMOD_CAPS ) printf( "CAPSLOCK " );
	if( mod & KMOD_LCTRL ) printf( "LCTRL " );
	if( mod & KMOD_RCTRL ) printf( "RCTRL " );
	if( mod & KMOD_RSHIFT ) printf( "RSHIFT " );
	if( mod & KMOD_LSHIFT ) printf( "LSHIFT " );
	if( mod & KMOD_RALT ) printf( "RALT " );
	if( mod & KMOD_LALT ) printf( "LALT " );
	if( mod & KMOD_CTRL ) printf( "CTRL " );
	if( mod & KMOD_SHIFT ) printf( "SHIFT " );
	if( mod & KMOD_ALT ) printf( "ALT " );
	printf( "\n" );
}

/* Print all information about a key event */
void NibblerSDL::_printKeyInfo( SDL_KeyboardEvent *key ){
	/* Is it a release or a press? */
	if( key->type == SDL_KEYUP )
		printf( "Release:- " );
	else
		printf( "Press:- " );

	/* Print the hardware scancode first */
	printf( "Scancode: 0x%02X", key->keysym.scancode );
	/* Print the name of the key */
	printf( ", Name: %s", SDL_GetKeyName( key->keysym.sym ) );
	/* We want to print the unicode info, but we need to make */
	/* sure its a press event first (remember, release events */
	/* don't have unicode info                                */
	if( key->type == SDL_KEYDOWN ){
		/* If the Unicode value is less than 0x80 then the    */
		/* unicode value can be used to get a printable       */
		/* representation of the key, using (char)unicode.    */
		printf(", Unicode: " );
		if( key->keysym.unicode < 0x80 && key->keysym.unicode > 0 ){
			printf( "%c (0x%04X)", (char)key->keysym.unicode,
					key->keysym.unicode );
		}
		else{
			printf( "? (0x%04X)", key->keysym.unicode );
		}
	}
	printf( "\n" );
	/* Print modifier info */
	_printModifiers( static_cast<SDL_Keymod>(key->keysym.mod) );
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
