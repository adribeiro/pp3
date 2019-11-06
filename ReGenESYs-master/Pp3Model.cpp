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
#include "Batch.h"

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
//    tm->setTraceLevel(Util::TraceLevel::blockArrival);
    tm->setTraceLevel(Util::TraceLevel::report);

    // get easy access to classes used to insert components and elements into a model
    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();
    
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(36000);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setWarmUpPeriod(3600);
    infos->setWarmUpPeriodTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(10);
    infos->setDescription("./models/model01_CreDelDis.txt");

    //atributos
    Attribute* embalar = new Attribute("embalar");
    Attribute* pagar = new Attribute("pagar");
    Attribute* collector = new Attribute("collector");
    Attribute* tipo = new Attribute("tipo");
    Attribute* nrProdutos = new Attribute("nrProdutos");
    Attribute* tempo_registro = new Attribute("tempo_registro");
    Attribute* caixa_selecionado = new Attribute("caixa_selecionado");
    Attribute* tempo_caixa_idosos = new Attribute("tempo_caixa_idosos");
    Attribute* tempo_caixa = new Attribute("tempo_caixa");
    Attribute* registro = new Attribute("registro");
    Attribute* tempo_embalo = new Attribute("tempo_embalo");
    elements->insert(Util::TypeOf<Attribute>(), embalar);
    elements->insert(Util::TypeOf<Attribute>(), pagar);
    elements->insert(Util::TypeOf<Attribute>(), collector);
    elements->insert(Util::TypeOf<Attribute>(), tempo_caixa);
    elements->insert(Util::TypeOf<Attribute>(), tipo);
    elements->insert(Util::TypeOf<Attribute>(), nrProdutos);
    elements->insert(Util::TypeOf<Attribute>(), tempo_caixa_idosos);
    elements->insert(Util::TypeOf<Attribute>(), registro);
    elements->insert(Util::TypeOf<Attribute>(), tempo_embalo);
    elements->insert(Util::TypeOf<Attribute>(), caixa_selecionado);
    elements->insert(Util::TypeOf<Attribute>(), tempo_registro);
 
    
    //variaveis
    Variable* qtd_fila_1 = new Variable("qtd_fila_1");
    Variable* qtd_fila_2 = new Variable("qtd_fila_2");
    Variable* qtd_fila_3 = new Variable("qtd_fila_3");
    Variable* qtd_fila_4 = new Variable("qtd_fila_4");
    Variable* qtd_fila_5 = new Variable("qtd_fila_5");
    Variable* est_qtd_fila1 = new Variable("est_qtd_fila1");
    Variable* est_qtd_fila2 = new Variable("est_qtd_fila2");
    Variable* est_qtd_fila3 = new Variable("est_qtd_fila3");
    Variable* est_qtd_fila4 = new Variable("est_qtd_fila4");
    Variable* est_qtd_fila5 = new Variable("est_qtd_fila5");
//    Variable* tempo_registrar_produto = new Variable("tempo_registrar_produto");
//    tempo_registrar_produto->setValue(0.0578);
    Variable* registrados = new Variable("registrados");
    Variable* sacolas = new Variable("sacolas");
    Variable* aux_registro = new Variable("aux_registro");
    Variable* nProdutos = new Variable("nProdutos");
    Variable* tempo_registro_total = new Variable("tempo_registro_total");
    Variable* tempo_embalo_total = new Variable("tempo_embalo_total");
    Variable* tempo_caixa_total = new Variable("tempo_caixa_total");
    Variable* tempo_caixa_idosos_total = new Variable("tempo_caixa_idosos_total");
    Variable* contador = new Variable("contador");
    Variable* contador_idosos = new Variable("contador_idosos");
    elements->insert(Util::TypeOf<Variable>(), qtd_fila_1);
    elements->insert(Util::TypeOf<Variable>(), qtd_fila_2);
    elements->insert(Util::TypeOf<Variable>(), qtd_fila_3);
    elements->insert(Util::TypeOf<Variable>(), qtd_fila_4);
    elements->insert(Util::TypeOf<Variable>(), qtd_fila_5);
    elements->insert(Util::TypeOf<Variable>(), est_qtd_fila1);
    elements->insert(Util::TypeOf<Variable>(), est_qtd_fila2);
    elements->insert(Util::TypeOf<Variable>(), est_qtd_fila3);
    elements->insert(Util::TypeOf<Variable>(), est_qtd_fila4);
    elements->insert(Util::TypeOf<Variable>(), est_qtd_fila5);
