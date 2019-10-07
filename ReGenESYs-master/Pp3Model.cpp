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
    Attribute* embalar = new Attribute("embalar");
    Attribute* pagar = new Attribute("pagar");
    Attribute* collector = new Attribute("collector");
    Attribute* tipo = new Attribute("tipo");
    Attribute* nrProdutos = new Attribute("nrProdutos");
//    Attribute* registro = new Attribute("registro");
    Attribute* caixa_selecionado = new Attribute("caixa_selecionado");
    Attribute* tempo_caixa_idosos = new Attribute("tempo_caixa_idosos");
    Attribute* tempo_caixa = new Attribute("tempo_caixa");
//    Attribute* tempo_embalar = new Attribute("tempo_embalar");
    elements->insert(Util::TypeOf<Attribute>(), embalar);
    elements->insert(Util::TypeOf<Attribute>(), pagar);
    elements->insert(Util::TypeOf<Attribute>(), collector);
    elements->insert(Util::TypeOf<Attribute>(), tempo_caixa);
    elements->insert(Util::TypeOf<Attribute>(), tipo);
    elements->insert(Util::TypeOf<Attribute>(), nrProdutos);
    elements->insert(Util::TypeOf<Attribute>(), tempo_caixa_idosos);
//    elements->insert(Util::TypeOf<Attribute>(), tempo_embalar);
    elements->insert(Util::TypeOf<Attribute>(), caixa_selecionado);
//    elements->insert(Util::TypeOf<Attribute>(), registro);
    
    
    //variaveis
    Variable* qtd_fila_1 = new Variable("qtd_fila_1");
    Variable* qntd_fila_2 = new Variable("qtd_fila_2");
//    Variable* qntd_fila_3 = new Variable("qtd_fila_3");
//    Variable* qntd_fila_4 = new Variable("qtd_fila_4");
//    Variable* qntd_fila_5 = new Variable("qtd_fila_5");
    Variable* est_qtd_fila1 = new Variable("est_qtd_fila1");
    Variable* est_qtd_fila2 = new Variable("est_qtd_fila2");
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
    elements->insert(Util::TypeOf<Variable>(), qtd_fila_1);
    elements->insert(Util::TypeOf<Variable>(), qntd_fila_2);
