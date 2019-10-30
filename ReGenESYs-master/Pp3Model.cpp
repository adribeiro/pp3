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
    tm->setTraceLevel(Util::TraceLevel::mostDetailed);

    // get easy access to classes used to insert components and elements into a model
    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();
    
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(36000);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setWarmUpPeriod(3600);
    infos->setWarmUpPeriodTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(1);
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
    Variable* tempo_registrar_produto = new Variable("tempo_registrar_produto");
    tempo_registrar_produto->setValue(0.0578);
    Variable* registrados = new Variable("registrados");
    Variable* sacolas = new Variable("sacolas");
    Variable* aux_registro = new Variable("_aux_registro");
    Variable* nProdutos = new Variable("nProdutos");
    Variable* tempo_registro_total = new Variable("tempo_registro_total");
    Variable* tempo_embalo_total = new Variable("tempo_embalo_total");
//    Variable* _tempo_caixa_total = new Variable("_tempo_caixa_total");
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
    elements->insert(Util::TypeOf<Variable>(), tempo_registrar_produto);
    elements->insert(Util::TypeOf<Variable>(), sacolas);
    elements->insert(Util::TypeOf<Variable>(), registrados);
    elements->insert(Util::TypeOf<Variable>(), aux_registro);
    elements->insert(Util::TypeOf<Variable>(), nProdutos);
    elements->insert(Util::TypeOf<Variable>(), tempo_registro_total);
    elements->insert(Util::TypeOf<Variable>(), tempo_embalo_total);
