#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

enum	eLoglevel {
	LOGDEBUG, LOGINFO, LOGSUCCESS, LOGWARN, LOGERROR, LOGFATAL, NBLOG
};

#define log_(level, x) { std::stringstream ss; ss << x; logging.log(level, ss.str(), __FILE__, __LINE__); }

#define logDebug(x) log_(LOGDEBUG, x)
#define logInfo(x) log_(LOGINFO, x)
#define logSuccess(x) log_(LOGSUCCESS, x)
#define logWarn(x) log_(LOGWARN, x)
#define logErr(x) log_(LOGERROR, x)
#define logFatal(x) log_(LOGFATAL, x)
#define logErrExit(x) log_(LOGERROR, x)
#define logFatalExit(x) log_(LOGFATAL, x)

class Logging {
	public:
		Logging();
		Logging(Logging const &src);
		virtual ~Logging();

		Logging &			operator=(Logging const &rhs);

		void				setLoglevel(eLoglevel loglevel);  // don't cout under minLevel
		void				setLogColor(eLoglevel loglevel, std::string const & color);
		void				setPrintFileLine(eLoglevel loglevel, bool printFileLine);
		void				setPrintFileLine(bool printFileLine);

		void				log(eLoglevel level, std::string message, std::string file = "", int line = -1);

		std::string const &	getColor(eLoglevel loglevel) const;
		eLoglevel			getLoglevel() const;

	private:
		std::string		_colors[NBLOG];
		bool			_printFileLine[NBLOG];
		eLoglevel		_loglevel;
};

extern Logging		logging;
