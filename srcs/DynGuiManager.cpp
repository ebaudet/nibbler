#include "DynGuiManager.hpp"
#include <string>

// contain dynamic libs info
std::array<std::pair< std::string const, std::string const >, NB_GUI> const	DynGuiManager::_guiInfos = {{
	{"libNibblerSDL.so", "makeNibblerSDL"},
	{"libNibblerSFML.so", "makeNibblerSFML"}
}};

// -- Constructors -------------------------------------------------------------

DynGuiManager::DynGuiManager()
: _currentGuiID(NO_GUI_LOADED), _dl_handle(nullptr), nibblerGui(nullptr) {
}

DynGuiManager::DynGuiManager(DynGuiManager const &src) {
	*this = src;
}

DynGuiManager::~DynGuiManager() {
	if (_currentGuiID != NO_GUI_LOADED) {
		_quitGui();
	}
}

// -- Operators ----------------------------------------------------------------

DynGuiManager &DynGuiManager::operator=(DynGuiManager const &rhs) {
	if ( this != &rhs ) {
		_currentGuiID = rhs._currentGuiID;
		_dl_handle = rhs._dl_handle;
		_currentGuiID = rhs._currentGuiID;
	}
	return *this;
}

// std::ostream &	operator<<(std::ostream & os, const DynGuiManager& my_class) {
// 	os << my_class.getMember();
// 	return (os);
// }

// -- Accessors ----------------------------------------------------------------

uint8_t		DynGuiManager::getCurrentGuiID() const { return _currentGuiID; }


// -- Methods ------------------------------------------------------------------

void	loadGui(uint8_t id) {
	(void)id;
}

// -- Exceptions errors --------------------------------------------------------

DynGuiManager::DynGuiManagerException::DynGuiManagerException()
: std::runtime_error("DynGuiManager Exception") {}

DynGuiManager::DynGuiManagerException::DynGuiManagerException(const char* what_arg)
: std::runtime_error(std::string(std::string("DynGuiManagerError: ") + what_arg).c_str()) {}