//    elements->insert(Util::TypeOf<Variable>(), tempo_registrar_produto);
    elements->insert(Util::TypeOf<Variable>(), sacolas);
    elements->insert(Util::TypeOf<Variable>(), registrados);
    elements->insert(Util::TypeOf<Variable>(), aux_registro);
    elements->insert(Util::TypeOf<Variable>(), nProdutos);
    elements->insert(Util::TypeOf<Variable>(), tempo_registro_total);
    elements->insert(Util::TypeOf<Variable>(), tempo_embalo_total);
    elements->insert(Util::TypeOf<Variable>(), tempo_caixa_total);
    elements->insert(Util::TypeOf<Variable>(), tempo_caixa_idosos_total);
    elements->insert(Util::TypeOf<Variable>(), contador);
    elements->insert(Util::TypeOf<Variable>(), contador_idosos);
    
    
    //Resources e Sets
    Resource* registrador_1_IDOSO = new Resource(elements, "registrador_1_IDOSO");
    registrador_1_IDOSO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador_1_IDOSO);
    
    Resource* registrador_2_IDOSO = new Resource(elements, "registrador_2_IDOSO");
    registrador_2_IDOSO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador_2_IDOSO);
    
    Resource* registrador_1_OUTRO = new Resource(elements, "registrador_1_OUTRO");
    registrador_1_OUTRO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador_1_OUTRO);
    
    Resource* registrador_2_OUTRO = new Resource(elements, "registrador_2_OUTRO");
    registrador_2_OUTRO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador_2_OUTRO);
    
    Resource* registrador_3_OUTRO = new Resource(elements, "registrador_3_OUTRO");
    registrador_3_OUTRO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador_3_OUTRO);
    
    Resource* registrador_4_OUTRO = new Resource(elements, "registrador_4_OUTRO");
    registrador_4_OUTRO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador_4_OUTRO);
    
    Resource* registrador_5_OUTRO = new Resource(elements, "registrador_5_OUTRO");
    registrador_5_OUTRO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador_5_OUTRO);
    
    Resource* registrador_RAPIDO = new Resource(elements, "registrador_RAPIDO");
    registrador_RAPIDO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador_RAPIDO);
    
    Set* registradores_total = new Set(elements, "esteiras_total");
    registradores_total->setSetOfType(Util::TypeOf<Resource>());
    registradores_total->getElementSet()->insert(registrador_1_IDOSO);
    registradores_total->getElementSet()->insert(registrador_2_IDOSO);
    registradores_total->getElementSet()->insert(registrador_1_OUTRO);
    registradores_total->getElementSet()->insert(registrador_2_OUTRO);
    registradores_total->getElementSet()->insert(registrador_3_OUTRO);
    registradores_total->getElementSet()->insert(registrador_4_OUTRO);
    registradores_total->getElementSet()->insert(registrador_5_OUTRO);
    registradores_total->getElementSet()->insert(registrador_RAPIDO);
    elements->insert(Util::TypeOf<Set>(), registradores_total);
    
    Resource* esteira_1_IDOSO = new Resource(elements, "esteira_1_IDOSO");
    esteira_1_IDOSO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira_1_IDOSO);
    
    Resource* esteira_2_IDOSO = new Resource(elements, "esteira_2_IDOSO");
    esteira_2_IDOSO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira_2_IDOSO);
    
    Resource* esteira_1_OUTRO = new Resource(elements, "esteira_1_OUTRO");
    esteira_1_OUTRO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira_1_OUTRO);
    
    Resource* esteira_2_OUTRO = new Resource(elements, "esteira_2_OUTRO");
    esteira_2_OUTRO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira_2_OUTRO);
    
    Resource* esteira_3_OUTRO = new Resource(elements, "esteira_3_OUTRO");
    esteira_3_OUTRO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira_3_OUTRO);
    
    Resource* esteira_4_OUTRO = new Resource(elements, "esteira_4_OUTRO");
    esteira_4_OUTRO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira_4_OUTRO);
    
    Resource* esteira_5_OUTRO = new Resource(elements, "esteira_5_OUTRO");
    esteira_5_OUTRO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira_5_OUTRO);
    
    Resource* esteira_RAPIDO = new Resource(elements, "esteira_RAPIDO");
    esteira_RAPIDO->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira_RAPIDO);
    
    Set* esteiras_total = new Set(elements, "esteiras_total");
    esteiras_total->setSetOfType(Util::TypeOf<Resource>());
    esteiras_total->getElementSet()->insert(esteira_1_IDOSO);
    esteiras_total->getElementSet()->insert(esteira_2_IDOSO);
    esteiras_total->getElementSet()->insert(esteira_1_OUTRO);
    esteiras_total->getElementSet()->insert(esteira_2_OUTRO);
    esteiras_total->getElementSet()->insert(esteira_3_OUTRO);
    esteiras_total->getElementSet()->insert(esteira_4_OUTRO);
    esteiras_total->getElementSet()->insert(esteira_5_OUTRO);
    esteiras_total->getElementSet()->insert(esteira_RAPIDO);
    elements->insert(Util::TypeOf<Set>(), esteiras_total);
    
    
    Resource* caixa_1_IDOSO = new Resource(elements, "caixa_1_IDOSO");
    caixa_1_IDOSO->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa_1_IDOSO);
   
    Resource* caixa_2_IDOSO = new Resource(elements, "caixa_2_IDOSO");
    caixa_2_IDOSO->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa_2_IDOSO);
    
    Resource* caixa_1_OUTRO = new Resource(elements, "caixa_1_OUTRO");
    caixa_1_OUTRO->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa_1_OUTRO);
    
    Resource* caixa_2_OUTRO = new Resource(elements, "caixa_2_OUTRO");
    caixa_2_OUTRO->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa_2_OUTRO);
    
    Resource* caixa_3_OUTRO = new Resource(elements, "caixa_3_OUTRO");
    caixa_3_OUTRO->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa_3_OUTRO);
    
    Resource* caixa_4_OUTRO = new Resource(elements, "caixa_4_OUTRO");
    caixa_4_OUTRO->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa_4_OUTRO);
    
    Resource* caixa_5_OUTRO = new Resource(elements, "caixa_5_OUTRO");
    caixa_5_OUTRO->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa_5_OUTRO);
    
    Resource* caixa_RAPIDO = new Resource(elements, "caixa_RAPIDO");
    caixa_RAPIDO->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa_RAPIDO);

    Set* caixas_total = new Set(elements, "caixas_total");
    caixas_total->setSetOfType(Util::TypeOf<Resource>());
    caixas_total->getElementSet()->insert(caixa_1_IDOSO);
    caixas_total->getElementSet()->insert(caixa_2_IDOSO);
    caixas_total->getElementSet()->insert(caixa_1_OUTRO);
    caixas_total->getElementSet()->insert(caixa_2_OUTRO);
    caixas_total->getElementSet()->insert(caixa_3_OUTRO);
    caixas_total->getElementSet()->insert(caixa_4_OUTRO);
    caixas_total->getElementSet()->insert(caixa_5_OUTRO);
    caixas_total->getElementSet()->insert(caixa_RAPIDO);
    elements->insert(Util::TypeOf<Set>(), caixas_total);
    
    
    Set* caixas_nao_idoso = new Set(elements, "caixas_nao_IDOSO");
    caixas_nao_idoso->setSetOfType(Util::TypeOf<Resource>());
    caixas_nao_idoso->getElementSet()->insert(caixa_1_OUTRO);
    caixas_nao_idoso->getElementSet()->insert(caixa_2_OUTRO);
    caixas_nao_idoso->getElementSet()->insert(caixa_3_OUTRO);
    caixas_nao_idoso->getElementSet()->insert(caixa_4_OUTRO);
    caixas_nao_idoso->getElementSet()->insert(caixa_5_OUTRO);
    caixas_nao_idoso->getElementSet()->insert(caixa_RAPIDO);
    elements->insert(Util::TypeOf<Set>(), caixas_nao_idoso);
    
    Set* caixas_OUTRO = new Set(elements, "caixas_OUTRO");
    caixas_OUTRO->setSetOfType(Util::TypeOf<Resource>());
    caixas_OUTRO->getElementSet()->insert(caixa_1_OUTRO);
    caixas_OUTRO->getElementSet()->insert(caixa_2_OUTRO);
    caixas_OUTRO->getElementSet()->insert(caixa_3_OUTRO);
    caixas_OUTRO->getElementSet()->insert(caixa_4_OUTRO);
    caixas_OUTRO->getElementSet()->insert(caixa_5_OUTRO);
    elements->insert(Util::TypeOf<Set>(), caixas_OUTRO);
    
    Set* caixas_IDOSO = new Set(elements, "caixas_IDOSO");
    caixas_IDOSO->setSetOfType(Util::TypeOf<Resource>());
    caixas_IDOSO->getElementSet()->insert(caixa_1_IDOSO);
    caixas_IDOSO->getElementSet()->insert(caixa_2_IDOSO);
    elements->insert(Util::TypeOf<Set>(), caixas_IDOSO);
    
    Set* caixas_RAPIDO = new Set(elements, "caixas_RAPIDO");
    caixas_RAPIDO->getElementSet()->insert(caixa_RAPIDO);
    elements->insert(Util::TypeOf<Set>(), caixas_RAPIDO);
    
    
    
    //Queues
    Queue* fila_caixas_RAPIDO = new Queue(elements, "fila_caixas_RAPIDO");
    fila_caixas_RAPIDO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_caixas_RAPIDO);
    
    Queue* fila_1_IDOSO = new Queue(elements, "fila_1_IDOSO");
    fila_1_IDOSO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_1_IDOSO);
    
    Queue* fila_2_IDOSO = new Queue(elements, "fila_2_IDOSO");
    fila_2_IDOSO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_2_IDOSO);
    
    Queue* fila_1_OUTRO = new Queue(elements, "fila_1_OUTRO");
    fila_1_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_1_OUTRO);
    
    Queue* fila_2_OUTRO = new Queue(elements, "fila_2_OUTRO");
    fila_2_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_2_OUTRO);
    
    Queue* fila_3_OUTRO = new Queue(elements, "fila_3_OUTRO");
    fila_3_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_3_OUTRO);
    
    Queue* fila_4_OUTRO = new Queue(elements, "fila_4_OUTRO");
    fila_4_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_4_OUTRO);
    
    Queue* fila_5_OUTRO = new Queue(elements, "fila_5_OUTRO");
    fila_5_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_5_OUTRO);
    
    Queue* fila_esteira_Rapido = new Queue(elements, "fila_esteira_Rapido");
    fila_esteira_Rapido->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_esteira_Rapido);
    
    Queue* fila_esteira_1_IDOSO = new Queue(elements, "fila_esteira_1_IDOSO");
    fila_esteira_1_IDOSO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_esteira_1_IDOSO);
    
    Queue* fila_esteira_2_IDOSO = new Queue(elements, "fila_esteira_2_IDOSO");
    fila_esteira_2_IDOSO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_esteira_2_IDOSO);
    
    Queue* fila_esteira_1_OUTRO = new Queue(elements, "fila_esteira_1_OUTRO");
    fila_esteira_1_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_esteira_1_OUTRO);
    
    Queue* fila_esteira_2_OUTRO = new Queue(elements, "fila_esteira_2_OUTRO");
    fila_esteira_2_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_esteira_2_OUTRO);
    
    Queue* fila_esteira_3_OUTRO = new Queue(elements, "fila_esteira_3_OUTRO");
    fila_esteira_3_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_esteira_3_OUTRO);
    
    Queue* fila_esteira_4_OUTRO = new Queue(elements, "fila_esteira_4_OUTRO");
    fila_esteira_4_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_esteira_4_OUTRO);
    
    Queue* fila_esteira_5_OUTRO = new Queue(elements, "fila_esteira_5_OUTRO");
    fila_esteira_5_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_esteira_5_OUTRO);
    
    Queue* fila_registrador_RAPIDO = new Queue(elements, "fila_registrador_RAPIDO");
    fila_registrador_RAPIDO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_registrador_RAPIDO);
    
    Queue* fila_registrador_1_IDOSO = new Queue(elements, "fila_registrador_1_IDOSO");
    fila_registrador_1_IDOSO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_registrador_1_IDOSO);
    
    Queue* fila_registrador_2_IDOSO = new Queue(elements, "fila_registrador_2_IDOSO");
    fila_registrador_2_IDOSO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_registrador_2_IDOSO);
    
    Queue* fila_registrador_1_OUTRO = new Queue(elements, "fila_registrador_1_OUTRO");
    fila_registrador_1_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_registrador_1_OUTRO);
    
    Queue* fila_registrador_2_OUTRO = new Queue(elements, "fila_registrador_2_OUTRO");
    fila_registrador_2_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_registrador_2_OUTRO);
    
    Queue* fila_registrador_3_OUTRO = new Queue(elements, "fila_registrador_3_OUTRO");
    fila_registrador_3_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_registrador_3_OUTRO);
    
    Queue* fila_registrador_4_OUTRO = new Queue(elements, "fila_registrador_4_OUTRO");
    fila_registrador_4_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_registrador_4_OUTRO);
    
    Queue* fila_registrador_5_OUTRO = new Queue(elements, "fila_registrador_5_OUTRO");
    fila_registrador_5_OUTRO->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_registrador_5_OUTRO);
    
    //seizes
    Seize* entra_na_fila_RAPIDO = new Seize(model);
    entra_na_fila_RAPIDO->setResource(caixa_RAPIDO);
    entra_na_fila_RAPIDO->setQueue(fila_caixas_RAPIDO);
    components->insert(entra_na_fila_RAPIDO);
    
    Seize* entra_na_fila = new Seize(model);
    entra_na_fila->setSet(caixas_total);
    entra_na_fila->insertQueue(fila_1_IDOSO);
    entra_na_fila->insertQueue(fila_2_IDOSO);
    entra_na_fila->insertQueue(fila_1_OUTRO);
    entra_na_fila->insertQueue(fila_2_OUTRO);
    entra_na_fila->insertQueue(fila_3_OUTRO);
    entra_na_fila->insertQueue(fila_4_OUTRO);
    entra_na_fila->insertQueue(fila_5_OUTRO);
    entra_na_fila->insertQueue(fila_caixas_RAPIDO);
    entra_na_fila->setSaveAttribute("caixa_selecionado");
    entra_na_fila->setRule(Resource::ResourceRule::ESPECIFIC);
    components->insert(entra_na_fila);
    
    Seize* entra_esteira = new Seize(model);
    entra_esteira->setSet(esteiras_total);
    entra_esteira->insertQueue(fila_esteira_1_IDOSO);
    entra_esteira->insertQueue(fila_esteira_2_IDOSO);
    entra_esteira->insertQueue(fila_esteira_1_OUTRO);
    entra_esteira->insertQueue(fila_esteira_2_OUTRO);
    entra_esteira->insertQueue(fila_esteira_3_OUTRO);
    entra_esteira->insertQueue(fila_esteira_4_OUTRO);
    entra_esteira->insertQueue(fila_esteira_5_OUTRO);
    entra_esteira->insertQueue(fila_esteira_Rapido);
    entra_esteira->setSaveAttribute("caixa_selecionado");
    entra_esteira->setRule(Resource::ResourceRule::ESPECIFIC);
    components->insert(entra_esteira);
    
    Seize* aloca_registrador = new Seize(model);
    aloca_registrador->setSet(registradores_total);
    aloca_registrador->insertQueue(fila_registrador_1_IDOSO);
    aloca_registrador->insertQueue(fila_registrador_2_IDOSO);
    aloca_registrador->insertQueue(fila_registrador_1_OUTRO);
    aloca_registrador->insertQueue(fila_registrador_2_OUTRO);
    aloca_registrador->insertQueue(fila_registrador_3_OUTRO);
    aloca_registrador->insertQueue(fila_registrador_4_OUTRO);
    aloca_registrador->insertQueue(fila_registrador_5_OUTRO);
    aloca_registrador->insertQueue(fila_registrador_RAPIDO);
    aloca_registrador->setSaveAttribute("caixa_selecionado");
    aloca_registrador->setRule(Resource::ResourceRule::ESPECIFIC);
    components->insert(aloca_registrador);
    
    Seize* aloca_registrador_2 = new Seize(model);
    aloca_registrador_2->setSet(registradores_total);
    aloca_registrador_2->insertQueue(fila_registrador_1_IDOSO);
    aloca_registrador_2->insertQueue(fila_registrador_2_IDOSO);
    aloca_registrador_2->insertQueue(fila_registrador_1_OUTRO);
    aloca_registrador_2->insertQueue(fila_registrador_2_OUTRO);
    aloca_registrador_2->insertQueue(fila_registrador_3_OUTRO);
    aloca_registrador_2->insertQueue(fila_registrador_4_OUTRO);
    aloca_registrador_2->insertQueue(fila_registrador_5_OUTRO);
    aloca_registrador_2->insertQueue(fila_registrador_RAPIDO);
    aloca_registrador_2->setSaveAttribute("caixa_selecionado");
    aloca_registrador_2->setRule(Resource::ResourceRule::ESPECIFIC);
    aloca_registrador_2->setPriority(1);
    components->insert(aloca_registrador_2);