//    elements->insert(Util::TypeOf<Variable>(), _tempo_caixa_total);
    
    
    //Resources e Sets
    Resource* registrador1_idoso = new Resource(elements, "registrador_1_IDOSO");
    registrador1_idoso->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador1_idoso);
    
    Resource* registrador2_idoso = new Resource(elements, "registrador_2_IDOSO");
    registrador2_idoso->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador2_idoso);
    
    Resource* registrador1_jovem = new Resource(elements, "registrador_1_OUTRO");
    registrador1_jovem->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador1_jovem);
    
    Resource* registrador2_jovem = new Resource(elements, "registrador_2_OUTRO");
    registrador2_jovem->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador2_jovem);
    
    Resource* registrador3_jovem = new Resource(elements, "registrador_3_OUTRO");
    registrador3_jovem->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador3_jovem);
    
    Resource* registrador4_jovem = new Resource(elements, "registrador_4_OUTRO");
    registrador4_jovem->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador4_jovem);
    
    Resource* registrador5_jovem = new Resource(elements, "registrador_5_OUTRO");
    registrador5_jovem->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador5_jovem);
    
    Resource* registrador_rapido = new Resource(elements, "registrador_1_RAPIDO");
    registrador_rapido->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), registrador_rapido);
    
    Set* registradores_total = new Set(elements, "esteiras_total");
    registradores_total->setSetOfType(Util::TypeOf<Resource>());
    registradores_total->getElementSet()->insert(registrador1_idoso);
    registradores_total->getElementSet()->insert(registrador2_idoso);
    registradores_total->getElementSet()->insert(registrador1_jovem);
    registradores_total->getElementSet()->insert(registrador2_jovem);
    registradores_total->getElementSet()->insert(registrador3_jovem);
    registradores_total->getElementSet()->insert(registrador4_jovem);
    registradores_total->getElementSet()->insert(registrador5_jovem);
    registradores_total->getElementSet()->insert(registrador_rapido);
    elements->insert(Util::TypeOf<Set>(), registradores_total);
    
    Resource* esteira1_idoso = new Resource(elements, "esteira1_idoso");
    esteira1_idoso->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira1_idoso);
    
    Resource* esteira2_idoso = new Resource(elements, "esteira2_idoso");
    esteira2_idoso->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira2_idoso);
    
    Resource* esteira1_jovem = new Resource(elements, "esteira1_jovem");
    esteira1_jovem->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira1_jovem);
    
    Resource* esteira2_jovem = new Resource(elements, "esteira2_jovem");
    esteira2_jovem->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira2_jovem);
    
    Resource* esteira3_jovem = new Resource(elements, "esteira3_jovem");
    esteira3_jovem->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira3_jovem);
    
    Resource* esteira4_jovem = new Resource(elements, "esteira4_jovem");
    esteira4_jovem->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira4_jovem);
    
    Resource* esteira5_jovem = new Resource(elements, "esteira5_jovem");
    esteira5_jovem->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira5_jovem);
    
    Resource* esteira_rapido = new Resource(elements, "esteira_rapido");
    esteira_rapido->setCapacity(7);
    elements->insert(Util::TypeOf<Resource>(), esteira_rapido);
    
    Set* esteiras_total = new Set(elements, "esteiras_total");
    esteiras_total->setSetOfType(Util::TypeOf<Resource>());
    esteiras_total->getElementSet()->insert(esteira1_idoso);
    esteiras_total->getElementSet()->insert(esteira2_idoso);
    esteiras_total->getElementSet()->insert(esteira1_jovem);
    esteiras_total->getElementSet()->insert(esteira2_jovem);
    esteiras_total->getElementSet()->insert(esteira3_jovem);
    esteiras_total->getElementSet()->insert(esteira4_jovem);
    esteiras_total->getElementSet()->insert(esteira5_jovem);
    esteiras_total->getElementSet()->insert(esteira_rapido);
    elements->insert(Util::TypeOf<Set>(), esteiras_total);
    
    
    Resource* caixa1_idoso = new Resource(elements, "caixa1_idoso");
    caixa1_idoso->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa1_idoso);
   
    Resource* caixa2_idoso = new Resource(elements, "caixa2_idoso");
    caixa2_idoso->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa2_idoso);
    
    Resource* caixa1_jovem = new Resource(elements, "caixa1_jovem");
    caixa1_jovem->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa1_jovem);
    
    Resource* caixa2_jovem = new Resource(elements, "caixa2_jovem");
    caixa2_jovem->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa2_jovem);
    
    Resource* caixa3_jovem = new Resource(elements, "caixa3_jovem");
    caixa3_jovem->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa3_jovem);
    
    Resource* caixa4_jovem = new Resource(elements, "caixa4_jovem");
    caixa4_jovem->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa4_jovem);
    
    Resource* caixa5_jovem = new Resource(elements, "caixa5_jovem");
    caixa5_jovem->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa5_jovem);
    
    Resource* caixa_rapido = new Resource(elements, "caixa_rapido");
    caixa_rapido->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa_rapido);

    Set* caixas_total = new Set(elements, "caixas_total");
    caixas_total->setSetOfType(Util::TypeOf<Resource>());
    caixas_total->getElementSet()->insert(caixa1_idoso);
    caixas_total->getElementSet()->insert(caixa2_idoso);
    caixas_total->getElementSet()->insert(caixa1_jovem);
    caixas_total->getElementSet()->insert(caixa2_jovem);
    caixas_total->getElementSet()->insert(caixa3_jovem);
    caixas_total->getElementSet()->insert(caixa4_jovem);
    caixas_total->getElementSet()->insert(caixa5_jovem);
    caixas_total->getElementSet()->insert(caixa_rapido);
    elements->insert(Util::TypeOf<Set>(), caixas_total);
    
    
    Set* caixas_nao_idoso = new Set(elements, "caixas_nao_idoso");
    caixas_nao_idoso->setSetOfType(Util::TypeOf<Resource>());
    caixas_nao_idoso->getElementSet()->insert(caixa1_jovem);
    caixas_nao_idoso->getElementSet()->insert(caixa2_jovem);
    caixas_nao_idoso->getElementSet()->insert(caixa3_jovem);
    caixas_nao_idoso->getElementSet()->insert(caixa4_jovem);
    caixas_nao_idoso->getElementSet()->insert(caixa5_jovem);
    caixas_nao_idoso->getElementSet()->insert(caixa_rapido);
    elements->insert(Util::TypeOf<Set>(), caixas_nao_idoso);
    
    Set* caixas_jovem = new Set(elements, "caixas_jovem");
    caixas_jovem->setSetOfType(Util::TypeOf<Resource>());
    caixas_jovem->getElementSet()->insert(caixa1_jovem);
    caixas_jovem->getElementSet()->insert(caixa2_jovem);
    caixas_jovem->getElementSet()->insert(caixa3_jovem);
    caixas_jovem->getElementSet()->insert(caixa4_jovem);
    caixas_jovem->getElementSet()->insert(caixa5_jovem);
    elements->insert(Util::TypeOf<Set>(), caixas_jovem);
    
    Set* caixas_idoso = new Set(elements, "caixas_idoso");
    caixas_idoso->setSetOfType(Util::TypeOf<Resource>());
    caixas_idoso->getElementSet()->insert(caixa1_idoso);
    elements->insert(Util::TypeOf<Set>(), caixas_idoso);
    
    Set* caixas_rapido = new Set(elements, "caixas_rapido");
    caixas_rapido->getElementSet()->insert(caixa_rapido);
    elements->insert(Util::TypeOf<Set>(), caixas_rapido);
    
    
    
    //Queues
    Queue* fila_rapido = new Queue(elements, "fila_caixas_RAPIDO");
    fila_rapido->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila_rapido);
    
    Queue* fila1_idoso = new Queue(elements, "fila_1_IDOSO");
    fila1_idoso->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila1_idoso);
    
    Queue* fila2_idoso = new Queue(elements, "fila_2_IDOSO");
    fila2_idoso->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila2_idoso);
    
    Queue* fila1_jovem = new Queue(elements, "fila_1_OUTRO");
    fila1_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila1_jovem);
    
    Queue* fila2_jovem = new Queue(elements, "fila_2_OUTRO");
    fila2_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila2_jovem);
    
    Queue* fila3_jovem = new Queue(elements, "fila_3_OUTRO");
    fila3_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila3_jovem);
    
    Queue* fila4_jovem = new Queue(elements, "fila_4_OUTRO");
    fila4_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila4_jovem);
    
    Queue* fila5_jovem = new Queue(elements, "fila_5_OUTRO");
    fila5_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila5_jovem);
    
    Queue* filaE_rapido = new Queue(elements, "fila_esteira_1_RAPIDO");
    filaE_rapido->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaE_rapido);
    
    Queue* filaE1_idoso = new Queue(elements, "fila_esteira_1_IDOSO");
    filaE1_idoso->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaE1_idoso);
    
    Queue* filaE2_idoso = new Queue(elements, "fila_esteira_2_IDOSO");
    filaE2_idoso->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaE2_idoso);
    
    Queue* filaE1_jovem = new Queue(elements, "fila_esteira_1_OUTRO");
    filaE1_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaE1_jovem);
    
    Queue* filaE2_jovem = new Queue(elements, "fila_esteira_2_OUTRO");
    filaE2_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaE2_jovem);
    
    Queue* filaE3_jovem = new Queue(elements, "fila_esteira_3_OUTRO");
    filaE3_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaE3_jovem);
    
    Queue* filaE4_jovem = new Queue(elements, "fila_esteira_4_OUTRO");
    filaE4_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaE4_jovem);
    
    Queue* filaE5_jovem = new Queue(elements, "Fila_esteira_5_OUTRO");
    filaE5_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaE5_jovem);
    
    Queue* filaR_rapido = new Queue(elements, "Fila_registrador_1_rapido");
    filaR_rapido->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaR_rapido);
    
    Queue* filaR1_idoso = new Queue(elements, "Fila_registrador_1_IDOSO");
    filaR1_idoso->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaR1_idoso);
    
    Queue* filaR2_idoso = new Queue(elements, "Fila_registrador_2_IDOSO");
    filaR2_idoso->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaR2_idoso);
    
    Queue* filaR1_jovem = new Queue(elements, "Fila_registrador_1_OUTRO");
    filaR1_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaR1_jovem);
    
    Queue* filaR2_jovem = new Queue(elements, "Fila_registrador_2_OUTRO");
    filaR2_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaR2_jovem);
    
    Queue* filaR3_jovem = new Queue(elements, "Fila_registrador_3_OUTRO");
    filaE3_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaR3_jovem);
    
    Queue* filaR4_jovem = new Queue(elements, "Fila_registrador_4_OUTRO");
    filaR4_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaR4_jovem);
    
    Queue* filaR5_jovem = new Queue(elements, "Fila_registrador_5_OUTRO");
    filaR5_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), filaR5_jovem);
    
    //seizes
    Seize* aloca_rapido = new Seize(model);
    aloca_rapido->setResource(caixa_rapido);
    aloca_rapido->setQueue(fila_rapido);
    components->insert(aloca_rapido);
    
    Seize* aloca_Nrapido = new Seize(model);
    aloca_Nrapido->setSet(caixas_total);
    aloca_Nrapido->insertQueue(fila1_idoso);
    aloca_Nrapido->insertQueue(fila2_idoso);
    aloca_Nrapido->insertQueue(fila1_jovem);
    aloca_Nrapido->insertQueue(fila2_jovem);
    aloca_Nrapido->insertQueue(fila3_jovem);
    aloca_Nrapido->insertQueue(fila4_jovem);
    aloca_Nrapido->insertQueue(fila5_jovem);
    aloca_Nrapido->insertQueue(fila_rapido);
    aloca_Nrapido->setSaveAttribute("caixa_selecionado");
    aloca_Nrapido->setRule(Resource::ResourceRule::ESPECIFIC);
    components->insert(aloca_Nrapido);
    
    Seize* aloca_esteira = new Seize(model);
    aloca_esteira->setSet(esteiras_total);
    aloca_esteira->insertQueue(filaE1_idoso);
    aloca_esteira->insertQueue(filaE2_idoso);
    aloca_esteira->insertQueue(filaE1_jovem);
    aloca_esteira->insertQueue(filaE2_jovem);
    aloca_esteira->insertQueue(filaE3_jovem);
    aloca_esteira->insertQueue(filaE4_jovem);
    aloca_esteira->insertQueue(filaE5_jovem);
    aloca_esteira->insertQueue(filaE_rapido);
    aloca_esteira->setSaveAttribute("caixa_selecionado");
    aloca_esteira->setRule(Resource::ResourceRule::ESPECIFIC);
    components->insert(aloca_esteira);
    
    Seize* aloca_registrador = new Seize(model);
    aloca_registrador->setSet(registradores_total);
    aloca_registrador->insertQueue(filaR1_idoso);
    aloca_registrador->insertQueue(filaR2_idoso);
    aloca_registrador->insertQueue(filaR1_jovem);
    aloca_registrador->insertQueue(filaR2_jovem);
    aloca_registrador->insertQueue(filaR3_jovem);
    aloca_registrador->insertQueue(filaR4_jovem);
    aloca_registrador->insertQueue(filaR5_jovem);
    aloca_registrador->insertQueue(filaR_rapido);
    aloca_registrador->setSaveAttribute("caixa_selecionado");
    aloca_registrador->setRule(Resource::ResourceRule::ESPECIFIC);
    components->insert(aloca_registrador);
    
    Seize* aloca_registrador1 = new Seize(model);
    aloca_registrador1->setSet(registradores_total);
    aloca_registrador1->insertQueue(filaR1_idoso);
    aloca_registrador1->insertQueue(filaR2_idoso);
    aloca_registrador1->insertQueue(filaR1_jovem);
    aloca_registrador1->insertQueue(filaR2_jovem);
    aloca_registrador1->insertQueue(filaR3_jovem);
    aloca_registrador1->insertQueue(filaR4_jovem);
    aloca_registrador1->insertQueue(filaR5_jovem);
    aloca_registrador1->insertQueue(filaR_rapido);
    aloca_registrador1->setSaveAttribute("caixa_selecionado");
    aloca_registrador1->setRule(Resource::ResourceRule::ESPECIFIC);
    aloca_registrador1->setPriority(1);
    components->insert(aloca_registrador1);
   
    //Release
    Release* livra_esteira = new Release(model);
    livra_esteira->setSet(esteiras_total);
    livra_esteira->setSaveAttribute("caixa_selecionado");
    components->insert(livra_esteira);
    
    Release* livra_registrador = new Release(model);
    livra_registrador->setSet(registradores_total);
    livra_registrador->setSaveAttribute("caixa_selecionado");
    components->insert(livra_registrador);
    
    Release* livra_registrador1 = new Release(model);
    livra_registrador1->setSet(registradores_total);
    livra_registrador1->setSaveAttribute("caixa_selecionado");
    components->insert(livra_registrador1);
    
    Release* livra_caixa = new Release(model);
    livra_caixa->setSet(caixas_total);
    livra_caixa->setSaveAttribute("caixa_selecionado");
    components->insert(livra_caixa);
    
    // create stations to enter and route to
    Station* rapido = new Station(elements, "rapido");
    elements->insert(Util::TypeOf<Station>(), rapido);
    
    //enter
    
    Enter* enter_rapido = new Enter(model);
    enter_rapido->setStation(rapido);
    components->insert(enter_rapido);
    
    //route  
    Route* rapido_livre = new Route(model);
    rapido_livre->setStation(rapido);
    rapido_livre->setRouteTimeExpression("UNIF(2,5)");
    rapido_livre->setRouteTimeTimeUnit(Util::TimeUnit::second);
    components->insert(rapido_livre);
   
    
    //entidades
    EntityType* cliente = new EntityType(elements, "cliente");
    elements->insert(Util::TypeOf<EntityType>(), cliente);
    
    EntityType* produto = new EntityType(elements, "produto");
    elements->insert(Util::TypeOf<EntityType>(), produto);
    
    
    //assigns e componentes
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
    
    
    Assign* inicia_cliente = new Assign(model);
    Assign::Assignment* a_qtd_fila_1 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_1", "0");
    Assign::Assignment* a_qtd_fila_2 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_2", "0");
    Assign::Assignment* a_qtd_fila_3 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_3", "0");
    Assign::Assignment* a_qtd_fila_4 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_4", "0");
    Assign::Assignment* a_qtd_fila_5 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_5", "0");
    Assign::Assignment* a_embalar = new Assign::Assignment(Assign::DestinationType::Attribute, "embalar", "8");
    Assign::Assignment* a_pagar = new Assign::Assignment(Assign::DestinationType::Attribute, "pagar", "100");
    Assign::Assignment* a_collector = new Assign::Assignment(Assign::DestinationType::Attribute, "collector", "0");
    Assign::Assignment* a_tipo_jovem = new Assign::Assignment(Assign::DestinationType::Attribute, "tipo", "1");//DISC(0.3,0,1,1)
    Assign::Assignment* a_tempo_caixa = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_caixa", "TNOW");
    Assign::Assignment* a_nrProdutos = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "UNIF(0,1)");//TRUNC(DISC(0.45,UNIF(1,8),0.9,UNIF(9,12),1,UNIF(13,20)))
    inicia_cliente->getAssignments()->insert(a_qtd_fila_1);
    inicia_cliente->getAssignments()->insert(a_qtd_fila_2);
    inicia_cliente->getAssignments()->insert(a_qtd_fila_3);
    inicia_cliente->getAssignments()->insert(a_qtd_fila_4);
    inicia_cliente->getAssignments()->insert(a_qtd_fila_5);
    inicia_cliente->getAssignments()->insert(a_embalar);
    inicia_cliente->getAssignments()->insert(a_pagar);
    inicia_cliente->getAssignments()->insert(a_collector);
    inicia_cliente->getAssignments()->insert(a_tipo_jovem);
    inicia_cliente->getAssignments()->insert(a_tempo_caixa);
    inicia_cliente->getAssignments()->insert(a_nrProdutos);
    components->insert(inicia_cliente);
    
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
    
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------- Modificacao: DISC(0.3,0,1,1) -----------------------------------------------------------

    Decide* identifica_tipo_cliente = new Decide(model);
    identifica_tipo_cliente->getConditions()->insert("UNIF(0,1) < 0.3");
    
    Assign* define_idoso = new Assign(model);
    Assign::Assignment* a_tempo_caixa_idosos = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_caixa_idosos", "TNOW");
    Assign::Assignment* a_tipo_idoso = new Assign::Assignment(Assign::DestinationType::Attribute, "tipo", "0");
    define_idoso->getAssignments()->insert(a_tempo_caixa_idosos);
    define_idoso->getAssignments()->insert(a_tipo_idoso);
    components->insert(define_idoso);
    //-----------------------------------------------------------------------------------------------------------------------------------------------
    
    Decide* identifica_fila_idoso = new Decide(model);
    identifica_fila_idoso->getConditions()->insert("STATE(caixa1_idoso) == 1");
    identifica_fila_idoso->getConditions()->insert("STATE(caixa2_idoso) == 1");
    identifica_fila_idoso->getConditions()->insert("SETSUM(caixas_nao_idoso) < NUMSET(caixas_nao_idoso)");
    identifica_fila_idoso->getConditions()->insert("nrProdutos < 9 and NQ(fila_rapido) < 5");
    identifica_fila_idoso->getConditions()->insert("NQ(fila1_idoso) < NQ(fila2_idoso)");
    
    Assign* define_fila1_idoso = new Assign(model);
    Assign::Assignment* a_caixa1_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "0");
