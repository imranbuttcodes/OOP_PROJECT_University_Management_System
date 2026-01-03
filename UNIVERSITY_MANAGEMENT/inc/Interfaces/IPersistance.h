#pragma once
#include<iostream>



class Persistance {
public: 
    virtual void LoadFromFile(const std::string& filename) = 0;
    virtual void SaveToFile(const std::string& filename) const = 0;

    virtual ~Persistance() {} 
};

