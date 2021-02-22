#ifndef LEASTSQUARE_H_INCLUDED
#define LEASTSQUARE_H_INCLUDED

#include <iomanip>
#include <string>
#include "Graph.h"

class LeastSquare :public ComputionalGraph{
	int x_num;
	int train_num;
	int times;
	double a; //���� 
	 //�Ա�������ɵľ����ת���������� ATA 
  	double matrix[100][100];
	//ATA����
	double inverse[100][100];
	//ϵ�� 
	std::vector<double>w; 
	void get_cofactor(double arcs[100][100],int n,double ans[100][100]);
	double get_matrix_value(double arcs[100][100],int n); 
	//�����Ա���������� 
	void x_y_factory();
	//����ϵ�� 
	void w_factory();
	//����Ԥ��ֵ 
	void predict_factory();
	//�ݶ��½����ж������� 
	void diff_Loss_factory();
	//�����Ա����������� 
	void build_matrix();
	//�������� 
	void matrix_inverse();
	//������С���˷��м���ϵ�� 
	void calc_w();
	//������� 
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
