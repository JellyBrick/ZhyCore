#ifndef DEBUGER_H
#define DEBUGER_H
#include <string>

class Debuger
{
    public:
        Debuger();
        virtual ~Debuger();

  std::string bin2hex(const std::string &strBin);
  protected:

    private:
char strHex[1464];
};

#endif // DEBUGER_H