//   
    //Release
    Release* sai_da_esteira = new Release(model);
    sai_da_esteira->setSet(esteiras_total);
    sai_da_esteira->setSaveAttribute("caixa_selecionado");
    components->insert(sai_da_esteira);
    
    Release* libera_registrador = new Release(model);
    libera_registrador->setSet(registradores_total);
    libera_registrador->setSaveAttribute("caixa_selecionado");
    components->insert(libera_registrador);
    
    Release* libera_registrador_2 = new Release(model);
    libera_registrador_2->setSet(registradores_total);
    libera_registrador_2->setSaveAttribute("caixa_selecionado");
    components->insert(libera_registrador_2);
    
    Release* libera_caixa = new Release(model);
    libera_caixa->setSet(caixas_total);
    libera_caixa->setSaveAttribute("caixa_selecionado");
    components->insert(libera_caixa);
   
    
    //entidades
    EntityType* cliente = new EntityType(elements, "cliente");
    elements->insert(Util::TypeOf<EntityType>(), cliente);
    
    EntityType* produto = new EntityType(elements, "produto");
    elements->insert(Util::TypeOf<EntityType>(), produto);
    
    
    //create e disposes
    
    Create* cliente_chega_para_pagar = new Create(model);
    cliente_chega_para_pagar->setEntityType(cliente);
    cliente_chega_para_pagar->setTimeBetweenCreationsExpression("EXPO(20)");
    cliente_chega_para_pagar->setTimeUnit(Util::TimeUnit::second);
    cliente_chega_para_pagar->setEntitiesPerCreation(1);
    components->insert(cliente_chega_para_pagar);
    
    Dispose* cliente_sai_do_caixa = new Dispose(model);
    components->insert(cliente_sai_do_caixa);

    
    //decides
    Decide* verifica_tempo_simulado = new Decide(model);
    verifica_tempo_simulado->getConditions()->insert("TNOW<10800 or TNOW>25200");
    
    Decide* identifica_tipo_de_cliente = new Decide(model);
    identifica_tipo_de_cliente->getConditions()->insert("UNIF(0,1) < 0.3");
    
    Decide* idoso_decide_fila = new Decide(model);
    idoso_decide_fila->getConditions()->insert("STATE(caixa_1_IDOSO) == 1");
    idoso_decide_fila->getConditions()->insert("STATE(caixa_2_IDOSO) == 1");
    idoso_decide_fila->getConditions()->insert("SETSUM(caixas_nao_IDOSO) < NUMSET(caixas_nao_IDOSO)");
    idoso_decide_fila->getConditions()->insert("nrProdutos < 9 and NQ(fila_caixas_RAPIDO) < 5");
    idoso_decide_fila->getConditions()->insert("NQ(fila_1_IDOSO) < NQ(fila_2_IDOSO)");
    

    Decide* carrinho_ou_cestinha = new Decide(model);
    carrinho_ou_cestinha->getConditions()->insert("nrProdutos < 9");
    
    Decide* decide_para_cestinha = new Decide(model);
    decide_para_cestinha->getConditions()->insert("SETSUM(caixas_RAPIDO) < NUMSET(caixas_RAPIDO)");
    decide_para_cestinha->getConditions()->insert("SETSUM(caixas_OUTRO) < NUMSET(caixas_OUTRO)");
    decide_para_cestinha->getConditions()->insert("SETSUM(caixas_IDOSO) < NUMSET(caixas_IDOSO)");
    
    Decide* verifica_fila_vazia = new Decide(model);
    verifica_fila_vazia->getConditions()->insert("STATE(caixa_1_OUTRO) == 1");
    verifica_fila_vazia->getConditions()->insert("STATE(caixa_2_OUTRO) == 1");
    verifica_fila_vazia->getConditions()->insert("STATE(caixa_3_OUTRO) == 1");
    verifica_fila_vazia->getConditions()->insert("STATE(caixa_4_OUTRO) == 1");
    
    Decide* decide_para_carrinho = new Decide(model);
    decide_para_carrinho->getConditions()->insert("SETSUM(caixas_OUTRO) < NUMSET(caixas_OUTRO)");
    decide_para_carrinho->getConditions()->insert("SETSUM(caixas_IDOSO) < NUMSET(caixas_IDOSO)");
    
    Decide* estima_pelo_tamanho_ou_nr_de_produtos = new Decide(model);
    estima_pelo_tamanho_ou_nr_de_produtos->getConditions()->insert("UNIF(0,1) < 0.5");
    
    Decide* verifica_menor_fila = new Decide(model);
    verifica_menor_fila->getConditions()->insert("NQ(fila_1_OUTRO) <= NQ(fila_2_OUTRO) and NQ(fila_1_OUTRO) <= NQ(fila_3_OUTRO) and NQ(fila_1_OUTRO) <= NQ(fila_4_OUTRO) and NQ(fila_1_OUTRO) <= NQ(fila_5_OUTRO)");
    verifica_menor_fila->getConditions()->insert("NQ(fila_2_OUTRO) <= NQ(fila_1_OUTRO) and NQ(fila_2_OUTRO) <= NQ(fila_3_OUTRO) and NQ(fila_2_OUTRO) <= NQ(fila_4_OUTRO) and NQ(fila_2_OUTRO) <= NQ(fila_5_OUTRO)");
    verifica_menor_fila->getConditions()->insert("NQ(fila_3_OUTRO) <= NQ(fila_1_OUTRO) and NQ(fila_3_OUTRO) <= NQ(fila_2_OUTRO) and NQ(fila_3_OUTRO) <= NQ(fila_4_OUTRO) and NQ(fila_3_OUTRO) <= NQ(fila_5_OUTRO)");
    verifica_menor_fila->getConditions()->insert("NQ(fila_4_OUTRO) <= NQ(fila_1_OUTRO) and NQ(fila_4_OUTRO) <= NQ(fila_2_OUTRO) and NQ(fila_4_OUTRO) <= NQ(fila_3_OUTRO) and NQ(fila_4_OUTRO) <= NQ(fila_5_OUTRO)");
        
    Decide* verifica_menos_produtos = new Decide(model);
    verifica_menos_produtos->getConditions()->insert("est_qtd_fila1 < est_qtd_fila2 and est_qtd_fila1 < est_qtd_fila3 and est_qtd_fila1 < est_qtd_fila4 and est_qtd_fila1 < est_qtd_fila5");
    verifica_menos_produtos->getConditions()->insert("est_qtd_fila2 < est_qtd_fila1 and est_qtd_fila2 < est_qtd_fila3 and est_qtd_fila2 < est_qtd_fila4 and est_qtd_fila2 < est_qtd_fila5");
    verifica_menos_produtos->getConditions()->insert("est_qtd_fila3 < est_qtd_fila1 and est_qtd_fila3 < est_qtd_fila2 and est_qtd_fila3 < est_qtd_fila4 and est_qtd_fila3 < est_qtd_fila5");
    verifica_menos_produtos->getConditions()->insert("est_qtd_fila4 < est_qtd_fila1 and est_qtd_fila4 < est_qtd_fila2 and est_qtd_fila4 < est_qtd_fila3 and est_qtd_fila4 < est_qtd_fila5");
    
        
    Decide* ultimo_produto = new Decide(model);
    ultimo_produto->getConditions()->insert("registro==nrProdutos");
    
    Decide* ultimo_produto_2 = new Decide(model);
    ultimo_produto_2->getConditions()->insert("registro==nrProdutos");
    
    Decide* eh_idoso = new Decide(model);
    eh_idoso->getConditions()->insert("tipo==0");
    
    //delays
    Delay* fora_de_horario_de_pico = new Delay(model);
    fora_de_horario_de_pico->setName("fora_de_horario_de_pico");
    fora_de_horario_de_pico->setDelayExpression("NORM(50,30)");
    fora_de_horario_de_pico->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(fora_de_horario_de_pico);
    
    Delay* vai_para_fila_RAPIDO = new Delay(model);
    vai_para_fila_RAPIDO->setName("vai_para_fila_RAPIDO");
    vai_para_fila_RAPIDO->setDelayExpression("UNIF(2,5)");
    vai_para_fila_RAPIDO->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(vai_para_fila_RAPIDO);
    
        
    Delay* pegando_produtos = new Delay(model);
    pegando_produtos->setName("pegando_produtos");
    pegando_produtos->setDelayExpression("NORM(1.5,0.8)");
    pegando_produtos->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(pegando_produtos);
        
    Delay* tempo_na_esteira = new Delay(model);
    tempo_na_esteira->setName("tempo_na_esteira");
    tempo_na_esteira->setDelayExpression("3");
    tempo_na_esteira->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(tempo_na_esteira);
        
    Delay* tempo_para_registrar = new Delay(model);
    tempo_para_registrar->setName("tempo_para_registrar");
    tempo_para_registrar->setDelayExpression("0.0578");
    tempo_para_registrar->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(tempo_para_registrar);
        
    Delay* tempo_para_embalar = new Delay(model);
    tempo_para_embalar->setName("tempo_para_embalar");
    tempo_para_embalar->setDelayExpression("UNIF(1,2) * embalar");
    tempo_para_embalar->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(tempo_para_embalar);
        
    Delay* tempo_para_pagar = new Delay(model);
    tempo_para_pagar->setName("tempo_para_pagar");
    tempo_para_pagar->setDelayExpression("NORM(8,3)");
    tempo_para_pagar->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(tempo_para_pagar);
    
    //assigns
    Assign* define_tipo_de_cliente = new Assign(model);
    Assign::Assignment* a_qtd_fila_1 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_1", "0");
    Assign::Assignment* a_qtd_fila_2 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_2", "0");
    Assign::Assignment* a_qtd_fila_3 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_3", "0");
    Assign::Assignment* a_qtd_fila_4 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_4", "0");
    Assign::Assignment* a_qtd_fila_5 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_5", "0");
    Assign::Assignment* a_embalar = new Assign::Assignment(Assign::DestinationType::Attribute, "embalar", "100");
    Assign::Assignment* a_pagar = new Assign::Assignment(Assign::DestinationType::Attribute, "pagar", "100");
    Assign::Assignment* a_collector = new Assign::Assignment(Assign::DestinationType::Attribute, "collector", "0");
    Assign::Assignment* a_tipo_jovem = new Assign::Assignment(Assign::DestinationType::Attribute, "tipo", "1");//DISC(0.3,0,1,1)
    Assign::Assignment* a_tempo_caixa = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_caixa", "TNOW");
    Assign::Assignment* a_nrProdutos = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "UNIF(0,1)");//TRUNC(DISC(0.45,UNIF(1,8),0.9,UNIF(9,12),1,UNIF(13,20)))
    define_tipo_de_cliente->getAssignments()->insert(a_qtd_fila_1);
    define_tipo_de_cliente->getAssignments()->insert(a_qtd_fila_2);
    define_tipo_de_cliente->getAssignments()->insert(a_qtd_fila_3);
    define_tipo_de_cliente->getAssignments()->insert(a_qtd_fila_4);
    define_tipo_de_cliente->getAssignments()->insert(a_qtd_fila_5);
    define_tipo_de_cliente->getAssignments()->insert(a_embalar);
    define_tipo_de_cliente->getAssignments()->insert(a_pagar);
    define_tipo_de_cliente->getAssignments()->insert(a_collector);
    define_tipo_de_cliente->getAssignments()->insert(a_tipo_jovem);
    define_tipo_de_cliente->getAssignments()->insert(a_tempo_caixa);
    define_tipo_de_cliente->getAssignments()->insert(a_nrProdutos);
    components->insert(define_tipo_de_cliente);
    
    Assign* controla_tempo = new Assign(model);
    Assign::Assignment* a_tempo_caixa_idosos = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_caixa_idosos", "TNOW");
    Assign::Assignment* a_tipo_idoso = new Assign::Assignment(Assign::DestinationType::Attribute, "tipo", "0");
    controla_tempo->getAssignments()->insert(a_tempo_caixa_idosos);
    controla_tempo->getAssignments()->insert(a_tipo_idoso);
    components->insert(controla_tempo);
    
        
    Assign* fila_selecionada_1_idoso = new Assign(model);
    Assign::Assignment* a_caixa1_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "0");
    Assign::Assignment* a_nProdutos1 = new Assign::Assignment(Assign::DestinationType::VariableArray, "nProdutos","nrProdutos");
    a_nProdutos1->setDestinationArray("caixa_selecionado",0);
    fila_selecionada_1_idoso->getAssignments()->insert(a_caixa1_selecionado);
    fila_selecionada_1_idoso->getAssignments()->insert(a_nProdutos1);
    components->insert(fila_selecionada_1_idoso);
    
    Assign* fila_selecionada_2_idoso = new Assign(model);
    Assign::Assignment* a_caixa2_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "1");
    Assign::Assignment* a_nProdutos2 = new Assign::Assignment(Assign::DestinationType::VariableArray, "nProdutos","nrProdutos");
    a_nProdutos2->setDestinationArray("caixa_selecionado",0);
    fila_selecionada_2_idoso->getAssignments()->insert(a_caixa2_selecionado);
    fila_selecionada_2_idoso->getAssignments()->insert(a_nProdutos2);
    components->insert(fila_selecionada_2_idoso);
    
    Assign* adiciona_7 = new Assign(model);
    Assign::Assignment* a_caixaR_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "7");
    Assign::Assignment* a_nProdutos7 = new Assign::Assignment(Assign::DestinationType::VariableArray, "nProdutos","nrProdutos");
    a_nProdutos7->setDestinationArray("caixa_selecionado",0);
    adiciona_7->getAssignments()->insert(a_caixaR_selecionado);
    adiciona_7->getAssignments()->insert(a_nProdutos7);
    components->insert(adiciona_7);
    
    Assign* atribui_nr_de_produtos_de_cada_fila = new Assign(model);
    Assign::Assignment* a_est_qtd_fila1 = new Assign::Assignment(Assign::DestinationType::Variable, "est_qtd_fila1", "UNIF(qtd_fila_1*0.7,qtd_fila_1*1.3)");
    Assign::Assignment* a_est_qtd_fila2 = new Assign::Assignment(Assign::DestinationType::Variable, "est_qtd_fila2","UNIF(qtd_fila_2*0.7,qtd_fila_2*1.3)");
    Assign::Assignment* a_est_qtd_fila3 = new Assign::Assignment(Assign::DestinationType::Variable, "est_qtd_fila3", "UNIF(qtd_fila_3*0.7,qtd_fila_3*1.3)");
    Assign::Assignment* a_est_qtd_fila4 = new Assign::Assignment(Assign::DestinationType::Variable, "est_qtd_fila4","UNIF(qtd_fila_4*0.7,qtd_fila_4*1.3)");
    Assign::Assignment* a_est_qtd_fila5 = new Assign::Assignment(Assign::DestinationType::Variable, "est_qtd_fila5", "UNIF(qtd_fila_5*0.7,qtd_fila_5*1.3)");
    atribui_nr_de_produtos_de_cada_fila->getAssignments()->insert(a_est_qtd_fila1);
    atribui_nr_de_produtos_de_cada_fila->getAssignments()->insert(a_est_qtd_fila2);
    atribui_nr_de_produtos_de_cada_fila->getAssignments()->insert(a_est_qtd_fila3);
    atribui_nr_de_produtos_de_cada_fila->getAssignments()->insert(a_est_qtd_fila4);
    atribui_nr_de_produtos_de_cada_fila->getAssignments()->insert(a_est_qtd_fila5);
    components->insert(atribui_nr_de_produtos_de_cada_fila);
    
    Assign* fila_selecionada_1_OUTRO = new Assign(model);
    Assign::Assignment* a_caixa1J_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "2");
    Assign::Assignment* a_nProdutos1J = new Assign::Assignment(Assign::DestinationType::VariableArray, "nProdutos","nrProdutos");
    a_nProdutos1J->setDestinationArray("caixa_selecionado",0);
    fila_selecionada_1_OUTRO->getAssignments()->insert(a_caixa1J_selecionado);
    fila_selecionada_1_OUTRO->getAssignments()->insert(a_nProdutos1J);
    components->insert(fila_selecionada_1_OUTRO);
    
    Assign* fila_selecionada_2_OUTRO = new Assign(model);
    Assign::Assignment* a_caixa2J_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "3");
    Assign::Assignment* a_nProdutos2J = new Assign::Assignment(Assign::DestinationType::VariableArray, "nProdutos","nrProdutos");
    a_nProdutos2J->setDestinationArray("caixa_selecionado",0);
    fila_selecionada_2_OUTRO->getAssignments()->insert(a_caixa2J_selecionado);
    fila_selecionada_2_OUTRO->getAssignments()->insert(a_nProdutos2J);
    components->insert(fila_selecionada_2_OUTRO);
    
    Assign* fila_selecionada_3_OUTRO = new Assign(model);
    Assign::Assignment* a_caixa3J_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "4");
    Assign::Assignment* a_nProdutos3J = new Assign::Assignment(Assign::DestinationType::VariableArray, "nProdutos","nrProdutos");
    a_nProdutos3J->setDestinationArray("caixa_selecionado",0);
    fila_selecionada_3_OUTRO->getAssignments()->insert(a_caixa3J_selecionado);
    fila_selecionada_3_OUTRO->getAssignments()->insert(a_nProdutos3J);
    components->insert(fila_selecionada_3_OUTRO);
    
    Assign* fila_selecionada_4_OUTRO = new Assign(model);
    Assign::Assignment* a_caixa4J_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "5");
    Assign::Assignment* a_nProdutos4J = new Assign::Assignment(Assign::DestinationType::VariableArray, "nProdutos","nrProdutos");
    a_nProdutos4J->setDestinationArray("caixa_selecionado",0);
    fila_selecionada_4_OUTRO->getAssignments()->insert(a_caixa4J_selecionado);
    fila_selecionada_4_OUTRO->getAssignments()->insert(a_nProdutos4J);
    components->insert(fila_selecionada_4_OUTRO);
    
    Assign* fila_selecionada_5_OUTRO = new Assign(model);
    Assign::Assignment* a_caixa5J_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "6");
    Assign::Assignment* a_nProdutos5J = new Assign::Assignment(Assign::DestinationType::VariableArray, "nProdutos","nrProdutos");
    a_nProdutos5J->setDestinationArray("caixa_selecionado",0);
    fila_selecionada_5_OUTRO->getAssignments()->insert(a_caixa5J_selecionado);
    fila_selecionada_5_OUTRO->getAssignments()->insert(a_nProdutos5J);
    components->insert(fila_selecionada_5_OUTRO);
        
    Assign* calcula_quantidade_produto_filas = new Assign(model);
    Assign::Assignment* a1_qtd_fila_1 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_1", "SAQUE(fila_1_OUTRO,nrProdutos)");
    Assign::Assignment* a1_qtd_fila_2 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_2","SAQUE(fila_2_OUTRO,nrProdutos)");
    Assign::Assignment* a1_qtd_fila_3 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_3", "SAQUE(fila_3_OUTRO,nrProdutos)");
    Assign::Assignment* a1_qtd_fila_4 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_4","SAQUE(fila_4_OUTRO,nrProdutos)");
    Assign::Assignment* a1_qtd_fila_5 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_5", "SAQUE(fila_5_OUTRO,nrProdutos)");
    calcula_quantidade_produto_filas->getAssignments()->insert(a1_qtd_fila_1);
    calcula_quantidade_produto_filas->getAssignments()->insert(a1_qtd_fila_2);
    calcula_quantidade_produto_filas->getAssignments()->insert(a1_qtd_fila_3);
    calcula_quantidade_produto_filas->getAssignments()->insert(a1_qtd_fila_4);
    calcula_quantidade_produto_filas->getAssignments()->insert(a1_qtd_fila_5);
    components->insert(calcula_quantidade_produto_filas);
    
