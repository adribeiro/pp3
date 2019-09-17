/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pp3Model.h
 * Author: ad
 *
 * Created on 17 de setembro de 2019, 09:34
 */

#ifndef PP3MODEL_H
#define PP3MODEL_H

#include "BaseConsoleGenesysApplication.h"
#include "Model.h"

class Pp3Model: public BaseConsoleGenesysApplication {
public:
    Pp3Model();
    Pp3Model(const Pp3Model& orig);
    virtual ~Pp3Model();
    virtual int main(int argc, char** argv);
private:

};

#endif /* PP3MODEL_H */

