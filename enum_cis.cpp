#include "SAPPOROBDD/ZBDD.h"
#include "SAPPOROBDD/SBDD_helper.h"

#include "tdzdd/DdSpec.hpp"
#include "tdzdd/DdStructure.hpp"

#include "tdzdd/spec/SizeConstraint.hpp"
#include "tdzdd/eval/ToZBDD.hpp"
#include "tdzdd/spec/SapporoZdd.hpp"
#include "tdzdd/util/Graph.hpp"

#include "ConnectedInducedSubgraphSpec.hpp"
#include "ConvEVDD.hpp"
#include "testCIS.hpp"

using namespace tdzdd;
using namespace sbddh;

int main(int argc, char** argv) {

    if (argc == 1) {
        testCIS(); // run test code
        std::cout << "test passed!" << std::endl;
    } else {
        // Show messages when ZDD construction by TdZdd is running
        MessageHandler::showMessages(true);

        // construct a graph by reading the input file
        Graph graph;
        graph.readEdges(argv[1]);

        std::cerr << "# vertices = " << graph.vertexSize()
                << ", # edges = " << graph.edgeSize() << std::endl;

        // initialize SAPPOROBDD library
        BDD_Init(1024, 1024 * 1024 * 1024);
        for (int i = 0; i < graph.vertexSize() + graph.edgeSize(); ++i) {
            BDD_NewVar();
        }

        // construct CIS DD
        ConnectedInducedSubgraphSpec cis_spec(graph, true);
        DdStructure<2> dd_E = DdStructure<2>(cis_spec);
        dd_E.zddReduce();

        std::cerr << "# E ZDD node = " << dd_E.size()
                << ", # E ZDD card = " << dd_E.evaluate(ZddCardinality<>()) << std::endl;

        // translate E-DD to V-DD
        ConvEVDD::VariableList vlist(graph);
        ZBDD dd_V = ConvEVDD::eToVZdd(dd_E, graph, vlist);

        std::cerr << "# V ZDD node = " << dd_V.Size()
                << ", # V ZDD card = " << dd_V.Card() << std::endl;
    }
    return 0;
}
