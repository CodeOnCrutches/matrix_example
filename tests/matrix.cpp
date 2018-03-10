#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"

TEST_CASE("creating matrix")
{
    matrix_t matrix;
    REQUIRE( matrix.rows() == 0 );
    REQUIRE( matrix.collumns() == 0 );
}

TEST_CASE("reading matrix")
{
    std::string input{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t matrix;
    std::istringstream istream{ input };
    
    REQUIRE( matrix.read( istream ) );
    REQUIRE( matrix.rows() == 3 );
    REQUIRE( matrix.collumns() == 3 );
    
    std::ostringstream ostream;
    matrix.write( ostream );
    
    REQUIRE( input == ostream.str() );
}

TEST_CASE("matrix copy")
{
       std::string input{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t matrix;
    std::istringstream istream{ input };
    REQUIRE( matrix.read( istream ) );
    
    matrix_t copy(matrix);
    REQUIRE( copy.rows() == 3 );
    REQUIRE( copy.collumns() == 3 );
}

TEST_CASE("add, [oper+]")
{
    std::string input{
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };
    std::string input_two
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1"
    };
    matrix_t A;
    matrix_t B;
    std::istringstream istream{ input };
    std::istringstream istream_two { input_two };
    REQUIRE( A.read( istream ) );
    REQUIRE( B.read( istream_two ) );

}
