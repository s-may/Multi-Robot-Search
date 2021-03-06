#ifndef SVG_NEIGHBOR_H
#define SVG_NEIGHBOR_H

#include <iostream>

using namespace std;

/*
	This is an auxiliary class for the svg_label_computer which uses it to list the neighbors
	of a particular vertex when the labels for its edge are computed.
*/

class neighbor
{
public:
    int in;
    int out;
    int w;
    int lambda_noncon;  //stores the non-contiguous label of the edge
    int lambda_hybrid;  //stores the hybrid label of the edge
    int lambda_hybrid_true;
    int rho_hybrid;         	//diff between
    int rho_noncon;         	//diff between
    int rho_hybrid_true;
    void print();
private:
};

bool neighbor_comparison_noncon (const neighbor& a,const neighbor& b)  //WE ARE INVERTING THIS< BAD STYLE > s.t. sort sorts DESC
{
    return (a.rho_noncon > b.rho_noncon);
}

bool neighbor_comparison_hybrid (const neighbor& a,const neighbor& b)  //WE ARE INVERTING THIS< BAD STYLE > s.t. sort sorts DESC
{
    return (a.rho_hybrid > b.rho_hybrid);
}

bool neighbor_comparison_hybrid_true (const neighbor& a,const neighbor& b)  //WE ARE INVERTING THIS< BAD STYLE > s.t. sort sorts DESC
{
    return (a.rho_hybrid_true > b.rho_hybrid_true);
}


void neighbor::print()
{
    cout << "|| Neigh. w: " << w << " rho: " << rho_hybrid << "|" << rho_noncon << " lambda (h|nc): " << lambda_hybrid << "|" << lambda_noncon << " V_2? " << is_in_V_2 << endl;
}

#endif