//    elements->insert(Util::TypeOf<Variable>(), qntd_fila_3);
//    elements->insert(Util::TypeOf<Variable>(), qntd_fila_4);
//    elements->insert(Util::TypeOf<Variable>(), qntd_fila_5);
    elements->insert(Util::TypeOf<Variable>(), est_qtd_fila1);
    elements->insert(Util::TypeOf<Variable>(), est_qtd_fila2);
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
   
    Resource* caixa2_idoso = new Resource(elements, "caixa2_idoso");
    caixa2_idoso->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa2_idoso);
    
    Set* caixas_idoso = new Set(elements, "caixas_idoso");
    caixas_idoso->setSetOfType(Util::TypeOf<Resource>());
    caixas_idoso->getElementSet()->insert(caixa1_idoso);
    caixas_idoso->getElementSet()->insert(caixa2_idoso);
    elements->insert(Util::TypeOf<Set>(), caixas_idoso);
    
    Resource* caixa1_jovem = new Resource(elements, "caixa1_jovem");
    caixa1_jovem->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa1_jovem);
    
    Resource* caixa2_jovem = new Resource(elements, "caixa2_jovem");
    caixa2_jovem->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), caixa2_jovem);
    
    Set* caixas_jovem = new Set(elements, "caixas_jovem");
    caixas_jovem->setSetOfType(Util::TypeOf<Resource>());
    caixas_jovem->getElementSet()->insert(caixa1_jovem);
    caixas_jovem->getElementSet()->insert(caixa2_jovem);
    elements->insert(Util::TypeOf<Set>(), caixas_jovem);
    
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
    
    Set* caixas_rapido = new Set(elements, "caixas_rapido");
    caixas_rapido->setSetOfType(Util::TypeOf<Resource>());
    caixas_rapido->getElementSet()->insert(caixa1_rapido);
    caixas_rapido->getElementSet()->insert(caixa2_rapido);
    caixas_rapido->getElementSet()->insert(caixa3_rapido);
    caixas_rapido->getElementSet()->insert(caixa4_rapido);
    elements->insert(Util::TypeOf<Set>(), caixas_rapido);
    
    
    //Queues
    //---------------------------- Modificacao: Fila unica ----------------------------------
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
    //-------------------------------------------------------------------------------
    
    Queue* fila1_idoso = new Queue(elements, "fila1_idoso");
    fila1_idoso->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila1_idoso);
    
    Queue* fila2_idoso = new Queue(elements, "fila2_idoso");
    fila2_idoso->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila2_idoso);
    
    Queue* fila1_jovem = new Queue(elements, "fila1_jovem");
    fila1_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila1_jovem);
    
    Queue* fila2_jovem = new Queue(elements, "fila2_jovem");
    fila2_jovem->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), fila2_jovem);
    
    //seizes
    Seize* aloca_rapido1 = new Seize(model);
    aloca_rapido1->setResource(caixa1_rapido);
    aloca_rapido1->setQueue(fila1_rapido);
    components->insert(aloca_rapido1);
    
    Seize* aloca_rapido2 = new Seize(model);
    aloca_rapido2->setResource(caixa2_rapido);
    aloca_rapido2->setQueue(fila2_rapido);
    components->insert(aloca_rapido2);
    
    Seize* aloca_rapido3 = new Seize(model);
    aloca_rapido3->setResource(caixa3_rapido);
    aloca_rapido3->setQueue(fila3_rapido);
    components->insert(aloca_rapido3);
    
    Seize* aloca_rapido4 = new Seize(model);
    aloca_rapido4->setResource(caixa4_rapido);
    aloca_rapido4->setQueue(fila4_rapido);
    components->insert(aloca_rapido4);
    
    //-------------------------------------------------- Modificacao: unico size de set, multiplas fila --------------------------------------------------------
    Seize* aloca_idoso1 = new Seize(model);
    aloca_idoso1->setResource(caixa1_idoso);
    aloca_idoso1->setQueue(fila1_idoso);
    components->insert(aloca_idoso1);
    
    Seize* aloca_idoso2 = new Seize(model);
    aloca_idoso2->setResource(caixa2_idoso);
    aloca_idoso2->setQueue(fila2_idoso);
    components->insert(aloca_idoso2);
    
    Seize* aloca_jovem1 = new Seize(model);
    aloca_jovem1->setResource(caixa1_jovem);
    aloca_jovem1->setQueue(fila1_jovem);
    components->insert(aloca_jovem1);
    
    Seize* aloca_jovem2 = new Seize(model);
    aloca_jovem2->setResource(caixa2_jovem);
    aloca_jovem2->setQueue(fila2_jovem);
    components->insert(aloca_jovem2);
    //------------------------------------------------------------------------------------------------------------------------------------
    
    
    // create stations to enter and route to
    Station* idoso = new Station(elements, "idoso");
    Station* jovem = new Station(elements, "jovem");
    Station* rapido = new Station(elements, "rapido");
    elements->insert(Util::TypeOf<Station>(), rapido);
    elements->insert(Util::TypeOf<Station>(), idoso);
    elements->insert(Util::TypeOf<Station>(), jovem);
    
    //enter
    Enter* enter_idoso = new Enter(model);
    enter_idoso->setStation(idoso);
    components->insert(enter_idoso);
    
    Enter* enter_jovem = new Enter(model);
    enter_jovem->setStation(jovem);
    components->insert(enter_jovem);
    
    Enter* enter_rapido = new Enter(model);
    enter_rapido->setStation(rapido);
    components->insert(enter_rapido);
    
    //route
    Route* cliente_idoso = new Route(model);
    cliente_idoso->setStation(idoso);
    cliente_idoso->setRouteTimeExpression("0");
    components->insert(cliente_idoso);
    
    Route* cliente_jovem = new Route(model);
    cliente_jovem->setStation(jovem);
    cliente_jovem->setRouteTimeExpression("0");
    components->insert(cliente_jovem);
    
    Route* jovem_livre = new Route(model);
    jovem_livre->setStation(jovem);
    jovem_livre->setRouteTimeExpression("0");
    components->insert(jovem_livre);
    
    Route* rapido_livre = new Route(model);
    rapido_livre->setStation(rapido);
    rapido_livre->setRouteTimeExpression("UNIF(2,5)");
    rapido_livre->setRouteTimeTimeUnit(Util::TimeUnit::second);
    components->insert(rapido_livre);
   
    
    //entidades
    EntityType* cliente = new EntityType(elements, "cliente");
    elements->insert(Util::TypeOf<EntityType>(), cliente);
    
    
    //assigns e componentes
    Create* chegada_cliente = new Create(model);
    chegada_cliente->setEntityType(cliente);
    chegada_cliente->setTimeBetweenCreationsExpression("50");
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
//    Assign::Assignment* a_qtd_fila_1 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_1", "0");
//    Assign::Assignment* a_qtd_fila_2 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_2", "0");
//    Assign::Assignment* a_qtd_fila_3 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_3", "0");
//    Assign::Assignment* a_qtd_fila_4 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_4", "0");
//    Assign::Assignment* a_qtd_fila_5 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_5", "0");
    Assign::Assignment* a_embalar = new Assign::Assignment(Assign::DestinationType::Attribute, "embalar", "8");
    Assign::Assignment* a_pagar = new Assign::Assignment(Assign::DestinationType::Attribute, "pagar", "100");
    Assign::Assignment* a_collector = new Assign::Assignment(Assign::DestinationType::Attribute, "collector", "0");
    Assign::Assignment* a_tipo_jovem = new Assign::Assignment(Assign::DestinationType::Attribute, "tipo", "1");//DISC(0.3,0,1,1)
    Assign::Assignment* a_tempo_caixa = new Assign::Assignment(Assign::DestinationType::Attribute, "tempo_caixa", "TNOW");
    Assign::Assignment* a_nrProdutos = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "UNIF(0,1)");//AINT(DISC(0.45,UNIF(1,8),0.9,UNIF(9,12),1,UNIF(13,20)))
