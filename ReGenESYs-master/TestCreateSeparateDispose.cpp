/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCreateSeparateDispose.cpp
 * Author: ad
 * 
 * Created on 9 de outubro de 2019, 11:51
 */

#include "TestCreateSeparateDispose.h"

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

TestCreateSeparateDispose::TestCreateSeparateDispose() {
}

TestCreateSeparateDispose::TestCreateSeparateDispose(const TestCreateSeparateDispose& orig) {
}

TestCreateSeparateDispose::~TestCreateSeparateDispose() {
}

int TestCreateSeparateDispose::main(int argc, char** argv){
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
//    Assign::Assignment* a_qtd_fila_1 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_1", "0");
//    Assign::Assignment* a_qtd_fila_2 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_2", "0");
//    Assign::Assignment* a_qtd_fila_3 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_3", "0");
//    Assign::Assignment* a_qtd_fila_4 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_4", "0");
//    Assign::Assignment* a_qtd_fila_5 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_5", "0");
//    Assign::Assignment* a_embalar = new Assign::Assignment(Assign::DestinationType::Attribute, "embalar", "8");
//    Assign::Assignment* a_pagar = new Assign::Assignment(Assign::DestinationType::Attribute, "pagar", "100");
//    Assign::Assignment* a_collector = new Assign::Assignment(Assign::DestinationType::Attribute, "collector", "0");
//    Assign::Assignment* a_tipo_jovem = new Assign::Assignment(Assign::DestinationType::Attribute, "tipo", "1");//DISC(0.3,0,1,1)
//    Assign::Assignment* a_tempo_caixa = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_caixa", "TNOW");
    Assign::Assignment* a_nrProdutos = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "20");//AINT(DISC(0.45,UNIF(1,8),0.9,UNIF(9,12),1,UNIF(13,20)))
//    inicia_cliente->getAssignments()->insert(a_qtd_fila_1);
//    inicia_cliente->getAssignments()->insert(a_qtd_fila_2);
//    inicia_cliente->getAssignments()->insert(a_qtd_fila_3);
//    inicia_cliente->getAssignments()->insert(a_qtd_fila_4);
//    inicia_cliente->getAssignments()->insert(a_qtd_fila_5);
//    inicia_cliente->getAssignments()->insert(a_embalar);
//    inicia_cliente->getAssignments()->insert(a_pagar);
//    inicia_cliente->getAssignments()->insert(a_collector);
//    inicia_cliente->getAssignments()->insert(a_tipo_jovem);
//    inicia_cliente->getAssignments()->insert(a_tempo_caixa);
    inicia_cliente->getAssignments()->insert(a_nrProdutos);
    components->insert(inicia_cliente);
    
    Separate* divide_produtos = new Separate(model);
    divide_produtos->setSplitBatch(false);
    divide_produtos->setAmountToDuplicate("nrProdutos");
    components->insert(divide_produtos);
    
    Dispose* saida_cliente = new Dispose(model);
    components->insert(saida_cliente);
    
    Dispose* saida_produto = new Dispose(model);
    components->insert(saida_produto);


    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    chegada_cliente->getNextComponents()->insert(inicia_cliente);
    inicia_cliente->getNextComponents()->insert(divide_produtos);
    divide_produtos->getNextComponents()->insert(saida_cliente);
    divide_produtos->getNextComponents()->insert(saida_produto);
    
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
