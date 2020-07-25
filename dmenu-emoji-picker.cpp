#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <algorithm>
#include <string>
#include <sstream>

std::string notificationExecutable = "notify-send";
std::string dmenuCommand = "dmenu-custom -i -l 10 -p 'Emoji: '";
std::string emojiFileLocation = "~/repos/dmenu-emoji-picker/emoji";

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int copy(std::string str){
	std::string copyCommand = "echo -n '" + str + "' | xclip -selection c";
	system(copyCommand.c_str());
	
	return 0;
}

int main() {
	std::string notificationCommand;
	std::string text = exec(("cat " + emojiFileLocation + " | " + dmenuCommand).c_str());
	text.erase(std::remove(text.begin(), text.end(), '\n'), text.end()); // Remove any newlines, otherwise selecting the emoji will fail
	//std::cout << "Result: " << text << "EOL" << std::endl;

	if(text.empty()){
		notificationCommand = notificationExecutable + " -t 200 'Emoji selection cancelled'";
    	system(notificationCommand.c_str());
		return 0;
	}

    //Check if the result actually exists in the file
    std::string catResult = exec(("cat " + emojiFileLocation).c_str());
    std::stringstream ss(catResult);
    std::string to;
    bool found = false;
    while(std::getline(ss,to,'\n')){
        if(to == text){
            found = true;
        }
    }
    if(!found){
        return 0;
    }
		
	//int i = text.length() - 1;
    //while (i != 0 && !isspace(text[i]))
    //{
    //  --i;
    //}
    //std::string emoji = text.substr(i+1);
    std::string emoji = text.substr(0, text.find(" "));
    //std::cout << "Selected: " << emoji << std::endl;
	
	copy(emoji);

	notificationCommand = notificationExecutable + " -t 200 '" + emoji + " copied!'";
    system(notificationCommand.c_str());
    return 0;
}
