#ifndef GENERAL_FACTORY_H_
#define GENERAL_FACTORY_H_ 

#include <iostream>
#include <memory>
#include <unordered_map>

template<typename BaseClass>
class GeneralClassFactory {
public:
  virtual std::shared_ptr<BaseClass> CreateObj() = 0;
};

template<typename BaseClass>
class GeneralFactory {
public:
  static GeneralFactory& Instance() {
    static GeneralFactory general_factory;
    return general_factory;
  }

  virtual std::shared_ptr<BaseClass> CreateObj(const std::string& class_name) {
    if (class_map_.find(class_name) == class_map_.end()) {
      std::cout << "GeneralFactory return nullptr" << std::endl;
      return nullptr;
    }
    return class_map_[class_name]->CreateObj();
  }

  virtual void RegisterClass(const std::string& class_name, GeneralClassFactory<BaseClass>* factory) {
    if (class_map_.find(class_name) != class_map_.end()) {
      std::cout << "Error: class_name has already registered. class_name: " << class_name << std::endl;
      return;
    }
    class_map_[class_name] = factory;
  }

private:
  GeneralFactory() {}
  GeneralFactory(const GeneralFactory<BaseClass>&);
  GeneralFactory* operator=(const GeneralFactory<BaseClass>&);

private:
  std::unordered_map<std::string, GeneralClassFactory<BaseClass>* > class_map_;
}; // GeneralFactory

template<typename SubClass, typename BaseClass> 
class GeneralClassFactoryImpl: public GeneralClassFactory<BaseClass> {
public:
  virtual std::shared_ptr<BaseClass> CreateObj() {
    return std::make_shared<SubClass>();
  }
}; // GeneralClassFactoryImpl

template<typename BaseClass>
class GeneralClassRegister {
public:
  GeneralClassRegister(const std::string& class_name, GeneralClassFactory<BaseClass>* general_class_factory, GeneralFactory<BaseClass>& general_factory) {
    general_factory.RegisterClass(class_name, general_class_factory);
  }
}; // class GeneralClassRegister

#define REGISTER_CLASS(class_name, base_class) \
    static GeneralClassFactoryImpl<class_name, base_class> general_class##_general_factory;\
    static GeneralClassRegister<base_class> general_class##general_register(#class_name, &general_class##_general_factory, GeneralFactory<base_class>::Instance());

#endif // GENERAL_FACTORY_H_ 
