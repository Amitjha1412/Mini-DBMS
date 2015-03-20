#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>
#include<cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>
#include <sstream>
using namespace std;

int pageSize;

struct table
{
    string name;
    int nr;
    int bfr;
    vector<int>pageidx;
    bool modified;
    int modifiedIdx;
    int modifiedLine;
    vector <string> Attributes;
    set<string> unique[10];
    vector <string> Data_Type;
};

struct Query
{
    string type;
    vector<string> columns;
    vector<string> tables;
    vector<string> distinct;
    vector<string> condition;
    vector<string> orderby;
    vector<string> groupby;
    vector<string> having;
    vector<string> attributes;
    vector<string> data_type;
    vector<string> join_condition;
    bool cf,tf,df,conf,of,gf,hf,af,dtf,valid,sf;
    int jf;
    Query *child;
};

struct comparer{
    comparer(vector<pair<pair<int,int>,int> > ocolons){
        this->ocolons=ocolons;
    }
    bool operator ()(vector<string> a,vector<string> b)
    {
        int i=0;
        for( i=0;i<ocolons.size()-1;i++)
        {
            int coln=ocolons[i].first.first,val=ocolons[i].first.second,l=ocolons[i].second;
            if(val==1)
            {
                if(l==1)
                {
                    if(a[coln].compare(b[coln])>0)
                        return false;
                    else if(a[coln].compare(b[coln])<0)
                        return true;
                }
                else
                {
                    if ((atoi(a[coln].c_str())-atoi(b[coln].c_str()))>0)
                        return false;
                    else if ((atoi(a[coln].c_str())-atoi(b[coln].c_str()))<0)
                        return true;
                }
            }
            else
            {
                if(l==1)
                {
                    if(a[coln].compare(b[coln])>0)
                        return true;
                    else if(a[coln].compare(b[coln])<0)
                        return false;
                }
                else
                {
                    if ((atoi(a[coln].c_str())-atoi(b[coln].c_str()))>0)
                        return true;
                    else if ((atoi(a[coln].c_str())-atoi(b[coln].c_str()))<0)
                        return false;
                }
            }
        }
        int coln=ocolons[i].first.first,val=ocolons[i].first.second,l=ocolons[i].second;
        if(val==1)
        {
            if(l==1)
                return (a[coln].compare(b[coln])>=0)?false:true;
            else
                return ((atoi(a[coln].c_str())-atoi(b[coln].c_str()))>=0)?false:true;
        }
        else
        {
            if(l==1)
                return (a[coln].compare(b[coln])>=0)?true:false;
            else
                return ((atoi(a[coln].c_str())-atoi(b[coln].c_str()))>=0)?true:false;
        }
    }
    bool cmp(vector<string> a,vector<string> b)
    {
        int i=0;
        for( i=0;i<ocolons.size()-1;i++)
        {
            int coln=ocolons[i].first.first,val=ocolons[i].first.second,l=ocolons[i].second;
            if(val==1)
            {
                if(l==1)
                {
                    if(a[coln].compare(b[coln])>0)
                        return false;
                    else if(a[coln].compare(b[coln])<0)
                        return true;
                }
                else
                {
                    if ((atoi(a[coln].c_str())-atoi(b[coln].c_str()))>0)
                        return false;
                    else if ((atoi(a[coln].c_str())-atoi(b[coln].c_str()))<0)
                        return true;
                }
            }
            else
            {
                if(l==1)
                {
                    if(a[coln].compare(b[coln])>0)
                        return true;
                    else if(a[coln].compare(b[coln])<0)
                        return false;
                }
                else
                {
                    if ((atoi(a[coln].c_str())-atoi(b[coln].c_str()))>0)
                        return true;
                    else if ((atoi(a[coln].c_str())-atoi(b[coln].c_str()))<0)
                        return false;
                }
            }
        }
        int coln=ocolons[i].first.first,val=ocolons[i].first.second,l=ocolons[i].second;
        if(val==1)
        {
            if(l==1)
                return (a[coln].compare(b[coln])>=0)?false:true;
            else
                return ((atoi(a[coln].c_str())-atoi(b[coln].c_str()))>=0)?false:true;
        }
        else
        {
            if(l==1)
                return (a[coln].compare(b[coln])>=0)?true:false;
            else
                return ((atoi(a[coln].c_str())-atoi(b[coln].c_str()))>=0)?true:false;
        }
    }
    vector<pair<pair<int,int>,int> > ocolons;
};
struct tcomp{
    tcomp(vector<pair<pair<int,int>,int> > ocolons){
        this->ocolons=ocolons;
    }
    int comp(vector<string> a,vector<string> b)
    {
        int coln1=ocolons[0].first.first,coln2=ocolons[0].first.second,l=ocolons[0].second;
        if(l==1)
            return (a[coln1].compare(b[coln2])>0)?1:((a[coln1].compare(b[coln2])<0)?-1:0);
        else
        {
            a[coln1].erase(remove( a[coln1].begin(), a[coln1].end(), '\"' ),a[coln1].end());
            b[coln2].erase(remove( b[coln2].begin(), b[coln2].end(), '\"' ),b[coln2].end());
            int x=atoi(a[coln1].c_str());
            int y=atoi(b[coln2].c_str());
            //cout<<x<<" "<<y<<endl;
            if(x==y)
                return 0;
            else if(x>y)
                return 1;
            else
                return -1;
           // return ((atoi(a[coln1].c_str())-atoi(b[coln2].c_str()))>0)?1:((atoi(a[coln1].c_str())-atoi(b[coln2].c_str())<0)?-1:0);
        }
    }
    vector<pair<pair<int,int>,int> > ocolons;
};
int sizeofv(vector<string> vec)
{
    int ans=0;
    for(int i=0;i<vec.size();i++)
    {
        ans=ans+(vec[i].size()*vec[i][0]);
    }
    return ans;
}

vector<vector<string> > merge(vector<vector<string> > &a,vector<vector<string> > &b,vector<pair<pair<int,int>,int> > &ocolons)
{
    comparer cmp = comparer(ocolons);
    vector<vector<string> > result;
    for(int i=0,j=0;i<a.size() || j<b.size();)
    {
        if(i<a.size() && j<b.size())
        {
            if(cmp.cmp(b[j],a[i]))
            {
                result.push_back(b[j]);
                j++;
            }
            else
            {
                result.push_back(a[i]);
                i++;
            }
        }
        else if(j<b.size())
        {
            result.push_back(b[j]);
            j++;
        }
        else if(i<a.size())
        {
            result.push_back(a[i]);
            i++;
        }
    }
    return result;
}

