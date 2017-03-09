#include "lib.h"
#define black 1
#define red 0
typedef book _type;
//����С�ںţ�α
int less(_type a,_type b){return a.book_ID<b.book_ID;}
//���ص��ںţ�α
int equal(_type a,_type b){return a.book_ID==b.book_ID;}
typedef void (*FUNC)(_type);
//����������ڵ���
typedef struct btn{
    struct btn *parent,*left_son,*right_son;
    int color; _type data;
}btn;
//�������ڵ㹹�캯����α
btn *new_btn(_type d,btn *pr,int c){
    btn *p=(btn*)malloc(sizeof(btn));
    p->data=d;p->parent=pr;p->color=c;
    p->left_son=p->right_son=NULL;
    return p;
}
//���ݺ�������巵�ؽڵ���ɫ
int _color(btn *p){
    return p?p->color:black;
}
//�жϽڵ��Ƿ�Ϊ����
int is_left(btn *p){
    if(!p)return 3;if(!p->parent)return 2;
    if(p==p->parent->left_son)return 1;
    else return 0;
}
//�ڽڵ����Һ��ӵ�����·��ؽڵ������������
btn *succ(btn *p){
    if(!p)return (btn*)NULL;
    btn *q=p->right_son;
    while(q&&q->left_son)q=q->left_son;
    return q;
}
//������dataֵ���������Ǹ�����һ��ֻ����һ�Σ�Ц
void swap(_type *a,_type *b){
    _type t=*a;*a=*b;*b=t;
}
//���ؽڵ���ֵܽڵ�
btn *bro(btn *n){
    return is_left(n)?n->parent->right_son:n->parent->left_son;
}
//���ýڵ��к�ɫ���ӣ����ظú�ɫ����
btn *red_son(btn *n){
    if(!n)return (btn*)NULL;
    btn *s=n->left_son;
    if(!_color(n->right_son))s=n->right_son;
    return s;
}
//�������
typedef struct RB_tree{
    btn *_root,*_hot;
}RB_tree;
//��������캯����α
RB_tree *new_tree(){
    RB_tree *p=(RB_tree*)malloc(sizeof(RB_tree));
    p->_root=p->_hot=NULL;
    return p;
}
//���������������ʵ�һ�д������ģ�������
void in_order(btn *n,FUNC visit){
    if(!n)return;
    in_order(n->left_son,visit);
    visit(n->data);//printf("(%d) ",n->color);
    in_order(n->right_son,visit);
}
//�����������
void pre_order(btn *n,FUNC visit){
    if(!n)return;
    visit(n->data);
    pre_order(n->left_son,visit);
    pre_order(n->right_son,visit);
}
//3+4�ع�
btn *updata34(btn *p1,btn *p2,btn *p3,\
              btn *s1,btn *s2,btn *s3,btn *s4){
    p2->left_son=p1;p1->parent=p2;
    p2->right_son=p3;p3->parent=p2;
    p1->left_son=s1;if(s1)s1->parent=p1;
    p1->right_son=s2;if(s2)s2->parent=p1;
    p3->left_son=s3;if(s3)s3->parent=p3;
    p3->right_son=s4;if(s4)s4->parent=p3;
    return p2;
}
//�ж��ع����Ͳ������������ڵ�ĺ���
btn *updata_balance(btn *g,btn *p,btn *n,RB_tree *T){
    int mode=is_left(g),Case=is_left(p)*2+is_left(n);
    btn *P,*G=g->parent;
    switch(Case){
    case 0:P=updata34(g,p,n,\
        g->left_son,p->left_son,n->left_son,n->right_son);
        break;
    case 1:P=updata34(g,n,p,\
        g->left_son,n->left_son,n->right_son,p->right_son);
        break;
    case 2:P=updata34(p,n,g,\
        p->left_son,n->left_son,n->right_son,g->right_son);
        break;
    case 3:P=updata34(n,p,g,\
        n->left_son,n->right_son,p->right_son,g->right_son);
        break;}
    if(mode==0)G->right_son=P;
    else if(mode==1)G->left_son=P;
    else if(mode==2)T->_root=P;
    P->parent=G;
    return P;
}
//���������С���ZigOrZag����
void zig_or_zag(btn *p,btn *n,RB_tree *T){
    btn *g=p->parent,*s1,*s2,*s3; int mode=is_left(p);
    if(less(p->data,n->data)){
        s1=p->left_son;s2=n->left_son;s3=n->right_son;
        n->left_son=p;p->parent=n;
        n->right_son=s3;if(s3)s3->parent=n;
        p->left_son=s1;if(s1)s1->parent=p;
        p->right_son=s2;if(s2)s2->parent=p;}
    else {
        s1=n->left_son;s2=n->right_son;s3=p->right_son;
        n->left_son=s1;if(s1)s1->parent=n;
        n->right_son=p;p->parent=n;
        p->left_son=s2;if(s2)s2->parent=p;
        p->right_son=s3;if(s3)s3->parent=p;}
    n->parent=g;
    if(g){if(mode)g->left_son=n;else g->right_son=n;}
    else T->_root=n;
    n->color=black;p->color=red;
}
//����˫��ȱ�ݣ��Ӻ���������ɫ����
void double_red_1(btn *g,btn *p,btn *n,RB_tree *T){
    btn *P=updata_balance(g,p,n,T);
    P->color=black;P->left_son->color=P->right_son->color=red;
}
//����˫��ȱ�ݣ�������
void double_red(btn *g,btn *p,btn *n,RB_tree *T){
    if(is_left(p)?_color(g->right_son):_color(g->left_son))
    {double_red_1(g,p,n,T);return;}
    g->color=g==T->_root?black:red;
    g->left_son->color=g->right_son->color=black;
    if(g->parent&&g->parent->color==red){
        double_red(g->parent->parent,g->parent,g,T);}
}
//����˫��ȱ�ݣ��Ӻ���������ɫ����
void double_black_1(btn *g,btn *p,btn *n,RB_tree *T){
    int c=_color(g);
    btn *G=updata_balance(g,p,n,T);
    G->color=c;
    G->left_son->color=G->right_son->color=black;
}
//����˫��ȱ�ݣ�������
void double_black(btn *n,RB_tree *T){
    btn *b=(T->_hot->left_son==n)?(T->_hot->right_son):(T->_hot->left_son);
    btn *p=T->_hot,*rs=red_son(b);
    if(!_color(b)){zig_or_zag(p,b,T);
        double_black(n,T);return;}
    else if(_color(b->left_son)&&_color(b->right_son)){
        if(_color(p)){b->color=red;
            T->_hot=p->parent;if(T->_hot)double_black(p,T);}
        else {
            T->_hot->color=black;b->color=red;}
    }
    else double_black_1(p,b,rs,T);
}
//��������������֧��������Ц
btn *search(_type a,RB_tree *T){
    btn *p=T->_root; T->_hot=NULL;
    while(p&&!equal(p->data,a)){
        T->_hot=p;
        p=less(a,p->data)?p->left_son:p->right_son;}
    return p;
}
void insert(_type a,RB_tree *T){
    btn *p=search(a,T); if(p)return;
    if(!T->_hot){T->_root=new_btn(a,0,black);return;}
    if(less(a,T->_hot->data))T->_hot->left_son=p=new_btn(a,T->_hot,red);
    else T->_hot->right_son=p=new_btn(a,T->_hot,red);
    if(T->_hot->color==black)return;
    double_red(T->_hot->parent,T->_hot,p,T);
}
void erase(_type a,RB_tree *T){
    btn *p=search(a,T),*pr,*son,*q=succ(p);
    int mode; if(!p)return;
    if(p->left_son&&p->right_son){swap(&p->data,&q->data);p=q;}
    son=p->left_son?p->left_son:p->right_son;
    pr=T->_hot=p->parent;
    mode=is_left(p);
    if(son)son->parent=pr;
    if(!pr){T->_root=son;if(son)son->color=black;}
    else {
    if(mode)pr->left_son=son;else pr->right_son=son;
    if(_color(p)&&_color(son))double_black(son,T);
    if(son)son->color=black;}
    free(p);
}
