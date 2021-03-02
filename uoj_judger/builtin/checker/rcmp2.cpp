#include "testlib.h"
#include <cmath>

using namespace std;

const double EPS = 1E-2;

int main(int argc, char * argv[])
{
    setName("compare two sequences of doubles, max absolute or relative error = %.3lf", EPS);
    registerTestlibCmd(argc, argv);

    int n = 0;
    double j, p;

    while (!ans.seekEof()) 
    {
        n++;
        j = ans.readDouble();
        p = ouf.readDouble();
        if (!doubleCompare(j, p, EPS))
        {
            quitf(_wa, "%d%s numbers differ - expected: '%.3lf', found: '%.3lf', error = '%.3lf'",
                n, englishEnding(n).c_str(), j, p, doubleDelta(j, p));
        }
    }

    if (n == 1)
        quitf(_ok, "found '%.3lf', expected '%.3lf', error '%.3lf'", p, j, doubleDelta(j, p));
    
    quitf(_ok, "%d numbers", n);
}