vector<vector<vector<string> > > sortmerge(vector<vector<vector<string > > > &result, vector<pair<pair<int,int>,int> > &ocolons)
{

    //cout<<"akjchutiya"<<endl;
    //sort part
    for(int j=0;j<result.size();j++)
    {
        //cout<<"ENDLakjchutiya"<<endl;
        sort(result[j].begin(),result[j].end(),comparer(ocolons));
    }
    //cout<<"iocolons "<<i<<endl;
    //cout<<"akjchutiya"<<endl;
    //merge part
    for(int j=2;(j/2)<result.size();j*=2)
        //		int j=2;
    {
        for(int k=0;k<result.size();k+=j)
        {
            //cout << "aaaaaaaaaaa\n";
            vector<vector<string> >a;
            vector<vector<string> >b;
            for(int l=k;(l<k+j/2)&&(l<result.size());l++)
            {
                for(int m=0;m<result[l].size();m++)
                    a.push_back(result[l][m]);
                //result[l].clear();
            }
            //cout << "bbbbbbbbbbb\n";
            for(int l=k+j/2;(l<k+j)&&(l<result.size());l++)
            {
                for(int m=0;m<result[l].size();m++)
                    b.push_back(result[l][m]);
                //result[l].clear();
            }
            //cout << "ccccccccccc\n";
            vector<vector<string> > c=merge(a,b,ocolons);
            int curr=k;
            int l=0;
            //int currsize=0;
            //for(int l=0;l<c.size();l++)
            //{
            for(int li=k;(li<k+j)&&(li<result.size());li++)
            {

                for(int lj=0;lj<result[li].size();lj++)
                    result[li][lj]=c[l++];
            }
            /*int sl=sizeofv(c[l]);
              if(currsize+sl<pageSize)
              {
              currsize+=sl;
              result[curr].push_back(c[l]);
              }
              else
              {
              curr++;
              currsize=sl;
              result[curr].push_back(c[l]);
              }*/
            //}
        }

    }
    return result;
}
//exec Join Part

vector<pair<vector<string>,vector<string> > > execjoin(Query q, vector<table> &Table, vector<vector <string> > &page){
    //get table1, table2
    int table1,table2;
    for(int i=0;i<Table.size();i++)
    {
        if(Table[i].name==q.tables[0])
            table1=i;
        else if(Table[i].name==q.tables[1])
            table2=i;
    }

    /*************************************************************************************************/
    /*************************************************************************************************/
    /*************************************************************************************************/


    //get attributes for both
    vector<string> srow;
    vector<vector<vector < string > > > result1;
    vector<vector<vector < string > > > result2;
    vector<pair<pair<int,int >,int> > ocolons1;
    vector<pair<pair<int,int >,int> > ocolons2;
    boost::split(srow,q.join_condition[0],boost::is_any_of("="));	//each element is particular value, entire vector is a row
    vector<vector<string> > tpage;
    int i=table1;
    int currsize=0;
    for(int j=0;j<Table[i].pageidx.size();j++)
    {
        for(int k=0;k<page[Table[i].pageidx[j]].size();k++)
        {
            string row=page[Table[i].pageidx[j]][k];
            vector<string> srow;
            boost::split(srow,row,boost::is_any_of(","));	//each element is particular value, entire vector is a row
            if(1)		//satisfy function is handling where clause
            {
                if(currsize+(sizeof(row[0])*row.size())<=pageSize)
                {
                    tpage.push_back(srow);
                    currsize+=sizeof(row[0])*row.size();
                }
                else
                {
                    result1.push_back(tpage);
                    currsize=0;
                    tpage.clear();
                    tpage.push_back(srow);
                    currsize+=sizeof(row[0])*row.size();
                }
            }
        }
    }
    if(tpage.size()>0)
        result1.push_back(tpage);
    tpage.clear();
    currsize=0;
    i=table2;
    for(int j=0;j<Table[i].pageidx.size();j++)
    {
        //cout<<"loop wala: "<<page[Table[i].pageidx[j]].size()<<endl;
        for(int k=0;k<page[Table[i].pageidx[j]].size();k++)
        {
            string row=page[Table[i].pageidx[j]][k];
            vector<string> srow;
            boost::split(srow,row,boost::is_any_of(","));	//each element is particular value, entire vector is a row
            if(1)		//satisfy function is handling where clause
            {
                if(currsize+(sizeof(row[0])*row.size())<=pageSize)
                {
                    tpage.push_back(srow);
                    currsize+=sizeof(row[0])*row.size();
                }
                else
                {
                    result2.push_back(tpage);
                    currsize=0;
                    tpage.clear();
                    tpage.push_back(srow);
                    currsize+=sizeof(row[0])*row.size();
                }
                //cout<<row<<endl;
            }
        }
    }
    if(tpage.size()>0)
        result2.push_back(tpage);
    int j=table1;	//assign table no of required table.
    //cout<<"T1 "<<srow[0]<<endl;
    for(int k=0;k<Table[j].Attributes.size();k++)
    {
        string row=srow[0];
        vector<string> ssrow;
        boost::split(ssrow,row,boost::is_any_of("."));	//each element is particular value, entire vector is a row
        if(ssrow[1]==Table[j].Attributes[k])
        {
            int l=(Table[j].Data_Type[k]=="string")?1:2;
            ocolons1.push_back(make_pair(make_pair(k,1),l));
            //cout<<"IRWINNER"<<endl;
        }	//store colnumbers,order to be outputted.
    }
    j=table2;
    for(int k=0;k<Table[j].Attributes.size();k++)
    {
        string row=srow[1];
        vector<string> ssrow;
        boost::split(ssrow,row,boost::is_any_of("."));	//each element is particular value, entire vector is a row
        if(ssrow[1]==Table[j].Attributes[k])
        {
            int l=(Table[j].Data_Type[k]=="string")?1:2;
            ocolons2.push_back(make_pair(make_pair(k,1),l));
        }	//store colnumbers,order to be outputted.
    }


    /*************************************************************************************************/
    /*************************************************************************************************/
    /*************************************************************************************************/
    //sort on basis of attributes
    /*
       for(int i=0;i<result1.size();i++)
       {
       for(int j=0;j<result1[i].size();j++)
       {
       for(int k=0;k<result1[i][j].size();k++)
       {
       cout<<result1[i][j][k]<<",";
       }
       cout<<endl;
       }
       cout<<"end of page "<<i<<endl;
       }
       for(int i=0;i<ocolons1.size();i++)
       cout<<ocolons1[i].first.first<<" "<<ocolons1[i].first.second<<" "<<ocolons1[i].second<<endl;*/
    result1=sortmerge(result1,ocolons1);
    result2=sortmerge(result2,ocolons2);


    /*************************************************************************************************/
    /*************************************************************************************************/
    /*************************************************************************************************/
    //merge to get join
    vector<pair<vector<string>,vector<string> > > result;
    vector<pair<pair<int,int >,int> > ocolons;
    ocolons.push_back(make_pair(make_pair(ocolons1[0].first.first,ocolons2[0].first.first),ocolons1[0].second));
    tcomp cmp = tcomp(ocolons);

    int li=0,lj=0;
    /*for(int i=0;i<result1.size();i++)
        for(int j=0;j<result1[i].size();j++,cout<<"\n")
            for(int k=0;k<result1[i][j].size();k++)
                cout<<result1[i][j][k]<<" ";*/
    while(li<result1.size() && lj<result2.size())
    {
        int i=0;int j=0;
        while(i<result1[li].size() && j<result2[lj].size() && li<result1.size() && lj<result2.size())
        {
       /*     for(int it=0;it<result1[li][i].size();it++)
                cout<<result1[li][i][it]<<" ";
            cout<<endl;
            for(int it=0;it<result2[li][j].size();it++)
                cout<<result2[lj][j][it]<<" ";
            cout<<endl;*/
            if(cmp.comp(result1[li][i],result2[lj][j])==1)
                j++;
            else if(cmp.comp(result1[li][i],result2[lj][j])==-1)
                i++;
            else
            {
                //output the matched tuple
                result.push_back(make_pair(result1[li][i],result2[lj][j]));

                //output other tuples matching result2

                int nj=j+1,nlj=lj;
                if(nj>=result2[lj].size())
                {
                    nj=0;nlj=lj+1;
                }
                while(nj<result2[nlj].size() && nlj<result2.size() && cmp.comp(result1[li][i],result2[nlj][nj])==0)
                {
                    result.push_back(make_pair(result1[li][i],result2[nlj][nj]));
                    nj++;
                    if(nj>=result2[nlj].size())
                    {
                        //nj=0;nlj=lj+1;
                        nj=0;nlj++;//akj edit
                    }

                }

                //output other tuples matching result1

                int ni=i+1,nli=li;
                if(ni>=result1[li].size())
                {
                    ni=0;nli=li+1;
                }
                while(ni<result1[nli].size() && nli<result1.size() && cmp.comp(result1[nli][ni],result2[lj][j])==0)
                {
                    result.push_back(make_pair(result1[nli][ni],result2[lj][j]));
                    ni++;
                    if(ni>=result1[nli].size())
                    {
                        //ni=0;nli=li+1;
                        ni=0;nli++;//akj edit
                    }

                }
                i=ni;j=nj;li=nli;lj=nlj;
            }
        }
        if(i>=result1[li].size())
        {
            i=0;
            li++;
        }
        if(j>=result2[lj].size())
        {
            j=0;
            lj++;
        }
    }
    /*************************************************************************************************/
    /*************************************************************************************************/
    /*************************************************************************************************/

    return result;
}

