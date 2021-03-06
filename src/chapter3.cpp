#include "chapter3.h"
#include <sstream>

namespace chapter3{
    //释放二叉树的内存空间，将二叉树置空
    void BTreeDestroy(treeNode *tree)
    {
        if(tree==NULL)
        {
            return;
        }
        BTreeDestroy(tree->left);
        BTreeDestroy(tree->right);
        delete tree;
    }

    string getSpace(int cnt){
        string space;
        for(int i=0;i<cnt;++i)
            space.push_back(' ');
        return space;
    }
    void printInorder(treeNode *head,int height,string to,int len){
        if(!head)
            return;
        printInorder(head->right,height+1,"v",len);
        string val;
        std::ostringstream os;
        os<<to<<head->value<<to;
        val=os.str();
        int lenM=val.size();
        int lenL=(len-lenM)/2;
        int lenR=len-lenM-lenL;
        val=getSpace(lenL)+val+getSpace(lenR);
        cout<<getSpace(height*len)+val<<endl;
        printInorder(head->left,height+1,"^",len);
    }
    void printTree(treeNode *root){
        cout<<"Binany Tree:"<<endl;
        printInorder(root,0,"H",17);
        cout<<endl;
    }

    void preorderWalk(treeNode *root){
        if(root){
            stack<treeNode*> s;
            s.push(root);
            while(!s.empty()){
                treeNode *cur=s.top();
                cout<<cur->value<<",";
                s.pop();
                if(cur->right)
                    s.push(cur->right);
                if(cur->left)
                    s.push(cur->left);
            }
            cout<<endl;
        }
    }

    void inorderWalk(treeNode *root){
        if(root){
            stack<treeNode*> s;            
            while(!s.empty()||root){
                if(root){
                    s.push(root);
                    root=root->left;
                }
                else{
                    root=s.top();
                    s.pop();
                    cout<<root->value<<" ";
                    root=root->right;
                }
            }
            cout<<endl;
        }
    }
    // 使用两个栈
    void postrderWalkV1(treeNode *root){
        if(root){
            stack<treeNode*> s1;
            stack<treeNode*> s2;
            s1.push(root);
            while(!s1.empty()){
                treeNode *cur=s1.top();
                s1.pop();
                s2.push(cur);
                if(cur->right)
                    s1.push(cur->right);
                if(cur->left)
                    s2.push(cur->left);
            }
            while(!s2.empty()){
                treeNode *cur=s2.top();
                cout<<cur->value<<" ";
                s2.pop();
            }
            cout<<endl;
        }
    }

    void postorderWalk(treeNode *root){
        if(root){
         
            stack<treeNode*> s;
            s.push(root);
            treeNode *cur=NULL;
            treeNode *h=root;//最近访问过的点
            
            while(!s.empty()){
                cur=s.top();
                if(cur->left&&h!=cur->left&&h!=cur->right)//表明左子树和右子树都没有处理过
                    s.push(cur->left);
                else if(cur->right&&h!=cur->right)//表明右子树没有处理过
                    s.push(cur->right);
                else{//左右子树已经处理
                    cout<<s.top()->value<<" ";
                    s.pop();
                    h=cur;
                }
            }
            cout<<endl;
        }
    }

    string intTostr(int val){        
        ostringstream os;
        os<<val;
        return os.str();
    }
    int strToint(const string &s){
       istringstream is(s);
       int num=0;
       is>>num;
       return num;
    }

    vector<string> split(const string& src, string separate_character)
    {
        vector<string> strs;
        
        int separate_characterLen = separate_character.size();//分割字符串的长度,这样就可以支持如“,,”多字符串的分隔符
        int lastPosition = 0,index = -1;
        while (-1 != (index = src.find(separate_character,lastPosition)))
        {
            strs.push_back(src.substr(lastPosition,index - lastPosition));
            lastPosition = index + separate_characterLen;
        }
        string lastString = src.substr(lastPosition);//截取最后一个分隔符后的内容
        if (!lastString.empty())
            strs.push_back(lastString);//如果最后一个分隔符后还有内容就入队
        return strs;
    }

