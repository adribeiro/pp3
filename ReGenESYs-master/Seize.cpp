/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Seize.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 21 de Agosto de 2018, 16:17
 */

#include "Seize.h"
#include "Resource.h"
#include "Attribute.h"
#include <string>

Seize::Seize(Model* model) : ModelComponent(model, Util::TypeOf<Seize>()) {
}

Seize::Seize(const Seize& orig) : ModelComponent(orig) {
}

std::string Seize::show() {
    return ModelComponent::show() +
	    ",resourceType=" + std::to_string(static_cast<int> (this->_resourceType)) +
	    ",resource=\"" + this->_resource->getName() + "\"" +
	    ",quantity=" + this->_quantity;
}

void Seize::setLastMemberSeized(unsigned int _lastMemberSeized) {
    this->_lastMemberSeized = _lastMemberSeized;
}

unsigned int Seize::getLastMemberSeized() const {
    return _lastMemberSeized;
}

void Seize::setSaveAttribute(std::string _saveAttribute) {
    this->_saveAttribute = _saveAttribute;
}

std::string Seize::getSaveAttribute() const {
    return _saveAttribute;
}

void Seize::setRule(Resource::ResourceRule _rule) {
    this->_rule = _rule;
}

Resource::ResourceRule Seize::getRule() const {
    return _rule;
}

void Seize::setQuantity(std::string _quantity) {
    this->_quantity = _quantity;
}

std::string Seize::getQuantity() const {
    return _quantity;
}

void Seize::setResourceType(Resource::ResourceType _resourceType) {
    this->_resourceType = _resourceType;
}

Resource::ResourceType Seize::getResourceType() const {
    return _resourceType;
}

void Seize::setPriority(unsigned short _priority) {
    this->_priority = _priority;
}

unsigned short Seize::getPriority() const {
    return _priority;
}

void Seize::setAllocationType(unsigned int _allocationType) {
    this->_allocationType = _allocationType;
}

unsigned int Seize::getAllocationType() const {
    return _allocationType;
}

void Seize::setQueueName(std::string queueName) throw () {
    Queue* queue = dynamic_cast<Queue*> (_model->getElementManager()->getElement(Util::TypeOf<Queue>(), queueName));
    if (queue != nullptr) {
	_queue = queue;
    } else {
	throw std::invalid_argument("Queue does not exist");
    }
}

void Seize::_handlerForResourceEvent(Resource* resource) {
    Queue* queue = nullptr;
    
    if(this->_resourceType == Resource::ResourceType::SET){
        if(_rule == Resource::ResourceRule::RANDOM){
            _model->getTraceManager()->trace(Util::TraceLevel::blockInternal ,"Queue RANDOM");
            queue = this->_queue;
        }else if(_rule == Resource::ResourceRule::ESPECIFIC){
            List<ModelElement*>* resources = _set->getElementSet();
            bool cond = true;
            int i = 0;
            while(cond && i< resources->size()){
                if(resource->getId() == resources->getAtRank(i)->getId()){
                    _lastMemberSeized = i;
                    cond = false;
                }
                i++;
            }
            queue = this->_queues->getAtRank(_lastMemberSeized);
        }
    }else{
        queue = this->_queue;
    }
    
    Waiting* first = queue->first();
    if (first != nullptr) { // there are entities waiting in the queue
	unsigned int quantity = _model->parseExpression(this->_quantity);
	if ((resource->getCapacity() - resource->getNumberBusy()) >= quantity) { //enought quantity to seize
	    if(this->_resourceType == Resource::ResourceType::SET &&_rule == Resource::ResourceRule::RANDOM){
                first->getEntity()->setAttributeValue(this->_saveAttribute, _lastMemberSeized);
            }
            double tnow = _model->getSimulation()->getSimulatedTime();
	    resource->seize(quantity, tnow);
	    _model->getEvents()->insert(new Event(tnow, first->getEntity(), this->getNextComponents()->frontConnection()));
	    queue->removeElement(first);
	    _model->getTraceManager()->traceSimulation(Util::TraceLevel::blockInternal, tnow, first->getEntity(), this, "Waiting entity " + std::to_string(first->getEntity()->getEntityNumber()) + " now seizes " + std::to_string(quantity) + " elements of resource \"" + resource->getName() + "\"");
            
	}
    }
}

void Seize::setResourceName(std::string resourceName) throw () {
    Resource* resource = dynamic_cast<Resource*> (_model->getElementManager()->getElement(Util::TypeOf<Resource>(), resourceName));
    if (resource != nullptr) {
	_resource = resource;
    } else {
	throw std::invalid_argument("Resource does not exist");
    }
}

std::string Seize::getResourceName() const {
    return _resource->getName();
}

std::string Seize::getQueueName() const {
    return _queue->getName();
}