struct JoinPlan
{
    int cost;
    int nr;
    int bfr;
    string plan;
};

//cost join part
/*JoinPlan costjoin(int S,JoinPlan dp[])
  {
  if(dp[S].cost!=INT_MIN)
  return dp[S];
//for()
return ret;
}*/

bool satisfy(vector<string> &srow,vector<string> &cond,table &ctable)
{
    if(!cond.size())
        return true;
    bool ret=1;
    vector<bool>bit;
    vector<string>c;
    stack<bool>st;
    // vector<string>cond;
    //    for(int i=0;i<condition.size();i++)
    //	    cout<<condition[i]<<endl;
    //   boost::split(cond,condition[0],boost::is_any_of(" "));   //each element is particular value, entire vector is a row
    for(int i=0,k=0;i<cond.size();i=i+4,k++)
    {
        for(int j=0;j<ctable.Attributes.size();j++)
        {
            if(cond[i+0].compare(ctable.name+"."+ctable.Attributes[j])==0)
            {
                if(cond[i+1]=="=")
                {
                    bit.push_back(!srow[j].compare(cond[i+2]));
                    //			cout<<srow[j]<<" "<<cond[i+2]<<endl;
                    //			cout<<bit[k]<<endl;
                }
                else if(cond[i+1]=="<")
                {
                    if(atof(srow[j].c_str()) < atof(cond[i+2].c_str()) )
                        bit.push_back(1);
                    else
                        bit.push_back(0);
                    //			cout<<srow[j]<<" "<<cond[i+2]<<endl;
                    //			cout<<bit[k]<<endl;
                }
                else if(cond[i+1]==">")
                {
                    if(atof(srow[j].c_str()) > atof(cond[i+2].c_str()) )
                        bit.push_back(1);
                    else
                        bit.push_back(0);
                    //			cout<<srow[j]<<" "<<cond[i+2]<<endl;
                    //			cout<<bit[k]<<endl;
                }
                else if(cond[i+1]=="<=")
                {
                    if(atof(srow[j].c_str()) <= atof(cond[i+2].c_str()) )
                        bit.push_back(1);
                    else
                        bit.push_back(0);
                }
                else if(cond[i+1]==">=")
                {
                    if(atof(srow[j].c_str()) >= atof(cond[i+2].c_str()) )
                        bit.push_back(1);
                    else
                        bit.push_back(0);
                }
                else if(cond[i+1]=="LIKE")
                {
                    bit.push_back(boost::iequals(srow[j],cond[i+2]));
                }
                if((i+3)<cond.size())
                    c.push_back(cond[i+3]);
                break;
            }
        }

    }
    /*if(c.size()==1)
    {
    if(c[0].compare("and")==0)
        ret=bit[0]&bit[1];
    else if(c[0].compare("or")==0)
        ret=bit[0]|bit[1];
    }
    else ret=bit[0];*/
    st.push(bit[0]);
    for(int i=1;i<bit.size();i++)
    {
        if(c[i-1]=="and")
        {
            bool t=st.top();
            st.pop();
            t=t&bit[i];
            st.push(t);
        }
        else if(c[i-1]=="or")
            st.push(bit[i]);
    }
    /* for(int k=1,i=4;i<cond.size();i=i+4,k++)
       {
       if(cond[i-1]=="and")
       ret=ret&bit[k];
       else
       ret=ret|bit[k];
       }*/
    /*  st.push(bit[0]);
        for(int k=1,i=4;i<cond.size();i=i+4,k++)
        {
    //    cout<<bit[k]<<endl;
    if(cond[i-1]=="and")
    {
    bool t=st.top();
    st.pop();
    t=t&bit[k];
    st.push(t);
    }
    else if(cond[i-1]=="or")
    st.push(bit[k]);
    }*/
   if(st.empty())
        return ret;
    ret=st.top();
    st.pop();
    while(!st.empty())
    {
        bool t=st.top();
        st.pop();
        ret=ret|t;
    }
    //   cout<<"akj rocks"<<endl;
    //  if(ret==1)
    //	    for(int i=0;i<srow.size();i++)
    //		    cout<<srow[i]<<" ";
    //   cout<<endl;
    return ret;
}
void executeSelect(Query q, vector<table> &Table, vector<vector <string> > &page)
{
    vector<string> strs;        //temp vector of string to store splitted parts
    vector<int> colnos;         //assuming only single table, no joins
    int table_no;               //table number of corressponding table
    vector<vector<vector<string> > > result;    //vector of pages containing results.
    /* check for joins */
    int jc=q.jf;
    if(jc==1)
    {
        vector<pair<vector<string>,vector<string> > > result;
        result=execjoin(q,Table,page);
        for(int i=0;i<result.size();i++)
        {
            vector<string> a = result[i].first;
            for(int j=0;j<a.size();j++)
            {
                cout<<a[j]<<",";
            }
            a=result[i].second;
            int tj;
            for(tj=0;tj<a.size()-1;tj++)
            {
                cout<<a[tj]<<",";
            }
            cout<<a[tj]<<endl;
        }
        return;
    }
    else if(jc>1)
    {
        vector<string>table;
        for(int i=0;i<q.tables.size();i++)
        {
            table.push_back(q.tables[i]);
        }
        int n=table.size()+1;
        JoinPlan dp[n][n];
        for(int i=1 ;i<n;i++)
        {
            for(int j=0;j<Table.size();j++)
                if(table[i-1].compare(Table[j].name)==0)
                {
                    dp[i][i].nr=Table[j].nr;
                    dp[i][i].bfr=Table[j].bfr;
                    dp[i][i].cost=0;
                    dp[i][i].plan=Table[j].name;
                    //   cout<<dp[i][i].nr<<" "<<dp[i][i].bfr<<" "<<dp[i][i].cost<<" "<<dp[i][i].plan<<endl;
                }
        }
        for(int L=2;L<n;L++)
        {
            for(int i=1;i<n-L+1;i++)
            {
                int j=i+L-1;
                dp[i][j].cost=INT_MAX;
                for(int k=i;k<=j-1;k++)
                {
                    //cout<<i<<" "<<k<<" "<<k+1<<" "<<j<<endl;
                    int q=dp[i][k].cost+dp[k+1][j].cost+(dp[i][k].nr/dp[i][k].bfr)*(1+log2(dp[i][k].nr/dp[i][k].bfr))+(dp[k+1][j].nr/dp[k+1][j].bfr)*(1+log2(dp[k+1][j].nr/dp[k+1][j].bfr));
                    if(q<dp[i][j].cost)
                    {
                        dp[i][j].cost=q;
                        dp[i][j].nr=dp[i][k].nr*dp[k+1][j].nr;
                        dp[i][j].bfr=dp[i][k].bfr;
                        dp[i][j].plan='(' + dp[i][k].plan+',' + dp[k+1][j].plan+')';
                    }
                }
            }
        }
        cout<<dp[1][n-1].plan<<endl;
        cout<<dp[1][n-1].cost<<endl;
        // JoinPlan a = costjoin(k-1);
        //cout<<a<<endl;
    }
    else
    {
        for(int i=0;i<q.columns.size();i++)
        {
            strs.clear();
            boost::split(strs,q.columns[i],boost::is_any_of("."));
            for(int j=0;j<Table.size();j++)
            {
                if(strs[0]==Table[j].name)
                {
                    table_no=j;	//assign table no of required table.
                    for(int k=0;k<Table[j].Attributes.size();k++)
                    {
                        if(strs[1]==Table[j].Attributes[k])
                            colnos.push_back(k);	//store all col numbers to be outputted.
                    }
                    break;
                }
            }
        }
        int i=table_no;
        //cout<<i<<endl;
        //cout<<"tpi  :"<<Table[i].pageidx.size()<<endl;
        vector<vector<string> > tpage;
        int currsize=0;
        for(int j=0;j<Table[i].pageidx.size();j++)
        {
            //cout<<"loop wala: "<<page[Table[i].pageidx[j]].size()<<endl;
            for(int k=0;k<page[Table[i].pageidx[j]].size();k++)
            {
                string row=page[Table[i].pageidx[j]][k];
                vector<string> srow;
                boost::split(srow,row,boost::is_any_of(","));	//each element is particular value, entire vector is a row
                if(q.condition.size()==0 || satisfy(srow,q.condition,Table[i]))		//satisfy function is handling where clause
                {
                    if(currsize+(sizeof(row[0])*row.size())<=pageSize)
                    {
                        tpage.push_back(srow);
                        currsize+=sizeof(row[0])*row.size();
                    }
                    else
                    {
                        result.push_back(tpage);
                        currsize=0;
                        tpage.clear();
                        tpage.push_back(srow);
                        currsize+=sizeof(row[0])*row.size();
                    }
                    //cout<<row<<endl;
                }
            }
        }
        if(tpage.size()>0)
            result.push_back(tpage);
        //now orderby part
        //gather all colnos for which orderby is to be applied
        vector<pair<pair<int,int >,int> > ocolons;
        for(int i=0;i<q.orderby.size();i++)
        {
            strs.clear();
            boost::split(strs,q.orderby[i],boost::is_any_of("."));
            //	for(int in=0;in<strs.size();in++)
            //		cout<<strs[in]<<" ";
            //	cout<<"orderby vars"<<endl;
            int j=table_no;	//assign table no of required table.
            for(int k=0;k<Table[j].Attributes.size();k++)
            {
                if(strs[1]==Table[j].Attributes[k])
                {
                    int l=(Table[j].Data_Type[k]=="string")?1:2;
                    //	cout<<Table[j].Data_Type[k]<<" "<<l<<"check type "<<endl;
                    if(strs.size()==2)
                        ocolons.push_back(make_pair(make_pair(k,1),l));
                    else if(strs[2]=="ASC)")
                        ocolons.push_back(make_pair(make_pair(k,1),l));
                    else
                        ocolons.push_back(make_pair(make_pair(k,2),l));
                }	//store all orderby colnumbers,order to be outputted.
            }
        }
        for(int i=0;i<ocolons.size();i++)
        {
            //sort part
            for(int j=0;j<result.size();j++)
            {
                sort(result[j].begin(),result[j].end(),comparer(ocolons));
            }
            //cout<<"iocolons "<<i<<endl;
            //merge part
            for(int j=2;(j/2)<result.size();j*=2)
                //		int j=2;
            {
                for(int k=0;k<result.size();k+=j)
                {
                    //cout << "aaaaaaaaaaa\n";
                    vector<vector<string> >a;
                    vector<vector<string> >b;
                    for(int l=k;(l<k+j/2)&&(l<result.size());l++)
                    {
                        for(int m=0;m<result[l].size();m++)
                            a.push_back(result[l][m]);
                        //result[l].clear();
                    }
                    //cout << "bbbbbbbbbbb\n";
                    for(int l=k+j/2;(l<k+j)&&(l<result.size());l++)
                    {
                        for(int m=0;m<result[l].size();m++)
                            b.push_back(result[l][m]);
                        //result[l].clear();
                    }
                    //cout << "ccccccccccc\n";
                    vector<vector<string> > c=merge(a,b,ocolons);
                    int curr=k;
                    int l=0;
                    //int currsize=0;
                    //for(int l=0;l<c.size();l++)
                    //{
                    for(int li=k;(li<k+j)&&(li<result.size());li++)
                    {

                        for(int lj=0;lj<result[li].size();lj++)
                            result[li][lj]=c[l++];
                    }
                    /*int sl=sizeofv(c[l]);
                      if(currsize+sl<pageSize)
                      {
                      currsize+=sl;
                      result[curr].push_back(c[l]);
                      }
                      else
                      {
                      curr++;
                      currsize=sl;
                      result[curr].push_back(c[l]);
                      }*/
                    //}
                }

            }
        }

        //for(int j=0;j<result.size();j++)
        //then print result part
        //cout<<"dddddddddddddd"<<endl;
        for(int j=0;j<result.size();j++)
        {
            for(int k=0;k<result[j].size();k++)
            {
                int l=0;
                for(l=0;l<colnos.size()-1;l++)
                    cout<<result[j][k][colnos[l]]<<",";
                cout<<result[j][k][colnos[l]]<<endl;
            }
            //cout<<"End fro page i"<< j << endl;
        }
    }
}

