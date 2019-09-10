/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyReGenESYsApplication.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 20 de Maio de 2019, 21:01
 */

#include "MyApp.h"
#include "GenesysConsole.h"

// GEnSyS Simulator
#include "Simulator.h"

// Configuration
#include "Traits.h"

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
#include "ElementManager.h"
#include "EntityType.h"
#include "Attribute.h"
#include "Variable.h"
#include "ProbDistrib.h"
#include "Group.h"
#include "Formula.h"
#include "ODE.h"

void traceHandler(TraceEvent e) {
    std::cout << e.getText() << std::endl;
}

void traceSimulationHandler(TraceSimulationEvent e) {
    std::cout << e.getText() << std::endl;
}

void onSimulationStartHandler(SimulationEvent* re) {
    std::cout << "(Handler) Simulation is starting" << std::endl;
}

void onReplicationStartHandler(SimulationEvent* re) {
    std::cout << "(Handler) Replication " << re->getReplicationNumber() << " starting." << std::endl;
}

void onProcessEventHandler(SimulationEvent* re) {
    std::cout << "(Handler) Processing event " << re->getEventProcessed()->show() << std::endl;
}

void onReplicationEndHandler(SimulationEvent* re) {
    std::cout << "(Handler) Replication " << re->getReplicationNumber() << " ending." << std::endl;
}

void onEntityRemoveHandler(SimulationEvent* re) {
    std::cout << "(Handler) Entity " << re->getEventProcessed()->getEntity() << " was removed." << std::endl;
}

MyApp::MyApp() {
}

MyApp::MyApp(const MyApp& orig) {
}

MyApp::~MyApp() {
}

void MyApp::insertFakePluginsByHand(Simulator* simulator) {
    // model elements
    simulator->getPluginManager()->insert(new Plugin(&Attribute::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Counter::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&EntityType::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Queue::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Resource::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&StatisticsCollector::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Variable::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Group::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Formula::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&ODE::GetPluginInformation));
    // model components
    simulator->getPluginManager()->insert(new Plugin(&Assign::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Create::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Decide::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Delay::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Dispose::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Dummy::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Record::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Release::GetPluginInformation));
    simulator->getPluginManager()->insert(new Plugin(&Seize::GetPluginInformation));
}

void _testaMeuModelo(Model* model) {
    ModelInfo* info = model->getInfos();
    info->setNumberOfReplications(1);
    info->setReplicationLength(6);
    info->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    model->getTraceManager()->setTraceLevel(Util::TraceLevel::mostDetailed);

    EntityType* entType1 = new EntityType(model->getElementManager());
    entType1->setName("Carro");
    model->getElementManager()->insert(Util::TypeOf<EntityType>(), entType1);

    //Formula* form1 = new Formula(model->getElementManager());
    //form1->setName("Gravidade");
    //form1->setFormulaExpression("2+3-1");
    //model->getElementManager()->insert(Util::TypeOf<Formula>(), form1);

    Create* create1 = new Create(model);
    create1->setEntityType(entType1);
    create1->setTimeBetweenCreationsExpression("2+3-1"); //("Gravidade");
    create1->setTimeUnit(Util::TimeUnit::second);
    model->getComponentManager()->insert(create1);


    Variable* var1 = new Variable();
    var1->setName("var1");
    model->getElementManager()->insert(Util::TypeOf<Variable>(), var1);

    ODE* ode1 = new ODE(model->getElementManager());
    ODEfunction* func1 = new ODEfunction("var1 - TNOW*TNOW + 1", 0.0, 0.5);
    ode1->getODEfunctions()->insert(func1);
    ode1->setStepH(0.2);
    ode1->setEndTime(2.0);
    model->getElementManager()->insert(Util::TypeOf<ODE>(), ode1);

    Dummy* dummy1 = new Dummy(model);
    dummy1->setOde(ode1);
    model->getComponentManager()->insert(dummy1);
    //ODE* ode1 = new ODE(model);
    //model->getComponentManager()->insert(ode1);

    Dispose* dispose1 = new Dispose(model);
    model->getComponentManager()->insert(dispose1);

    create1->getNextComponents()->insert(dummy1);
    dummy1->getNextComponents()->insert(dispose1);
}

