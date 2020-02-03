#include "Logging.hpp"
#include "DynGuiManager.hpp"

void	initLogs() {
	// init logging
	#if DEBUG
		logging.setLoglevel(LOGDEBUG);
		logging.setPrintFileLine(LOGWARN, true);
		logging.setPrintFileLine(LOGERROR, true);
		logging.setPrintFileLine(LOGFATAL, true);
	#else
		logging.setLoglevel(LOGINFO);
	#endif
	logDebug("using debug mode");
}

int		main() {
	initLogs();

	uint8_t			guiId = 0;
	DynGuiManager	dynGuiManager;

	// Load the default gui
	try {
		dynGuiManager.loadGui(guiId);
	} catch (const std::exception &e) {
		logErr(e.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
