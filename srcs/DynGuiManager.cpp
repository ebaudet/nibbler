#include "DynGuiManager.hpp"
#include "ANibblerGui.hpp"
#include "Logging.hpp"
#include <string>
#include <dlfcn.h>

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

void	DynGuiManager::loadGui(uint8_t id) {
	logInfo("Load GUI " + std::to_string(id));

	if (id >= NB_GUI || id < 0)
		throw DynGuiManagerException((
			"Not existence of GUI " + std::to_string(id)
			).c_str());

	if (_currentGuiID != NO_GUI_LOADED)
		_quitGui();

	_dl_handle = dlopen(_guiInfos[id].first.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!_dl_handle)
		throw DynGuiManagerException(dlerror());

	void* mkr = dlsym(_dl_handle, _guiInfos[id].second.c_str());
	if (!nibblerGui)
		throw DynGuiManagerException(dlerror());

	_currentGuiID = id;
	nibblerGui = reinterpret_cast<nibblerGuiCreator>(mkr)();
}

void	DynGuiManager::_quitGui() {
	delete nibblerGui;
	dlclose(_dl_handle);
	_currentGuiID = NO_GUI_LOADED;
}

// -- Exceptions errors --------------------------------------------------------

DynGuiManager::DynGuiManagerException::DynGuiManagerException()
: std::runtime_error("DynGuiManager Exception") {}

DynGuiManager::DynGuiManagerException::DynGuiManagerException(const char* what_arg)
: std::runtime_error(std::string(std::string("DynGuiManagerError: ") + what_arg).c_str()) {}
