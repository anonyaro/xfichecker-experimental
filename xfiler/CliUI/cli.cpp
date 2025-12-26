#include "cli.h"
#include "xfilerrorhandler.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <filesystem>

void CLI::addItem(const std::string_view title, std::function<void()> action) {
    items.push_back({ title, action });
}

void CLI::run() {
    addItem(CALC, [this]() { onCalculate(); });
    addItem(CHECK, [this]() { onVerify(); });
    addItem(ABOUT, [this]() { onAbout(); });
    addItem(SUPPORT, [this]() { onSupport(); });

    display();
}

void CLI::onCalculate() {
    std::cout << "\n [METHOD] Calculate FNV-1a Hash\n Enter path to file: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, path2file);

    try {
        unsigned long long hash = xfile.calculateHash(path2file);
        std::cout << " [SUCCESS] Hash: 0x" << std::hex << std::uppercase << hash << std::dec << "\n";
    }
    catch (const XFileError& ex) {
        std::cerr << " [ERROR] " << ex.what() << "\n";
    }
}

void CLI::onVerify() {

    try {
        std::cout << "\n [ACTION] Integrity Check\n Enter path to file: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, path2file);

        std::cout << " Enter expected hash (in hex): ";
        if (!(std::cin >> std::hex >> expectedHash)) {
            std::cout << " [!] Invalid hex format.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }
        std::cout << std::dec;

        if (xfile.verifyData(path2file, expectedHash)) {
            std::cout << " [OK] File is intact. Hashes match!\n";
        }
        else {
            std::cout << " [FAIL] WARNING! Hash mismatch! File may be corrupted.\n";
        }
    }
    catch (const XFileError& ex) {
        std::cerr << " [ERROR] " << ex.what() << "\n";
    }
}

void CLI::onAbout() {
	system("cls||clear");
    std::cout << ABOUTMSG;
    display();
}
void CLI::onSupport() {
    std::cout << ONSUPPORT_LOG;

#if defined(_WIN32) || defined(_WIN64)
    // Windows
    std::string command = "start \"\" \"" + static_cast<std::string>(SUPPORT_URL) + "\"";
    system(command.c_str());

#elif defined(__APPLE__)
    // macOS
    std::string command = "open " + static_cast<std::string>(SUPPORT_URL);
    system(command.c_str());

#else
	// Linux & other Unix-like systems *using xdg-open for variety of DE's*
    std::string command = "xdg-open " + static_cast<std::string>(SUPPORT_URL) + " > /dev/null 2>&1";
    int result = system(command.c_str());

    if (result != 0)
        std::cout << " [!] Could not open default browser. Please visit: " << SUPPORT_URL << std::endl;
#endif   
}


void CLI::display() {
    std::cout << MAIN << "\n";
    for (const auto& item : items) {
        std::cout << item.title << "\n";
    }
    std::cout << EXIT << "\n";

    while (running) {
        std::cout << PROMPT;

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "[!] Invalid command <-> Select an option to continue (e.g: '3' to see more 'About XFIChecker')\n";
            continue;
        }

        if (choice == 0) break;

        if (choice > 0 && choice <= items.size()) {
            items[choice - 1].action();
        }
        else {
            std::cout << "[!] Invalid command!\n";
        }
    }
}