Query parseSelect(vector<string> vec,vector<table> Table)
{
    vector<string> vec2;
    vec2.push_back("where");
    vec2.push_back("orderby");
    vec2.push_back("groupby");
    vec2.push_back("having");
    vec2.push_back("disctinct");
    vec2.push_back("join");
    vec2.push_back("on");
    Query q;
    q.type="select";
    q.cf=false;
    q.tf=false;
    q.df=false;
    q.conf=false;
    q.of=false;
    q.gf=false;
    q.hf=false;
    q.af=false;
    q.valid=true;
    q.jf=0;
    int i=1;
    while(vec[i]!="from" and i<vec.size())
    {
        q.cf=true;
        if(vec[i]=="distinct")
        {
            i+=1;
            q.df=true;
            if(i==vec.size())
            {
                q.valid=false;
                break;
            }
            else
            {
                q.distinct.push_back(vec[i]);
                q.columns.push_back(vec[i]);
            }
        }
        else
            q.columns.push_back(vec[i]);
        i+=1;
    }
    while(i<vec.size())
    {
        if ( vec [i]== "from")
        {
            q.tf=true;
            while(i<vec.size())
            {
                i+=1;
                if ( i == vec.size())
                    break;
                if ( find(vec2.begin(), vec2.end(), vec[i]) != vec2.end() )
                    break;
                else
                    q.tables.push_back(vec[i]);
            }
        }
        else if ( vec [i]== "where")
        {
            q.conf=true;
            while(i<vec.size())
            {
                i+=1;
                if ( i == vec.size())
                    break;
                if ( find(vec2.begin(), vec2.end(), vec[i]) != vec2.end() )
                    break;
                else
                    q.condition.push_back(vec[i]);
            }
        }
        else if(vec[i]=="join")
        {
            q.jf++;
            while(i<vec.size())
            {
                i+=1;
                if ( i == vec.size())
                    break;
                if ( find(vec2.begin(), vec2.end(), vec[i]) != vec2.end() )
                    break;
                else
                    q.tables.push_back(vec[i]);
            }
        }
        else if(vec[i]=="on")
        {
            while(i<vec.size())
            {
                i+=1;
                if ( i == vec.size())
                    break;
                if ( find(vec2.begin(), vec2.end(), vec[i]) != vec2.end() )
                    break;
                else
                    q.join_condition.push_back(vec[i]);
            }
        }
        else if ( vec [i]== "groupby")
        {
            q.gf=true;
            while(i<vec.size())
            {
                i+=1;
                if ( i == vec.size())
                    break;
                if ( find(vec2.begin(), vec2.end(), vec[i]) != vec2.end() )
                    break;
                else
                    q.groupby.push_back(vec[i]);
            }
        }
        else if ( vec [i]== "having")
        {
            q.hf=true;
            while(i<vec.size())
            {
                i+=1;
                if ( i == vec.size())
                    break;
                if ( find(vec2.begin(), vec2.end(), vec[i]) != vec2.end() )
                    break;
                else
                    q.having.push_back(vec[i]);
            }
        }
        else if ( vec [i]== "orderby")
        {
            q.of=true;
            while(i<vec.size())
            {
                i+=1;
                if ( i == vec.size())
                    break;
                if ( find(vec2.begin(), vec2.end(), vec[i]) != vec2.end() )
                    break;
                else
                    q.orderby.push_back(vec[i]);
            }
        }
    }
    if(q.columns[0]=="*")
    {
        q.sf=1;
        q.columns.clear();
        for(int i=0;i<q.tables.size();i++)
        {
            for(int j=0;j<Table.size();j++)
            {
                if(q.tables[i]==Table[j].name)
                {
                    for(int k=0;k<Table[j].Attributes.size();k++)
                    {
                        string t="";
                        t=t+q.tables[i]+"."+Table[j].Attributes[k];
                        q.columns.push_back(t);
                    }
                }
            }
        }


    }
    return q;
}

