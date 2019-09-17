/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCreateDecideDispose.cpp
 * Author: ad
 * 
 * Created on 17 de setembro de 2019, 09:42
 */

#include "TestCreateDecideDispose.h"
#include "ComponentManager.h"


// you have to included need libs

// GEnSyS Simulator
#include "Simulator.h"

// Model Components
#include "Create.h"
#include "Delay.h"
#include "Dispose.h"
#include "Seize.h"
#include "Release.h"
#include "Assign.h"
#include "Record.h"
#include "Decide.h"
#include "Dummy.h"

// Model elements
#include "EntityType.h"
#include "Attribute.h"
#include "Variable.h"
#include "ProbDistrib.h"
#include "Group.h"
#include "Formula.h"
#include "ODE.h"

TestCreateDecideDispose::TestCreateDecideDispose() {
}

TestCreateDecideDispose::TestCreateDecideDispose(const TestCreateDecideDispose& orig) {
}

TestCreateDecideDispose::~TestCreateDecideDispose() {
}

int TestCreateDecideDispose::main(int argc, char** argv){
    Simulator* simulator = new Simulator();
    // creates an empty model
    Model* model = new Model(simulator);
    // Handle traces and simulation events to output them
    TraceManager* tm = model->getTraceManager();
    this->setDefaultTraceHandlers(tm);
    // set the trace level of simulation to "blockArrival" level, which is an intermediate level of tracing
    tm->setTraceLevel(Util::TraceLevel::blockArrival);
    // insert "fake plugins" since plugins based on dynamic loaded library are not implemented yet
    this->insertFakePluginsByHand(simulator);
    // get easy access to classes used to insert components and elements into a model
    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();
    //
    // build the simulation model
    //
    // set general info about the model
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(36000);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(1);
    infos->setDescription("./models/model01_CreDelDis.txt");


    EntityType* entityType1 = new EntityType(elements, "Cliente");
    elements->insert(Util::TypeOf<EntityType>(), entityType1);

    Create* chegada_cliente = new Create(model);
    chegada_cliente->setEntityType(entityType1);
    chegada_cliente->setTimeBetweenCreationsExpression("EXPO(20)");
    chegada_cliente->setTimeUnit(Util::TimeUnit::second);
    chegada_cliente->setEntitiesPerCreation(1);
    components->insert(chegada_cliente);
    

    Decide* decide1 = new Decide(model);
    decide1->getConditions()->insert("TNOW<10800 or TNOW>25200");
//    decide1->getConditions()->insert("NQ(Queue_Machine_1) <= 2*NQ(Queue_Machine_2)");

    Dispose* saida_cliente_velho = new Dispose(model);
    components->insert(saida_cliente_velho);
    
    Dispose* saida_cliente_novo = new Dispose(model);
    components->insert(saida_cliente_novo);

    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    chegada_cliente->getNextComponents()->insert(decide1);
    decide1->getNextComponents()->insert(saida_cliente_velho);
    decide1->getNextComponents()->insert(saida_cliente_novo);
    
    // insert the model into the simulator 
    simulator->getModelManager()->insert(model);
    // check the model
    model->checkModel();
    // save the model into a text file 
    model->saveModel("./temp/testEnterLeaveRoute.txt");
    // show the model
    model->show();
    // execute the simulation
    model->getSimulation()->startSimulation();
    return 0;
    
}