//    Assign::Assignment* a_nProdutos1 = new Assign::Assignment(true,Assign::DestinationType::VariableArray, "nProdutos",Assign::DestinationType::Attribute,"nrProdutos",Assign::DestinationType::Attribute,"caixa_selecionado",0);
    define_fila1_idoso->getAssignments()->insert(a_caixa1_selecionado);
//    define_fila1_idoso->getAssignments()->insert(a_nProdutos1);
    components->insert(define_fila1_idoso);
    
    Assign* define_fila2_idoso = new Assign(model);
    Assign::Assignment* a_caixa2_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "1");
//    Assign::Assignment* a_nProdutos2 = new Assign::Assignment(true,Assign::DestinationType::VariableArray, "nProdutos",Assign::DestinationType::Attribute,"nrProdutos",Assign::DestinationType::Attribute,"caixa_selecionado",0);
    define_fila2_idoso->getAssignments()->insert(a_caixa2_selecionado);
//    define_fila2_idoso->getAssignments()->insert(a_nProdutos2);
    components->insert(define_fila2_idoso);
    
    Assign* define_nrProdutos_fila = new Assign(model);
    Assign::Assignment* a1_qtd_fila_1 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_1", "SAQUE(fila1_jovem,Entity.nrProdutos)");
    Assign::Assignment* a1_qtd_fila_2 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_2","SAQUE(fila2_jovem,Entity.nrProdutos)");
    Assign::Assignment* a1_qtd_fila_3 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_3", "SAQUE(fila3_jovem,Entity.nrProdutos)");
    Assign::Assignment* a1_qtd_fila_4 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_4","SAQUE(fila4_jovem,Entity.nrProdutos)");
    Assign::Assignment* a1_qtd_fila_5 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_5", "SAQUE(fila5_jovem,Entity.nrProdutos)");
    define_nrProdutos_fila->getAssignments()->insert(a1_qtd_fila_1);
    define_nrProdutos_fila->getAssignments()->insert(a1_qtd_fila_2);
    define_nrProdutos_fila->getAssignments()->insert(a1_qtd_fila_3);
    define_nrProdutos_fila->getAssignments()->insert(a1_qtd_fila_4);
    define_nrProdutos_fila->getAssignments()->insert(a1_qtd_fila_5);
    components->insert(define_nrProdutos_fila);
   
        
    Assign* define_fila_rapido = new Assign(model);
    Assign::Assignment* a_caixaR_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "7");
