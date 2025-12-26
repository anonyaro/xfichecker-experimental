#ifndef XFILERRORHANDLER_H
#define XFILERRORHANDLER_H

#include <stdexcept>
#include "xfiler.h"

class XFileError : public std::runtime_error {
	public:
        explicit XFileError(const std::string& path2file,
            const std::string& msg = "XFIChecker couldn't find")
            : std::runtime_error(msg + " -> \"" + path2file + "\" or open it \n Returning to main menu...") {}
};
#endif // XFILERRORHANDLER_H