//    Assign* assign_48 = new Assign(model);
//    Assign::Assignment* a_entityType = new Assign::Assignment(Assign::DestinationType::Entity, "produto","");
//    assign_48->getAssignments()->insert(a_entityType);
//    components->insert(assign_48);
        
    Assign* inicio_do_registro = new Assign(model);
    Assign::Assignment* a_tempo_registro = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_registro", "TNOW");
    inicio_do_registro->getAssignments()->insert(a_tempo_registro);
    components->insert(inicio_do_registro);
        
    Assign* adiciona_registrados = new Assign(model);
    Assign::Assignment* a_registrados = new Assign::Assignment(Assign::DestinationType::VariableArray, "registrados","registrados");
    a_registrados->setDestinationExpressionArray("caixa_selecionado","caixa_selecionado",1);
    Assign::Assignment* a_registro = new Assign::Assignment(Assign::DestinationType::Attribute, "registro", "registrados");
    a_registro->setExpressionArray("caixa_selecionado",0);
    adiciona_registrados->getAssignments()->insert(a_registrados);
    adiciona_registrados->getAssignments()->insert(a_registro);
    components->insert(adiciona_registrados);
        
    Assign* fim_do_registro = new Assign(model);
    Assign::Assignment* a_fim_tempo_registro = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_registro", "TNOW-tempo_registro");
    Assign::Assignment* a_tempo_registro_total = new Assign::Assignment(Assign::DestinationType::Variable, "tempo_registro_total","tempo_registro_total+tempo_registro");
    fim_do_registro->getAssignments()->insert(a_fim_tempo_registro);
    fim_do_registro->getAssignments()->insert(a_tempo_registro_total);
    components->insert(fim_do_registro);
        
    Assign* adiciona_aux = new Assign(model);
    Assign::Assignment* a_aux_registro = new Assign::Assignment(Assign::DestinationType::VariableArray, "aux_registro","aux_registro");
    a_aux_registro->setDestinationExpressionArray("caixa_selecionado","caixa_selecionado",1);
    adiciona_aux->getAssignments()->insert(a_aux_registro);
    components->insert(adiciona_aux);
        
    Assign* inicio_do_embalo = new Assign(model);
    Assign::Assignment* a_tempo_embalo = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_embalo", "TNOW");
    inicio_do_embalo->getAssignments()->insert(a_tempo_embalo);
    components->insert(inicio_do_embalo);
    
    Assign* libera_batch = new Assign(model);
    Assign::Assignment* a_embalar1 = new Assign::Assignment(Assign::DestinationType::Attribute, "embalar", "aux_registro");
    a_embalar1->setExpressionArray("caixa_selecionado",0);
    Assign::Assignment* a_collector1 = new Assign::Assignment(Assign::DestinationType::Attribute, "collector", "1");
    libera_batch->getAssignments()->insert(a_embalar1);
    libera_batch->getAssignments()->insert(a_collector1);
    components->insert(libera_batch);
        
    Assign* limpa_aux = new Assign(model);
    Assign::Assignment* a_aux_registro1 = new Assign::Assignment(Assign::DestinationType::VariableArray, "aux_registro","0");
    a_aux_registro1->setDestinationArray("caixa_selecionado",0);
    limpa_aux->getAssignments()->insert(a_aux_registro1);
    components->insert(limpa_aux);
        
    Assign* adiciona_sacolas = new Assign(model);
    Assign::Assignment* a_sacolas = new Assign::Assignment(Assign::DestinationType::VariableArray, "sacolas","sacolas");
    a_sacolas->setDestinationExpressionArray("caixa_selecionado","caixa_selecionado",1);
    adiciona_sacolas->getAssignments()->insert(a_sacolas);
    components->insert(adiciona_sacolas);
        
    Assign* libera_batch_2 = new Assign(model);
    Assign::Assignment* a_pagar1 = new Assign::Assignment(Assign::DestinationType::Attribute, "pagar", "sacolas");
    a_pagar1->setExpressionArray("caixa_selecionado",0);
    libera_batch_2->getAssignments()->insert(a_pagar1);
    components->insert(libera_batch_2);
    
        
    Assign* fim_do_embalo = new Assign(model);
    Assign::Assignment* a_tempo_embalo1 = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_embalo", "TNOW-tempo_embalo");
    Assign::Assignment* a_tempo_embalo_total = new Assign::Assignment(Assign::DestinationType::Variable, "tempo_embalo_total","tempo_embalo_total+tempo_embalo");
    fim_do_embalo->getAssignments()->insert(a_tempo_embalo1);
    fim_do_embalo->getAssignments()->insert(a_tempo_embalo_total);
    components->insert(fim_do_embalo);
    
    Assign* sai_do_caixa = new Assign(model);
    Assign::Assignment* a_tempo_caixa_saida = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_caixa", "TNOW-tempo_caixa");
    Assign::Assignment* a_tempo_caixa_total_saida = new Assign::Assignment(Assign::DestinationType::Variable, "tempo_caixa_total","tempo_caixa_total+tempo_caixa");
    Assign::Assignment* a_contador = new Assign::Assignment(Assign::DestinationType::Variable, "contador","contador+1");
    sai_do_caixa->getAssignments()->insert(a_tempo_caixa_saida);
    sai_do_caixa->getAssignments()->insert(a_tempo_caixa_total_saida);
    sai_do_caixa->getAssignments()->insert(a_contador);
    components->insert(sai_do_caixa);
    
    Assign* sai_do_caixa_2 = new Assign(model);
    Assign::Assignment* a_tempo_caixa_velho = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_caixa", "TNOW-tempo_caixa");
    Assign::Assignment* a_tempo_caixa_total_velho = new Assign::Assignment(Assign::DestinationType::Variable, "tempo_caixa_total","tempo_caixa_total+tempo_caixa");
    Assign::Assignment* a_tempo_idosos_velho = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_caixa_idosos", "TNOW-tempo_caixa_idosos");
    Assign::Assignment* a_tempo_idosos_total_velho = new Assign::Assignment(Assign::DestinationType::Variable, "tempo_caixa_idosos_total","tempo_caixa_idosos_total+tempo_caixa_idosos");
    Assign::Assignment* a_contador_velho = new Assign::Assignment(Assign::DestinationType::Variable, "contador","contador+1");
    Assign::Assignment* a_contador1_velho = new Assign::Assignment(Assign::DestinationType::Variable, "contador_idosos","contador_idosos+1");
    sai_do_caixa_2->getAssignments()->insert(a_tempo_caixa_velho);
    sai_do_caixa_2->getAssignments()->insert(a_tempo_caixa_total_velho);
    sai_do_caixa_2->getAssignments()->insert(a_tempo_idosos_velho);
    sai_do_caixa_2->getAssignments()->insert(a_tempo_idosos_total_velho);
    sai_do_caixa_2->getAssignments()->insert(a_contador_velho);
    sai_do_caixa_2->getAssignments()->insert(a_contador1_velho);
    components->insert(sai_do_caixa_2);
    
    Assign* limpa_variaveis = new Assign(model);
    Assign::Assignment* a_limpa_registrados = new Assign::Assignment(Assign::DestinationType::VariableArray, "registrados","0");
    a_limpa_registrados->setDestinationArray("caixa_selecionado",0);
    Assign::Assignment* a_limpa_sacolas = new Assign::Assignment(Assign::DestinationType::VariableArray, "sacolas","0");
    a_limpa_sacolas->setDestinationArray("caixa_selecionado",0);
    Assign::Assignment* a_limpa_nProdutos = new Assign::Assignment(Assign::DestinationType::VariableArray, "nProdutos","0");
    a_limpa_nProdutos->setDestinationArray("caixa_selecionado",0);
    limpa_aux->getAssignments()->insert(a_limpa_registrados);
    limpa_aux->getAssignments()->insert(a_limpa_sacolas);
    limpa_aux->getAssignments()->insert(a_limpa_nProdutos);
    components->insert(limpa_aux);
    
    //Batch e Separate
        
    Separate* separa_produtos = new Separate(model);
    separa_produtos->setSplitBatch(false);
    separa_produtos->setAmountToDuplicate("nrProdutos");
    components->insert(separa_produtos);
    
    Decide* decide_espera_produtos = new Decide(model);
    decide_espera_produtos->getConditions()->insert("caixa_selecionado==0");
    decide_espera_produtos->getConditions()->insert("caixa_selecionado==1");
    decide_espera_produtos->getConditions()->insert("caixa_selecionado==2");
    decide_espera_produtos->getConditions()->insert("caixa_selecionado==3");
    decide_espera_produtos->getConditions()->insert("caixa_selecionado==4");
    decide_espera_produtos->getConditions()->insert("caixa_selecionado==5");
    decide_espera_produtos->getConditions()->insert("caixa_selecionado==6");
    
    Batch* espera_produtos0 = new Batch(model);
    espera_produtos0->setByAttributeBatch(true);
    espera_produtos0->setAttributeName("caixa_selecionado");
    espera_produtos0->setPermanentBatch(false);
    espera_produtos0->setExpression("embalar");
    espera_produtos0->setBatchName("espera_produtos");
    espera_produtos0->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_produtos0);
    
    Batch* espera_produtos1 = new Batch(model);
    espera_produtos1->setByAttributeBatch(true);
    espera_produtos1->setAttributeName("caixa_selecionado");
    espera_produtos1->setPermanentBatch(false);
    espera_produtos1->setExpression("embalar");
    espera_produtos1->setBatchName("espera_produtos");
    espera_produtos1->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_produtos1);
    
    Batch* espera_produtos2 = new Batch(model);
    espera_produtos2->setByAttributeBatch(true);
    espera_produtos2->setAttributeName("caixa_selecionado");
    espera_produtos2->setPermanentBatch(false);
    espera_produtos2->setExpression("embalar");
    espera_produtos2->setBatchName("espera_produtos");
    espera_produtos2->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_produtos2);
    
    Batch* espera_produtos3 = new Batch(model);
    espera_produtos3->setByAttributeBatch(true);
    espera_produtos3->setAttributeName("caixa_selecionado");
    espera_produtos3->setPermanentBatch(false);
    espera_produtos3->setExpression("embalar");
    espera_produtos3->setBatchName("espera_produtos");
    espera_produtos3->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_produtos3);
    
    Batch* espera_produtos4 = new Batch(model);
    espera_produtos4->setByAttributeBatch(true);
    espera_produtos4->setAttributeName("caixa_selecionado");
    espera_produtos4->setPermanentBatch(false);
    espera_produtos4->setExpression("embalar");
    espera_produtos4->setBatchName("espera_produtos");
    espera_produtos4->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_produtos4);
    
    Batch* espera_produtos5 = new Batch(model);
    espera_produtos5->setByAttributeBatch(true);
    espera_produtos5->setAttributeName("caixa_selecionado");
    espera_produtos5->setPermanentBatch(false);
    espera_produtos5->setExpression("embalar");
    espera_produtos5->setBatchName("espera_produtos");
    espera_produtos5->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_produtos5);
    
    Batch* espera_produtos6 = new Batch(model);
    espera_produtos6->setByAttributeBatch(true);
    espera_produtos6->setAttributeName("caixa_selecionado");
    espera_produtos6->setPermanentBatch(false);
    espera_produtos6->setExpression("embalar");
    espera_produtos6->setBatchName("espera_produtos");
    espera_produtos6->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_produtos6);
    
    Batch* espera_produtos7 = new Batch(model);
    espera_produtos7->setByAttributeBatch(true);
    espera_produtos7->setAttributeName("caixa_selecionado");
    espera_produtos7->setPermanentBatch(false);
    espera_produtos7->setExpression("embalar");
    espera_produtos7->setBatchName("espera_produtos");
    espera_produtos7->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_produtos7);
    
    Decide* decide_espera_para_pagar = new Decide(model);
    decide_espera_para_pagar->getConditions()->insert("caixa_selecionado==0");
    decide_espera_para_pagar->getConditions()->insert("caixa_selecionado==1");
    decide_espera_para_pagar->getConditions()->insert("caixa_selecionado==2");
    decide_espera_para_pagar->getConditions()->insert("caixa_selecionado==3");
    decide_espera_para_pagar->getConditions()->insert("caixa_selecionado==4");
    decide_espera_para_pagar->getConditions()->insert("caixa_selecionado==5");
    decide_espera_para_pagar->getConditions()->insert("caixa_selecionado==6");
       
    Batch* espera_para_pagar0 = new Batch(model);
    espera_para_pagar0->setByAttributeBatch(true);
    espera_para_pagar0->setAttributeName("caixa_selecionado");
    espera_para_pagar0->setPermanentBatch(true);
    espera_para_pagar0->setExpression("pagar+1");
    espera_para_pagar0->setBatchName("espera_para_pagar");
    espera_para_pagar0->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_para_pagar0);
    
    Batch* espera_para_pagar1 = new Batch(model);
    espera_para_pagar1->setByAttributeBatch(true);
    espera_para_pagar1->setAttributeName("caixa_selecionado");
    espera_para_pagar1->setPermanentBatch(true);
    espera_para_pagar1->setExpression("pagar+1");
    espera_para_pagar1->setBatchName("espera_para_pagar");
    espera_para_pagar1->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_para_pagar1);
    
    Batch* espera_para_pagar2 = new Batch(model);
    espera_para_pagar2->setByAttributeBatch(true);
    espera_para_pagar2->setAttributeName("caixa_selecionado");
    espera_para_pagar2->setPermanentBatch(true);
    espera_para_pagar2->setExpression("pagar+1");
    espera_para_pagar2->setBatchName("espera_para_pagar");
    espera_para_pagar2->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_para_pagar2);
    
    Batch* espera_para_pagar3 = new Batch(model);
    espera_para_pagar3->setByAttributeBatch(true);
    espera_para_pagar3->setAttributeName("caixa_selecionado");
    espera_para_pagar3->setPermanentBatch(true);
    espera_para_pagar3->setExpression("pagar+1");
    espera_para_pagar3->setBatchName("espera_para_pagar");
    espera_para_pagar3->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_para_pagar3);
    
    Batch* espera_para_pagar4 = new Batch(model);
    espera_para_pagar4->setByAttributeBatch(true);
    espera_para_pagar4->setAttributeName("caixa_selecionado");
    espera_para_pagar4->setPermanentBatch(true);
    espera_para_pagar4->setExpression("pagar+1");
    espera_para_pagar4->setBatchName("espera_para_pagar");
    espera_para_pagar4->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_para_pagar4);
    
    Batch* espera_para_pagar5 = new Batch(model);
    espera_para_pagar5->setByAttributeBatch(true);
    espera_para_pagar5->setAttributeName("caixa_selecionado");
    espera_para_pagar5->setPermanentBatch(true);
    espera_para_pagar5->setExpression("pagar+1");
    espera_para_pagar5->setBatchName("espera_para_pagar");
    espera_para_pagar5->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_para_pagar5);
    
    Batch* espera_para_pagar6 = new Batch(model);
    espera_para_pagar6->setByAttributeBatch(true);
    espera_para_pagar6->setAttributeName("caixa_selecionado");
    espera_para_pagar6->setPermanentBatch(true);
    espera_para_pagar6->setExpression("pagar+1");
    espera_para_pagar6->setBatchName("espera_para_pagar");
    espera_para_pagar6->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_para_pagar6);
    
    Batch* espera_para_pagar7 = new Batch(model);
    espera_para_pagar7->setByAttributeBatch(true);
    espera_para_pagar7->setAttributeName("caixa_selecionado");
    espera_para_pagar7->setPermanentBatch(true);
    espera_para_pagar7->setExpression("pagar+1");
    espera_para_pagar7->setBatchName("espera_para_pagar");
    espera_para_pagar7->setRepresentativeEntityTypeName("cliente");
    components->insert(espera_para_pagar7);
    
    //---------------------------------------- Modificacao: TRUNC(DISC(0.45,UNIF(1,8),0.9,UNIF(9,12),1,UNIF(13,20))) ----------------------------------------------
    Decide* identifica_numero_produtos = new Decide(model);
    identifica_numero_produtos->getConditions()->insert("nrProdutos < 0.4");
    identifica_numero_produtos->getConditions()->insert("nrProdutos >= 0.4 and nrProdutos < 0.8");
    
    Assign* define_numero_produtos1 = new Assign(model);
    Assign::Assignment* a_numero_produtos1 = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "TRUNC(UNIF(1,8))");
    define_numero_produtos1->getAssignments()->insert(a_numero_produtos1);
    components->insert(define_numero_produtos1);
    
    Assign* define_numero_produtos2 = new Assign(model);
    Assign::Assignment* a_numero_produtos2 = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "TRUNC(UNIF(9,12))");
    define_numero_produtos2->getAssignments()->insert(a_numero_produtos2);
    components->insert(define_numero_produtos2);
    
    Assign* define_numero_produtos3 = new Assign(model);
    Assign::Assignment* a_numero_produtos3 = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "TRUNC(UNIF(13,20))");
    define_numero_produtos3->getAssignments()->insert(a_numero_produtos3);
    components->insert(define_numero_produtos3);