//    Assign::Assignment* a_nProdutos7 = new Assign::Assignment(true,Assign::DestinationType::VariableArray, "nProdutos",Assign::DestinationType::Attribute,"nrProdutos",Assign::DestinationType::Attribute,"caixa_selecionado",0);
    define_fila_rapido->getAssignments()->insert(a_caixaR_selecionado);
//    define_fila_rapido->getAssignments()->insert(a_nProdutos7);
    components->insert(define_fila_rapido);

    Decide* identifica_carrinho_cestinha = new Decide(model);
    identifica_carrinho_cestinha->getConditions()->insert("nrProdutos < 9");
    
    Decide* identifica_fila_cestinha = new Decide(model);
    identifica_fila_cestinha->getConditions()->insert("SETSUM(caixas_rapido) < NUMSET(caixas_rapido)");
    identifica_fila_cestinha->getConditions()->insert("SETSUM(caixas_jovem) < NUMSET(caixas_jovem)");
    identifica_fila_cestinha->getConditions()->insert("SETSUM(caixas_idoso) < NUMSET(caixas_idoso)");

    Decide* identifica_fila_carrinho = new Decide(model);
    identifica_fila_carrinho->getConditions()->insert("SETSUM(caixas_jovem) < NUMSET(caixas_jovem)");
    identifica_fila_carrinho->getConditions()->insert("SETSUM(caixas_idoso) < NUMSET(caixas_idoso)");
    
    Decide* identifica_fila_vazia = new Decide(model);
    identifica_fila_vazia->getConditions()->insert("STATE(caixa1_jovem) == 1");
    identifica_fila_vazia->getConditions()->insert("STATE(caixa2_jovem) == 1");
    identifica_fila_vazia->getConditions()->insert("STATE(caixa3_jovem) == 1");
    identifica_fila_vazia->getConditions()->insert("STATE(caixa4_jovem) == 1");
    
    
    Decide* identifica_tamanho_nrProduto = new Decide(model);
    identifica_tamanho_nrProduto->getConditions()->insert("UNIF(0,1) < 0.5");
    
    Decide* identifica_menor_fila = new Decide(model);
    identifica_menor_fila->getConditions()->insert("NQ(fila1_jovem) <= NQ(fila2_jovem) and NQ(fila1_jovem) <= NQ(fila3_jovem) and NQ(fila1_jovem) <= NQ(fila4_jovem) and NQ(fila1_jovem) <= NQ(fila5_jovem)");
    identifica_menor_fila->getConditions()->insert("NQ(fila2_jovem) <= NQ(fila1_jovem) and NQ(fila2_jovem) <= NQ(fila3_jovem) and NQ(fila2_jovem) <= NQ(fila4_jovem) and NQ(fila2_jovem) <= NQ(fila5_jovem)");
    identifica_menor_fila->getConditions()->insert("NQ(fila3_jovem) <= NQ(fila1_jovem) and NQ(fila3_jovem) <= NQ(fila2_jovem) and NQ(fila3_jovem) <= NQ(fila4_jovem) and NQ(fila3_jovem) <= NQ(fila5_jovem)");
    identifica_menor_fila->getConditions()->insert("NQ(fila4_jovem) <= NQ(fila1_jovem) and NQ(fila4_jovem) <= NQ(fila2_jovem) and NQ(fila4_jovem) <= NQ(fila3_jovem) and NQ(fila4_jovem) <= NQ(fila5_jovem)");
    
    Assign* define_nrProdutos_esteira = new Assign(model);
    Assign::Assignment* a_est_qtd_fila1 = new Assign::Assignment(Assign::DestinationType::Variable, "est_qtd_fila1", "UNIF((qtd_fila_1*0.7),(qtd_fila_1*1.3))");
    Assign::Assignment* a_est_qtd_fila2 = new Assign::Assignment(Assign::DestinationType::Variable, "est_qtd_fila2","UNIF((qtd_fila_2*0.7)),(qtd_fila_2*1.3))");
    Assign::Assignment* a_est_qtd_fila3 = new Assign::Assignment(Assign::DestinationType::Variable, "est_qtd_fila3", "UNIF((qtd_fila_3*0.7),(qtd_fila_3*1.3))");
    Assign::Assignment* a_est_qtd_fila4 = new Assign::Assignment(Assign::DestinationType::Variable, "est_qtd_fila4","UNIF((qtd_fila_4*0.7),(qtd_fila_4*1.3))");
    Assign::Assignment* a_est_qtd_fila5 = new Assign::Assignment(Assign::DestinationType::Variable, "est_qtd_fila5", "UNIF((qtd_fila_5*0.7),(qtd_fila_5*1.3))");
    define_nrProdutos_esteira->getAssignments()->insert(a_est_qtd_fila1);
    define_nrProdutos_esteira->getAssignments()->insert(a_est_qtd_fila2);
    define_nrProdutos_esteira->getAssignments()->insert(a_est_qtd_fila3);
    define_nrProdutos_esteira->getAssignments()->insert(a_est_qtd_fila4);
    define_nrProdutos_esteira->getAssignments()->insert(a_est_qtd_fila5);
    components->insert(define_nrProdutos_esteira);
    
    Decide* identifica_menos_produtos = new Decide(model);
    identifica_menos_produtos->getConditions()->insert("est_qtd_fila1 < est_qtd_fila2 and est_qtd_fila1 < est_qtd_fila3 and est_qtd_fila1 < est_qtd_fila4 and est_qtd_fila1 < est_qtd_fila5");
    identifica_menos_produtos->getConditions()->insert("est_qtd_fila2 < est_qtd_fila1 and est_qtd_fila2 < est_qtd_fila3 and est_qtd_fila2 < est_qtd_fila4 and est_qtd_fila2 < est_qtd_fila5");
    identifica_menos_produtos->getConditions()->insert("est_qtd_fila3 < est_qtd_fila1 and est_qtd_fila3 < est_qtd_fila2 and est_qtd_fila3 < est_qtd_fila4 and est_qtd_fila3 < est_qtd_fila5");
    identifica_menos_produtos->getConditions()->insert("est_qtd_fila4 < est_qtd_fila1 and est_qtd_fila4 < est_qtd_fila2 and est_qtd_fila4 < est_qtd_fila3 and est_qtd_fila4 < est_qtd_fila5");
    
    Assign* define_fila1_jovem = new Assign(model);
    Assign::Assignment* a_caixa1J_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "2");
