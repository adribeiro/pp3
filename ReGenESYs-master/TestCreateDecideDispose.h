/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCreateDecideDispose.h
 * Author: ad
 *
 * Created on 17 de setembro de 2019, 09:42
 */

#ifndef TESTCREATEDECIDEDISPOSE_H
#define TESTCREATEDECIDEDISPOSE_H

#include "BaseConsoleGenesysApplication.h"

class TestCreateDecideDispose: public BaseConsoleGenesysApplication {
public:
    TestCreateDecideDispose();
    TestCreateDecideDispose(const TestCreateDecideDispose& orig);
    virtual ~TestCreateDecideDispose();
    virtual int main(int argc, char** argv);
private:

};

#endif /* TESTCREATEDECIDEDISPOSE_H */

