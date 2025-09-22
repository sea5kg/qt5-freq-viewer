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

#include "all_controllers.h"
#include <iostream>

std::map<std::string, QObject *> *g_pControllers = nullptr;
std::map<std::string, std::string> *g_pMangledNames = nullptr;

void Controllers::initGlobalVariables() {
  if (g_pControllers == nullptr) {
    // WsjcppLog::info(std::string(), "Create employees map");
    g_pControllers = new std::map<std::string, QObject *>();
  }
  if (g_pMangledNames == nullptr) {
    g_pMangledNames = new std::map<std::string, std::string>();
  }
}

void Controllers::addController(const std::string &sName, QObject *pEmploy) {
  Controllers::initGlobalVariables();
  if (g_pControllers->find(sName) == g_pControllers->end()) {
      std::cout << "Added controller " << sName << std::endl;
      g_pControllers->insert(std::pair<std::string, QObject *>(sName, pEmploy));
  }
}

void Controllers::addMangledName(const std::string &sMangledName, const std::string &sControllerName) {
  Controllers::initGlobalVariables();
  g_pMangledNames->insert(std::pair<std::string, std::string>(sMangledName, sControllerName));
}