/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TesteCreateSeparateBatchDispose.h
 * Author: ad
 *
 * Created on 18 de outubro de 2019, 10:19
 */

#ifndef TESTECREATESEPARATEBATCHDISPOSE_H
#define TESTECREATESEPARATEBATCHDISPOSE_H

#include "BaseConsoleGenesysApplication.h"

class TesteCreateSeparateBatchDispose : public BaseConsoleGenesysApplication{
public:
    TesteCreateSeparateBatchDispose();
    TesteCreateSeparateBatchDispose(const TesteCreateSeparateBatchDispose& orig);
    virtual ~TesteCreateSeparateBatchDispose();
    virtual int main(int argc, char** argv);
private:

};

#endif /* TESTECREATESEPARATEBATCHDISPOSE_H */