bool validate(Query q,vector<table>&Table)
{
    string token;
    bool ret=true;
    for(int i=0;i<q.tables.size() && ret;i++)
    {
        bool flag=false;
        //cout<<q.tables[i]<<endl;
        for(int j=0;j<Table.size();j++)
        {
            if(Table[j].name==q.tables[i])
            {
                flag=true;
                break;
            }
        }
        if(flag==false)
            ret=false;
    }
    if(q.type=="create")
    {
        return !ret;
    }
    for(int i=0;i<q.columns.size() && ret && !q.sf;i++)
    {
        string s=q.columns[i];
        if(q.columns[i].find(".")!=string::npos)
        {
            bool flag=false;
            token = q.columns[i].substr(0, q.columns[i].find("."));
            s.erase(0, token.length() + 1);
            for(int j=0;j<Table.size();j++)
            {
                if(Table[j].name==token)
                {
                    //cout<<Table[j].name<<endl;
                    for(int k=0;k<Table[j].Attributes.size();k++)
                    {
                        // cout<<Table[j].Attributes[k]<<endl;
                        if(s==Table[j].Attributes[k])
                        {
                            flag=true;
                            break;
                        }
                    }
                }
            }
            if(flag==false)
                ret=false;
        }
        else
        {
            bool flag=false;
            for(int j=0;j<Table.size();j++)
                for(int k=0;k<Table[j].Attributes.size();k++)
                    if(q.columns[i]==Table[j].Attributes[k])
                    {
                        flag=true;
                        break;
                    }
            if(flag==false)
                ret=false;
        }
    }
    return ret;
}
Query parseCreate(vector<string> v)
{
    Query q;
    q.type="create";
    q.tables.push_back(v[2]);
    q.tf=true;
    for(int i=3;i<v.size();)
    {
        q.af=true;
        q.dtf=true;
        q.attributes.push_back(v[i]);
        q.data_type.push_back(v[i+1]);
        i=i+2;
    }
    return q;
}

