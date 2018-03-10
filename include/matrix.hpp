#include <iostream>

class matrix_t {
private:
	float ** elements_;
	std::size_t rows_;
	std::size_t collumns_;
public:
	matrix_t();
	matrix_t( matrix_t const & other );
	matrix_t & operator =( matrix_t const & other );
	~matrix_t();

	std::size_t rows() const;
	std::size_t collumns() const;

	bool operator==(const matrix_t&)const;
	matrix_t operator +( matrix_t const & other ) const;
	matrix_t operator -( matrix_t const & other ) const;
	matrix_t operator *( matrix_t const & other ) const;

	matrix_t & operator -=( matrix_t const & other );
	matrix_t & operator +=( matrix_t const & other );
	matrix_t & operator *=( matrix_t const & other );

	std::istream & read( std::istream & stream );
	std::ostream & write( std::ostream  & stream ) const;
};
