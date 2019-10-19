/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Batch.h
 * Author: rlcancian
 *
 * Created on 03 de Junho de 2019, 15:14
 */

#ifndef BATCH_H
#define BATCH_H

#include "ModelComponent.h"

/*!
 This component ...
 */
class Batch : public ModelComponent {
public: // constructors
    Batch(Model* model);
    Batch(const Batch& orig);
    virtual ~Batch();
public:  // virtual
    virtual std::string show();
public:  // static
    static PluginInformation* GetPluginInformation();
    static ModelComponent* LoadInstance(Model* model, std::map<std::string, std::string>* fields);
    
    void setBatchSize(unsigned int value);
    void setBatchName(std::string value);
    void setPermanentBatch(bool value);
    void setByAttributeBatch(bool value);
    void setAttributeName(std::string value);
    void setRepresentativeEntityTypeName(std::string value);
protected:  // virtual
    virtual void _execute(Entity* entity);
    virtual void _initBetweenReplications();
    virtual bool _loadInstance(std::map<std::string, std::string>* fields);
    virtual std::map<std::string, std::string>* _saveInstance();
    virtual bool _check(std::string* errorMessage);
private: // methods
    void initializeGroupAttribute();
private: // attributes 1:n
    unsigned int _batchSize;
    unsigned int _batchesCount;
    std::string _batchName;
    bool _permanent;
    bool _byAttribute;
    std::string _attributeName;
    std::string _representativeEntityTypeName;
};


#endif /* BATCH_H */

