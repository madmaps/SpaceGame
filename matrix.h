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
};

matrix matrix::operator+(matrix& rhs)
{
	
	if(m_rows!=rhs.getRows() || m_cols!=rhs.getCols())
	{
		return NULL;
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

matrix matrix::operator-(matrix& rhs)
{
	
	if(m_rows!=rhs.getRows() || m_cols!=rhs.getCols())
	{
		return NULL;
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

matrix matrix::operator*(matrix& rhs)
{
	int num1,num2;
	if(m_cols!=rhs.getRows())
	{
		return NULL;
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
