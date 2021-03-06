#include <unistd.h>
#include <chrono>

#include "main.hpp"
#include "Logging.hpp"
#include "ANibblerGui.hpp"


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

std::chrono::milliseconds getMs() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());
}

void	gameLoop(DynGuiManager &dynGuiManager) {
	float	loopTime = 1000 / FPS;
	std::chrono::milliseconds	time_start;
	ANibblerGui		*nibblerGui = nullptr;

	#if DEBUG_FPS_LOW == true
		bool firstLoop = true;
	#endif

	nibblerGui = dynGuiManager.nibblerGui;

	while (nibblerGui->input.quit == false) {
		time_start = getMs();

		nibblerGui->updateInput();

		// verify id viability
		if (nibblerGui->input.loadGuiID < NB_GUI && \
		nibblerGui->input.loadGuiID != dynGuiManager.getCurrentGuiID()) {
			// change Gui
			dynGuiManager.loadGui(nibblerGui->input.loadGuiID);
			nibblerGui = dynGuiManager.nibblerGui;
			nibblerGui->init();

			nibblerGui->input.loadGuiID = NO_GUI_LOADED;
		}

		nibblerGui->draw();

		// fps
		std::chrono::milliseconds time_loop = getMs() - time_start;
		if (time_loop.count() > loopTime) {
			#if DEBUG_FPS_LOW == true
				if (!firstLoop)
					logDebug("update loop slow -> " << time_loop.count() << "ms / " << loopTime << "ms (" << FPS << "fps)");
			#endif
		}
		else {
			usleep((loopTime - time_loop.count()) * 1000);
		}
		#if DEBUG_FPS_LOW == true
			firstLoop = false;
		#endif
	}
}

int		main() {
	initLogs();

	uint8_t			guiId = 0;
	DynGuiManager	dynGuiManager;

	// Load the default gui
	try {
		dynGuiManager.loadGui(guiId);
		dynGuiManager.nibblerGui->init();

		gameLoop(dynGuiManager);
	} catch (const std::exception &e) {
		logErr(e.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
