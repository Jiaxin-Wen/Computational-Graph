#include "LeastSquare.h"

void LeastSquare::run()
{
	Initialize(); 
	ReadIn();
	Square(); 
	GradientDescent();
	
}
//�������� 
void LeastSquare::ReadIn()
{
	std::cin >> x_num >> train_num >> a >> times;
	x_y_factory();
	for(int i=1;i<=train_num;i++)
	{
		for(int j=0;j<=x_num;j++)
		{
			if(j==0) NodeMap["x"+std::to_string(i)+std::to_string(0)]->SetValue(1.);
			else 
			{
				double temp = 0.;
				std::cin >> temp;
				NodeMap["x"+std::to_string(i)+std::to_string(j)]->SetValue(temp);
			}
		}
		double temp = 0.;
		std::cin >> temp;
		NodeMap["y"+std::to_string(i)]->SetValue(temp);
	}
	w.resize(x_num+1,1);
} 
//��ʼ�����нڵ� 
void LeastSquare::Initialize()
{
	auto iter = NodeMap.begin();
    auto itend = NodeMap.end();
    for(; iter != itend; iter++)
    {
        delete iter->second;
    }
    NodeMap.clear();
}
/*
x��һλ��ѵ�����ĸ�������1��ʼ���ڶ�λ�Ǳ����ĸ�������0��ʼ��x0��1
w��0��ʼ ���Ǳ�������+1 
y��1��ʼ��������ѵ�����ĸ��� 
*/
void LeastSquare::x_y_factory()
{ 
	for(int i=1;i<=train_num;i++)
	{
		for(int j=0;j<=x_num;j++)
		{
			Node * NewPointer = new Placeholder("x"+std::to_string(i)+std::to_string(j));
			NodeMap.insert(std::make_pair(NewPointer->GetName(), NewPointer));
		}
		Node * NewPointer = new Placeholder("y"+std::to_string(i));
		NodeMap.insert(std::make_pair(NewPointer->GetName(),NewPointer)); 
	}
}
//����ϵ�� 
void LeastSquare::w_factory()
{
	for(int i=0;i<=x_num;i++)
	{
		if(NodeMap.count("w"+std::to_string(i))==1)
		{
			NodeMap["w"+std::to_string(i)]->SetValue(w[i]);
		}
		else{
			Node * NewPointer = new Variable("w"+std::to_string(i),w[i]);
			NodeMap.insert(std::make_pair(NewPointer->GetName(),NewPointer));
		}
		
	}
}
//����Ԥ��ֵ 
void LeastSquare::predict_factory()
{
	for(int i=1;i<=train_num;i++)
	{
		double temp = 0.;
		for(int j=0;j<=x_num;j++)
		{
			temp += NodeMap["w"+std::to_string(j)]->GetValue() * NodeMap["x" + std::to_string(i)+std::to_string(j)]->GetValue();
		}
		if(NodeMap.count("predict"+std::to_string(i))) NodeMap["predict"+std::to_string(i)] ->SetValue(temp);
		else 
		{
			Node * NewPointer = new Variable("predict"+std::to_string(i),temp);
			NodeMap.insert(std::make_pair(NewPointer->GetName(),NewPointer));
		}
	}
}
//�������� 
void LeastSquare::build_matrix()
{
	
	for(int i=0;i<=x_num;i++)
	{
		for(int j=0;j<=x_num;j++)
		{
			double temp = 0.;
			for(int t=1;t<=train_num;t++)
			{
				temp += NodeMap["x"+std::to_string(t)+std::to_string(i)]->GetValue()
						* NodeMap["x"+std::to_string(t)+std::to_string(j)]->GetValue();
			}
			matrix[i][j] = temp; 
		}
	}
}
//������������ʽ 
double LeastSquare::get_matrix_value(double arcs[100][100],int n) 
{
	if(n==1)
    {
    	return arcs[0][0];
    }
    double ans = 0;
    double temp[100][100];
    int i,j,k;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-1;j++)
        {
            for(k=0;k<n-1;k++)
            {
                temp[j][k] = arcs[j+1][(k>=i)?k+1:k];
                  
        	}
        }
        double t = get_matrix_value(temp,n-1);
        if(i%2==0)
        {
            ans += arcs[0][i]*t;
        }
        else
        {
            ans -= arcs[0][i]*t;
        }
    }
    return ans;
}