//    inicia_cliente->getAssignments()->insert(a_qtd_fila_1);
//    inicia_cliente->getAssignments()->insert(a_qtd_fila_2);
//    inicia_cliente->getAssignments()->insert(a_qtd_fila_3);
//    inicia_cliente->getAssignments()->insert(a_qtd_fila_4);
//    inicia_cliente->getAssignments()->insert(a_qtd_fila_5);
    inicia_cliente->getAssignments()->insert(a_embalar);
    inicia_cliente->getAssignments()->insert(a_pagar);
    inicia_cliente->getAssignments()->insert(a_collector);
    inicia_cliente->getAssignments()->insert(a_tipo_jovem);
    inicia_cliente->getAssignments()->insert(a_tempo_caixa);
    inicia_cliente->getAssignments()->insert(a_nrProdutos);
    components->insert(inicia_cliente);
    
    //---------------------------------------- Modificacao: AINT(DISC(0.45,UNIF(1,8),0.9,UNIF(9,12),1,UNIF(13,20))) ----------------------------------------------
    Decide* identifica_numero_produtos = new Decide(model);
    identifica_numero_produtos->getConditions()->insert("nrProdutos < 0.4");
    identifica_numero_produtos->getConditions()->insert("nrProdutos >= 0.4 and nrProdutos < 0.8");
    
    Assign* define_numero_produtos1 = new Assign(model);
    Assign::Assignment* a_numero_produtos1 = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "AINT(UNIF(1,8))");
    define_numero_produtos1->getAssignments()->insert(a_numero_produtos1);
    components->insert(define_numero_produtos1);
    
    Assign* define_numero_produtos2 = new Assign(model);
    Assign::Assignment* a_numero_produtos2 = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "AINT(UNIF(9,12))");
    define_numero_produtos2->getAssignments()->insert(a_numero_produtos2);
    components->insert(define_numero_produtos2);
    
    Assign* define_numero_produtos3 = new Assign(model);
    Assign::Assignment* a_numero_produtos3 = new Assign::Assignment(Assign::DestinationType::Attribute, "nrProdutos", "AINT(UNIF(13,20))");
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
    identifica_fila_idoso->getConditions()->insert("nrProdutos < 9 and NQ(fila1_rapido) + NQ(fila2_rapido) < 5");
    identifica_fila_idoso->getConditions()->insert("NQ(fila1_idoso) < NQ(fila2_idoso)");
    
    Assign* define_fila1_idoso = new Assign(model);
    Assign::Assignment* a_caixa1_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "1");
