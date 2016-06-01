#include "matrix.h"

matrix::matrix(const int& rows,const int& cols):m_rows(rows),m_cols(cols)
{
	m_matrix.assign(rows*cols,0);
}


matrix::matrix(const int& rows,const int& cols,const double info[])
{
	m_rows=rows;
	m_cols=cols;
	for(int i=0;i<=cols-1;i++)
	{
		for(int j=0;j<=rows-1;j++)
		{
			m_matrix.push_back(info[(i*rows)+j]);
		}
	}
}


matrix::matrix(const matrix& inMatrix)
{
	m_rows = inMatrix.m_rows;
	m_cols = inMatrix.m_cols;
	m_matrix = inMatrix.m_matrix;
}

matrix& matrix::operator=(const matrix& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	m_rows = rhs.m_rows;
	m_cols = rhs.m_cols;
	m_matrix = rhs.m_matrix;
	return *this;
}

matrix matrix::operator+(const matrix& rhs)
{
	
	if(m_rows!=rhs.getRows() || m_cols!=rhs.getCols())
	{
		return 0;
	}
	matrix retMatrix(m_rows,m_cols);
	for(int rows=0;rows<m_rows;rows++)
	{
		for(int cols=0;cols<m_cols;cols++)
		{
			retMatrix.setLocation((cols*m_cols)+rows,m_matrix[(cols*m_cols)+rows]+rhs.getLocation((cols*m_cols)+rows));
		}
	}
	return retMatrix;


}

matrix matrix::operator-(const matrix& rhs)
{
	
	if(m_rows!=rhs.getRows() || m_cols!=rhs.getCols())
	{
		return 0;
	}
	matrix retMatrix(m_rows,m_cols);
	for(int rows=0;rows<m_rows;rows++)
	{
		for(int cols=0;cols<m_cols;cols++)
		{
			retMatrix.setLocation((cols*m_cols)+rows,m_matrix[(cols*m_cols)+rows]-rhs.getLocation((cols*m_cols)+rows));
		}
	}
	return retMatrix;


}

matrix matrix::operator*(const matrix& rhs)
{
	if(m_cols!=rhs.getRows())
	{
		return 0;
	}
	matrix retMatrix(m_rows,rhs.getCols());
	float sum=0;
	for(int col=0;col<m_rows;col++)
	{
		for(int row=0;row<rhs.getCols();row++)
		{
			sum=0;
			for(int k=0;k<m_cols;k++)
			{
				sum=sum+m_matrix.at((col*m_cols)+k)*rhs.getLocation((k*rhs.getCols())+row);
			}
			retMatrix.setLocation((col*rhs.getCols())+row,sum);
		}
		
	}
	return retMatrix;
};

void matrix::setMatrix(const int& rows, const int& cols, const double info[])
{
	m_rows=rows;
	m_cols=cols;
	m_matrix.assign(0,0);
	for(int i=0;i<=cols-1;i++)
	{
		for(int j=0;j<=rows-1;j++)
		{
			m_matrix.push_back(info[(i*rows)+j]);
		}
	}
};
