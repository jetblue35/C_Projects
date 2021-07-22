int count_node(struct TreeNode* root)
{
	
    if(root == NULL)	/*Base condition.*/
    {
   	    return 0;
    }

    /*Count left and right side and root(+1).*/	
   	return  ( count_node(root.left) + count_node(root.right) + 1);
}
int size = count_node(struct TreeNode* root);

int array_index = 0;
int* arr;	/*Holds the address.*/
arr = (int*)malloc(size * sizeof(int));






/*This function finds the number of node in tree recursively.*/
void inorder_search(struct TreeNode* root)
{
	
    if(root == NULL)
    {
        return;
    }
    
    inorder_search(root -> left);
    if(NULL != root->left)				/*Holds the left side node's address.*/
    {
        arr[array_index] = root -> left;
        array_index++;
    }
    if(NULL != root -> right)			/*Holds the right side node's address.*/
    {
        arr[array_index] = root -> right;
        array_index++;
    }
    
    inorder_search(root -> right);
}


int are_all_uniqe()
{
	int i, j;
    for(i = 0; i < size; ++i)
    {
        for(j = i + 1; j < size; ++j)
        {
            if(arr[i] == arr[j])	/*If there are anomaly (Node have two parents).(Return 1)*/
            {
                return 1;
            }
        }
    }
    
    return 0;		
}

int check_tree(struct TreeNode *root)
{
    inorder(root);					/*Function calls.*/
    return are_all_uniqe();
}