/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCreateSeparateDispose.h
 * Author: ad
 *
 * Created on 9 de outubro de 2019, 11:51
 */

#ifndef TESTCREATESEPARATEDISPOSE_H
#define TESTCREATESEPARATEDISPOSE_H

#include "BaseConsoleGenesysApplication.h"

class TestCreateSeparateDispose : public BaseConsoleGenesysApplication{
public:
    TestCreateSeparateDispose();
    TestCreateSeparateDispose(const TestCreateSeparateDispose& orig);
    virtual ~TestCreateSeparateDispose();
    virtual int main(int argc, char** argv);
private:

};

#endif /* TESTCREATESEPARATEDISPOSE_H */