void Seize::setResource(Resource* resource) {
    this->_resource = resource;
    _resource->addResourceEventHandler(Resource::SetResourceEventHandler<Seize>(&Seize::_handlerForResourceEvent, this));
}

Resource* Seize::getResource() const {
    return _resource;
}

void Seize::setSet(Set* set){
    Resource* resource = nullptr;
    if(set->getSetOfType() == Util::TypeOf<Resource>()){
        this->_resourceType = Resource::ResourceType::SET;
        this->_set= set;
        List<ModelElement*>* resources = _set->getElementSet();
        for(int i = 0; i< resources->size();i++){
            resource = (Resource *) resources->getAtRank(i);
            resource->addResourceEventHandler(Resource::SetResourceEventHandler<Seize>(&Seize::_handlerForResourceEvent, this));
            _model->getTraceManager()->trace(Util::TraceLevel::blockInternal ,"Set added");
        }
    }else{
        _model->getTraceManager()->trace(Util::TraceLevel::blockInternal ,"Not a Set to add");
    }
}
void Seize::insertQueue(Queue* queue){
    _queues->insert(queue);
    
}

void Seize::setQueue(Queue* queue) {
    this->_queue = queue;
}

Queue* Seize::getQueue() const {
    return _queue;
}

Seize::~Seize() {
}

void Seize::_execute(Entity* entity) {
    /* TODO +: not implemented yet */
    Resource* resource = nullptr;
    Queue* queue = nullptr;
    TraceManager* traceManager = this->_model->getTraceManager();
    if (this->_resourceType == Resource::ResourceType::SET) {
        traceManager->trace(Util::TraceLevel::blockInternal, "Identificou que e um set");
	List<ModelElement*>* resources = _set->getElementSet();
        if(_rule == Resource::ResourceRule::RANDOM){
            traceManager->trace(Util::TraceLevel::blockInternal, "Identificou que a rule e RANDOM");
            unsigned int quant = _model->parseExpression(this->_quantity);
            bool cond = true;
            queue = this->_queue;
            int i = 0;
            while(cond && i < resources->size()){
                resource = (Resource *)resources->getAtRank(i);
                if(resource->getCapacity() - resource->getNumberBusy() > quant){
                    cond = false;
                    _lastMemberSeized = i;
                }
                i++;
            }
            resource = (Resource *)resources->getAtRank(_lastMemberSeized);
            
        }else if(_rule == Resource::ResourceRule::ESPECIFIC){
            traceManager->trace(Util::TraceLevel::blockInternal, "Identificou que a rule e ESPECIFIC");
            unsigned int especificNumber = entity->getAttributeValue(this->_saveAttribute);
            if(especificNumber < resources->size()){
                traceManager->trace(Util::TraceLevel::blockInternal, std::to_string(especificNumber));
                resource = resources->getAtRank(especificNumber);
                queue = _queues->getAtRank(especificNumber);
            }
        }
    } else {
	resource = this->_resource;
        queue = this->_queue;
    }
    
    unsigned int quantity = _model->parseExpression(this->_quantity);
    if (resource->getCapacity() - resource->getNumberBusy() < quantity) { // not enought free quantity to allocate. Entity goes to the queue
	traceManager->trace(Util::TraceLevel::blockInternal, "not enought free quantity to allocate. Entity goes to the queue");
        WaitingResource* waitingRec = new WaitingResource(entity, this, _model->getSimulation()->getSimulatedTime(), quantity);
	queue->insertElement(waitingRec); // ->getList()->insert(waitingRec);
	_model->getTraceManager()->traceSimulation(Util::TraceLevel::blockInternal, _model->getSimulation()->getSimulatedTime(), entity, this, "Entity starts to wait for resource in queue \"" + queue->getName() + "\" with " + std::to_string(queue->size()) + " elements");

    } else { // alocate the resource
        traceManager->trace(Util::TraceLevel::blockInternal, "alocate the resource");
	_model->getTraceManager()->traceSimulation(Util::TraceLevel::blockInternal, _model->getSimulation()->getSimulatedTime(), entity, this, "Entity seizes " + std::to_string(quantity) + " elements of resource \"" + resource->getName() + "\" (capacity:"+std::to_string(resource->getCapacity()) +", numberbusy:"+std::to_string(resource->getNumberBusy())+")");
	resource->seize(quantity, _model->getSimulation()->getSimulatedTime());
	if(this->_resourceType == Resource::ResourceType::SET &&_rule == Resource::ResourceRule::RANDOM){
            traceManager->trace(Util::TraceLevel::blockInternal, "Salvando attribute");
            entity->setAttributeValue(this->_saveAttribute, this->_lastMemberSeized);  
        }
        _model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
        

    }
}

