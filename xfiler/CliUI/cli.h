#ifndef CLI_H
#define CLI_H

#include <vector>
#include <string>
#include <functional>
#include <string_view>
#include "xfiler.h"

struct MenuItem {
    std::string_view title;
    std::function<void()> action;
};

class CLI {
public:
    void run(); 

private:
    void addItem(std::string_view title, std::function<void()> action);
    void display();

    void onCalculate();
    void onVerify();
    void onAbout();
	void onSupport();

    XFile xfile; 
    std::vector<MenuItem> items;
    bool running = true;
    int choice;
    std::string path2file;
    uint64_t expectedHash;

    static constexpr std::string_view MAIN = R"(
__________________________________________________________
>  __  __ _____ ___   ____ _               _             <
>  \ \/ /|  ___|_ _| / ___| |__   ___  ___| | _____ _ __ <
>   \  / | |_   | | | |   | '_ \ / _ \/ __| |/ / _ \ '__|<
>   /  \ |  _|  | | | |___| | | |  __/ (__|   <  __/ |   <
>  /_/\_\|_|   |___| \____|_| |_|\___|\___|_|\_\___|_|   <
>________________________________________________~ ~ ~ ~ <
                                            //  /   by   \                                            
                                            \\__\anonyaro/
                                                 \______/
    )";
    static constexpr std::string_view EXIT = "[0] Exit Program";
    static constexpr std::string_view CALC = "[1] Calculate Hash";
    static constexpr std::string_view CHECK = "[2] Verify Integrity";
    static constexpr std::string_view ABOUT = "[3] About XFIChecker";
    static constexpr std::string_view SUPPORT = "[4] Support the XFIChecker";
    static constexpr std::string_view HELPER = "[5] Help to see more and usage sample";

    static constexpr std::string_view PROMPT = "\nSelect an option: ";
	static constexpr std::string_view INVALID = " [!] Invalid option. Please try again.\n";
	static constexpr std::string_view COMPLETION = "\n [*] Operation completed. Returning to main menu...\n";
    static constexpr std::string_view ABOUTMSG = "\nXFIChecker by anonyaro\nRelease date: 26.12.2025;\nCurrent version: 1.0.0 (stable)";
    static constexpr std::string_view SUPPORT_URL = "https://www.donationalerts.com/r/xenyaro";
    static constexpr std::string_view ONSUPPORT_LOG = "\n[*] Opened support XFIChecker in your default browser...\n";

};
#endif