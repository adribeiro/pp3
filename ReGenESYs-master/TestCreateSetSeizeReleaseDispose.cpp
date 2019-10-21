/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCreateSetSeizeReleaseDispose.cpp
 * Author: ad
 * 
 * Created on 21 de outubro de 2019, 14:09
 */

#include "TestCreateSetSeizeReleaseDispose.h"

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

TestCreateSetSeizeReleaseDispose::TestCreateSetSeizeReleaseDispose() {
}

TestCreateSetSeizeReleaseDispose::TestCreateSetSeizeReleaseDispose(const TestCreateSetSeizeReleaseDispose& orig) {
}

TestCreateSetSeizeReleaseDispose::~TestCreateSetSeizeReleaseDispose() {
}

int TestCreateSetSeizeReleaseDispose::main(int argc, char** argv){
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
    Attribute* nrCaixa = new Attribute("nrCaixa");
    elements->insert(Util::TypeOf<Attribute>(), nrCaixa);
    
    //variables
    
    //resources and sets
    Resource* caixa1_jovem = new Resource(elements, "caixa1_jovem");
    caixa1_jovem->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa1_jovem);
    
    Resource* caixa2_jovem = new Resource(elements, "caixa2_jovem");
    caixa2_jovem->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa2_jovem);
    
    Resource* caixa1_rapido = new Resource(elements, "caixa1_rapido");
    caixa1_rapido->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa1_rapido);
    
    Resource* caixa2_rapido = new Resource(elements, "caixa2_rapido");
    caixa2_rapido->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa2_rapido);
    
    Resource* caixa3_rapido = new Resource(elements, "caixa3_rapido");
    caixa3_rapido->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa3_rapido);
    
    Resource* caixa4_rapido = new Resource(elements, "caixa4_rapido");
    caixa4_rapido->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa4_rapido);

    Set* caixas_nao_idoso = new Set(elements, "caixas_nao_idoso");
    caixas_nao_idoso->setSetOfType(Util::TypeOf<Resource>());
    caixas_nao_idoso->getElementSet()->insert(caixa1_rapido);
    caixas_nao_idoso->getElementSet()->insert(caixa2_rapido);
    caixas_nao_idoso->getElementSet()->insert(caixa3_rapido);
    caixas_nao_idoso->getElementSet()->insert(caixa4_rapido);
    caixas_nao_idoso->getElementSet()->insert(caixa1_jovem);
    caixas_nao_idoso->getElementSet()->insert(caixa2_jovem);
    elements->insert(Util::TypeOf<Set>(), caixas_nao_idoso);
    
    //Queues
    Queue* fila1_rapido = new Queue(elements, "fila1_rapido");
    fila1_rapido->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila1_rapido);
    
    Queue* fila2_rapido = new Queue(elements, "fila2_rapido");
    fila2_rapido->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila2_rapido);
    
    Queue* fila3_rapido = new Queue(elements, "fila3_rapido");
    fila3_rapido->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila3_rapido);
    
    Queue* fila4_rapido = new Queue(elements, "fila4_rapido");
    fila4_rapido->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila4_rapido);
    
    Queue* fila1_jovem = new Queue(elements, "fila1_jovem");
    fila1_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila1_jovem);
    
    Queue* fila2_jovem = new Queue(elements, "fila2_jovem");
    fila2_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila2_jovem);
    
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
    chegada_cliente->setTimeBetweenCreationsExpression("1000");
    chegada_cliente->setTimeUnit(Util::TimeUnit::second);
    chegada_cliente->setEntitiesPerCreation(1);
    components->insert(chegada_cliente);
    
    Assign* inicia_cliente = new Assign(model);
    Assign::Assignment* a_nrCaixa = new Assign::Assignment(Assign::DestinationType::Attribute, "nrCaixa", "TRUNK(UNIF(0,5))");
    inicia_cliente->getAssignments()->insert(a_nrCaixa);
    components->insert(inicia_cliente);
    
    Seize* seize1 = new Seize(model);
    seize1->setSet(caixas_nao_idoso);
    seize1->insertQueue(fila1_rapido);
    seize1->insertQueue(fila2_rapido);
    seize1->insertQueue(fila3_rapido);
    seize1->insertQueue(fila4_rapido);
    seize1->insertQueue(fila1_jovem);
    seize1->insertQueue(fila2_jovem);
    seize1->setSaveAttribute("nrCaixa")
    seize1->setRule(Resource::ResourceRule::ESPECIFIC);
    components->insert(seize1);
    
    Delay* delay1 = new Delay(model);
    delay1->setDelayExpression("NORM(5,1.5)");
    delay1->setDelayTimeUnit(Util::TimeUnit::minute);
    components->insert(delay1);

    Release* release1 = new Release(model);
    release1->setSet(caixas_nao_idoso);
    components->insert(release1);
    
    Dispose* saida_cliente = new Dispose(model);
    components->insert(saida_cliente);



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