    string serialBypreorder(treeNode *root){
        if(!root)
            return string("#!");
        // cout<<intTostr(root->value)<<endl;   
        string ret=intTostr(root->value)+"!";
        ret+=serialBypreorder(root->left);
        ret+=serialBypreorder(root->right);
        return ret;
    }

    treeNode *reconverByprevorder(queue<string> &q){
        string value=q.front();
        q.pop();
        if(value=="#")
            return NULL;
        treeNode *head=new treeNode(strToint(value));
        head->left=reconverByprevorder(q);
        head->right=reconverByprevorder(q);
        return head;
    }

    treeNode* recoverByprevstring(string prevStr){
        vector<string> vals=split(prevStr,"!");
// #define _DEBUG
#ifdef _DEBUG
        for(auto val:vals)
            cout<<val<<endl;

#endif        
        queue<string> q;
        for(auto estr:vals)
            q.push(estr);
        return reconverByprevorder(q);
    }

    string serialBylevel(treeNode *root){
        if(!root)
            return string("#!");
        string res=intTostr(root->value)+"!";
        queue<treeNode*> q;
        q.push(root);
        while(!q.empty()){
            root=q.front();
            q.pop();
            if(root->left){
                res+=intTostr(root->left->value)+"!";
                q.push(root->left);
            }
            else
                res+="#!";
            if(root->right){
                res+=intTostr(root->right->value)+"!";
                q.push(root->right);
            }
            else
                res+="#!";
        }
        return res;
    }
    treeNode* createNodeFromstr(const string &str){
        if(str=="#")
            return NULL;
        return new treeNode(strToint(str));
    }

    treeNode* reconBylevel(const string &str){
        vector<string> values=split(str,"!");
        int index=0;
        treeNode *root=createNodeFromstr(values[index++]);
        queue<treeNode*> q;
        if(root)
            q.push(root);
        treeNode *node=NULL;    
        while(!q.empty()){
            node=q.front();
            q.pop();
            node->left=createNodeFromstr(values[index++]);
            node->right=createNodeFromstr(values[index++]);
            if(node->left)
                q.push(node->left);
            if(node->right)
                q.push(node->right);
        }
        return root;
    }

    int preorderAndGotSum(treeNode *head,int sum,int preSum,
                int level,int maxLen,unordered_map<int,int> &sumMap){
        if(!head)
            return maxLen;
        int curSum=preSum+head->value;
        if(sumMap.find(curSum)==sumMap.end())
            sumMap.insert(make_pair(curSum,level));
        if(sumMap.find(curSum-sum)!=sumMap.end())
        {
            auto iter=sumMap.find(curSum-sum);
            maxLen=max(level-iter->second,maxLen);            
        }
        maxLen=preorderAndGotSum(head->left,sum,curSum,level+1,maxLen,sumMap);
        maxLen=preorderAndGotSum(head->right,sum,curSum,level+1,maxLen,sumMap);
        if(level==(sumMap.find(curSum)->second))
            sumMap.erase(curSum);
        return maxLen;        
    }

    int getMaxlen(treeNode *root,int sum){
        unordered_map<int,int> sumMap;
        sumMap.insert(make_pair(0,0));
        return preorderAndGotSum(root,sum,0,1,0,sumMap);
    }

