#include <cctype>
#include "Utilities/InputValidator.h"

bool InputValidator::isDigit(std::string var) {
    if(var.empty())     return false;
    int start_idx = 0;
    if (var[0] == '-' || var[0] == '+') {
        if(var.size() == 1) return false;
        start_idx = 1;
    }
    for(int i = start_idx; i < var.size(); i++) {
        if(!isdigit(var[i]))        return false; 
    }
    
    return true;
} 