void _buildModel01_CreDelDis(Model* model) {
    // buildModelWithAllImplementedComponents
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(60);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(1);
    infos->setDescription("./models/model01_CreDelDis.txt");

    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();

    EntityType* entityType1 = new EntityType(elements, "EntityType_1");
    elements->insert(Util::TypeOf<EntityType>(), entityType1);

    Create* create1 = new Create(model);
    create1->setEntityType(entityType1);
    create1->setTimeBetweenCreationsExpression("1");
    create1->setTimeUnit(Util::TimeUnit::second);
    create1->setEntitiesPerCreation(1);
    components->insert(create1);

    Delay* delay1 = new Delay(model);
    delay1->setDelayExpression("2");
    delay1->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(delay1);

    Dispose* dispose1 = new Dispose(model);
    components->insert(dispose1);

    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    create1->getNextComponents()->insert(delay1);
    delay1->getNextComponents()->insert(dispose1);
}

void _buildModel02_CreDelDis(Model* model) {
    // buildModelWithAllImplementedComponents
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(60);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(1);
    infos->setDescription("./models/model02_CreDelDis.txt");

    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();

    EntityType* entityType1 = new EntityType(elements, "EntityType_1");
    elements->insert(Util::TypeOf<EntityType>(), entityType1);

    Create* create1 = new Create(model);
    create1->setEntityType(entityType1);
    create1->setTimeBetweenCreationsExpression("expo(1)");
    create1->setTimeUnit(Util::TimeUnit::second);
    create1->setEntitiesPerCreation(1);
    components->insert(create1);

    Delay* delay1 = new Delay(model);
    delay1->setDelayExpression("norm(2,0.67)");
    delay1->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(delay1);

    Dispose* dispose1 = new Dispose(model);
    components->insert(dispose1);

    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    create1->getNextComponents()->insert(delay1);
    delay1->getNextComponents()->insert(dispose1);
}

void _buildModel03_CreSeiDelResDis(Model* model) {
    // buildModelWithAllImplementedComponents
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(60);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(1);
    infos->setDescription("./models/model03_CreSeiDelRelDis.txt");

    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();

    EntityType* entityType1 = new EntityType(elements, "EntityType_1");
    elements->insert(Util::TypeOf<EntityType>(), entityType1);

    Create* create1 = new Create(model);
    create1->setEntityType(entityType1);
    create1->setTimeBetweenCreationsExpression("expo(2)");
    create1->setTimeUnit(Util::TimeUnit::second);
    create1->setEntitiesPerCreation(1);
    components->insert(create1);

    Resource* machine1 = new Resource(elements, "Machine_1");
    machine1->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), machine1);

    Queue* queueSeize1 = new Queue(elements, "Queue_Machine_1");
    queueSeize1->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), queueSeize1);

    Seize* seize1 = new Seize(model);
    seize1->setResource(machine1);
    seize1->setQueue(queueSeize1);
    components->insert(seize1);

    Delay* delay1 = new Delay(model);
    delay1->setDelayExpression("norm(2,0.67)");
    delay1->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(delay1);

    Release* release1 = new Release(model);
    release1->setResource(machine1);
    components->insert(release1);

    Dispose* dispose1 = new Dispose(model);
    components->insert(dispose1);

    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    create1->getNextComponents()->insert(seize1);
    seize1->getNextComponents()->insert(delay1);
    delay1->getNextComponents()->insert(release1);
    release1->getNextComponents()->insert(dispose1);
}

