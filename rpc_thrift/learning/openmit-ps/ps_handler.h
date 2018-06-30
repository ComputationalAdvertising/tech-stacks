/*!
 *  Copyright (c) 2017 by Contributors
 *  \file ps_handler.h
 *  \brief parameter server handler
 */
#ifndef OPENMIT_PS_PS_HANDLER_H_
#define OPENMIT_PS_PS_HANDLER_H_

#include "Ps.h" 
#include "ps_types.h"

#include <memory>
#include <string>

using namespace openmit::thrift;

namespace openmit {
namespace ps {

class PsHandler : public PsIf {
public:
  PsHandler(std::string& mode);
  
  ~PsHandler();

  void Pull(std::string& rsp, const std::vector<std::string>& names, const std::string& reqs, const std::string& info_type, const int64_t log_id) override;

  void Push(const std::vector<std::string>& names, const std::string& reqs, const std::string& info_type, const int32_t epoch, const int64_t log_id) override; 

  void Create(std::vector<std::string>& rsp, const std::string& name, const std::vector<std::string>& txt_model_defs) override;

  void Drop(const std::string& name) override;

  void Dump(const std::vector<std::string>& names, const std::string& path, const std::string& info_type, const std::string& format, const bool dump_zero) override;

  void DumpAll(const std::string& info_type, const std::string& format, const bool dump_zero) override;

  void Load(const std::string& name, const std::string& path) override;

  void RestoreModels() override;

  void SetStreamingUpdate(const std::vector<std::string>& names, const bool dump_zero) override;

  void GetUpdated(std::vector<std::string>& rsp, const std::vector<std::string>& names) override;

  void Stat(std::vector<std::string>& rsp, const std::vector<std::string>& names) override;

  void ListModels(std::vector<ModelInfo>& rsp) override;

  int32_t NumServer() override;

  void Mode(std::string& rsp) override;

private:
  int tmp = 0;
  std::string mode_;
  //std::shared_ptr<ModelMgr> model_mgr_;  // model manager
};

} // namespace ps 
} // namespace openmit

#endif // OPENMIT_PS_PS_HANDLER_H_
