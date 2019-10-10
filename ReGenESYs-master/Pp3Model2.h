/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pp3Model2.h
 * Author: ad
 *
 * Created on 8 de outubro de 2019, 23:40
 */

#ifndef PP3MODEL2_H
#define PP3MODEL2_H

#include "BaseConsoleGenesysApplication.h"
#include "Model.h"

class Pp3Model2: public BaseConsoleGenesysApplication {
public:
    Pp3Model2();
    Pp3Model2(const Pp3Model2& orig);
    virtual ~Pp3Model2();
    virtual int main(int argc, char** argv);
private:

};

#endif /* PP3MODEL2_H */

