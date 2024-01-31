#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

struct MinHeapNode
{

    char data;

    unsigned freq;

    struct MinHeapNode *left, *right;
};

struct MinHeap
{

    unsigned size;

    unsigned capacity;

    struct MinHeapNode **array;
};

struct MinHeapNode *
newNode(char data, unsigned freq)
{

    struct MinHeapNode *temp =
        (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;

    temp->data = data;

    temp->freq = freq;

    return temp;
}

struct MinHeap *
createMinHeap(unsigned capacity)
{

    struct MinHeap *minHeap =
        (struct MinHeap *)malloc(sizeof(struct MinHeap));

    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array =
        (struct MinHeapNode **)malloc(minHeap->capacity *
                                      sizeof(struct MinHeapNode *));

    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b)
{

    struct MinHeapNode *t = *a;

    *a = *b;

    *b = t;
}

void

minHeapify(struct MinHeap *minHeap, int idx)
{

    int smallest = idx;

    int left = 2 * idx + 1;

    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)

        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)

        smallest = right;

    if (smallest != idx)
    {

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap *minHeap)
{

    return (minHeap->size == 1);
}

struct MinHeapNode *
extractMin(struct MinHeap *minHeap)
{

    struct MinHeapNode *temp = minHeap->array[0];

    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;

    minHeapify(minHeap, 0);

    return temp;
}

void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode)
{

    ++minHeap->size;

    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];

        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

struct MinHeap *
buildMinHeap(char data[], int freq[], int size)
{

    struct MinHeap *minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)

        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;

    int i;

    for (i = (minHeap->size - 2) / 2; i >= 0; --i)

        minHeapify(minHeap, i);

    return minHeap;
}

struct MinHeapNode *
buildHuffmanTree(char data[], int freq[], int size)
{

    struct MinHeapNode *left, *right, *top;

    struct MinHeap *minHeap = buildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap))
    {

        left = extractMin(minHeap);

        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);

        top->left = left;

        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void printCodes(struct MinHeapNode *root, int arr[], int top)
{

    if (root->left)
    {

        arr[top] = 0;

        printCodes(root->left, arr, top + 1);
    }

    if (root->right)
    {

        arr[top] = 1;

        printCodes(root->right, arr, top + 1);
    }

    if (!(root->left) && !(root->right))
    {

        printf("%c: ", root->data);

        for (int i = 0; i < top; ++i)
        {

            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

void

HuffmanCodes(char data[], int freq[], int size)
{

    struct MinHeapNode *root = buildHuffmanTree(data, freq, size);

    int arr[MAX_TREE_HT], top = 0;

    printCodes(root, arr, top);
}
int main()
{
    char input_string[MAX_TREE_HT];

    printf("Enter a string: ");
    fgets(input_string, sizeof(input_string), stdin);
    input_string[strcspn(input_string, "\n")] = '\0';

    int size = strlen(input_string);

    char data[MAX_TREE_HT];
    int freq[MAX_TREE_HT];
    int unique_chars = 0;

    for (int i = 0; i < size; i++)
    {
        char current_char = input_string[i];

        if (current_char == ' ' || current_char == '\t' || current_char == '\n' || current_char == '\r')
        {
            continue;
        }

        int j;

        for (j = 0; j < unique_chars; j++)
        {
            if (data[j] == current_char)
            {
                freq[j]++;
                break;
            }
        }

        if (j == unique_chars)
        {
            data[unique_chars] = current_char;
            freq[unique_chars] = 1;
            unique_chars++;
        }
    }

    printf("\nHuffman Codes:\n");
    HuffmanCodes(data, freq, unique_chars);

    return 0;
}
