// Create, init, and return a new Node with value val
listNode * CreateNode(int val)
{
    // Allocate mem for the new Node + check for mem fail
    listNode * newNode = malloc(sizeof(Node));

    // Create Node with value "val"
    newNode->value = val;

    // Set next pointer to NULL
    newNode->next = NULL;

    // Return the newly created node
    return newNode;
}

// Count the number of integers in a given file
int countFromFile(char * file_name)
{
    FILE * fptr = fopen(file_name, "r");
    if(fptr==NULL) return EXIT_FAILURE;
    int value=0,count=0;
    while(fscanf(fptr, "%d", &value)==1) count++;
    fclose(fptr);
    return count;
}

// Insert value v at the beginning of the LL
void LinkedListInsert(listNode ** head, int v)
{
    listNode * newNode = CreateNode(v);
    newNode->next = *head;
    *head = newNode;
}

// Reverse a linked list, returning nothing
void LinkedListReverse(listNode ** head)
{
    listNode * prev = NULL;
    listNode * current = *head;
    listNode * next = NULL;
    while(current != NULL)
    {
        // Copy the next node
        next = current->next;
        // Reverse the current node's pointer
        current->next = prev;
        // Move pointers by 1 position
        prev = current;
        current = next;
    }
    *head = prev;
}

// Create a linked list with values given in file located at path "name"
void LinkedListCreate(listNode ** head, char * name)
{
    // Variable declaration
    int ind=0;
    int tmp;

    // We are given a string corresponding to a file with input data
    // Lets open it
    FILE * finput = fopen(name,"r");

    // Check fail...
    if(finput==NULL) return;

    // Lets get a count of items in this file
    int count = countFromFile(name);

    // Lets create the LL by inserting each of these values one at a time
    while(ind<count)
    {
        if(fscanf(finput,"%d",&tmp) != 1) fclose(finput);
        LinkedListInsert(head,tmp);
        ind++;
    }

    // Flip the LL around
    LinkedListReverse(head);
    fclose(finput);
}

void DeleteNextNode(listNode ** head, int val)
{
    // If nothing in list, do nothing
    if(*head==NULL) return;

    // Store the head
    listNode * temp = *head;
    listNode * newNext = NULL;

    // If the node we are looking for is at the very first node
    if(temp->value == val)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    // Traverse! Break when reach node right before target
    while(((temp->next) != NULL) && (temp->next->value != val))
    {  temp = temp->next;  }

    // Check if we over-traversed...
    if((temp->next) == NULL) return;

    // Save the pointer to the next of the node to be deleted
    newNext = temp->next->next;

    // Unlink the node from the LL
    free(temp->next);

    // Append the rest of the list using pointer to the next of deleted
    temp->next = newNext;
}

// This function returns 1 if a value exists in any LL, returns 0 else
int LinkedListExists(listNode * head, int val)
{
    listNode * temp = head;
    while(temp != NULL)
    {
        if(temp->value == val) return 1;
        temp=temp->next;
    }
    return 0;
}

// This function will remove repetitions of a linked list value
void RemoveDuplicate(listNode * headRef)
{
    // Declare some pointers
    listNode * prevSeenHead = NULL;
    listNode * tempHead = headRef;
    listNode * buildingHead = NULL;

    while(tempHead->next != NULL)
    {
        if(LinkedListExists(prevSeenHead,tempHead->value))
        {
            /* DONT INSERT THIS NODE */
            // Increment the original list
            tempHead = tempHead->next;
        }
        else
        {
            // Append the previously seen list
            LinkedListInsert(&prevSeenHead, tempHead->value);
            // Append the originals list
            LinkedListInsert(&buildingHead, tempHead->value);
            // Increment the original list
            tempHead = tempHead->next;
        }
    }

    // Take care of that last node...
    if(!LinkedListExists(prevSeenHead,tempHead->value))
    {  LinkedListInsert(&buildingHead, tempHead->value);  }

    // Reverse the list
    LinkedListReverse(&buildingHead);

    // Set the head  == the temp LL
    headRef = buildingHead;

    // Free the helper linked lists
    LinkedListDestroy(&buildingHead);
    LinkedListDestroy(&prevSeenHead);
    free(prevSeenHead);
    free(buildingHead);
}

// This function will delete the entire linked list and free memory
void LinkedListDestroy(listNode ** head)
{
    listNode * current = *head;
    while(current!=NULL)
    {
        *head = current->next;
        free(current);
        current=*head;
    }
}
