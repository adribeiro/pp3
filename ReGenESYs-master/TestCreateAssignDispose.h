/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCreateAssignDispose.h
 * Author: ad
 *
 * Created on 17 de setembro de 2019, 09:42
 */

#ifndef TESTCREATEASSIGNDISPOSE_H
#define TESTCREATEASSIGNDISPOSE_H

#include "BaseConsoleGenesysApplication.h"

class TestCreateAssignDispose : public BaseConsoleGenesysApplication{
public:
    TestCreateAssignDispose();
    TestCreateAssignDispose(const TestCreateAssignDispose& orig);
    virtual ~TestCreateAssignDispose();
    virtual int main(int argc, char** argv);
private:

};

#endif /* TESTCREATEASSIGNDISPOSE_H */

