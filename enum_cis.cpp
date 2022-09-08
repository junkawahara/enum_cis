#include "SAPPOROBDD/ZBDD.h"
#include "SAPPOROBDD/SBDD_helper.h"

// Delete commentout if necessary.
//#include "tdzdd/DdEval.hpp"
#include "tdzdd/DdSpec.hpp"
//#include "tdzdd/DdSpecOp.hpp"
#include "tdzdd/DdStructure.hpp"

// Comment out if your program does not need the following headers.
#include "tdzdd/spec/SizeConstraint.hpp"
#include "tdzdd/eval/ToZBDD.hpp"
#include "tdzdd/spec/SapporoZdd.hpp"
#include "tdzdd/util/Graph.hpp"

#include "ConnectedInducedSubgraphSpec.hpp"
#include "ConvEVDD.hpp"

using namespace tdzdd;
using namespace sbddh;

int main(int argc, char** argv) {

    BDD_Init(1024, 1024 * 1024 * 1024);
    for (int i = 0; i < 100; ++i) {
        BDD_NewVar();
    }

    MessageHandler::showMessages(true);

    Graph graph;
    graph.readEdges(argv[1]);

    std::cerr << "# vertices = " << graph.vertexSize()
              << ", # edges = " << graph.edgeSize() << std::endl;

    // construct CIS DD
    ConnectedInducedSubgraphSpec cis_spec(graph, true);
    DdStructure<2> dd_E = DdStructure<2>(cis_spec);
    dd_E.zddReduce();

    std::cerr << "# E node = " << dd_E.size()
            << ", # E card = " << dd_E.evaluate(ZddCardinality<>()) << std::endl;

    // translate E_DD to EV_DD
    //ZDDEVSpec ev_spec(dd_E, graph);
    //DdStructure<2> dd_EV = DdStructure<2>(ev_spec);
    //dd_EV.zddReduce();

    ConvEVDD::VariableList vlist(graph);
    ZBDD dd_V = ConvEVDD::eToVZdd(dd_E, graph, vlist);

    std::cerr << "# V node = " << dd_V.Size()
              << ", # V card = " << dd_V.Card() << std::endl;

    return 0;
}
