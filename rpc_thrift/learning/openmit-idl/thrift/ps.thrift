namespace cpp   openmit.thrift
namespace py    openmit.thrift
namespace java  openmit.thrift

# Define service for commincation between ps and worker
struct ModelInfo {
  1: string model_name,
  2: string group_name,
  3: i64 model_index,
}

service Ps
{
  # Key op 
  binary Pull(1:list<string> names, 2:binary reqs, 3:string info_type, 4:i64 log_id),
  oneway void Push(1:list<string> names, 2:binary reqs, 3:string info_type, 4:i32 epoch=0, 5:i64 log_id),
  
  # Model op in ps side. format: PB/TXT, info_type: WEIGHT/PARAM/GRAD
  list<string> Create(1:string name, 2:list<string> txt_model_defs), 
  void Drop(1:string name),
  void Dump(1:list<string> names, 2:string path, 3:string info_type='WEIGHT', 4:string format='PB', 5:bool dump_zero=false),
  void DumpAll(1:string info_type='WEIGHT', 2:string format='PB', 3:bool dump_zero=false),
  void Load(1:string name, 2:string path),
  void RestoreModels(),
  void SetStreamingUpdate(1:list<string> names, 2:bool streaming_update),
  list<binary> GetUpdated(1:list<string> names),
  list<string> Stat(1:list<string> names),
  list<ModelInfo> ListModels(),

  # Number of ps node
  i32 NumServer(),

  # Mode: offline | online | nearline
  string Mode();
}
