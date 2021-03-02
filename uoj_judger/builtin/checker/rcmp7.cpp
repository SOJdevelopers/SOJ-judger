#include "testlib.h"
#include <cmath>

using namespace std;

const double EPS = 1E-7;

int main(int argc, char * argv[])
{
    setName("compare two sequences of doubles, max absolute or relative error = %.8lf", EPS);
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
            quitf(_wa, "%d%s numbers differ - expected: '%.8lf', found: '%.8lf', error = '%.8lf'",
                n, englishEnding(n).c_str(), j, p, doubleDelta(j, p));
        }
    }

    if (n == 1)
        quitf(_ok, "found '%.8lf', expected '%.8lf', error '%.8lf'", p, j, doubleDelta(j, p));

    quitf(_ok, "%d numbers", n);
}