//    Assign::Assignment* a_nProdutos1J = new Assign::Assignment(true,Assign::DestinationType::VariableArray, "nProdutos",Assign::DestinationType::Attribute,"nrProdutos",Assign::DestinationType::Attribute,"caixa_selecionado",0);
    define_fila1_jovem->getAssignments()->insert(a_caixa1J_selecionado);
//    define_fila1_jovem->getAssignments()->insert(a_nProdutos1J);
    components->insert(define_fila1_jovem);
    
    Assign* define_fila2_jovem = new Assign(model);
    Assign::Assignment* a_caixa2J_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "3");
//    Assign::Assignment* a_nProdutos2J = new Assign::Assignment(true,Assign::DestinationType::VariableArray, "nProdutos",Assign::DestinationType::Attribute,"nrProdutos",Assign::DestinationType::Attribute,"caixa_selecionado",0);
    define_fila2_jovem->getAssignments()->insert(a_caixa2J_selecionado);
//    define_fila2_jovem->getAssignments()->insert(a_nProdutos2J);
    components->insert(define_fila2_jovem);
    
    Assign* define_fila3_jovem = new Assign(model);
    Assign::Assignment* a_caixa3J_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "4");
//    Assign::Assignment* a_nProdutos3J = new Assign::Assignment(true,Assign::DestinationType::VariableArray, "nProdutos",Assign::DestinationType::Attribute,"nrProdutos",Assign::DestinationType::Attribute,"caixa_selecionado",0);
    define_fila3_jovem->getAssignments()->insert(a_caixa3J_selecionado);