//    Assign::Assignment* a_nProdutos1 = new Assign::Assignment(Assign::DestinationType::Variable, "nProdutos_1","nrProdutos");
    define_fila1_idoso->getAssignments()->insert(a_caixa1_selecionado);
//    define_fila1_idoso->getAssignments()->insert(a_nProdutos1);
    components->insert(define_fila1_idoso);
    
    Assign* define_fila2_idoso = new Assign(model);
    Assign::Assignment* a_caixa2_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "2");
//    Assign::Assignment* a_nProdutos2 = new Assign::Assignment(Assign::DestinationType::Variable, "nProdutos_2","nrProdutos");
    define_fila2_idoso->getAssignments()->insert(a_caixa2_selecionado);
//    define_fila2_idoso->getAssignments()->insert(a_nProdutos2);
    components->insert(define_fila2_idoso);
   
    
    //----------------------------------------------- Modificacao: unico size de set, unica fila -----------------------
    Decide* identifica_fila_rapido = new Decide(model);
    identifica_fila_rapido->getConditions()->insert("NQ(fila1_rapido) <= NQ(fila2_rapido) and NQ(fila1_rapido) <= NQ(fila3_rapido) and NQ(fila1_rapido) <= NQ(fila4_rapido)");
    identifica_fila_rapido->getConditions()->insert("NQ(fila2_rapido) <= NQ(fila1_rapido) and NQ(fila2_rapido) <= NQ(fila3_rapido) and NQ(fila2_rapido) <= NQ(fila4_rapido)");
    identifica_fila_rapido->getConditions()->insert("NQ(fila3_rapido) <= NQ(fila1_rapido) and NQ(fila3_rapido) <= NQ(fila2_rapido) and NQ(fila3_rapido) <= NQ(fila4_rapido)");
    
    Assign* define_fila1_rapido = new Assign(model);
    Assign::Assignment* a_caixa1r_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "5");
//    Assign::Assignment* a_nProdutos1r = new Assign::Assignment(Assign::DestinationType::Variable, "nProdutos_5","nrProdutos");
    define_fila1_rapido->getAssignments()->insert(a_caixa1r_selecionado);
//    define_fila1_rapido->getAssignments()->insert(a_nProdutos1r);
    components->insert(define_fila1_rapido);
    
    Assign* define_fila2_rapido = new Assign(model);
    Assign::Assignment* a_caixa2r_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "6");
//    Assign::Assignment* a_nProdutos2r = new Assign::Assignment(Assign::DestinationType::Variable, "nProdutos_6","nrProdutos");
    define_fila2_rapido->getAssignments()->insert(a_caixa2r_selecionado);
//    define_fila2_rapido->getAssignments()->insert(a_nProdutos2r);
    components->insert(define_fila2_rapido);
    
    Assign* define_fila3_rapido = new Assign(model);
    Assign::Assignment* a_caixa3r_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "7");
//    Assign::Assignment* a_nProdutos3r = new Assign::Assignment(Assign::DestinationType::Variable, "nProdutos_7","nrProdutos");
    define_fila3_rapido->getAssignments()->insert(a_caixa3r_selecionado);
//    define_fila3_rapido->getAssignments()->insert(a_nProdutos3r);
    components->insert(define_fila3_rapido);
    
    Assign* define_fila4_rapido = new Assign(model);
    Assign::Assignment* a_caixa4r_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "8");
//    Assign::Assignment* a_nProdutos4r = new Assign::Assignment(Assign::DestinationType::Variable, "nProdutos_8","nrProdutos");
    define_fila4_rapido->getAssignments()->insert(a_caixa4r_selecionado);
