
struct elemento{
    int key;
};

struct pila{
    struct elemento elements[3];
    int count = 0;
    int tope = 3;
};

int isEmpty(struct pila);
int isFull(struct pila);
int push(struct pila*, struct elemento);
int pop(struct pila*, struct elemento *);
int count (struct pila *);
bool isInside(struct pila *, int);

/* 
 * Comprobamos si la pila esta vacia.
 */
inline int isEmpty(pila p){
   if(p.count == 0) {return 1;}
   return 0;
}
inline int isFull(pila p){
   if(p.count > p.tope) {return 1;}
   return 0;
}
inline int push(pila *p,elemento new_element){

    if(p == nullptr){return -1;}
    if(isFull(*p) == 1){return -2;}

    p->elements[p->count] = new_element;
    p->count++;

    return 1;
}
inline int pop(pila *p, elemento *delete_element){
    if(p == nullptr){return -1;}
    if(isFull(*p) == 1){return -2;}
    
    struct elemento resp = (*p).elements[(*p).count -1];
    p->count--;

    delete_element->key =resp.key;

    return 1;
}

inline bool isInside(pila *p, int key)
{
    bool inside = false;
    int i = 0;
    while(!inside && i<=p->count){
        if(p->elements[i].key == key){
            inside =true;
        }
        i++;
    }
    return inside;
}