//    define_fila3_jovem->getAssignments()->insert(a_nProdutos3J);
    components->insert(define_fila3_jovem);
    
    Assign* define_fila4_jovem = new Assign(model);
    Assign::Assignment* a_caixa4J_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "5");
//    Assign::Assignment* a_nProdutos4J = new Assign::Assignment(true,Assign::DestinationType::VariableArray, "nProdutos",Assign::DestinationType::Attribute,"nrProdutos",Assign::DestinationType::Attribute,"caixa_selecionado",0);
    define_fila4_jovem->getAssignments()->insert(a_caixa4J_selecionado);
//    define_fila4_jovem->getAssignments()->insert(a_nProdutos4J);
    components->insert(define_fila4_jovem);
    
    Assign* define_fila5_jovem = new Assign(model);
    Assign::Assignment* a_caixa5J_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "6");
//    Assign::Assignment* a_nProdutos5J = new Assign::Assignment(true,Assign::DestinationType::VariableArray, "nProdutos",Assign::DestinationType::Attribute,"nrProdutos",Assign::DestinationType::Attribute,"caixa_selecionado",0);
    define_fila5_jovem->getAssignments()->insert(a_caixa5J_selecionado);
//    define_fila5_jovem->getAssignments()->insert(a_nProdutos5J);
    components->insert(define_fila5_jovem);
    
    Separate* divide_produtos = new Separate(model);
    divide_produtos->setSplitBatch(false);
    divide_produtos->setAmountToDuplicate("nrProdutos");
    divide_produtos->setAttributeType(true);
    components->insert(divide_produtos);
    
    Assign* define_produto = new Assign(model);
//    Assign::Assignment* a_entityType = new Assign::Assignment();
//    define_produto->getAssignments()->insert(a_entityType);
//    define_produto->setEntityType(produto);
    components->insert(define_produto);
    
    Delay* pega_produto = new Delay(model);
    pega_produto->setDelayExpression("NORM(0.8,1.5)");
    pega_produto->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(pega_produto);
    
    Delay* tempo_esteira = new Delay(model);
    pega_produto->setDelayExpression("3");
    pega_produto->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(pega_produto);
    
    Assign* inicio_registro = new Assign(model);
    Assign::Assignment* a_tempo_registro = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_registro", "TNOW");
    inicia_cliente->getAssignments()->insert(a_tempo_registro);
    components->insert(inicio_registro);
    
    Delay* tempo_registrar = new Delay(model);
    tempo_registrar->setDelayExpression("tempo_registrar_produto");
    tempo_registrar->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(tempo_registrar);
    
    Assign* define_registro = new Assign(model);
//    Assign::Assignment* a_registrados = new Assign::Assignment(Assign::DestinationType::VariableArray, "registrados",Assign::DestinationType::Attribute,"caixa_selecionado",Assign::DestinationType::VariableArray,"registrados",Assign::DestinationType::Attribute,"caixa_selecionado",1);
//    Assign::Assignment* a_registro = new Assign::Assignment(false,Assign::DestinationType::Attribute, "registro",Assign::DestinationType::VariableArray, "registrados",Assign::DestinationType::Attribute,"caixa_selecionado",0);
//    define_registro->getAssignments()->insert(a_registrados);
//    define_registro->getAssignments()->insert(a_registro);
    components->insert(define_registro);
    
    Assign* define_fim_registro = new Assign(model);
    Assign::Assignment* a_fim_tempo_registro = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_registro", "TNOW - tempo_registro");
    Assign::Assignment* a_tempo_registro_total = new Assign::Assignment(Assign::DestinationType::Variable, "tempo_registro_total","tempo_registro_total - tempo_registro");
    define_fim_registro->getAssignments()->insert(a_fim_tempo_registro);
    define_fim_registro->getAssignments()->insert(a_tempo_registro_total);
    components->insert(define_fim_registro);
    
    Assign* define_embalo = new Assign(model);
    Assign::Assignment* a_tempo_embalo = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_embalo", "TNOW");
    define_embalo->getAssignments()->insert(a_tempo_embalo);
    components->insert(define_embalo);
    
    Assign* define_aux = new Assign(model);
