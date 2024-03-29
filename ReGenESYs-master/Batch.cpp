/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Batch.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:14
 */

#include "Batch.h"
#include "EntityGroup.h"
#include "Model.h"
#include "Attribute.h"

Batch::Batch(Model* model) : ModelComponent(model, Util::TypeOf<Batch>()) {
    this->_batchesCount = 0u;
    this->_batchSize = 0u;
    this->_permanent = false;
    this->_representativeEntityTypeName = "";

    initializeGroupAttribute();
}

Batch::Batch(const Batch& orig) : ModelComponent(orig) {
}

Batch::~Batch() {
}

/*!
 * Display information about the Batch component
 */
std::string Batch::show() {
    return ModelComponent::show() +
	    ",batchSize=" + std::to_string(static_cast<unsigned int> (this->_batchSize)) +
	    ",batchName=\"" + this->_batchName + "\"";
}

ModelComponent* Batch::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Batch* newComponent = new Batch(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

/*!
 *  Set the size of the batch to be created when grouping entities.
 */
void Batch::setBatchSize(unsigned int value) {
    this->_batchSize = value;
}

/*!
 *  Set the name of the batch to be created when grouping entities.
 */
void Batch::setBatchName(std::string value) {
    this->_batchName = value;
}

/*!
 *    Set the type of the batch to be created when grouping entities. Whether
 *  permanent or not
 */
void Batch::setPermanentBatch(bool value) {
    this->_permanent = value;
}

/*!
 *  Set the type of the batch to be created when grouping entities.
 */
void Batch::setByAttributeBatch(bool value) {
    this->_byAttribute = value;
}

/*!
 *  Set the name of the batch to be created when grouping entities.
 */
void Batch::setAttributeName(std::string value) {
    this->_attributeName = value;
}

/*!
 *  Set the entity type of the batch to be created when grouping entities.
 */
void Batch::setRepresentativeEntityTypeName(std::string value) {
    this->_representativeEntityTypeName = value;
}


/*!
 *  Execute the default behavior of the Batch component, which is group a set
 * of entities into a single one. Can be used as an abstraction to a group
 * of entities. It creates a temporary entity with a group reference
 */
void Batch::_execute(Entity* entity) {
    double currentTime = this->_model->getSimulation()->getSimulatedTime();
    ElementManager* elementManager = this->_model->getElementManager();
    TraceManager* traceManager = this->_model->getTraceManager();
//    traceManager->trace(Util::TraceLevel::mostDetailed, "Chegou no batch");
    double attributeValue = 0;
    std::string batchEntityName = entity->getEntityTypeName();
    
//    if(entity->getEntityTypeName().find("_Batch")){
//        batchEntityName = entity->getEntityTypeName();
//    }else{
//        batchEntityName = entity->getEntityTypeName() + "_Batch";
//    }
    std::string batchesCountStr = std::to_string(this->_batchesCount);

    std::string batchEntityID = "";
    if (this->_byAttribute){
    	attributeValue = _model->parseExpression(this->_attributeName);
        batchEntityID = this->_batchName + batchesCountStr  + batchEntityName + std::to_string(attributeValue);
    }else{
        batchEntityID = this->_batchName+ batchesCountStr + batchEntityName;
    }


    traceManager->trace(Util::TraceLevel::blockInternal, "Arrival of entity " + std::to_string(entity->getId()) +
                                                         " at time " + std::to_string(currentTime));
    EntityGroup* group = (EntityGroup*) elementManager->getElement(Util::TypeOf<EntityGroup>(), batchEntityID);

    if (group == nullptr) {
        group = new EntityGroup(elementManager, batchEntityID);
        elementManager->insert(Util::TypeOf<EntityGroup>(), group);
    }

    group->insertElement(entity);

    unsigned int alreadyGrouped = group->size();
    unsigned int batchSize = 0;
    
    batchSize = _model->parseExpression(this->_expression);
    traceManager->trace(Util::TraceLevel::blockInternal, "BatchSize = "+std::to_string(batchSize));
    if (alreadyGrouped == batchSize) {
       
        traceManager->trace(Util::TraceLevel::blockInternal, "Release of batch entity " + std::to_string(entity->getId()) +
                                                             " at time " + std::to_string(currentTime));

        Entity* batchEntity = new Entity(elementManager);
        for (int i = 0; i < elementManager->getNumberOfElements(Util::TypeOf<Attribute>()); i++) {
            List<ModelElement*>* attributes = elementManager->getElements(Util::TypeOf<Attribute>());
            for (int j = 0; j < attributes->size(); j++) {
                Attribute * attr = (Attribute *) attributes->getAtRank(j);
                batchEntity->setAttributeValue(attr->getName(), entity->getAttributeValue(attr->getName()));

            }
        }
        EntityType* batchEntityType = (EntityType*) elementManager->getElement(Util::TypeOf<EntityType>(), batchEntityName);

        if (batchEntityType == nullptr) {
            batchEntityType = new EntityType(elementManager, batchEntityName);
            elementManager->insert(Util::TypeOf<EntityType>(), batchEntityType);
        }

        batchEntity->setEntityType(batchEntityType);
        batchEntity->setAttributeValue("Entity.GroupRankID", (double)elementManager->getRankOf(Util::TypeOf<EntityGroup>(), batchEntityID));
        batchEntity->setAttributeValue("Entity.CopyNumber", 0);
        batchEntity->setAttributeValue("Entity.AttributeValue", (double)attributeValue);

        if (this->_permanent) { batchEntity->setAttributeValue("Entity.Permanent", 1.0); }
        
        

        elementManager->insert(Util::TypeOf<Entity>(), batchEntity);
        elementManager->remove(Util::TypeOf<EntityType>(), batchEntityType);
        elementManager->remove(Util::TypeOf<EntityGroup>(), group);
        this->_model->sendEntityToComponent(batchEntity, this->getNextComponents()->front(), 0.0);
        
        this->_batchesCount++;
    }
}

/*!
 *  Load a previous instance of the Batch class stored.
 */
bool Batch::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
      this->_batchSize = std::stoi((*(fields->find("batchSize"))).second);
      this->_batchName = (*(fields->find("batchName"))).second;
      this->_permanent = (*(fields->find("permanent"))).second == "true";
      this->_attributeName = (*(fields->find("attributeName"))).second;
      this->_representativeEntityTypeName = (*(fields->find("representativeType"))).second;
    }
    return res;
}