void Seize::_initBetweenReplications() {
    this->_lastMemberSeized = 0;
    
    if (this->_resourceType == Resource::ResourceType::SET) {
        Resource* resource = nullptr;
        List<ModelElement*>* resources = _set->getElementSet();
        for(int i = 0; i< resources->size();i++ ){
                resource = (Resource *)resources->getAtRank(i);
                resource->initBetweenReplications();
        }
        if(_rule == Resource::ResourceRule::RANDOM){
            this->_queue->initBetweenReplications();
        }else if(_rule == Resource::ResourceRule::ESPECIFIC){
            for(int i = 0; i< _queues->size();i++ ){
                _queues->getAtRank(i)->initBetweenReplications();
            }
        }
    } else {
	this->_queue->initBetweenReplications();
        this->_resource->initBetweenReplications();
    }
}

bool Seize::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	this->_allocationType = std::stoi((*(fields->find("allocationType"))).second);
	this->_priority = std::stoi((*(fields->find("priority"))).second);
	this->_quantity = ((*(fields->find("quantity"))).second);
	this->_resourceType = static_cast<Resource::ResourceType> (std::stoi((*(fields->find("resourceType"))).second));
	this->_rule = static_cast<Resource::ResourceRule> (std::stoi((*(fields->find("rule"))).second));
	this->_saveAttribute = ((*(fields->find("saveAttribute"))).second);
	//Util::identitifcation queueId = std::stoi((*(fields->find("queueId"))).second);
	//Queue* queue = dynamic_cast<Queue*> (_model->getElementManager()->getElement(Util::TypeOf<Queue>(), queueId));
	std::string queueName = ((*(fields->find("queueName"))).second);
	Queue* queue = dynamic_cast<Queue*> (_model->getElementManager()->getElement(Util::TypeOf<Queue>(), queueName));
	this->_queue = queue;
	//Util::identitifcation resourceId = std::stoi((*(fields->find("resourceId"))).second);
	//Resource* resource = dynamic_cast<Resource*> (_model->getElementManager()->getElement(Util::TypeOf<Resource>(), resourceId));
	std::string resourceName = ((*(fields->find("resourceName"))).second);
	Resource* resource = dynamic_cast<Resource*> (_model->getElementManager()->getElement(Util::TypeOf<Resource>(), resourceName));
	this->_resource = resource;
	_resource->addResourceEventHandler(Resource::SetResourceEventHandler<Seize>(&Seize::_handlerForResourceEvent, this));

    }
    return res;
}

std::map<std::string, std::string>* Seize::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance(); //Util::TypeOf<Seize>());
    fields->emplace("allocationType", std::to_string(this->_allocationType));
    fields->emplace("priority=", std::to_string(this->_priority));
    fields->emplace("quantity", this->_quantity);
    
    if (this->_resourceType == Resource::ResourceType::SET) {
	
    } else {
	fields->emplace("queueId", std::to_string(this->_queue->getId()));
        fields->emplace("queueName", (this->_queue->getName()));
        fields->emplace("resourceId", std::to_string(this->_resource->getId()));
        fields->emplace("resourceName", (this->_resource->getName()));
    }
    fields->emplace("resourceType", std::to_string(static_cast<int> (this->_resourceType)));  
    fields->emplace("rule", std::to_string(static_cast<int> (this->_rule)));
    fields->emplace("saveAttribute", this->_saveAttribute);
    return fields;
}

bool Seize::_check(std::string* errorMessage) {
    bool resultAll = true;
    resultAll &= _model->checkExpression(_quantity, "quantity", errorMessage);
    if (this->_resourceType == Resource::ResourceType::SET) {
        resultAll &= _model->getElementManager()->check(Util::TypeOf<Set>(), _set, "Set", errorMessage);
        if(_rule == Resource::ResourceRule::RANDOM){
            resultAll &= _model->getElementManager()->check(Util::TypeOf<Queue>(), _queue, "Queue", errorMessage);
        }else if(_rule == Resource::ResourceRule::ESPECIFIC){
            resultAll &= _model->getElementManager()->check(Util::TypeOf<Queue>(), _queues->getAtRank(0), "Queue", errorMessage);
        }
    } else {
        resultAll &= _model->getElementManager()->check(Util::TypeOf<Resource>(), _resource, "Resource", errorMessage);
        resultAll &= _model->getElementManager()->check(Util::TypeOf<Queue>(), _queue, "Queue", errorMessage);
    }
    
    resultAll &= _model->getElementManager()->check(Util::TypeOf<Attribute>(), _saveAttribute, "SaveAttribute", false, errorMessage);
    return resultAll;
}

PluginInformation* Seize::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<Seize>(), &Seize::LoadInstance);
    info->insertDynamicLibFileDependence("queue.so");
    info->insertDynamicLibFileDependence("resource.so");
    return info;
}

ModelComponent* Seize::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Seize* newComponent = new Seize(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;

}

