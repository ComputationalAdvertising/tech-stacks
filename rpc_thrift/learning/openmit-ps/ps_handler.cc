/*!
 *  Copyright (c) 2017 by Contributors
 *  \file ps_handler.cc
 *  \brief parameter server handler
 */
#include "ps_handler.h" 

#include <iostream>

namespace openmit {
namespace ps {

  PsHandler::PsHandler(std::string& mode): mode_(mode) { 
  std::cout << "PsHandler::PsHandler ..." << std::endl; 
}
  
PsHandler::~PsHandler() {
  std::cout << "PsHandler::~PsHandler ..." << std::endl; 
}

void PsHandler::Pull(std::string& rsp, const std::vector<std::string>& names, const std::string& reqs, const std::string& info_type, const int64_t log_id) {
  std::cout << "PsHandler::Pull ..." << std::endl;
}

void PsHandler::Push(const std::vector<std::string>& names, const std::string& reqs, const std::string& info_type, const int32_t epoch, const int64_t log_id) {
  std::cout << "PsHandler::Push ..." << std::endl;
}

void PsHandler::Create(std::vector<std::string>& rsp, const std::string& name, const std::vector<std::string>& txt_model_defs) {
  std::cout << "PsHandler::Create ..." << std::endl;
}

void PsHandler::Drop(const std::string& name) {
  std::cout << "PsHandler::Drop ..." << std::endl;
}

void PsHandler::Dump(const std::vector<std::string>& names, const std::string& path, const std::string& info_type, const std::string& format, const bool dump_zero) {
  std::cout << "PsHandler::Dump ..." << std::endl;
}

void PsHandler::DumpAll(const std::string& info_type, const std::string& format, const bool dump_zero) {
  std::cout << "PsHandler::DumpAll..." << std::endl;
}

void PsHandler::Load(const std::string& name, const std::string& path) {
  std::cout << "PsHandler::Load ..." << std::endl;
}

void PsHandler::RestoreModels() {  
  std::cout << "PsHandler::RestoreModels ..." << std::endl;
}

void PsHandler::SetStreamingUpdate(const std::vector<std::string>& names, const bool dump_zero) {
  std::cout << "PsHandler::SetStreamingUpdate ..." << std::endl;
}

void PsHandler::GetUpdated(std::vector<std::string>& rsp, const std::vector<std::string>& names) {  
  std::cout << "PsHandler::GetUpdated ..." << std::endl;
}

void PsHandler::Stat(std::vector<std::string>& rsp, const std::vector<std::string>& names) {
  std::cout << "PsHandler::Stat ..." << std::endl;
}

void PsHandler::ListModels(std::vector<ModelInfo>& rsp) {
  std::cout << "PsHandler::ListModels ..." << std::endl;
}

int32_t PsHandler::NumServer() {
  std::cout << "PsHandler::NumServer ..." << std::endl;
  return 10;
}

void PsHandler::Mode(std::string& rsp) {
  rsp = mode_;
  std::cout << "PsHandler::Mode ..." << std::endl;
}

} // namespace ps 
} // namespace openmit
