#pragma once

#include <map>
#include <string>
#include <vector>

/*
 *		控制台命令处理
 */
class CmdlineParser {
public:
  //用main函数的参数来构造(填充m_vec_strCmdblocks
  CmdlineParser(int arg_amount, char *arg_value[]);

  //根据命令单元开始分析处理
  //返回 命令->参数 的映射
  std::map<std::string, std::string> DoProcess();

private:
  //
  static bool __IsCmd(const std::string &str);
  //
  static bool __IsValue(const std::string &str);

private:
  std::vector<std::string> m_vec_strCmdblocks;
};