//    Assign::Assignment* a_aux_registro = new Assign::Assignment(Assign::DestinationType::VariableArray, "aux_registro",Assign::DestinationType::Attribute,"caixa_selecionado",Assign::DestinationType::VariableArray,"aux_registro",Assign::DestinationType::Attribute,"caixa_selecionado",1);
//    define_aux->getAssignments()->insert(a_aux_registro);
    components->insert(define_aux);
    
    Decide* identifica_ultimo_produto = new Decide(model);
    identifica_ultimo_produto->getConditions()->insert("registro == nrProdutos");
    
    Assign* define_fim_embalo = new Assign(model);
//    Assign::Assignment* a_embalar1 = new Assign::Assignment(false,Assign::DestinationType::Attribute, "embalar", Assign::DestinationType::VariableArray, "aux_registro",Assign::DestinationType::Attribute,"caixa_selecionado",0);
    Assign::Assignment* a_collector1 = new Assign::Assignment(Assign::DestinationType::Attribute, "collector", "1");
//    define_fim_embalo->getAssignments()->insert(a_embalar1);
    define_fim_embalo->getAssignments()->insert(a_collector1);
    components->insert(define_fim_embalo);
    
    Batch* junta_produtos = new Batch(model);
    junta_produtos->setByAttributeBatch(true);
    junta_produtos->setAttributeName("caixa_selecionado");
    junta_produtos->setPermanentBatch(true);
    junta_produtos->setAttributeBatch(true);
    junta_produtos->setExpression("embalar");
    junta_produtos->setBatchName("juntaProdutos");
    junta_produtos->setRepresentativeEntityTypeName("cliente");
    components->insert(junta_produtos);
    
    Assign* define_limpa_aux = new Assign(model);
//    Assign::Assignment* a_aux_registro1 = new Assign::Assignment(true,Assign::DestinationType::VariableArray, "aux_registro",Assign::DestinationType::Variable,"0",Assign::DestinationType::Attribute,"caixa_selecionado",0);
//    define_limpa_aux->getAssignments()->insert(a_aux_registro1);
    components->insert(define_limpa_aux);
    
    Delay* tempo_embalar = new Delay(model);
    tempo_embalar->setDelayExpression("UNIF(1,2) * embalar");
    tempo_embalar->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(tempo_embalar);
    
    Assign* define_sacolas = new Assign(model);
//    Assign::Assignment* a_sacolas = new Assign::Assignment(Assign::DestinationType::VariableArray, "sacolas",Assign::DestinationType::Attribute,"caixa_selecionado",Assign::DestinationType::VariableArray,"sacolas",Assign::DestinationType::Attribute,"caixa_selecionado",1);
//    define_sacolas->getAssignments()->insert(a_sacolas);
    components->insert(define_sacolas);
    
    Decide* identifica_ultimo_produto1 = new Decide(model);
    identifica_ultimo_produto1->getConditions()->insert("registro == nrProdutos");
    
    Assign* define_pagamento = new Assign(model);
