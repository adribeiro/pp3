/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Separate.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:14
 */

#include "Separate.h"

#include "Model.h"
#include "EntityGroup.h"

#include <string>
#include <list>
#include <assert.h>
#include "Attribute.h"

Separate::Separate(Model* model) : ModelComponent(model, Util::TypeOf<Separate>()) {
}

Separate::Separate(const Separate& orig) : ModelComponent(orig) {
}

Separate::~Separate() {
}

std::string Separate::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Separate::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Separate* newComponent = new Separate(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

/*!
 *  Set the name of the separate to be created when spliting entities.
 */
void Separate::setSeparateName(std::string value) {
    this->_separateName = value;
}

/*!
 *    Set the type of the separate, whether it must split existing batch or
 *  duplicate the incoming entity
 */
void Separate::setSplitBatch(bool value) {
    this->_splitBatch = value;
}

/*!
 *  Set the number of duplicates to an entity to be generated, when using
 * duplication
 */
void Separate::setAmountToDuplicate(std::string value) {
    this->_amountToDup = value;
}

/*!
 *  Set how to assign the representative entity attribute values to the
 *  original entities
 */
void Separate::setTakeAllRepresentativeValues(bool value) {
	this->_takeAllRepresentativeValues = value;
}

/*!
 *  Execute the default behavior of the Separate component, which receives an
 * entity with a Batch of entities. It must split the original batch or
 * duplicate it, based on it's parameters. Can receive either a Batch entity
 * or any other entity
 */
void Separate::_execute(Entity* entity) {
    double currentTime = _model->getSimulation()->getSimulatedTime();

    ElementManager* elementManager = this->_model->getElementManager();
    TraceManager* traceManager = this->_model->getTraceManager();

    traceManager->trace(Util::TraceLevel::blockInternal, "Arrival of entity " + std::to_string(entity->getId()) +
                                                         " at time " + std::to_string(currentTime));
    
    double replicationsNumber = _model->parseExpression(this->_amountToDup);
    
    if (this->_splitBatch) {
      /* Split the existing Batch entity */
      /*TODO*/

    } else {
      /* Duplicate the existing entity */
        traceManager->trace(Util::TraceLevel::blockInternal, "Duplicate the existing entity");


        Entity* duplicateEntity;

        _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "Sending the original entity forward to the first connection");
        this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);

        for (int k = 0; k < replicationsNumber; k++) {
            /* Duplicate input entity in N entities*/

            if (entity->getEntityTypeName().find("_Batch") != std::string::npos) {
                /*TODO*/
            } else {
                duplicateEntity = new Entity(elementManager);
                duplicateEntity->setEntityType(entity->getEntityType());
                ElementManager* elements = _model->getElementManager();
                for(int i =0; i<elements->getNumberOfElements(Util::TypeOf<Attribute>());i++){
                    List<ModelElement*>* attributes = elements->getElements(Util::TypeOf<Attribute>());
                    for(int j =0; j< attributes->size();j++){
                        Attribute * attr = (Attribute *) attributes->getAtRank(j);
                        duplicateEntity->setAttributeValue(attr->getName(),entity->getAttributeValue(attr->getName()));
                        
                    }
                }
                _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "Sending a copied entity forward to the second connection");
                _model->sendEntityToComponent(duplicateEntity, this->getNextComponents()->getConnectionAtRank(1), 0.0);
            }
        }
    }
}

bool Separate::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
        //...
    }
    return res;
}

void Separate::_initBetweenReplications() {
}

std::map<std::string, std::string>* Separate::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Separate::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Separate::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Separate>(), &Separate::LoadInstance);
    // ...
    return info;
}