//    define_fila4_rapido->getAssignments()->insert(a_nProdutos4r);
    components->insert(define_fila4_rapido);
    
    //---------------------------------------------------------------------------------------------------------------------
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
    
    Route* idoso_livre = new Route(model);
    idoso_livre->setStation(idoso);
    idoso_livre->setRouteTimeExpression("0");
    components->insert(idoso_livre);
    
    Decide* identifica_tamanho_nrProduto = new Decide(model);
    identifica_tamanho_nrProduto->getConditions()->insert("UNIF(0,1) < 0.5");
    
    Decide* identifica_menor_fila = new Decide(model);
    identifica_menor_fila->getConditions()->insert("NQ(fila1_jovem) <= NQ(fila2_jovem)");
    
    Assign* define_nrProdutos_fila = new Assign(model);
    Assign::Assignment* a_est_qtd_fila1 = new Assign::Assignment(Assign::DestinationType::Variable, "est_qtd_fila1", "UNIF(qtd_fila_1*0.7,qtd_fila_1*1.3)");
    Assign::Assignment* a_est_qtd_fila2 = new Assign::Assignment(Assign::DestinationType::Variable, "est_qtd_fila2","UNIF(qtd_fila_2*0.7,qtd_fila_2*1.3)");
    define_nrProdutos_fila->getAssignments()->insert(a_est_qtd_fila1);
    define_nrProdutos_fila->getAssignments()->insert(a_est_qtd_fila2);
    components->insert(define_nrProdutos_fila);
    
    Decide* identifica_menos_produtos = new Decide(model);
    identifica_menos_produtos->getConditions()->insert("est_qtd_fila1 < est_qtd_fila2");
    
    Assign* define_fila1_jovem = new Assign(model);
    Assign::Assignment* a_caixa1j_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "3");
//    Assign::Assignment* a_nProdutos1j = new Assign::Assignment(Assign::DestinationType::Variable, "nProdutos_3","nrProdutos");
    Assign::Assignment* a_qtd_fila_1 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_1","qtd_fila_1 + nrProdutos");
    define_fila1_jovem->getAssignments()->insert(a_caixa1j_selecionado);
//    define_fila1_jovem->getAssignments()->insert(a_nProdutos1j);
    define_fila1_jovem->getAssignments()->insert(a_qtd_fila_1);
    components->insert(define_fila1_jovem);
    
    Assign* define_fila2_jovem = new Assign(model);
    Assign::Assignment* a_caixa2j_selecionado = new Assign::Assignment(Assign::DestinationType::Attribute, "caixa_selecionado", "4");
//    Assign::Assignment* a_nProdutos2j = new Assign::Assignment(Assign::DestinationType::Variable, "nProdutos_4","nrProdutos");
    Assign::Assignment* a_qtd_fila_2 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_2","qtd_fila_2 + nrProdutos");
    define_fila2_jovem->getAssignments()->insert(a_caixa2j_selecionado);
