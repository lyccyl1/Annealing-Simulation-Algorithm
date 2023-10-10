#include<bits/stdc++.h>
using namespace std;
int n,m;//工件数和机器数 
int t[1010][1010];//存放各工件在个机器上的时间数组 
long long res[1010][1010];//存放各工件在个机器上完工时间的数组 
int pos[1010];//排序数组 
int pos_min[1010];//全局最优解的排序序列数组 
const double k=0.995;//温度下降常数 
const double temp_min=1e-15;//下界温度 
long long res_min;//当前解 
long long res_now;//邻域解 
long long getres()//计算总完工时间 
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			res[i][j]=0;
		}
	}//初始化各个工件在各台机器上的完工时间均为0 
	for(int i=1; i<=m; i++)
	{
		res[pos[1]][i]=res[pos[1]][i-1]+t[pos[1]][i];
	}//计算排序为第一位的工件在各机器上的完工时间 
	for(int i=2; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			res[pos[i]][j]=max(res[pos[i]][j-1],res[pos[i-1]][j])+t[pos[i]][j];
		}
	}//利用动态规划计算剩余排序工件在各机器上的完工时间 
	return res[pos[n]][m];//返回答案 
}
void init()
{
	for (int i =1 ; i<= n ; i++)
	{
		pos[i]=i;
	}
}//初始化队列 按输入顺序排序 
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
}//移动邻域策略的正向操作 
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
}//移动邻域操作的逆向操作 
int main ()
{
	srand(time(NULL));//以现在的系统时间作为随机数的种子来产生随机数 
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1 ; j <=m; j++)
		{
			int num;
			scanf("%d",&num);
			scanf("%d",&t[i][num+1]);
		}
	}//读入输入数据 
	init();//初始化解序列 
	res_min=getres();//得到初始解 
	//int cnt = 0;用于计算求解次数 
	int min =0x3F3F3F3F; //初始化全局最优解 
	for (int l=1;l<=20;l++)
	{
		//cnt ++;
		double temp=10000.0;//设置初始温度 
		while (temp>temp_min)//一轮模拟退火，边界条件 
		{
			for (int i=1; i<=4; i++)//每个温度下的迭代次数 
			{
				int a = rand()%n+1;
				int b = rand()%n+1;//获取两个不同的随机数 
				while (a == b)
				{
					b = rand()%n+1;
				}
				neg(a,b);//移动邻域策略 
				//swap(pos[a], pos[b]);//交换邻域策略 
				res_now = getres();//求得邻域解 
				long long deta_e = res_now - res_min;//计算能量差 
				double double_e=deta_e;//转换成double类型 
				if(deta_e<=0)//如果邻域解比当前解小，则接受 
				{
					res_min= res_now;
				}
				else//否则以概率接受邻域解 
				{
					double cond = exp((-double_e)/temp)-double(rand()/RAND_MAX);
					if (cond > 0)
					{
						res_min = res_now ;
					}
					else//不接受，则进行逆操作 
					{
						unneg(a,b);
						//swap(pos[a],pos[b]);
					}
				}
				temp*=k;//温度下降 
			}
		}
/*	for(int i = 1; i<=n; i++)
		{
			printf("%d ",pos[i]);
		}*/
//		printf("\n");//每次输出当前解的排序序列 
		if (res_min <min )
		{
			min = res_min;
			for(int i = 1; i<=n; i++)
			{
				pos_min[i]=pos[i];
			}

		}//更替全局最优解 
//		printf("%d\n",cnt);//输出迭代次数 
		printf("     %d\n",res_min);//输出当前解 
	}
	for(int i =1 ; i<=n; i++)
	{
		printf("%d ",pos[i]);
	}//输出当前解序列 
	printf("%d\n",min);//输出全局最优解 
	return 0;
}
