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
    tm->setTraceLevel(Util::TraceLevel::blockArrival);
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
    
    Variable* variable1 = new Variable("qtd_fila_1");
    Variable* variable2 = new Variable("qtd_fila_2");
    Variable* variable3 = new Variable("qtd_fila_3");
    Variable* variable4 = new Variable("qtd_fila_4");
    Variable* variable5 = new Variable("qtd_fila_5");
    elements->insert(Util::TypeOf<Variable>(), variable1);
    elements->insert(Util::TypeOf<Variable>(), variable2);
    elements->insert(Util::TypeOf<Variable>(), variable3);
    elements->insert(Util::TypeOf<Variable>(), variable4);
    elements->insert(Util::TypeOf<Variable>(), variable5);
    
    
    Attribute* attribute1 = new Attribute("embalar");
    Attribute* attribute2 = new Attribute("pagar");
    Attribute* attribute3 = new Attribute("collector");
    Attribute* attribute4 = new Attribute("tempo_caixa");
    Attribute* attribute5 = new Attribute("tipo");
    Attribute* attribute6 = new Attribute("nrProdutos");
    elements->insert(Util::TypeOf<Attribute>(), attribute1);
    elements->insert(Util::TypeOf<Attribute>(), attribute2);
    elements->insert(Util::TypeOf<Attribute>(), attribute3);
    elements->insert(Util::TypeOf<Attribute>(), attribute4);
    elements->insert(Util::TypeOf<Attribute>(), attribute5);
    elements->insert(Util::TypeOf<Attribute>(), attribute6);
    
    Assign* define_tipo_cliente = new Assign(model);
    Assign::Assignment* qtd_fila_1 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_1", "0");
    Assign::Assignment* qtd_fila_2 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_2", "0");
    Assign::Assignment* qtd_fila_3 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_3", "0");
    Assign::Assignment* qtd_fila_4 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_4", "0");
    Assign::Assignment* qtd_fila_5 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_5", "0");
    Assign::Assignment* embalar = new Assign::Assignment(Assign::DestinationType::Attribute, "embalar", "8");
    Assign::Assignment* pagar = new Assign::Assignment(Assign::DestinationType::Attribute, "pagar", "100");
    Assign::Assignment* collector = new Assign::Assignment(Assign::DestinationType::Attribute, "collector", "0");
    Assign::Assignment* tipo = new Assign::Assignment(Assign::DestinationType::Attribute, "tipo", "DISC(0.3,0,1,1)");
    Assign::Assignment* tempo_caixa = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_caixa", "TNOW");
    Assign::Assignment* nrProdutos = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "AINT(DISC(0.45,UNIF(1,8),0.9,UNIF(9,12),1,UNIF(13,20)))");
    define_tipo_cliente->getAssignments()->insert(qtd_fila_1);
    define_tipo_cliente->getAssignments()->insert(qtd_fila_2);
    define_tipo_cliente->getAssignments()->insert(qtd_fila_3);
    define_tipo_cliente->getAssignments()->insert(qtd_fila_4);
    define_tipo_cliente->getAssignments()->insert(qtd_fila_5);
    define_tipo_cliente->getAssignments()->insert(embalar);
    define_tipo_cliente->getAssignments()->insert(pagar);
    define_tipo_cliente->getAssignments()->insert(collector);
    define_tipo_cliente->getAssignments()->insert(tipo);
    define_tipo_cliente->getAssignments()->insert(tempo_caixa);
    define_tipo_cliente->getAssignments()->insert(nrProdutos);
    components->insert(define_tipo_cliente);
    
    

    Decide* decide1 = new Decide(model);
    decide1->getConditions()->insert("tipo == 1");
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