/*!
 *    Execute the clean up before each new replication. Simply resets the
 *  counter for already grouped entities and erase existing groups of
 *  entities from the model, if any
 */
void Batch::_initBetweenReplications() {
    this->_batchesCount = 0u;

    ElementManager* elementManager = this->_model->getElementManager();
    EntityGroup* existingGroup = (EntityGroup*) elementManager->getElement(Util::TypeOf<EntityGroup>(), this->_batchName);

    if (existingGroup != nullptr)
      elementManager->remove(Util::TypeOf<EntityGroup>(), existingGroup);
}

std::map<std::string, std::string>* Batch::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    fields->emplace("batchSize", std::to_string(this->_batchSize));
    fields->emplace("batchName", this->_batchName);
    fields->emplace("permanent", std::to_string(this->_permanent));
    fields->emplace("attributeName", this->_attributeName);
    fields->emplace("representativeType", this->_representativeEntityTypeName);
    return fields;
}

/*!
 *  Initialize internal batch specific attributes.
 */
void Batch::initializeGroupAttribute() {
    ElementManager* elementManager = this->_model->getElementManager();
    Attribute* attr = (Attribute*) elementManager->getElement(Util::TypeOf<Attribute>(), "Entity.GroupRankID");

    if (attr == nullptr)
        elementManager->insert(Util::TypeOf<Attribute>(), new Attribute("Entity.GroupRankID"));

    attr = (Attribute*) elementManager->getElement(Util::TypeOf<Attribute>(), "Entity.Permanent");
    if (attr == nullptr)
        elementManager->insert(Util::TypeOf<Attribute>(), new Attribute("Entity.Permanent"));

    attr = (Attribute*) elementManager->getElement(Util::TypeOf<Attribute>(), "Entity.CopyNumber");
    if (attr == nullptr)
        elementManager->insert(Util::TypeOf<Attribute>(), new Attribute("Entity.CopyNumber"));

    attr = (Attribute*) elementManager->getElement(Util::TypeOf<Attribute>(), "Entity.AttributeValue");
    if (attr == nullptr)
        elementManager->insert(Util::TypeOf<Attribute>(), new Attribute("Entity.AttributeValue"));
}

bool Batch::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Batch::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Batch>(), &Batch::LoadInstance);
    // ...
    return info;
}

void Batch::setExpression(std::string value){
    this->_expression = value;
}

