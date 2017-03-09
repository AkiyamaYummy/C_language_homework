//��ʼ�ڴ��С
#define INIT_RAM 2
//����һЩ��
typedef long long vector_type;
typedef void (*v_FUNC)(vector_type);
//��ʱ���Ժ���PRINT
void v_PRINT(vector_type a){printf("%I64d ",a);}
//����������
typedef struct vector{
    vector_type *_head; Rank _size,_ram;
}vector;
//�������캯��
vector *new_vector(){
    vector *V=(vector*)malloc(sizeof(vector));
    V->_size=0;V->_ram=INIT_RAM;
    V->_head=(vector_type*)malloc(sizeof(vector_type)*V->_ram);
    return V;
}
//��������ڴ��������
void to_big(Rank i,vector *V){
    if(V->_size+i<=V->_ram)return;
    V->_ram=2*(V->_size+i);
    vector_type *new_head=\
    (vector_type*)malloc(sizeof(vector_type)*V->_ram);
    for(i=0;i<V->_size;i++)new_head[i]=V->_head[i];
    free(V->_head);V->_head=new_head;
}
void to_little(vector *V){
    if(V->_ram/2<=V->_size)return;
    V->_ram=V->_ram/2<INIT_RAM?INIT_RAM:V->_ram/2;
    vector_type *new_head=\
    (vector_type*)malloc(sizeof(vector_type)*V->_ram);
    Rank i;for(i=0;i<V->_size;i++)new_head[i]=V->_head[i];
    free(V->_head);V->_head=new_head;
}
//������ĩβ��ӽڵ�
void push_back(vector_type a,vector *V){
    to_big(1,V);
    V->_head[V->_size++]=a;
}
//������ĩβɾ���ڵ�
void pop_back(vector *V){
    if(!V->_size)return; V->_size--;
    to_little(V);
}
//����������нڵ�
void clear(vector *V){
    V->_size=0;V->_ram=INIT_RAM;
    free(V->_head);
    V->_head=(vector_type*)malloc(sizeof(vector_type)*V->_ram);
}
//�����������нڵ�
void for_each(vector *V,v_FUNC visit){
    Rank i;for(i=0;i<V->_size;i++)visit(V->_head[i]);
}
