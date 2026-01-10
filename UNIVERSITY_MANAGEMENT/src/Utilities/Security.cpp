#include <string>
#include <cstdlib>
#include "Utilities/Security.h"

using std::string;
std::string Security::GenerateStrongPassowrd() {
    std::string chars_string = "abcdefghijklmnoprstuvwxyz123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$^&*()^_-<>?+=~";
    std::string strong_password = "";
    for(int i = 0; i < 10; i++) {
        strong_password += chars_string[rand() % 77];
    }
    return strong_password;
}


bool Security::IsValidAge(int age) {
if (age < 0) {
    return false;
}
if (age > 130)   return false;
return true;
}