//    //---------------------------------------------------------------------------------------------------------------------------------------------------------------
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//   
//    
//    
//    
//    
//    
//    
//
//
    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    cliente_chega_para_pagar->getNextComponents()->insert(verifica_tempo_simulado);
    verifica_tempo_simulado->getNextComponents()->insert(fora_de_horario_de_pico);
    verifica_tempo_simulado->getNextComponents()->insert(define_tipo_de_cliente);
    fora_de_horario_de_pico->getNextComponents()->insert(define_tipo_de_cliente);
    define_tipo_de_cliente->getNextComponents()->insert(identifica_numero_produtos);
    identifica_numero_produtos->getNextComponents()->insert(define_numero_produtos1);
    identifica_numero_produtos->getNextComponents()->insert(define_numero_produtos2);
    identifica_numero_produtos->getNextComponents()->insert(define_numero_produtos3);
    define_numero_produtos1->getNextComponents()->insert(identifica_tipo_de_cliente);
    define_numero_produtos2->getNextComponents()->insert(identifica_tipo_de_cliente);
    define_numero_produtos3->getNextComponents()->insert(identifica_tipo_de_cliente);
    identifica_tipo_de_cliente->getNextComponents()->insert(controla_tempo);
    identifica_tipo_de_cliente->getNextComponents()->insert(carrinho_ou_cestinha);
    controla_tempo->getNextComponents()->insert(idoso_decide_fila);
    
    idoso_decide_fila->getNextComponents()->insert(fila_selecionada_1_idoso);
    idoso_decide_fila->getNextComponents()->insert(fila_selecionada_2_idoso);
    idoso_decide_fila->getNextComponents()->insert(carrinho_ou_cestinha);
    idoso_decide_fila->getNextComponents()->insert(vai_para_fila_RAPIDO);
    idoso_decide_fila->getNextComponents()->insert(fila_selecionada_1_idoso);
    idoso_decide_fila->getNextComponents()->insert(fila_selecionada_2_idoso);
    fila_selecionada_1_idoso->getNextComponents()->insert(calcula_quantidade_produto_filas);
    fila_selecionada_2_idoso->getNextComponents()->insert(calcula_quantidade_produto_filas);
    
    vai_para_fila_RAPIDO->getNextComponents()->insert(entra_na_fila_RAPIDO);
    entra_na_fila_RAPIDO->getNextComponents()->insert(adiciona_7);
    adiciona_7->getNextComponents()->insert(separa_produtos);
    
    carrinho_ou_cestinha->getNextComponents()->insert(decide_para_cestinha);
    carrinho_ou_cestinha->getNextComponents()->insert(decide_para_carrinho);
    decide_para_cestinha->getNextComponents()->insert(vai_para_fila_RAPIDO);
    decide_para_cestinha->getNextComponents()->insert(verifica_fila_vazia);
    decide_para_cestinha->getNextComponents()->insert(idoso_decide_fila);
    decide_para_cestinha->getNextComponents()->insert(vai_para_fila_RAPIDO);
    verifica_fila_vazia->getNextComponents()->insert(fila_selecionada_1_OUTRO);
    verifica_fila_vazia->getNextComponents()->insert(fila_selecionada_2_OUTRO);
    verifica_fila_vazia->getNextComponents()->insert(fila_selecionada_3_OUTRO);
    verifica_fila_vazia->getNextComponents()->insert(fila_selecionada_4_OUTRO);
    verifica_fila_vazia->getNextComponents()->insert(fila_selecionada_5_OUTRO);
    fila_selecionada_1_OUTRO->getNextComponents()->insert(calcula_quantidade_produto_filas);
    fila_selecionada_2_OUTRO->getNextComponents()->insert(calcula_quantidade_produto_filas);
    fila_selecionada_3_OUTRO->getNextComponents()->insert(calcula_quantidade_produto_filas);
    fila_selecionada_4_OUTRO->getNextComponents()->insert(calcula_quantidade_produto_filas);
    fila_selecionada_5_OUTRO->getNextComponents()->insert(calcula_quantidade_produto_filas);
    decide_para_carrinho->getNextComponents()->insert(verifica_fila_vazia);
    decide_para_carrinho->getNextComponents()->insert(idoso_decide_fila);
    decide_para_carrinho->getNextComponents()->insert(estima_pelo_tamanho_ou_nr_de_produtos);
    estima_pelo_tamanho_ou_nr_de_produtos->getNextComponents()->insert(verifica_menor_fila);
    estima_pelo_tamanho_ou_nr_de_produtos->getNextComponents()->insert(atribui_nr_de_produtos_de_cada_fila);
    verifica_menor_fila->getNextComponents()->insert(fila_selecionada_1_OUTRO);
    verifica_menor_fila->getNextComponents()->insert(fila_selecionada_2_OUTRO);
    verifica_menor_fila->getNextComponents()->insert(fila_selecionada_3_OUTRO);
    verifica_menor_fila->getNextComponents()->insert(fila_selecionada_4_OUTRO);
    verifica_menor_fila->getNextComponents()->insert(fila_selecionada_5_OUTRO);
    atribui_nr_de_produtos_de_cada_fila->getNextComponents()->insert(verifica_menos_produtos);
    verifica_menos_produtos->getNextComponents()->insert(fila_selecionada_1_OUTRO);
    verifica_menos_produtos->getNextComponents()->insert(fila_selecionada_2_OUTRO);
    verifica_menos_produtos->getNextComponents()->insert(fila_selecionada_3_OUTRO);
    verifica_menos_produtos->getNextComponents()->insert(fila_selecionada_4_OUTRO);
    verifica_menos_produtos->getNextComponents()->insert(fila_selecionada_5_OUTRO);
    calcula_quantidade_produto_filas->getNextComponents()->insert(entra_na_fila);
    
    entra_na_fila->getNextComponents()->insert(separa_produtos);
    separa_produtos->getNextComponents()->insert(decide_espera_para_pagar);
    separa_produtos->getNextComponents()->insert(pegando_produtos);
