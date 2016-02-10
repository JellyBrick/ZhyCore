#ifndef DEBUGER_H
#define DEBUGER_H
#include <string>
using namespace std;
class Debuger
{
    public:
        Debuger();
        virtual ~Debuger();
        string BinToHex( std::string &strBin, bool bIsUpper = false);
        string HexToBin( std::string &strHex);
    protected:

    private:
};

#endif // DEBUGER_H
