#ifndef DYNGUIMANAGER_HPP_
#define DYNGUIMANAGER_HPP_

# define NB_GUI	1

#include <iostream>
#include <stdexcept>
#include <array>
#include <string>
#include "ANibblerGui.hpp"

class DynGuiManager {
private:
	// Members
	uint8_t	_currentGuiID;
	void	*_dl_handle;
	static	std::array<std::pair<std::string const, std::string const>, NB_GUI> const _guiInfos;

	void	_quitGui();

public:
	// Members
	ANibblerGui	*nibblerGui;

	// Constructors
	DynGuiManager();
	DynGuiManager(DynGuiManager const &src);
	virtual ~DynGuiManager();

	// Operators
	DynGuiManager &operator=(DynGuiManager const &rhs);
	//// friend std::ostream& operator<<(std::ostream& os, const DynGuiManager& my_class);

	// Accessors
	uint8_t		getCurrentGuiID() const;

	// Methods
	void	loadGui(uint8_t id);

	// Exceptions
	class DynGuiManagerException : public std::runtime_error {
	public:
		DynGuiManagerException();
		explicit DynGuiManagerException(const char* what_arg);
	};
};

#endif  // DYNGUIMANAGER_HPP_
