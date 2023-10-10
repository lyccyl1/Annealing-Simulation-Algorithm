#include<bits/stdc++.h>
using namespace std;
int n,m;//�������ͻ����� 
int t[1010][1010];//��Ÿ������ڸ������ϵ�ʱ������ 
long long res[1010][1010];//��Ÿ������ڸ��������깤ʱ������� 
int pos[1010];//�������� 
int pos_min[1010];//ȫ�����Ž�������������� 
const double k=0.995;//�¶��½����� 
const double temp_min=1e-15;//�½��¶� 
long long res_min;//��ǰ�� 
long long res_now;//����� 
long long getres()//�������깤ʱ�� 
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			res[i][j]=0;
		}
	}//��ʼ�����������ڸ�̨�����ϵ��깤ʱ���Ϊ0 
	for(int i=1; i<=m; i++)
	{
		res[pos[1]][i]=res[pos[1]][i-1]+t[pos[1]][i];
	}//��������Ϊ��һλ�Ĺ����ڸ������ϵ��깤ʱ�� 
	for(int i=2; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			res[pos[i]][j]=max(res[pos[i]][j-1],res[pos[i-1]][j])+t[pos[i]][j];
		}
	}//���ö�̬�滮����ʣ�����򹤼��ڸ������ϵ��깤ʱ�� 
	return res[pos[n]][m];//���ش� 
}
void init()
{
	for (int i =1 ; i<= n ; i++)
	{
		pos[i]=i;
	}
}//��ʼ������ ������˳������ 
void neg(int a, int b)
{
	if (a < b)
	{
		int x =pos[a];
		for (int i=a; i<=b-1; i++ )
		{
			pos[i]=pos[i+1];
		}
		pos[b]=x;
	}
	else
	{
		int x =pos[a];
		for (int i=a; i>=b+1 ; i-- )
		{
			pos[i]=pos[i-1];
		}
		pos[b]=x;
	}
}//�ƶ�������Ե�������� 
void unneg(int a,int b)
{
	if (a < b)
	{
		int x =pos[b];
		for (int i=b; i>=a+1; i-- )
		{
			pos[i]=pos[i-1];
		}
		pos[a]=x;
	}
	else
	{
		int x =pos[b];
		for (int i=b; i<=a-1; i++ )
		{
			pos[i]=pos[i+1];
		}
		pos[a]=x;
	}
}//�ƶ����������������� 
int main ()
{
	srand(time(NULL));//�����ڵ�ϵͳʱ����Ϊ���������������������� 
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1 ; j <=m; j++)
		{
			int num;
			scanf("%d",&num);
			scanf("%d",&t[i][num+1]);
		}
	}//������������ 
	init();//��ʼ�������� 
	res_min=getres();//�õ���ʼ�� 
	//int cnt = 0;���ڼ��������� 
	int min =0x3F3F3F3F; //��ʼ��ȫ�����Ž� 
	for (int l=1;l<=20;l++)
	{
		//cnt ++;
		double temp=10000.0;//���ó�ʼ�¶� 
		while (temp>temp_min)//һ��ģ���˻𣬱߽����� 
		{
			for (int i=1; i<=4; i++)//ÿ���¶��µĵ������� 
			{
				int a = rand()%n+1;
				int b = rand()%n+1;//��ȡ������ͬ������� 
				while (a == b)
				{
					b = rand()%n+1;
				}
				neg(a,b);//�ƶ�������� 
				//swap(pos[a], pos[b]);//����������� 
				res_now = getres();//�������� 
				long long deta_e = res_now - res_min;//���������� 
				double double_e=deta_e;//ת����double���� 
				if(deta_e<=0)//��������ȵ�ǰ��С������� 
				{
					res_min= res_now;
				}
				else//�����Ը��ʽ�������� 
				{
					double cond = exp((-double_e)/temp)-double(rand()/RAND_MAX);
					if (cond > 0)
					{
						res_min = res_now ;
					}
					else//�����ܣ����������� 
					{
						unneg(a,b);
						//swap(pos[a],pos[b]);
					}
				}
				temp*=k;//�¶��½� 
			}
		}
/*	for(int i = 1; i<=n; i++)
		{
			printf("%d ",pos[i]);
		}*/
//		printf("\n");//ÿ�������ǰ����������� 
		if (res_min <min )
		{
			min = res_min;
			for(int i = 1; i<=n; i++)
			{
				pos_min[i]=pos[i];
			}

		}//����ȫ�����Ž� 
//		printf("%d\n",cnt);//����������� 
		printf("     %d\n",res_min);//�����ǰ�� 
	}
	for(int i =1 ; i<=n; i++)
	{
		printf("%d ",pos[i]);
	}//�����ǰ������ 
	printf("%d\n",min);//���ȫ�����Ž� 
	return 0;
}