void show(Query q)
{
    cout<<"Querytype: "<<q.type<<endl;
    if(q.tf)
    {
        cout<<"Tablename: ";
        for(int i=0;i<q.tables.size()-1;i++)
            cout<<q.tables[i]<<",";
        cout<<q.tables[q.tables.size()-1]<<endl;
    }
    if(q.type=="select")
    {
        if(q.cf)
        {
            cout<<"Columns: ";
            for(int i=0;i<q.columns.size()-1;i++)
                cout<<q.columns[i]<<",";
            cout<<q.columns[q.columns.size()-1]<<endl;
        }
        if(q.df)
        {
            cout<<"Distinct: ";
            for(int i=0;i<q.distinct.size()-1;i++)
                cout<<q.distinct[i]<<",";
            cout<<q.columns[q.distinct.size()-1]<<endl;
        }
        else
            cout<<"Distinct: NA\n";
        if(q.conf)
        {
            cout<<"Conditions: ";
            for(int i=0;i<q.condition.size()-1;i++)
                cout<<q.condition[i]<<",";
            cout<<q.condition[q.condition.size()-1]<<endl;
        }
        else
            cout<<"Conditions: NA\n";
        if(q.of)
        {
            cout<<"Orderby: ";
            for(int i=0;i<q.orderby.size()-1;i++)
                cout<<q.orderby[i]<<",";
            cout<<q.orderby[q.orderby.size()-1]<<endl;
        }
        else
            cout<<"Orderby: NA\n";
        if(q.gf)
        {
            cout<<"Groupby: ";
            for(int i=0;i<q.groupby.size()-1;i++)
                cout<<q.groupby[i]<<",";
            cout<<q.groupby[q.groupby.size()-1]<<endl;
        }
        else
            cout<<"Groupby: NA\n";
        if(q.hf)
        {
            cout<<"Having: ";
            for(int i=0;i<q.having.size()-1;i++)
                cout<<q.having[i]<<",";
            cout<<q.having[q.having.size()-1]<<endl;
        }
        else
            cout<<"Having: NA\n";
    }
    else
    {
        if(q.af)
        {
            cout<<"Attributes: ";
            for(int i=0;i<q.attributes.size()-1;i++)
                cout<<q.attributes[i]<<" "<<q.data_type[i]<<",";
            cout<<q.attributes[q.attributes.size()-1]<<" "<<q.data_type[q.data_type.size()-1]<<endl;
        }
    }
}

int pagecnt=0;
class DBSystem
{
    public:
        vector<table>Table;
        int binary_search(int start,int end,vector<pair<int,int> > mapping,int r)
        {
            vector <int> search;
            for(int i=start;i<=end;i++)
                search.push_back(mapping[i].second);
            vector<int>::iterator low=lower_bound(search.begin(),search.end(),r);
            vector<int>::iterator high=upper_bound(search.begin(),search.end(),r);
            return (low-search.begin());
        }
        vector<vector<string> > page;
        vector<pair <int,int> > mapping;
        vector <int> LRU;
        vector <bool> page_modified;
        vector <int> page_line_modified;
        vector <int> page_table;
        vector <vector<string> > cache;
        int PAGESIZE;
        int curr_size;
        int NUM_PAGES;
        string PATH_FOR_DATA;
        string config_file_path;
        /* string table1_name;
           string table2_name;*/

        int V(string tableName,string attributeName)
        {
            for(int i=0;i<Table.size();i++)
            {
                if(Table[i].name.compare(tableName)==0)
                {
                    for(int j=0;j<Table[i].Attributes.size();j++)
                        if(Table[i].Attributes[j].compare(attributeName)==0)
                            return Table[i].unique[j].size();
                }
            }
        }