//    Assign::Assignment* a_pagar1 = new Assign::Assignment(false,Assign::DestinationType::Attribute, "pagar",Assign::DestinationType::VariableArray, "sacolas",Assign::DestinationType::Attribute,"caixa_selecionado",0);
//    define_pagamento->getAssignments()->insert(a_pagar1);
    components->insert(define_pagamento);
    
    Batch* sai_caixa = new Batch(model);
    sai_caixa->setByAttributeBatch(true);
    sai_caixa->setAttributeName("nrCaixa");
    sai_caixa->setPermanentBatch(true);
    sai_caixa->setAttributeBatch(true);
    sai_caixa->setExpression("pagar");
    sai_caixa->setBatchSize(1);
    sai_caixa->setBatchName("saiCaixa");
    sai_caixa->setRepresentativeEntityTypeName("produto");
    components->insert(sai_caixa);
    
    Assign* define_fim_embalo1 = new Assign(model);
    Assign::Assignment* a_tempo_embalo1 = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_embalo", "TNOW");
    Assign::Assignment* a_tempo_embalo_total = new Assign::Assignment(Assign::DestinationType::Variable, "tempo_embalo_total","tempo_embalo_total+tempo_embalo");
    define_fim_embalo1->getAssignments()->insert(a_tempo_embalo1);
    define_fim_embalo1->getAssignments()->insert(a_tempo_embalo_total);
    components->insert(define_fim_embalo1);
    
    Delay* tempo_pagar = new Delay(model);
    tempo_pagar->setDelayExpression("38 + 51 * BETA(4.38,2.67)");
    tempo_pagar->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(tempo_pagar);
    
    
    
    
    
    
    
    
    
    
    
    
   
    
    
    
    
    
    
    Dispose* saida = new Dispose(model);
    components->insert(saida);


    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    chegada_cliente->getNextComponents()->insert(verifica_tempo_simulado);
    verifica_tempo_simulado->getNextComponents()->insert(dentro_horario_pico);
    verifica_tempo_simulado->getNextComponents()->insert(inicia_cliente);
    dentro_horario_pico->getNextComponents()->insert(inicia_cliente);
    inicia_cliente->getNextComponents()->insert(identifica_numero_produtos);
    identifica_numero_produtos->getNextComponents()->insert(define_numero_produtos1);
    identifica_numero_produtos->getNextComponents()->insert(define_numero_produtos2);
    identifica_numero_produtos->getNextComponents()->insert(define_numero_produtos3);
    define_numero_produtos1->getNextComponents()->insert(identifica_tipo_cliente);
    define_numero_produtos2->getNextComponents()->insert(identifica_tipo_cliente);
    define_numero_produtos3->getNextComponents()->insert(identifica_tipo_cliente);
    identifica_tipo_cliente->getNextComponents()->insert(define_idoso);
    identifica_tipo_cliente->getNextComponents()->insert(identifica_fila_cestinha);
    define_idoso->getNextComponents()->insert(identifica_fila_idoso);
    
    identifica_fila_idoso->getNextComponents()->insert(define_fila1_idoso);
    identifica_fila_idoso->getNextComponents()->insert(define_fila2_idoso);
    identifica_fila_idoso->getNextComponents()->insert(identifica_fila_cestinha);
    identifica_fila_idoso->getNextComponents()->insert(rapido_livre);
    identifica_fila_idoso->getNextComponents()->insert(define_fila1_idoso);
    identifica_fila_idoso->getNextComponents()->insert(define_fila2_idoso);
    define_fila1_idoso->getNextComponents()->insert(define_nrProdutos_fila);
    define_fila2_idoso->getNextComponents()->insert(define_nrProdutos_fila);
    
    enter_rapido->getNextComponents()->insert(aloca_rapido);
    aloca_rapido->getNextComponents()->insert(define_fila_rapido);
    define_fila_rapido->getNextComponents()->insert(divide_produtos);
    
    identifica_carrinho_cestinha->getNextComponents()->insert(identifica_fila_cestinha);
    identifica_carrinho_cestinha->getNextComponents()->insert(identifica_fila_carrinho);
    identifica_fila_cestinha->getNextComponents()->insert(rapido_livre);
    identifica_fila_cestinha->getNextComponents()->insert(identifica_fila_vazia);
    identifica_fila_cestinha->getNextComponents()->insert(identifica_fila_idoso);
    identifica_fila_cestinha->getNextComponents()->insert(rapido_livre);
    identifica_fila_vazia->getNextComponents()->insert(define_fila1_jovem);
    identifica_fila_vazia->getNextComponents()->insert(define_fila2_jovem);
    identifica_fila_vazia->getNextComponents()->insert(define_fila3_jovem);
    identifica_fila_vazia->getNextComponents()->insert(define_fila4_jovem);
    identifica_fila_vazia->getNextComponents()->insert(define_fila5_jovem);
    define_fila1_jovem->getNextComponents()->insert(define_nrProdutos_fila);
    define_fila2_jovem->getNextComponents()->insert(define_nrProdutos_fila);
    define_fila3_jovem->getNextComponents()->insert(define_nrProdutos_fila);
    define_fila4_jovem->getNextComponents()->insert(define_nrProdutos_fila);
    define_fila5_jovem->getNextComponents()->insert(define_nrProdutos_fila);
    identifica_fila_carrinho->getNextComponents()->insert(identifica_fila_vazia);
    identifica_fila_carrinho->getNextComponents()->insert(identifica_fila_idoso);
    identifica_fila_carrinho->getNextComponents()->insert(identifica_tamanho_nrProduto);
    identifica_tamanho_nrProduto->getNextComponents()->insert(identifica_menor_fila);
    identifica_tamanho_nrProduto->getNextComponents()->insert(define_nrProdutos_esteira);
    identifica_menor_fila->getNextComponents()->insert(define_fila1_jovem);
    identifica_menor_fila->getNextComponents()->insert(define_fila2_jovem);
    identifica_menor_fila->getNextComponents()->insert(define_fila3_jovem);
    identifica_menor_fila->getNextComponents()->insert(define_fila4_jovem);
    identifica_menor_fila->getNextComponents()->insert(define_fila5_jovem);
    define_nrProdutos_esteira->getNextComponents()->insert(identifica_menos_produtos);
    identifica_menos_produtos->getNextComponents()->insert(define_fila1_jovem);
    identifica_menos_produtos->getNextComponents()->insert(define_fila2_jovem);
    identifica_menos_produtos->getNextComponents()->insert(define_fila3_jovem);
    identifica_menos_produtos->getNextComponents()->insert(define_fila4_jovem);
    identifica_menos_produtos->getNextComponents()->insert(define_fila5_jovem);
    define_nrProdutos_fila->getNextComponents()->insert(aloca_Nrapido);
    
    aloca_Nrapido->getNextComponents()->insert(divide_produtos);
    divide_produtos->getNextComponents()->insert(sai_caixa);
    divide_produtos->getNextComponents()->insert(define_produto);
    define_produto->getNextComponents()->insert(pega_produto);
    pega_produto->getNextComponents()->insert(aloca_esteira);
    aloca_esteira->getNextComponents()->insert(tempo_esteira);
    tempo_esteira->getNextComponents()->insert(inicio_registro);
    inicio_registro->getNextComponents()->insert(aloca_registrador);
    aloca_registrador->getNextComponents()->insert(livra_esteira);
    livra_esteira->getNextComponents()->insert(tempo_registrar);
    tempo_registrar->getNextComponents()->insert(define_registro);
    define_registro->getNextComponents()->insert(livra_registrador);
    livra_registrador->getNextComponents()->insert(define_fim_registro);
    define_fim_registro->getNextComponents()->insert(define_embalo);
    define_embalo->getNextComponents()->insert(define_aux);
    define_aux->getNextComponents()->insert(identifica_ultimo_produto);
    identifica_ultimo_produto->getNextComponents()->insert(define_fim_embalo);
    identifica_ultimo_produto->getNextComponents()->insert(junta_produtos);
    define_fim_embalo->getNextComponents()->insert(junta_produtos);
    junta_produtos->getNextComponents()->insert(define_limpa_aux);
    define_limpa_aux->getNextComponents()->insert(aloca_registrador1);
    aloca_registrador1->getNextComponents()->insert(tempo_embalar);
    tempo_embalar->getNextComponents()->insert(livra_registrador1);
    livra_registrador1->getNextComponents()->insert(define_sacolas);
    define_sacolas->getNextComponents()->insert(identifica_ultimo_produto1);
    identifica_ultimo_produto1->getNextComponents()->insert(define_pagamento);
    identifica_ultimo_produto1->getNextComponents()->insert(sai_caixa);
    define_pagamento->getNextComponents()->insert(sai_caixa);
    sai_caixa->getNextComponents()->insert(define_fim_embalo1);
    define_fim_embalo1->getNextComponents()->insert(tempo_pagar);
    tempo_pagar->getNextComponents()->insert(livra_caixa);
    livra_caixa->getNextComponents()->insert(saida);

    
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
