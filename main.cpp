#include			<iostream>

#include			"OptionManager.hpp"

int				main(void)
{
  Manager::OptionManager	&m = Manager::OptionManager::getInstance();;
  std::string			t;

  m.add<std::string>("toto", "toto");

  std::cout << m.get<std::string>("toto", t) << std::endl;
  std::cout << m.get<std::string>("toto")->get() << std::endl;
  return (0);
}