//    assign_48->getNextComponents()->insert(pegando_produtos);
    pegando_produtos->getNextComponents()->insert(entra_esteira);
    entra_esteira->getNextComponents()->insert(tempo_na_esteira);
    tempo_na_esteira->getNextComponents()->insert(inicio_do_registro);
    inicio_do_registro->getNextComponents()->insert(aloca_registrador);
    aloca_registrador->getNextComponents()->insert(sai_da_esteira);
    sai_da_esteira->getNextComponents()->insert(tempo_para_registrar);
    tempo_para_registrar->getNextComponents()->insert(adiciona_registrados);
    adiciona_registrados->getNextComponents()->insert(libera_registrador);
    libera_registrador->getNextComponents()->insert(fim_do_registro);
    fim_do_registro->getNextComponents()->insert(inicio_do_embalo);
    inicio_do_embalo->getNextComponents()->insert(adiciona_aux);
    adiciona_aux->getNextComponents()->insert(ultimo_produto);
    ultimo_produto->getNextComponents()->insert(libera_batch);
    ultimo_produto->getNextComponents()->insert(decide_espera_produtos);
    libera_batch->getNextComponents()->insert(decide_espera_produtos);
    
    decide_espera_produtos->getNextComponents()->insert(espera_produtos0);
    decide_espera_produtos->getNextComponents()->insert(espera_produtos1);
    decide_espera_produtos->getNextComponents()->insert(espera_produtos2);
    decide_espera_produtos->getNextComponents()->insert(espera_produtos3);
    decide_espera_produtos->getNextComponents()->insert(espera_produtos4);
    decide_espera_produtos->getNextComponents()->insert(espera_produtos5);
    decide_espera_produtos->getNextComponents()->insert(espera_produtos6);
    decide_espera_produtos->getNextComponents()->insert(espera_produtos7);
    espera_produtos0->getNextComponents()->insert(limpa_aux);
    espera_produtos1->getNextComponents()->insert(limpa_aux);
    espera_produtos2->getNextComponents()->insert(limpa_aux);
    espera_produtos3->getNextComponents()->insert(limpa_aux);
    espera_produtos4->getNextComponents()->insert(limpa_aux);
    espera_produtos5->getNextComponents()->insert(limpa_aux);
    espera_produtos6->getNextComponents()->insert(limpa_aux);
    espera_produtos7->getNextComponents()->insert(limpa_aux);
    limpa_aux->getNextComponents()->insert(aloca_registrador_2);
    aloca_registrador_2->getNextComponents()->insert(tempo_para_embalar);
    tempo_para_embalar->getNextComponents()->insert(libera_registrador_2);
    libera_registrador_2->getNextComponents()->insert(adiciona_sacolas);
    adiciona_sacolas->getNextComponents()->insert(ultimo_produto_2);
    ultimo_produto_2->getNextComponents()->insert(libera_batch_2);
    ultimo_produto_2->getNextComponents()->insert(decide_espera_para_pagar);
    libera_batch_2->getNextComponents()->insert(decide_espera_para_pagar);
    decide_espera_para_pagar->getNextComponents()->insert(espera_para_pagar0);
    decide_espera_para_pagar->getNextComponents()->insert(espera_para_pagar1);
    decide_espera_para_pagar->getNextComponents()->insert(espera_para_pagar2);
    decide_espera_para_pagar->getNextComponents()->insert(espera_para_pagar3);
    decide_espera_para_pagar->getNextComponents()->insert(espera_para_pagar4);
    decide_espera_para_pagar->getNextComponents()->insert(espera_para_pagar5);
    decide_espera_para_pagar->getNextComponents()->insert(espera_para_pagar6);
    decide_espera_para_pagar->getNextComponents()->insert(espera_para_pagar7);
    espera_para_pagar0->getNextComponents()->insert(fim_do_embalo);
    espera_para_pagar1->getNextComponents()->insert(fim_do_embalo);
    espera_para_pagar2->getNextComponents()->insert(fim_do_embalo);
    espera_para_pagar3->getNextComponents()->insert(fim_do_embalo);
    espera_para_pagar4->getNextComponents()->insert(fim_do_embalo);
    espera_para_pagar5->getNextComponents()->insert(fim_do_embalo);
    espera_para_pagar6->getNextComponents()->insert(fim_do_embalo);
    espera_para_pagar7->getNextComponents()->insert(fim_do_embalo);
    
    fim_do_embalo->getNextComponents()->insert(tempo_para_pagar);
    tempo_para_pagar->getNextComponents()->insert(libera_caixa);
    libera_caixa->getNextComponents()->insert(eh_idoso);
    eh_idoso->getNextComponents()->insert(sai_do_caixa_2);
    eh_idoso->getNextComponents()->insert(sai_do_caixa);
    sai_do_caixa_2->getNextComponents()->insert(limpa_variaveis);
    sai_do_caixa->getNextComponents()->insert(limpa_variaveis);
    limpa_variaveis->getNextComponents()->insert(cliente_sai_do_caixa);
    

    
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
