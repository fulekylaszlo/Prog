class Madar
    {
    public:
    virtual void repul() {};
    };

class Program
    {
    public:
    void fgv ( Madar &madar )
        {
        madar.repul();
        }
    };

class Sas : public Madar
{};

class Pingvin : public Madar
{};

int main ( int argc, char **argv )
    {
    Program program;
    Madar madar;
    program.fgv ( madar );

    Sas sas;
    program.fgv ( sas );

    Pingvin pingvin;
    program.fgv ( pingvin );
    }
