typedef struct tLinkedListNode{
	void		*memAddress;
	vc_uint16	file;
	vc_uint16	line;
	vc_uint16	size;
}tLinkedListNode;
typedef struct tLinkedList  {
	tLinkedListNode data;
	struct tLinkedList* next;
	struct tLinkedList* prev;
}tLinkedList;
tLinkedList* vc_heap_head;
tLinkedList* GetNewNode(void *x,unsigned int size, unsigned int file, unsigned int line) 
{
	tLinkedList* newNode = (tLinkedList*)pvPortMalloc(sizeof(tLinkedList));	
	newNode->data.memAddress = x;
	newNode->data.file = file;
	newNode->data.line = line;
	newNode->data.size = size;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

//Inserts a Node at head of doubly linked list
void LL_InsertAtHead(void *x,unsigned int size, unsigned int file, unsigned int line) {
	tLinkedList* newNode = GetNewNode(x,size,file,line);
	if(vc_heap_head == NULL) {
		vc_heap_head = newNode;
		return;
	}
	vc_heap_head->prev = newNode;
	newNode->next = vc_heap_head; 
	vc_heap_head = newNode;
}

//Inserts a Node at tail of Doubly linked list
void LL_InsertAtTail(void *x, unsigned int size, unsigned int file, unsigned int line) {
	tLinkedList* temp = vc_heap_head;
	tLinkedList* newNode = GetNewNode(x,size,file,line);
	if(vc_heap_head == NULL) {
		vc_heap_head = newNode;
		return;
	}
	while(temp->next != NULL) temp = temp->next;
	temp->next = newNode;
	newNode->prev = temp;
}
void LL_DeleteNode(void *x)
{
    tLinkedList* temp = vc_heap_head, *prev;
    if (temp != NULL && temp->data.memAddress == x){
        vc_heap_head = temp->next;
        vPortFree(temp);
        return;
    } 
    while (temp != NULL && temp->data.memAddress != x){
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next; 
    vPortFree(temp);
}
int LL_get_len()
{
	tLinkedList* temp = vc_heap_head;
	vc_uint8	linkedlist_count= 0;	
	while(temp != NULL) {
		temp = temp->next;
		linkedlist_count++;
	}
	return linkedlist_count;
}