void _buildMostCompleteModel(Model* model) {
    // buildModelWithAllImplementedComponents
    ModelInfo* infos = model->getInfos();
    infos->setAnalystName("Your name");
    infos->setProjectTitle("The title of the project");
    infos->setDescription("The description of the project");
    infos->setReplicationLength(1e3);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::minute);
    infos->setNumberOfReplications(10);
    infos->setWarmUpPeriod(50);
    infos->setWarmUpPeriodTimeUnit(Util::TimeUnit::minute);
    infos->setDescription("./models/model99_AllTogether.txt");

    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();

    EntityType* entityType1 = new EntityType(elements, "Representative_EntityType");
    elements->insert(Util::TypeOf<EntityType>(), entityType1);

    Create* create1 = new Create(model);
    create1->setEntityType(entityType1);
    create1->setTimeBetweenCreationsExpression("EXPO(5)");
    create1->setTimeUnit(Util::TimeUnit::minute);
    create1->setEntitiesPerCreation(1);
    components->insert(create1);

    Attribute* attribute1 = new Attribute("Attribute_1");
    elements->insert(Util::TypeOf<Attribute>(), attribute1);
    Variable* variable1 = new Variable("Variable_1");
    elements->insert(Util::TypeOf<Variable>(), variable1);

    Assign* assign1 = new Assign(model);
    Assign::Assignment* attrib2Assignment = new Assign::Assignment(Assign::DestinationType::Variable, "Variable_1", "Variable_1 + 1");
    assign1->getAssignments()->insert(attrib2Assignment);
    Assign::Assignment* attrib1Assignment = new Assign::Assignment(Assign::DestinationType::Attribute, "Attribute_1", "Variable_1");
    assign1->getAssignments()->insert(attrib1Assignment);
    components->insert(assign1);

    Decide* decide1 = new Decide(model);
    //decide1->getConditions()->insert("UNIF(0,1)>=0.5");
    decide1->getConditions()->insert("NQ(Queue_Machine_1) <= 2*NQ(Queue_Machine_2)");

    Resource* machine1 = new Resource(elements, "Machine_1");
    machine1->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), machine1);

    Queue* queueSeize1 = new Queue(elements, "Queue_Machine_1");
    queueSeize1->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), queueSeize1);

    Seize* seize1 = new Seize(model);
    seize1->setResource(machine1);
    seize1->setQueue(queueSeize1);
    components->insert(seize1);

    Delay* delay1 = new Delay(model);
    delay1->setDelayExpression("NORM(5,1.5)");
    delay1->setDelayTimeUnit(Util::TimeUnit::minute);
    components->insert(delay1);

    Release* release1 = new Release(model);
    release1->setResource(machine1);
    components->insert(release1);

    Record* record1 = new Record(model);
    record1->setExpressionName("Time in system after releasing machine 1");
    record1->setExpression("TNOW - Entity.ArrivalTime");
    record1->setFilename("./temp/TimeAfterMachine1.txt");
    components->insert(record1);

    Dispose* dispose1 = new Dispose(model);
    components->insert(dispose1);

    Resource* machine2 = new Resource(elements, "Machine_2");
    machine2->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), machine2);

    Queue* queueSeize2 = new Queue(elements, "Queue_Machine_2");
    queueSeize2->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), queueSeize2);

    Seize* seize2 = new Seize(model);
    seize2->setResource(machine2);
    seize2->setQueue(queueSeize2);
    components->insert(seize2);

    Delay* delay2 = new Delay(model);
    delay2->setDelayExpression("NORM(5,1.5)");
    delay2->setDelayTimeUnit(Util::TimeUnit::minute);
    components->insert(delay2);

    Release* release2 = new Release(model);
    release2->setResource(machine2);
    components->insert(release2);

    Record* record2 = new Record(model);
    record2->setExpressionName("Time in system after releasing machine 2");
    record2->setExpression("TNOW - Entity.ArrivalTime");
    record2->setFilename("./temp/TimeAfterMachine2.txt");
    components->insert(record2);

    Dummy* dummy1 = new Dummy(model);
    components->insert(dummy1);

    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    create1->getNextComponents()->insert(assign1);
    assign1->getNextComponents()->insert(decide1);
    decide1->getNextComponents()->insert(seize1);
    decide1->getNextComponents()->insert(seize2);
    seize1->getNextComponents()->insert(delay1);
    delay1->getNextComponents()->insert(release1);
    release1->getNextComponents()->insert(record1);
    record1->getNextComponents()->insert(dispose1);
    seize2->getNextComponents()->insert(delay2);
    delay2->getNextComponents()->insert(release2);
    release2->getNextComponents()->insert(record2);
    record2->getNextComponents()->insert(dummy1);
    dummy1->getNextComponents()->insert(dispose1);
}

