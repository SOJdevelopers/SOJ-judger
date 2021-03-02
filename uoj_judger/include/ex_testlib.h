#ifndef _TESTLIB_H_
#include "testlib.h"
#endif

#ifndef _EX_TESTLIB_H
#define _EX_TESTLIB_H
int __testlib_ancestor(int x, std::vector <int> &p) {return p[x] == x ? x : (p[x] = __testlib_ancestor(p[x], p));}

std::set < std::pair <int, int> > readTree(InStream &in, int vertex, int weight_min = -1, int weight_max = -1) {
	int i, u, v;
	std::set < std::pair <int, int> > E;
	if (weight_min > weight_max)
		__testlib_fail("readTree(const Istream &in, int vertex, int weight_min, int weight_max): weight_min must be less than or equal to weight_max");
	std::vector <int> p;
	for (i = 0; i <= vertex; ++i) p.push_back(i);
	for (i = 1; i < vertex; ++i) {
		u = in.readInt(1, vertex, "u[" + vtos(i) + "]"); if (in.strict) in.readSpace();
		v = in.readInt(1, vertex, "v[" + vtos(i) + "]");
		if (__testlib_ancestor(u, p) == __testlib_ancestor(v, p))
			in.quitf(_wa, "Tree can't contain cycles. [Edge #%d: (%d, %d)]", i, u, v);
		if (~weight_min && ~weight_max) {
			if (in.strict) in.readSpace();
			in.readInt(weight_min, weight_max, "w[" + vtos(i) + "]");
		}
		p[p[u]] = p[v];
		E.insert(std::pair <int, int> (u, v));
		E.insert(std::pair <int, int> (v, u));
		if (in.strict) in.readEoln();
	}
}

std::set < std::pair <int, int> > readGraph(InStream &in, int vertex, int edge, int weight_min = -1, int weight_max = -1) {
	int i, u, v;
	if (weight_min > weight_max)
		__testlib_fail("readGraph(const Istream &in, int vertex, int edge, int weight_min, int weight_max): weight_min must be less than or equal to weight_max");
	std::set < std::pair <int, int> > E;
	for (i = 1; i <= edge; ++i) {
		u = in.readInt(1, vertex, "u[" + vtos(i) + "]"); if (in.strict) in.readSpace();
		v = in.readInt(1, vertex, "v[" + vtos(i) + "]");
		if (u == v)
			in.quitf(_wa, "Graph can't contain loops. [Edge #%d: (%d, %d)]", i, u, v);
		if (E.find(std::pair <int, int> (u, v)) != E.end())
			in.quitf(_wa, "Graph can't contain multiple edges. [Edge #%d: (%d, %d)]", i, u, v);
		E.insert(std::pair <int, int> (u, v));
		E.insert(std::pair <int, int> (v, u));
		if (~weight_min && ~weight_max) {
			if (in.strict) in.readSpace();
			in.readInt(weight_min, weight_max, "w[" + vtos(i) + "]");
		}
		if (in.strict) in.readEoln();
	}
	return E;
}
#endif
