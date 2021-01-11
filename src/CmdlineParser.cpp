#include "CmdlineParser.h"

CmdlineParser::CmdlineParser(int arg_amount, char *arg_value[]) {
  //填充
  for (int index = 0; index != arg_amount; index++) {
    m_vec_strCmdblocks.push_back(arg_value[index]);
  }
}

std::map<std::string, std::string> CmdlineParser::DoProcess() {
  std::map<std::string, std::string> cmd_map;

  std::string cmd;
  std::string val;
  for (int index = 0; index <= m_vec_strCmdblocks.size();
       /*在循环内部控制 index */) {
    cmd.clear();
    val.clear();

    if (__IsCmd(m_vec_strCmdblocks[index])) {
      index++;
      if (index == m_vec_strCmdblocks.size()) {
        //末尾了，没参数的命令
        cmd_map.insert({m_vec_strCmdblocks[index - 1], ""});
        break;
      }

      if (__IsValue(m_vec_strCmdblocks[index])) {
        //有参数的命令
        cmd_map.insert(
            {m_vec_strCmdblocks[index - 1], m_vec_strCmdblocks[index]});
        index++;
      } else {
        //没参数的命令
        cmd_map.insert({m_vec_strCmdblocks[index - 1], ""});
      }
    } else {
      //孤立参数
      cmd_map.insert(
          {std::to_string(cmd_map.size()), m_vec_strCmdblocks[index]});
      index++;
    }
  }

  return cmd_map;
}

bool CmdlineParser::__IsCmd(const std::string &str) {
  //短命令
  if (str[0] == '-') {
    if (str.size() > 1 && isalpha(str[1])) {
      return true;
    }
  }

  //长命令
  if (str.size() > 2 && (str.find("--", 0) != str.npos)) {
    if (isalpha(str[2])) {
      return true;
    }
  }

  return false;
}

bool CmdlineParser::__IsValue(const std::string &str) {
  //如果第一个是横杠，那么后面一定是数字
  if (str[0] == '-') {
    if (str.size() < 2) {
      return false;
    }

    if (isalnum(str[1]) && !isalpha(str[1])) {
      return true;
    } else {
      return false;
    }
  } else {
    //如果第一个不是横杠那么肯定是参数
    return true;
  }
}