//    define_fila2_jovem->getAssignments()->insert(a_nProdutos2j);
    define_fila2_jovem->getAssignments()->insert(a_qtd_fila_2);
    components->insert(define_fila2_jovem);
    
    Assign* define_saida_fila1_jovem = new Assign(model);
    Assign::Assignment* a1_qtd_fila_1 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_1","qtd_fila_1 - nrProdutos");
    define_saida_fila1_jovem->getAssignments()->insert(a1_qtd_fila_1);
    components->insert(define_saida_fila1_jovem);
    
    Assign* define_saida_fila2_jovem = new Assign(model);
    Assign::Assignment* a1_qtd_fila_2 = new Assign::Assignment(Assign::DestinationType::Variable, "qtd_fila_2","qtd_fila_2 - nrProdutos");
    define_saida_fila2_jovem->getAssignments()->insert(a1_qtd_fila_1);
    components->insert(define_saida_fila2_jovem);
    
    
    Dispose* saida_rapido = new Dispose(model);
    components->insert(saida_rapido);
    
    Dispose* saida_normal = new Dispose(model);
    components->insert(saida_normal);


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
    identifica_tipo_cliente->getNextComponents()->insert(cliente_jovem);
    define_idoso->getNextComponents()->insert(cliente_idoso);
    
    enter_idoso->getNextComponents()->insert(identifica_fila_idoso);
    identifica_fila_idoso->getNextComponents()->insert(define_fila1_idoso);
    identifica_fila_idoso->getNextComponents()->insert(define_fila2_idoso);
    identifica_fila_idoso->getNextComponents()->insert(jovem_livre);
    identifica_fila_idoso->getNextComponents()->insert(rapido_livre);
    identifica_fila_idoso->getNextComponents()->insert(define_fila1_idoso);
    identifica_fila_idoso->getNextComponents()->insert(define_fila2_idoso);
    define_fila1_idoso->getNextComponents()->insert(aloca_idoso1);
    define_fila2_idoso->getNextComponents()->insert(aloca_idoso2);
    aloca_idoso1->getNextComponents()->insert(saida_normal);
    aloca_idoso2->getNextComponents()->insert(saida_normal);
    
    enter_rapido->getNextComponents()->insert(identifica_fila_rapido);
    identifica_fila_rapido->getNextComponents()->insert(aloca_rapido1);
    identifica_fila_rapido->getNextComponents()->insert(aloca_rapido2);
    identifica_fila_rapido->getNextComponents()->insert(aloca_rapido3);
    identifica_fila_rapido->getNextComponents()->insert(aloca_rapido4);
    aloca_rapido1->getNextComponents()->insert(define_fila1_rapido);
    aloca_rapido2->getNextComponents()->insert(define_fila2_rapido);
    aloca_rapido3->getNextComponents()->insert(define_fila3_rapido);
    aloca_rapido4->getNextComponents()->insert(define_fila4_rapido);
    define_fila1_rapido->getNextComponents()->insert(saida_rapido);
    define_fila2_rapido->getNextComponents()->insert(saida_rapido);
    define_fila3_rapido->getNextComponents()->insert(saida_rapido);
    define_fila4_rapido->getNextComponents()->insert(saida_rapido);
    
    enter_jovem->getNextComponents()->insert(identifica_carrinho_cestinha);
    identifica_carrinho_cestinha->getNextComponents()->insert(identifica_fila_cestinha);
    identifica_carrinho_cestinha->getNextComponents()->insert(identifica_fila_carrinho);
    identifica_fila_cestinha->getNextComponents()->insert(rapido_livre);
    identifica_fila_cestinha->getNextComponents()->insert(identifica_fila_vazia);
    identifica_fila_cestinha->getNextComponents()->insert(idoso_livre);
    identifica_fila_cestinha->getNextComponents()->insert(rapido_livre);
    identifica_fila_vazia->getNextComponents()->insert(define_fila1_jovem);
    identifica_fila_vazia->getNextComponents()->insert(define_fila2_jovem);
    define_fila1_jovem->getNextComponents()->insert(aloca_jovem1);
    define_fila2_jovem->getNextComponents()->insert(aloca_jovem2);
    identifica_fila_carrinho->getNextComponents()->insert(identifica_fila_vazia);
    identifica_fila_carrinho->getNextComponents()->insert(idoso_livre);
    identifica_fila_carrinho->getNextComponents()->insert(identifica_tamanho_nrProduto);
    identifica_tamanho_nrProduto->getNextComponents()->insert(identifica_menor_fila);
    identifica_tamanho_nrProduto->getNextComponents()->insert(define_nrProdutos_fila);
    identifica_menor_fila->getNextComponents()->insert(define_fila1_jovem);
    identifica_menor_fila->getNextComponents()->insert(define_fila2_jovem);
    define_nrProdutos_fila->getNextComponents()->insert(identifica_menos_produtos);
    identifica_menos_produtos->getNextComponents()->insert(define_fila1_jovem);
    identifica_menos_produtos->getNextComponents()->insert(define_fila2_jovem);
    aloca_jovem1->getNextComponents()->insert(define_saida_fila1_jovem);
    aloca_jovem2->getNextComponents()->insert(define_saida_fila2_jovem);
    define_saida_fila1_jovem->getNextComponents()->insert(saida_normal);
    define_saida_fila2_jovem->getNextComponents()->insert(saida_normal);
    
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
