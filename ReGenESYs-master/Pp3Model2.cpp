/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pp3Model.cpp
 * Author: ad
 * 
 * Created on 17 de setembro de 2019, 09:34
 */

#include "Pp3Model2.h"

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

Pp3Model2::Pp3Model2() {
}

Pp3Model2::Pp3Model2(const Pp3Model2& orig) {
}

Pp3Model2::~Pp3Model2() {
}

int Pp3Model2::main(int argc, char** argv) {
    Simulator* simulator = new Simulator();

    // insert "fake plugins" since plugins based on dynamic loaded library are not implemented yet
    this->insertFakePluginsByHand(simulator);

    // creates an empty model
    Model* model = new Model(simulator);

    // Handle traces and simulation events to output them
    TraceManager* tm = model->getTraceManager();
    this->setDefaultTraceHandlers(tm);
    tm->setTraceLevel(Util::TraceLevel::blockArrival);

    // get easy access to classes used to insert components and elements into a model
    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();
    
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(4000);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(1);
    infos->setDescription("./models/model01_CreDelDis.txt");

    
    //atributos
//    Attribute* embalar = new Attribute("embalar");
//    Attribute* pagar = new Attribute("pagar");
//    Attribute* collector = new Attribute("collector");
//    Attribute* tipo = new Attribute("tipo");
    Attribute* nrProdutos = new Attribute("nrProdutos");
//    Attribute* registro = new Attribute("registro");
//    Attribute* caixa_selecionado = new Attribute("caixa_selecionado");
//    Attribute* tempo_caixa_idosos = new Attribute("tempo_caixa_idosos");
//    Attribute* tempo_caixa = new Attribute("tempo_caixa");
//    Attribute* tempo_embalar = new Attribute("tempo_embalar");
//    elements->insert(Util::TypeOf<Attribute>(), embalar);
//    elements->insert(Util::TypeOf<Attribute>(), pagar);
//    elements->insert(Util::TypeOf<Attribute>(), collector);
//    elements->insert(Util::TypeOf<Attribute>(), tempo_caixa);
//    elements->insert(Util::TypeOf<Attribute>(), tipo);
    elements->insert(Util::TypeOf<Attribute>(), nrProdutos);
//    elements->insert(Util::TypeOf<Attribute>(), tempo_caixa_idosos);
//    elements->insert(Util::TypeOf<Attribute>(), tempo_embalar);
//    elements->insert(Util::TypeOf<Attribute>(), caixa_selecionado);
//    elements->insert(Util::TypeOf<Attribute>(), registro);
    
    
    //variaveis
//    Variable* qtd_fila_1 = new Variable("qtd_fila_1");
//    Variable* qntd_fila_2 = new Variable("qtd_fila_2");
//    Variable* qntd_fila_3 = new Variable("qtd_fila_3");
//    Variable* qntd_fila_4 = new Variable("qtd_fila_4");
//    Variable* qntd_fila_5 = new Variable("qtd_fila_5");
//    Variable* est_qtd_fila1 = new Variable("est_qtd_fila1");
//    Variable* est_qtd_fila2 = new Variable("est_qtd_fila2");
//    Variable* _registrados = new Variable("_registrados");
//    Variable* _sacolas = new Variable("_sacolas");
//    Variable* _aux_registro = new Variable("_aux_registro");
//    Variable* nProdutos_1 = new Variable("nProdutos_1");
//    Variable* nProdutos_2 = new Variable("nProdutos_2");
//    Variable* nProdutos_3 = new Variable("nProdutos_3");
//    Variable* nProdutos_4 = new Variable("nProdutos_4");
//    Variable* nProdutos_5 = new Variable("nProdutos_5");
//    Variable* nProdutos_6 = new Variable("nProdutos_6");
//    Variable* nProdutos_7 = new Variable("nProdutos_8");
//    Variable* nProdutos_8 = new Variable("nProdutos_7");
//    Variable* _embalador = new Variable("_embalador");
//    Variable* _tempo_registro_total = new Variable("_tempo_registro_total");
//    Variable* _tempo_embalo_total = new Variable("_tempo_embalo_total");
//    Variable* _tempo_caixa_total = new Variable("_tempo_caixa_total");
//    elements->insert(Util::TypeOf<Variable>(), qtd_fila_1);
//    elements->insert(Util::TypeOf<Variable>(), qntd_fila_2);
//    elements->insert(Util::TypeOf<Variable>(), qntd_fila_3);
//    elements->insert(Util::TypeOf<Variable>(), qntd_fila_4);
//    elements->insert(Util::TypeOf<Variable>(), qntd_fila_5);
//    elements->insert(Util::TypeOf<Variable>(), est_qtd_fila1);
//    elements->insert(Util::TypeOf<Variable>(), est_qtd_fila2);
//    elements->insert(Util::TypeOf<Variable>(), _sacolas);
//    elements->insert(Util::TypeOf<Variable>(), _registrados);
//    elements->insert(Util::TypeOf<Variable>(), _aux_registro);
//    elements->insert(Util::TypeOf<Variable>(), nProdutos_1);
//    elements->insert(Util::TypeOf<Variable>(), nProdutos_2);
//    elements->insert(Util::TypeOf<Variable>(), nProdutos_3);
//    elements->insert(Util::TypeOf<Variable>(), nProdutos_4);
//    elements->insert(Util::TypeOf<Variable>(), nProdutos_5);
//    elements->insert(Util::TypeOf<Variable>(), nProdutos_6);
//    elements->insert(Util::TypeOf<Variable>(), nProdutos_7);
//    elements->insert(Util::TypeOf<Variable>(), nProdutos_8);
    
//    elements->insert(Util::TypeOf<Variable>(), _embalador);
//    elements->insert(Util::TypeOf<Variable>(), _tempo_registro_total);
//    elements->insert(Util::TypeOf<Variable>(), _tempo_embalo_total);
//    elements->insert(Util::TypeOf<Variable>(), _tempo_caixa_total);
    
    
    //Resources e Sets
    Resource* caixa1_idoso = new Resource(elements, "caixa1_idoso");
    caixa1_idoso->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa1_idoso);
    
    //Queues
    Queue* fila1_idoso = new Queue(elements, "fila1_idoso");
    fila1_idoso->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila1_idoso);
    
    
    //seizes

    Seize* aloca_idoso1 = new Seize(model);
    aloca_idoso1->setResource(caixa1_idoso);
    aloca_idoso1->setQueue(fila1_idoso);
    components->insert(aloca_idoso1);
    
    //releases
    
    // create stations to enter and route to
    
    //enter
    
    //route
    
    //entidades
    EntityType* cliente = new EntityType(elements, "cliente");
    elements->insert(Util::TypeOf<EntityType>(), cliente);
    
    
    //assigns e componentes
    Create* chegada_cliente = new Create(model);
    chegada_cliente->setEntityType(cliente);
    chegada_cliente->setTimeBetweenCreationsExpression("EXPO(20)");
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
    Assign::Assignment* a_nrProdutos = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "AINT(UNIF(1,20))");//AINT(DISC(0.45,UNIF(1,8),0.9,UNIF(9,12),1,UNIF(13,20)))
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


    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    chegada_cliente->getNextComponents()->insert(inicia_cliente);
    
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
