#ifndef __MATRIX__
#define __MATRIX__
#include <vector>

class matrix
{
public:
	//constructors
	matrix(const int& rows=4,const int& cols=4):m_rows(rows),m_cols(cols){m_matrix.assign(rows*cols,0);}
	matrix(const int& rows,const int& cols,const double info[]);
	//destructor
	~matrix(){}
	//operator overloading
	matrix operator*(matrix& rhs);
	matrix operator+(matrix& rhs);
	matrix operator-(matrix& rhs);
	//getters
	//Matrix getMatrix();
	int getRows(){return m_rows;}
	int getCols(){return m_cols;}
	double getLocation(const int& locX,const int& locY){return m_matrix.at((locY*m_cols)+locX);}//might not work right???
	double getLocation(const int& loc){return m_matrix.at(loc);}
	//setters
	void setLocation(const int& loc,const double& val){m_matrix[loc]=val;}//return m_matrix.
	//void setRows(const int& rows);
	//void setCols(const int& cols);
	void setRowsCols(const int& rows,const int& cols){m_rows=rows;m_cols=cols;m_matrix.clear();m_matrix.assign((rows*cols),0);}
	void setMatrix(const int& rows, const int& cols, const double info[]);
	//void setMatrix(const int& range_low,const int& range_high,const double& info);

private:
	int m_rows;
	int m_cols;
	std::vector<double> m_matrix;
};

#endif