        void readConfig(string configFilePath)
        {
            config_file_path=configFilePath;
            string line;
            ifstream f (configFilePath.c_str());
            int flag_begin=0,flag_end=0;
            if(f.is_open())
            {
                while(getline(f,line))
                {
                    size_t found_pagesize =line.find("PAGE_SIZE");
                    size_t found_path_for_data =line.find("PATH_FOR_DATA");
                    size_t found_num_pages =line.find("NUM_PAGES");
                    size_t found_begin =line.find("BEGIN");
                    if(flag_begin)
                    {
                        string delimiter = ", ";
                        table t;
                        t.name=line;
                        while(getline(f,line))
                        {
                            string token,s=line;
                            size_t found_end = line.find("END");
                            if (found_end!=string::npos)
                                break;
                            else
                            {
                                token = s.substr(0, s.find(delimiter));
                                token.erase( std::remove_if( token.begin(), token.end(), ::isspace ), token.end() );
                                t.Attributes.push_back(token);
                                s.erase(0, token.length() + delimiter.length());
                                s.erase( std::remove_if( s.begin(), s.end(), ::isspace ), s.end() );
                                t.Data_Type.push_back(s);
                            }
                        }
                        t.pageidx.clear();
                        Table.push_back(t);
                        flag_begin=0;
                    }
                    if (found_pagesize!=string::npos)
                    {
                        PAGESIZE=atoi(&line[found_pagesize+9]);
                    }
                    if (found_num_pages!=string::npos)
                        NUM_PAGES=atoi(&line[found_num_pages+10]);
                    if (found_path_for_data!=string::npos)
                        PATH_FOR_DATA=(&line[found_path_for_data+14]);
                    if(found_begin!=string::npos)
                        flag_begin=1;
                }
                f.close();
            }
            else
                cout << "Unable to open file";
            //   for(int i=0;i<NUM_PAGES;i++)
            // {
            //   LRU.push_back(i);
            //cache.push_back(page[i]);
            // }
        }
        void populatePageInfo()
        {
            for(int i=0;i<Table.size();i++)
            {
                Table[i].nr=0;
                Table[i].bfr=PAGESIZE;
                string DataFilePath=PATH_FOR_DATA;
                DataFilePath.append(Table[i].name);
                DataFilePath.append(".csv");
                string line;
                curr_size=0;
                int start_record_id=0,end_record_id=0;
                vector <string> temp;
                int flag=0;
                ifstream f (DataFilePath.c_str());

                //Yogesh: initialising modified bool and modifiedIdx for every table
                Table[i].modified = false;
                Table[i].modifiedIdx = 0;//value has no significance if modified = False
                Table[i].modifiedLine = 0;//value has no significance if modified = False
                vector<string>str;
                if(f.is_open())
                {
                    while(getline(f,line))
                    {
                        Table[i].nr++;
                        str.clear();
                        boost::split(str,line,boost::is_any_of(","));
                        for(int j=0;j<str.size();j++)
                            Table[i].unique[j].insert(str[j]);
                        //cout<<line<<endl;
                        if((curr_size + sizeof(line[0])*line.size())<=PAGESIZE)
                        {
                            temp.push_back(line);
                            curr_size+=(sizeof(line[0])*line.size());
                            end_record_id++;
                        }
                        else
                        {
                            //printf("dfdfds\n");
                            page.push_back(temp);
                            page_modified.push_back(false); //initialising modified bool
                            page_line_modified.push_back(0); // initialising modified line
                            page_table.push_back(i); //linking table id with page
                            Table[i].pageidx.push_back(pagecnt);
                            pagecnt++;
                            curr_size=0;
                            mapping.push_back(make_pair(start_record_id,end_record_id-1));
                            temp.clear();
                            temp.push_back(line);
                            start_record_id=end_record_id;
                            end_record_id++;
                            curr_size=sizeof(line[0])*line.size();
                        }
                    }
                }
                f.close();
                page.push_back(temp);
               // cout<<temp.size()<<endl;
                page_modified.push_back(false); //initialising modified bool
                page_table.push_back(i); // initialising modified line
                page_line_modified.push_back(0); // linking table id with page
                Table[i].pageidx.push_back(pagecnt);
                pagecnt++;
                //cout<<"pagecnt"<<pagecnt<<endl;
                temp.clear();
                mapping.push_back(make_pair(start_record_id,end_record_id-1));
                //cout<<page[Table[i].pageidx.size()-1].size()<<endl;
            }
        }

