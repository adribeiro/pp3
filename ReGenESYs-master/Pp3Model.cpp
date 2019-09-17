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

#include "Pp3Model.h"

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

Pp3Model::Pp3Model() {
}

Pp3Model::Pp3Model(const Pp3Model& orig) {
}

Pp3Model::~Pp3Model() {
}

int Pp3Model::main(int argc, char** argv) {
    Simulator* simulator = new Simulator();

    // insert "fake plugins" since plugins based on dynamic loaded library are not implemented yet
    this->insertFakePluginsByHand(simulator);

    // creates an empty model
    Model* model = new Model(simulator);

    // Handle traces and simulation events to output them
    TraceManager* tm = model->getTraceManager();
    this->setDefaultTraceHandlers(tm);

    // get easy access to classes used to insert components and elements into a model
    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();
    
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(36000);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(1);
    infos->setDescription("./models/model01_CreDelDis.txt");

    EntityType* cliente = new EntityType(elements, "cliente");
    elements->insert(Util::TypeOf<EntityType>(), cliente);

    Create* chegada_cliente = new Create(model);
    chegada_cliente->setEntityType(cliente);
    chegada_cliente->setTimeBetweenCreationsExpression("EXPO(20)");
    chegada_cliente->setTimeUnit(Util::TimeUnit::second);
    chegada_cliente->setEntitiesPerCreation(1);
    components->insert(chegada_cliente);

    Decide* verifica_tempo_simulado = new Decide(model);
    verifica_tempo_simulado->getConditions()->insert("TNOW<10800 or TNOW>25200");
    
    Delay* dentro_horario_pico = new Delay(model);
    dentro_horario_pico->setDelayExpression("NORM(30,50)");
    dentro_horario_pico->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(dentro_horario_pico);
    
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
//    Attribute* attribute6 = new Attribute("nrProdutos");
    elements->insert(Util::TypeOf<Attribute>(), attribute1);
    elements->insert(Util::TypeOf<Attribute>(), attribute2);
    elements->insert(Util::TypeOf<Attribute>(), attribute3);
    elements->insert(Util::TypeOf<Attribute>(), attribute4);
    elements->insert(Util::TypeOf<Attribute>(), attribute5);
//    elements->insert(Util::TypeOf<Attribute>(), attribute6);
    
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
//    Assign::Assignment* nrProdutos = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "ANINT(DISC(0.45,UNIF(1,8),0.9,UNIF(9,12),1,UNIF(13,20)))");
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
//    define_tipo_cliente->getAssignments()->insert(nrProdutos);
    components->insert(define_tipo_cliente);
    
    Decide* identifica_tipo_cliente = new Decide(model);
    identifica_tipo_cliente->getConditions()->insert("tipo == 0");
    
    Attribute* attribute6 = new Attribute("tempo_caixa_idosos");
    elements->insert(Util::TypeOf<Attribute>(), attribute6);
    
    Assign* controla_tempo = new Assign(model);
    Assign::Assignment* tempo_caixa_idosos = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_caixa_idosos", "TNOW");
    controla_tempo->getAssignments()->insert(tempo_caixa_idosos);
    components->insert(controla_tempo);

    Dispose* saida_idoso = new Dispose(model);
    components->insert(saida_idoso);
    
    Dispose* saida_jovem = new Dispose(model);
    components->insert(saida_jovem);


    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    chegada_cliente->getNextComponents()->insert(verifica_tempo_simulado);
    verifica_tempo_simulado->getNextComponents()->insert(dentro_horario_pico);
    verifica_tempo_simulado->getNextComponents()->insert(define_tipo_cliente);
    dentro_horario_pico->getNextComponents()->insert(define_tipo_cliente);
    define_tipo_cliente->getNextComponents()->insert(identifica_tipo_cliente);
    identifica_tipo_cliente->getNextComponents()->insert(controla_tempo);
    identifica_tipo_cliente->getNextComponents()->insert(saida_jovem);
    controla_tempo->getNextComponents()->insert(saida_idoso);
    
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