//--------------------------------------------------------PP3 Model----------------------------------------------------------------------------------------------
void _buildModelPP3(Model* model) {
    // buildModelWithAllImplementedComponents
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(36000);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(1);
    infos->setDescription("./models/model01_CreDelDis.txt");

    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();

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
}
//--------------------------------------------------------Testes-------------------------------------------------------------------------------------------------
void _testeAssign(Model* model) {
    // buildModelWithAllImplementedComponents
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(36000);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(1);
    infos->setDescription("./models/model01_CreDelDis.txt");

    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();

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
}
void _testeDecide(Model* model) {
    // buildModelWithAllImplementedComponents
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(36000);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(1);
    infos->setDescription("./models/model01_CreDelDis.txt");

    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();

    EntityType* entityType1 = new EntityType(elements, "Cliente");
    elements->insert(Util::TypeOf<EntityType>(), entityType1);

    Create* chegada_cliente = new Create(model);
    chegada_cliente->setEntityType(entityType1);
    chegada_cliente->setTimeBetweenCreationsExpression("EXPO(20)");
    chegada_cliente->setTimeUnit(Util::TimeUnit::second);
    chegada_cliente->setEntitiesPerCreation(1);
    components->insert(chegada_cliente);
    

    Decide* decide1 = new Decide(model);
    decide1->getConditions()->insert("TNOW<10800 or TNOW>25200");
//    decide1->getConditions()->insert("NQ(Queue_Machine_1) <= 2*NQ(Queue_Machine_2)");

    Dispose* saida_cliente_velho = new Dispose(model);
    components->insert(saida_cliente_velho);
    
    Dispose* saida_cliente_novo = new Dispose(model);
    components->insert(saida_cliente_novo);

    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    chegada_cliente->getNextComponents()->insert(decide1);
    decide1->getNextComponents()->insert(saida_cliente_velho);
    decide1->getNextComponents()->insert(saida_cliente_novo);
}

/**
 * This function shows an example of how to create a simulation model.
 * It creates some handlers for tracing (debug) and for events, set model infos and than creates the model itself.
 * The model is a composition of components (and elements that they use), connected to form a process/fluxogram 
 * @param model - The instance returned that will contains the built model
 */
void MyApp::builAndRunSimulationdModel() {
    Simulator* simulator = new Simulator();

    // traces handle and simulation events to output them
    TraceManager* tm = simulator->getTraceManager();
//    tm->addTraceHandler(&traceHandler);
    tm->addTraceReportHandler(&traceHandler);
//    tm->addTraceSimulationHandler(&traceSimulationHandler);

    /*
OnEventManager* ev = model->getOnEventManager();
ev->addOnSimulationStartHandler(&onSimulationStartHandler);
ev->addOnReplicationStartHandler(&onReplicationStartHandler);
ev->addOnReplicationEndHandler(&onReplicationEndHandler);
ev->addOnProcessEventHandler(&onProcessEventHandler);
     */

    // Insert some fake plugins, since components and elements are NOT dynamic linked. 
    // Basically all ModelComponents and ModelElements classes that may de used to buikd simulation models and to be persisted to files, should be "declared" by plugins.
    this->insertFakePluginsByHand(simulator);

    Model* model = new Model(simulator);
//    _testeDecide(model);
//    _testeAssign(model);
    _buildModelPP3(model);
    
    
    
    
    
    
//    _buildModel01_CreDelDis(model);
    //_buildModel02_CreDelDis(model);
    //_buildModel03_CreSeiDelResDis(model);
    //_testaMeuModelo(model);
//    _buildMostCompleteModel(model);

    //simulator->getModelManager()->insert(model);
    //model->saveModel(model->getInfos()->getDescription());

    //simulator->getModelManager()->loadModel("./models/model99_AllTogether.txt");
    simulator->getModelManager()->loadModel("./models/model01_CreDelDis.txt");

    //model->checkModel();
    model->show();
    model->getSimulation()->startSimulation();
}

int MyApp::main(int argc, char** argv) {
    this->builAndRunSimulationdModel();
    return 0;
}