//����������ʽ
void LeastSquare::get_cofactor(double arcs[100][100],int n,double ans[100][100])  
{
    int i,j,k,t;
    double temp[100][100];
	for(i=0;i<n;i++)
	{
    	for(j=0;j<n;j++)
    	{
            for(k=0;k<n-1;k++)
            {
                for(t=0;t<n-1;t++)
                {
                    temp[k][t] = arcs[k>=i?k+1:k][t>=j?t+1:t];
                }
            }
            ans[j][i]  =  get_matrix_value(temp,n-1);  
            if((i+j)%2 == 1)
            {
                ans[j][i] = - ans[j][i];
        	}
        }
    }
}
//���������� 
void LeastSquare::matrix_inverse()
{
    double flag=get_matrix_value(matrix,x_num+1);
    double t[100][100];
    get_cofactor(matrix,x_num+1,t);
    for(int i=0;i<=x_num;i++)
    {
        for(int j=0;j<=x_num;j++)
        {
        	if(flag!=0){
        		inverse[i][j]=t[i][j]/flag;
			}
            else inverse[i][j] = t[i][j];
        }
	}
}

//������С���˷�����ϵ�� 
void LeastSquare::calc_w()
{
	std::vector<double> t;
	for(int i=0;i<=x_num;i++)
	{
		double temp = 0.;
		for(int j=1;j<=train_num;j++)
		{
			temp += NodeMap["x"+std::to_string(j)+std::to_string(i)]->GetValue()
					* NodeMap["y"+std::to_string(j)]->GetValue();
		}
		t.push_back(temp);
	}
	for(int i=0;i<=x_num;i++){
		double temp = 0.;
		for(int j=0;j<=x_num;j++){
			temp += inverse[i][j] * t[j]; 
		}
		w[i]=temp;
	}
}
//��С���˷� 
void LeastSquare::Square()
{ 
	build_matrix(); 
	matrix_inverse();
	calc_w();
	
	std::cout << "LeastSquare: ";
	for(int i=0;i<=x_num;i++)
	{
		std::cout << std::fixed << std::setprecision(4) << w[i] << " ";
	} 
	std::cout << std::endl;
	
	Loss_factory();
	
}
//�õ������ 
void LeastSquare::Loss_factory()
{	
	w_factory();
	predict_factory();
	for(int i=1;i<=train_num;i++)
	{
		double temp = (NodeMap["predict"+ std::to_string(i)]->GetValue()-NodeMap["y"+std::to_string(i)]->GetValue()) *
						(NodeMap["predict"+ std::to_string(i)]->GetValue()-NodeMap["y"+std::to_string(i)]->GetValue());
		if(NodeMap.count("Loss"+std::to_string(i))) NodeMap["Loss"+std::to_string(i)]->SetValue(temp);
		else
		{
			Node * NewPointer = new Variable("Loss"+std::to_string(i),temp);
			NodeMap.insert(std::make_pair(NewPointer->GetName(),NewPointer));
		}
	}
	std::cout << "Loss: " ;
	for(int i=1;i<=train_num;i++)
	{
		std::cout << NodeMap["Loss"+std::to_string(i)]->GetValue() << std::endl;
	}
} 
//������� 
void LeastSquare::diff_Loss_factory()
{
	for(int i=0;i<=x_num;i++)
	{
		double temp=0.;
		for(int j=1;j<=train_num;j++)
		{
			temp += (NodeMap["predict" + std::to_string(j)]->GetValue()-NodeMap["y"+std::to_string(j)]->GetValue())*
					NodeMap["x"+std::to_string(j)+std::to_string(i)]->GetValue();
		} 
		if(NodeMap.count("diff_Loss"+std::to_string(i))==1) NodeMap["diff_Loss"+std::to_string(i)] ->SetValue(temp);
		else 
		{
			Node * NewPointer = new Variable("diff_Loss"+std::to_string(i),temp);
			NodeMap.insert(std::make_pair(NewPointer->GetName(),NewPointer));
		}
	}
}
//�ݶ��½�
void LeastSquare::GradientDescent()
{  
	//��ʼ��w 
	
	w_factory();
	for(int i=0;i<times;i++)
	{
		predict_factory();
		diff_Loss_factory();
		for(int t=0;t<=x_num;t++){
			w[t] -= a*NodeMap["diff_Loss"+std::to_string(t)]->GetValue()/(double)train_num;
		}
		w_factory();
	}
	
	std::cout << "GradientDescent: ";
	for(int i=0;i<=x_num;i++){
		 
		std::cout << std::fixed << std::setprecision(4) << w[i] << " ";
	}
	std::cout << std::endl;
	Loss_factory();
	
}