    treeNode* postOrder(treeNode *head,vector<int> &record){
        if(!head){
            record[0]=0;//存取节点个数
            record[1]=INT_MAX;//存储最小值
            record[2]=INT_MIN;//存储子数最大值
            return NULL;
        }
        int value=head->value;
        treeNode *left=head->left,*right=head->right;
        treeNode *lBST=postOrder(left,record);
        int lSize=record[0];
        int lMin=record[1];
        int lMax=record[2];
        treeNode *rBst=postOrder(right,record);
        int rSize=record[0];
        int rMin=record[1];
        int rMax=record[2];
        record[1]=min(lMin,value);
        record[2]=max(rMax,value);
        if(left==lBST&&right==rBst&&lMax<value&&value<rMin){
            record[0]=lSize+rSize+1;
            return head;
        }
        record[0]=max(lSize,rSize);
        return lSize>rSize?lBST:rBst;
    }
    
    treeNode* largestSubBST(treeNode *root){
        vector<int> record(3,0);
        return postOrder(root,record);
    }


    bool isBSTNode(treeNode *h,treeNode *n,int val){
        if(!h)
            return false;
        if(h==n)
            return true;
        return isBSTNode(h->value>val?h->left:h->right,n,val);
    }

    int maxTOPO(treeNode *h,treeNode *n){
        if(h&&n&&isBSTNode(h,n,n->value))
            return maxTOPO(h,n->left)+maxTOPO(h,n->right)+1;
        return 0;
    }

    int bstTopoSize1(treeNode *head){
        if(!head)
            return 0;
        int maxVal=maxTOPO(head,head);
        // cout<<maxVal<<endl;
        maxVal=max(bstTopoSize1(head->left),maxVal);
        maxVal=max(bstTopoSize1(head->right),maxVal);
        return maxVal;
    }
    //flag is true means goto the right edge,otherwise false means goto left edge
    int modifyHash(treeNode *node,int v,unordered_map<treeNode*,record> &m,bool flag){
        auto iter=m.find(node);
        if(!node||(iter==m.end()))
            return 0;
        record red=iter->second;
        if((flag&&node->value>v)||(!flag&&node->value<v))
        {
            m.erase(iter);
            return red.l+red.r+1;
        }
        else{
            int minus=modifyHash(flag?node->right:node->left,v,m,flag);
            if(flag){
                red.r=red.r-minus;                
            }
            else{
                red.l=red.l-minus;
            }
            m.insert(make_pair(node,red));
            return minus;
        }
    }

    int postorderFind(treeNode *h,unordered_map<treeNode*,record> &m){
        if(!h)
            return 0;
        int ls=postorderFind(h->left,m);//当前节点的左子树的最大拓扑点数
        int rs=postorderFind(h->right,m);//当期节点的走字数的最大拓扑点数
        modifyHash(h->left,h->value,m,true);
        modifyHash(h->right,h->value,m,false);
        auto lr=m.find(h->left);
        auto rr=m.find(h->right);
        int lbst=(lr==m.end())?0:(lr->second.l+lr->second.r+1);//算入本节点以后左子树的贡献
        int rbst=(rr==m.end())?0:(rr->second.l+rr->second.r+1);//算入本节点以后右字数的贡献
        m.insert(make_pair(h,record(lbst,rbst)));
        return max(lbst+rbst+1,max(ls,rs));
    }

    int bstTopoSize2(treeNode *root){
        unordered_map<treeNode*,record> m;
        return postorderFind(root,m);
    }

    void printByLevel(treeNode *root){
        if(!root)
            return;
        queue<treeNode*> q;
        int level=1;
        q.push(root);
        treeNode *last=root,*nextLast=NULL;
        cout<<"Level "<<(level++)<<":";
        while(!q.empty()){
            root=q.front();
            q.pop();
            cout<<root->value<<" ";
            if(root->left){
                q.push(root->left);
                nextLast=root->left;
            }
            if(root->right){
                q.push(root->right);
                nextLast=root->right;
            }
            if(root==last&&!q.empty()){
                cout<<"\nLevel "<<(level++)<<":";
                last=nextLast;
            }
        }
        cout<<endl;
    }

    void printLevelAndOrient(int level,bool lr){
        cout<<"Level "<<level<<" from ";
        cout<<(lr?"left to right:":"right to left:");
    }

