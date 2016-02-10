class CStudent
{
public:
            void operator() (string strName, int nAge)
            {
                cout << strName << " : " << nAge << endl;
            }
};

CStudent stu;
function<void (string, int)> f = stu;
f("Mike",  12);