        void getRecord(string tableName, int recordId)
        {
            string record;
            int idx=-1;
            for(int i=0;i<Table.size();i++)
            {
                if(Table[i].name.compare(tableName)==0)
                {
                    for(int j=0;j<Table[i].pageidx.size();j++)
                    {
                        if(recordId<=mapping[Table[i].pageidx[j]].second && recordId>=mapping[Table[i].pageidx[j]].first)
                        {
                            idx=Table[i].pageidx[j];
                            break;
                        }
                    }
                    break;
                }
            }
            if(idx==-1)
                cout<<"Record Missing\n";
            //cout<<idx<<" "<<recordId<<'\n';
            vector<int>::iterator it;
            // cout<<idx<<endl;
            it = find (LRU.begin(), LRU.end(), idx);
            if (it != LRU.end())
            {
                cout<<"HIT"<<'\n';
                LRU.erase(it);
                int idex=it-LRU.begin();
                //cache.erase(cache.begin()+idex);
                LRU.push_back(idx);
                //cache.push_back(page[idx]);
            }
            else
            {
                //            cout<<NUM_PAGES<<endl;
                //          cout<<LRU.size()<<endl;
                if(LRU.size()<NUM_PAGES)
                {
                    cout<<"MISS"<<" "<<LRU.size()<<endl;
                    LRU.push_back(idx);
                }
                else
                {
                    cout<<"MISS"<<" "<<LRU[0]<<endl;
                    LRU.erase(LRU.begin()+0);
                    //cache.erase(cache.begin()+0);
                    LRU.push_back(idx);
                    //cache.push_back(page[idx]);
                }
            }
        }
        void insertRecord(string tableName, string record)
        {
            for(int i=0;i<Table.size();i++)
            {
                if(Table[i].name.compare(tableName)==0)
                {
                    vector<string>str;
                    boost::split(str,record,boost::is_any_of(","));
                    for(int j=0;j<str.size();j++)
                        Table[i].unique[j].insert(str[j]);
                    int idx=Table[i].pageidx[Table[i].pageidx.size()-1];
                    vector<int>::iterator it;
                    it = find (LRU.begin(), LRU.end(), idx);
                    if (it != LRU.end())
                    {
                        int idex=it-LRU.begin();
                        //		cache.erase(cache.begin()+idex);
                        LRU.erase(it);
                        LRU.push_back(idx);
                        //		cache.push_back(page[idx]);
                    }
                    else
                    {
                        if(LRU.size()<NUM_PAGES)
                        {
                            LRU.push_back(idx);
                        }
                        else
                        {
                            LRU.erase(LRU.begin()+0);
                            //cache.erase(cache.begin()+0);
                            LRU.push_back(idx);
                            //cache.push_back(page[idx]);
                        }
                        //		cache.erase(cache.begin()+0);
                        //		cache.push_back(page[idx]);
                    }
                    if((curr_size+(sizeof(record[0])*record.size()))<=PAGESIZE)
                    {
                        curr_size+=(sizeof(record[0])*record.size());
                        page[idx].push_back(record);
                        mapping[idx].second++;
                        if(!page_modified[idx])
                        {
                            page_modified[idx]=true;
                            page_line_modified[idx]=mapping[idx].second-mapping[idx].first;
                        }
                        //cout<<"Record"<<page[idx][mapping[idx].second-mapping[idx].first]<<" inserted at page "<<idx<<endl;
                        //since Table is modified once assign the bool
                        if(!Table[i].modified)
                        {
                            Table[i].modifiedIdx=idx;
                            Table[i].modifiedLine=mapping[idx].second;
                            //	cout<<"1.Table[i].modifiedLine"<<Table[i].modifiedLine<<endl;
                        }
                        Table[i].modified=true;
                        //
                    }
                    else
                    {
                        int start_record_id,end_record_id;
                        int size = Table[i].pageidx.size();
                        start_record_id = mapping[Table[i].pageidx[size-1]].second+1;
                        end_record_id=start_record_id;
                        vector<string>temp;
                        temp.push_back(record);
                        page.push_back(temp);
                        page_modified.push_back(true);
                        page_line_modified.push_back(0);
                        page_table.push_back(i);
                        mapping.push_back(make_pair(start_record_id,end_record_id));
                        Table[i].pageidx.push_back(pagecnt);
                        curr_size=0;
                        //since Table is modified once assign the bool
                        int idx=Table[i].pageidx[Table[i].pageidx.size()-1];
                        //cout<<"Record"<<page[idx][mapping[idx].second-mapping[idx].first]<<" inserted at page "<<idx<<endl;
                        //		cache.erase(cache.begin()+0);
                        LRU.erase(LRU.begin()+0);
                        LRU.push_back(pagecnt);
                        //		cache.push_back(page[pagecnt]);
                        if(!Table[i].modified)
                        {
                            Table[i].modifiedIdx=pagecnt;
                            Table[i].modifiedLine=mapping[idx].second;
                            //	cout<<"2.Table[i].modifiedLine"<<Table[i].modifiedLine<<endl;
                        }
                        Table[i].modified=true;
                        //
                        pagecnt++;
                    }
                }
            }
        }
        void flushPages()
        {
            for(int i=0;i<LRU.size();i++)
            {
                if(page_modified[LRU[i]])
                {
                    string DataFilePath=PATH_FOR_DATA;
                    DataFilePath.append(Table[page_table[LRU[i]]].name);
                    DataFilePath.append(".csv");
                    fstream f;
                    f.open(DataFilePath.c_str(), fstream::out | fstream::app);
                    int start=page_line_modified[LRU[i]];
                    int index=LRU[i];
                    cout<<"index "<<index<<endl;
                    cout<<"start "<<start<<" page index.size() " <<page[index].size()<<endl;
                    for(int j=start;j<page[index].size();j++)
                    {
                        f<<page[index][j]<<'\n';
                        cout<<"appending "<<page[index][j]<<" for table "<<Table[page_table[LRU[i]]].name<<'\n';
                    }
                    /*for(int j=index+1;j<Table[i].pageidx.size();j++)
                      {
                      cout<<"index "<<index<<endl;
                      for(int k=0;k<page[j].size();k++)
                      {
                      f<<page[j][k]<<'\n';
                      cout<<"appending "<<page[j][k]<<"for table"<<i<<'\n';
                      }
                      }*/
                    f.close();
                }
            }
        }
        void queryType(string query)
        {
            //here query is tokenized and type is checked.
            vector<string> v;
            stringstream sq(query);
            char delim =' ';
            string item;
            string item2;
            int count=0;
            while (getline(sq, item, delim))
            {
                string x=item;
                if (x.find('(')!= string::npos)
                {
                    stringstream s2(x);
                    char del='(';
                    count+=1;
                    while (getline(s2, item2, del))
                    {
                        if ( item2!="")
                            v.push_back(item2);
                    }
                }
                else if (x.find(')')!= std::string::npos)
                {
                    stringstream s2(x);
                    char del =')';
                    count-=1;
                    while (getline(s2, item2, del)){
                        if ( item2!="")
                            v.push_back(item2);
                    }
                }
                else if (x.find(',')!= std::string::npos)
                {
                    stringstream s2(x);
                    char del=',';
                    while (getline(s2, item2, del))
                        v.push_back(item2);
                }
                else
                    v.push_back(x);
            }
            if (v[0]=="create")
                createCommand(v);
            else if(v[0]=="select")
                selectCommand(v);
            else
                cout<<"Invalid Query"<<endl;
        }
        void createCommand(vector<string> v)
        {
            //parse query and create table
            Query q = parseCreate(v);
            if(validate(q,Table))
            {
                //show(q);
                ofstream file;
                file.open((q.tables[0]+".data").c_str());
                file.close();
                file.open((q.tables[0]+".csv").c_str());
                file.close();
                fstream f;
                string line;
                f.open(config_file_path.c_str(), fstream::out | fstream::app);
                f<<"BEGIN"<<"\n";
                f<<q.tables[0]<<"\n";
                for(int i=0;i<q.attributes.size()-1;i++)
                    f<<q.attributes[i]<<", "<<q.data_type[i]<<'\n';
                f<<q.attributes[q.attributes.size()-1]<<", "<<q.data_type[q.data_type.size()-1]<<endl;
                f<<"END"<<"\n";
                f.close();
            }
            else
                cout<<"Query Invalid"<<endl;
        }
        void selectCommand(vector<string> v)
        {
            //parse query
            Query q = parseSelect(v,Table);
            if(validate(q,Table))
            {
               // show(q);
                executeSelect(q,Table,page);
            }
            else
                cout<<"Query Invalid"<<endl;

        }
};
int main(int argc,char *argv[])
{
    DBSystem DB;
    DB.readConfig(argv[1]);
    DB.populatePageInfo();
    /*        for(int i=0;i<DB.Table.size();i++)
              {
              for(int j=0;j<DB.Table[i].pageidx.size();j++)
              cout<<DB.mapping[DB.Table[i].pageidx[j]].first<<" "<<DB.mapping[DB.Table[i].pageidx[j]].second<<endl;
              }*/
    /* for(int i=0;i<DB.Table.size();i++)
       {
       cout<<DB.Table[i].name<<endl;
       for(int j=0;j<DB.Table[i].Attributes.size();j++)
       cout<<DB.Table[i].Attributes[j]<<" "<<DB.Table[i].Data_Type[j]<<endl;
       }*/
    string str,query;
    pageSize = DB.PAGESIZE;
    query.clear();
    char delim=' ';
    int t;
    getline (cin, str);
    t=atoi(str.c_str());
    while(t--)
    {
        getline (cin, str);
        DB.queryType(str.substr(0,str.length()-1));
        cout<<endl;
        /*		if(str[str.length()-1]==';')
                {
                query=query+" "+str.substr(0,str.length()-1);
                DB.queryType(query);
                query.clear();

                }
                else
                if(query=="")
                query=query+str.substr(0,str.length());
                else
                query=query+" "+str.substr(0,str.length());*/
    }
    /*while(1)
      {
      string str;
      cin>>str;
      cout<<str[0];
      if(feof(stdin))
      {
      break;
      }
      else
      DB.queryType(str);
      cout<<endl;
      }*/
    //DB.insertRecord("table1",s1);
    //DB.insertRecord("table2",s2); table_name => string; record => comma separated string;
    //DB.getRecord("table_name",record_id); table_name=> string ; record_id => int
    //DB.flushPages();
    return 0;
}
