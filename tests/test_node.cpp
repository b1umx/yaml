#include <catch2/catch_test_macros.hpp>

#include <byaml/detail/node.hpp>


using namespace std;
using namespace byaml;


TEST_CASE( "Test Node::type()", "[node]" ) {
    Node undefinedNode;
    REQUIRE( undefinedNode.type() == "undefined" );
    Node boolNode(false);
    REQUIRE( boolNode.type() == "boolean" );
    Node intNode(2846);
    REQUIRE( intNode.type() == "integer" );
    Node floatNode(3.14);
    REQUIRE( floatNode.type() == "floating point" );
    Node stringNode("test");
    REQUIRE( stringNode.type() == "string" );
    
    vector<Node> seqValue = { false, 3.14 };
    Node seqNode(seqValue);
    REQUIRE( seqNode.type() == "sequence" );

    map<string, Node> mapValue = {{ "address", "Moscow" }, { "building", 1 }};
    Node mapNode(mapValue);
    REQUIRE( mapNode.type() == "mapping" );

    OrderedMap<string, Node> omapValue = {{ "address", "Moscow" }, { "building", 1 }};
    Node omapNode(omapValue);
    REQUIRE( omapNode.type() == "ordered mapping" );
}


TEST_CASE( "Test Node::isUndefined()", "[node]" ) {
    Node undefinedNode;
    REQUIRE( undefinedNode.isUndefined() );
    Node fullNode = 1;
    REQUIRE( !fullNode.isUndefined() );
}

