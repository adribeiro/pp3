/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TesteCreateSeparateBatchDispose.cpp
 * Author: ad
 * 
 * Created on 18 de outubro de 2019, 10:19
 */

#include "TesteCreateSeparateBatchDispose.h"

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
#include "Enter.h"
#include "Route.h"
#include "Leave.h"
#include "Separate.h"
#include "Batch.h"

// Model elements
#include "EntityType.h"
#include "Station.h"
#include "Attribute.h"
#include "Variable.h"
#include "ProbDistrib.h"
#include "EntityGroup.h"
#include "Set.h"
#include "Formula.h"
#include "ODE.h"

TesteCreateSeparateBatchDispose::TesteCreateSeparateBatchDispose() {
}

TesteCreateSeparateBatchDispose::TesteCreateSeparateBatchDispose(const TesteCreateSeparateBatchDispose& orig) {
}

TesteCreateSeparateBatchDispose::~TesteCreateSeparateBatchDispose() {
}

int TesteCreateSeparateBatchDispose::main(int argc, char** argv){
    Simulator* simulator = new Simulator();

    // insert "fake plugins" since plugins based on dynamic loaded library are not implemented yet
    this->insertFakePluginsByHand(simulator);

    // creates an empty model
    Model* model = new Model(simulator);

    // Handle traces and simulation events to output them
    TraceManager* tm = model->getTraceManager();
    this->setDefaultTraceHandlers(tm);
    tm->setTraceLevel(Util::TraceLevel::blockInternal);

    // get easy access to classes used to insert components and elements into a model
    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();
    
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(4000);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(1);
    infos->setDescription("./models/model01_CreDelDis.txt");

    
    //attributes
    Attribute* nrProdutos = new Attribute("nrProdutos");
    elements->insert(Util::TypeOf<Attribute>(), nrProdutos);
    
    Attribute* nrCaixa = new Attribute("nrCaixa");
    elements->insert(Util::TypeOf<Attribute>(), nrCaixa);
    
    //variables
    
    //resources and sets
    
    //Queues
    
    //seizes
    
    //releases
    
    //stations
    
    //enter
    
    //route
    
    //entities
    EntityType* cliente = new EntityType(elements, "cliente");
    elements->insert(Util::TypeOf<EntityType>(), cliente);

    
    //componentes
    Create* chegada_cliente = new Create(model);
    chegada_cliente->setEntityType(cliente);
    chegada_cliente->setTimeBetweenCreationsExpression("5000");
    chegada_cliente->setTimeUnit(Util::TimeUnit::second);
    chegada_cliente->setEntitiesPerCreation(1);
    components->insert(chegada_cliente);
    
    Assign* inicia_cliente = new Assign(model);

    Assign::Assignment* a_nrProdutos = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "10");
    Assign::Assignment* a_nrCaixa = new Assign::Assignment(Assign::DestinationType::Attribute, "nrCaixa", "0");
    inicia_cliente->getAssignments()->insert(a_nrProdutos);
    inicia_cliente->getAssignments()->insert(a_nrCaixa);
    components->insert(inicia_cliente);
    
    Separate* divide_produtos = new Separate(model);
    divide_produtos->setSplitBatch(false);
    divide_produtos->setAmountToDuplicate("nrProdutos");
    components->insert(divide_produtos);
    
    Delay* delay1 = new Delay(model);
    delay1->setDelayExpression("NORM(5,1.5)");
    delay1->setDelayTimeUnit(Util::TimeUnit::minute);
    components->insert(delay1);
    
    Batch* junta_produtos = new Batch(model);
    junta_produtos->setByAttributeBatch(true);
    junta_produtos->setAttributeName("nrCaixa");
    junta_produtos->setPermanentBatch(false);
    junta_produtos->setExpression("nrProdutos");
    junta_produtos->setBatchName("juntaProdutos");
    components->insert(junta_produtos);
    
    Batch* sai_caixa = new Batch(model);
    sai_caixa->setByAttributeBatch(true);
    sai_caixa->setAttributeName("nrCaixa");
    sai_caixa->setPermanentBatch(true);
    sai_caixa->setExpression("2");
    junta_produtos->setBatchName("saiCaixa");
    components->insert(sai_caixa);
    
    
    Dispose* saida_cliente = new Dispose(model);
    components->insert(saida_cliente);


    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    chegada_cliente->getNextComponents()->insert(inicia_cliente);
    inicia_cliente->getNextComponents()->insert(divide_produtos);
    divide_produtos->getNextComponents()->insert(sai_caixa);
    divide_produtos->getNextComponents()->insert(delay1);
    delay1->getNextComponents()->insert(junta_produtos);
    junta_produtos->getNextComponents()->insert(sai_caixa);
    sai_caixa->getNextComponents()->insert(saida_cliente);
    
     // insert the model into the simulator 
    simulator->getModelManager()->insert(model);

    // if the model is ok then save the model into a text file 
    if (model->checkModel()) {
	model->saveModel("./temp/fullSimulationModel.txt");
    }

    // execute the simulation
    model->getSimulation()->startSimulation();

    return 0;
}