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

void Controllers::initGlobalVariables() {
  if (g_pControllers == nullptr) {
    // WsjcppLog::info(std::string(), "Create employees map");
    g_pControllers = new std::map<std::string, QObject *>();
  }
}

// void Controllers::deinitGlobalVariables() {
//   const std::string TAG = "WsjcppEmployees::deinit";
//   if (g_pWsjcppEmployees != nullptr) {
//     std::map<std::string, WsjcppEmployBase *>::iterator it;
//     for (it = g_pWsjcppEmployees->begin(); it != g_pWsjcppEmployees->end(); ++it) {
//       std::string sEmployName = it->first;
//       WsjcppLog::ok(TAG, sEmployName + " ... UNREGISTERED");
//       delete it->second;
//       it->second = nullptr;
//     }
//     g_pWsjcppEmployees->clear();
//     delete g_pWsjcppEmployees;
//     g_pWsjcppEmployees = nullptr;
//   }

//   if (g_pWsjcppInitEmployees != nullptr) {
//     g_pWsjcppInitEmployees->clear();
//     delete g_pWsjcppInitEmployees;
//     g_pWsjcppInitEmployees = nullptr;
//   }

//   if (g_pWsjcppInitWith != nullptr) {
//     g_pWsjcppInitWith->clear();
//     delete g_pWsjcppInitWith;
//     g_pWsjcppInitWith = nullptr;
//   }
// }

void Controllers::addController(const std::string &sName, QObject *pEmploy) {
  Controllers::initGlobalVariables();
  if (g_pControllers->find(sName) == g_pControllers->end()) {
      std::cout << "Added controller " << sName << std::endl;
      g_pControllers->insert(std::pair<std::string, QObject *>(sName, pEmploy));
  }
}