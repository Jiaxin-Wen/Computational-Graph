#ifndef LEASTSQUARE_H_INCLUDED
#define LEASTSQUARE_H_INCLUDED

#include <iomanip>
#include <string>
#include "Graph.h"

class LeastSquare :public ComputionalGraph{
	int x_num;
	int train_num;
	int times;
	double a; //步长 
	 //自变量所组成的矩阵的转置与矩阵相乘 ATA 
  	double matrix[100][100];
	//ATA的逆
	double inverse[100][100];
	//系数 
	std::vector<double>w; 
	void get_cofactor(double arcs[100][100],int n,double ans[100][100]);
	double get_matrix_value(double arcs[100][100],int n); 
	//建立自变量与因变量 
	void x_y_factory();
	//更新系数 
	void w_factory();
	//更新预测值 
	void predict_factory();
	//梯度下降法中对误差的求导 
	void diff_Loss_factory();
	//对于自变量构建矩阵 
	void build_matrix();
	//矩阵求逆 
	void matrix_inverse();
	//用于最小二乘法中计算系数 
	void calc_w();
	//运算误差 
	void Loss_factory();
public:
	~LeastSquare() = default;
	
	void Square();
	void run();
	void Initialize();
	void ReadIn();
	void GradientDescent();
};

#endif
