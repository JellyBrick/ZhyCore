#ifndef DEBUGER_H
#define DEBUGER_H


class Debuger
{
    public:
        Debuger();
        virtual ~Debuger();
   char* bin2hex(char *chs,int chlen);

    protected:

    private:
char strHex[1464];
};

#endif // DEBUGER_H