    void printByZigZag(treeNode *root){
        if(!root)
            return;
        deque<treeNode*> dq;
        int level=1;
        bool lr=true;
        treeNode *last=root,*nlast=NULL;
        dq.push_front(root);
        printLevelAndOrient(level++,lr);
        while(!dq.empty()){
            if(lr){
                root=dq.front();
                dq.pop_front();
                if(root->left){
                    nlast=(nlast==NULL)?root->left:nlast;
                    dq.push_back(root->left);
                }
                if(root->right){
                    nlast=(nlast==NULL)?root->right:nlast;
                    dq.push_back(root->right);
                }
            }
            else{
                root=dq.back();
                dq.pop_back();
                if(root->right){
                    nlast=(nlast==NULL)?root->right:nlast;
                    dq.push_front(root->right);
                }
                if(root->left){
                    nlast=(nlast==NULL)?root->left:nlast;
                    dq.push_front(root->left);
                }
            }
            cout<<root->value<<" ";
            if(root==last&&!dq.empty()){
                lr=!lr;
                last=nlast;
                nlast=NULL;
                cout<<endl;
                printLevelAndOrient(level++,lr);
            }
        }
        cout<<endl;
    }

    bool check(treeNode *root,treeNode *t2){
        if(t2==NULL)
            return true;
        if(root==NULL||root->value!=t2->value)
            return false;
        return check(root->left,t2)&&check(root->right,t2);
    }

    bool contains(treeNode *t1,treeNode *t2){
        return contains(t1,t2)||contains(t1->left,t2)||contains(t1->right,t2);
    }

    int getTreeHeight(treeNode *root,int level,bool &flag){
        if(!root)
            return level;
        int lH=getTreeHeight(root->left,level+1,flag);
        if(!flag)
            return level;
        int rH=getTreeHeight(root->right,level+1,flag);
        if(!flag)
            return level;
        if(abs(lH-rH)>1)
            flag=false;
        return max(lH,rH);
    }

    bool isBalancedTree(treeNode *root){
        bool flag=true;
        getTreeHeight(root,1,flag);
        return flag;
    }

/*
判断子数组start-end之间是否为后序，
less记录最后一个小于arr[end]元素的位置;
more记录第一个大于arr[end]元素的位置；
less!=more不符合条件，否则继续递归判断左右两个子数组
*/
    bool isPost(int arr[],int start,int end){
        if(start==end)
            return true;
        int less=-1,more=end;
        for(int i=0;i<end;++i){
            if(arr[i]<arr[end])
                less=i;
            else
                more=(more==end)?i:more;
        }
        if(less==-1||more==end)
            return isPost(arr,start,end-1);
        if(less+1!=more)
            return false;
        return isPost(arr,start,less)&&isPost(arr,more,end);
    }

    bool isPostArray(int arr[],int n){
        if(arr==NULL||n==1)
            return true;
        return isPost(arr,0,n-1);
    }

/*
Morris神级遍历方法，空间复杂度O（1）
*/
    void morrisInorder(treeNode *root){
        if(!root)
            return ;
        treeNode *cur1=root,*cur2=NULL;
        while(cur1){
            cur2=cur1->left;
            if(cur2){
                while(cur2->right&&cur2->right!=cur1)
                    cur2=cur2->right;
                if(cur2->right==NULL){//调整结构，令cu2->righ指向其后继也就是cur1
                    cur2->right=cur1;
                    cur1=cur1->left;
                    continue;
                }
                else
                    cur2->right=NULL;//恢复结构
            }
            cout<<cur1->value<<" ";
            cur1=cur1->right;            
        }
        cout<<endl;
    }
        
    bool isSubTree(treeNode *root1,treeNode *root2){
    	string t1Str=serialBypreorder(root1);
    	string t2Str=serialBypreorder(root2);
    	return kmpMatch(t1Str,t2Str)!=-1;
    }
}
