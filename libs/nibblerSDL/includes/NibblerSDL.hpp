#ifndef NIBBLERSDL_HPP_
#define NIBBLERSDL_HPP_

#include <SDL2/SDL.h>
#include <iostream>
#include <stdexcept>
#include "ANibblerGui.hpp"

class NibblerSDL : public ANibblerGui {
private:
	// Members
	SDL_Window	*_win;
	SDL_Surface	*_surface;
	SDL_Event	*_event;


public:
	// Constructors
	NibblerSDL();
	NibblerSDL(NibblerSDL const &src);
	~NibblerSDL();

	// Operators
	NibblerSDL &operator=(NibblerSDL const &rhs);

	// Methods
	virtual bool	init();
	virtual void	updateInput();
	virtual bool	draw();

	// Exceptions
	class NibblerSDLException : public std::runtime_error {
	public:
		NibblerSDLException();
		explicit NibblerSDLException(const char* what_arg);
	};
};

#endif  // NIBBLERSDL_HPP_
