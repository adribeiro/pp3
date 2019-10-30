/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCreateAssignDispose.cpp
 * Author: ad
 * 
 * Created on 17 de setembro de 2019, 09:42
 */

#include "TestCreateAssignDispose.h"
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
#include "EntityGroup.h"
#include "Set.h"
#include "Formula.h"
#include "ODE.h"

TestCreateAssignDispose::TestCreateAssignDispose() {
}

TestCreateAssignDispose::TestCreateAssignDispose(const TestCreateAssignDispose& orig) {
}

TestCreateAssignDispose::~TestCreateAssignDispose() {
}

int TestCreateAssignDispose::main(int argc, char** argv) {
    Simulator* simulator = new Simulator();
    // creates an empty model
    Model* model = new Model(simulator);
    // Handle traces and simulation events to output them
    TraceManager* tm = model->getTraceManager();
    this->setDefaultTraceHandlers(tm);
    // set the trace level of simulation to "blockArrival" level, which is an intermediate level of tracing
    tm->setTraceLevel(Util::TraceLevel::mostDetailed);
    // insert "fake plugins" since plugins based on dynamic loaded library are not implemented yet
    this->insertFakePluginsByHand(simulator);
    // get easy access to classes used to insert components and elements into a model
    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();
    
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
    
    Variable* variable = new Variable("variable");
    Variable* variableArray = new Variable("variableArray");
    elements->insert(Util::TypeOf<Variable>(), variable);
    elements->insert(Util::TypeOf<Variable>(), variableArray);
    
    
    Attribute* attribute = new Attribute("attribute");
    elements->insert(Util::TypeOf<Attribute>(), attribute);
    
    Assign* define_tipo_cliente = new Assign(model);
    Assign::Assignment* a_variable = new Assign::Assignment(Assign::DestinationType::Variable, "variable", "1");
    Assign::Assignment* a_attribute = new Assign::Assignment(Assign::DestinationType::Attribute, "attribute", "2");
    Assign::Assignment* a_variableArray1 = new Assign::Assignment(Assign::DestinationType::VariableArray, "variableArray", "10");
    a_variableArray1->setDestinationArray(true,"attribute");
    Assign::Assignment* a_variableArray2 = new Assign::Assignment(Assign::DestinationType::VariableArray, "variableArray", "20");
    a_variableArray2->setDestinationArray(false,"variable");
    Assign::Assignment* a_variableArray3 = new Assign::Assignment(Assign::DestinationType::Variable, "variable", "variableArray");
    a_variableArray3->setExpressionArray(false, "variable");
    Assign::Assignment* a_variableArray4 = new Assign::Assignment(Assign::DestinationType::Attribute, "attribute", "variableArray");
    a_variableArray4->setExpressionArray(true, "attribute");
    Assign::Assignment* a_variableArray5 = new Assign::Assignment(Assign::DestinationType::VariableArray, "variableArray", "variableArray");
    a_variableArray5->setDestinationExpressionArray(true, "attribute",false, "1");
    Assign::Assignment* a_variableArray6 = new Assign::Assignment(Assign::DestinationType::VariableArray, "variableArray", "variableArray");
    a_variableArray6->setDestinationExpressionArray(true, "attribute",true, "attribute");
    Assign::Assignment* a_variableArray7 = new Assign::Assignment(Assign::DestinationType::VariableArray, "variableArray", "variableArray");
    a_variableArray7->setDestinationExpressionArray(false, "2",false, "1");
    Assign::Assignment* a_variableArray8 = new Assign::Assignment(Assign::DestinationType::VariableArray, "variableArray", "variableArray");
    a_variableArray8->setDestinationExpressionArray(false, "2",true, "attribute");
    define_tipo_cliente->getAssignments()->insert(a_variable);
    define_tipo_cliente->getAssignments()->insert(a_attribute);
    define_tipo_cliente->getAssignments()->insert(a_variableArray1);
    define_tipo_cliente->getAssignments()->insert(a_variableArray2);
    define_tipo_cliente->getAssignments()->insert(a_variableArray3);
    define_tipo_cliente->getAssignments()->insert(a_variableArray4);
    define_tipo_cliente->getAssignments()->insert(a_variableArray5);
    define_tipo_cliente->getAssignments()->insert(a_variableArray6);
    define_tipo_cliente->getAssignments()->insert(a_variableArray7);
    define_tipo_cliente->getAssignments()->insert(a_variableArray8);
    components->insert(define_tipo_cliente);
    
    

    Decide* decide1 = new Decide(model);
    decide1->getConditions()->insert("attribute == 10");
//    decide1->getConditions()->insert("NQ(Queue_Machine_1) <= 2*NQ(Queue_Machine_2)");

    Dispose* dispose1 = new Dispose(model);
    components->insert(dispose1);
    
    Dispose* dispose2 = new Dispose(model);
    components->insert(dispose2);

    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    chegada_cliente->getNextComponents()->insert(define_tipo_cliente);
    define_tipo_cliente->getNextComponents()->insert(decide1);
    decide1->getNextComponents()->insert(dispose1);
    decide1->getNextComponents()->insert(dispose2);
    
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