/*
MIT License

Copyright (c) 2025 Evgenii Sopov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <map>
#include <iostream>
#include <QObject>

#define CLASSNAME_QUOTE(x) #x

extern std::map<std::string, QObject *> *g_pControllers;
extern std::map<std::string, std::string> *g_pMangledNames;

class Controllers {
public:
  static void initGlobalVariables();
  // static void deinitGlobalVariables();
  static void addController(const std::string &sName, QObject *pController);
  static void addMangledName(const std::string &sMangledName, const std::string &sControllerName);
};

// findController

template <class T> T *findController() {
  Controllers::initGlobalVariables();
  std::string sMangledName = typeid(T).name();
  std::string sNameController = g_pMangledNames->at(sMangledName);

  // T::name();
  QObject *pController = nullptr;
  if (g_pControllers->count(sNameController)) {
    pController = g_pControllers->at(sNameController);
  }
  if (!pController) {
    std::cerr << "Not found controller: " << sNameController << std::endl;
    return nullptr;
  }
  T *pTController = dynamic_cast<T *>(pController);
  if (!pTController) {
    std::cerr << "Controller could not cast to T [" << sNameController << "]" << std::endl;
    return nullptr;
  }
  return pTController;
};

// registrar

template <typename T>
class RegistrarController {
private:
    T *controller;
public:
  RegistrarController(const std::string &sName) {
    // m_sName = sName;
    controller = new T();
    Controllers::addController(sName, controller);
    std::string sMangledName = typeid(T).name();
    Controllers::addMangledName(sMangledName, sName);
  };
  ~RegistrarController() {
    delete controller;
  }
};

// REGISTRY_SINGLE_CONTROLLER
#define REGISTRY_SINGLE_CONTROLLER(classname) \
    static RegistrarController<classname> g_pController##classname(CLASSNAME_QUOTE(classname));
