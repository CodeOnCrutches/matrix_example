#include "matrix.hpp"

matrix_t::matrix_t() : elements_{ nullptr }, rows_{ 0 }, collumns_{ 0 }
{
}

matrix_t::matrix_t(matrix_t const & other)
{
	rows_ = other.rows_;
	collumns_ = other.collumns_;

	elements_ = new float * [rows_];
	for (size_t i = 0; i < rows_; i++)
	{
		elements_[i] = new float[collumns_];
		for (size_t j = 0; j < collumns_; j++)
		{
			elements_[i][j] = other.elements_[i][j];
		}
	}
}

matrix_t & matrix_t::operator=(matrix_t const & other)
{
	if (this != &other) 
	{	
		for (size_t i = 0; i < collumns_; i++)
		{
			delete[]elements_[i];
		}
		delete[]elements_;

		rows_ = other.rows_;
		collumns_ = other.collumns_;

		elements_ = new float *[rows_];
		for (size_t i = 0; i < rows_; i++)
		{
			elements_[i] = new float[collumns_];
			for (size_t j = 0; j < collumns_; i++)
			{
				elements_[i][j] = other.elements_[i][j];
			}
		}
	}

	return *this;
}

bool matrix_t::operator==(matrix_t const & other) const
{
	if (rows_ != other.rows_ || collumns_ != other.collumns_)
	{
		return false;
	}

	for (size_t i = 0; i < rows_; i++)
	{
		for (size_t j = 0; j < collumns_; j++)
		{
			if (elements_[i][j] != other.elements_[i][j])
				return false;
		}
	}

	return true;
}

matrix_t::~matrix_t()
{
	for (size_t i = 0; i < rows_; i++)
	{
		delete[]elements_[i];
	}

	delete[]elements_;
}

std::size_t matrix_t::rows() const
{
	return rows_;
}

std::size_t matrix_t::collumns() const
{
	return collumns_;
}

matrix_t matrix_t::operator +(matrix_t const & other) const
{
	
	//assert(rows_ == other.rows_ && collumns_ == other.collumns_);

	matrix_t result;

	result.elements_ = new float *[other.rows_];
	for (size_t i = 0; i < other.rows_; i++)
	{
		result.elements_[i] = new float[other.collumns_];
	}

	for (size_t i = 0; i < other.rows_; i++)
	{
		for (size_t j = 0; j < other.collumns_; j++)
		{
			result.elements_[i][j] = elements_[i][j] + other.elements_[i][j];
		}
	}

	result.rows_ = rows_;
	result.collumns_ = collumns_;

	return result;
}

matrix_t matrix_t::operator - (matrix_t const & other) const
{
	matrix_t result;

	result.elements_ = new float *[other.rows_];
	for (size_t i = 0; i < other.rows_; i++)
	{
		result.elements_[i] = new float[other.collumns_];
	}

	for (size_t i = 0; i < other.rows_; i++)
	{
		for (size_t j = 0; j < other.collumns_; j++)
		{
			result.elements_[i][j] = elements_[i][j] - other.elements_[i][j];
		}
	}

	result.rows_ = other.rows_;
	result.collumns_ = other.collumns_;


	return result;
}

matrix_t matrix_t::operator *(matrix_t const & other) const
{
	matrix_t result;

	result.elements_ = new float *[rows_];
	for (size_t i = 0; i < rows_; i++)
	{
		result.elements_[i] = new float[other.collumns_];
	}

	for (size_t i = 0; i < rows_; i++)
	{
		for (size_t j = 0; j < other.collumns_; j++)
		{
			result.elements_[i][j] = 0;
			for (size_t k = 0; k < collumns_; k++)
			{
				result.elements_[i][j] += elements_[i][k] * other.elements_[k][j];
			}
		}
	}

	result.rows_ = rows_;
	result.collumns_ = other.collumns_;

	return result;
}

matrix_t & matrix_t::operator -=(matrix_t const & other)
{
	for (size_t i = 0; i < rows_; i++)
	{
		for (size_t j = 0; j < collumns_; j++)
		{
			elements_[i][j] -= other.elements_[i][j];
		}
	}

	return *this;
}

matrix_t & matrix_t::operator +=(matrix_t const & other)
{
	for (size_t i = 0; i < rows_; i++)
	{
		for (size_t j = 0; j < collumns_; j++)
		{
			elements_[i][j] += other.elements_[i][j];
		}
	}

	return *this;
}

matrix_t & matrix_t::operator *=(matrix_t const & other)
{
	matrix_t copy(*this);

	*this = copy * other;

	return *this;
}

std::istream & matrix_t::read(std::istream & stream)
{
	std::size_t rows;
	std::size_t collumns;
	char symbol;

	bool success = true;
	if (stream >> rows && stream >> symbol && symbol == ',' && stream >> collumns) {
		float ** elements = new float *[rows];
		for (std::size_t i = 0; success && i < rows; ++i) {
			elements[i] = new float[collumns];
			for (std::size_t j = 0; j < collumns; ++j) {
				if (!(stream >> elements[i][j])) {
					success = false;
					break;
				}
			}
		}

		if (success) {
			for (std::size_t i = 0; i < rows_; ++i) {
				delete[] elements_[i];
			}
			delete[] elements_;

			rows_ = rows;
			collumns_ = collumns;
			elements_ = elements;
		}
		else {
			for (std::size_t i = 0; i < rows; ++i) {
				delete[] elements[i];
			}
			delete[] elements;
		}
	}
	else {
		success = false;
	}

	if (!success) {
		stream.setstate(std::ios_base::failbit);
	}

	return stream;
}

std::ostream & matrix_t::write(std::ostream & stream) const
{
	stream << rows_ << ", " << collumns_;
	for (std::size_t i = 0; i < rows_; ++i) {
		stream << '\n';
		for (std::size_t j = 0; j < collumns_; ++j) {
			stream << elements_[i][j];
			if (j != rows_ - 1) {
				stream << ' ';
			}
		}
	}

	return stream;
}
